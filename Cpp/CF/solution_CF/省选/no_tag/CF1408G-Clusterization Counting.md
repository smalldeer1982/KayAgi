# Clusterization Counting

## 题目描述

There are $ n $ computers in the company network. They are numbered from $ 1 $ to $ n $ .

For each pair of two computers $ 1 \leq i < j \leq n $ you know the value $ a_{i,j} $ : the difficulty of sending data between computers $ i $ and $ j $ . All values $ a_{i,j} $ for $ i<j $ are different.

You want to separate all computers into $ k $ sets $ A_1, A_2, \ldots, A_k $ , such that the following conditions are satisfied:

- for each computer $ 1 \leq i \leq n $ there is exactly one set $ A_j $ , such that $ i \in A_j $ ;
- for each two pairs of computers $ (s, f) $ and $ (x, y) $ ( $ s \neq f $ , $ x \neq y $ ), such that $ s $ , $ f $ , $ x $ are from the same set but $ x $ and $ y $ are from different sets, $ a_{s,f} < a_{x,y} $ .

For each $ 1 \leq k \leq n $ find the number of ways to divide computers into $ k $ groups, such that all required conditions are satisfied. These values can be large, so you need to find them by modulo $ 998\,244\,353 $ .

## 说明/提示

Here are all possible ways to separate all computers into $ 4 $ groups in the second example:

- $ \{1, 2\}, \{3, 4\}, \{5\}, \{6, 7\} $ ;
- $ \{1\}, \{2\}, \{3, 4\}, \{5, 6, 7\} $ ;
- $ \{1, 2\}, \{3\}, \{4\}, \{5, 6, 7\} $ .

## 样例 #1

### 输入

```
4
0 3 4 6
3 0 2 1
4 2 0 5
6 1 5 0```

### 输出

```
1 0 1 1```

## 样例 #2

### 输入

```
7
0 1 18 15 19 12 21
1 0 16 13 17 20 14
18 16 0 2 7 10 9
15 13 2 0 6 8 11
19 17 7 6 0 4 5
12 20 10 8 4 0 3
21 14 9 11 5 3 0```

### 输出

```
1 1 2 3 4 3 1```

# 题解

## 作者：Karry5307 (赞：13)

### 题意

给定 $n$ 个点的无向带权完全图，边权为 $1\sim\frac{n(n-1)}{2}$。对于满足 $1\leq k\leq n$ 的每个 $k$ 求出将原图划分成 $k$ 个组的方案数，满足组间边的权大于组内边的权值，答案对 $998244353$ 取模。

$\texttt{Data Range:}1\leq n\leq 1500$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13769995.html)

这个题蛮好的，只是我赛时没有想出来（甚至差点没有看懂题目），果然还是我太菜了/kk

首先从小到大把边加进来，然后可以发现一个结论：一个连通块是满足条件的当且仅当在加完某条边之后这个连通块是一个团。

这个时候可以直接用类似于 Kruskal 的方法：从小到大加边，并查集维护一下这个连通块的大小和边数，当加完某条边时候可以满足这个连通块是一个团的话就标记一下这个连通块是可以的。

这个时候好像是可以 DP 了，但是复杂度会爆炸。

考虑优化一下，在从小到大加边的过程中考虑 Kruskal 重构树。由于**重构树新加的节点维护的是一个连通块，其叶子节点是连通块中所有的节点**，所以可以对重构树进行 dfs，用一段区间表示一个连通块。

于是现在变成了有一些区间，要从中选出 $k$ 个覆盖 $1\sim n$ 的所有位置。把所有区间挂到右端点上，设 $f_{i,j}$ 表示当前位置为 $i$ 并且钦定当前最后一个区间右端点为 $i$，选出了 $j$ 个区间的答案，转移的时候枚举一下最后一个区间的左端点是什么就没了。

