# Graph And Numbers

## 题目描述

You are given an undirected graph with $ n $ vertices and $ m $ edges. You have to write a number on each vertex of this graph, each number should be either $ 0 $ or $ 1 $ . After that, you write a number on each edge equal to the sum of numbers on vertices incident to that edge.

You have to choose the numbers you will write on the vertices so that there is at least one edge with $ 0 $ written on it, at least one edge with $ 1 $ and at least one edge with $ 2 $ . How many ways are there to do it? Two ways to choose numbers are different if there exists at least one vertex which has different numbers written on it in these two ways.

## 样例 #1

### 输入

```
6 5
1 2
2 3
3 4
4 5
5 1
```

### 输出

```
20
```

## 样例 #2

### 输入

```
4 4
1 2
2 3
3 4
4 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
35 29
1 2
2 3
3 1
4 1
4 2
3 4
7 8
8 9
9 10
10 7
11 12
12 13
13 14
14 15
15 16
16 17
17 18
18 19
19 20
20 21
21 22
22 23
23 24
24 25
25 26
26 27
27 28
28 29
29 30
```

### 输出

```
34201047040
```

# 题解

## 作者：AThousandSuns (赞：11)

在我的博客园看效果更佳：[点这里](https://www.cnblogs.com/1000Suns/p/11566940.html)

至今觉得这场 edu 的 G 比 EF 都要简单……

不知道为什么出题人要把 $m=0$ 放进去，先特判掉。

要求至少一个 $0$，至少一个 $1$，至少一个 $2$，容斥一波，变成总方案数-没有 $0$-没有 $1$-没有 $2$+没有 $01$+没有 $02$+没有 $12$+没有 $012$。

没有 $0$ 和没有 $2$ 比较难搞，放到最后讨论。

没有 $1$，考虑一个联通块，这个联通块所有数都一样，方案数是 $2^{cnt}$，其中 $cnt$ 是联通块个数。

没有 $01$，也就是只有 $2$，如果一个联通块中没有边（单独一个点），那么当然可以随便放，否则这个联通块所有数都是 $1$。方案数 $2^{cnt2}$，其中 $cnt2$ 是单独一个点的联通块个数。

没有 $02$，也就是只有 $1$，等价于将这个图黑白染色的方案数。如果可以黑白染色，那么方案数是 $2^{cnt}$，否则是 $0$。

没有 $12$，和没有 $01$ 一样。方案数是 $2^{cnt2}$。

没有 $012$，因为 $m\ne 0$，显然不可能。方案数为 $0$。

接下来就考虑没有 $0$ 的方案数（没有 $2$ 是一样的）。

这个数据范围很明显是让我们折半搜索。我们不妨先搜后半部分。

对于每个合法的后半部分（即没有两个是 $0$ 的点相邻），前半部分有哪些点不能是 $0$ 我们是知道的。

转变一下，变成当前半部分选取的 $0$ 点集合为 $S$ 时，后半部分有多少种方案 $val_S$。（我是这么写的）

满足条件的 $S$ 就是不能选的点的补集的子集。

实际上，在补集的 $val$ 加个 $1$，搜完后再做高维后缀和就能得到真的 $val_S$。应该不难理解。

然后再搜前半部分，对每个合法方案都加上它的 $val$ 就行了。

时间复杂度，如果前半部分有 $T$ 个点，复杂度是 $O(2^TT+2^{n-T})$。

由于我比较懒，我就取了 $T=\frac{n}{2}$。实际上要是 $T$ 控制得够好，应该可以跑过 $n=50$。（取 $T=23$，大概是 3e8，3.5s+CF 神机应该没问题）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=1048576;
#define MP make_pair
#define PB push_back
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline ll read(){
	char ch=getchar();ll x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,m,cnt,cnt2,bar,lim;
ll e[40],ans,val[maxn];
bool ind[40],vis[40],col[40],flag=true;
void dfs(int u){
	vis[u]=true;
	FOR(v,0,n-1) if((e[u]>>v)&1){
		if(!vis[v]) col[v]=col[u]^1,dfs(v);
		else{
			if(col[v]!=(col[u]^1)) flag=false;
		}
	}
}
void dfs1(int dep,ll st,ll used){
	if(dep==bar) return void(val[(~st)&(lim-1)]++);
	dfs1(dep-1,st,used);
	if(!((st>>dep)&1)) dfs1(dep-1,st|e[dep],used|1<<dep);
}
void dfs2(int dep,ll st,ll used){
	if(dep==bar+1) return void(ans-=2*val[used&(lim-1)]);
	dfs2(dep+1,st,used);
	if(!((st>>dep)&1)) dfs2(dep+1,st|e[dep],used|1<<dep);
}
int main(){
	n=read();m=read();
	if(!m) return puts("0"),0;
	FOR(i,0,n-1) ind[i]=true;
	FOR(i,1,m){
		int u=read()-1,v=read()-1;
		e[u]|=1ll<<v;e[v]|=1ll<<u;
		ind[u]=ind[v]=false;
	}
	FOR(i,0,n-1) if(ind[i]) cnt2++;
	FOR(i,0,n-1) if(!vis[i]) cnt++,dfs(i);
	ans=(1ll<<n)-(1ll<<cnt)+(1ll<<cnt2)+(1ll<<cnt2)+(flag?1ll<<cnt:0);
	bar=(n-1)/2;lim=1<<(bar+1);
	dfs1(n-1,0,0);
	for(int i=1;i<lim;i<<=1)
		for(int j=0;j<lim;j+=i<<1)
			FOR(k,0,i-1) val[j+k]+=val[i+j+k];
	dfs2(0,0,0);
	printf("%lld\n",ans);
}
```

---

## 作者：Alex_Wei (赞：5)

- Update on 2022.10.17：重写题解，[原题解](https://www.luogu.com.cn/paste/wxpdoc1e)。

> [CF1221G Graph And Numbers](https://www.luogu.com.cn/problem/CF1221G)

特判 $m = 0$ 答案为 $0$。

我们发现，钦定一个数出现是困难的，但钦定一个数不出现是容易的。因此，我们考虑没有出现的数的集合 $S$，设其对应方案数为 $f_S$，设钦定 $S$ 没有出现的方案数为 $g_S$，则 $g_S = \sum\limits_{S\subseteq T \subset \{0, 1, 2\}} f_T$。我们希望求 $f_{\varnothing}$，容斥得 $f_{\varnothing} = \sum\limits_{S\subset \{0, 1, 2\}} (-1) ^ {|S|} g_S$。
- 删去所有孤点。设孤点数为 $c$，则最终将答案乘以 $2 ^ c$。
- $g_{\varnothing}$：显然等于 $2 ^ {n - c}$。
- $g_{\{0, 1\}}$：要求每个连通块只出现 $2$。因为不存在孤点，只能全部填 $1$。
- $g_{\{0, 2\}}$：要求每条边的两端分别为 $0$ 和 $1$。若存在连通块不是二分图，则 $g_{\{0, 2\}} = 0$，否则每个连通块有两种染色方案，为 $2$ 的连通块数次方。
- $g_{\{1, 2\}}$：和 $g_{\{0, 1\}}$ 对称。
- $g_{\{0\}}$：填 $0$ 的数形成独立集，问题转化为经典独立集计数。Meet-in-the-middle，将点集分成左右两部分 $L, R$。设 $L$ 的所有独立集的集合为 $S_L$，$R$ 的所有独立集的集合为 $S_R$，关于左部点子集 $I$ 的函数 $N(I)$ 表示与 $I$ 相邻的右部点集，则答案为 $\sum\limits_{I\in S_L}\sum\limits_{J\in S_R} [N(I) \cup J = \varnothing]$，即 $\sum\limits_{I\in S_L} \sum\limits_{J\in S_R} [J\subseteq (R\backslash N(I))]$。高位前缀和 $F(J) = [J\in S_R]$ 得到 $\hat F(J) = \sum\limits_{J'\in S_R} [J'\subseteq J]$ 即可。
- $g_{\{1\}}$：如果一个连通块同时存在 $0, 1$ 点，则必然存在 $1$ 边。所以要求每个连通块要么全填 $0$，要么全填 $1$，为 $2$ 的连通块数次方。
- $g_{\{2\}}$：填 $1$ 的数形成独立集，和 $g_{\{0\}}$ 对称。

综上，总时间复杂度视实现精细程度为 $\mathcal{O}(2 ^ {n/2} n ^ 2)$ 或 $\mathcal{O}(2 ^ {n / 2} n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using uint = unsigned int;
using ld = long double;
// using lll = __int128;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ull = unsigned long long;
inline ll read() {
  ll x = 0, sgn = 0;
  char s = getchar();
  while(!isdigit(s)) sgn |= s == '-', s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return sgn ? -x : x;
}
inline void print(ll x) {
  if(x < 0) return putchar('-'), print(-x);
  if(x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}
bool Mbe;
constexpr int N = 40 + 5;
constexpr int K = 1 << 20;
int n, m, e[N][N], ind[N], vis[N], size;
void dfs(int id) {
  ind[size++] = id, vis[id] = 1;
  for(int i = 1; i <= n; i++) if(e[id][i] && !vis[i]) dfs(i);
}
ll single, _1 = 1, _01 = 1, _02;
int bipar, col[N], f[K], lim[K];
void check(int id, int c) {
  col[id] = c;
  for(int i = 1; i <= n; i++) {
    if(!e[id][i]) continue;
    if(col[i] == -1) check(i, c ^ 1);
    else if(col[i] == c) bipar = 0;
  }
}
void solve() {
  if(size == 1) return single++, void();
  bipar = 1, check(ind[0], 0);
  _1 *= bipar ? 2 : 0, _02++;
  int L = size + 1 >> 1, R = size - L;
  memset(lim, 0, sizeof(lim));
  for(int i = 0; i < L; i++)
    for(int j = 0; j < R; j++)
      if(e[ind[i]][ind[L + j]])
        lim[1 << i] |= 1 << j;
  for(int i = 1; i < 1 << L; i++) lim[i] = lim[i & -i] | lim[i ^ (i & -i)];
  memset(f, 0, sizeof(f));
  for(int i = 0; i < 1 << R; i++) {
    bool ok = 1;
    for(int j = 0; j < R; j++) if(i >> j & 1)
      for(int k = j + 1; k < R; k++) if(i >> k & 1)
        ok &= !e[ind[L + j]][ind[L + k]];
    f[i] = ok;
  }
  for(int k = 1; k < 1 << R; k <<= 1)
    for(int i = 0; i < 1 << R; i += k << 1)
      for(int j = 0; j < k; j++)
        f[i | j | k] += f[i | j];
  ll msk = (1 << R) - 1, ans = 0;
  for(int i = 0; i < 1 << L; i++) {
    bool ok = 1;
    for(int j = 0; j < L; j++) if(i >> j & 1)
      for(int k = j + 1; k < L; k++) if(i >> k & 1)
        ok &= !e[ind[j]][ind[k]];
    if(ok) ans += f[msk ^ lim[i]];
  }
  _01 *= ans;
}
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n >> m;
  if(!m) cout << "0\n", exit(0);
  for(int i = 1; i <= m; i++) {
    int u = read(), v = read();
    e[u][v] = e[v][u] = 1;
  }
  memset(col, -1, sizeof(col));
  for(int i = 1; i <= n; i++) {
    if(vis[i]) continue;
    size = 0, dfs(i), solve();
  }
  cout << (1ll << n) - (_01 + _01 + (1ll << _02) - 1 - _1 - 1 << single) << "\n";
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/10/17
author: Alex_Wei
start coding at 
finish debugging at 15:36
*/
```

---

## 作者：tobie (赞：4)

提供一个不一样的搜索做法，可以跑 $n\le 50 , T= 20$，其中 $T$ 为数据组数。

首先我们通过容斥之类的技巧把问题转化成独立集计数问题。这部分可以看其他 dalao 的题解，这里不再赘述。

考虑 $dp(S)$ 表示 $S$ 的生成子图的独立集个数。朴素的做法是去钦定编号最小的点是否在独立集中。加上记忆化可以做到 $2^{\frac n 2}$。

考虑优化转移的过程：每次不再选择编号最小的点，而是选择生成子图中度数最大的点把它删掉。

似乎还是没有什么本质上的优化。但是我们发现一个性质：如果一个图的最大度数 $\le 2$，那它就是由一堆不想交的环和链组成的平凡图，而环和链的问题我们都可以预处理出来，这部分的时间可以忽略不计。

所以我们只需要考虑 $\max(deg)\ge 3$ 的问题。那我们记 $f(n)$ 表示一个大小为 $n$ 的图的递归次数，则有 $f(n)=f(n-3)+f(n-1)$，在 $n=50$ 时大约为 $83316385$，可以接受，而且甚至不需要用到记忆化。

此外，如果 $S$ 由多个连通块组成，则可以对这些连通块分开处理，最后把它们乘起来就是答案。

虽然处理连通块以及求度数之类的操作可能会产生一个 $O(n^2)$ 的常数，但是这个 $f(n)$ 是严重卡不满的，而且跑得飞快。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
inline int Read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while('0'<=ch&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}
typedef long long ll;
const int N=59;
struct Bian{
	int u,v;
}e[N*N];
int n,m;
namespace Task1{

ll G[N];
ll dp[N][2][2],f[N],g[N];
int col[N];
void dfs2(int u,ll S,int c)
{
	col[u]=c;
	for(int j=0;j<n;j++)
	if((((S&G[u])>>j)&1)&&!col[j]) dfs2(j,S,c);
}
inline int popc(ll x)
{
	int res=0;
	while(x) res++,x-=(x&(-x));
	return res;	
}
ll dfs(ll S)
{
	if(S==0) return 1;
	int ccnt=0;
	for(int i=0;i<n;i++) col[i]=0;
	for(int i=0;i<n;i++)
	if(((S>>i)&1)&&!col[i]) dfs2(i,S,++ccnt);
	if(ccnt>1)
	{
		vector<ll> fz(ccnt);
		for(int i=0;i<n;i++)
		if(col[i]) fz[col[i]-1]|=(1ll<<i);
		ll ans=1; 
		for(int i=0;i<ccnt;i++) ans*=dfs(fz[i]);
		return ans;
	}
	
	int mx=-1,pos=-1;
	int dsum=0;
	for(int i=0;i<n;i++)
	if((S>>i)&1)
	{
		int d=popc(G[i]&S);
		dsum+=d;
		if(d>mx) mx=d,pos=i;
	}
	if(mx<=2)
	{
		int siz=popc(S);
		if(dsum==(siz<<1)) return g[siz];
		else return f[siz];
	}
	else
	{
		return dfs(S^(S&G[pos])^(1ll<<pos))+dfs(S^(1ll<<pos));
	}
}
void ycl()
{
	dp[1][0][0]=dp[1][1][1]=1;
	for(int i=1;i<=50;i++)
	for(int x=0;x<=1;x++)
	for(int y=0;y<=1;y++)
	for(int z=0;z<=1;z++)
	if(!(y&z)) dp[i][x][z]+=dp[i-1][x][y];
	for(int i=1;i<=50;i++)
	{
		if(i==1) f[i]=2;
		else
		{
			for(int x=0;x<=1;x++)
			for(int y=0;y<=1;y++)
			{
				f[i]+=dp[i][x][y];
				if(!(x&y)) g[i]+=dp[i][x][y];
			}
		}
	}
}
ll work()
{
	for(int i=0;i<n;i++) G[i]=0;
	for(int i=1;i<=m;i++)
	{
		int u=e[i].u,v=e[i].v;
		u--,v--;
		G[u]|=(1ll<<v);
		G[v]|=(1ll<<u);
	}
	ll ans=dfs((1ll<<n)-1);
	return ans;
}

}
int bcj[N*2],siz[N];
int getfa(int x){return bcj[x]==x?x:bcj[x]=getfa(bcj[x]);return x;}
void work(int id_)
{
	n=Read(),m=Read();
	for(int i=1;i<=n*2;i++) bcj[i]=i;
	for(int i=1;i<=m;i++)
	{
		e[i].u=Read(),e[i].v=Read();
		bcj[getfa(e[i].u)]=getfa(e[i].v+n);
		bcj[getfa(e[i].v)]=getfa(e[i].u+n);
	}
	if(m==0) return puts("0"),void();
	ll ans=(1ll<<n);
//	cerr<<"ans = "<<ans<<endl;
	ans-=(Task1::work()<<1);
//	cerr<<"ans = "<<ans<<endl;
	bool pd=1;
	for(int i=1;i<=n;i++)
	if(getfa(i)==getfa(i+n)) pd=0;
	
	for(int i=1;i<=n;i++) bcj[i]=i,siz[i]=0;
	for(int i=1;i<=m;i++) bcj[getfa(e[i].u)]=getfa(e[i].v);
	int cnt=0,cnt1=0;
	for(int i=1;i<=n;i++) siz[getfa(i)]++;
	for(int i=1;i<=n;i++)
	if(bcj[i]==i)
	{
		cnt++;
		cnt1+=(siz[i]==1);
	}
	if(pd) ans+=(1ll<<cnt);
	ans>>=cnt1;
	ans-=(1ll<<(cnt-cnt1))-2;
	ans<<=cnt1;
	printf("%lld\n",ans);
}
signed main()
{
	int T=1;
//	scanf("%d",&T);
	Task1::ycl();
	for(int i=1;i<=T;i++) work(i);
}
```

---

## 作者：2018ljw (赞：4)

蒟蒻表示看不懂高维前缀和、子集 dp 什么的是如何将复杂度降到 $O(2^n)$ 的，写一个比较暴力但好理解的做法。

首先基本容斥，转化为 $\{012\}-\{01\}-\{12\}-\{01\}+\{0\}+\{1\}+\{2\}-\{\emptyset\}$。这里的集合表示**允许出现**的权值。

设图中连通块个数为 $x$，其中孤立点有 $y$ 个。逐项分析，先处理比较好搞的。

1. $\{012\}$。随便填，$2^n$。
2. $\{02\}$、$\{0\}$、$\{2\}$。每条边两端颜色同为 $0$ 或 $1$，同一连通块颜色唯一。$\{02\}$ 贡献为 $2^x$，后两个贡献为 $2^y$。
3. $\{1\}$ 每条边两端颜色不同，转化为二分图判定问题，合法贡献为 $2^x$，不合法无贡献。

然后考虑 $\{01\}$ 与 $\{12\}$。这两种情况是对称的，方案数相同， 以 $\{01\}$ 为例。

一条边两边不能同为 $1$，即 $1$ 的点构成独立集，转化为独立集计数。

将原图分为两半，设左半点数为 $T$。暴力处理出左半某些位置为 $1$ 的每种方案是否可行，暴力处理出右半每种选择下左半哪些位置可以为 $1$。

这时我们枚举右半，就等价于问子集权值和。大佬用的高维前缀和蒟蒻理解上不去，所以我们暴力一些：枚举左半的 $2^T$ 种情况，暴力计算这些情况的答案后记录，即可 $O(1)$ 回答一次查询。

然后？没了。枚举子集复杂度用二项式定理可以化简成 $O(3^T)$。右半枚举+判合法复杂度 $O(2^{n-T}(n-T)^2)$，总复杂度 $O(2^{n-T}(n-T)^2+3^T)$，取 $T=17$ 即可通过。

```cpp
#include<cstdio>
int fa[41],sz[41],n;
int hed[4001],net[4001],ver[4001],tot;
bool lk[41][41];
void add(int x,int y){
	ver[++tot]=y;
	lk[x][y]=1;
	net[tot]=hed[x];
	hed[x]=tot;
}
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]); 
}
int col[41],lp,rp;
bool dfs(int x){
	int i;
	for(i=hed[x];i;i=net[i]){
		int y=ver[i];
		if(col[x]==col[y])return 0;
		if(col[y])continue;
		col[y]=col[x]^1;
		if(!dfs(y))return 0;
	}
	return 1;
}
bool lcheck(int s){
	int i,j;
	for(i=1;i<=lp;i++){
		if(!(s&(1<<i-1)))continue;
		for(j=i+1;j<=lp;j++){
			if(!(s&(1<<j-1)))continue;
			if(lk[i][j])return 0;
		}
	}
	return 1;
}
bool rcheck(int s){
	int i,j;
	for(i=1;i<=rp;i++){
		if(!(s&(1<<i-1)))continue;
		for(j=i+1;j<=rp;j++){
			if(!(s&(1<<j-1)))continue;
			if(lk[i+lp][j+lp])return 0;
		}
	}
	return 1;
}
int rts(int s){
	int d=(1<<lp)-1,i,j;
	for(i=1;i<=rp;i++){
		if(!(s&(1<<i-1)))continue;
		for(j=1;j<=lp;j++){
			if(!lk[i+lp][j])continue;
			if(d&(1<<j-1))d^=1<<j-1;
		}
	}
	return d;
}
int dp[1048577],sum[21];
bool fn[1048577];
int main(){
	int i,j,k,m;
	scanf("%d%d",&n,&m);
	if(m<=2)return printf("0"),0;
	for(i=1;i<=n;i++)fa[i]=i,sz[i]=1;
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
		int p=find(x),q=find(y);
		if(p==q)continue;
		fa[p]=q;sz[q]+=sz[p];
	}
	long long ans=1ll<<n;
	int gl=0,lt=0;
	for(i=1;i<=n;i++){
		if(fa[i]==i)lt++;
		if(fa[i]==i&&sz[i]==1)gl++;
	}
	long long a02=1;
	for(i=1;i<=n;i++){
		if(fa[i]==i){
			col[i]=2;
			if(dfs(i))a02*=2;
			else a02=0;
		}
	}
	ans+=1ll<<gl+1;ans+=a02;ans-=1ll<<lt;
	lp=n/2;if(lp>17)lp-=lp-17;rp=n-lp;
	const int lm=1<<lp,rm=1<<rp;
	for(i=0;i<lm;i++)fn[i]=lcheck(i);
	for(i=0;i<lm;i++){
		dp[i]=1;
		for(j=i;j;j=(j-1)&i)dp[i]+=fn[j];
	}
	for(i=0;i<rm;i++){
		if(!rcheck(i))continue;
		ans-=2ll*dp[rts(i)];
	}
	printf("%lld",ans);
}
```

---

## 作者：米奇 (赞：3)

## 思维+子集DP

现场本来是想到分成两半+子集DP，但有人说我是口胡就没写。

容斥，总方案-没有0-没有1-没有2+没有01+没有02+没有12-没有012 

整理一下，总方案-2*没有0-没有1+2*没有01（只有2）+没有02（只有1）

想一想：没有0和没有2是不是一样的 

总方案:2^n

没有0:对于一条边A-B,A=0那么B=1,分成两半，一半枚举选法，一半子集dp求出方案。

没有1:每个联通块全0或全1，dfs即可

没有01（只有2）:对于没边的点能选01，其他全1

没有02（只有1）: 2^(联通块个数) 

```cpp
//什么叫你的基本都是对的，我的都是口胡 
#include<bits/stdc++.h>
using namespace std;
#define next Next
#define last Last
#define int long long
const int N=45;
const int M=(1<<21);
int n,m,pd,mp[N][N],fa[N],vis[N],A[M],B[M],C[M],D[M];
/*char buf[1<<21],*p1=buf,*p2=buf;
inline int gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}*/
#define gc getchar
inline int read()
{
	int ret=0,f=0;char c=gc();
	while(!isdigit(c)){if(c=='-')f=1;c=gc();}
	while(isdigit(c)){ret=ret*10+c-48;c=gc();}
	if(f)return -ret;return ret;
}
int find(int x)
{
	if(fa[x]==x)return x;
	fa[x]=find(fa[x]);
	return fa[x];
}
int mei0()
{
	int xu=n/2,jia=n-xu;
	for(int i=1;i<=xu;i++)
		for(int j=1;j<=xu;j++)
			if(mp[i][j])A[(1<<(i-1))+(1<<(j-1))]=1;//不能相同 
	for(int i=xu+1;i<=n;i++)
		for(int j=xu+1;j<=n;j++)
			if(mp[i][j])B[(1<<(i-xu-1))+(1<<(j-xu-1))]=1;//不能相同 
	for(int i=0;i<xu;i++)
		for(int j=0;j<(1<<xu);j++)
			if(j&(1<<i))A[j]|=A[j^(1<<i)];
	for(int i=0;i<jia;i++)
		for(int j=0;j<(1<<jia);j++)
			if(j&(1<<i))B[j]|=B[j^(1<<i)];
	for(int i=0;i<(1<<jia);i++)
		if(!B[i])C[i]++;
	for(int i=0;i<jia;i++)
		for(int j=0;j<(1<<jia);j++)
			if(j&(1<<i))C[j]+=C[j^(1<<i)];
	for(int i=1;i<=xu;i++)
		for(int j=xu+1;j<=n;j++)
			if(mp[i][j])D[1<<(i-1)]|=(1<<(j-xu-1));
	for(int i=0;i<jia;i++)
		for(int j=0;j<(1<<jia);j++)
			if(j&(1<<i))D[j]|=D[j^(1<<i)];
	int ans=0;
	for(int i=0;i<(1<<xu);i++)
	{
		if(A[i])continue;
		int x=D[i];
		x=(1<<jia)-1-x;
		ans+=C[x];
	}
	return ans;
}
int mei1()
{
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(mp[i][j])fa[find(i)]=find(j);
	int ans=0;
	for(int i=1;i<=n;i++)
		if(fa[i]==i)ans++;
	return 1<<ans;
}
int mei01()
{
	int ans=1;
	for(int i=1;i<=n;i++)
	{
		bool flag=0;
		for(int j=1;j<=n;j++)
			if(mp[i][j])flag=1;
		if(!flag)ans=ans*2;
	}
	return ans;
}
void dfs(int u,int op)
{
	if(pd)return;
	vis[u]=op;
	for(int i=1;i<=n;i++)
		if(mp[u][i])
		{
			if(vis[i]==op)
			{
				pd=1;
				return;
			}
			else{
				if(vis[i]==-1)dfs(i,op^1);
			}
		}
}
int mei02()
{
	memset(vis,-1,sizeof(vis));
	int ans=0;
	for(int i=1;i<=n;i++)
		if(vis[i]==-1)
		{
			pd=0;
			dfs(i,0);
			if(pd)return 0;
			ans++;
		}
	return 1<<ans;
}
signed main()
{
	n=read();m=read();
	if(m==0){cout<<0;return 0;}
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		mp[x][y]=mp[y][x]=1;
	}
	int ans=1ll*(1ll<<n)-2*mei0()-mei1()+2*mei01()+mei02();
	cout<<ans;
	return 0;
}
/*
容斥，总方案-没有0-没有1-没有2+没有01+没有02+没有12-没有012 
整理一下，总方案-2*没有0-没有1+2*没有01（只有2）+没有02（只有1）
想一想：没有0和没有2是不是一样的 
总方案:2^n
没有0:对于一条边A-B,A=0那么B=1,分成两半，一半枚举选法，一半子集dp求出方案。
没有1:每个联通块全0或全1，dfs即可
没有01（只有2）:对于没边的点能选01，其他全1
没有02（只有1）: 2^(联通块个数) 
*/
```

---

## 作者：未来姚班zyl (赞：2)

## 题目大意

给定一张无向图，你需要给每个点写上数字 $0$ 或 $1$。满足：

1. 至少有一条边满足其连接的两个点都是 $1$。
2. 至少有一条边满足其连接的两个点有且仅有一个 $1$。
3. 至少有一条边满足其连接的两个点都是 $0$。

## 题目分析

这一类限制数量很少，但拼在一起很难计数的题，可以考虑容斥计数。

- 钦定不满足 $1$ 条件

则条边至少有一个 $0$，这是点覆盖计数问题，可以采用经典算法：每次枚举度数最大的点是否选 $0$，如果选了，则点数减少 $deg$，否则点数减少 $1$。当所有点的度数均 $\le 2$ 时，图只由链和环组成，可以直接 dp 预处理。

钦定不满足 $3$ 条件与其对称，所以方案数一样。

- 钦定不满足 $2$ 条件

则每条边连接的点取值一样，答案就是 $2^{cnt}$，$cnt$ 是连通块个数。

- 钦定不满足 $12$ 条件

有边的连通块只能选 $0$，独立点两种都可以选。

钦定不满足 $23$ 与之对称，方案数一样。

- 钦定不满足 $13$ 条件

则相当于二分图染色，如果图不是二分图方案数就是 $0$，否则就是 $2^{cnt}$。

最后按照容斥原理加减即可，复杂度在求点覆盖方案数的部分，使用位运算可以将一些 $O(m)$ 的部分化为 $O(n)$，在 $n\le 40$ 时跑得飞快。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,ln
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=5e1+10,M=3e3+5,inf=(1LL<<31)-1,mod=1e9+7;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,m,h[N],to[M],nxt[M],cnt,testid;
inline void add_(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
}

inline void clear(){
	repn(i)h[i]=0;
	cnt=0;
}
ll dp[N][2],F[N],G[N];
map<ll,ll>P;
map<ll,int>Id;
inline bool ck(ll s,int x){
	return (s>>x-1)&1;
}
ll sta[55];
bool v[55];
inline void dfs(int x,ll s,int &V,bool &c){
	v[x]=1;
	ll nx=s&sta[x];
	int deg=__builtin_popcountll(nx),y;
	V++,c|=deg<=1;
	if(!deg)return;
	if(deg==1){
		y=Id[nx];
		if(!v[y])dfs(y,s,V,c);
	}else{
		y=Id[nx&-nx];
		if(!v[y])dfs(y,s,V,c);
		nx-=nx&-nx;
		y=Id[nx];
		if(!v[y])dfs(y,s,V,c);
	}
}
inline ll calc(ll s){
	if(P.find(s)!=P.end())return P[s];
	P[s]=0;
	ll &ans=P[s];
	int deg;
	repn(x)if(ck(s,x)){
		ll Nw=s&sta[x];
		deg=__builtin_popcountll(Nw);
		if(deg<=2)continue;
		return ans=calc(s^(1LL<<x-1))+calc(s^(1LL<<x-1)^Nw);
	}
	repn(i)v[i]=0;
	ans=1;
	repn(x)if(ck(s,x)&&!v[x]){
		int V=0;
		bool fc=0;
		dfs(x,s,V,fc);
		if(fc)ans*=F[V];
		else ans*=G[V];
	}
	return ans;
}
inline void solve(int n){
	if(n<=2)return F[n]=n+1,void();
	dp[1][0]=dp[1][1]=1;
	rep(i,2,n)dp[i][0]=dp[i-1][1],dp[i][1]=dp[i-1][0]+dp[i-1][1];
	F[n]=dp[n][0]+dp[n][1];
	dp[1][0]=0,dp[1][1]=1;
	rep(i,2,n)dp[i][0]=dp[i-1][1],dp[i][1]=dp[i-1][0]+dp[i-1][1];
	G[n]=dp[n][0]+dp[n][1];
	dp[1][0]=1,dp[1][1]=0;
	rep(i,2,n)dp[i][0]=dp[i-1][1],dp[i][1]=dp[i-1][0]+dp[i-1][1];
	G[n]+=dp[n][1];
}
inline void prep(){
	rep(i,1,50)solve(i);
	ll nw=1;
	int i=1;
	while(i<=50)Id[nw]=i,i++,nw*=2LL;
}
int col[N];
inline void dfs_(int x,bool &f,bool &ff){
	e(x){
		if(col[y]){
			if(col[y]==col[x])f=0;
		}else ff=1,col[y]=3-col[x],dfs_(y,f,ff);
	}
}
inline void subtaskall(){
	if(m<=2)return puts("0"),void();
	P.clear();
	repn(x){
		sta[x]=0;
		e(x)sta[x]|=1LL<<y-1;
	}
	repn(i)col[i]=0;
	int Cnt=0,Ct=0;
	bool ff=1,fff=0;
	repn(i)if(!col[i])fff=0,Cnt++,col[i]=1,dfs_(i,ff,fff),Ct+=fff;
	ll K0=calc((1LL<<n)-1),K1=1LL<<Cnt,K2=K0,K01=1LL<<Cnt-Ct,K12=K01,K02=0;
	if(ff)K02=K1;
	cout <<(1LL<<n)-K0-K1-K2+K01+K02+K12<<'\n';

}
inline void Main(){
    n=read(),m=read();
	repm(i){
		int x=read(),y=read();
		add_(x,y),add_(y,x);
	}
	return subtaskall(),clear(),void();
}
signed main(){
	prep();
	int T=1;
	while(T--)Main();
	return 0;
}
```

