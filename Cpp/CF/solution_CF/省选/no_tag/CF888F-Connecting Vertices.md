# Connecting Vertices

## 题目描述

There are $ n $ points marked on the plane. The points are situated in such a way that they form a regular polygon (marked points are its vertices, and they are numbered in counter-clockwise order). You can draw $ n-1 $ segments, each connecting any two marked points, in such a way that all points have to be connected with each other (directly or indirectly).

But there are some restrictions. Firstly, some pairs of points cannot be connected directly and have to be connected undirectly. Secondly, the segments you draw must not intersect in any point apart from the marked points (that is, if any two segments intersect and their intersection is not a marked point, then the picture you have drawn is invalid).

How many ways are there to connect all vertices with $ n-1 $ segments? Two ways are considered different iff there exist some pair of points such that a segment is drawn between them in the first way of connection, but it is not drawn between these points in the second one. Since the answer might be large, output it modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
3
0 0 1
0 0 1
1 1 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
0 1 1 1
1 0 1 1
1 1 0 1
1 1 1 0
```

### 输出

```
12
```

## 样例 #3

### 输入

```
3
0 0 0
0 0 1
0 1 0
```

### 输出

```
0
```

# 题解

## 作者：tzc_wk (赞：16)

> Codeforces 888F

> 题意：有一个 $n$ 个点的多边形，顶点从 $1$ 到 $n$ 标号，问有多少种方法在它们之间连 $n-1$ 条边，得到一棵树。

> 不过连边有些条件：

> 1. 如果在 $(i,j)$ 之间连边，那么必须满足 $a_{i,j}=1$，其中 $a$ 是一个输入时给出的 $01$ 矩阵，$a_{i,i}=0$，$a_{i,j}=a_{j,i}$

> 2. 连出来的边只能在顶点处相交。

> 答案对 $10^9+7$ 取模。

> 数据范围 $1 \leq n \leq 500$

~~好吉利的题号~~

我想说，这个数据范围给出的算法提示已经足够了吧。

区间 $dp$

我们把这个多边形展开成一条链，那么题目中的条件 “两条线段不能在顶点之外的地方相交”，就可以被我们转化为任意两条线段只能是相离、相切或者包含关系。

我们考虑 $dp$，$dp[l][r]$ 表示将 $[l,r]$ 连在一起的最小代价。

那么有以下两种转移方式：

1. 如果 $l$ 和 $r$ 之间可以连边，那么就在 $l$ 到 $r$ 之间连边，之后我们枚举断点 $k$，然后将 $[l,k]$ 连在一起，$[k+1,r]$ 连在一起。根据乘法原理，这一部分的贡献为 $\sum dp[l][k] \times dp[k+1][r]$。这一部分有贡献的前提是 $a_{l,r}=1$

2. 不在 $[l,r]$ 之间连边，还是枚举断点，在 $[l,k]$ 之间连边，$[k,r]$ 之间连边，这一部分贡献为 $\sum dp[l][k] \times dp[k][r]$。

将两部分加在一起就是 $dp[l][r]$。

边界：$dp[i][i]=1$

最终答案 $dp[1][n]$

不过这个做法是错误的。

原因：例如我们要求 $dp[1][4]$ 的值，那么在 $(1,4)$ 不连边的情况下，有一种方式是连边 $(1,2),(2,3),(3,4)$。但是我们在枚举断点的时候，$k=2$ 的时候统计了一遍这个答案，$k=3$ 的时候又统计了一遍，故这个算法是错误的。

我们考虑扩充状态。$dp[l][r][0]$ 表示把 $[l,r]$ 连在一起，且 **$[l,r]$ 之间必须连边的方案数**，$dp[l][r][1]$ 表示把 $[l,r]$ 连在一起，且 **$[l,r]$ 之间必须不连边的方案数**，那么 $dp[l][r][0]+dp[l][r][1]$ 的值就是原来的 $dp[l][r]$。

计算 $dp[l][r][0]$ 的值，就和上面一样枚举断点转移，即 $\sum (dp[l][k][0]+dp[l][k][1]) \times (dp[k+1][r][0]+dp[k+1][r][1])$。

计算 $dp[l][r][1]$ 的值，同样要枚举断点，不过这次我们枚举的 $k$ 的意义是 $[l,k]$ 之间强制连边的方案。那么贡献就是 $\sum dp[l][k][0] \times (dp[k][r][0]+dp[k][r][1])$，前提条件是 $a_{l,k}=1$，这样就可以避免之前的问题了。

最终答案 $dp[1][n][0]+dp[1][n][1]$

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
const int MOD=1e9+7;
int n=read();
int a[505][505];
int dp[505][505][2];
signed main(){
	fz(i,1,n)	fz(j,1,n)	a[i][j]=read();
	fz(i,1,n)	dp[i][i][0]=1;
	fz(len,2,n){
		for(int l=1,r=len;r<=n;l++,r++){
			if(a[l][r]){
				for(int k=l;k<r;k++){
					dp[l][r][0]=(dp[l][r][0]+(dp[l][k][0]+dp[l][k][1])*(dp[k+1][r][0]+dp[k+1][r][1])%MOD)%MOD;
				}
			}
			fz(k,l+1,r-1){
				if(a[l][k])
					dp[l][r][1]=(dp[l][r][1]+dp[l][k][0]*(dp[k][r][0]+dp[k][r][1])%MOD)%MOD;
			}
		}
	}
	cout<<(dp[1][n][0]+dp[1][n][1])%MOD<<endl;
	return 0;
}
```