时间复杂度 $O(n^2\log n)$，主要瓶颈在排序上。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=3e3+51,MOD=998244353;
struct EdgeForKruskal{
	ll from,to,dist;
	inline bool operator <(const EdgeForKruskal &rhs)const
	{
		return this->dist<rhs.dist;
	}
};
EdgeForKruskal ed[MAXN*MAXN];
ll n,m,idx,u,v,itvc;
ll x[MAXN][MAXN],f[MAXN][MAXN],ffa[MAXN],sz[MAXN],edc[MAXN];
ll l[MAXN],r[MAXN],flg[MAXN];
vector<ll>g[MAXN],itv[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll find(ll x)
{
	return ffa[x]==x?x:ffa[x]=find(ffa[x]);
}
inline void add(ll x)
{
	if((++edc[x])==sz[x]*(sz[x]-1)/2)
	{
		flg[x]=1;
	}
}
inline void dfs(ll x)
{
	if(x<=n)
	{
		return (void)(l[x]=r[x]=++itvc);
	}
	l[x]=n+1;
	for(register int to:g[x])
	{
		dfs(to),l[x]=min(l[x],l[to]);
	}
	r[x]=itvc,flg[x]?itv[r[x]].push_back(l[x]):(void)1;
}
int main()
{
	n=read(),f[0][0]=1;
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			x[i][j]=read();
			j>i?(void)(ed[++m]=(EdgeForKruskal){i,j,x[i][j]}):(void)1;
		}
	}
	idx=n,sort(ed+1,ed+m+1);
	for(register int i=1;i<=n;i++)
	{
		flg[i]=1,itv[i].push_back(i),ffa[i]=i,sz[i]=1,edc[i]=0;
	}
	for(register int i=1;i<=m;i++)
	{
		u=find(ed[i].from),v=find(ed[i].to);
		if(u==v)
		{
			add(u);
		}
		else
		{
			g[++idx].push_back(u),g[idx].push_back(v);
			ffa[u]=ffa[v]=ffa[idx]=idx;
			sz[idx]=sz[u]+sz[v],edc[idx]=edc[u]+edc[v],add(idx);
		}
	}
	dfs(idx);
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			for(register int k:itv[i])
			{
				f[i][j]=(f[i][j]+f[k-1][j-1])%MOD;
			}
		}
	}
	for(register int i=1;i<=n;i++)
	{
		printf("%d ",f[n][i]);
	}
}
```

---

## 作者：Soulist (赞：13)

请注意，**题面保证了 $a_{i,j}$ 互不相同...**（如果你没看到可能会像我一样被卡很久...）

我们发现第二个条件等价于，每个连通块内部的边总是小于连通块外部的边。

我们发现可以从小到大将边排序，然后依次加边。

然后我们发现，一个连通块是满足条件 $2$ 的当且仅当按此加边方法其内部构成了一个团。

考虑预处理那些连通块是合法，我们考虑类似于生成树一样，借助并查集维护连通块，然后加边量到达 $\frac{sz\times (sz-1)}{2}$ 时就标记这个连通块合法。

这样已经可以 dp 了，但复杂度是指数的。

考虑优化，我们发现如果将这个流程对应的 Kruskal 重构树建出来，每个合法的连通块都对应一个区间，问题等价于有 $n+m$ （$m<n$）个区间是合法的，选 $k$ 个区间不重复的覆盖所有位置的方案数。

将区间挂在 $r$ 端点上，然后直接 dp 即可，复杂度瓶颈在排序上，为 $\mathcal O(n^2\log n)$

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define pb push_back
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int P = 998244353 ; 
const int N = 3000 + 5 ; 
int n, cnt, a[1505][1505], ans[N], fa[N], sz[N], eg[N], L[N], R[N], fl[N] ; 
int num, dp[1505][1505], Id[N] ; 
struct E {
	int fr, to, w ; 
} e[N * N] ;
vector<int> G[N] ; 
vector<int> rr[N] ; 
bool cmp( E x, E y ) {
	return x.w < y.w ; 
}
int fd(int x) {
	return (x == fa[x]) ? x : fa[x] = fd(fa[x]) ; 
}
void inc(int x) {
	++ eg[x] ; 
	if( eg[x] == sz[x] * (sz[x] - 1) / 2 ) fl[x] = 1 ; 
}
void Dfs(int x){
	if( x <= n ) {
		L[x] = R[x] = ++ num ; return ; 
	}
	L[x] = n + 1 ; 
	for(int v : G[x]) {
		Dfs(v) ; 
		L[x] = min( L[x], L[v] ) ;
	}
	R[x] = num ;
	if( fl[x] ) rr[R[x]].pb(L[x]) ; 
}
signed main()
{
	n = gi() ; 
	rep( i, 1, n ) rep( j, 1, n ) a[i][j] = gi() ; 
	rep( i, 1, n ) for(int j = i + 1; j <= n; ++ j)
	e[++ cnt] = (E){ i, j, a[i][j] } ;
	sort(e + 1, e + cnt + 1, cmp) ; 
	rep( i, 1, n ) fl[i] = 1, rr[i].pb(i) ; 
	rep( i, 1, n ) fa[i] = i, sz[i] = 1, eg[i] = 0 ; 
	int idx = n ; 
	rep( i, 1, cnt ) {
		int x = e[i].fr, y = e[i].to ; 
		int u = fd(x), v = fd(y) ;
		if( u == v ) inc(u) ; 
		else {
			++ idx ; G[idx].pb(u), G[idx].pb(v) ; 
			fa[u] = idx, fa[v] = idx, fa[idx] = idx ; 
			sz[idx] = sz[u] + sz[v], 
			eg[idx] = eg[v] + eg[u], 
			inc(idx) ; 
		}
	}
	Dfs(idx) ;
	dp[0][0] = 1 ; 
	for(re int i = 1; i <= n; ++ i) {
		for(re int k = 1; k <= n; ++ k) {
			for(int v : rr[i])
			dp[i][k] = (dp[i][k] + dp[v - 1][k - 1]) % P ; 
		}
	}
	rep( i, 1, n ) printf("%lld ", dp[n][i] ) ; puts("") ; 
	return 0 ;
}
```

---

## 作者：约瑟夫用脑玩 (赞：10)

从小到大加边，并查集维护，加入某条边成了一个团说明这个团是可行的。

考虑可行团之间的关系，发现要么包含要么不交，**于是按包含关系建成一棵树**，类似树上背包做子树形成了多少个团即可，复杂度同树上背包，$n^2$。

---

## 作者：crashed (赞：4)

