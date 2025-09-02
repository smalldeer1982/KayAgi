# Polygon

## 题目描述

给定一个凸 $n$ 边形，将这个 $n$ 边形沿顶点连线分割 $k$ 次，每条分割线不能相交，得到 $k+1$ 个小多边形。问分割出的多边形面积最小值最大是多少。

## 样例 #1

### 输入

```
8 4
-2 -4
2 -2
4 2
1 5
0 5
-4 4
-5 0
-5 -1```

### 输出

```
11```

## 样例 #2

### 输入

```
6 3
2 -2
2 -1
1 2
0 2
-2 1
-1 0```

### 输出

```
3```

# 题解

## 作者：JWRuixi (赞：3)

~~算面积没加绝对值……~~

- 题意

给定凸 $n$ 边形 $\{a_1,a_2\dots a_n\}$，求将切成 $k + 1$ 个无交的部分中面积的最小值的最大值。

- 分析

首先考虑二分答案，将问题转化成能否将原多边形切成 $k+1$ 个部分使得每个部分面积均大于等于 $w$。

因为任意两个部分无交，所以可以考虑区间 dp，设 $f_{i,j}$ 表示区间 $[i,j]$ 最多分成多少部分，$g_{i,j}$ 为在部分最多的前提下凸多边形 $\{a_i,\dots,a_j\}$ 剩余的面积。

考虑转移即枚举一个 $k \in (i,j)$，直接转移就行了，$f_{i,j}=\max\limits_{k} f_{i,k}+f_{k,j}+[w\le g_{i,k}+g_{k,j}+\text{area}(a_i,a_j,a_k)]$。

$\text{area}(a,b,c)$ 表示有点 $a,b,c$ 组成的三角形的面积，由于每次最多增加一块，所以这样做是正确的。

时间复杂度 $\mathcal O(n^3\log w)$。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define int long long
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(205);
int n, lim, f[maxn][maxn], g[maxn][maxn];

struct Point {
	int x, y;
	inline Point operator + (const Point &rhs) const {
		return {x + rhs.x, y + rhs.y};
	}
	inline Point operator - (const Point &rhs) const {
		return {x - rhs.x, y - rhs.y};
	}
	inline int operator * (const Point &rhs) const {
		return x * rhs.y - y * rhs.x;
	}
} a[maxn];

inline int calc (Point a, Point b, Point c) {
	return abs((b - a) * (c - a));
}

inline bool check (int w) {
	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));
	for (int len = 3; len <= n; ++len) {
		for (int i = 1, j = i + len - 1; i <= n; ++i, ++j) {
			for (int k = i + 1; k < j; ++k) {
				int s = g[i][k] + g[k][j] + calc(a[i], a[j], a[k]);
				if (f[i][j] < f[i][k] + f[k][j] + (s >= w)) f[i][j] = f[i][k] + f[k][j] + (s >= w), g[i][j] = s >= w ? 0 : s;
				else if (f[i][j] == f[i][k] + f[k][j] && s < w) g[i][j] = max(g[i][j], s);
			}
		}
	}
	return f[1][n] >= lim + 1;
}