---

## 作者：juicyyou (赞：7)

# CF888F Connecting Vertices

首先呢，我们可以看到数据范围是 500 ，那么写出的算法大致上应该是一个 $O(n^3)$ 的做法。

而这个题它又让我们计数，不难想到使用 DP 进行求解。

既然这是一棵树，那我们不妨假设它的根为 1。

接着，我们可以去考虑一下，从 1 连下来的最后一条边。

由于这是一棵树，那么这条边两侧一定有一些点和它是联通的。

而题目告诉我们这些边不能有相交的，那么很显然，这些点一定是一段连续的点。而且右端点一定是 N。

既然如此，那就可以去枚举这一段连续的点的左端点，并且在区间里选出一个点让 1 连向这个点，然后这个问题就变成了这个点左侧和这个点右侧两个子问题，那么就可以利用区间 dp 去转移了。

方程是这样的：
$$
dp[l][r] = \sum\limits_{j = l + 1}^{r}dp[l][j-1]\cdot\left(\sum\limits_{k = j, a[l][k] = 1}^{r} dp[j][k] \cdot dp[k][r] \right)
$$
但是这样的复杂度就是 $O(n^4)$ 超出了 $O(n^3)$ 的极限复杂度。

考虑优化一下。

我们发现，分割点左侧的点其实可以表示为这样：把 $[l, j-1]$ 分成两个连通块的第二个连通块。

但是定义的话会有重复的问题，所以我们这么定义：$f[l][r]$ 表示把 $[l, r]$ 分成两个连通块且其中第二个的大小大于 0。

那么就可以直接转移了，方程如下：
$$
dp[l][r] = \sum\limits_{j = l+1}^{r} (dp[l][j - 1] + f[l][j]) \cdot dp[j][r]
$$

$$
f[l][r] = \sum\limits_{j = l+1}^{r-1} dp[l][j - 1] \cdot dp[j][r]
$$

那么这样的复杂度就是 $O(n^3)$ 了，可以过。

