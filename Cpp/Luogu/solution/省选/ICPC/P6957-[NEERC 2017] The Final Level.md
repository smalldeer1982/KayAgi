# [NEERC 2017] The Final Level

## 题目描述

用长度为 $n$ 的 L 型方块摆在二维网格平面上，仅通过方块从 $(0,0)$ 走到 $(a,b)$。

## 说明/提示

对于 $100\%$ 的数据，$1 \le m \le 100, -10^8 \le a, b  \le 10^8, 2 \le n \le 10^8$。

## 样例 #1

### 输入

```
2
2 3 2
4 -1 3
```

### 输出

```
2
1 1 0 0
1 2 2 3
2
0 0 2 -2
3 -3 5 -1
```

# 题解

## 作者：Graphcity (赞：1)

首先可以通过翻转坐标系（也就是 $x,y$ 取相反数）的方式使得终点满足 $x\ge 0,y\ge 0$。

我们希望尽量让从左上到右下，拐点在左下方的 “L” 形块接通 $(0,0)$ 到 $(x,y)$。不妨令当前点在 $(a,b)$，且必然有 $(x,y)$ 在 L 形块的右下方，分类讨论：

![](https://cdn.luogu.com.cn/upload/image_hosting/wtjq69i2.png)

- $(a,b)$ 走一步即可到达 $(x,y)$：
  - $x\in [a,a+n-1]$，$y\in (b,b+n]$（黄色部分）：直接填 $(x-n+1,b+1)$，$(b+1,b+n)$。
  - $x\in[a-n+1,a)$，$y\in (b,b+n]$（橙色部分）：这个时候需要把 L 形块上下翻转，填 $(x+n-1,b+1)$，$(x,b+n)$。
  - $x\in (a,a+n]$，$y\in [b-n+1,b]$（红色部分）：直接填 $(a+1,y)$，$(a+n,y+n-1)$。
  - $x\in (a,a+n]$，$y\in (b,b+n-1]$（蓝色部分）：直接填 $(a+1,b)$，$a+n,b+n-1$。

- 如果还走不到：
  - $x\in (a-n,a]$，直接往下平移。
  - $y\in (b-n,b]$：直接往右平移。
  - $x-a\ge y-b$：往右下角平移，左上角端点在 $(a+1,b)$。
  - $x-a<y-b$：往右下角平移，左上角端点在 $(a,b+1)$。

对于这题，有一点特别注意的：固定两个端点会得到两个不同的 L 形块，所以本题区分 L 形块的依据之一就是端点的顺序。一定要写对端点的顺序。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

int T,n,a,b,opx,opy;
vector<array<int,4>> ans;

inline void Solve()
{
    cin>>a>>b>>n; opx=1,opy=1;
    if(a<0) a=-a,opx*=-1;
    if(b<0) b=-b,opy*=-1;
    if(a==0 && b==0) {printf("0\n"); return;}
    int x=a,y=b; a=0,b=-1;
    while(1)
    {
        if(y>b && x>=a && x<=a+n-1 && y<=b+n)
        {
            ans.push_back({x-n+1,b+1,x,b+n});
            break;
        }
        if(y>b && y<=b+n && x<a)
        {
            ans.push_back({x+n-1,b+1,x,b+n});
            break;
        }
        if(b>=0 && x>a && x<=a+n && y<=b)
        {
            ans.push_back({a+1,y,a+n,y+n-1});
            break;
        }
        if(b>=0 && x>a && x<=a+n && y<=b+n-1)
        {
            ans.push_back({a+1,b,a+n,b+n-1});
            break;
        }
        if(x>=a-n+1 && x<=a)
        {
            ans.push_back({a-n+1,b+1,a,b+n}),b+=n;
            continue;
        }
        if(b>=0 && y>=b-n+1 && y<=b)
        {
            ans.push_back({a+1,b-n+1,a+n,b}),a+=n;
            continue;
        }
        if(b>=0 && x-a>y-b)
        {
            ans.push_back({a+1,b,a+n,b+n-1}),a+=n,b+=n-1;
            continue;
        }
        ans.push_back({a,b+1,a+n-1,b+n}),a+=n-1,b+=n;
        continue;
    }
    cout<<ans.size()<<endl;
    for(auto i:ans)
    {
        int a=i[0]*opx,b=i[1]*opy,c=i[2]*opx,d=i[3]*opy;
        swap(a,c),swap(b,d);
        printf("%d %d %d %d\n",a,b,c,d);
    }
    ans.clear();
}

int main()
{
    cin>>T;
    while(T--) Solve();
    return 0;
}
```

---

## 作者：zhylj (赞：1)

不妨设目标点在第一象限。

我们先考虑整个 L 字形连通块的右上角最远能到哪里，不难发现除了第一块可以令最远点到达 $(n-1,n-1)$ 之外，后面的 L 字形都可以令某一维加 $n-1$，另一位加 $n$。

于是考虑一个贪心，记当前能到达的最远点为 $(x,y)$：

- 若当前 $x\lt a$，$y\lt b$，那么选取相距更远的一维加上 $n$，另一维加上 $n-1$（如下图第一二块）。
- 否则，我们只令还未超过目标点的那一维加 $n$（如下图第二三块）。
- 若某时刻 $x \ge a$ 且 $y \ge b$，则终止贪心过程。

不难发现，上述贪心过程花费的连通块个数是答案的下界，我们断言其就是答案：在上述过程结束后，目标点 $(a,b)$ 右侧一定存在一个与 $(0,0)$ 连通的格子，且距离它不超过 $n-1$，我们可以将这个图形向左平移一段距离，使得这个格子与 $(a,b)$ 重合，然后就构造完毕了。

时间复杂度 $\mathcal O(\sum\operatorname{ans})$。

![例子](https://i.loli.net/2021/11/11/WL7CeuniBUVJpEY.png)

```cpp
int main() {
	int test_case_cnt = 1; rd(test_case_cnt);
	while(test_case_cnt--) {
		int a, b, n, si_x = 1, si_y = 1; rd(a, b, n);
		if(a < 0) si_x = -1, a = -a;
		if(b < 0) si_y = -1, b = -b;
		std::vector <std::pair <pii, pii> > ans;
		ans.push_back(mkp(mkp(n - 1, n - 1), mkp(0, 0)));
		int cur_x = n - 1, cur_y = n - 1;
		while(a > cur_x || b > cur_y) {
			if(a > cur_x && b > cur_y) {
				if(a - cur_x > b - cur_y) {
					ans.push_back(mkp(mkp(cur_x + n, cur_y + n - 1), mkp(cur_x + 1, cur_y)));
					cur_x += n; cur_y += n - 1;
				} else {
					ans.push_back(mkp(mkp(cur_x + n - 1, cur_y + n), mkp(cur_x, cur_y + 1)));
					cur_x += n - 1; cur_y += n;
				}
			} else if(a > cur_x) {
				ans.push_back(mkp(mkp(cur_x + n, cur_y), mkp(cur_x + 1, cur_y - n + 1)));
				cur_x += n;
			} else {
				ans.push_back(mkp(mkp(cur_x, cur_y + n), mkp(cur_x - n + 1, cur_y + 1)));
				cur_y += n;
			}
		}
		int d_x = a - cur_x;
		for(auto &i : ans) {
			i.fi.fi += d_x;
			i.se.fi += d_x;
		}
		printf("%d\n", (int)ans.size());
		for(auto i : ans) {
			printf("%d %d %d %d\n",
				si_x * i.fi.fi, si_y * i.fi.se,
				si_x * i.se.fi, si_y * i.se.se
			);
		}
	} return 0;
}
```

---

