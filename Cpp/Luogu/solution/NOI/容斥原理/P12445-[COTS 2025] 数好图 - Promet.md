# [COTS 2025] 数好图 / Promet

## 题目描述


给定正整数 $N$ 和素数 $P$。

$\forall K=0,1,\ldots,N$，求出满足以下条件的**简单**有向图的数量：

- 图中仅包含 $i\to j$（$1\le i\lt j\le N$）的边；
- 满足以下条件的点 $u$ 恰好有 $K$ 个：
	- 存在 $1\to u$ 和 $u\to N$ 的路径。

只需要输出答案对 $P$ 取模后的结果。

## 说明/提示


### 样例解释

样例 $2$ 解释：

$K=0$ 的时候，根据定义，下面三个边集合法：

- $\varnothing$；
- $\{(1, 2)\}$；
- $\{(2, 3)\}$。


$K=2$ 时，合法的边集：

- $\{(1, 3)\}$；
- $\{(1, 3), (1, 2)\}$；
- $\{(1, 3), (2, 3)\}$。

$K=3$ 时，合法的边集：

- $\{(1, 2), (2, 3)\}$；
- $\{(1, 2), (1, 3), (2, 3)\}$。

### 数据范围

- $2\le N\le 2\,000$；
- $10^8\le P\le 10^9+100$；
- $P$ 是素数。
### 子任务

子任务 $0$ 为样例。

| 子任务编号 | $N\le$ | 得分 |
| :-: | :-: | :-: |
| $1$ | $7$ | $4$ |
| $2$ | $18$ | $7$ |
| $3$ | $50$ | $23$ |
| $4$ | $100$ | $13$ |
| $5$ | $300$ | $18$ |
| $6$ | $2\,000$ | $35$ |


## 样例 #1

### 输入

```
2 1000000007```

### 输出

```
1 0 1```

## 样例 #2

### 输入

```
3 1000000007```

### 输出

```
3 0 3 2```

## 样例 #3

### 输入

```
5 1000000007```

### 输出

```
183 0 183 286 250 122```

# 题解

## 作者：Purslane (赞：19)

# Solution

我做这个题，花了将近 2 个小时……如此水平，如何 NOI！/ll

不过克罗地亚国家队在这道题上得分 $\max$ 为 $4$。

-------

考虑 $k=n$ 怎么做，也就是所有点都在某一条 $1 \to n$ 路径上。

考虑让 $1$ 到 $n-1$ 每个点至少有一条出边，这样可以保证所有点都能到 $n$。而只要除了 $1$ 以外所有点入度都不是 $0$，就能保证 $1$ 能到达所有点。

那么直接施加容斥。设 $dp_{i,j}$ 为，考虑了后 $i$ 个点，有 $j$ 个点被钦定了入度为 $0$（特别的，倒数第 $i$ 个点此时不能被钦定，只能在转移的时候被钦定。即，$j < i$）。这个可以 $O(n^2)$ 做。

在 $O(n^2)$ 复杂度内，我们还可以算出 $t$ 个点构成的、满足所有点都在 $1$ 到 $t$ 路径上的 DAG 数量，设为 $g_t$。

对于 $k$ 更小的情况，考虑在 $g_k$ 的基础上增加点，使得仍然只有这 $k$ 个点满足要求。

将点划分为 $3$ 类：

- $1$ 类点，表示在 $1$ 到 $n$ 的路径上（即在我们钦定的 $k$ 个点之中）；
- $2$ 类点，表示能从 $1$ 到达的、但不是 $1$ 类点的点；
- $3$ 类点，表示不能从 $1$ 到达的点。

记 $op_i$ 表示这 $n$ 个点类型构成的序列，其中 $op_1=op_n=1$。我们还需要再 $op$ 中分配 $k-2$ 个 $1$，以及若干个 $2$ 和 $3$。对于每一种分配方式，我们计算所有额外边（不是 $1$ 类和 $1$ 类的连边）的连接方式，乘上 $g_k$，加到 $ans_k$ 中。

对于每个点，我们往前连边。

- $1$ 类点：可以往编号比他小的 $3$ 类点连边；
- $2$ 类点：可以往编号比他小的 $1$、$2$、$3$ 类点连边，且必须往至少一个 $1$ 或 $2$ 类点连边；
- $3$ 类点：可以往编号比他小的 $3$ 类点连边。

发现什么？$3$ 类点可以往其后面所有点连边。所以假设所有的 $3$ 类点在 $p_1$、$p_2$、$\cdots$、$p_z$ 处，可以产生的贡献为 $2^{\sum_{i=1}^z n-p_i}$。

因此我们可以 DP 求出所有的贡献之和，然后将 $3$ 类点删掉，只考虑 $1$、$2$ 类点之间的贡献。这也可以 $O(n^2)$ 暴力。