下面是我的 Code：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
const ll maxn = 5e2 + 5;
const ll mod = 1e9 + 7;
ll f[maxn][maxn][3], g[maxn][maxn];
ll n, a[maxn][maxn];
ll cal(ll l, ll r, ll num){
	if(f[l][r][num] != -1) return f[l][r][num];
	if(l == r && num == 1) return 1;
	if(l == r && num == 2) return 0;
	f[l][r][num] = 0;
	if(num == 2){
		for(int i = l + 1;i < r;i++){
			f[l][r][2] += cal(l, i - 1, 1) * cal
			(i, r, 1) % mod;
			f[l][r][2] %= mod;
		}
		return f[l][r][2];
	}
	for(int i = l + 1;i <= r;i++){
		if(!a[l][i]) continue;
		f[l][r][1] += (cal(l, i - 1, 1) + cal(l, i, 2)) * cal(i, r, 1) % mod;
		f[l][r][1] %= mod;
	}
	return f[l][r][1];
}
int main(){
	memset(f, -1, sizeof(f));
	scanf("%lld", &n);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			scanf("%lld", &a[i][j]);
		}
	}
	printf("%lld\n", cal(1, n, 1));
//	for(int i = 1;i <= n;i++){
//		for(int j = 1;j <= n;j++){
//			cout << f[i][j][1] << " ";
//		}
//		puts("");
//	}
	return 0;
}
```

这样就可以过了。

---

## 作者：Sol1 (赞：7)

一看要求方案数，先往计数 DP 上面想。

计数 DP 的一般套路是要构造一个“不可划分的整体”。我们来看这个问题里面能有什么东西无法划分。

瞪一会就会发现：对于两个点 $i,j$，如果这两点之间直接连边，那么区间 $[i,j]$ 就是不能划分的；因为一旦划分就会导致边在圆内交叉。

所以我们设计 $f_{i,j}$ 为使得 $[i,j]$ 区间连通，而且必须连 $i\leftrightarrow j$ 这条边的方案数。

但是直接用区间 DP 的方式来转移是 $O(n^2\times n^2)$ 的，不能接受。

我们发现瓶颈主要在计算区间 $[i,j]$ **任意连通**（即不一定要存在 $i\leftrightarrow j$ 的边）的方案数。

所以我们再开一个 $g_{i,j}$ 表示上面的那个值。

然后先来转移 $g$。有两种转移：

1. 连边，此时枚举中间断哪条边，转移是 $g_{i,j}\leftarrow \sum\limits_{k} g_{i,k}\cdot g_{k+1,j}$。
2. 不连边，此时枚举断点，得到转移 $g_{i,j}\leftarrow \sum\limits_{k} g_{i,k}\cdot f_{k,j}$。

然后来转移 $f$，直接取上面的 1 转移就可以了。

最后就是边界和答案。边界显然：

- $f_{i,i}=g_{i,i}=1$
- $f_{i,i+1}=g_{i,i+1}=a_{i,i+1}$

答案同样显然：

- $\text{Ans}=g_{1,n}$

采用区间 DP，时间复杂度为 $O(n^3)$。

代码：

（变量名有点乱……mp 对应 a，dp 对应 g，dp2 对应 f）

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

const long long mod = 1000000007;
bool mp[1005][1005];
long long dp[1005][1005], dp2[1005][1005], ans[1005];
int n;

inline void Read() {
	n = qread();
	for (register int i = 1;i <= n;i++) {
		for (register int j = 1;j <= n;j++) mp[i][j] = mp[i + n][j + n] = mp[i + n][j] = mp[i][j + n] = qread();
	}
}

inline void Solve() {
	for (register int i = 1;i <= n + 1;i++) dp2[i][i] = dp[i][i] = 1;
	for (register int i = 1;i <= n;i++) dp2[i][i + 1] = dp[i][i + 1] = mp[i][i + 1];
	for (register int l = 3;l <= n;l++) {
		for (register int i = 1;i <= n + 1 - l + 1;i++) {
			register int j = i + l - 1;
			for (register int k = i + 1;k < j;k++) dp[i][j] = (dp[i][j] + dp[i][k] * dp2[k][j] % mod) % mod;
			if (mp[i][j]) {
				register long long cur = dp[i][j];
				//if (l > 3) dp[i][j] = (dp[i][j] + dp[i + 1][j - 1] * (mp[i][i + 1] + mp[i][j - 1] + mp[j][i + 1] + mp[j][j - 1]) % mod) % mod;
				//else dp[i][j] = (dp[i][j] + dp[i + 1][j - 1] * (mp[i][i + 1] + mp[j][i + 1]) % mod) % mod;
				for (register int k = i;k < j;k++) {
					dp2[i][j] = (dp2[i][j] + dp[i][k] * dp[k + 1][j] % mod) % mod;
					dp[i][j] = (dp[i][j] + dp[i][k] * dp[k + 1][j] % mod) % mod;
				}
			}
		}
	}
	// for (register int i = 1;i <= n;i++) {
	// 	for (register int j = i + 1;j <= n;j++) {
	// 		printf("%lld ", dp2[i][j]);
	// 	}
	// 	puts("");
	// }
	ans[1] = 1;
	for (register int i = 2;i <= n;i++) {
		for (register int j = 1;j < i;j++) ans[i] = (ans[i] + ans[j] * dp2[j][i] % mod) % mod;
	}
	printf("%lld", dp[1][n] % mod);
}

int main() {
	Read();
	Solve();
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}
```