**去往[原博客](https://www.cnblogs.com/crashed/p/13805657.html)食用更佳。**
   
# 题目

[点这里](https://www.luogu.com.cn/problem/CF1408G)看题目。

# 分析

不难想到，题目的要求，就是要**组内边总是比相邻的组间边小**。

也就是要**组内边的最大值小于组间边的最小值**。   

于是可以从小到大加边。如果一个连通块在加边的时候，变成了一个**团**，这就意味着**现在这个连通块可以单分为一组**（剩余的边只有可能成为组间边，组间边都比组内边大）。之后我们就用 $G(G\subset V)$ 表示一个组。     

-------

我们可以证明，能分的组的数量是 $O(n)$ 的，且**任意两组要么包含，要么不交**。   

关于数量的证明：

考虑用组内边的**权最大**的一条来代替这个组，我们称这种边为 " 标准边 " 。

对于标准边 $e$，我们可以不断地扩展边权小于 $e$ 的边，最终找到这条标准边对应的组的点集。

如果仅由标准边形成的子图有环，那么考虑一个环上的最大边 $e$ 和次大边 $e'$。此时 $e'$ 对应的组包含这个环，但是环上点集对应的团包含了 $e$，$e$ 的权大于 $e'$，出现了矛盾。

所以可以知道，标准边最终会形成**森林**的样子，因此数量是 $O(n)$ 的。   

关于组的关系的证明：

直接考虑**两个相交但却不包含的组** $G_1,G_2$。我们提出它们的两个标准边，记为 $e_1,e_2$。  

由于边权彼此不等，因此不妨认为 $e_1$ 的权大于 $e_2$。那么显然 $G_2\subset G_1$，矛盾。   

--------------

综合以上我们可以知道，最终可以单独划分的组**数量是 $O(n)$ 的，且可以按照包含关系划分成树的形状**。   

我们可以直接从小到大加边，建立 Kruskal 重构树。此时树上的每一个点都对应了一个连通块。我们可以直接在建树的时候判断一个连通块是否可以被单独划分。  

接着就可以直接在树上对可行的块进行**背包 DP** 了。时间复杂度是 $O(n^2)$ 的。

# 代码

```cpp
#include <cstdio>
#include <utility>
using namespace std;

typedef long long LL;
typedef pair<int, int> Edge;

const int mod = 998244353;
const int MAXN = 3e3 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar(); int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ); s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) putchar( '-' ), x = -x;
	if( 9 < x ) write( x / 10 );
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

int f[MAXN][MAXN];
int lch[MAXN], rch[MAXN], tot[MAXN];
bool able[MAXN];

int fa[MAXN], siz[MAXN], Etot[MAXN];

Edge E[MAXN * MAXN];
int Graph[MAXN][MAXN];
int N, ID;

int Edg( const int n ) { return n * ( n - 1 ) >> 1; }
int Sub( int x, int v ) { return x < v ? x + mod - v : x - v; }
int Mul( LL x, int v ) { x *= v; if( x >= mod ) x %= mod; return x; }
int Add( int x, int v ) { return x + v >= mod ? x + v - mod : x + v; }
int FindSet( const int u ) { return fa[u] = ( fa[u] == u ? u : FindSet( fa[u] ) ); }

void DFS( const int u )
{
	if( u <= N ) { tot[u] = f[u][1] = 1; return; }
	int l = lch[u], r = rch[u]; DFS( l ), DFS( r );
	for( int j = 1 ; j <= tot[r] ; j ++ )
		for( int k = 1 ; k <= tot[l] ; k ++ )
			f[u][j + k] = Add( f[u][j + k], Mul( f[l][k], f[r][j] ) );
	tot[u] = tot[l] + tot[r];
	if( able[u] ) f[u][1] = Add( f[u][1], 1 );
}

int main()
{
	read( N );
	for( int i = 1 ; i <= N ; i ++ )
		for( int j = 1 ; j <= N ; j ++ )
		{
			read( Graph[i][j] );
			if( i < j ) E[Graph[i][j]] = Edge( i, j );
		}
	for( int i = 1 ; i <= N << 1 ; i ++ )
		fa[i] = i, siz[i] = i <= N;
	int cnt = N, rt = N;
	for( int i = 1 ; i <= N ; i ++ ) f[i][1] = 1;
	for( int i = 1, u, v ; i <= Edg( N ) ; i ++ )
	{
		u = FindSet( E[i].first ), 
		v = FindSet( E[i].second );
		if( u != v )
		{
			fa[u] = fa[v] = ++ cnt;
			lch[cnt] = u, rch[cnt] = v, rt = cnt;
			Etot[cnt] = Etot[u] + Etot[v] + 1, siz[cnt] = siz[u] + siz[v];
			if( Etot[cnt] == Edg( siz[cnt] ) ) able[cnt] = true;
		}
		else
		{
			if( ( ++ Etot[u] ) == Edg( siz[u] ) )
				able[u] = true;
		}
	}
	DFS( rt );
	for( int k = 1 ; k <= N ; k ++ ) write( f[rt][k] ), putchar( k == N ? '\n' : ' ' );
	return 0;
}
```

---

## 作者：GIFBMP (赞：3)

首先我们考虑什么样的联通块一定满足题目给定的性质。考虑从小到大加边，当加到某一条边的时候，如果一个连通块形成了团，那么这个连通块一定是合法的。那么我们就可以考虑 DP，但是这样是 $\Theta(2^n\times n)$ 的，显然无法通过本题。

考虑对加边的过程建立 Kruskal 重构树。我们发现每一个合法的连通块都对应了 Kruskal 重构树上的一棵子树，这样合法的连通块数最多有 $2\times n-1$ 个。于是我们可以 dfs 一遍求出每个叶子节点的 dfs 序以及每棵子树代表的区间，问题就转化为了：给定若干个区间，求从中选出 $k$ 个不交的区间，使得它们可以覆盖 $[1,n]$ 的方案数。设 $f_{i,j}$ 表示当前覆盖了 $[1,i]$，用了 $j$ 个区间的方案数。直接转移即可。

时间复杂度 $\Theta(n^2\log n)$。

Code:

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm> 
#include <vector>
using namespace std ;
const int MAXN = 2e3 + 10 , MAXM = 4e6 + 10 , mod = 998244353 ;
int n , a[MAXN][MAXN] , px[MAXM] , py[MAXM] ;
int fa[MAXN * 2] , sz[MAXN * 2] , c[MAXN * 2] , cnt , vis[MAXN * 2] ;
int find (int x) {return fa[x] == x ? x : fa[x] = find (fa[x]) ;}
int fir[MAXN * 2] , tot , L[MAXN * 2] , R[MAXN * 2] , cc ;
struct edge {int to , nxt ;} e[MAXN * 4] ;
void add (int u , int v) {
	e[++tot].to = v ; e[tot].nxt = fir[u] ; fir[u] = tot ;
}
void merge (int x , int y) {
	x = find (x) , y = find (y) ;
	if (x == y) {
		if ((++c[x]) == sz[x] * (sz[x] - 1) / 2) vis[x] = 1 ;
		return ;
	}
	fa[x] = fa[y] = ++cnt , sz[cnt] = sz[x] + sz[y] , c[cnt] = c[x] + c[y] + 1 ;
	add (cnt , x) , add (cnt , y) ;
	if (c[cnt] == (sz[cnt]) * (sz[cnt] - 1) / 2) vis[cnt] = 1 ;
}
int f[MAXN][MAXN] ;
vector <int> G[MAXN * 2] ;
void dfs (int x) {
	if (x <= n) {L[x] = R[x] = ++cc , G[cc].push_back (cc) ; return ;}
	L[x] = n + 1 , R[x] = 0 ;
	for (int i = fir[x] ; i ; i = e[i].nxt)
		dfs (e[i].to) , L[x] = min (L[x] , L[e[i].to]) ;
	if (vis[x]) G[(R[x] = cc)].push_back (L[x]) ;
}
int main () {
	scanf ("%d" , &n) ; cnt = n ;
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= n ; j++)
			scanf ("%d" , &a[i][j]) , px[a[i][j]] = i , py[a[i][j]] = j ;
	for (int i = 1 ; i <= n ; i++) sz[i] = 1 , c[i] = 0 , vis[i] = 1 ;
	for (int i = 1 ; i < 2 * n ; i++) fa[i] = i ;
	for (int i = 1 ; i <= n * (n - 1) / 2 ; i++) merge (px[i] , py[i]) ;
	f[0][0] = 1 ; dfs (cnt) ;
	for (int i = 1 ; i <= n ; i++) {
		for (int j = 1 ; j <= n ; j++) {
			for (int k = 0 ; k < G[i].size () ; k++)
				f[i][j] = (f[i][j] + f[G[i][k] - 1][j - 1]) % mod ;
		}
	}
	for (int i = 1 ; i <= n ; i++) printf ("%d " , f[n][i]) ;
	return 0 ;
} 
```

---

## 作者：RiverHamster (赞：2)

## 题意

- 给定 $n$ 个点的带权无向完全图，点 $i, j$ 之间的权值为 $a_{i, j}$，权值是一个 $1 \sim \frac{n(n-1)}{2}$ 的排列。
- 计数把原图划分成 $k$ 个组的方案数，满足：
  - 对于任意的 $(s, f), (x, y)$，其中 $s, f, x$ **同组**，$y$ 与 $x$ **不同组** （$s \ne f, x \ne y$），$a_{s, f} < a_{x, y}$，即（对于每个组）组间边大于组内边。
- 输出一行 $n$ 个数，对于 $k \in [1, n]$ 求出答案，对 $998244353$ 取模。
- $n \le 1500$

## 题解

考虑从小到大处理边。将边排序，依次在并查集上连接。

设 $f_i$ 为某个连通块划分成 $i$ 个组的方案数。

如果一个连通块还不是团时就已经和另一个连通块相连接，那么它不能单独成组，因为组内有比组间更大的边（还未加入）。

初始时每个点可以单独成组，因此对于每个点 $f_1 = 1$。连接两个连通块时直接做多项式卷积即可（不可能发生合并），加入所有边即可得到答案。

当一个连通块形成一个团时，可以单独成组，因此令 $f_1$ 增 $1$。

复杂度 $\mathcal O(n^2)$，类似树形 DP。

[参考实现](https://www.cnblogs.com/RiverHamster/p/sol-cf1408g.html)

---

## 作者：SegTree (赞：1)

考虑如果 $i$ 出现，则和 $i$ 同时出现在一组的一定是按照 $a_{i,j}$ 排序后选取的一段前缀，那么只需要 check 这个前缀中是否每个点长度为 $j$ 的前缀集合与它相等、并且外面没有权值更小的。可以用 XOR Hash 随便维护一下。

显然，集合要么包含，要么不交，只有 $O(n)$ 个，可以把它们建成一颗树，每个点的父亲是包含它的最小集合，然后给集合中每个数跑一个 dfn 序，从而把每个集合映射到数轴上的一段区间。

问题转化为：给你区间若干，问 $1\sim n$ 每个点均被覆盖恰 $1$ 次，选 $j$ 个点的方案数，可以通过平凡 dp 解决。

复杂度 $O(n^2\log n)$。

---

## 作者：daniEl_lElE (赞：1)

组间边大于组内边的限制容易让人想到从小到大加入边。我们发现加入一条边会有两种情况：

* 这条边两个端点原本不连通。
* 这条边两个端点原本连通。

容易发现在加边的过程中，只会出现 $O(n)$ 种不同的连通块。

考虑 $dp_{i,j}$ 表示加入一些边后，$i$ 所在连通块被分成了 $j$ 个不同的组。其中 $i$ 代表了这个连通块，可以理解为在使用并查集后，$i$ 是连通块内唯一 $f_i=i$。

对于第一种，转移时合并两边所在连通块即可。第二种无需转移。

然而，当某时刻某连通块中形成了完全图，此时这个连通块可以成为同一个组，每次加边后特判一下，给 $dp_{i,0}$ 加上 $1$ 即可。

根据树上依赖背包的证明可得复杂度为 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define s(i,j) ((i-1)*n+j)
#define mid ((l+r)>>1)
#define add(i,j) ((i+j)>=mod?i+j-mod:i+j)
using namespace std;
const int mod=998244353;
int f[1505],siz[1505],ed[1505],a[1505][1505],dp[1505][1505],tmp[1505];
pair<int,int> pos[2250005];
int find(int i){
	return f[i]==i?f[i]:f[i]=find(f[i]);
}
signed main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
			if(i<j) pos[a[i][j]].first=i,pos[a[i][j]].second=j;
		}
	}
	for(int i=1;i<=n;i++) f[i]=i,siz[i]=1,dp[i][1]=1;
	for(int i=1;i<=n*(n-1)/2;i++){
		int x=pos[i].first,y=pos[i].second;
		if(find(x)==find(y)){
			ed[find(x)]++;
		}
		else{
			int u=find(x),v=find(y);
			memset(tmp,0,sizeof(tmp));
			for(int j=1;j<=siz[u];j++){
				for(int k=1;k<=siz[v];k++){
					(tmp[j+k]+=dp[u][j]*dp[v][k])%=mod;
				}
			}
			siz[u]+=siz[v];
			ed[u]+=ed[v]+1;
			f[v]=u;
			for(int j=1;j<=siz[u];j++){
				dp[u][j]=tmp[j];
			}
		}
		int u=find(x);
		if(ed[u]==siz[u]*(siz[u]-1)/2) dp[u][1]=1;
	}
	for(int i=1;i<=n;i++) cout<<dp[find(1)][i]<<" ";
	return 0; 
}
```

---

## 作者：s_r_f (赞：1)

一些怨念：赛时差 2min 没冲完这个题……

建出 $Kruskal$ 重构树. 不难发现我们取的联通块必然是 $Kruskal$ 重构树上的一个子树。

那么 $check$ 每个子树能否成为一个联通块，然后做一个树上背包即可。

$\Theta(n^2)$ , 如果直接对边排序了就是 $\Theta(n^2\log n)$ 的，也能过。

code : 
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
template <typename T> void read(T &x){
	static char ch; x = 0,ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0',ch = getchar();
}
inline void write(int x){if (x > 9) write(x/10); putchar(x%10+'0'); }
const int N = 3005,P = 998244353;
inline void upd(int &x,int v){ x = (x+v>=P)?(x+v-P):(x+v); }
int n,G[N][N],cntv;
struct Union_Find_Set{
	int fa[N<<1];
	inline void init(){ for (int i = 1; i <= n<<1; ++i) fa[i] = i; }
	inline int Find(int x){ return x == fa[x] ? x : (fa[x] = Find(fa[x])); }
	inline void Merge(int x,int y){ fa[Find(x)] = Find(y); }
}S;
struct Edge{
	int x,y;
	bool operator < (const Edge w) const{ return G[x][y] < G[w.x][w.y]; }
}e[N*N/2]; int le;
int Rt,fa[N<<1],ch[N<<1][2];
int F[N<<1][N],siz[N],tl[N],tr[N],Time,pos[N];
int mx[N<<1],pre[N][N],suf[N][N];
inline void dfs0(int x){
	if (x <= n){ tl[x] = tr[x] = ++Time; pos[Time] = x; siz[x] = 1; return; }
	dfs0(ch[x][0]); dfs0(ch[x][1]); tl[x] = tl[ch[x][0]],tr[x] = tr[ch[x][1]]; siz[x] = siz[ch[x][0]] + siz[ch[x][1]];
}
inline void dfs(int x){
	if (x <= n){ F[x][1] = 1;  return; }
	dfs(ch[x][0]); dfs(ch[x][1]);
	for (int i = 1; i <= siz[ch[x][0]]; ++i)
	for (int j = 1; j <= siz[ch[x][1]]; ++j){
		upd(F[x][i+j],(LL)F[ch[x][0]][i] * F[ch[x][1]][j] % P);
	}
	mx[x] = max(mx[ch[x][0]],mx[ch[x][1]]);
	for (int i = tl[ch[x][0]]; i <= tr[ch[x][0]]; ++i)
	for (int j = tl[ch[x][1]]; j <= tr[ch[x][1]]; ++j) mx[x] = max(mx[x],G[pos[i]][pos[j]]);
	for (int i = tl[x]; i <= tr[x]; ++i){
		int val = 1000000000;
		if (tl[x] > 1) val = min(val,pre[pos[i]][tl[x]-1]);
		if (tr[x] < n) val = min(val,suf[pos[i]][tr[x]+1]);
		if (val < mx[x]){ F[x][1] = (F[x][1] + P-1) % P; break; }
	}
	F[x][1] = (F[x][1] + 1) % P;
}
int main(){
	int i,j,u,v;
	read(n); cntv = n; S.init();
	for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) read(G[i][j]);
	for (i = 1; i <= n; ++i) for (j = i+1; j <= n; ++j) ++le,e[le].x = i,e[le].y = j;
	for (i = 1; i <= n; ++i) G[i][i] = 100000000;
	sort(e+1,e+le+1);
	for (i = 1; i <= le; ++i){
		u = S.Find(e[i].x),v = S.Find(e[i].y);
		if (u == v) continue;
		++cntv; S.Merge(u,cntv); S.Merge(v,cntv);
		ch[cntv][0] = u,ch[cntv][1] = v; fa[u] = fa[v] = cntv; Rt = cntv;
	}
	dfs0(Rt);
	for (i = 1; i <= n; ++i){
		for (j = 1; j <= n; ++j) pre[i][j] = suf[i][j] = G[i][pos[j]];
		for (j = 2; j <= n; ++j) pre[i][j] = min(pre[i][j],pre[i][j-1]);
		for (j = n-1; j ; --j) suf[i][j] = min(suf[i][j],suf[i][j+1]);
	}
	dfs(Rt);
	for (i = 1; i <= n; ++i) write(F[Rt][i]),putchar(i<n?' ':'\n');
	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1408G)

