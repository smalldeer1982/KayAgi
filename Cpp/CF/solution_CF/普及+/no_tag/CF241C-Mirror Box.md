# Mirror Box

## 题目描述

Mirror Box is a name of a popular game in the Iranian National Amusement Park (INAP). There is a wooden box, $ 10^{5} $ cm long and $ 100 $ cm high in this game. Some parts of the box's ceiling and floor are covered by mirrors. There are two negligibly small holes in the opposite sides of the box at heights $ h_{l} $ and $ h_{r} $ centimeters above the floor. The picture below shows what the box looks like.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF241C/6424a01d70e5009585312ab434deff869a3c6956.png)In the game, you will be given a laser gun to shoot once. The laser beam must enter from one hole and exit from the other one. Each mirror has a preset number $ v_{i} $ , which shows the number of points players gain if their laser beam hits that mirror. Also — to make things even funnier — the beam must not hit any mirror more than once.

Given the information about the box, your task is to find the maximum score a player may gain. Please note that the reflection obeys the law "the angle of incidence equals the angle of reflection".

## 说明/提示

The second sample is depicted above. The red beam gets $ 10+50+5+35+8+2=110 $ points and the blue one gets $ 120 $ .

The red beam on the picture given in the statement shows how the laser beam can go approximately, this is just illustration how the laser beam can gain score. So for the second sample there is no such beam that gain score 110.

## 样例 #1

### 输入

```
50 50 7
10 F 1 80000
20 T 1 80000
30 T 81000 82000
40 T 83000 84000
50 T 85000 86000
60 T 87000 88000
70 F 81000 89000
```

### 输出

```
100
```

## 样例 #2

### 输入

```
80 72 9
15 T 8210 15679
10 F 11940 22399
50 T 30600 44789
50 F 32090 36579
5 F 45520 48519
120 F 49250 55229
8 F 59700 80609
35 T 61940 64939
2 T 92540 97769
```

### 输出

```
120
```

# 题解

## 作者：recollect_i (赞：10)

不妨光从洞中射出的时候是向下边的，如果是向上边的可以把图翻转过来。可以发现，当反射次数确定的时候，路径是确定的，所以可以每局反射次数，然后模拟整个过程。在原题中，光在反射而镜子和盒子不动，但可以让光走一条直线而镜子和盒子反复翻转，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/d6faebdv.png)

其中黑色框是原来的盒子，绿色框是盒子翻转的结果，黄色实线是原来的光线，黄色虚线是将光线第一段延长形成的射线，它与右侧绿色线段的交点与原盒子中右侧的洞对应，两个红色点都表示第二次遇到的镜子。

经过这样转化，就光线变成了比较简单的直线。首先求出右侧洞对应点的坐标。设反射次数为 $i$，当 $i$ 为偶数，坐标为 $\left(10^5,-100i+h_r\right)$；当 $i$ 为奇数时，坐标为 $\left(10^5,-100(i-1)-h_r\right)$。然后就可以求出光线所在直线的解析式，然后求出这条直线每次反射的位置，及与翻转后的盒子的交点，判断这个点是否在镜子上并且没有使用过这个镜子，然后计算贡献。时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int n, l, r, nu, nd;
char s[3];
struct node{
	double l, r;
	int v;
	bool operator <(const node &w) const
	{
		return l < w.l;
	}
}up[N], down[N];
bool usu[N], usd[N];
double k, b, x;
int res;

void jxs(double ya, double yb)
{
	b = ya;
	k = (yb - ya) / 1e5;
}
void jd(double y)
{
	x = (y - b) / k;
}
void solve()
{
	for(int i = 1; i <= n; i ++ )
	{
		memset(usu, 0, sizeof usu);
		memset(usd, 0, sizeof usd);
		int cnt = 0;
		if(i & 1)
		{
			double pr = -r - 100 * (i - 1);
			jxs(l, pr);
			for(int j = 0; j < i; j ++ )
			{
				jd(-100 * j);
				if(j & 1)
				{
					int k = upper_bound(up + 1, up + nu + 1, (node){x, 0, 0}) - up - 1;
					if(x > up[k].r || usu[k]) cnt = -2e9;
					else cnt += up[k].v;
					usu[k] = true;
				}
				else
				{
					int k = upper_bound(down + 1, down + nd + 1, (node){x, 0, 0}) - down - 1;
					if(x > down[k].r || usd[k]) cnt = -2e9;
					else cnt += down[k].v;
					usd[k] = true;
				}
			}
		}
		else
		{
			double pr = r - 100 * i;
			jxs(l, pr);
			for(int j = 0; j < i; j ++ )
			{
				jd(-100 * j);
				if(j & 1)
				{
					int k = upper_bound(up + 1, up + nu + 1, (node){x, 0, 0}) - up - 1;
					if(x > up[k].r || usu[k]) cnt = -2e9;
					else cnt += up[k].v;
					usu[k] = true;
				}
				else
				{
					int k = upper_bound(down + 1, down + nd + 1, (node){x, 0, 0}) - down - 1;
					if(x > down[k].r || usd[k]) cnt = -2e9;
					else cnt += down[k].v;
					usd[k] = true;
				}
			}
		}
		res = max(res, cnt);
	}
}

int main()
{
	scanf("%d%d%d", &l, &r, &n);
	for(int i = 1; i <= n; i ++ )
	{
		int a, b, c;
		scanf("%d%s%d%d", &a, s, &b, &c);
		if(*s == 'T') up[ ++ nu] = {(double)b, (double)c, a};
		else down[ ++ nd] = {(double)b, (double)c, a};
	}
	
	sort(up + 1, up + nu + 1), sort(down + 1, down + nd + 1);
	solve();
	l = 100 - l, r = 100 - r;
	swap(nu, nd);
	for(int i = 1; i <= n; i ++ ) swap(up[i], down[i]);
	solve();
	
	printf("%d\n", res);
	return 0;
}
```

---