---

## 作者：zyh_helen (赞：5)

## CF888F 题解

----

### 题意

给你 $n$ 个点，请你用 $n-1$ 条线段将这些点连成树，并保证：

1.任意一条边的两端点 $i,j$ 必须满足 $a_{i,j}=1$；

2.任意两条边不相交。

--------

### 思路

看到这个题的时候我一下就想到了多边形切分为三角形，

然后随便画了个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/pwuf3bob.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

可以发现有 $n-3$ 条对角线，加上连向最后两个点的两条边
一共是 $n-1$ 条线段，恰恰是题中所求的树。

![](https://cdn.luogu.com.cn/upload/image_hosting/aqvchize.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

下面沿着任意一条树边（蓝边）看，可以发现任意一天树边都会把整个多边形分成两块新的多边形，并且我们还在新的多边形里面进行三角形切割。~~（画技泪目~~

![](https://cdn.luogu.com.cn/upload/image_hosting/r2ae6xp7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


然后区间的性质就显而易见了，解法也浮出水面——区间 dp。

-----

### 很 naive 的解法

定义 $dp_{i,j}$ 表示将 $i,j$ 之间的所有点连在一起的方案数。

case 1：$i,j$ 之间连边，那么将下面的部分继续分成两部分；即枚举 $k$，$i$ 到 $k$ 为一部分，$k+1$ 到 $j$ 为另一部分；

case 2：$i,j$ 之间不连边，那么必然下面有一个点将 $i,j$ 连接，并将下面的部分分成两部分；即枚举 $k$，$i$ 到 $k$ 为一部分，$k$ 到 $j$ 为另一部分。

综上所述，$dp_{i,j}=\begin{cases}\sum\limits_{k=i}^{j-1}{dp_{i,k} \times dp_{k+1,j}}&a_{i,j}=1\\\sum\limits_{k=i}^{j}{dp_{i,k} \times dp_{k,j}}\end{cases}$

但是这个解法是错误的，

因为会算重。

那么就可以用一种很经典的扩充 dp 状态方式。

----
### 真正的解法

定义 $dp_{i,j,0}$ 表示 $i,j$ 之间连边，将 $i$ 到 $j$ 之间的所有点连到一起的方案数；$dp_{i,j,1}$ 表示 $i,j$ 之间不连边，将 $i$ 到 $j$ 之间的所有点连到一起的方案数。

类似的，我们分出上文的两个 case。

但是，我们在 case 2 的转移中，强制命令 $i,k$ 必须连边，这样就不会出现重复的情况了，同时 case 2 的转移中必须要满足 $a_{i,k}=1$。

综上所述，

$dp_{i,j,0}=[a_{i,j}=1]\times\sum\limits_{k=i}^{j-1}{(dp_{i,k,0}+dp_{i,k,1})\times(dp_{k+1,j,0}+dp_{k+1,j,1})}$

$dp_{i,j,1}=\sum\limits_{k=i}^j{dp_{i,k,0} \times (dp_{k,j,0}+dp_{k,j,1})\times[a_{i,k}=1]}$

---

### 代码

蒟蒻自认为马蜂很好。

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
#include<stack>
#include<vector>
#include<cstdlib>
#include<ctime>
#define int long long
#define y1 yyyyyyyyyyyyyyyy1
using namespace std;
const int N = 5e2 + 10, INF = 0x3ffffffffffffff, mod = 1e9 + 7;
int n, dp[N][N][2], a[N][N];
signed main(){
	cin >> n;
	for(int i = 1;i <= n;i++)for(int j = 1;j <= n;j++)cin >> a[i][j];
	for(int i = 1;i <= n;i++)dp[i][i][0] = 1;
	for(int len = 2;len <= n;len++){
		for(int i = 1;i <= n;i++){
			int j = i + len - 1;
			if(j > n)break;
			if(a[i][j])for(int k = i;k < j;k++)dp[i][j][0] = (dp[i][j][0] + (dp[i][k][0] + dp[i][k][1]) * (dp[k + 1][j][0] + dp[k + 1][j][1] % mod)) % mod;
			for(int k = i;k < j;k++){
				if(!a[i][k])continue;
				dp[i][j][1] = (dp[i][j][1] + dp[i][k][0] * (dp[k][j][0] + dp[k][j][1]) % mod) % mod;
			}
		}
	}
	cout << (dp[1][n][1] + dp[1][n][0]) % mod;
	return 0;
}
```

---

## 作者：EuphoricStar (赞：3)

做做简单题放松身心。

考虑区间 dp，设 $f_{i, j}$ 为只考虑 $[i, j]$ 的点的生成树个数。

转移枚举 $i$ 往右连的最后一条边 $(i, k)$，那么 $[k, j]$ 的点都不能往前连。

再设一个 $g_{i, j}$ 为只考虑 $[i, j]$ 的点，并且连边 $(i, j)$ 的生成树个数。那么 $f$ 有转移：

$$\forall k \in [i + 1, j], f_{i, j} \gets g_{i, k} \times f_{k, j}$$

考虑如何求 $g_{i, j}$。因为是一棵树，所以连 $(i, j)$ 之前，$i, j$ 必然不连通，并且此时 $[i, j]$ 形成 $2$ 个连通块。枚举 $[i, k]$ 为 $i$ 所属连通块，那么 $g$ 有转移：

$$\forall k \in [i, j - 1], g_{i, j} \gets f_{i, k} \times f_{k + 1, j}$$

做完了。时间复杂度 $O(n^3)$。

[code](https://codeforces.com/problemset/submission/888/216598133)

---

## 作者：Purslane (赞：1)

# Solution

显然要断环成链。我们要计算出 $f_{l,r}$ 表示 $l$ 和 $r$ 联通的方案数。

如果 $l$ 和 $r$ 之间需要有连边，则将它删掉之后，区间 $[l,r]$ 中的点恰好分为两个连通块；如果没有连边，我们可以找到最大的 $u$ 使得 $u$ 和 $r$ 有连边，这样拆分成 $[l,u]$ 联通与 $[u,r]$ 联通。

我们发现，还是要记录 $l$ 和 $r$ 有连边的方案数，设为 $g_{l,r}$。

因此转移就是：

$$
g_{l,r} = a_{l,r} \sum_{t=l}^{r-1} f_{l,t}f_{t+1,r}
$$

以及

$$
f_{l,r} = g_{l,r} + \sum_{u=l+1}^{r-1} f_{l,u}g_{u,r}
$$

答案就是 $f_{1,n}$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=500+10,MOD=1e9+7;
int n,a[MAXN][MAXN],f[MAXN][MAXN],g[MAXN][MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) ffor(j,1,n) cin>>a[i][j];
	ffor(i,1,n) f[i][i]=1;
	ffor(len,2,n) for(int l=1,r=len;r<=n;l++,r++) {
		if(a[l][r]) ffor(t,l,r-1) g[l][r]=(g[l][r]+f[l][t]*f[t+1][r])%MOD;
		f[l][r]=g[l][r];
		ffor(u,l+1,r-1) f[l][r]=(f[l][r]+f[l][u]*g[u][r])%MOD;
	}
	cout<<f[1][n];
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

观察一下线段不相交说明什么。

我们发现这说明每条边都会分割多边形。

不妨来试着解决只考虑端点 $l \sim r$ 的问题，设计状态 $dp_{l,r},g_{l,r}$ 分别表示考虑端点 $l \sim r$，$l,r$ 是否已经联通时，生成树数量。

转移考虑枚举 $l$ 最靠后的出边 $k$，其会把 $[l,r]$ 分割为 $[l,k]$ 与 $[k,r]$ 两个互不干扰的问题，有 $dp_{l,r} = \sum dp_{l,k} \times dp_{k,r} \times a_{l,i} + g_{l+1,r}$，最后一项 $g_{l+1,r}$ 是考虑没有出边时的情况。对于 $g$，有 $g_{l,r} = \sum dp_{l,k} \times g_{k,r} \times a_{l,k} + dp_{l,r} \times a_{l,r}$，最后 $dp_{l,r} \times a_{l,r}$ 是考虑 $l$ 连向 $r$ 的情况。

时间复杂度 $O(n^3)$。

最后统计答案时还需要钦定一下最前面和最后面连向 $1$ 的点。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 514;
int n;
int a[maxn][maxn];
int dp[maxn][maxn][2];//0 l,r 已经联通 1 l,r 还未联通 
int vis[maxn][maxn][3];
int f[maxn];
int solve(int l,int r,int ty){
	if(vis[l][r][ty]!=0) return dp[l][r][ty];
	vis[l][r][ty]=1;
	if(l==r){
		return dp[l][r][ty]=1;
	}
	if(r==l%n+1){
		return dp[l][r][ty]=((ty==0?1:0)|a[l][r]);
	}
	if(ty==0){
		dp[l][r][ty]=(dp[l][r][ty]+solve(l%n+1,r,1))%mod;
		for(int i=l%n+1;i!=r;i++){
			dp[l][r][ty]=(dp[l][r][ty]+solve(l,i,0)*solve(i,r,0)%mod*a[l][i])%mod;
		}
	}else{
		for(int i=l%n+1;i!=r;i++){
			dp[l][r][ty]=(dp[l][r][ty]+solve(l,i,0)*solve(i,r,1)%mod*a[l][i])%mod;
		}
		dp[l][r][ty]=(dp[l][r][ty]+solve(l,r,0)*a[l][r]%mod)%mod;
	}
	return dp[l][r][ty];
}
int ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) cin>>a[i][j];
	}
	for(int i=2;i<=n;i++){
		f[i]=solve(2,i,1)*a[1][i];
		for(int j=2;j<i;j++){
			f[i]=(f[i]+f[j]*solve(j,i,0)%mod*a[1][i])%mod;
		}
		ans=(ans+f[i]*solve(i,n,1)%mod)%mod;
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：lg_zhou (赞：0)

计数类，要么是数学，要么是 $dp$。这题数学不好做，很显然是 $dp$。

**步骤 $1$ :** 

首先题目要求线段不能相交，我从这一点以及数据范围看出了这题是一道区间 $dp$。为什么？因为一棵范围为 $[l,r]$ 的树只有可能是由 $[l,k]$ 和 $[k+1,r]$ 两棵树拼成的。如果是 $[l,k_1]
$ 和 $[k_2,r]$ 共同一棵树，$[k_1+1,k_2-1]$ 是另一棵树，这两棵树拼成的，可以化为上种情况。如果是两段交叉的树拼成，那么线段必定相交（如 $[1,4]$ 这棵树不可能由  $\{ 1,3 \}$ 和 $\{ 2,4 \}$ 两棵树合并而来）。

**步骤 $2$ :** 

确定了要用区间 $dp$ 后，注意遵守一个计数类 $dp$ 的准则，即不重不漏。

为了不漏，我们枚举中间点 $k$，由 $[l,k]$ 和 $[k+1,r]$ 两棵树拼成 $[l,r]$。但是这样显然会重复。

为了不重，我们要找到每棵树唯一的特征。我们可以定为最左边的点 $l$ 连接的最右边节点的位置。

这样有两个好处，一是不重，因为如果 $l$ 所连最右边节点不同，那么两棵树一定不同。所以我们用 $f[i][j]$ 代表 $[i,j]$ 区间内组成一棵树且 $i,j$ 必须相连的方案数，$g[i][j]$ 代表 $[i,j]$ 区间内组成一棵树的方案数。那么 $g$ 可以轻易由 $f$ 转移来，具体的，对于 $g[i][j]$，枚举中间节点 $k$，累加所有 $f[i][k]\times g[k][j]$ 即可。

第二个好处是，我们可以轻易算出 $f$ 数组，原因又有二。第一：对于一棵树 $[l,r]$，$(l,r)$ 这条边是一定可以连的！不用担心会与其他线段交叉。第二，在计算 $f$ 数组，枚举断点 $k$ 时，对于任意 $[l,k]$ 与 $[k+1,r]$，之前肯定都没有连过 $(l,r)$ 这条边，由于之前 $k$ 不同，不连通的两棵树也不同，现在加了一条一样的边，构成的树也不同，所以算 $f$ 也不会重。具体的，对于 $f[i][j]$，枚举每一个中间点 $k$，累加 $g[i][k] \times g[k+1][r]$ 即可。

这道题就轻松地搞定了。






---

## 作者：xuantianhao (赞：0)

# [Connecting Vertices](https://www.luogu.com.cn/problem/CF888F)

这个奇怪的限制（两条边不能有交点）让我们想到什么？

对于任何一种方案，不存在 $x_0<x_1<y_0<y_1$，其中连边 $(x_0,y_0),(x_1,y_1)$。

也就是说，对于任何一段区间 $[i,j]$，如果里面所有点全都连通：

要么 $i,j$ 两点之间自己连了条边，此时，存在且仅存在一个 $k$，使得区间 $[i,k]$ 和 $[k+1,j]$ 间有且只有 $(i,j)$ 一条边；

要么可以找到一个点 $k$，使得区间 $[i,k-1]$ 与 $[k+1,j]$ 之间没有边，并且 $k$ 与两个集合连通。

因此我们可以轻而易举写出：

$$(a_{i,j}=1):f[i,j]=\sum\limits_{k=i}^{j} f[i,k] \times f[k+1,j]$$

$$f[i,j]=\sum\limits_{k=i+1}^{j-1} f[i,k] \times f[k,j]$$

但是这样会出问题：

要么可以找到一个点 $k$，使得区间 $[i,k-1]$ 与 $[k+1,j]$ 之间没有边，并且 $k$ 与两个集合连通。

并不表示这样的 $k$ 唯一。例如，$(1,2)\rightarrow(2,3)\rightarrow(3,4)$ 中，2 是一个 $k$，3 也是一个 $k$，这同一种方案就被算了两边！

因此，我们可以只拿最左边那个 $k$ 为准。即，$i$ 与 $k$ 直接连边的 $k$ 才是好 $k$。

我们新增维数：

设 $f[i,j][0/1]$ 表示：区间 $i,j$ 全部连通，并且 $i,j$ 强制连边/强制不连边。

则有

$$(a_{i,j}=1):f[i,j][0]=\sum\limits_{k=i}^{j} (f[i,k][0]+f[i,k][1]) \times (f[k+1,j][0]+f[k+1,j][1])$$

$$f[i,j]=\sum\limits_{k=i+1}^{j-1} f[i,k][0] \times (f[k,j][0]+f[k,j][1])$$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int N=550;
int n;
int g[N][N],f[N][N][2];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>g[i][j];
    for(int i=1;i<=n;i++) f[i][i][0]=1;
    for(int l=2;l<=n;l++){
		for(int i=1,j=i+l-1;j<=n;i++,j++){
		    if(g[i][j]){
				for(int k=i;k<j;k++){
					(f[i][j][0]+=(f[i][k][0]+f[i][k][1])*(f[k+1][j][0]+f[k+1][j][1])%mod)%=mod;
				}
			}
		    for(int k=i+1;k<j;k++){
				if(g[i][k]){
					(f[i][j][1]+=f[i][k][0]*(f[k][j][0]+f[k][j][1])%mod)%=mod;
				}
			}
		}
	}
    cout<<(f[1][n][0]+f[1][n][1])%mod;
    return 0;
}
```


---

## 作者：MSqwq (赞：0)

考虑区间 dp，如果是 $dp_{l,r}$ 表示 $[l,r]$ 的贡献，那么只需要分两种情况，一个是 $l$ 和 $r$ 连边，一个是不连边。如果连边，那么考虑枚举中间的断点，将其分开，不然就不是树了，就是   
$dp_{i,j}=\sum\limits_{k=l}^{r-1}dp_{l,k}\times dp_{k+1,r}$  
如果不连边，那么就是找一个点将其联通，贡献就是  
$dp_{i,j}=\sum\limits_{k=l+1}^{r-1}dp_{l,k}\times dp_{k,r}$   
值得一提的是枚举不连接的断点的情况应该是 $[l+1,r-1]$ 有些题解好像这里写错了，但是无所谓都是细节问题了。
然后写了这个只后，发现会算重，举个简单例子，因为可能存一个不连接分别算在左右两边部分，但实际上是一种情况。    
所以把状态设成 $dp_{l,r,0/1}$ 表示$[l,r]$ 的贡献并且强制 $l$ 到 $r$ 连或者不连。  
如果 $0$ 表示不连，$1$ 表示连。  
那么还是上面两种情况，那么就是   

$dp_{i,j,0}=\sum\limits_{k=l+1}^{r-1}dp_{l,k,1}\times (dp_{k,r,0}+ dp_{k,r,1})$   
$dp_{i,j,1}=\sum\limits_{k=l}^{r-1}(dp_{l,k,0} + dp_{l,k,1})\times (dp_{k+1,r,0}+ dp_{k+1,r,1})$  
下面一种情况可能很好理解，就是直接乘法原理嘛，全部情况相乘，因为 $l$ 和 $r$ 都连了，所以不在乎中间的情况。  
主要是不连的情况，为啥少了 $dp_{l,k,0}$ 呢，很好理解，因为保证每一种树的形态算一次，那么我么保证 $l$ 和 $k$ 有边的情况，就是保证形态唯一了。  
复杂度 $O(n^3)$。  
感谢一个大哥和我一起讨论这个题，但是好像洛谷找不到他了，但是真的很感谢，给我讲懂了这题，也讲了很久，谢谢。  
代码：  
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
using namespace std;
const int mod=1e9+7;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

const int N=600;
bool a[N][N];
int dp[N][N][2];
int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)a[i][j]=read();
	for(int i=1;i<=n;i++)dp[i][i][0]=1;
	for(int len=2;len<=n;len++)
	{
		for(int l=1;l+len-1<=n;l++)
		{
			int r=l+len-1;
			if(a[l][r])
			{
				for(int k=l+1;k<r;k++)
					if(a[l][k])dp[l][r][0]=(dp[l][r][0]+1ll*dp[l][k][1]*(dp[k][r][1]+dp[k][r][0])%mod)%mod;
				for(int k=l;k<r;k++)
					dp[l][r][1]=(dp[l][r][1]+1ll*(dp[l][k][0]+dp[l][k][1])*(dp[k+1][r][0]+dp[k+1][r][1])%mod)%mod;
			}
			else
			{
				for(int k=l+1;k<r;k++)
					if(a[l][k])dp[l][r][0]=(dp[l][r][0]+1ll*dp[l][k][1]*(dp[k][r][1]+dp[k][r][0])%mod)%mod;			
			}
		}
	}
	cout<<(dp[1][n][0]+dp[1][n][1])%mod<<endl;
	return 0;
}
```


---