---

## 作者：ran_qwq (赞：2)

meet-in-the-middle 好题。

题目的限制放在一起很复杂，我们容斥分开考虑。具体地，设

- $A$ 为没有边值为 $0$ 的方案数。
- $B$ 为没有边值为 $1$ 的方案数。
- $C$ 为没有边值为 $2$ 的方案数。
- $D$ 为没有边值为 $0$ 或 $1$ 的方案数。
- $E$ 为没有边值为 $0$ 或 $2$ 的方案数。
- $F$ 为没有边值为 $1$ 或 $2$ 的方案数。
- $G$ 为没有边值为 $0$ 或 $1$ 或 $2$ 的方案数。

$A$ 较难考虑，先考虑其他的。

$B$ 就是每个连通块点值相同，$B=2^\text{连通块个数}$。

$C=A$，把图的点值反转形成双射。

$D$ 就是所有连上边的点都是 $1$，$D=2^\text{孤立点个数}$。

$E$ 就是连边两点值不同，如果是二分图 $E=2^{连通块个数}$，否则 $E=0$。

$F=D$，把图的点值反转形成双射。

$G$ 就是不能有边，如果 $m=0$，$G=2^n$，否则 $G=0$。

答案为 $2^n-A-B-C+D+E+F-G$，$B\sim G$ 可以在图上 dfs 轻松解决，这里不赘述。