整体时间复杂度为 $O(n^2)$，足以通过本题。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2000+10;
int n,MOD,dp[MAXN][MAXN],C[MAXN][MAXN],pw[MAXN*MAXN],ans[MAXN];
int mul[MAXN][MAXN],f[MAXN][MAXN],g[MAXN]; 
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>MOD;
	pw[0]=1; ffor(i,1,n*n) pw[i]=pw[i-1]*2%MOD;
	ffor(i,0,n) {
		C[i][0]=1;
		ffor(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;	
	}
	dp[1][0]=1;
	ffor(i,2,n) ffor(j,0,i-1) {
		int mul=dp[i-1][j];
		if(j) mul=(mul+dp[i-1][j-1])%MOD;
		dp[i][j]=mul*(pw[i-j-1]-1)%MOD;
	}
	ffor(i,2,n) ffor(j,0,i) g[i]=(g[i]+dp[i][j]*(1-2*(j&1)))%MOD;
	mul[n][0]=1;
	roff(i,n-1,2) ffor(j,0,n) {
		mul[i][j]=mul[i+1][j];
		if(j) mul[i][j]=(mul[i][j]+mul[i+1][j-1]*pw[n-i])%MOD;
	}
	f[1][0]=1;
	ffor(i,1,n) ffor(j,(i==1),n-i) {
		f[i][j]=f[i-1][j],ans[i]=(ans[i]+mul[2][n-i-j]*f[i][j])%MOD;
		if(j) f[i][j]=(f[i][j]+f[i][j-1]*(pw[i+j-1]-1))%MOD;
	}
	ffor(i,2,n) ans[i]=ans[i]*g[i]%MOD;
	ans[0]=pw[n*(n-1)/2];
	ffor(i,2,n) ans[0]=(ans[0]-ans[i])%MOD;
	ffor(i,0,n) cout<<(ans[i]%MOD+MOD)%MOD<<' ';
	return 0;
}
```

---

## 作者：forgive_ (赞：6)

妙妙妙妙题！

仅包含 $i<j$ 的边让我们很自然的想到按编号从小到大依次加入每个点，同时考虑它与已存在的点进行连边。

尝试一下直接做，我们发现大体上需要知道四类点的信息：

- 能从 $1$ 到，且钦定最终能到 $n$ 的。
- 没法从 $1$ 到 ，但钦定能到 $n$。
- 能从 $1$ 到，钦定最终到不了 $n$。
- 都不行的。

这样状态数多的离谱，我们尝试找一些性质使得某些信息可以分开处理。

发现首先可以把前两类归为一类（称为 $1$ 类点），后两类归为一类（称为 $2$ 类点），它们的本质区别在于能否到 $n$。

还是考虑从小到大加点的过程：

对于每个 $1$ 类点，能连向它的只有 $1$ 类点。

对于每个 $2$ 类点，在它前面的 $1,2$ 类点可以 **任意** 选择是否连向它。

这表明，$1$ 类点内部的连边对 $2$ 类点的连边方案没有影响，我们可以分开考虑。

先考虑 $2$ 类点，设 $h_{i,j}$ 表示考虑前 $i$ 个点，其中 $j$ 个二类点，**不考虑 $1$ 类点之间连边的方案数**，按照上面说的方式转移就好，复杂度 $O(n^2)$。

接下来考虑 $1$ 类点内部，重新定义这里面能从 $1$ 到的为 $1$ 类，不能的为 $2$ 类。我们考虑把加点的过程倒过来，从大到小加，发现和上面第一种情况是一样的，每个 $2$ 类点可以任意连向后面的 $1,2$ 类点，不受 $1$ 类点内部连边的影响。

类似 $h_{i,j}$，我们同样定义 $f_{i,j}$ 来处理，转移也很简单。

接下来最后一步是处理既能从 $1$ 到，也能到 $n$ 的点。

我们尝试找一下这样的图的充要条件，发现等价于 $2\sim n-1$ 中每个点都既有入度又有出度。

还是从小到大加点，入度的限制可以在一个点被加入时处理，而出度的限制就要记录到状态里了，设 $dp_{i,j}$ 表示考虑前 $i$ 个点，当前 $0$ 出度点有 $j$ 个的方案数，转移需要枚举有多少个 $0$ 出度点连向新加入的点，复杂度是 $O(n^3)$，因为涉及到一些组合数的系数，不太能前缀和优化。

那么考虑改变一下计数方式，发现可以容斥，我们直接钦定若干个点为最终的图上的 $0$ 出度点，转移就不需要枚举了。

考虑容斥系数，相当于是要求 "方案中恰好有 $1$ 个限制的话贡献为 $1$，否则为 $0$"，这种形式的容斥系数是 $c\times (-1)^{c-1}$，其中 $c$ 是限制个数。

设 $res_i$ 为这部分有 $i$ 个点的答案，最终答案 $ans_i=\sum\limits_{j}h_{n,j}\times f_{j-1,i-1}\times res_i$，对 $f$ 的两维 $-1$ 是因为要刨去 $1$ 号点。

求出 $ans_{1\sim n}$ 后用总方案减掉就是 $ans_0$。

总复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std ;

typedef long long LL ;
const int N = 2100 ;

int n , mod ;
LL C[N][N] , pw2[N] , V[N] , ans[N] ;
LL f[N][N] , h[N][N] ;//选k个点的系数 
LL dp[N][N] ;//考虑前i个点，钦定j个没出度的方案数 
void pre_work( int n )
{
	for(int i = 0 ; i <= n ; i ++ ) {
		if( i == 0 ) pw2[i] = 1 ;
		else pw2[i] = pw2[i-1]*2%mod ;
		C[i][0] = 1 ;
		for(int j = 1 ; j <= i ; j ++ ) {
			C[i][j] = (C[i-1][j]+C[i-1][j-1])%mod ;
		}
	}
}
inline int pw( int x )
{
	if( x&1 ) return -1 ;
	return 1 ;
}

int main()
{
	scanf("%d%d" , &n , &mod ) ;
	pre_work(n) ;
	h[1][1] = 1 ; f[1][1] = 1 ; 
	dp[1][0] = 1 ;
	for(int i = 1 ; i < n ; i ++ ) {
		for(int j = 0 ; j <= i ; j ++ ) {
			dp[i+1][j+1] = ( dp[i+1][j+1] + dp[i][j]*(pw2[i-j]-1) ) % mod ;
			dp[i+1][j] = ( dp[i+1][j] + dp[i][j]*(pw2[i-j]-1) ) % mod ;
			if( j ) {
				h[i+1][j+1] = ( h[i+1][j+1] + h[i][j] ) % mod ;
				if( i != n-1 )  h[i+1][j] = ( h[i+1][j] + h[i][j]*pw2[i] ) % mod ;
				f[i+1][j+1] = ( f[i+1][j+1] + f[i][j] ) % mod ;//倒着加 
				if( i != n-1 ) f[i+1][j] = ( f[i+1][j] + f[i][j]*(pw2[i]-1) ) % mod ;
			}
		}
	}
	for(int j = 1 ; j <= n ; j ++ ) {
		for(int k = 1 ; k <= j ; k ++ ) {
			V[k] = ( V[k] + h[n][j]*f[j-1][k-1] ) % mod ;
		}
	}
	ans[0] = 1 ;
	for(int i = 1 ; i <= n*(n-1)/2 ; i ++ ) ans[0] = ans[0]*2%mod ;
	for(int i = 1 ; i <= n ; i ++ ) {
		LL res = 0 ; 
		for(int j = 0 ; j <= i ; j ++ ) {
			res = ( res + dp[i][j]*j*pw(j-1) ) % mod ;
		}
		res = (res+mod)%mod ;
		ans[i] = res*V[i]%mod ;
		ans[0] = ( ans[0] - ans[i] + mod ) % mod ;
	}
	for(int i = 0 ; i <= n ; i ++ ) {
		printf("%lld " , ans[i] ) ;
	}
	return 0 ;
}
```

