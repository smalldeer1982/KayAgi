# [NWRRC 2016] Integral Polygons

## 题目描述

Ingrid 在一个遥远的国家经营着一家多边形商店。她只出售具有整数坐标的凸多边形。她的顾客更喜欢可以以适当方式切割成两半的多边形，即切割应是直线，起点和终点在多边形的顶点上，并且两半都不为空且面积为整数。切割多边形的适当方式越多，多边形就越昂贵。

例如，左边的多边形有三种适当的切割方式，而右边的多边形有两种。

![](https://cdn.luogu.com.cn/upload/image_hosting/fei0xc33.png)

商店里的多边形质量总是很优秀，所以业务正在扩展。现在 Ingrid 需要一些自动化工具来确定适当切割多边形的方式数量。这对她的商店非常重要，否则你将花费大量时间来设定价格——想象一下为一辆中型货车的多边形设定价格需要多少时间。你能帮助 Ingrid 编写这个工具吗？

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
7 3
3 5
1 4
2 1
5 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 1
3 1
5 5
1 3
```

### 输出

```
2
```

# 题解

## 作者：catandcode (赞：2)

计算几何+状压，个人感觉是道好题，用最基础的奇偶变换搞人心态。

Provicy 大佬的思路非常清晰，我的对叉积的优化也来自于他，但像我这样的蒟蒻可能看不懂大佬的题解，所以我来写一篇。第一篇题解，如果有不足还请指出，欢迎 hack。
## 前置
本题需要运用叉积的知识。

首先是 $O(n^2)$ 的暴力判断，很明显是无法通过的，但我们可以对其进行优化。

由于题目给出全部坐标均为整点，根据叉积公式 $(x_1-x_0)\cdot(y_2-y_0)-(x_2-x_0)\cdot(y_1-y_0)$，可以看出返回叉积值必然为整数，而三角形的面积是叉积的一半。据此，我们可以根据奇偶性判断面积是否为整数，同时也避免了冗杂的计算。

对于输入的整点，可以直接与 $1$ 做与运算，利用前缀和处理面积。

这里先说一下我这里说的前缀和处理一般情况的面积的含义。

![](https://cdn.luogu.com.cn/upload/image_hosting/22v07ubk.png)

对于这样一个多边形，首先是计算 $AB\times AC$，累加到面积中，然后计算 $AC\times AD$，以此类推，这样对于任意的 $s[i]-s[j]$，计算的就是 $Ai$ 和 $Aj$ 所截面积。

对于任意数据，由于只需要考虑奇偶两种情况，可以对叉积的运算式进行优化。

如果原点坐标（单指横坐标或纵坐标，下同）是偶数，所得向量坐标的奇偶性（相对于终点，下同）是没有改变的，若为奇数，向量的奇偶性相反，但由于是对于两个终点都取反，最后影响可以抵消。对于原公式中的加减法，奇偶相加减得奇，偶偶或奇奇相加减得偶，这恰好和异或运算的规则相同，于是公式可以更改为 $(x_1\cdot y_2)\operatorname{xor}(x_2\cdot y_1)$.

同时时间复杂度的部分优化也在这里。由于我们可以剔除原点的影响，就没有必要分别计算从不同原点出发的前缀和，可以直接用一个前缀和数组表示。

这边要注意一下，原点是要从 $n$ 开始的，这是为了从第一个点开始有面积面积，将第一条边加入计数，当然也可以更改循环，但是这个比较麻烦。~~我在这里卡了好久 qaq~~

特判一下整个图形面积为奇数，这种情况显然无解。
## DP
由于只考虑奇偶性，我们可以定义一个三维的数组 $dp_{i,j,k}$，$j$ 表示出发点的横坐标，$k$ 表示出发点的纵坐标，$i$ 表示从原点到出发点的面积，在每个顶点考虑之后将其加入 dp 数组。这里我将 $i$ 这一维放到了最后，因为这一维是由出发点坐标和终点时累计面积决定的。逆运算仍然是异或，~~是不是很神奇，~~ 具体过程可以参考代码。

为了不重复计数，我们对于对角线的一般计数方式是只考虑 $i$ 至 $n$ 的对角线，这也营造了一种类似于单调性的性质。即若倒叙考虑，对于任意一个顶点，只会与前面遍历过的顶点相组合，这也满足了 dp 的一大性质。

但在实现之后会有一个问题，测试输出与样例输出并不吻合，且刚好相差 $n$。

手推一下实现过程，可以发现 $(i,i-1)$ 这一对无序点对是不符合对角线条件的，但是递推仍会将其考虑进去，所以最后 $ans$ 的结果要减去 $n$。

最终时间复杂度 $O(n)$。
## 代码
~~冷知识：short 类型的空间占用是小于 bool 类型的。~~

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ll long long
#define pre(x) x==1?n:x-1
using namespace std;
int aa,bb;
struct point
{
	short x,y;
	void give(){ x=abs(aa)&1,y=abs(bb)&1; }
	short operator ^(point a){ return (x*a.y)^(a.x*y); }
}p[200005];//个人习惯在结构体中初始化和重载，减少码量
int n;
short sum[200005];
ll ans,dp[2][2][2];
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>aa>>bb;
		p[i].give();
	}
	for(int i=1;i<=n;++i) sum[i]=sum[i-1]^(p[i]^p[pre(i)]);
	if(sum[n]&1) { cout<<0<<endl; return 0; }
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<=1;++j)
			for(int k=0;k<=1;++k)
			{
				point e=(point){j,k};
				short temp=sum[i]^(p[i]^e);
				ans+=dp[temp][j][k];
			}
		++dp[sum[i]][p[i].x][p[i].y];
	}
	cout<<ans-n<<endl;
	return 0;
}

```

---

## 作者：Provicy (赞：2)

$\text{Problem}:$[Integral Polygons](https://codeforces.com/gym/101142/attachments/download/4765/20162017-acmicpc-neerc-northern-subregional-contest-en.pdf)

$\text{Solution}:$

前置知识：用叉积算三角形面积。

把凸多边形看作若干个三角形拼接而成，面积也可以用叉积求出。而整点凸多边形的面积乘 $2$ 一定是整数，这提示我们用叉积算凸多边形的面积时只需考虑其奇偶性即可。

首先特判凸包面积不为整数的情况。然后统计满足 $i$ 到 $j$ 的凸包面积为整数的无序点对 $(i,j),\lvert i-j\rvert>1$ 的个数。可以用前缀和维护 $1$ 到 $i$ 的凸包面积，这样可以在 $O(1)$ 的时间内求出 $i$ 到 $j$ 的凸包面积，时间复杂度 $O(n^{2})$。

考虑只需要知道凸包面积是否是整数，这说明无论是面积还是坐标，都只存在 $0/1$ 两个状态。那么对于一个 $i$，它的坐标和前缀面积的组合只有 $8$ 种情况，这提示我们可以用桶去记录。时间复杂度优化至 $O(n)$。

注意统计时，$(i,i-1)$ 是不满足条件的，但是会被计算在内。所以将答案减去 $n$ 即可。

$\text{Code}:$

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define int long long
#define ri register
#define mk make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define is insert
#define es erase
using namespace std; const int N=400010;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar();
	return s*w;
}
int n;
struct Node { int x,y; }e[N];
int p[N],Ans,qz[N],F[2][2][2];
signed main()
{
	n=read();
	for(ri int i=1;i<=n;i++)
	{
		e[i].x=read(), e[i].y=read();
		e[i].x=abs(e[i].x)&1, e[i].y=abs(e[i].y)&1;
	}
	e[0]=e[n];
	for(ri int i=1;i<=n;i++)
	{
		p[i]=(e[i].x*e[i-1].y)^(e[i-1].x*e[i].y);
		qz[i]=qz[i-1]^p[i];
	}
	if(qz[n]&1) return puts("0")&0;
	for(ri int i=1;i<=n;i++)
	{
		for(ri int x=0;x<2;x++)
		for(ri int y=0;y<2;y++)
		{
			int gg=qz[i]^((x*e[i].y)^(y*e[i].x));
			Ans+=F[gg][x][y];
		}
		F[qz[i]][e[i].x][e[i].y]++;
	}
	printf("%lld\n",Ans-n);
	return 0;
}
```

---