下面计算 $A$（称点值为 $1$ 为该点被选），独立集计数是 NP，考虑 meet-in-the-middle。

我们发现，把图分两半，限制分为左半边内部的限制，右半边内部的限制，左右半边之间的限制三类。

枚举左半边，对一条左右半边之间的连边 $(u,v)$（前者在左），如果 $u$ 被选，则 $v$ 不能选。最后右半边形如有些点不能选，有些点可选可不选。即右半边选点的集合是一个子集，对这个子集加 $1$。

枚举左半边时在可选集合的位置加 $1$，统计答案时做一遍高维后缀和。

时间复杂度 $O(2^{\frac n2}n)$。

```cpp
int n,m,k,u,cnt,fg,vis[N],U[N*N],V[N*N]; ll ans,st[N],sm[1<<K];
void QwQ() {
	n=rd(),m=rd(),k=n>>1,u=(1<<n-k)-1,ans=1ll<<n,cnt=0,fg=1,mst(st,0),mst(vis,0),memset(sm,0,u+1<<3);
	for(int i=1,u,v;i<=m;i++) u=U[i]=rd()-1,v=V[i]=rd()-1,st[u]|=1ll<<v,st[v]|=1ll<<u;
	auto chk1=[&](int s) {
		for(int i=0;i<k;i++) if((s>>i&1)&&(s&st[i])) return 0;
		return 1;
	};
	auto chk2=[&](int s) {
		for(int i=k;i<n;i++) if((s>>i-k&1)&&(s&(st[i]>>k))) return 0;
		return 1;
	};
	for(int s=0;s<1<<k;s++) if(chk1(s)) {
		int t=u;
		for(int i=0;i<k;i++) if(s>>i&1) t&=u^(st[i]>>k);
		sm[t]++;
	};
	for(int i=0;i<n-k;i++) for(int s=u;~s;s--)
		if(!(s>>i&1)) sm[s]+=sm[s^1<<i];
	for(int s=0;s<=u;s++) if(chk2(s)) ans-=sm[s]<<1;
	auto dfs1=[&](auto &&dfs1,int u)->void {
		vis[u]=1;
		for(int v=0;v<n;v++) if((st[u]>>v&1)&&!vis[v]) dfs1(dfs1,v);
	};
	for(int u=0;u<n;u++) if(!vis[u]) cnt++,dfs1(dfs1,u);
	ans-=1ll<<cnt,mst(vis,0);
	auto dfs2=[&](auto &&dfs2,int u,int c)->void {
		vis[u]=c;
		for(int v=0;v<n&&fg;v++) if(st[u]>>v&1)
			if(!vis[v]) dfs2(dfs2,v,3-c);
			else if(vis[u]==vis[v]) return fg=0,void();
	};
	for(int u=0;u<n;u++) if(!vis[u]) dfs2(dfs2,u,1);
	ans+=fg?1ll<<cnt:0,mst(vis,0);
	for(int i=1;i<=m;i++) vis[U[i]]=vis[V[i]]=1;
	wrll(ans+=(1ll<<count(vis,vis+n,0)+1)-(!m?1ll<<n:0),"\n");
}
```