---

## 作者：Undead2008 (赞：5)

[COTS 2025 题解合集](https://www.luogu.com.cn/article/dupadkce)

很好的考验基本功的计数题。

这个 $K=0$ 非常恶心先把他特判了，以下默认 $1$ 能走到 $n$。

考虑能否直接硬做，dp 一维维护点数，两维维护和 $1/n$ 联通的点数，一维维护 $K$。

你会发现上面的状态数炸缸了，处理该问题的经典方法是将多维压缩起来。这启发我们探究 dp 维度之间的关系。

轻微手摸之后可以发现一个点能从 $1$ 到达且走不到 $n$（称为一类点），其所有出边指到的都仅可能为一类点。一个点不能从 $1$ 到达且能走到 $n$（称为二类点），其所有入边指到的都仅可能为二类点。

然后你惊喜的发现这两个玩意好像独立了，就是把一类点二类点和孤点扔出去之后剩下就是题目要求数的点（三类点），直接求解这个东西，然后再把一类点和孤点加进去，再把二类点加进去，就做完了。

一二类点加进去的过程是简单的，对于一类点按照编号从小到大插入，一个点向之前的所有点（一类点，三类点）至少有一条连边。对于二类点按照编号从大到小插入，一个点向之后的所有点（包括一类点，二类点，三类点，孤点）至少有一条连边。

遗留问题就是如何把 $K$ 个三类点搞出来，要想都是三类点，限制有且仅有这两个：

- 除了 $1$，一个点至少有一条入边
- 除了 $n$，一个点至少有一条出边

还是做不了，蛋疼的部分就是有两个限制，太多了，容斥，你们两个只能活一个。

让第一个活，然后 dp 维护容斥过程，设 $f_{i,j}$ 表示当前 $i$ 个三类点，硬点了 $j$ 个不满足条件二的图方案数，直接转移是 $O(1)$ 的。

至此本题的所有步骤做到了 $O(n^2)$。如果做不到可以分步转移让他做到。

因为这题细节挺多所以贴个代码。

```cpp
#include"bits/stdc++.h"
#ifdef REANI
	#include"windows.h"
	using namespace std;
	void SetMemoryLimit(SIZE_T MB){
		HANDLE job=CreateJobObject(NULL,NULL);
		assert(job!=NULL);
		JOBOBJECT_EXTENDED_LIMIT_INFORMATION info={0};
		info.BasicLimitInformation.LimitFlags=JOB_OBJECT_LIMIT_PROCESS_MEMORY;
		info.ProcessMemoryLimit=MB;
		assert(SetInformationJobObject(job,JobObjectExtendedLimitInformation,&info,sizeof(info))&&AssignProcessToJobObject(job,GetCurrentProcess()));
	}
#else
	using namespace std;
#endif
const int maxn = 2010;
int n,mo,Pw[maxn];
inline int Ksm(int b,int t){
	int r=1;
	while(t){
		if(t&1)r=1ll*r*b%mo;
		b=1ll*b*b%mo,t>>=1;
	}
	return r;
}
inline int Pl(int u,int v){return (u+v>=mo?u+v-mo:u+v);}
inline int Mi(int u,int v){return Pl(u,mo-v);}
inline int Ml(int x){return x;}
template <typename ...Args>inline int Ml(int u,Args ...v){return 1ll*u*Ml(v...)%mo;}
template <typename ...Args>inline int Pl(int u,Args ...v){return Pl(u,Pl(v...))%mo;}
int f[maxn][maxn],F[maxn],h[maxn][maxn],H[maxn],C[maxn][maxn],A[maxn],Coef[maxn],g[maxn];
int main(){
	#ifdef REANI
		SetMemoryLimit(512*1048576);
	#endif
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n>>mo,Pw[0]=1;
	for(int i=1;i<=n;i++)Pw[i]=Ml(2,Pw[i-1]);
	for(int i=0;i<=n;i++)C[i][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			C[i][j]=Pl(C[i-1][j],C[i-1][j-1]);
	f[1][0]=1,f[1][1]=1;
	for(int i=2;i<=n;i++)
		for(int j=0;j<i;j++){
			f[i][j]=Pl(f[i][j],Ml(f[i-1][j],Mi(Pw[i-1-j],1)));
			f[i][j+1]=Pl(f[i][j+1],Ml(f[i-1][j],Mi(Pw[i-1-j],1)));
		}
	for(int i=2;i<=n;i++){
		for(int j=0;j<i;j++){
			if(j&1)F[i]=Mi(F[i],Ml(f[i-1][j],Mi(Pw[i-1-j],1)));
			else F[i]=Pl(F[i],Ml(f[i-1][j],Mi(Pw[i-1-j],1)));
		}
	}
	h[1][1]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=i;j++)
			h[i][j]=Pl(Ml(h[i-1][j],Mi(Pw[i-1],1)),h[i-1][j-1]);
	for(int i=n;i>=1;i--)
		for(int j=n;j>=1;j--){
			h[i][j]=h[i-1][j-1];
			if(h[i][j])assert(i>=2),H[j]=Pl(H[j],Ml(C[n-2][n-i],h[i][j]));
		}
	for(int N=1;N<=n;N++)
		for(int r=1;r<=N;r++)
			Coef[r]=Pl(Coef[r],Ml(h[n][N],C[N-2][r-2]));
	for(int K=2;K<=n;K++)
		for(int r=K;r<=n;r++)
			A[K]=Pl(A[K],Ml(F[K],h[r][K],Coef[r]));
	A[0]=Ksm(2,n*(n-1)/2);
	for(int i=2;i<=n;i++)
		A[0]=Mi(A[0],A[i]);
	for(int K=0;K<=n;K++)
		cout<<A[K]<<' ';
	cout<<'\n';
}
```

---

## 作者：BreakPlus (赞：5)

想了很久二项式反演，但没有什么用。


以下计数的内容均默认存在 $1 \to n$ 的路径。只需要最后输出答案的时候令 $ans_0 = ans_2$ 即可。

----


先把能到达 $1$ 和 $n$ 的这 $K$ 个点扣出来，称为黑点（忽略不在这 $K$ 个点之中的其他点），计数这些点之间的连边方案。

不难设计一个 dp。令 $dp_{i,j}$ 表示前 $i$ 个点还剩 $j$ 个点没有后继（也就是这些点将来要么连到之后的某个点，要么连到 $n$），新加入一个点之后，这 $j$ 个点中某些点会连向新点，又有了后继。枚举这样的点有 $k$ 个，写出转移方程：

$dp_{i,j} \times \binom{j}{k} \times (2^{i-j}-[k=0])\to dp_{i+1,j+1-k}$

然后得到 $w_K = \sum \limits_{1 \le j < K} 2^{K-1-j}dp_{K-1,j}$，表示这 $K$ 个点之间的连边方案数。

----

再考虑在**黑**点中插入能到达 $1$ 但不能到达 $n$ 的点，称为**红**点。

> 这些点必须向前连一条边，且红点黑点都可以连，但不能向后连黑点。这部分系数是容易计算的，从前往后考虑并 dp 即可（记录 $g_{i,j}$ 表示前 $i$ 个点中有 $j$ 个红点）。

再考虑在已有**红、黑**点的图中，加入一些**白**点（不能到达 $1$）。

> 这些点可以向后连边（也可以不连），且**白、红、黑**点都可以连，但不能向前连**红、黑**点。也容易计算，从后往前考虑并 dp。

---

这两部分都可以 $\mathcal{O}(n^2)$ 完成 dp 和贡献计算。但算 $w_K$ 的复杂度是 $\mathcal{O}(n^3)$ 的。

对于一个有一定经验的计数选手来说，$\mathcal{O}(n^3)$ 过 2000 的 dp 是极其容易的。这题只要加一个 barrett 优化取模就好了。

```cpp
inline void addmod(int &x){ if(x >= mod) x -= mod; }
int dp[2005][2005],C[2005][2005],pw[2005],ok[2005],g[2005][2005],h[2005][2005],cpy[2005][2005],fk[2005][2005];

int tmp[2005][2005], ans[2005];
const int N = 500000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}
struct Mod
{
    ll m, p;
    void init(int pp) { m = ((__int128)1 << 64) / pp; p = pp; }
    ll operator ()(ll x)
    {
        return x - ((__int128(x) * m) >> 64) * p;
    }
} node;
void procedure(){
	n=read(),mod=read(); node.init(mod);
	math_init();
	pw[1]=1; for(int i=2;i<=n;i++) pw[i]=(2*pw[i-1]+1)%mod;
	dp[1][1]=fk[1][1]=1;

	for(int i=1;i<n;i++){
		for(int j=1;j<=i;j++){
			cpy[i][j]=dp[i][j]=1ll*dp[i][j]*fac[j]%mod;
			dp[i][j]=1ll*dp[i][j]*(pw[i-j]+1)%mod;
		}
		for(int j=1;j<=i;j++){
			for(int k=0;k<=j;k++){
				dp[i+1][j+1-k]=node(dp[i+1][j+1-k]+1ll*dp[i][j]*inv[k]);
			}
			addmod(dp[i+1][j+1]+=mod-cpy[i][j]);
		}
		for(int j=0;j<=i;j++){
			dp[i+1][j+1]=1ll*dp[i+1][j+1]*inv[j]%mod;
			fk[i+1][j+1]=dp[i+1][j+1];
		}
	}
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++){
			ok[i]=(ok[i]+1ll*fk[i-1][j]*(pw[i-1-j]+1))%mod;
		}
	}
	g[1][0]=1;
	for(int i=1;i<n;i++){
		for(int j=0;j<i;j++){
			g[i+1][j]=(g[i+1][j]+g[i][j])%mod;
			g[i+1][j+1]=(g[i+1][j+1]+1ll*g[i][j]*pw[i])%mod;
		}
	}

	h[1][0]=1;
	for(int i=1;i<n;i++){
		for(int j=0;j<i;j++){
			h[i+1][j]=(h[i+1][j]+h[i][j])%mod;
			h[i+1][j+1]=(h[i+1][j+1]+1ll*h[i][j]*(pw[i]+1))%mod;
		}
	}

	for(int i=2;i<=n;i++){
		for(int j=0;j<=i-2;j++){
			ans[i-j]=(ans[i-j]+1ll*g[i-1][j]*ok[i-j]%mod*h[n-1][n-i])%mod;

		}
	}
	ans[0]=ans[2];
	for(int i=0;i<=n;i++) printf("%d ", ans[i]); puts("");
}
```

---

## 作者：Petit_Souris (赞：1)

很考验基本功的计数题。

先考虑 $k = n$ 怎么做。省选 2025 D2T2 再次警醒我们，DAG 上每个点都有经过他的 $1\to n$ 的路径等价于每个点都有入边和出边，除了 $1, n$。

两个限制不方便同时处理，这时候可以考虑容斥。比如说我们强制规定一些点违反限制，入度必须为 $0$。这时候可以直接从后往前 dp：设 $dp_{i, j}$ 表示 $[i, n]$ 中的点，强制违反了 $j$ 个点。那么对于 $i$ 连边时，就是在 $n - i - j$ 个没有强制违反的点中任意取一个子集。最后系数为 $(-1) ^ j$。

这样可以求出所有 $i$ 个点的 $k = i$ 的答案，设为 $f_i$。

现在考虑 $k < n$ 的情况。那么我们先选出一个 $k$ 个点的方案 $f_k$，再考虑剩下的点。因此所有点可以分为三类：

- $1$ 类点：$1\to x \to n$ 的点；

- $2$ 类点：$1 \to x$，但是 $x \to n$ 不成立；

- $3$ 类点：$1\to x$ 不成立。

考虑 $1-1$ 以外的连边。发现 $3$ 可以往后面任意点连边，而 $1,2$ 都只能向后面 $2$ 连边。

因此我们可以这样倒过来 dp：设 $g_{i, j, k}$ 表示 $[i, n]$ 中，目前有 $j$ 个 $1$，$k$ 个 $2$ 的方案数。这样是 $\mathcal O(n ^ 3)$ 的。

但是我们发现 $3$ 类点的贡献只跟位置相关，是一个 $2^{n - i}$ 的形式。也就是说我们可以做一个分步转移：

首先求出 $g_{i, j}$ 表示 $i$ 个 $1, 2$ 类点，目前 $j$ 个 $1$ 类点的方案数；再求出 $h_{i, j}$ 表示 $i$ 个点中选出 $j$ 个 $3$ 类点，贡献之和。最后再把 $f, g, h$ 结合起来就容易计算出答案。

时间复杂度 $\mathcal O(n ^ 2)$。

```cpp
#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using namespace std;
template <class T>
using Ve = vector<T>;
#define ALL(v) (v).begin(), (v).end()
#define pii pair<ll, ll>
#define rep(i, a, b) for(ll i = (a); i <= (b); ++i)
#define per(i, a, b) for(ll i = (a); i >= (b); --i)
#define pb push_back
bool Mbe;
ll read() {
    ll x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}
void write(ll x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const ll N = 2009;
ll n, Mod, pw2[N], dp[N][N], f[N], dp2[N][N], ans[N];
ll pw(ll x, ll p) {
    ll res = 1;
    while(p) {
        if(p & 1) res = res * x % Mod;
        x = x * x % Mod, p >>= 1;
    }
    return res;
}
bool Med;
int main() {
    cerr << fabs(&Med - &Mbe) / 1048576.0 << "MB\n";
    n = read(), Mod = read();
    pw2[0] = 1;
    rep(i, 1, n) pw2[i] = pw2[i - 1] * 2 % Mod;
    dp[1][0] = 1, f[1] = 1;
    rep(i, 1, n - 1) {
        rep(j, 0, i - 1) {
            dp[i + 1][j] = (dp[i + 1][j] + dp[i][j] * (pw2[i - j] - 1)) % Mod;
        }
        rep(j, 0, i) {
            if(j & 1) f[i + 1] = (f[i + 1] - dp[i + 1][j] + Mod) % Mod;
            else f[i + 1] = (f[i + 1] + dp[i + 1][j]) % Mod;
        }
        rep(j, 0, i - 1) {
            dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j] * (pw2[i - j] - 1)) % Mod;
        }
    }
    dp2[0][0] = 1;
    rep(i, 0, n - 1) {
        rep(j, 0, i) {
            // 3
            if(i && i < n - 1) dp2[i + 1][j + 1] = (dp2[i + 1][j + 1] + dp2[i][j] * pw2[n - i - 1]) % Mod;
            // !3
            dp2[i + 1][j] = (dp2[i + 1][j] + dp2[i][j]) % Mod;
        }
    } 
    memset(dp, 0, sizeof(dp));
    dp[1][1] = 1;
    rep(i, 1, n - 1) {
        rep(j, 1, i) {
            // 1
            dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % Mod;
        }
        rep(j, 2, i + 1) {
            ans[j] = (ans[j] + dp[i + 1][j] * dp2[n][n - (i + 1)] % Mod * f[j]) % Mod;
            // if(j == 2) cout << i << " " << dp[i + 1][j] << " " << dp2[n][n - (i + 1)] << " " << f[j] << endl;
        }
        rep(j, 1, i) {
            // 2
            dp[i + 1][j] = (dp[i + 1][j] + dp[i][j] * (pw2[i] - 1)) % Mod;
        }
    }
    ans[0] = ans[2];
    rep(i, 0, n) write(ans[i]), putchar(' ');
    putchar('\n');
    cerr << "\n" << clock() * 1.0 / CLOCKS_PER_SEC * 1000 << "ms\n";
    return 0;
}
```

---

## 作者：Cindy_Li (赞：1)

计数题。

首先考虑 $k=n$ 即所有点都在 $1\to n$ 的路径上。注意到只需保证除 $1$ 之外所有点入度 $>0$，除 $n$ 之外所有点出度 $>0$ 即可。

两个条件不好，容斥掉一个。$f1(i,j)$ 表示后 $i$ 个点，钦定 $j$ 个点入度为 $0$ 的方案数，要求 $j<i$ 即第 $i$ 个点只能在转移时被钦定是否有入度（其实就是为了让第一个点没有限制）。

容易通过 $f1$ 容斥得出 $g(i)$ 表示 $i$ 个点都在 $1\to i$ 的路径上的方案数。

接下来考虑插入其他点并保证新的点不在 $1\to n$ 的路径上。
图中的点可以分为三类：
1. $1\to i,i\to n$
2. $1\to i,i\not\to n$
3. $1\not\to i$

- $1$ 类点可以和编号比它小的 $3$ 类点连边。
- $2$ 类点可以和编号比它小的 $1, 2 ,3$ 类点连边，且必须至少和一个 $1$ 或 $2$ 类点连边。
- $3$ 类点可以和编号比它小的 $3$ 类点连边。

注意到，$3$ 类点可以向任意编号比它大的点连边，贡献可以单独计算。

这样就只剩下形如 $1\to 2$ 和 $2\to 2$ 的连边，$f2(i,j)$ 表示当前有 $i$ 个 $1$ 类点，$j$ 个 $2$ 类点的方案数。初始 $f(1,0)=1$，转移时每个 $2$ 类点可以和前面的所有点连边。统计答案时要限定最后一个点是 $1$ 类点。

最后把三部分贡献乘起来就好啦。

---

## 作者：Danslapiscine (赞：0)

注意到若把整张 DAG 分成三类点，一类是符合题目条件的点，一类是从 1 号点可以到达的点，一类是从 1 号点不可到达的点。那么合法点连边方法有 ① -> ②，③ -> ①，③ -> ②。他们之间相互独立，也就是不同类之间的连边合法性只与类的种类有关，故可以将他们分开考虑，再进行合并，以降低问题复杂度。

考虑全为 ① 类点，即只 $k = n$ 的情况怎么做。容易地设计 $O(n^3)$ 的 dp：$f(i,j)$ 表示前 $i$ 个点，有 $j$ 个不同分支（即有 $j$ 个出度为 0 的点），DAG 的方案数。枚举 $k$ 表示前面连接了多少出度为 0 的点，$f(i,j) = \sum f(i-1,j+k-1) \times C_{j+k-1}^{k} \times 2^{(i-1)-(j+k-1)}$。~~我会FFT~~但是难以优化。

所以~~难以~~想到用容斥原理的思路设计状态。相当于维护每个节点入度出度不为 0，保证入度不为 0 是好做的。我们主要要维护出度为 0 的点，那么设 $f(i,j)$ 为前 $i$ 个点，钦定 $j$ 个点出度为 0，那么可以转移 $f(i,j) = f(i-1,j) \times (2^{i-1-j}-1) + f(i-1,j-1) \times (2^{i-j}-1)$ ，然后通过容斥公式用 $f(i)$ 计算出使用 $i$ 个点，没有出度为 0 的点的 DAG 的方案数。时间复杂度 $O(n^2)$。

若加入 ② 类点，就相当于在 ① 类点有 $i$ 个的基础上，将方案数乘上 $j$ 个 ② 类点自己连边和与 ① 类点连边的方案数，得到符合条件的点数为 $i$，总点数为 $i+j$ 的答案。这直接 dp 就好了。加 ③ 类点同理。具体写法看代码。

这个故事告诉我们，对计数 dp 的优化束手无策的时候，也许可以试试容斥。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, p;
int fac[2002], inv[2002], invfac[2002];
void init(){
	fac[0] = 1, inv[1] = 1, invfac[0] = 1;
	for(int i=1;i<=2000;i++) fac[i] = 1ll * fac[i-1] * i % p;
	for(int i=2;i<=2000;i++) inv[i] = (1ll * (-p/i) * inv[p%i] % p + p) % p;
	for(int i=1;i<=2000;i++) invfac[i] = 1ll * invfac[i-1] * inv[i] % p;
}
int C(int x,int y){
	if(x < y || x < 0 || y < 0) return 0;
	return 1ll * fac[x] * invfac[y] % p * invfac[x-y] % p;
}
int ksm(int s,int cnt){
	int ret = 1;
	while(cnt){
		if(cnt&1) ret = 1ll * ret * s % p;
		s = 1ll * s * s % p;
		cnt >>= 1;
	}
	return ret;
}

int f[2002][2002], g[2002][2002]; // 前 i 个数，钦定 j 个没有出度
int S[2002]; 

int dp1[2002][2002], dg1[2002][2002], dp2[2002][2002];
int Ans[2002];

int main(){
	scanf("%d%d",&n,&p);
	init();
	
	f[0][0] = 1, g[0][0] = 1;
	f[1][0] = 1, f[1][1] = 1, g[1][0] = 1;
	for(int i=2;i<=n;i++) {
		for(int j=0;j<=i;j++) {
			if(i != j) f[i][j] = 1ll * f[i-1][j] * (ksm(2, i-j-1) - 1) % p;
			if(i != j) g[i][j] = 1ll * f[i-1][j] * (ksm(2, i-j-1) - 1) % p;
			if(j > 0) f[i][j] = (1ll * f[i][j] + 1ll * f[i-1][j-1] * (ksm(2, i-j) - 1) % p) % p;
		}
	}
	for(int i=0;i<=n;i++) {
		for(int j=0;j<=i;j++){
			if(j & 1) S[i] = ((1ll * S[i] - g[i][j]) % p + p) % p;
			else S[i] = (1ll * S[i] + g[i][j]) % p;
		}
	}
	
	dp1[0][0] = 1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			dp1[i][j] = dp1[i-1][j];
			dg1[i][j] = dp1[i-1][j];
			if(i != 1 && i != n) dp1[i][j] = (dp1[i][j] + 1ll * dp1[i-1][j-1] * (ksm(2, i-1)-1) % p) % p;
		}
	}
	
	dp2[0][0] = 1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			dp2[i][j] = 1ll * dp2[i-1][j] * ksm(2, j) % p;
			if(i != 1 && i != n && j != 0) dp2[i][j] = (dp2[i][j] + 1ll * dp2[i-1][j-1] * ksm(2, j-1) % p) % p;
		}
	}
	
	//S[i] * dg1[k][k-i] * dp2[n][n-k]
	for(int i=0;i<=n;i++){
		for(int k=i;k<=n;k++){
			Ans[i] = (Ans[i] + 1ll * S[i] * dg1[k][k-i] % p * dp2[n][n-k] % p) % p;
		}
	}
	Ans[0] = Ans[2];
	
	for(int i=0;i<=n;i++) printf("%d ",Ans[i]);
	
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

