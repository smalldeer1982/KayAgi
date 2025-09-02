# [ICPC 2024 Xi'an I] Triangle

## 题目描述

在平面直角坐标系中有三个点 $A(a, 0)$、$B(0, b)$、$C(0, 0)$。定义三角形 $ABC$ 的大小为属于它的正方形的数量。

对于整数 $x, y$，一个正方形由四个点 $(x, y)$、$(x + 1, y)$、$(x, y + 1)$、$(x + 1, y + 1)$ 定义。如果一个正方形有一半或更多的部分在三角形内，我们认为它属于三角形。

例如，当 $a = 8, b = 6$ 时，三角形 $ABC$ 的大小为 $24$。下图显示了哪些正方形被计入三角形中。

![](https://cdn.luogu.com.cn/upload/image_hosting/3fnqi74y.png)

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
6 8```

### 输出

```
24```

## 样例 #2

### 输入

```
5 5
```

### 输出

```
15```

## 样例 #3

### 输入

```
1 999999```

### 输出

```
500000```

# 题解

## 作者：Cypher_404 (赞：10)

# P10562 [ICPC2024 Xi'an I] Triangle 题解

终于，第 5 篇了。

## 分析题意

题目给出 $A$ 的坐标：$(a,0)$，和 $B$ 的坐标：$(0,b)$，再加上已知的原点 $O$：$(0,0)$。

这三个点构成了一个直角三角形，需要你求出有多少个正方形在其中。（不足一个的如果占到了面积的 $50\%$ 及以上算，否则不算）。

## 分析做法

看到 $1 \le a,b \le 10^6$ 并不大，可以考虑暴力模拟。

具体模拟思路：

算出直线 $AB$ 的解析式，算出每一个的 $x$ 坐标所对应的 $y$，然后使用梯形面积公式（上底加下底的和除以 2）。

看到面积 $\ge 50\%$ 考虑四舍五入。

四舍五入：给浮点数类型的数字加上 $0.5$ 再强制转化成整形即可。可自行模拟检验。

## 坑点：

1. 卡精度：可以用 double 类型再乘上一个浮点数，如：$1.0000$。

2. 读题不仔细或思考不全：答案可能会爆 int，$\frac {10^6 \times 10^6} {2}$ 达到了惊人的 $5\times 10^{11}$ 必须使用 long long。 

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
double k,n,m;//浮点数类型
long long ans;//答案：可能会炸 int
double opt=1.00000;//乘数，减小精度误差
int main()
{
    cin>>n>>m;
    k=n*opt/-m;//计算 k
    for(int i=0;i<(int)m;i++)//从 1~m，虽然不加 (int) 也可以
    {
        double t=n+(2*i+1)*k/2;//简化以后的梯形公式
        t+=0.5;//四舍五入
        ans+=(long long)t;//强制转换成 long long 类型。实测：转换成 int 也可以。
    }
    cout<<ans;//输出
    return 0;
}
```

其实还是比较简单的一道题，希望大家多多点赞。

---

## 作者：lihl (赞：7)

**本题解所有除法都是 C++ 意义下 $\text{int}$ 的向下取整整除。**

不难发现在朴素状态下答案就是三角形的面积。

但还存在一种特殊情况。

如果 $\cfrac{a}{\gcd(a,b)}$ 和 $\cfrac{b}{\gcd(a,b)}$ 都为奇数，那么：

- 如果 $a=b$，那么斜边正好穿过所有位于斜边上的正方形，易得答案为 $\cfrac{ab+\gcd(a,b)}{2}$ 个。
- 否则 $a \ne b$，那么根据割补法，有 $\cfrac{ab}{2}+\cfrac{\gcd(a,b)}{2}$ 个区域被补成正方形，即有 $\cfrac{ab+\gcd(a,b)}{2}$ 个大于 $\cfrac{1}{2}$ 的区域。

综上，普通情况的答案是 $\cfrac{ab}{2}$ ，特殊情况的答案是 $\cfrac{ab+\gcd(a,b)}{2}$。

---

## 作者：鸡枞_ (赞：2)

# P10562 [ICPC2024 Xi'an I] Triangle
## 题意
数出三角形覆盖区域中占据面积大于等于 $\frac{1}{2}$ 的格点的个数。
## 思路
按列枚举，考虑每一列的中点处的纵坐标，记为 $y=\frac{b}{a}\times x$。如果 $y - \lfloor y\rfloor \ge \frac{1}{2}$，则当前列的答案为 $\lfloor y\rfloor + 1$，否则为 $\lfloor y\rfloor$。时间复杂度为 $O(n)$。注意需要开 `double`。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;

const int MAXN = 1e6 + 10;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

mt19937 rnd(114514);

void solve()
{
	ll a, b;
	cin >> a >> b;

	ll cnt = 0;
	for(double i = 0.5; i <= a; i += 1)
	{
		double res = i * b / a;
		cnt += int(res);
		if(res - int(res) >= 0.5) ++cnt;
	}
	cout << cnt << "\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int Task = 1;
	// cin >> Task;
	while(Task--)
	{
		solve();
	}

	return 0;
}
```

---

## 作者：LINYUHENG (赞：2)

# P10562 [ICPC2024 Xi'an I] Triangle 题解
[题目](https://www.luogu.com.cn/problem/P10562)  
## 题意
题目给出 $A$ 的坐标：$(a,0)$，和 $B$ 的坐标 $(0,b)$，再加上已知的原点 $O$：$(0,0)$。

这三个点构成了一个直角三角形，需要你求出有多少个正方形在其中。（不足一个的如果占到了面积的 $\frac{1}{2}$ 及以上算，否则不算）
## 做法
我们看到数据范围 $1≤a,b≤10^6$ 并不大，可以考虑暴力模拟。

### 具体模拟思路：

算出直线 $AB$ 的解析式，算出每一个的 $x$ 坐标所对应的 $y$，然后使用梯形面积公式（上底加下底的和除以 2）。

看到面积 $≥\frac{1}{2}$ 考虑四舍五入。

四舍五入：给浮点数类型的数字加上 $0.5$ 再强制转化成整形即可。可自行模拟检验。
## 注意！！！
1. 卡精度：可以用 double 类型再乘上一个浮点数，如： $1.0000$。
2. 十年 OI 一场空，不开 long long 见祖宗
# code
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
double k,n,m;
long long ans;//答案
double opt=1.00000;//乘数，减小精度误差（见注意1）
int main(){
    cin>>n>>m;
    h=n*opt/-m;//计算 h
    for(int i=0;i<(int)m;i++){
        double t=n+(2*i+1)*h/2;//梯形公式
        t+=0.5;//四舍五入法
        ans+=(long long)t;//强制转换成 long long 类型。
    }
    cout<<ans;
    return 0;//拜拜
}

---

## 作者：zxh923 (赞：1)

# P10562 [ICPC2024 Xi'an I] Triangle 题解

[题目传送门](https://www.luogu.com.cn/problem/P10562)

### 思路

我们看到这个图形，考虑进行分治，把它分成整块的和不是整块的。

例如样例被分成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/goei0pyc.png)

这里小三角形的个数就是 $\gcd(x,y)$，$x,y$ 为大三角形边长，因为其斜边除了与 $y$ 轴的交点，共有这么多个，这就是小三角形的右下角。

接下来我们考虑，如果一个三角形的两边长互质，那么他的超过半格的数量就是它的面积上取整。

对于整块的部分，大概形如这样，可以用等差数列求和公式计算。

例如这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/njq6qtts.png)

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l,r; 
int merge(int l,int r){
	int d=__gcd(l,r);
	if(d==1)return floor(1.0*l*r/2+0.5);//如果已经互质
	return d*merge(l/d,r/d)+(r/d)*(d-1)*l/2;//否则分成多个三角和正方形部分
}
signed main(){
	cin>>l>>r;
	cout<<merge(l,r);
	return 0;
}
```

---

## 作者：huet (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10562)
## 题意
- 求给定三角形覆盖的格子数。
- 覆盖指有大于**等于**一半的面积在三角形内。
## 分析
首先，假设只有覆盖超过一半的格子。\
考虑由另一个全等的三角形与其组成的矩形，则单个三角形覆盖的格子数为 $\left\lfloor\dfrac{a\times b}{2}\right\rfloor$。

接下来考虑覆盖一半的情况。\
对于正方形而言，我们知道一重要性质，即穿过其中心的直线将其分为面积相等的两部分。 \
因此，仅需考虑在 $l_{AB}:y=-\dfrac{b}{a}x+b$ 上每一个横坐标为 $k+0.5(k \le a,k\in N)$ 的点，对应的纵坐标是否形如 $m+0.5(m\in N)$。 \
对于每一个 $x=i+0.5$，
$$y=-\dfrac{b}{a}(i+0.5)+b=-\dfrac{b(2i-1)}{2a}+b$$

即，当 $a\mid {b(2i-1)}$ 且 $2\nmid \dfrac{b(2i-1)}{a}$ 时，该格恰好有一半被三角形所覆盖。

考虑到覆盖一半的格子是对称的，因此已有一半计入前一部分中，则总覆盖的格子数为 $\left\lfloor\dfrac{a\times b}{2}\right\rfloor$+$\left\lceil\dfrac{cnt}{2}\right\rceil$。

注意到两边长值域均为 $[1,10^6]$，结果可能爆 int，开 long long。 \
时间复杂度 $O(a)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,cnt,y;
int main(){
	cin>>a>>b;
	for(int i=0;i<a;i++){
		y=b*(2*i-1);
		if(y%a==0 && y/a%2!=0) cnt++;
	}
	cout<<a*b/2+(cnt+1)/2;
	return 0;
}
```

---