---

## 作者：Fish_ht (赞：2)

## Upd 2024.8.29: 修改了关于双向搜索的部分题解

这是一道双向搜索神题，~~我太菜了~~连题解里面的双向搜索合并的部分~~都没看懂~~，所以就有了这篇题解。

## 题意

给出一个 $n$ 个点 $m$ 条边的图，一个点的点权为 $0$ 或 $1$， 定义一条边的边权为两端点权和。

求至少一条边权为 $0$ 的边，至少一条边权为 $1$ 的边，至少一条边权为 $2$ 的边的方案数。

$1 \leq n \leq 40$

## 思路

题目中要求三个边权都至少出现一次的方案数，但直接去维护显然不可做。

不妨另辟蹊径，令 $f(S)$ 表示边权的值域为 $S$ 的方案数。

则根据容斥原理有 $ans=f({0,1,2}) - f({0,1})-f({1,2})-f({0,2})+f({1})+f({0})+f({2})$。

显然有 $f({0,1,2})=2^n$。

对于 $f({0})/f({2})$，孤立点任取，其他必须取 $0/1$。
记 $cnt$ 为孤立点数量，则 $f({0})/f({2})=2^{cnt}$。

对于 $f({0,2})$ 两端点权相同即每个连通块点权相同，则又记 $tot$ 为连通块数量，$f({0,2})=2^{tot}$。