考虑 $k=n$ 的解法。即需要计算有多少个 DAG 满足每个点都能到达 $n$ 且 $1$ 能到达每个点。

我们下面说明满足的图是：对于每个 $u$（$u\neq 1$）都有入度；对每个 $u$（$u\neq n$）都有出边。

首先满足原题条件的图一定满足这个条件。其次满足上述条件的图，随便找个点不断往前走肯定能到达 $n$，从里反过来也能到达 $1$。

于是，我们考虑来容斥这个条件，钦定一些点没有入度，一些点没有出度。这样条件下，变成每条从可以有出度的点指向可以有出度的点，每条边是独立选取的。直接 dp 即可，复杂度 $O(n^2)$。

考虑如果有 $k$ 个满足条件的点。假设这样的点为 A 类点，剩下的点会分成两类，能从 1 到达而不可达 $n$（B 类）和不能从 1 到达（C 类）。

我们观察这 3 类点之间的关系：

- A 类点之间的方案数我们上面的 dp 已经求出来了；
- B 类点的前驱可以是任意点，B 类点的后驱不能是 A 类点（否则可达 $n$）；
- C 类点的后驱可以是任意点，C 类点的前驱不能是 AB 类点。

你发现这三个条件是有包含关系的。我们先做一次 dp 确定哪些是 C 类点，再做一次 dp 确定哪些是 B 类点即可。