---

# 思路：
把边从小到大排序依次加入，维护 $f_{i,j}$ 表示在当前连通块 $i$ 中有 $j$ 个团的方案。

团只考虑当前加入的边，加入一条边后先把两个块卷积合并（如果不同的话）。

然后考虑新增的团，如果当前连通块不是一个团，那么如果要加就只能加一部分，即剩下一些边不加。

由于当前边是连通块中最大的，所以不能满足条件。

如果是一个团的话那就把 $f_{i,j}+1$。

卷积的复杂度同树上背包，时间复杂度 $O(n^2)$。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
const int M=2e3+10;
#define add(a,b) a=((a)+(b))%998244353
int a[N][2],fa[M],s1[M],s2[M],n,l,tot,x,y,s,A[M],f[M][M];
int gf(int t){
	if(fa[t]==t){
		return fa[t];
	} 
	fa[t]=gf(fa[t]);
	return fa[t];
}
signed main(){
	cin>>n;
	s=n*(n-1)/2;
	for(int i=1;i<=n;i++){
		fa[i]=i;
		s1[i]=f[i][1]=1;
		for(int j=1;j<=n;j++){
			cin>>x;
			if(i<j){
				a[x][0]=i;
				a[x][1]=j;
			}
		}
	}
	for(int i=1;i<=s;i++){
		x=gf(a[i][0]);
		y=gf(a[i][1]);
		if(x!=y){
			memset(A,0,sizeof(A));
			for(int j=1;j<=s1[x];j++){
				for(int k=1;k<=s1[y];k++){
					add(A[j+k],f[x][j]*f[y][k]);
				}
			}
			memcpy(f[x],A,sizeof(A));
			fa[y]=x;
			s1[x]+=s1[y];
			s2[x]+=s2[y]+1;
		}else{
			s2[x]++;
		}
		if(s1[x]*(s1[x]-1)/2==s2[x]){
			f[x][1]++;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<f[gf(1)][i]<<" ";
	}
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

考虑分组可能的形态。发现它必定是进行 Kruskal 求 MST 的过程中曾经出现过的一个连通块（而且某一时刻，这个连通块需要是完全图）。

因此求出 Kruskal 重构树，我们需要选出 $k$ 个不相交子树，使得他们覆盖了所有的叶子。对于每个子树，我们都可以判断出他们能不能选。

使用树形背包即可做到 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1500+10,MOD=998244353;
int n,v[MAXN][MAXN],tot,fa[MAXN],cnt[MAXN],dp[MAXN*2][MAXN],sze[MAXN*2],ls[MAXN*2],rs[MAXN*2],rt[MAXN],flg[MAXN*2];
int find(int k) {return (fa[k]==k)?k:(fa[k]=find(fa[k]));}
void merge(int u,int v) {return u=find(u),v=find(v),cnt[u]+=cnt[v],fa[v]=u,void();}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) ffor(j,1,n) cin>>v[i][j];
	ffor(i,1,n) flg[i]=1,fa[i]=i,rt[i]=i,sze[i]=1;
	tot=n;
	vector<pair<int,pair<int,int>>> e;
	ffor(i,1,n) ffor(j,i+1,n) e.push_back({v[i][j],{i,j}});
	sort(e.begin(),e.end());
	for(auto pr:e) {
		int w=pr.first,u=pr.second.first,v=pr.second.second;
		if(find(u)!=find(v)) ++tot,ls[tot]=rt[find(u)],rs[tot]=rt[find(v)],sze[tot]=sze[rt[find(u)]]+sze[rt[find(v)]],merge(u,v),rt[find(u)]=tot;
		cnt[find(u)]++;
		if(cnt[find(u)]*2==sze[rt[find(u)]]*(sze[rt[find(u)]]-1)) flg[rt[find(u)]]=1;
	}
	ffor(i,1,tot) {
		if(ls[i]) ffor(j,0,sze[ls[i]]) ffor(k,0,sze[rs[i]]) dp[i][j+k]=(dp[i][j+k]+dp[ls[i]][j]*dp[rs[i]][k])%MOD;	
		dp[i][1]+=flg[i];
	}
	ffor(i,1,n) cout<<dp[tot][i]<<' ';
	return 0;
}
```

---

## 作者：xfrvq (赞：0)

简单题。

从小到大建 Kruskal 重构树，一组必须取一个子树。

易证：重构树上一个子树内，任意两点存在**最大边 $\le$ 子树根权值的路径**。丢掉任意点，都可以和子树其它点产生非法边。

问题变为选 $k$ 个子树覆盖所有叶子方案数，设 $f_{u,k}$：**选 $k$ 个子树覆盖 $u$ 子树内所有叶子方案数**。$O(n^2)$ 树形 DP。

初始状态 $f_{u,1}=1$，**但条件是 $u$ 子树能被取**。什么时候 $u$ 子树不能被取呢？此时 $u$ 子树中存在两个叶子，它们边长超过了 $u$ 父亲的权值。由于权值单调，这个条件可以判断所有非法情况。

```cpp
using ll = long long;