对于 $f({1})$ 每条边两端一定是 $0$ 与 $1$，则如果每个连通块都是二分图 $f({1})=2^{tot}$，不然 $f({1})=0$。

又对于 $f({0,1}),f({1,2})$，实际上只需考虑一个 (点权取反后相同)。

而计算 $f({0,1})$ 考虑折半搜索。

我们先对一个点的权值讨论。

若其权值为 $0$ 相邻的点可以随便取。

若其权值为 $1$ 相邻的点只能取 $0$。

双向搜索，将图分成两半。

左半部分按上面讲的对于每一个状态判断合法。

一个状态是否合法我们可以用 $V_s$ 记录。

对于合法的右半段，可以考虑拼起来。对于右半权值为 $0$，显然左半的可以任取权值。若右半是 $1$，左半只能是 $0$。

记一个二进制状态 $s$ 所表示的值为 $p_s$。

我们可以先找到一个 $p_s$ **最大**的左部的一个状态 (对于右部的状态而言是合法的) $s$， 再去更新答案。

则 $s$ 对答案的贡献为 $\sum_{t\in s} V_t$。

因为 $p_s$ **最大**说明了此时左部状态 $t$ 的 $p_t$ 取值范围为 $[0,p_s]$ 即 $s$ 的子集 $q$ 的 $p_q$ 的取值范围，又因为还要判断是否合法所以对答案的贡献是 $\sum_{t\in s} V_t$。

补充：由于右部取 $1$ 只能是 $0$，而取 $0$ 可以是任意的，所以 $s$ 的子集一定满足对于右部合法 (是 $0$ 的就是 $0$，是 $1$ 的可以不取就是 $0$)。

可以看下图理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/30aixyiv.png)

### 修正上图：是合法状态构成的集合的子集。

令左半部分点数为 $G$。

则 $G$ 取 $17$ 时可以卡过。

实现的时候注意是**每个连通块都是二分图**。

其他地方代码里有注释可以看下。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 7;
int n, m, f[51], sz[52], cnt = 0, tot = 0;
// f并查集
// sz维护连通块大小
ll res = 0;
int color[N], ln = 0, rn = 0; // ln左部点数,rn右部
ll sum[2000007];
bool vis[2000007]; // 题解中的V
bool v[57][57]; // 邻接矩阵
vector<int> e[N << 1];
// cnt孤立点,tot连通块
inline void add(const int u, const int vv)
{
    e[u].push_back(vv);
    v[u][vv] = 1;
    return;
}
inline int find(int x)
{
    if (x != f[x])
        return f[x] = find(f[x]);
    return x;
}
inline bool dfs(int x, int cl)
{ // 染色法
    color[x] = cl;
    for (auto v : e[x]) {
        if (!color[v]) {
            bool tmp = dfs(v, -cl);
            if (!tmp)
                return false;
        } else if (color[x] == color[v])
            return false;
    }
    return true;
}
// 这里以求f(0,1)为例
inline bool check_l(int S)
{ // S是二进制压缩后的状态
    for (int i = 1; i <= ln; i++) {
        if (!(S & (1ll << i - 1)))
            continue;
        for (int j = i + 1; j <= ln; j++) {
            if (!(S & (1ll << j - 1)))
                continue;
            if (v[i][j])
                return false; // 存在2矛盾
        }
    }
    return true;
}
inline bool check_r(int S)
{ // 同上
    for (int i = 1; i <= rn; i++) {
        if (!(S & (1 << i - 1)))
            continue;
        for (int j = i + 1; j <= rn; j++) {
            if (!(S & (1 << j - 1)))
                continue;
            if (v[i + ln][j + ln])
                return false;
        }
    }
    return true;
}
inline int solve(int S)
{
    int sum = (1ll << ln) - 1;
    for (int i = 1; i <= rn; i++) {
        if (!(S & (1 << i - 1)))
            continue;
        for (int j = 1; j <= ln; j++) {
            if (!v[i + ln][j])
                continue;
            if (sum & (1 << j - 1))
                sum ^= (1ll << j - 1); // 调整
        }
    }
    return sum;
}
signed main()
{
    cin >> n >> m;
    if (m <= 2) { // 特判
        puts("0");
        return 0;
    }
    for (int i = 1; i <= n; i++)
        f[i] = i, sz[i] = 1;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        add(x, y);
        add(y, x);
        int u = find(x), v = find(y);
        if (u == v)
            continue;
        f[u] = v;
        sz[v] += sz[u];
    }
    res = (1ll << n); // f(0,1,2)
    for (int i = 1; i <= n; i++) {
        if (f[i] == i)
            tot++;
        if (f[i] == i && sz[i] == 1)
            cnt++;
    }
    ll p = (1ll << tot);
    for (int i = 1; i <= n; i++) {
        if (f[i] == i) {
            if (!dfs(i, 1)) {
                p = 0;
                break;
            }
        }
    }
    res += p; // f(1)
    res += (1ll << cnt); // f(2)
    res += (1ll << cnt); // f(3)
    res -= (1ll << tot); // f(0,2)
    ln = n / 2;
    if (ln > 17)
        ln = 17; // 取17可过
    rn = n - ln;
    const ll Ls = (1ll << ln);
    const ll Rs = (1ll << rn);
    // 不用dfs,递归函数常数太大（亲测过不了）
    for (int i = 0; i < Ls; i++)
        vis[i] = check_l(i); // V预处理
    for (int i = 0; i < Ls; i++) {
        sum[i] = 1;
        for (int j = i; j; j = (j - 1) & i)
            sum[i] += vis[j]; // 枚举子集,类似前缀和
    }
    for (int i = 0; i < Rs; i++)
        if (check_r(i))
            res -= 2ll * sum[solve(i)]; // f(0,1)+f(1,2),子集的Vs和
    cout << res << "\n";
}
```

## 参考资料

[2018ljw 的题解](https://www.luogu.com.cn/article/5v6v5wbn)

[老师](https://www.luogu.com.cn/user/20360)上课讲的大概思路。

代码参考了 2018ljw 的题解的代码写法，另外写了一些自己的想法，组织自己的语言，就构成了这篇题解。

## 总结

总体来说是一道比较好的思维 + 双向搜索题，尤其是双向搜索部分，很难想到想通为什么是子集的和，以及一些判断合法，调整状态的细节。

---

## 作者：Albert_van (赞：2)

特判 $m=0$。然后考虑做一个容斥。令 $F(E)\;(E\subseteq\{0,1,2\})$ 表示边权集合 $\subseteq E$（没有不在 $E$ 内的数字）的方案数。那么答案为

$$F(\{0,1,2\})-F(\{0,1\})-F(\{1,2\})-F(\{0,2\})+F(\{0\})+F(\{1\})+F(\{2\})$$

对原图求孤点（所在连通块大小为 $1$）个数 $c$ 与连通块个数 $k$（另一种做法是把孤点全部删掉再处理），显然有：

- $F(\{0,1,2\})=2^n$。
- $F(\{0\})=F(\{2\})=2^c$。这等价于，对于大小 $>1$ 的所有连通块包含的点，它们的点权必须全为 $0$，或者全为 $1$。
- $F(\{0,2\})=2^k$。每个连通块要么全为 $0$，要么全为 $1$。

以及：

- 若原图不是二分图，那么 $F(\{1\})=0$。对于每条边，它两端点的点权必须恰为 $1$ 和 $0$。这就是黑白染色，也就是二分图的模型。
- 否则，$F(\{1\})=2^k$。每个连通块有两种染色方案。

现在还剩下 $F(\{0,1\})$ 和 $F(\{1,2\})$。它们意即，原图中没有相邻的 $1$，或是没有相邻的 $0$。那么有 $F(\{0,1\})=F(\{1,2\})$。

问题等价于，在原图中选出一个独立集，求方案数。

$n=40$，且考场有 $n=20$ 的包，启发我们折半搜索。取阈值 $B$，对编号 $\le B$ 的结点，枚举选择它们的所有合法方案 $S$，记 $S$ 中所有点的邻接点集为 $A$，那么编号 $>B$ 的结点，可选择的范围就是 $T=\large \complement_{[1,n]}A$。即，编号 $>B$ 结点选择的合法方案，一定是 $T$ 的子集。

这是一个明显的 SOS（Sum Over Subsets）计数。使用 FWT 等技巧可以在 $\mathcal O(2^{n-B})$ 内完成。可我只会 $\Theta(3^{n-B})$ 对每种可能的 $T\subseteq (B,n]$ 暴力枚举子集啊。分析复杂度：

$$\Theta(2^B+3^{n-B})$$

令 $2^B=3^{n-B}$，解得 $B=n\times \log_6 3$。那么总复杂度就是 $\Theta(2^B)$。$n=40$ 时 $B\approx 24.525$，取 $B=24$。完全不卡。

精细实现（预处理 $A$ 等）可以让搜索过程的复杂度完全不带 $n$ 或 $m$。

```cpp
#include <cstdio>
#include <cmath>
#define ll long long