signed main () {
	n = read(), lim = read();
	for (int i = 1; i <= n; i++) a[i] = {read(), read()};
	int l = 0, r = 1e18, mid, res = -1;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (check(mid)) l = mid + 1, res = mid;
		else r = mid - 1;
	}
	write(res);
    return 0;
}
```

---

## 作者：JQ6561 (赞：3)

看这道题还没有题解，正好做到，自己发一篇

这道题还是比较套路的，感觉洛谷评蓝合理，$CF$的$3000$真的有些离谱
 
$1.$首先，题目要求最小值最大，本能地想到**二分答案**

$2.$接下来就该考虑如何对一个确定的最小面积$w$进行可行性判定了

$3.$由于是不规则图形，且有只能用顶点连线将进行分割的条件限制，因此可以得出结论：**贪心不可行**

$4.$考虑到是在一个可以视作圆环的凸多边形上做操作，且任意两条线不能相交，没有后效性，有没有感觉有些熟悉，这就是**区间DP**的模板呀

$5.$确定了算法方向，考虑如何设计状态

$6.$我们希望让分的块数$\ge k+1$，退一步说，我们想让分的块数尽量多，在当前分完块后，我们当然希望让手里的分块方案继续分块的潜力尽可能更大，那也就是占用位置尽量小

$7.$于是就可以愉快地设出**DP方程**了，设$dp_{i,j}=(n,m)$表示第$i$至第$j$号点组成的多边形中，最多可以分出$n$块，在此基础上，最少占用$m$的面积

$8.$进行转移，每次枚举中间点为未被分割的点，可以证明，前后两端区间的未占用区域必定联通，且总面积满足$S_1<w,S_2<w\to S<2w$（剩余面积必定小于$w$，要不然就直接多分一块了）因此，转移时只需讨论是否能够多分一块的问题

$9.$如果发现对于一个$w$，$dp_{1,n}\ge k+1$，那么答案合法

$10.$**算多边形面积的公式（鞋带定理）：**

对于一个已知每一个点坐标$(x_i,y_i)$的多边形，有

$2S=\sum_{i=1}^n x_iy_{i+1}-x_{i+1}y_i$

感兴趣的可以自己学学怎么推导，这里直接当一个定理用了

---

## 作者：Purslane (赞：0)

# Solution

有点绷不住。

考虑二分答案。我们需要求出整个多边形最多被剖分为多少个面积 $\ge S$ 的图形。

设 $dp_{i,j}$ 为，考虑凸包上 $i \to i+1 \to \cdots \to j-1 \to j \to i$ 的多边形（模意义下）能划分为多少个面积 $\ge S$ 的图形。

考虑边 $(i,j)$ 所对的结构，必然存在一个 $i \to i+1 \to \cdots \to j$ 上的一个点 $k$。

考虑 $i \to i+1 \to \cdots \to k$ 和 $k \to k+1 \to \cdots \to j$ 两条链。

比如链 $i \to i+1 \to \cdots \to k$ 中，$i \to k$ 边可能会对应一部分面积放到 $i \to j$ 对应的多边形中，剩下的部分被划分成了 $t$ 个面积 $\ge S$ 的图形。

**如果 $i \to i+1 \to \cdots k$ 实际上可以被划分为 $t+1$ 或更多的面积 $\ge S$ 的图形，这放弃 $i \to j$ 边对应的多边形，改用这 $t+1$ 个的划分方案更优**。这样调整之后，不仅划分数不变，还让 $i \to j$ 上附着了更大的面积（原先是 $0$，这是给考虑范围外的多边形用的）。

因此我们可以得到最优结构：给定 $(i,j)$，要求**最多能划分为多少个合法的多边形**，**以及这样的划分之后最多还能剩下多少的面积**。

容易做到 $O(n^3 \log n)$。

不要把多边形剖分想的太简单，不然会像我一样写出错误的算法，调了一个小时还不知情。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=200+10;
int n,k,x[MAXN],y[MAXN],ss[MAXN][MAXN][MAXN];
inline int calc(const int t) {return (t>n)?t-n:t;}
#define pre(u) (((u)==1)?n:(u-1))
#define nxt(u) (((u)==n)?1:(u+1))
pair<int,int> dp[MAXN][MAXN];
int check(int S) {
	memset(dp,-0x3f,sizeof(dp));	
	ffor(i,1,n) dp[i][nxt(i)]=dp[i][i]={0,0};
	ffor(len,3,n) for(int x=1,y=len;x<=n;x++,y=nxt(y)) {
		int pos=nxt(x);
		while(pos!=y) {
			pair<int,int> pr;
			pr.first=dp[x][pos].first+dp[pos][y].first;
			pr.second=dp[x][pos].second+dp[pos][y].second;
			pr.second+=ss[x][y][pos];
			if(pr.second>=S) pr.second=0,pr.first++;
			dp[x][y]=max(dp[x][y],pr),pos=nxt(pos);
		}
	}
	ffor(i,1,n) ffor(j,1,n) {
		auto pr=dp[i][j];
		int pos=j;
		while(pos!=i) pr.second+=ss[i][pos][nxt(pos)],pos=nxt(pos);
		if(pr.second>=S) pr.first++,pr.second=0;
		if(pr.first>=k+1) return 1;
	}
	return 0;
}
int bfind(int l,int r) {
	int ans=-1;
	while(l<=r) {
		int mid=l+r>>1;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;	
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	ffor(i,1,n) cin>>x[i]>>y[i];
	ffor(id1,1,n) ffor(id2,1,n) ffor(id3,1,n) {
		int dx1=x[id2]-x[id1],dy1=y[id2]-y[id1];
		int dx2=x[id3]-x[id1],dy2=y[id3]-y[id1];
		ss[id1][id2][id3]=abs(dx1*dy2-dx2*dy1);
	}
	cout<<bfind(1,100000000000000000);
	return 0;
}
```

---

## 作者：freoepn (赞：0)

二分最小面积 $S$，则需要划分出的 $k+1$ 块面积都要 $\geq S$。

考虑先切 $l \rightarrow r$，再划分 $[l,r]$ 之间的点，需要做到每一块面积都 $\geq S$ 且切割出的块数尽可能多。

设 $dp_{l,r} = (x,y)$，表示第 $l$ 至第 $r$ 号点组成的多边形中，最多可以分出 $x$ 块，在此基础上，最少占用 $y$ 的面积。

枚举中间点转移即可。

---