---

## 作者：happybob (赞：0)

考虑 $k=n$ 时答案是多少，这个限制等价于 $\forall 2 \leq i \leq n,in_i > 0$，且 $\forall 1 \leq i < n, out_i > 0$。

同时刻画入度和出度是很麻烦的，考虑从后往前限定每个点都有出边，同时容斥一些入度为 $0$ 的点，记 $f_{i,j}$ 表示考虑了 $i$ 个点，钦定 $j$ 个点入度为 $0$，且每个点出度都非 $0$ 时的总方案数。转移很容易，于是可以对每个 $n$ 求出 $n=k$ 的答案，记为 $h_n$。

对于 $k<n$，考虑图应该是先有一个 $h_k$，然后加入 $n-k$ 个点，要求每个点要么不能从 $1$ 到达，要么不能到达 $n$。

考虑每个新加入的点，其可能可以从 $1$ 到达，此时限制其不能到达 $n$，或者其无法从 $1$ 到达，此时对这个点没有任何限制。考虑将新加入的点分为这两类，容易发现无法从 $1$ 到达的点可以向其之后的所有点任意连边而不影响条件合法性，所以贡献就是 $2^{n-i}$，对于能从 $1$ 到达的点，则限制其向后只能连接 $1$ 类点，且每个 $1$ 类点向前必然有以前加入的点或者 $1$ 类点向其连边。

将 $2$ 类点的 $\prod 2^{n-i}$ 的贡献单独计算，由于 $1$ 类点以及原来的 $k$ 个点向后不能连接 $2$ 类点，所以之间是独立的。对于原 $k$ 个点和 $1$ 类点，考虑从前往后 DP，对于每个 $1$ 类点，要求前面至少一个 $1$ 类或原有点向其连边，容易记 $f_{i,j}$ 表示 $i$ 个点，有 $j$ 个原有点的方案数，从而进行转移。另外再记一个 DP 就可以将 $2$ 类点与其他点贡献合并，总复杂度 $O(n^2)$。

---