double log2(double x){
	return log(x)/log(2);
}

const int N=114514;

int F,S,A,B,adj[50],sad[50];

ll sos[N],ans;

void whl(int now){
	if(now>B) return ans+=sos[F^S],void();
	if(!(A&adj[now])){
		int ps=S,pa=A;S|=sad[now];A|=(1<<now-1);
		whl(now+1);S=ps;A=pa;
	}
	whl(now+1);
}

int n;bool bass[N];

void pre(int now){
	if(now>n-B) return bass[A]=1,void();
	if(!(A&adj[now])) A|=(1<<now-1),pre(now+1),A^=(1<<now-1);
	pre(now+1);
}

void sum(int now){
	if(now>n-B) return sos[S]+=bass[A],void();
	if(S&(1<<now-1)) A|=(1<<now-1),sum(now+1),A^=(1<<now-1);
	sum(now+1);
}

int G[50][50];

ll NoAdj(){
	B=n*log2(3)/log2(6);
	for(int i=0;i<n-B;++i) F|=(1<<i);
	for(int i=1;i<=n-B;++i) for(int j=1;j<=n-B;++j) adj[i]|=(G[i+B][j+B]<<(j-1));
	pre(1);for(S=0;S<(1<<n-B);++S) sum(1);
	for(int i=1;i<=B;++i){
		adj[i]=0;for(int j=1;j<=B;++j) adj[i]|=(G[i][j]<<(j-1));
	}
	for(int i=1;i<=B;++i) for(int j=B+1;j<=n;++j) sad[i]|=(G[i][j]<<(j-B-1));
	S=0;whl(1);return ans;
}

int co[50];bool flg;

void chkBin(int now,int c){
	if(co[now]){
		flg|=(co[now]!=c);return ;
	}
	co[now]=c;for(int i=1;i<=n;++i) if(G[now][i]) chkBin(i,((c-1)^1)+1);
}

int blk;

ll Ol1(){
	for(int i=1;i<=n;++i) if(!co[i]) chkBin(i,1),++blk;
	if(flg) return 0;
	else return 1ll<<blk;
}

int main()
{
	int m,x,y,isc=0;scanf("%d%d",&n,&m);
	while(m--) scanf("%d%d",&x,&y),G[x][y]=G[y][x]=1;
	for(int i=1;i<=n;++i){
		bool flg=0;for(int j=1;j<=n;++j) flg|=G[i][j];
		isc+=!flg;
	}
	printf("%lld",(1ll<<n)-2*NoAdj()+Ol1()-(1ll<<blk)+2*(1ll<<isc));
}
```



---

## 作者：RainySoul (赞：1)

*从巨佬 ydq 那里学到的神奇做法。爆搜，应该是目前为止最简单易懂的做法。*

### 思路

直接计算合法情况是困难的，考虑容斥。

用 $\{01\}$ 表示只存在边权为 $0$ 和 $1$ 的边时的方案数，其他以此类推。

那么合法方案数就是：

$\{012\}-\{01\}-\{12\}-\{02\}+\{0\}+\{1\}+\{2\}$

来看下这个式子的每一项的贡献都是啥。

设总点数为 $n$，孤立点个数为 $cnt1$，连通块个数为 $cnt2$。

> $\{012\}$：随意给每个点填 $0$ 或 $1$ 都是合法的，方案数是 $2^{n}$。

> $\{0\}$ 和 $\{2\}$：除了孤立点，其他点都是被限制死的，而孤立点可以随便填。这两个的方案数都是 $2^{cnt1}$。

> $\{02\}$：相当于每个连通块内必须全部填 $0$ 或全填 $1$，方案数是 $2^{cnt2}$。

> $\{1\}$：每条边连接的两个点都必须一个填 $1$，另一个填 $0$。相当于把一个图黑白染色，如果存在合法方案，你把一个连通块里面的 $0$ 和 $1$ 全部翻转可以得到另一种合法方案，所以方案数就是 $2^{cnt2}$；如果不存在合法方案它的贡献就是 $0$ 啦。

最后还剩下 $\{01\}$ 和 $\{12\}$ 两种没有计算。这两个可以转化成**独立集计数**问题。拿 $\{01\}$ 举例子，通俗地来讲就是如果一个点填了 $1$，那么它的所有邻居中的点都不能填 $1$ 了。而 $\{12\}$ 的方案可以由 $\{01\}$ 的方案中的 $0$ 和 $1$ 全部翻转得到，答案同 $\{01\}$。

本题重点来了，这个要怎么求呢？

你考虑一个最暴力的爆搜，每个连通块分别计算独立集个数，相乘得到答案。对于一个连通块，每次取出一个点，枚举这个点是填 $0$ 还是填 $1$。

填 $0$：拿走当前点。删去当前点的所有连边。

填 $1$：拿走当前点和它的邻居。删去当前点的所有连边，并删去其邻居的所有连边。这是因为你这个点填 $1$ 了，邻居就必须填 $0$，没有选择了对吧。

如果你每次按照编号取点，这样不用看，肯定是超时的，而且很可能还会因为编号顺序算错答案。

你考虑每次取出当前还未被操作过的**度数最大的点**进行操作。然后你发现如果度数最大的点度数都为 $0$ 了，剩下的点你没有再去做的必要了，所有的没有操作过的点都是可以任意填 $0$ 或 $1$ 的。

然后你发现每次操作，因为你选的就是度数最大的点，可以使其他点的度数飞速下降。时间复杂度比较不好计算，期望执行次数的递归式是 $f(n)=f(n-1)+f(n-degree)$ 的样子（其中 $degree$ 是当前点的度数），可以通过此题。

本地测了下 $n=50$ 时的极限数据，$0.004$ 秒就出了，跑得还挺快。

#### 一些细节

记得特判下 $m=0$ 的情况，明显是没有满足的方案的，输出 $0$。

要开 `long long`。

AC code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100;
int degree[N],cnt,n,m,ans,tans,vis[N],pw[N],cnt1,cnt2;
vector<int> e[N],kuai[N];
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();		
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
void dfs(int num){
    int maxn=0,now=0;
    for(int i=0;i<(int)kuai[num].size();i++){
        int loc=kuai[num][i];
        if(!vis[loc])
            if(degree[loc]>maxn)maxn=degree[loc],now=loc;
    }
    if(maxn==0){
        int cnt1=0;
        for(int i=0;i<(int)kuai[num].size();i++){
            int loc=kuai[num][i];
            if(degree[loc]==0&&vis[loc]==0)cnt1++;
        }
        tans+=pw[cnt1];
        return;
    }
    vis[now]=1;
    vector<int> v;
    v.clear();
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i];
        if(!vis[to]){
            degree[to]--;
            v.push_back(to);
        }
    }
    dfs(num);//这一个点染白
    vector<int> v2;
    v2.clear();
    for(int i=0;i<(int)v.size();i++){
        vis[v[i]]=1;
        for(int j=0;j<(int)e[v[i]].size();j++){
            int to=e[v[i]][j];
            if(!vis[to]){
                degree[to]--;
                v2.push_back(to);
            }
        }
    }
    dfs(num);//染黑
    for(int i=0;i<(int)v.size();i++)vis[v[i]]=0,degree[v[i]]++;
    for(int i=0;i<(int)v2.size();i++)degree[v2[i]]++;
    vis[now]=0;
    //回溯
}
void dfs1(int num,int now){//判连通块
    kuai[num].push_back(now);
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i];
        if(!vis[to]){
            vis[to]=1;
            dfs1(num,to);
        }
    }
}
int flag[N],temp;
void dfs2(int now){//对于一个连通块黑白染色
    if(temp==1)return;
    int f1=0,f2=0;
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i];
        if(flag[to]==1)f1=1;
        else if(flag[to]==2)f2=1;
    }
    if(f1&&f2){
        temp=1;
        return;
    }
    if(f2)flag[now]=1;
    else flag[now]=2;
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i];
        if(flag[to]==0)dfs2(to);
    }
}
bool check(){//看能否黑白染色
    memset(flag,0,sizeof flag);
    for(int i=1;i<=n;i++)
        if(!flag[i])dfs2(i);
    if(temp==1)return 0;
    return 1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
    pw[0]=1;
    for(int i=1;i<=N-10;i++)pw[i]=pw[i-1]*2;//预处理 2^i
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        e[u].push_back(v);
        e[v].push_back(u);
        degree[u]++;degree[v]++;
    }
    if(m==0){//别忘了特判
        cout<<"0\n";
        return 0;
    }
    int cnt1=0,cnt2=0;//cnt1为孤立点个数，cnt2为连通块个数
    for(int i=1;i<=n;i++)
        if(degree[i]==0)cnt1++;//计算 {0} 和 {2} 的情况
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            vis[i]=1;
            cnt2++;
            dfs1(cnt2,i);//计算 {1} 和 {0,2} 的情况
        }
    }
    memset(vis,0,sizeof vis);
    ans=1;
    for(int i=1;i<=cnt2;i++){
        tans=0;
        dfs(i);//计算 {0,1} 和 {1,2} 的情况
        ans*=tans;
    }
    //{0,1,2}-{0,2}-{0,1}-{1,2}+{0}+{2}(+{1})
    if(check())cout<<pw[n]-ans*2+pw[cnt1]*2<<'\n';//这里是 {0,2} 和 {1} 的抵消掉了
    else cout<<pw[n]-pw[cnt2]-ans*2+pw[cnt1]*2<<'\n';
	return 0;
} 
```