const int N = 3e3 + 5;
const ll mod = 998244353;

int n,m,b[N][N],a[N],ft[N],lc[N],rc[N],g[N];
ll f[N][N];
vector<tuple<int,int,int>> E;
basic_string<int> P[N];

int fnd(int x){ return x == ft[x] ? x : ft[x] = fnd(ft[x]); }

void dfs(int u){
	f[u][1] = 1;
	if(u <= n) return P[u] = u,void();
	dfs(lc[u]),dfs(rc[u]);
	P[u] = P[lc[u]] + P[rc[u]];
	g[u] = max(g[lc[u]],g[rc[u]]);
	for(int x : P[lc[u]]) for(int y : P[rc[u]]) g[u] = max(g[u],b[x][y]);
	if(g[lc[u]] > a[u]) f[lc[u]][1] = 0;
	if(g[rc[u]] > a[u]) f[rc[u]][1] = 0;
	for(int i = 1;i <= P[lc[u]].size();++i)
		for(int j = 1;j <= P[rc[u]].size();++j)
			(f[u][i + j] += f[lc[u]][i] * f[rc[u]][j] % mod) %= mod;
}

int main(){
	n = m = read();
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j) E.emplace_back(b[i][j] = read(),i,j);
	ranges::sort(E);
	iota(ft,ft + N,0);
	for(auto[w,u,v] : E)
		if(w && (u = fnd(u)) != (v = fnd(v)))
			++m,a[ft[lc[m] = u] = ft[rc[m] = v] = m] = w;
	dfs(m);
	for(int i = 1;i <= n;++i) printf("%lld ",f[m][i]);
	return 0;
}
```

---

## 作者：piggy123 (赞：0)

你说得对，但是 $n\leq 1500$ 为什么要写 $\mathcal{O}(n^2)$？

关于组间边大于组内边的限制，我们考虑从小到大加边，那么一个时间点一个连通块合法当且仅当他是一个团。注意到最多有 $\mathcal{O}(n)$ 个合法的连通块，团一定包含于这些连通块中。而非常显然地，他们一定形成一个树状结构，所以我们可以在加边的同时把所有可能合法地连通块建立成一棵树，我们将题意转化为了选出树上若干个合法节点覆盖所有叶子的方案数。这个是简单树形 DP。

那么难点就在建树。我们注意到一个大小为 $x$ 的团一定有 $\frac{x(x-1)}{2}$ 条边，所以在并查集的同时维护连通块内部边数，当恰好达到这个值时，这个连通块合法。至于这棵树，我们额外对于每个连通块维护一个 bitset 表示这个连通块包含的集合。我们容易找到包含他的大小最小的集合作为他的父亲，总复杂度 $\mathcal{O}(\frac{n^3}{w})$，实际上这个瓶颈也很容易去掉，把 bitset 变为启发式合并即可。

---

## 作者：gdf_yhm (赞：0)

[CF1408G](https://www.luogu.com.cn/problem/CF1408G)

模拟赛 T2。

### 思路

从小到大加边，用并查集维护，记录当前联通块的点数 $siz_i$ 和边数 $num_i$。如果 $num_i=\frac{siz_i\times (siz_i-1)}{2}$ 说明当前联通块是一个合法的组。但是不好计数。

手玩发现，对于任意两个合法的组，他们要么相互包含要么相互不交。这说明我们可以自己给点定一个顺序使得一个组重排后是一个区间。这样设 $dp_{i,j}$ 表示重新排序后前 $i$ 个点有 $j$ 个组的方案数，把一段合法的区间放在最左边的点上，可以 dp。

先做一遍并查集，记录 $n-1$ 次合并前 $f_u$ 的值。从后往前遍历每次合并 $f_v=u$，将合并后所有 $f_x=u$ 的 $x$ 按合并前 $f_x=u$ 和 $f_x=v$ 将分为左右两边。再用新的 $id_u$ 做并查集，找到的合法的组都是区间。

复杂度 $O(n^2)$。

### code

```cpp
int n,a[maxn][maxn];
int f[maxn],siz[maxn],num[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
pii pos[maxn*maxn];
int lst[maxn][maxn],tp;
pii st[maxn];
int id[maxn],tmp[maxn],rnk[maxn];
vector<int> p[maxn];
int dp[maxn][maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a[i][j]=read();
		a[i][i]=inf;
	}
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)pos[a[i][j]]={i,j};
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n*(n-1)/2;i++){
		int u=pos[i].first,v=pos[i].second;
		u=fd(u),v=fd(v);
		if(u!=v){//O(n)
			st[++tp]={v,u};
			for(int j=1;j<=n;j++)lst[tp][j]=fd(j);
			f[v]=u;
		}
	}
	++tp;for(int j=1;j<=n;j++)lst[tp][j]=fd(j);
	for(int i=1;i<=n;i++)id[i]=i;
	for(int i=tp-1;i;i--){
		for(int j=1;j<=n;j++)tmp[j]=id[j];
		int l,r;
		// for(int j=1;j<=n;j++)cout<<id[j]<<" ";cout<<"\n";
		for(int j=1;j<=n;j++)if(lst[i+1][tmp[j]]==st[i].second){l=j;break;}
		for(int j=1;j<=n;j++)if(lst[i+1][tmp[j]]==st[i].second)r=j;
		// cout<<i<<" "<<st[i].first<<" "<<st[i].second<<" "<<l<<" "<<r<<"\n";
		int h=l;
		for(int j=l;j<=r;j++)if(lst[i][tmp[j]]==st[i].second)id[h++]=tmp[j];
		for(int j=l;j<=r;j++)if(lst[i][tmp[j]]==st[i].first)id[h++]=tmp[j];
	}
	// for(int i=1;i<=n;i++)cout<<id[i]<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)rnk[id[i]]=i;
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=1,num[i]=0,p[i].push_back(i);
	for(int i=1;i<=n*(n-1)/2;i++){
		int u=rnk[pos[i].first],v=rnk[pos[i].second];
		if(u>v)swap(u,v);
		u=fd(u),v=fd(v);
		if(u==v)num[u]++;
		else{
			f[v]=u;siz[u]+=siz[v];num[u]+=num[v]+1;
		}
		if(num[u]==siz[u]*(siz[u]-1)/2){
			// for(int j=1;j<=n;j++)cout<<fd(j)<<" ";cout<<"\n";
			// for(int j=u;j<=n+1;j++)if(fd(j)!=u){
				// p[u].push_back(j-1);
				// // cout<<u<<" "<<j-1<<"\n";
				// break;
			// }
			p[u].push_back(u+siz[u]-1);
		}
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)if(dp[i-1][j-1]){
			// cout<<i<<" "<<j<<" "<<dp[i-1][j-1]<<"\n";
			for(int k:p[i])(dp[k][j]+=dp[i-1][j-1])%=mod;//共 O(n^2)
		}
	}
	for(int i=1;i<=n;i++)printf("%lld ",dp[n][i]);
}
```

---

## 作者：_ajthreac_ (赞：0)

## 0.题意
给出一个无向完全图，边的权值是 $1\sim n(n-1)/2$ 的排列，对于每个 $k\in[1,n]$，求出将其分为 $k$ 组且组内的边权全部小于组间的边权。
## 1.解法
其实题意概括完了这题就快做出来了。

由于每一组内部都是一个团，我们可以从小到大加入边，一旦边数达到当前连通块所能包含的边数上限就可以把这个连通块划为一组。

这个时候显然是不能直接暴力指数 dp 的，我们考虑跟连通性有关的其他性质。这时我们惊奇地发现，**Kruskal 重构树**上的点就对应了加边过程中形成的连通块，此时只需要考虑树上的 dp。

而这个树上 dp 就是一个简单的背包，我们看子树内划分成了几组（其实划分的是子树内的叶子），然后对于可以自成一组的连通块 $+1$ 即可。
## 2.代码
瓶颈在于排序边的 $O(n^2\log n)$，不过由于边权是一个排列它显然可以优化成 $O(n^2)$。

核心代码：
```cpp
const int N=3010,p=998244353;
int n,a[N][N];
struct Edge {
  int u,v,w;
  Edge(int _u=0,int _v=0,int _w=0){
    u=_u,v=_v,w=_w;
  }
  bool operator < (const Edge &rhs)const{
    return w<rhs.w;
  }
}e[N*N];int cnt;
//Kruskal
int tot,l[N],r[N],siz[N],ec[N],fa[N],f[N][N];
bool ok[N];//can be a group
int F(int k){
  return fa[k]==k?k:fa[k]=F(fa[k]);
}
void DFS(int u){
  if(u<=n)return (void)(f[u][1]=1);
  DFS(l[u]),DFS(r[u]);
  for(rg int i=1;i<=siz[l[u]];i++){
    for(rg int j=1;j<=siz[r[u]];j++){
      (f[u][i+j]+=(LL)f[l[u]][i]*f[r[u]][j]%p)%=p;
    }
  }
  if(ok[u])(f[u][1]+=1)%=p;
}
int main(){
  Read(n);
  for(rg int i=1;i<n+n;i++)fa[i]=i,siz[i]=i<=n;
  for(rg int i=1;i<=n;i++){
    for(rg int j=1;j<=n;j++){
      Read(a[i][j]);
      if(i<j)e[++cnt]=Edge(i,j,a[i][j]);
    }
  }
  sort(e+1,e+1+cnt);
  for(rg int i=1,tot=n;i<=cnt;i++){
    int u=F(e[i].u),v=F(e[i].v);
    if(u!=v){
      tot++,l[tot]=u,r[tot]=v,fa[u]=fa[v]=tot;
      ec[tot]=ec[u]+ec[v]+1,siz[tot]=siz[u]+siz[v];
      if(ec[tot]==siz[tot]*(siz[tot]-1)/2)ok[tot]=1;
    }else {
      if(++ec[u]==siz[u]*(siz[u]-1)/2)ok[u]=1;
    }
  }
  int rt=n+n-1;DFS(rt);
  for(rg int i=1;i<=n;i++)printf("%d ",f[rt][i]);
  KafuuChino HotoKokoa
}