另：如果你担心只直接计算最大度数为 $0$ 时的方案会超时，你也可以尝试把最大度数为 $0,1,2$ 时的方案全部直接计算了，并不是特别困难。对时间复杂度的优化相当之大，可以吊打标算。

---

## 作者：沉石鱼惊旋 (赞：1)

# 题目翻译

给定 $n$ 个点 $m$ 条边的图，定义边权为边连接的端点点权之和。你可以为点权赋值 $0$ 或 $1$，求**同时**存在至少一条边权为 $0$ 的边，存在至少一条边权为 $1$ 的边，存在至少一条边权为 $2$ 的边的方案数。

$1\leq n\leq 40$，$0\leq m\leq \dfrac{n(n-1)}{2}$。

# 题目思路

$m=0$ 显然答案为 $0$，是个 corner case 要判掉。

考虑先把答案容斥出来。设 $S_{\{k\}}$ 表示**可以**包含为 $k$ 的边权的方案数。$ans=S_{\{0,1,2\}}-S_{\{0,1\}}-S_{\{0,2\}}-S_{\{1,2\}}+S_{\{0\}}+S_{\{1\}}+S_{\{2\}}-S_{\emptyset}$。

由于已经判掉了 $m=0$ 所以 $S_{\emptyset}=0$。

不难发现 $S_{\{0,1,2\}}=2^n$ 也就是每个点任意选的方案。

接下来处理 $S_{\{0,1\}},S_{\{0,2\}},S_{\{1,2\}},S_{\{0\}},S_{\{1\}},S_{\{2\}}$。

不难发现 $S_{\{0,1\}}$ 与 $S_{\{1,2\}}$ 等价，而 $S_{\{0\}}$ 与 $S_{\{2\}}$ 也等价。

我们只需要算出 $S_{\{0,1\}},S_{\{0,2\}},S_{\{0\}},S_{\{1\}}$ 即可。

$S_{\{0\}}$ 孤点可以随便选，而 $size\gt 1$ 的联通块必须全选 $0$。也就是设 $x$ 为孤点数量，则 $S_{\{0\}}=2^x$。$x$ 可以并查集求出。

$S_{\{1\}}$ 那相邻点点权不同，不难联想到二分图。这等价于对原图做二分图染色的方案数。由于原图不一定联通，若会分成 $y$ 个联通块。如果 $y$ 个联通块都是二分图，则 $S_{\{1\}}=2^y$，否则 $S_{\{1\}}=0$，这可以直接跑二分图染色进行判定。

$S_{\{0,2\}}$ 那么每个联通块要么是全 $0$ 要么是全 $1$。设 $z$ 为原图联通块个数，则 $S_{\{0,2\}}=2^z$。这也可以并查集得到 $z$。

$S_{\{0,1\}}$ 就是原图的独立集个数。考虑若点权为 $1$ 看做是独立集中的点，点权为 $0$ 表示不是。不难发现这恰好满足了点权为 $1$ 的点不能相邻。

一般图独立集计数是困难的。但是数据范围启发我们折半搜索。

设 $h=\lceil\dfrac{n}{2}\rceil$。我们 $\mathcal O(2^{n/2})$ 枚举 $[1,h]$ 的点是否在独立集中，并且 $\mathcal O(n^2)$ 判掉是否存在边 $(x,y)$ 满足 $x,y\in [1,h]$ 且 $x,y$ 都在独立集中。

同理 $[h+1,n]$ 也可以这样算出来。

之后枚举 $[1,h]$ 的合法状态。我们根据这个合法状态，能够得到若干条限制。每条限制形如：$[h+1,n]$ 中的点 $x$ 不可以出现在独立集中。

我们对限制取补集，那么这个补集的所有子集，都是合法的可以构成独立集的。对于 $[h+1,n]$ 的状态做高维前缀和即可。

时间复杂度瓶颈在计算 $S_{\{0,1\}}$ 上。复杂度为 $\mathcal O(2^{n/2} n^2)$。其余别的都是线性或者带一个并查集的 $\alpha(n)$。

# 完整代码