---

## 作者：tommymio (赞：0)

这个中文翻译它就非常的魔性，直接告诉了你这道题一半的做法。

> （对于每个组）组内边 $<$ 组外边

这样很容易可以想到，使用并查集维护连通块，从小到大加边，一旦当前的连通块形成了一个团就记录一下这个团。然后可以 $\text{DP}$ ，但是复杂度是指数级别的无法承受。

仔细想一想，我们可以在并查集 $\text{merge}$ 过程中，根据先后次序得到一个点编号的序列 $b$，每个团在这个序列上对应一个区间。

那么题目所求就变为给定一些区间，用这些区间中的 $k$ 个覆盖整个序列 $b$ 的方案数，可以 $\text{DP}$ 求解。设 $f_{i,j}$ 为序列中前 $i$ 个数使用 $j$ 个区间覆盖的方案数。

为了便于转移，对于每个 $l$ 记录其对应的 $r$，这显然是一个集合，然后刷表转移即可。或者对于每个 $r$ 记录其对应的 $l$，填表转移。

代码非常好写，就不贴了。


---

## 作者：Fuyuki (赞：0)

如果一个点集满足点集内两两连边的权值小于其他点与这个点集连的边，这个点集就可以被单独划分出来。

将所有边按权值从小到大加入，如果某个时刻形成了一个团，那么这个团就是可以单独划分出来的合法点集。