[CF submission 283754107](https://codeforces.com/problemset/submission/1221/283754107)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int fa[40];
int sz[40];
int tot, o;
int F(int u) { return fa[u] ^ u ? fa[u] = F(fa[u]) : u; }
void U(int u, int v)
{
    u = F(u), v = F(v);
    if (u == v)
        return;
    sz[v] += sz[u];
    sz[u] = 0;
    fa[u] = v;
}
int n, m;
int hf;
bool e[40][40];
ll f[1 << 20];
ll g[1 << 20];
ll calc_any() { return 1LL << n; }
ll calc_01()
{
    ll ans = 0;
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    for (int mask = 0; mask < 1 << hf; mask++)
    {
        bool ok = 1;
        for (int x = 0; x < hf; x++)
        {
            for (int y = 0; y < hf; y++)
            {
                if (!e[x][y])
                    continue;
                if ((mask >> x & 1) && (mask >> y & 1))
                {
                    ok = 0;
                    break;
                }
            }
            if (!ok)
                break;
        }
        f[mask] = ok;
    }
    for (int mask = 0; mask < 1 << n - hf; mask++)
    {
        bool ok = 1;
        for (int x = hf; x < n; x++)
        {
            for (int y = hf; y < n; y++)
            {
                if (!e[x][y])
                    continue;
                if ((mask >> x - hf & 1) && (mask >> y - hf & 1))
                {
                    ok = 0;
                    break;
                }
            }
            if (!ok)
                break;
        }
        g[mask] = ok;
    }
    for (int i = 0; i < n - hf; i++)
    {
        for (int mask = 0; mask < 1 << n - hf; mask++)
        {
            if (mask >> i & 1)
                g[mask] += g[mask ^ (1 << i)];
        }
    }
    const int full = (1 << n - hf) - 1;
    for (int maskX = 0; maskX < 1 << hf; maskX++)
    {
        if (!f[maskX])
            continue;
        int maskY = 0;
        bool ok = 1;
        for (int x = 0; x < hf; x++)
        {
            for (int y = hf; y < n; y++)
            {
                if (!e[x][y])
                    continue;
                if (maskX >> x & 1)
                    maskY |= 1 << y - hf;
            }
        }
        ans += f[maskX] * g[full ^ maskY];
    }
    return ans;
}
ll calc_02() { return 1LL << tot; }
ll calc_12() { return calc_01(); }
ll calc_0() { return 1LL << o; }
ll calc_1()
{
    ll ans = 1;
    vector<int> col(n, -1);
    auto dfs = [&](auto self, int u, int c) -> void
    {
        col[u] = c;
        for (int v = 0; v < n; v++)
        {
            if (!e[u][v])
                continue;
            if (~col[v])
            {
                if (col[v] == c)
                    ans = 0;
                continue;
            }
            self(self, v, c ^ 1);
        }
    };
    for (int i = 0; i < n; i++)
    {
        if (~col[i])
            continue;
        dfs(dfs, i, 0);
        ans <<= 1;
    }
    return ans;
}
ll calc_2() { return calc_0(); }
ll calc_none() { return 0; }
int main()
{
    cin >> n >> m;
    hf = n + 1 >> 1;
    if (!m)
        return cout << 0 << endl, 0;
    for (int i = 0; i < n; i++)
        fa[i] = i, sz[i] = 1;
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        x--, y--;
        U(x, y);
        e[x][y] = e[y][x] = 1;
    }
    for (int i = 0; i < n; i++)
    {
        if (F(i) == i)
            tot++, o += sz[i] == 1;
    }
    // cout << calc_any() << endl
    //      << calc_01() << endl
    //      << calc_02() << endl
    //      << calc_12() << endl
    //      << calc_0() << endl
    //      << calc_1() << endl
    //      << calc_2() << endl
    //      << calc_none() << endl;

    cout << calc_any() - calc_01() - calc_02() - calc_12() + calc_0() + calc_1() + calc_2() - calc_none() << endl;
    return 0;
}
/*
任意 - 有 01 - 有 02 - 有 12 + 有 0 + 有 1 + 有 2 - 都没有

任意 2 ^ n

有 01 == 有 12
有 0 == 有 2

有 02
有 1

都没有 2 ^ n

corner: m == 0
*/
```

---

## 作者：SnowTrace (赞：1)

相当简单的一个题，比较大的难点可能是一个 corner case.

至少分别有一条边权值为 $0,1,2$，这个形式我们肯定要用容斥做，也就是钦定这里面只有某几种数或者没有限制，然后乘上一个系数。

这题的式子可以表示为下：

$ans = |S_{0,1,2}|-|S_{0,1}|-|S_{1,2}|-|S_{0,2}|+|S_{0}|+|S_{1}|+|S_{2}|-|S_{空}|$

$S$ 的下标代表的是哪些数是可以出现的。

我们接下来逐一讲解如何计算。

---
$S_{0,1,2} = 2^n$，每个点都可以随便赋值。

$S_{0,2} = 2^p$，$p$ 是联通块个数。

注意到只能有 $0,2$ 意味着如果要染一个联通块中的点那么这个联通块中的其他点都需要被染色。

---

$S_{0,1} = S_{1,2} = cnt$，其中 $cnt$ 表示图的独立集个数，这是本题的难点。

先证明 $S_{0,1} = S_{1,2}$，注意到把这个图所有点颜色取反就能把所有的 $0,1$ 变成 $1,2$。

而每条边大小最多为 $1$ 等价于两个处于同一条边上的点不能同时选，也就是独立集。

数据范围启示我们做折半搜索。

具体的我们可以先跑出前一半的点中能被选作独立集的集合，再跑出后一半点中能被选作独立集的点，然后我们枚举前一半点的集合，前半部分对后半部分的限制一定是后半部分代表的集合必须是某个集合 $T$ 的子集（实际上也就是说和前半部分相邻的点不能出现在后半部分），于是这件事情就相当于你要求 $\sum_{i\in T}[ok_i]$，我们可以用高维前缀和完成。这部分的总时间复杂度是 $O(n2^n)$，这里需要把集合状态压成一个正整数。

---

$S_0 = S_2$ 等价于不染联通块但是可以染孤立的点。

$S_1$ 等价于对图做二分图染色的方案数，如果图不是二分图那它就是空集。

$S_{空}$ 只有在 $m =0$ 的时候才能不会 $0$，大小是 $2^n$。

---

至此我们写完了一个水黑。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int x[2005],y[2005];
int n,m;
int ok[45][45],ss[45];
int col[2005],fa[2005],sz[2005];
vector<int>p[105];
int ok1[(1<<20)+5],ok2[(1<<20)+5],pre[(1<<20)+5];
int find(int x){
	if(fa[x] == x)return x;
	return fa[x] = find(fa[x]);
}void merge(int a,int b){
	if(find(a)!=find(b))sz[find(b)]+=sz[find(a)];
	fa[find(a)] = find(b);
}int okk = 1;
void color(int now,int c){
	col[now] = c;
	for(int i =0;i<p[now].size();i++){
		if(!col[p[now][i]])color(p[now][i],3-c);
		else if(col[p[now][i]] == col[now])okk = 0;
	}
}void dfs1(int dep,int s,int S){
	if(dep == n/2){
		ok1[S] = 1;return;
	}if(!(s>>dep&1)){
		dfs1(dep+1,s|ss[dep],S|(1ll<<dep));
	}dfs1(dep+1,s,S);
}int tot = 0;
void dfs2(int dep,int s,int S){
	if(dep == n){
		int tt = 0;
		for(int i =0;i<n/2;i++)tt+=((!(s>>i&1)))<<i;
		tot+=pre[tt];return;
	}if(!(s>>dep&1)){
		dfs2(dep+1,s|ss[dep],S|(1ll<<dep));
	}dfs2(dep+1,s,S);
}int solve_all(){
	return 1ll<<n;
}int solve_0(){
	int tt = 0;
	for(int i = 0;i<n;i++)if(sz[find(i)] == 1)tt++;
	return 1ll<<tt;
}int solve_1(){int tt = 0;
	for(int i = 0;i<n;i++){
		if(fa[i] == i)color(i,1),tt++;
	}if(okk == 0)return 0;return 1ll<<tt;
}int solve_2(){
	int tt =0 ;
	for(int i = 0;i<n;i++){
		if(sz[find(i)] == 1)tt++; 
	}return 1ll<<tt;
}int solve_01(){
	for(int i =0;i<n;i++){
		for(int j =0;j<n;j++){
			if(ok[i][j])ss[i]|=1ll<<j; 
		}
	}dfs1(0,0,0);
	memcpy(pre,ok1,sizeof(pre)); 
	for(int i = 0;i<n/2;i++){
		for(int j =0;j<(1<<(n/2));j++){
			if(j>>i&1)pre[j]+=pre[j^(1<<i)];
		}
	}dfs2(n/2,0,0);
	return tot;
}int solve_02(){
	int tt =0 ;
	for(int i = 0;i<n;i++){
		if(find(i) == i)tt++;
	}return 1ll<<tt;
}int solve_012(){
	if(m !=0)return 0;return 1ll<<n;
}
signed main(){
	cin >> n >> m;
	for(int i = 0;i<=n;i++)fa[i] = i,sz[i] = 1;
	for(int i = 1;i<=m;i++){
		int a,b;cin >> a >> b;a--,b--;
		ok[a][b] = ok[b][a] = 1;merge(a,b);
		p[a].push_back(b),p[b].push_back(a);
	}
	int ans = solve_all()-solve_01()*2-solve_02()+solve_0()+solve_1()+solve_2()-solve_012();
	cout << ans << endl; 
	return 0;
}/*
折半，bitset优化掉一个n。 
我去，真难写。 
 
4 4
1 2
2 3
3 4
4 1
*/
```

---

## 作者：shinkuu (赞：0)

一个更简单，更暴力且更快的做法！

首先把问题转化成独立集计数。考虑直接搜独立集。设 $dp_{S}$ 为点集 $S$ 的导出子图的最大独立集。转移考虑拿出 $S$ 中编号最小的点 $u$。考虑 $u$ 是否在独立集中，若不在则从 $dp_{S/\{u\}}$ 中转移过来，否则设和 $u$ 相邻的点以及 $u$ 组成的集合为 $A_{u}$，从 $dp_{S/A_u}$ 转移。

复杂度为什么是对的，可以参考[pb的证明](https://www.cnblogs.com/p-b-p-b/p/14200616.html)。具体就是，分成前 $\frac n2$ 层和后 $\frac n2$ 层。前 $\frac n2$ 层，因为每次只有两种转移，所以状态数显然为 $O(2^\frac n2)$，后 $\frac n2$ 次，考虑每次一定会从 $S$ 中删去编号最小的点，所以这些状态中为 $1$ 的位只有可能在后 $\frac n2$ 位中，也只有 $O(2^\frac n2)$ 种。并且显然卡不满。

@vidoliga 还有另一种证明方法，设复杂度为 $T(n)$，则全部顶满时 $T(n)=T(n-1)+T(n-2)$，这是因为若钦定 $u$ 点在独立集中，则一定至少使 $S$ 的大小减少 $2$，否则可以分开做。这样也能大概证明复杂度。

以及一个可能的常数优化是，对于一开始的不同连通块，分开做，再用一个 dp 合并成最后的答案。

code：

```cpp
int n,m,vis[N];
bool fl;
ll pw[N],a[N],dp[N][2][2][2];
vector<int> g;
map<ll,ll> mp;
int tot,head[N];
struct node{
	int to,nxt;
}e[M<<1];
il void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
void dfs(int u){
	g.eb(u);
	go(i,u){
		int v=e[i].to;
		if(vis[v]){
			if(vis[u]==vis[v]){
				fl=0;
			}
			continue;
		}
		vis[v]=3-vis[u];
		dfs(v);
	}
}
ll calc(ll S){
	if(!S){
		return 1;
	}
	if(mp.count(S)){
		return mp[S];
	}
	int u=__lg(S&(-S));
	return mp[S]=calc(S^(1ll<<u))+calc(S&a[u+1]);
}
void Yorushika(){
	read(n,m),tot=0;
	mp.clear();
	pw[0]=1;
	rep(i,1,n){
		head[i]=vis[i]=a[i]=0;
		pw[i]=2*pw[i-1];
	}
	rep(i,1,m){
		int u,v;read(u,v);
		add(u,v),add(v,u);
		a[u]|=1ll<<(v-1),a[v]|=1ll<<(u-1);
	}
	const ll mask=(1ll<<n)-1;
	rep(i,1,n){
		a[i]=mask^(a[i]|(1ll<<(i-1)));
	}
	mems(dp,0);
	dp[0][0][0][0]=1;
	int op=0;
	rep(i,1,n){
		if(vis[i]){
			continue;
		}
		g.clear(),fl=1;
		vis[i]=1,dfs(i);
		if(g.size()==1){
			op^=1,mems(dp[op],0);
			rep(j,0,1){
				rep(k,0,1){
					rep(l,0,1){
						dp[op][j][k][l]+=dp[op^1][j][k][l]*2;
					}
				}
			}
			continue;
		}
		ll S=0;
		for(int j:g){
			S|=1ll<<(j-1);
		}
		ll x=fl,y=calc(S);
		ll A=y-2*fl,B=pw[g.size()]-2*(A+x),C=2*x;
		op^=1,mems(dp[op],0);
		rep(j,0,1){
			rep(k,0,1){
				rep(l,0,1){
					dp[op][1][1][1]+=dp[op^1][j][k][l]*B;
					dp[op][1][k][1]+=dp[op^1][j][k][l]*(A-1);
					dp[op][1][k][l]+=dp[op^1][j][k][l];
					dp[op][j][1][1]+=dp[op^1][j][k][l]*(A-1);
					dp[op][j][1][l]+=dp[op^1][j][k][l];
					dp[op][j][k][1]+=dp[op^1][j][k][l]*C;
				}
			}
		}
	}
	printf("%lld\n",dp[op][1][1][1]);
}
signed main(){
	int t=1;
	while(t--){
		Yorushika();
	}
}
```

---