这个过程可以用并查集进行维护。如果假如一条边合并了两个连通块，那么就将其中一个连通块的点放在另一个连通块的左边。这样在所有边都处理完后，找到的所有合法团都是点序列上的一个区间。

设 $f_{i,j}$ 表示将点序列上前 $i$ 个点分成 $j$ 段的方案数，就可以直接转移了。

注意到合法团之间要么是不交，要么是真包含的关系，所以这些团的数量不超过 $2n-1$ 个。

那么总复杂度就为 $O(n^2)$，可以通过本题。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define I inline int
#define V inline void
#define P pair<int,int>
#define isnum(ch) ('0'<=ch&&ch<='9')
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define gc (_op==_ed&&(_ed=(_op=_buf)+fread(_buf,1,100000,stdin),_op==_ed)?EOF:*_op++)
char _buf[100000],*_op(_buf),*_ed(_buf);
I getint(){
	int _s=0,_f=1;char _ch=gc;
	while(!isnum(_ch))(_ch=='-')&&(_f=-1),_ch=gc;
	while(isnum(_ch))_s=_s*10+_ch-48,_ch=gc;
	return _s*_f;
}
const int N=2e3+1,mod=998244353;
P pos[N*N];
int n,m,tot;
vector<int>e[N];
int f[N][N],fa[N],id[N],tag[N];
int a[N][N],nxt[N],l[N],r[N],siz[N],cnt[N];
V check(int&x){x-=mod,x+=x>>31&mod;}
V input(){
	n=getint();
	FOR(i,1,n)FOR(j,1,n)a[i][j]=getint();
}
I find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
V merge(int x,int y){
	if((x=find(x))!=(y=find(y)))
		fa[y]=x,nxt[r[x]]=l[y],r[x]=r[y];
}
I C2(int x){return x*(x-1)/2;}
V init(){
	tot=C2(n),**f=1;
	FOR(i,1,n)FOR(j,i+1,n)pos[a[i][j]]=P(i,j);
	FOR(i,1,n)l[i]=i,r[i]=i,fa[i]=i;
	FOR(i,1,tot)merge(pos[i].first,pos[i].second);
	FOR(i,1,n)tag[nxt[i]]=1;
	FOR(i,1,n)if(!tag[i])id[m=1]=i;
	while(m<n)id[m+1]=nxt[id[m]],m++;
}
V link(int x,int y){
	if((x=find(x))!=(y=find(y)))
		fa[y]=x,r[x]=r[y],siz[x]+=siz[y],cnt[x]+=cnt[y];
	if(++cnt[x]==C2(siz[x]))e[l[x]].push_back(r[x]);
}
V work(){
	FOR(i,1,n)fa[i]=i,l[id[i]]=r[id[i]]=i;
	FOR(i,1,n)siz[i]=1,e[i].push_back(i);
	FOR(i,1,tot)link(pos[i].first,pos[i].second);
	FOR(u,1,n)FOR(i,0,n-1)if(f[u-1][i])for(int v:e[u])
		check(f[v][i+1]+=f[u-1][i]);
	FOR(i,1,n)cout<<f[n][i]<<' ';
		
}
int main(){
	input();
	init();
	work();
	return 0;
}

```

---

