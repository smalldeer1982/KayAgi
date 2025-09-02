# [HNOI/AHOI2018] 毒瘤

## 题目描述

从前有一名毒瘤。

毒瘤最近发现了量产毒瘤题的奥秘。考虑如下类型的数据结构题：给出一个数组，要求支持若干种奇奇怪怪的修改操作（比如区间加一个数，或者区间开平方），并支持询问区间和。毒瘤考虑了 $n$ 个这样的修改操作，并编号为 $1\sim n$。当毒瘤要出数据结构题的时候，他就将这些修改操作中选若干个出来，然后出成一道题。

当然了，这样出的题有可能不可做。通过精妙的数学推理，毒瘤揭露了这些修改操作的关系：有 $m$ 对“互相排斥”的修改操作，第 $i$ 对是第 $u_i$ 个操作和第 $v_i$ 个操作。当一道题同时含有 $u_i$ 和 $v_i$ 这两个操作时，这道题就会变得不可做。另一方面，一道题中不包含任何“互相排斥”的修改操作时，这个题就是可做的。此外，毒瘤还发现了一个规律：$m-n$ 是一个很小的数字，且任意两个修改操作都是连通的。两个修改操作 $a,b$ 是连通的，当且仅当存在若干操作 $t_0,t_1,\cdots,t_l$，使得 $t_0=a,t_l=b$，且对 $1\leq i\leq l$，$t_{i-1}$ 和 $t_i$ 都是“互相排斥”的修改操作。

一对“互相排斥”的修改操作称为互斥对。现在毒瘤想知道，给定值 $n$ 和 $m$ 个互斥对，他共能出出多少道可做的不同的数据结构题。两道数据结构题是不同的，当且仅当有一个修改操作在其中一道题中存在，而在另一道题中不存在。

## 说明/提示

#### 样例一说明

可做的题包括 $\varnothing,\{1\},\{2\},\{3\},\{1,3\}$。注意，**空集是合法的数据结构题**。

#### 数据范围

![](https://cdn.luogu.com.cn/upload/pic/17511.png)

## 样例 #1

### 输入

```
3 2
1 2
2 3```

### 输出

```
5```

## 样例 #2

### 输入

```
6 8
1 2
1 3
1 4
2 4
3 5
4 5
4 6
1 6```

### 输出

```
16```

## 样例 #3

### 输入

```
12 18
12 6
3 11
8 6
2 9
10 4
1 8
6 2
11 5
10 6
12 2
9 3
7 6
2 7
3 2
7 3
5 6
2 11
12 1```

### 输出

```
248```

# 题解

## 作者：Kelin (赞：39)

## [题意](https://blog.csdn.net/BeNoble_/article/details/80036891)

求一幅图的最大独立集方案数

$n\le10^5,$满足非树边$\le11$条

---

$AFO$之后这篇题解搁了好久$=.=$

---

## 题解

### $1.$考虑一棵树怎么做

和普通求独立集一样枚举这个点选不选然后用乘法原理计算即可

```
f[u][1]=f[u][1]*f[v][0];
f[u][0]=f[u][0]*(f[v][0]+f[v][1]);
```

### $2.$考虑怎么处理非树边

因为只有$11$条非树边$,$所以可以枚举这些边的两个端点的选择情况

可以发现只有$3$种情况$(1,0),(0,0),(0,1)$

但是实际上可以发现只需要枚举上面那个点选不选$,$即$(0,0)$和$(0,1)$可以合并起来

然后对于每一种状态再朴素做一遍树$DP$

复杂度$O(2^{m-n+1}n)$

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
template<class T>inline void we(T x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=1e5+5,P=998244353;
typedef int arr[N];
typedef long long ll;
struct eg{int nx,to;}e[N<<1];
int n,m,ans,dft,Cnt,f[N][2],fg[N][2];arr fi,fa,eu,ev,Mi,dfn,vis;
inline int pls(int a,int b){return a+=b,a<P?a:a-P;}
void dfs(int u){
    dfn[u]=++dft;
    go(u)if(v^fa[u]){
        if(!dfn[v])fa[v]=u,dfs(v);
        else if(dfn[u]<dfn[v])eu[++Cnt]=u,ev[Cnt]=v;
    }
}
void dp(int u){
    f[u][0]=!fg[u][1],f[u][1]=!fg[u][0],vis[u]=1;
    go(u)if(!vis[v]){
        dp(v);
        f[u][1]=(ll)f[u][1]*f[v][0]%P;
        f[u][0]=(ll)f[u][0]*(f[v][0]+f[v][1])%P;
    }
}
inline void add(int u,int v){static int ce=0;e[++ce]={fi[u],v},fi[u]=ce;}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    sd(n),sd(m);int u,v;
    fp(i,1,m)sd(u),sd(v),add(u,v),add(v,u);
    dfs(1);Mi[1]=1;fp(i,2,Cnt)Mi[i]=Mi[i-1]<<1;
    fp(s,0,(1<<Cnt)-1){
        fp(i,1,Cnt)
            if(s&Mi[i])fg[eu[i]][1]=fg[ev[i]][0]=1;
            else fg[eu[i]][0]=1;
        fp(i,1,n)vis[i]=0;dp(1);ans=pls(ans,pls(f[1][1],f[1][0]));
        fp(i,1,Cnt)
            if(s&Mi[i])fg[eu[i]][1]=fg[ev[i]][0]=0;
            else fg[eu[i]][0]=0;
    }
    printf("%d\n",ans);
return 0;
}
```

~~这样就可以拿到$75$分了~~

### $3.$考虑怎么优化

可以发现上面的~~暴力~~算法中有很多状态都是重复计算了的

我们把连有非树边的点当做关键点

因为每次影响$DP$值的就只有这些关键点

所以我们考虑建出这$22$个关键点的虚树

对于虚树上一条边$u\to v,dp$方程可以化为

$$f[u][0/1]=\prod k_{v,0/1,0}f[v][0]+k_{v,0/1,1}f[v][1]$$

可以发现每条边的系数是不会改变的

所以关键就在于怎么求出每一条边的系数

对于一条虚树边$u\to v,$将原树中$u\to v$的路径提出来

从$v$节点向上跳并暴力转移系数$,$若遇到分叉则额外转移上分叉处的系数

如果遇到一个新的关键点就重置系数

根据虚树的性质$,$一个分叉点要么是关键点要么子树里就一个关键点

可以发现这样转移的总复杂度是$O(n)$的

对于虚树上的边我们还是按照上面的想法枚举端点的情况

令$s=m-n+1,$那么复杂度就是$O(n+s2^s)$

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
template<class T>inline void we(T x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=1e5+15,P=998244353;
typedef int arr[N];
typedef long long ll;
struct eg{int nx,to;}e[N<<1];
int n,m,ans,dft,Cnt,f[N][2],p[N][2],fg[N][2];arr fi,fa,sz,eu,ev,Mi,dfn,vis,mark;
void dfs(int u){
    dfn[u]=++dft;
    go(u)if(v^fa[u]){
        if(!dfn[v])fa[v]=u,dfs(v),sz[u]+=sz[v];
        else{mark[u]=1;
            if(dfn[u]<dfn[v])eu[++Cnt]=u,ev[Cnt]=v;
        }
    }mark[u]|=sz[u]>=2;sz[u]=sz[u]||mark[u];
}
inline int pls(int a,int b){return a+=b,a<P?a:a-P;}
struct Coe{
    int x,y;
    inline Coe operator+(const Coe b){return{pls(x,b.x),pls(y,b.y)};}
    inline Coe operator*(const int b){return{int((ll)x*b%P),int((ll)y*b%P)};}
}k[N][2];
struct Vg{int nx,to;Coe a,b;}E[N];int Fi[N];
inline void ADD(int u,int v,Coe a,Coe b){static int ce=0;E[++ce]={Fi[u],v,a,b},Fi[u]=ce;}
int Vt(int u){
    p[u][0]=p[u][1]=1;vis[u]=1;int pos=0,w;
    go(u)if(!vis[v]){
        w=Vt(v);
        if(!w){
            p[u][1]=(ll)p[u][1]*p[v][0]%P;
            p[u][0]=(ll)p[u][0]*(p[v][0]+p[v][1])%P;
        }else if(mark[u])ADD(u,w,k[v][0]+k[v][1],k[v][0]);
        else k[u][1]=k[v][0],k[u][0]=k[v][0]+k[v][1],pos=w;
    }
    if(mark[u])k[u][0]={1,0},k[u][1]={0,1},pos=u;
    else k[u][0]=k[u][0]*p[u][0],k[u][1]=k[u][1]*p[u][1];
    return pos;
}
void dp(int u){
    f[u][0]=fg[u][1]?0:p[u][0],
    f[u][1]=fg[u][0]?0:p[u][1];
    for(int i=Fi[u],v=E[i].to;i;v=E[i=E[i].nx].to){
        dp(v);int p=f[v][0],q=f[v][1];
        f[u][0]=(ll)f[u][0]*((ll)E[i].a.x*p%P+(ll)E[i].a.y*q%P)%P;
        f[u][1]=(ll)f[u][1]*((ll)E[i].b.x*p%P+(ll)E[i].b.y*q%P)%P;
    }
}
inline void add(int u,int v){static int ce=0;e[++ce]={fi[u],v},fi[u]=ce;}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    sd(n),sd(m);int u,v;
    fp(i,1,m)sd(u),sd(v),add(u,v),add(v,u);
    dfs(1);mark[1]=1;
	Vt(1);Mi[1]=1;fp(i,2,Cnt)Mi[i]=Mi[i-1]<<1;
    fp(s,0,(1<<Cnt)-1){
        fp(i,1,Cnt)
            if(s&Mi[i])fg[eu[i]][1]=fg[ev[i]][0]=1;
            else fg[eu[i]][0]=1;
        dp(1);ans=pls(ans,pls(f[1][1],f[1][0]));
        fp(i,1,Cnt)
            if(s&Mi[i])fg[eu[i]][1]=fg[ev[i]][0]=0;
            else fg[eu[i]][0]=0;
    }
    printf("%d\n",ans);
return 0;
}
```

---

## 作者：Soulist (赞：24)

思路非常精妙的一道虚树题

简单题意：给一张图，求这张图上的独立集数量

对于一棵树的情况，可以设$dp_{u,0/1}$表示节点$u$选/不选的方案数

显然有：

$$dp_{u,0}=\prod (dp_{v,1}+dp_{v,0})$$

$$dp_{u,1}=\prod dp_{v,0}$$

接下来考虑非树边

正常$dp$的话那么转移应该是$O(n)$的

我们发现非树边很少，所以可以预处理出来，然后枚举其连接的两点之间的状态

不难发现状态只有如下三种：$(0,0),(0,1),(1,0)$

可以发现$(0,0)$和$(0,1)$可以合并

于是我们就只需要枚举所有的非树边其连接的$\rm dfn$较小的点的状态就可以了

复杂度$O(n*2^{11})$可以得到$75pts$的高分

接下来是一个很妙的做法：

我们可以考虑将所有非树边上的点拿下来建虚树

这应该是一个大小$\le(44+1)$的虚树

注意到，我们的$dp$转移本应如此：


$$dp_{u,0}=\prod (dp_{v,1}+dp_{v,0})$$

$$dp_{u,1}=\prod dp_{v,0}$$

但是放在虚树上这样显然是错的

我们发现虚树是维护了点之间的关系并构建了其$lca$，所以虚树上的点和其父亲两两之间是一条链的关系

我们仔细思考可以发现这个东西居然只是额外附带了一个系数而已...

不妨设虚树上的一条边$u,v$为$u->k_1->k_2...->k_r->v$，显然中间是没有其他关键点的

我们发现$v$对于$u$造成的贡献实际上是可以计算出来的

因为没有其他儿子，所以$k_r$本身的$dp$值可以计算出来，考虑$dp_{v,0}$对其造成的贡献，有：$dp_{k_r,1}*=dp_{v,0},dp_{k_r,0}*=(dp_{v,0}+dp_{v,1})$

$dp_{k_{r-1},1}*=dp_{k_r,0}$即$dp_{k_{r-1},1}*=(dp_{k_r,0}'*(dp_{v,0}+dp_{v,1}))$

$dp_{k_{r-1},0}*=(dp_{k_r,0}+dp_{k_r,1})$即$dp_{k_{r-1},0}*=(dp_{k_r,0}'*(dp_{v,0}+dp_{v,1})+dp_{k_r,1}'*dp_{v,0})$

好像这样类似下去这样的系数是可以预处理出来的欸欸欸？

于是我们可以把虚树上的转移式改成这样：

$$dp_{u,0}=\prod(k_{v,1->0}*dp_{v,1}+k_{v,0->0}*dp_{v,0})$$

$$dp_{u,1}=\prod(k_{v,1->1}*dp_{v,1}+k_{v,0->1}*dp_{v,0})$$

剩下的工作就是预处理系数了qwq

我们考虑如何求解系数，我们类比于上面展开那个式子的过程，将其中的$dp_{kr,0/1}'$换成到那个点时候的系数

就可以得到系数的递推式了，具体展开非常麻烦，就不写了

然后我们考虑在虚树上$dp$，仅仅给每个点额外附上一个系数就可以了吗？

当然是不行的，每个点的$dp$初值也不是我们一开始所说的$dp$值$1$了

所以我们还要对虚树上的每个点做$dp$以计算初值，不过这一步相对简单，因为仔细考虑我们会发现如果一个点的某棵子树内有被标记的点，那么显然这个子树会被表示成虚树上的一条边，系数已经计算出来了，所以我们实际上要处理的$dp$值只有那些子树内没有被标记点的$dp$值

一道虚树的题我硬生生写了$5kb$....汗，不亏是[毒瘤]


不过我的代码应该还比较清晰qwq

设$s=m-n+1$，尽管建树看似像遍历了$s$遍全树，但实际上只有一遍....

所以复杂度为$O(n+s*2^s)$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Next2( i, x ) for( register int i = fire[x]; i; i = p[i].next ) 
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long 
int gi() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int P = 998244353 ; 
const int N = 1e5 + 5 ;
const int M = 55 ; 
int dp[N][2], dfn[N], head[N], fire[N], Ans, n, m, cnt ;
int num, Cnt, Fr[N], Ed[N], vis[N], s[M], top, Rev[N][2] ; 
int Fa[N], Top[N], dep[N], sz[N], Son[N], k0[N][2], k1[N][2] ; 
struct E {
	int to, next ; 
} e[N * 2], p[N * 2] ;
void add( int x, int y ) {
	e[++ cnt] = (E){ y, head[x] }, head[x] = cnt , 
	e[++ cnt] = (E){ x, head[y] }, head[y] = cnt ; 
}
void add2( int x, int y ) {
	p[++ cnt] = (E){ y, fire[x] }, fire[x] = cnt ,
	p[++ cnt] = (E){ x, fire[y] }, fire[y] = cnt ;  
}
//建树 
inline void dfs( int x, int fa ) {
	dfn[x] = ++ num, Fa[x] = fa, dep[x] = dep[fa] + 1, sz[x] = 1 ; 
	Next( i, x ) {
		int v = e[i].to ; if( v == fa ) continue ; 
		if( !dfn[v] ) {
			dfs( v, x ), sz[x] += sz[v] ;
			if( sz[v] > sz[Son[x]] ) Son[x] = v ; 
		}
		else if( dfn[v] < dfn[x] ) Fr[++ Cnt] = v, Ed[Cnt] = x, vis[v] = vis[x] = 1 ; 
	}
}
inline void dfs2( int x, int high ) {
	Top[x] = high ; 
	if( Son[x] ) dfs2( Son[x], high ), vis[x] += vis[Son[x]] ;
	Next( i, x ) {
		int v = e[i].to ; if( v == Fa[x] || v == Son[x] ) continue ; 
		dfs2( v, v ), vis[x] += vis[v] ;
	}
}
int LCA( int x, int y ) {
	while( Top[x] != Top[y] ) {
		if( dep[Top[x]] < dep[Top[y]] ) swap( x, y ) ;
		x = Fa[Top[x]] ; 
	}
	return ( dep[x] > dep[y] ) ? y : x ; 
}
int K[50], tot ; 
bool cmp( int x, int y ) {
	return dfn[x] < dfn[y] ; 
}
inline void insert( int x ) {
	if( top == 1 && x != 1 ) { s[++ top] = x ; return ; }
	int lca = LCA( s[top], x ) ; if( lca == x ) return ; 
	while( top > 1 && dfn[lca] < dfn[s[top - 1]] ) add2( s[top - 1], s[top] ), -- top ;
	if( dfn[lca] < dfn[s[top]] ) add2( lca, s[top] ), -- top ;
	if( dfn[lca] > dfn[s[top]] ) s[++ top] = lca ; 
	s[++ top] = x ; 
}
//建立虚树 
void Maker() {
	cnt = 0 ;
	rep( i, 1, Cnt ) K[++ tot] = Fr[i], K[++ tot] = Ed[i] ; 
	sort( K + 1, K + tot + 1, cmp ) ; s[top = 1] = 1 ; 
	rep( i, 1, tot ) insert( K[i] ) ;
	while( top > 1 ) add2( s[top - 1], s[top] ), -- top ;
}
void init() {
	n = gi(), m = gi() ; 
	rep( i, 1, m ) add( gi(), gi() ) ; cnt = 0 ; 
	dfs( 1, 1 ), memset( head, 0, sizeof(head) ) ;
	rep( i, 1, n ) if( Fa[i] != i ) add( Fa[i], i ) ;
	dfs2( 1, 1 ), Maker() ; 
}
//辅助计算系数 
inline void DP( int x, int u ) {
	dp[x][1] = dp[x][0] = 1 ; 
	Next( i, x ) {
		int v = e[i].to ; if( v == Fa[x] || v == u ) continue ; 
		DP( v, x ), dp[x][1] *= dp[v][0], dp[x][1] %= P ;
		dp[x][0] *= ( dp[v][1] + dp[v][0] ), dp[x][0] %= P ; 
	}
}
//计算系数... 
inline void Get( int u, int fa ) {
	int v = u ; k0[u][0] = 1, k0[u][1] = 1, k1[u][0] = 1 ; 
	while( Fa[v] != fa ) {
		DP( Fa[v], v ) ; int r0 = k0[u][0], r1 = k0[u][1] ;
		k0[u][0] = ( dp[Fa[v]][0] * r0 + dp[Fa[v]][1] * k1[u][0] ) % P ;
		k0[u][1] = ( dp[Fa[v]][0] * r1 + dp[Fa[v]][1] * k1[u][1] ) % P ;
		k1[u][1] = dp[Fa[v]][0] * r1 % P, k1[u][0] = dp[Fa[v]][0] * r0 % P ;
		v = Fa[v] ; 
	}
}
//计算dp初值 
inline void Get_DP( int x, int fa ) {
	Rev[x][0] = Rev[x][1] = 1 ; 
	Next( i, x ) {
		int v = e[i].to ; if( v == fa || vis[v] ) continue ; 
		Get_DP( v, x ), Rev[x][0] *= ( Rev[v][0] + Rev[v][1] ), Rev[x][0] %= P ;
		Rev[x][1] *= Rev[v][0], Rev[x][1] %= P ;
	}
} 
//计算出每条边的系数，每个点的dp初值 
inline void dfs_init( int x, int fa ) {
	Get_DP( x, fa ), K[++ tot] = x ; 
	if( x != fa ) Get( x, fa ) ;
	Next2( i, x ) {
		int v = p[i].to ; if( v == fa ) continue ;
		dfs_init( v, x ) ; 
	}
}
//真正的dp，前面的都是预处理 
inline void Dp( int x, int fa ) {
	Next2( i, x ) {
		int v = p[i].to ; if( v == fa ) continue ; 
		Dp( v, x ) ; dp[x][0] *= ( k0[v][0] * dp[v][0] % P + k0[v][1] * dp[v][1] % P ), dp[x][0] %= P ;
		dp[x][1] *= ( k1[v][0] * dp[v][0] % P + k1[v][1] * dp[v][1] % P ), dp[x][1] %= P ;
	}
}
signed main()
{
	init(), tot = 0, dfs_init( 1, 1 ) ; 
	int maxn = ( 1 << Cnt ) - 1 ;
	rep( i, 0, maxn ) {
		rep( i, 1, tot ) dp[K[i]][0] = Rev[K[i]][0], dp[K[i]][1] = Rev[K[i]][1] ; 
		for( re int j = 1; j <= Cnt; ++ j ) {
			if( ( 1 << ( j - 1 ) ) & i ) dp[Fr[j]][0] = 0, dp[Ed[j]][1] = 0 ; 
			else dp[Fr[j]][1] = 0 ; 
		}
		Dp( 1, 1 ), Ans = ( Ans + dp[1][0] + dp[1][1] ) % P ;
	}
	printf("%d\n", Ans % P ) ;
	return 0;
}
```

---

## 作者：shadowice1984 (赞：16)

大家好我非常喜欢硬核数据结构，所以敲了个动态dp过了这题

可能常数有点丢人(其实就是树的点会跑200来ms)然后代码量似乎和很多人差不多？(4k左右)

这里强烈安利一下全局平衡二叉树这个动态dp的实现方式，这个算法有一个好处就是常数真的小，所以就算你胡乱实现也能过题(尽管这东西通常不是标算但是1e5内卡不住)比如今年noip的d2t3也能拿这个算法过掉(尽管并敲不出来)

________________________

### 前置知识：动态dp

不会这东西的可以出门左转你站模板区去学习一下

没准树剖也能过这题？

## 本题题解

题目意思简单易懂，给你一张连通图，求独立集的方案数，保证非树边最多11条

那么我们先不管非树边做一遍树形dp，设$dp(u,0/1)$表示当u选取或者不选取的时候,u的子树中的独立集方案数

那么转移方程当然十分的显然了，假设我们正在合并一条树边$(u,v)$并且u是v的父亲

$$dp(u,0)=dp(u,0)(dp(v,0)+dp(v,1))$$

$$dp(u,1)=dp(u,1)dp(v,0)$$

那么此时显然我们计数记多了，发现独立集限制(也就是非树边)最多有11条，因此我们可以$O(2^{11})$枚举一下到底打破了哪几个限制，然后用至少打破0个限制-至少打破1个限制+至少打破2个限制-至少打破3个限制....如此这般的容斥下来我们就可以得到答案了

假设我们已经钦定了一些非树边现在我们要全部打破这些限制

那这个操作实在是容易，钦定这些树边的端点全部出现在独立集中就行了，(而且似乎你也只能这么做)

接下来如果我们每次暴力跑个树形dp似乎复杂度有些捉急$O(2^{11}n)$
肯定是tle的

那么我们怎么办呢？

当然是动态dp大法啦~

来来来让我们把dp的转移写成轻重链剖分之后矩阵dp的形式

记

$$ldp(u,0)=\prod_{v \in u.lightson}dp(v,0)+dp(v,1)$$

$$ldp(u,1)=\prod_{v \in u.lightson}dp(v,0)$$

记$dp(i,0/1)$表示一条重链按照深度排序之后的第i大的点的dp值

则我们有

$$\begin{bmatrix} dp_{i-1,0} \\ dp_{i-1,1} \end{bmatrix} × \begin{bmatrix} ldp_{i,0} & ldp_{i,1} \\ ldp_{i,0} & 0 \end{bmatrix}=\begin{bmatrix} dp_{i,0} \\ dp_{i,1} \end{bmatrix}$$

这里的两个列向量其实是行向量，我主要是因为这样看起来比较爽才敲成这样的

那么我们采用全局平衡二叉树维护一下每条重链的矩阵连乘积就做完这题了？

不你忽略了一个问题……,在你跳跃全局平衡二叉树上的一条轻边的时候你需要在$ldp(fa(p),0/1)$中删掉$dp(p,0/1)$的值，换句话讲就是做除法,而显然这东西在$dp(p,0/1)$是0的时候是除不掉的……

那么怎么办呢？我们对于每一个$ldp(u,0/1)$如果他的值是0就额外记一下到底有几个0乘到了里面，这样我们就可以做除法了（因为我们只是想要删除一个值而不是真的做除法）

这样你就可以愉快的处理除0的问题了然后我们就可以大力的动态dp过了这题

只是需要注意一点朴素的枚举集合加动态dp的复杂度是$O(11×2^{11}log^2n+nlogn)$的可能常数不优秀就tle了……

没关系我们把枚举集合换成dfs然后这样的话我们总的修改量就是$O(2^{11})$级别的,然后这题简直随便过

如果你觉得撤销操作难写的话可以像我一样每个节点开一个栈专门用来回撤

然后这题就愉快的做完了~

上代码~

```C
// luogu-judger-enable-o2
#include<cstdio>
#include<algorithm>
using namespace std;const int N=1e5+10;typedef long long ll;const ll mod=998244353;
inline ll po(ll a,ll p){ll r=1;for(;p;p>>=1,a=a*a%mod)if(p&1)r=r*a%mod;return r;}
struct nod//用来做除法的结构体 
{
    ll v1;int c1;ll v2;int c2;
    inline void ins(const ll& t1,const ll& t2)
    {(v1*=(t1)?t1:1)%=mod;c1+=(t1==0);(v2*=(t2)?t2:1)%=mod;c2+=(t2==0);}
    inline void del(const ll& t1,const ll& t2)
    {
        (v1*=(t1)?po(t1,mod-2):1)%=mod;c1-=(t1==0);
        (v2*=(t2)?po(t2,mod-2):1)%=mod;c2-=(t2==0);
    }
};
struct mar//矩阵 
{
    ll mp[2][2];
    inline ll* operator [](const int& x){return mp[x];}
    friend mar operator *(mar a,mar b)
    {
        mar c;
        c[0][0]=((ll)a[0][0]*b[0][0]+(ll)a[0][1]*b[1][0])%mod;
        c[0][1]=((ll)a[0][0]*b[0][1]+(ll)a[0][1]*b[1][1])%mod;
        c[1][0]=((ll)a[1][0]*b[0][0]+(ll)a[1][1]*b[1][0])%mod;
        c[1][1]=((ll)a[1][0]*b[0][1]+(ll)a[1][1]*b[1][1])%mod;return c;
    }
    void operator =(const nod& b)
    {mp[1][0]=mp[0][0]=(b.c1)?0:b.v1;mp[0][1]=(b.c2)?0:b.v2;}
};
int v[2*N];int x[2*N];int ct;int al[N];int n;int m;ll ans;
int eu[22];int ev[22];int hd;int siz[N];int h[N];int mi[N];
inline void add(int u,int V){v[++ct]=V;x[ct]=al[u];al[u]=ct;}
struct bcj//智商不够数据结构来凑，随手敲了个并查集判非树边 
{
    int fa[N];
    inline int f(int x){return fa[x]=(x==fa[x])?x:f(fa[x]);}
    inline void u(int x,int y){fa[f(x)]=f(y);}
    inline void ih(){for(int i=1;i<=n;i++)fa[i]=i;}
    inline void ins(int U,int V)
    {if(f(U)==f(V))eu[++hd]=U,ev[hd]=V;else add(U,V),add(V,U),u(U,V);}
}ufs;
inline int dfs1(int u,int f)//轻重链剖分 
{
    for(int i=al[u];i;i=x[i])
        if(v[i]!=f)siz[u]+=dfs1(v[i],u),h[u]=(siz[h[u]]<siz[v[i]])?v[i]:h[u];return ++siz[u];
}
struct global_biased_tree//全局平衡二叉树 
{
    mar mul_bas[N][22];mar we_bas[N][22];nod ld_bas[N][22];int s[N][2];
    mar* nmul[N];mar* nwe[N];nod* nld[N];//为了写的爽每个点开了个指针模拟栈 
    int st[N];int tp;int wsiz[N];int rot;int fa[N];//define n连实现栈 
    # define mul(p) (*nmul[p])
    # define we(p) (*nwe[p])
    # define incm(p) (*(nmul[p]+1)=*nmul[p],++nmul[p])
    # define decm(p) (--nmul[p])
    # define incw(p) (*(nwe[p]+1)=*nwe[p],++nwe[p])
    # define decw(p) (--nwe[p])
    # define ld(p) (*nld[p])
    # define incl(p) (*(nld[p]+1)=*nld[p],++nld[p])
    # define decl(p) (--nld[p])
    inline void ud(int p){mul(p)=mul(s[p][0])*we(p)*mul(s[p][1]);}//更新 
    inline void ih()//初始化指针 
    {
        for(int i=0;i<=n;i++)nmul[i]=mul_bas[i];for(int i=0;i<=n;i++)nwe[i]=we_bas[i];
        for(int i=0;i<=n;i++)nld[i]=ld_bas[i];
        for(int i=0;i<=21;i++)mul_bas[0][i][0][0]=1,mul_bas[0][i][1][1]=1;
    }
    inline int sbuild(int l,int r)//每条重链建bst 
    {
        if(l>r)return 0;
        int mid=l;int sum=0;for(int i=l;i<=r;i++)sum+=wsiz[st[i]];
        for(int pre=0;(pre<<1)<sum;mid++)pre+=wsiz[st[mid]];mid--;
        s[st[mid]][0]=sbuild(l,mid-1);fa[s[st[mid]][0]]=st[mid];
        s[st[mid]][1]=sbuild(mid+1,r);fa[s[st[mid]][1]]=st[mid];ud(st[mid]);
        return st[mid];
    }
    inline int solve(int u,int f)//链分治 
    {
        for(int p=u,nf=f;p;nf=p,p=h[p])
        {
            wsiz[p]++;ld(p).v1++;ld(p).v2++;
            for(int j=al[p];j;j=x[j])
                if(v[j]!=h[p]&&v[j]!=nf)
                {
                    int ve=solve(v[j],p);fa[ve]=p;wsiz[p]+=siz[v[j]];
                    ld(p).ins((mul(ve)[0][0]+mul(ve)[0][1])%mod,mul(ve)[0][0]);
                }we(p)=ld(p);
        }tp=0;for(int p=u;p;p=h[p])st[++tp]=p;reverse(st+1,st+tp+1);return sbuild(1,tp);
    }
    inline void modify(int u)//修改 
    {
        incw(u);incl(u);ld(u).v1=0;we(u)=ld(u);
        for(int p=u;p;p=fa[p])
            if(fa[p]&&s[fa[p]][0]!=p&&s[fa[p]][1]!=p)
            {
                int f=fa[p];incw(f);incl(f);
                ld(f).del((mul(p)[0][0]+mul(p)[0][1])%mod,mul(p)[0][0]);incm(p),ud(p);
                ld(f).ins((mul(p)[0][0]+mul(p)[0][1])%mod,mul(p)[0][0]);we(f)=ld(f);
            }else incm(p),ud(p);
    }
    inline void undo(int u)//撤销 
    {
        decw(u);decl(u);
        for(int p=u;p;p=fa[p])
            if(fa[p]&&s[fa[p]][0]!=p&&s[fa[p]][1]!=p)decw(fa[p]),decl(fa[p]),decm(p);
            else decm(p);
    }
    inline ll calc(){return (mul(rot)[0][0]+mul(rot)[0][1])%mod;}
}gbt;
inline void dfs(int stp,int siz)//dfs+容斥 
{
    if(stp==hd+1)
    {
        if(siz&1)(ans+=mod-gbt.calc())%=mod;
        else (ans+=gbt.calc())%=mod;return;
    }dfs(stp+1,siz);
    if(!mi[eu[stp]]){mi[eu[stp]]=stp;gbt.modify(eu[stp]);}
    if(!mi[ev[stp]]){mi[ev[stp]]=stp;gbt.modify(ev[stp]);}
    dfs(stp+1,siz+1);
    if(mi[ev[stp]]==stp){mi[ev[stp]]=0;gbt.undo(ev[stp]);}
    if(mi[eu[stp]]==stp){mi[eu[stp]]=0;gbt.undo(eu[stp]);}
}
int main()
{
    scanf("%d%d",&n,&m);ufs.ih();
    for(int i=1,u,v;i<=m;i++)scanf("%d%d",&u,&v),ufs.ins(u,v);dfs1(1,0);
    gbt.ih();gbt.rot=gbt.solve(1,0);dfs(1,0);printf("%lld",ans);return 0;//拜拜程序~ 
}
```














---

## 作者：TernaryTree (赞：13)

非常好广义串并联图。虚树/no

根据经典结论，通过以下三个操作，最终得到的图的边数是 $|V|=2k,|E|=3k$ 级别的，其中 $k=m-n$。

- 消串联：选中一个度数为 $2$ 的点 $u$，设其连接的两个点分别为 $v_1,v_2$，将 $(u,v_1)(u,v_2)$ 删掉，再连接 $(v_1,v_2)$。
- 消并联：选中一对重边并删掉一条。
- 去断路：选中一个度数为 $1$ 的点 $u$，将 $u$ 与 $u$ 所连的唯一一条边删掉。

那么在这个题里面，可以发现 $2^{2(m-n)}$ 枚举的复杂度是完全可以接受的，于是考虑直接去动态在上述三个过程中维护答案。

在哪里维护答案呢？比较显然的是在边上的情况。对于一条边 $(u,v)$，这条边可以代表着一个子图及这个子图的两个端点 $u,v$。那么对于一条边记录以下四个值：

- 选 $u$ 选 $v$，$(u,v)$ 表示子图的独立集方案数
- 不选 $u$ 不选 $v$，$(u,v)$ 表示子图的独立集方案数
- 不选 $u$ 选 $v$，$(u,v)$ 表示子图的独立集方案数
- 选 $u$ 不选 $v$，$(u,v)$ 表示子图的独立集方案数

对于“消串联”操作，我们发现可以直接枚举 $u$ 是选还是不选，并对应加到 $(v_1,v_2)$ 的四个权值中。

对于“消并联”操作，我们发现实际上两条边的对应权值相互独立，于是四个值对应相乘即可。

问题来到了“去断路”操作，我们发现没办法直接统计答案，坏诶。于是考虑去给每个点一个权值，缩一个断路就相当于把这个断路表示的子图的贡献挂在了这个结点上。于是每个结点就有两个权值：$f_u,g_u$ 表示结点 $u$ 选/不选，被缩在这个点子图的方案数贡献。

那么这个时候，“去断路“操作就可以手推一下，本质是将 $u$ 的 $f,g$ 通过断路的边转移到 $v$ 的 $f,g$ 上。

这里还要注意一点，此时的“消串联”操作也发生了变化，因为中间点选还是不选又乘上了一个该点自己的系数，稍微修改一下转移即可。

统计答案直接枚举哪些点选了，将点的对应权值与边的对应权值乘起来，再累加到答案即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define umap unordered_map

using namespace std;

typedef pair<int, int> pii;
const int maxn = 2e6 + 10;
const int mod = 998244353;

struct edge {
	int u, v;
	int w[5] = {};
	edge() = default;
	edge(int u, int v, int a, int b, int c, int d): u(u), v(v) { w[1] = a, w[2] = b, w[3] = c, w[4] = d; }
	int& operator[] (int x) { return w[x]; }
};

int n, m, ans;
umap<int, edge> e[maxn]; 
edge ed[maxn];
int tot;
int deg[maxn];
int f[maxn], g[maxn];
int del[maxn];
int que[maxn], hd = 1, tl;
int id[maxn], cnt;
int pos[maxn];

void add_edge(int u, int v, int a, int b, int c, int d) {
	if (e[u].count(v)) {
		(e[u][v][1] *= a) %= mod;
		(e[u][v][2] *= b) %= mod;
		(e[u][v][3] *= c) %= mod;
		(e[u][v][4] *= d) %= mod;
	} else {
		edge cur = edge(u, v, a, b, c, d);
		e[u][v] = cur;
		deg[u]++;
	}
}

void del_edge(int u, int v) {
	e[u].erase(v);
	deg[u]--;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		add_edge(u, v, 0, 1, 1, 1);
		add_edge(v, u, 0, 1, 1, 1);
	}
	for (int i = 1; i <= n; i++) f[i] = g[i] = 1;
	for (int i = 1; i <= n; i++) if (deg[i] <= 2) que[++tl] = i;
	while (hd <= tl) {
		int u = que[hd++]; 
		if (!deg[u]) continue;
		if (deg[u] == 1) {
			edge i = e[u].begin()->second;
			int v = i.v;
			(f[v] *= (f[u] * i[1] % mod + g[u] * i[4] % mod) % mod) %= mod;
			(g[v] *= (f[u] * i[3] % mod + g[u] * i[2] % mod) % mod) %= mod;
			del[u] = true;
			del_edge(u, v), del_edge(v, u);
			if (deg[v] <= 2) que[++tl] = v;
		} else {
			edge i = e[u].begin()->second;
			edge j = next(e[u].begin())->second; 
			int v1 = i.v, v2 = j.v;
			swap(i[3], i[4]);
			edge cur = edge(v1, v2, 
				(i[1] * j[1] % mod * f[u] % mod + i[3] * j[4] % mod * g[u] % mod) % mod,
				(i[4] * j[3] % mod * f[u] % mod + i[2] * j[2] % mod * g[u] % mod) % mod,
				(i[1] * j[3] % mod * f[u] % mod + i[3] * j[2] % mod * g[u] % mod) % mod,
				(i[4] * j[1] % mod * f[u] % mod + i[2] * j[4] % mod * g[u] % mod) % mod
			);
			del[u] = true;
			del_edge(u, v1), del_edge(v1, u);
			del_edge(u, v2), del_edge(v2, u);
			add_edge(cur.u, cur.v, cur[1], cur[2], cur[3], cur[4]);
			add_edge(cur.v, cur.u, cur[1], cur[2], cur[4], cur[3]);
			if (deg[v1] <= 2) que[++tl] = v1;
			if (deg[v2] <= 2) que[++tl] = v2;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!del[i]) {
			id[++cnt] = i;
			pos[i] = cnt;
		}
	}
	for (int u = 1; u <= n; u++) {
		if (del[u]) continue;
		for (pair<int, edge> i : e[u]) if (u < i.second.v) ed[++tot] = i.second;
	}
	for (int S = 0; S < (1ll << cnt); S++) {
		int mul = 1;
		for (int i = 1; i <= cnt; i++) {
			if (S >> i - 1 & 1) (mul *= f[id[i]]) %= mod;
			else (mul *= g[id[i]]) %= mod;
		}
		for (int i = 1; i <= tot; i++) {
			int u = pos[ed[i].u], v = pos[ed[i].v];
			int p = S >> u - 1 & 1, q = S >> v - 1 & 1;
			if (p && q) (mul *= ed[i][1]) %= mod;
			else if (!p && !q) (mul *= ed[i][2]) %= mod;
			else if (p && !q) (mul *= ed[i][3]) %= mod;
			else (mul *= ed[i][4]) %= mod;
		}
		(ans += mul) %= mod;
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：dqa2022 (赞：11)

题意：给一张无向连通图，求其独立集个数。$n\leq 10^5, m-n\leq10$

求独立集个数，并且$m-n\le10$，很自然地往树上想。那么就是一个（生成）树上独立集个数问题，再特殊考虑一些边和点。树的独立集个数很好DP，设计状态强制子树根节点选/不选，不再赘述。

设$k=m-n+1$，则最直接的想法就是$O(3^k)$枚举特殊点的状态，然后再DP处理。另一个更好的想法是容斥，设$f(S)$表示“至少有集合$S$中的边两边的点冲突（即都选）”的方案数，$E'$表示非树边的集合，那么
$$ans=\sum_{S\subseteq E'} (-1)^{|S|}f(S).$$

这里的复杂度就降到了$O(2^k)$。下文讨论的做法均使用后者。

现在的任务就是加速一个带少量修改的DP的过程。这里提供两种思路。

## 思路一 虚树+树形DP
鉴于会被修改的点的个数是$O(k)$级别的，我们可以对其建出一棵虚树（这里不需要$O(k\log k)$建，$O(n)$dfs一遍建树即可）。

预处理时，

* 对于这棵虚树之外的点，我们可以直接dp。

* 对于这棵虚树之上并且被压缩的点，我们可以把答案表示成$a\times dp[s][0]+b\times dp[s][1]+c$，$s$表示虚树上该点下方的第一个点（显然唯一），维护这样的每个点的$a$、$b$和$c$即可。

* 对于这棵虚树之上并且没有被压缩的点，我们可以把其虚树之外的儿子先dp出来，和虚树有关的儿子先不管。

现在考虑每次修改后的DP，我们每次只会走到虚树上没有被压缩的点，此时枚举每个虚树上的儿子转移即可。

一个小技巧是可以把一个特殊点作为根，这样就不需要特殊考虑把根节点加入虚树了。

$O(n+k2^k)$

```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
using namespace std;
#define G getchar()
int read()
{
	int x=0; char ch=G;
	for (;!isdigit(ch);ch=G);
	for (;isdigit(ch);ch=G) x=(x<<3)+(x<<1)+(ch^48);
	return x;
}
typedef long long ll;
const int Mod=998244353;


int n,m,f[100010];
int dp[100010][2][3];
namespace V
{
	struct Edge{
		int to,nxt,v;
	}edge[1000];
	int cnt,last[100010];
	inline void addedge(int x,int y,int v)
	{
		edge[++cnt]=(Edge){y,last[x],v},last[x]=cnt;
	}
	void dfs3(int);
}
int find(int x)
{
	return f[x]?f[x]=find(f[x]):x;
}
struct Edge{
	int to,nxt;
}edge[200100];
int cnt=1,last[100010];
inline void addedge(int x,int y)
{
	edge[++cnt]=(Edge){y,last[x]},last[x]=cnt;
	edge[++cnt]=(Edge){x,last[y]},last[y]=cnt;
}
struct Rec{
	int u,v;
}rec[20]; int rectop;
int bin[40],bintop;

bool exst[100010],mrk[100010],mrk0[100010];
int rt[100010];
void dfs1(int cur,int fat)
{
	int exsttot=0;
	for (int i=last[cur];i;i=edge[i].nxt)
		if (edge[i].to^fat)
		{
			dfs1(edge[i].to,cur);
			exsttot+=exst[edge[i].to];
		}
	if (mrk0[cur]||exsttot>=2)
	{
		exst[cur]=mrk[cur]=true,rt[cur]=cur;
		for (int i=last[cur];i;i=edge[i].nxt)
			if (edge[i].to!=fat&&exst[edge[i].to])
				V::addedge(cur,rt[edge[i].to],edge[i].to);
	}
	else if (exsttot==1)
	{
		exst[cur]=true;
		for (int i=last[cur];i;i=edge[i].nxt)
			if (edge[i].to!=fat&&exst[edge[i].to])
			{
				rt[cur]=rt[edge[i].to]; break;
			}
	}
}
void dfs2(int cur,int fat)
{
	if (!exst[cur])
	{
		dp[cur][0][2]=dp[cur][1][2]=1;
		for (int i=last[cur];i;i=edge[i].nxt)
			if (edge[i].to!=fat)
			{
				dfs2(edge[i].to,cur);
				dp[cur][0][2]=1LL*dp[cur][0][2]*(dp[edge[i].to][0][2]+dp[edge[i].to][1][2])%Mod;
				dp[cur][1][2]=1LL*dp[cur][1][2]*dp[edge[i].to][0][2]%Mod;
			}
		return;
	}
	if (mrk[cur])
	{
		dp[cur][0][2]=dp[cur][1][2]=1;
		for (int i=last[cur];i;i=edge[i].nxt)
			if (edge[i].to!=fat&&!exst[edge[i].to])
			{
				dfs2(edge[i].to,cur);
				dp[cur][0][2]=1LL*dp[cur][0][2]*(dp[edge[i].to][0][2]+dp[edge[i].to][1][2])%Mod;
				dp[cur][1][2]=1LL*dp[cur][1][2]*dp[edge[i].to][0][2]%Mod;
			}
			else if (edge[i].to!=fat) dfs2(edge[i].to,cur);
		return;
	}
	int tmp0=1,tmp1=1,tmppos;
	for (int i=last[cur];i;i=edge[i].nxt)
		if (edge[i].to!=fat&&!exst[edge[i].to])
		{
			dfs2(edge[i].to,cur);
			tmp0=1LL*tmp0*(dp[edge[i].to][0][2]+dp[edge[i].to][1][2])%Mod;
			tmp1=1LL*tmp1*dp[edge[i].to][0][2]%Mod;
		}
		else if (edge[i].to!=fat) dfs2(edge[i].to,cur),tmppos=edge[i].to;
	int a,b,c,d,e,f;
	if (mrk[tmppos]) a=1,b=1,c=0,d=1,e=0,f=0;
	else a=(dp[tmppos][0][0]+dp[tmppos][1][0])%Mod,b=(dp[tmppos][0][1]+dp[tmppos][1][1])%Mod,c=(dp[tmppos][0][2]+dp[tmppos][1][2])%Mod,
		d=dp[tmppos][0][0],e=dp[tmppos][0][1],f=dp[tmppos][0][2];
	dp[cur][0][0]=1LL*tmp0*a%Mod,dp[cur][0][1]=1LL*tmp0*b%Mod,dp[cur][0][2]=1LL*tmp0*c%Mod;
	dp[cur][1][0]=1LL*tmp1*d%Mod,dp[cur][1][1]=1LL*tmp1*e%Mod,dp[cur][1][2]=1LL*tmp1*f%Mod;
}

int subdp[100010][2];
bool cond[100010];
void V::dfs3(int cur)
{
	subdp[cur][0]=dp[cur][0][2],subdp[cur][1]=dp[cur][1][2];
	for (int i=last[cur];i;i=edge[i].nxt)
	{
		dfs3(edge[i].to);
		if (edge[i].v==edge[i].to)
		{
			subdp[cur][0]=1LL*subdp[cur][0]*(subdp[edge[i].to][0]+subdp[edge[i].to][1])%Mod;
			subdp[cur][1]=1LL*subdp[cur][1]*subdp[edge[i].to][0]%Mod;
			continue;
		}
		subdp[cur][0]=subdp[cur][0]*(1LL*(dp[edge[i].v][0][0]+dp[edge[i].v][1][0])*subdp[edge[i].to][0]%Mod+
				1LL*(dp[edge[i].v][0][1]+dp[edge[i].v][1][1])*subdp[edge[i].to][1]%Mod+(dp[edge[i].v][0][2]+dp[edge[i].v][1][2]))%Mod;
		subdp[cur][1]=subdp[cur][1]*(1LL*dp[edge[i].v][0][0]*subdp[edge[i].to][0]%Mod+1LL*dp[edge[i].v][0][1]*subdp[edge[i].to][1]%Mod+
								dp[edge[i].v][0][2])%Mod;
	}
	if (cond[cur]) subdp[cur][0]=0;
}

int main()
{
	n=read(),m=read();
	for (int i=1,x,y,a,b;i<=m;i++)
	{
		x=read(),y=read();
		if ((a=find(x))^(b=find(y))) f[b]=a,addedge(x,y);
		else rec[++rectop]=(Rec){x,y},bin[++bintop]=x,bin[++bintop]=y;
	}
	sort(bin+1,bin+bintop+1);
	bintop=unique(bin+1,bin+bintop+1)-bin-1;
	for (int i=1;i<=bintop;i++) mrk0[bin[i]]=true;
	int RT=(rectop?rec[1].u:1);
	dfs1(RT,0);
	dfs2(RT,0);
	if (m==n-1) return printf("%d\n",(dp[RT][0][2]+dp[RT][1][2])%Mod),0;
	int ans=0;
	for (int i=0;i<(1<<m-n+1);i++)
	{
		int tot=0;
		for (int j=1;j<=m-n+1;j++) tot+=((i>>j-1)&1);
		tot=(tot&1?-1:1);
		for (int j=1;j<=bintop;j++) cond[bin[j]]=false;
		for (int j=1;j<=m-n+1;j++) if ((i>>j-1)&1) cond[rec[j].u]=cond[rec[j].v]=true;
		V::dfs3(RT);
		ans=(ans+tot*(subdp[RT][0]+subdp[RT][1])%Mod)%Mod;
	}
	printf("%d\n",(ans+Mod)%Mod)%Mod;
	return 0;
}

```


## 思路二 动态DP
“现在的任务就是加速一个带少量修改的DP的过程”，这是一个动态DP问题，直接树剖+线段树或者使用全局平衡二叉树即可。该做法能解决的问题就不只局限于可能被修改的点很少的情况了。

注意在动态DP的时候可能会乘上一个0或者撤回乘上一个0，鉴于0没有逆元，可以记一下乘上了几个0，对于0就直接在该标记处加加减减就行了。

一个小技巧是容斥的时候可以更改一下顺序，可以构造一个相邻两个数二进制只差一位的$[0,2^k)$的排列，这样每次修改就只有$O(1)$次了。具体方法是倍增，每次把已经构造出的$[0,2^{i-1})$的序列复制一遍，最高位全部加上一个1，,顺序翻转过来接到末尾。当然直接dfs也可以做到相同的复杂度。

$O(n\omega^3\log n+2^k(k+ (\log Mod+\omega^3)\log n))$，$\omega=2$为矩阵大小。

```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
using namespace std;
#define G getchar()
int read()
{
	int x=0; char ch=G;
	for (;!isdigit(ch);ch=G);
	for (;isdigit(ch);ch=G) x=(x<<3)+(x<<1)+(ch^48);
	return x;
}
typedef long long ll;
const int Mod=998244353;
int qpow(int x,int y)
{
	int res=1;
	for (;y;y>>=1,x=1LL*x*x%Mod)
		if (y&1) res=1LL*res*x%Mod;
	return res;
}

int n,m;
int f[100010];
int find(int x)
{
	return f[x]?f[x]=find(f[x]):x;
}
struct Edge{
	int to,nxt;
}edge[200010];
int cnt=1,last[100010];
inline void addedge(int x,int y)
{
	edge[++cnt]=(Edge){y,last[x]},last[x]=cnt;
	edge[++cnt]=(Edge){x,last[y]},last[y]=cnt;
}
int fat[100010],son[100010],siz[100010];
void dfs1(int cur,int fat)
{
	::fat[cur]=fat; siz[cur]=1;
	for (int i=last[cur];i;i=edge[i].nxt)
		if (edge[i].to^fat)
		{
			dfs1(edge[i].to,cur);
			siz[cur]+=siz[edge[i].to];
			if (!son[cur]||siz[edge[i].to]>siz[son[cur]]) son[cur]=edge[i].to;
		}
}
struct Num{
	int val,ztot;
}g[100010][2];
Num operator*(Num x,Num y)
{
	return (Num){1LL*x.val*y.val%Mod,x.ztot+y.ztot};
}
Num operator/(Num x,Num y)
{
	return (Num){y.val==1?x.val:1LL*x.val*qpow(y.val,Mod-2)%Mod,x.ztot-y.ztot};
}
struct Matrix{
	int mp[2][2];
};
Matrix operator*(Matrix x,Matrix y)
{
	Matrix res;
	res.mp[0][0]=(1LL*x.mp[0][0]*y.mp[0][0]+1LL*x.mp[0][1]*y.mp[1][0])%Mod;
	res.mp[0][1]=(1LL*x.mp[0][0]*y.mp[0][1]+1LL*x.mp[0][1]*y.mp[1][1])%Mod;
	res.mp[1][0]=(1LL*x.mp[1][0]*y.mp[0][0]+1LL*x.mp[1][1]*y.mp[1][0])%Mod;
	res.mp[1][1]=(1LL*x.mp[1][0]*y.mp[0][1]+1LL*x.mp[1][1]*y.mp[1][1])%Mod;
	return res;
}
struct Node{
	Matrix val,sum;
	int lson,rson,fat;
}node[100010];
int seq[100010]; int seqtot;
bool isroot(int cur)
{
	return node[node[cur].fat].lson!=cur&&node[node[cur].fat].rson!=cur;
}
void pushup(int cur)
{
	if (node[cur].rson) node[cur].sum=node[node[cur].rson].sum*node[cur].val;
	else node[cur].sum=node[cur].val;
	if (node[cur].lson) node[cur].sum=node[cur].sum*node[node[cur].lson].sum;
}
int build(int l,int r)
{
	int siztot=0;
	for (int i=l;i<=r;i++) siztot+=siz[seq[i]];
	int sizl=0;
	for (int i=l;i<=r;i++)
	{
		sizl+=siz[seq[i]];
		if ((sizl<<1)>=siztot)
		{
			int ls,rs;
			if (l<i) ls=build(l,i-1),node[seq[i]].lson=ls,node[ls].fat=seq[i];
			if (i<r) rs=build(i+1,r),node[seq[i]].rson=rs,node[rs].fat=seq[i];
			pushup(seq[i]);
			return seq[i];
		}
	}
}
int dfs2(int cur)
{
	for (int i=cur;i;i=son[i])
	{
		g[i][0]=g[i][1]=(Num){1,0};
		for (int j=last[i];j;j=edge[j].nxt)
			if (edge[j].to!=fat[i]&&edge[j].to!=son[i])
			{
				int t=dfs2(edge[j].to);
				node[t].fat=i;
				int tmp=node[t].sum.mp[0][0];
				g[i][1]=g[i][1]*(tmp?(Num){tmp,0}:(Num){1,1});
				tmp=(node[t].sum.mp[0][0]+node[t].sum.mp[0][1])%Mod;
				g[i][0]=g[i][0]*(tmp?(Num){tmp,0}:(Num){1,1});
			}
		int a=(g[i][0].ztot?0:g[i][0].val),b=(g[i][1].ztot?0:g[i][1].val);
		node[i].val=(Matrix){{{a,b},{a,0}}};
	}
	seqtot=0;
	for (int i=cur;i;i=son[i]) seq[++seqtot]=i,siz[i]-=siz[son[i]];
	return build(1,seqtot);
}
bool cond[100010]; int covertot[100010];
void modify(int x,bool y)
{
	if (cond[x]==y) return;
	cond[x]=y;
	int a=(g[x][0].ztot?0:g[x][0].val),b=(g[x][1].ztot?0:g[x][1].val);
	if (y) node[x].val=(Matrix){{{0,b},{0,0}}};
	else node[x].val=(Matrix){{{a,b},{a,0}}};
	for (int i=x;i;i=node[i].fat)
		if (isroot(i)&&node[i].fat)
		{
			int t=node[i].fat;
			a=node[i].sum.mp[0][0],b=(node[i].sum.mp[0][0]+node[i].sum.mp[0][1])%Mod;
			g[t][0]=g[t][0]/(b?(Num){b,0}:(Num){1,1});
			g[t][1]=g[t][1]/(a?(Num){a,0}:(Num){1,1});
			pushup(i);
			a=node[i].sum.mp[0][0],b=(node[i].sum.mp[0][0]+node[i].sum.mp[0][1])%Mod;
			g[node[i].fat][0]=g[node[i].fat][0]*(b?(Num){b,0}:(Num){1,1});
			g[node[i].fat][1]=g[node[i].fat][1]*(a?(Num){a,0}:(Num){1,1});
			
			a=(g[t][0].ztot?0:g[t][0].val),b=(g[t][1].ztot?0:g[t][1].val);
			if (cond[t]) node[t].val=(Matrix){{{0,b},{0,0}}};
			else node[t].val=(Matrix){{{a,b},{a,0}}};
		}
		else pushup(i);
}
struct Rec{
	int u,v;
}rec[100]; int rectop;
int bin[100]; int bintop;

int main()
{
	n=read(),m=read();
	for (int i=1,x,y,a,b;i<=m;i++)
	{
		x=read(),y=read();
		if ((a=find(x))^(b=find(y))) f[b]=a,addedge(x,y);
		else rec[++rectop]=(Rec){x,y},bin[++bintop]=x,bin[++bintop]=y;
	}
	sort(bin+1,bin+bintop+1);
	bintop=unique(bin+1,bin+bintop+1)-bin-1;
	dfs1(1,0); int rt=dfs2(1);
	int k=m-n+1;
	seqtot=0; seq[seqtot++]=0;
	for (int i=1;i<=k;i++)
	{
		for (int j=(1<<i-1)-1;j>=0;j--)
			seq[seqtot++]=seq[j]|(1<<i-1);
	}
	int ans=(node[rt].sum.mp[0][0]+node[rt].sum.mp[0][1])%Mod;
	for (int i=1,kk=-1;i<seqtot;i++,kk=-kk)
	{
		int pos; bool cnd;
		for (int j=1;j<=k;j++) if ((seq[i-1]^seq[i])==(1<<j-1)){pos=j,cnd=(seq[i]>>j-1)&1;break;}
		if (cnd) covertot[rec[pos].u]++,covertot[rec[pos].v]++;
		else covertot[rec[pos].u]--,covertot[rec[pos].v]--;
		modify(rec[pos].u,covertot[rec[pos].u]);
		modify(rec[pos].v,covertot[rec[pos].v]);
		ans=(ans+kk*(node[rt].sum.mp[0][0]+node[rt].sum.mp[0][1])%Mod)%Mod;
	}
	printf("%d\n",(ans+Mod)%Mod);
	return 0;
}
```

***
请批评指正！

---

## 作者：木xx木大 (赞：8)

[P4426 [HNOI/AHOI2018]毒瘤](https://www.luogu.com.cn/problem/P4426)

这题和它的名字一样毒瘤！~~这直接导致了我失去了一晚上的快乐颓废时光~~

一句话题意：求一幅图的独立集方案数。

**暴力：**

首先考虑树上怎么做。设 $dp[u][0/1]$ 表示不选/选 $u$ 的方案数，根据乘法原理，dp 方程显然：
$$
dp[u][0]=\prod  (dp[v][1]+dp[v][0])\\dp[u][1]=\prod dp[v][0]
$$
发现 $m-n$ 很小，我们暴力枚举非树边可能的情况，即$(1,0),(0,0),(0,1)$。发现后两种情况可以合并为一种。于是我们就得到了一个 $O(2^{m-n+1}n)$ 的做法。可以得 75pts，代码非常好写。（听说极致卡常的话能过？）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace FGF
{
	int n,m;
	const int N=1e5+5,mo=998244353;
	int dfn[N],num,eu[N],ev[N],tot,dp[N][2],op[N][2],ans;
	bool vis[N];
	vector<int> g[N];
	int read()
	{
		int s=0;char ch=getchar();
		while(!isdigit(ch))ch=getchar();
		while(isdigit(ch))s=s*10+ch-'0',ch=getchar();
		return s;
	}
	void dfs1(const int &u,const int &f)
	{
		dfn[u]=++num;
		for(auto v:g[u])
		{
			if(v==f)continue;
			if(!dfn[v])dfs1(v,u);
			else if(dfn[u]<dfn[v])eu[tot]=u,ev[tot++]=v;
		}
	}
	void getdp(const int &u)
	{
		dp[u][0]=!op[u][1],dp[u][1]=!op[u][0],vis[u]=1;
		for(auto v:g[u])		
		{
			if(vis[v])continue;
			getdp(v);
			dp[u][0]=1ll*dp[u][0]*(dp[v][0]+dp[v][1])%mo;
			dp[u][1]=1ll*dp[u][1]*dp[v][0]%mo;
		}
	}
	void work()
	{
		n=read(),m=read();
		for(int i=1,u,v;i<=m;i++)
		{
			u=read(),v=read();
			g[u].push_back(v),g[v].push_back(u);
		}
		dfs1(1,0);
		for(int i=0;i<(1<<tot);i++)
		{
			for(int j=0;j<tot;j++)
				if((i>>j)&1)op[eu[j]][1]=op[ev[j]][0]=1;
					else op[eu[j]][0]=1;
			getdp(1);
			memset(vis,0,sizeof(bool[n+1]));
			ans=(1ll*ans+dp[1][0]+dp[1][1])%mo;
			for(int j=0;j<tot;j++)
				if((i>>j)&1)op[eu[j]][1]=op[ev[j]][0]=0;
					else op[eu[j]][0]=0;
		}
		printf("%d",ans);
	}
}
int main()
{
	FGF::work();
	return 0;
}
```

**正解**

发现每次状态变化的只有非树边涉及的点，这样的点点数很少。对这些点建**虚树**。考虑虚树上的父子之间怎么转移。对于一条 $u\to x_1\to x_2\to\dots x_k \to v$，有转移

$dp[x_k][0]=dp'[x_k][0]\times (dp[v][1]+dp[v][0]),dp[x_k][1]=dp'[x_k][1]\times dp[v][0]$

$dp[x_{k-1}][0]=dp'[x_{k-1}][0]\times (dp[x_k][1]+dp[x_k][0])=dp'[x_{k-1}][0]\times (dp'[x_k][1]\times dp[v][0]+dp'[x_k][0]\times (dp[v][1]+dp[v][0])),\\dp[x_{k-1}][1]=dp'[x_{k-1}][1]\times dp[x_k][0]=dp'[x_{k-1}][1]\times dp'[x_k][0]\times (dp[v][1]+dp[v][0])$

依次类推，转移方程可以化为 $dp[u][0/1]=\prod (k[0/1][0]dp[v][0]+k[0/1][1]dp[v][1])$。我们只需要求出转移系数 $k$ 即可。 $k$ 的转移和原来的 dp 式子基本相同，但需要在 $u$ 为关键点时重置且需要统计分叉的贡献（即上面的 $dp'$）。除此之外，在虚树上 dp 时 $dp[u]$ 的初始值不再是 1 ，还需要预处理出 dp 的初始值。

复杂度为 $O(n+2^{m-n+1}(m-n+1))$

感觉还是有一定实现上的难度的，代码一定程度上参考了第一篇题解。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace FGF
{
	int n,m;
	const int N=1e5+5,mo=998244353;
	int siz[N],dfn[N],num,eu[N],ev[N],tot,dp[N][2],p[N][2],op[N][2],ans;
	bool vis[N],is[N];
	vector<int> g[N];
	struct Node{
		int x,y;
		Node(){}
		Node(int xx,int yy):x(xx),y(yy){};
	}k[N][2];
	Node operator +(Node a,Node b){return Node((a.x+b.x)%mo,(a.y+b.y)%mo);}
	Node operator *(Node a,int b){return Node(1ll*a.x*b%mo,1ll*a.y*b%mo);}
	struct edg{
		int to,nxt;Node a,b;
	}e[N<<1];
	int cnt,head[N];
	void add(int u,int v,Node a,Node b)
	{
		cnt++;
		e[cnt].to=v;
		e[cnt].nxt=head[u];
		head[u]=cnt;
		e[cnt].a=a,e[cnt].b=b;
	}
	void dfs1(int u,int f) 
	{
		dfn[u]=++num;
		for(auto v:g[u])
		{
			if(v==f)continue;
			if(!dfn[v])dfs1(v,u),siz[u]+=siz[v];
			else
			{
				is[u]=1;//把虚树上的点标起来 
				if(dfn[u]<dfn[v])eu[tot]=u,ev[tot++]=v;//记录非树边 
			}
		}
		is[u]|=siz[u]>=2;
		siz[u]=siz[u]||is[u];
	}
	int predp(int u)
	{
		vis[u]=1;
		p[u][0]=p[u][1]=1;//初始dp值 
		int pos=0,x;
		for(auto v:g[u])
		{
			if(vis[v])continue;
			x=predp(v);//原树子树内离自己最近的虚树上的点 
			if(!x)p[u][0]=1ll*p[u][0]*(p[v][0]+p[v][1])%mo,p[u][1]=1ll*p[u][1]*p[v][0]%mo;
			else if(is[u])add(u,x,k[v][1]+k[v][0],k[v][0]);
			else k[u][1]=k[v][0],k[u][0]=k[v][1]+k[v][0],pos=x;
		}
		if(is[u])k[u][0]={1,0},k[u][1]={0,1},pos=u;//这里k[u][0]={1,0}是因为初始k[u][0]+k[u][1]={1,1} 
		else k[u][0]=k[u][0]*p[u][0],k[u][1]=k[u][1]*p[u][1];
		return pos;
	}
	void getdp(int u)
	{
		dp[u][0]=(op[u][1]^1)*p[u][0],dp[u][1]=(op[u][0]^1)*p[u][1];
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			getdp(v);
			dp[u][0]=1ll*dp[u][0]*((1ll*e[i].a.x*dp[v][0]%mo+1ll*e[i].a.y*dp[v][1]%mo)%mo)%mo;
			dp[u][1]=1ll*dp[u][1]*((1ll*e[i].b.x*dp[v][0]%mo+1ll*e[i].b.y*dp[v][1]%mo)%mo)%mo;
		}
	}
	void work()
	{
		scanf("%d%d",&n,&m);
		for(int i=1,u,v;i<=m;i++)
		{
			scanf("%d%d",&u,&v);
			g[u].push_back(v),g[v].push_back(u);
		}
		dfs1(1,0);is[1]=1;
		predp(1);
		for(int i=0;i<(1<<tot);i++)
		{
			for(int j=0;j<tot;j++)
				if((i>>j)&1)op[eu[j]][1]=op[ev[j]][0]=1;//op:强制选某一种情况 
					else op[eu[j]][0]=1;
			getdp(1);
			ans=(1ll*ans+dp[1][0]+dp[1][1])%mo;
			for(int j=0;j<tot;j++)
				if((i>>j)&1)op[eu[j]][1]=op[ev[j]][0]=0;
					else op[eu[j]][0]=0;
		}
		printf("%d",ans);
	}
}
int main()
{
	FGF::work();
	return 0;
}
```


---

## 作者：litble (赞：7)

# 题目分析

[你真的不想来可爱的我的博客里瞅一眼吗？](https://blog.csdn.net/litble/article/details/80437073)

这是一道虽然不是数据结构，但也足够毒瘤了的毒瘤题。

原图应该是一棵树+若干非树边，题意转化为求独立集数量。

先考虑暴力做法，对于与非树边相连的点，我们暴力枚举它是选，还是不选。然后再跑一遍树形dp统计答案，方程显而易见：

`f[x][0]=f[x][0]*(f[son][0]+f[son[1]);`

`f[x][1]=f[x][1]*f[son][0];`

当然这个做法还是可以用容斥优化的，这样你就可以拿到70~80分的好分数，虽然划算但这并不是我们的重点。

那么有没有什么优美一点的做法呢？考虑我们dp的时候可以不整棵树弄一次，而是只把那些与非树边相连的点拿出来弄一弄.......让我们来建虚树吧！

那么建出虚树后，要怎么快速dp呢？

假设在虚树上有两个点x,y，y是x的父亲。在原树上，y的儿子是t,并且存在:

`f[t][0]=k0[x][0]*f[x][0]+k1[x][0]*f[x][1];`

`f[t][1]=k0[x][1]*f[x][0]+k1[x][1]*f[x][1];`

那么假设除去t这棵子树的贡献后，f(y,0)和f(y,1)分别记为orz(y,0),orz(y,1),就有：

`f[y][0]=orz[y][0]*(k0[x][0]+k0[x][1])*f[x][0]+orz[y][0]*(k1[x][0]+k1[x][1])*f[x][1]);`

`f[y][1]=orz[y][1]*k0[x][0]*f[x][0]+orz[y][1]*k1[x][0]*f[x][1];`

由此可见，k0和k1是可以进行dp的。我们可以做一次预处理，在不考虑以虚树点为根的子树的前提下弄出orz，然后再对k0和k1进行dp，最后求出来。

然后枚举所有与非树边相连的点是选还是不选，然后在虚树上dp，每次dp到y时，可以O(1)求出f(t,0)和f(t,1)，就可以愉♂快地dp啦！

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int q=0;char ch=' ';
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
	return q;
}
#define RI register int
const int mod=998244353,N=100020;
int n,m,now,K,js,top,ans;
int fa[N][17],dep[N],pos[N],vis[N],u[20],v[20],eno[N<<1];
struct tree{
	int tot,h[N],ne[N<<1],to[N<<1];
	void add(int x,int y) {to[++tot]=y,ne[tot]=h[x],h[x]=tot;}
}T1,T2;

void dfs(int x,int las) {
	pos[x]=++now,dep[x]=dep[las]+1,fa[x][0]=las,vis[x]=1;
	for(RI i=1;i<=16;++i) fa[x][i]=fa[fa[x][i-1]][i-1];
	for(RI i=T1.h[x];i;i=T1.ne[i])
		if(T1.to[i]!=las) {
			if(!vis[T1.to[i]]) dfs(T1.to[i],x);
			else ++K,u[K]=x,v[K]=T1.to[i],eno[i]=eno[i^1]=1;
		}
}
int lca(int x,int y) {
	if(dep[x]<dep[y]) swap(x,y);
	for(RI i=16;i>=0;--i) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if(x==y) return x;
	for(RI i=16;i>=0;--i)
		if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int inT2[N],st[100],p[100];
bool cmp(int x,int y) {return pos[x]<pos[y];}
void buildT2() {//建虚树
	for(RI i=1;i<=K;++i) {
		if(!inT2[u[i]]) inT2[u[i]]=1,p[++js]=u[i];
		if(!inT2[v[i]]) inT2[v[i]]=1,p[++js]=v[i];
	}
	sort(p+1,p+1+js,cmp);
	if(!inT2[1]) inT2[1]=1,st[++top]=1;
	for(RI i=1;i<=js;++i) {
		int x=p[i],o=0;
		while(top) {
			o=lca(st[top],x);
			if(top>1&&dep[st[top-1]]>dep[o]) T2.add(st[top-1],st[top]),--top;
			else if(dep[st[top]]>dep[o]) {inT2[o]=1,T2.add(o,st[top]),--top;break;}
			else break;
		}
		if(st[top]!=o) inT2[o]=1,st[++top]=o;
		st[++top]=x;
	}
	while(top>1) T2.add(st[top-1],st[top]),--top;
}

int f[N][2],k0[N][2],k1[N][2],g[N][2],bin[25],bj[N];
void predp(int x,int no) {//进行暴力算法中的dp，但是以no为根的子树不考虑
	f[x][0]=f[x][1]=1,inT2[x]=1;
	for(RI i=T1.h[x];i;i=T1.ne[i]) {
		if(T1.to[i]==fa[x][0]||T1.to[i]==no||inT2[T1.to[i]]||eno[i]) continue;
		predp(T1.to[i],no);
		f[x][0]=1LL*f[x][0]*(f[T1.to[i]][0]+f[T1.to[i]][1])%mod;
		f[x][1]=1LL*f[x][1]*f[T1.to[i]][0]%mod;
	}
}
void getk(int x,int y) {//获得k0,k1的值
	k0[x][0]=1,k1[x][1]=1;
	for(RI i=x;fa[i][0]!=y;i=fa[i][0]) {
		predp(fa[i][0],i);
		int t0=k0[x][0],t1=k1[x][0];
		k0[x][0]=1LL*f[fa[i][0]][0]*(k0[x][0]+k0[x][1])%mod;
		k1[x][0]=1LL*f[fa[i][0]][0]*(k1[x][0]+k1[x][1])%mod;
		k0[x][1]=1LL*f[fa[i][0]][1]*t0%mod;
		k1[x][1]=1LL*f[fa[i][0]][1]*t1%mod;
	}
}
void prework(int x) {//预处理
	for(RI i=T2.h[x];i;i=T2.ne[i]) prework(T2.to[i]),getk(T2.to[i],x);
	f[x][0]=f[x][1]=1;
	for(RI i=T1.h[x];i;i=T1.ne[i]) {//对于没有虚树点的子树进行预处理dp
		if(inT2[T1.to[i]]||eno[i]||T1.to[i]==fa[x][0]) continue;
		predp(T1.to[i],0);
		f[x][0]=1LL*f[x][0]*(f[T1.to[i]][0]+f[T1.to[i]][1])%mod;
		f[x][1]=1LL*f[x][1]*f[T1.to[i]][0]%mod;
	}
}
void dp(int x) {//统计答案
	g[x][0]=f[x][0],g[x][1]=f[x][1];
	for(RI i=T2.h[x];i;i=T2.ne[i]) {
		int y=T2.to[i];dp(y);
		int f0=(1LL*k0[y][0]*g[y][0]%mod+1LL*k1[y][0]*g[y][1]%mod)%mod;
		int f1=(1LL*k0[y][1]*g[y][0]%mod+1LL*k1[y][1]*g[y][1]%mod)%mod;
		g[x][0]=1LL*g[x][0]*(f0+f1)%mod,g[x][1]=1LL*g[x][1]*f0%mod;
	}
	if(bj[x]==1) g[x][0]=0;
	if(bj[x]==-1) g[x][1]=0;
}

int qm(int x) {return x>=mod?x-mod:x;}
int main()
{
	int x,y;
	n=read(),m=read(),T1.tot=1;
	for(RI i=1;i<=m;++i) x=read(),y=read(),T1.add(x,y),T1.add(y,x);
	dfs(1,0),buildT2(),prework(1);
	bin[1]=1;for(RI i=2;i<=js+1;++i) bin[i]=bin[i-1]<<1;
	for(RI zt=0;zt<bin[js+1];++zt) {//枚举与非树边相连的点的状态
		for(RI i=1;i<=js;++i)
			if(zt&bin[i]) bj[p[i]]=1;
			else bj[p[i]]=-1;
		int flag=0;
		for(RI i=1;i<=K;++i) if(bj[u[i]]==1&&bj[v[i]]==1) {flag=1;break;}
		if(flag) continue;
		dp(1),ans=qm(ans+qm(g[1][0]+g[1][1]));
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Fido_Puppy (赞：6)

## $\mathcal{Foreword}$

算是蒟蒻第一次发的黑题题解吧！

~~（本来 [P4887 【模板】莫队二次离线（第十四分块(前体)）](https://www.luogu.com.cn/problem/P4887)还是黑题的）~~

## $\mathcal{Question}$

[P4426 [HNOI/AHOI2018]毒瘤](https://www.luogu.com.cn/problem/P4426)

题目就是让你求一幅图的最大独立集的方案数。

## $\mathcal{Solution}$

我们会神奇的发现测试点 5~6 的数据范围是 $m = n - 1$。

于是我们首先从一棵树入手，考虑如何求一棵树的最大独立集的方案数。

设 $f_{u,0}$ 表示以 $u$ 为根的子树中不选 $u$ 节点的最大独立集的方案数。

设 $f_{u,1}$ 表示以 $u$ 为根的子树中选择 $u$ 节点的最大独立集的方案数。

假设 $v$ 是 $u$ 的一个子节点，易得：

$$f_{u,0} = f_{u,0} \times (f_{v,0} + f_{v,1})$$

$$f_{u,1} = f_{u,1} \times f_{v,0}$$

我们可以简单地打出代码：

```cpp
inline void dfs(int u, int fa) {
	f[u][0] = f[u][1] = 1; // 注意初始化
	for (auto v: G[u]) {
		if (v != fa) {
			dfs(v, u);
			(f[u][0] *= (f[v][1] + f[v][0])) %= mod;
			(f[u][1] *= f[v][0]) %= mod;
		}
	}
}
```
最后答案就是 $f_{Root,0} + f_{Root,1}$。

于是我们可以拿到 10 分的高分。

我们考虑如何求一个图的最大独立集的方案数。

我们会发现 $n - 1 \le m \le n + 10$。

也就代表一幅图中求出一棵生成树后，剩下的非树边最多只有 $11$ 条。

考虑暴力枚举每一条非树边两端节点的选与不选的状态。

对于每一条非树边两端节点，如果都选了明显是打破了限制。

我们可以套用容斥原理，最终的答案就是：

打破 $0$ 个限制的方案数 $-$ 打破 $1$ 个限制的方案数 $+$ 打破 $2$ 个限制的方案数……

大概就是这样的：

```cpp
inline void dfs(int x, int siz) { // siz 表示打破的限制的个数
	if (x == len + 1) { // len 表示非树边的数量
		if (siz & 1) (ans += (mod - ...)) %= mod;
		else (ans += ...) %= mod; // ... 表示每次这个选与不选状态下的生成树的最大独立集方案数
	}
	dfs(x + 1, siz);
	... // 选择这条非树边两端的节点，也就是打破这个限制
	dfs(x + 1, siz + 1);
	... // 还原打破的这个限制
}
```

如果我们对于每一个状态都暴力的跑一遍 dp，

时间复杂度就会变成 $\Theta (2^{11}n)$。

~~这样仿佛能够拿到 75 分的高分？~~

这样肯定是会超时的。

强制选择一个节点 $u$ 明显就是将 $g_{u,0}$ 乘上 $0$ （就是不能不选 $u$ 的意思），

而还原这个强制地选择明显就是再将 $g_{u,0}$ 除以 $0$。

于是我们可以考虑动态 dp。

（不会动态 dp 的左转 [P4719 【模板】"动态 DP"&动态树分治](https://www.luogu.com.cn/problem/P4719)）

这样单次修改和查询都是 $\Theta (log^2\ n)$ 的。

我们首先考虑树链剖分。

设 $g_{u,0}$ 表示只考虑 $u$ 的轻儿子的不选 $u$ 节点的以 $u$ 为根的子树中的最大独立集。

设 $g_{u,1}$ 表示只考虑 $u$ 的轻儿子的选择 $u$ 节点的以 $u$ 为根的子树中的最大独立集。

设 $hson_u$ 表示 $u$ 节点的重儿子，易得：

$$f_{u,0} = g_{u,0} \times (f_{hson_u,0} + f_{hson_u,1})$$

$$f_{u,1} = g_{u,1} \times f_{hson_u,0}$$

我们就可以把状态转移方程转换成矩阵：

$\left[ \begin{matrix} g_{u,0} & g_{u,0} \\ g_{u,1} & 0\end{matrix} \right] \times \left[ \begin{matrix} f_{hson_u,0}\\f_{hson_u,1}\end{matrix}\right] = \left[ \begin{matrix} f_{u,0} \\ f_{u,1} \end{matrix} \right]$

这个矩阵乘法是满足结合律的，明显我们可以用线段树来维护矩阵的乘积，修改时顺着重链往上跳就行了。

但是这道题和 [P4719 【模板】"动态 DP"&动态树分治](https://www.luogu.com.cn/problem/P4719) 不一样。

那道题的状态转移方程是加的，所以修改是加减法。

但这道题的状态转移方程是乘的，所以修改是乘除法。

~~（乘除法不是逆元就行了嘛？）~~

但这道题有时候会需要除以 $0$。

于是我们需要对于每一个节点 $i$ 的 $g_{i,0}$ 与 $g_{i,1}$。

都开一个数组 $Zero_{i,0}$ 和 $Zero_{i,1}$。

每一次乘 $0$ 就 ```Zero[u][0 or 1]++;```。

每一次除以 $0$ 就 ```Zero[u][0 or 1]--;```。

每一次查询一个节点 $x$ 的 $g_{x,opt}$ 的值：

```cpp
inline void val(int x, int opt) {
	return (Zero[x][opt] > 0? 0: g[u][opt]);
}
```

这样就能解决除以 $0$ 的问题了。

把矩阵乘法再改一下：

$\left[ \begin{matrix} val(u,0) & val(u,0) \\ val(u,1) & 0\end{matrix} \right] \times \left[ \begin{matrix} f_{hson_u,0}\\f_{hson_u,1}\end{matrix}\right] = \left[ \begin{matrix} f_{u,0} \\ f_{u,1} \end{matrix} \right]$

最后说一句：

不开 long long 见祖宗。

## $\mathcal{Code}$

好像就我一个码了 5 KB ~~（我还是太逊了）~~。

```cpp
// Best wishes!
#include <bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define pb push_back

typedef long long LL;

const int MAXN = 1e5 + 10;
const int mod = 998244353;

int n, m, father[MAXN];
vector <int> G[MAXN];

int A[MAXN], B[MAXN], len = 0;
int fa[MAXN], dep[MAXN], siz[MAXN], hson[MAXN];
int tot = 0, seg[MAXN], rev[MAXN], top[MAXN], End[MAXN];

LL f[MAXN][2], g[MAXN][2];
LL ans = 0;

int Zero[MAXN][2];

inline int find(int x) {
	if (father[x] != x) father[x] = find(father[x]);
	return father[x];
}

inline LL val(int u, int opt) {
	return (Zero[u][opt] > 0? 0: g[u][opt]);
}

struct _Matrix {
	LL Matrix[2][2];
	int n, m;
	
	_Matrix() {
		n = m = 0;
		
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				Matrix[i][j] = 0;
	}
	inline void Initialize(int x) {
		n = m = 2;
		
		Matrix[0][0] = val(x, 0); Matrix[0][1] = val(x, 0);
		Matrix[1][0] = val(x, 1); Matrix[1][1] = 0;
	}
	_Matrix operator * (const _Matrix &A) {
		_Matrix C; C.n = n; C.m = A.m;
		
		for (int i = 0; i < C.n; i++)
			for (int j = 0; j < C.m; j++)
				for (int k = 0; k < m; k++)
					(C.Matrix[i][j] += Matrix[i][k] * A.Matrix[k][j]) %= mod;
					
		return C; 
	}
};

struct Node {
	int l, r;
	_Matrix data;
}t[ MAXN << 2 ];

inline void build(int p, int l, int r) {
	t[p].l = l; t[p].r = r;
	
	if (l == r) {
		t[p].data.Initialize(rev[l]);
		return ;
	}
	
	int mid = l + r >> 1;
	
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	
	t[p].data = t[p << 1].data * t[p << 1 | 1].data;
}

inline void change(int p, int x) {
	if (t[p].l == t[p].r) {
		t[p].data.Initialize(rev[x]);
		return ;
	}
	
	int mid = t[p].l + t[p].r >> 1;
	
	if (x <= mid) change(p << 1, x);
	else change(p << 1 | 1, x);
	
	t[p].data = t[p << 1].data * t[p << 1 | 1].data;
}

inline _Matrix query(int p, int x, int y) {
	if (t[p].l >= x && t[p].r <= y) return t[p].data;
	
	int mid = t[p].l + t[p].r >> 1;
	
	if (y <= mid) return query(p << 1, x, y);
	if (mid < x) return query(p << 1 | 1, x, y);
	
	return query(p << 1, x, y) * query(p << 1 | 1, x, y); 
}

inline void dfs1(int u, int F) {
	fa[u] = F;
	dep[u] = dep[F] + 1;
	siz[u] = 1;
	
	for (auto v: G[u]) {
		if (v != F) {
			dfs1(v, u);
			
			siz[u] += siz[v];
			if (siz[ hson[u] ] < siz[v]) hson[u] = v;
		}
	}
}

inline void dfs2(int u, int Top) {
	top[u] = Top;
	seg[u] = ++tot;
	rev[tot] = u;
	
	f[u][0] = f[u][1] = g[u][0] = g[u][1] = 1ll;
	Zero[u][0] = Zero[u][1] = 0;
	
	if (hson[u]) {
		dfs2(hson[u], Top);
		(f[u][0] *= (f[ hson[u] ][0] + f[ hson[u] ][1])) %= mod;
		(f[u][1] *= f[ hson[u] ][0]) %= mod;
	}
	else End[Top] = u;
	
	for (auto v: G[u]) {
		if (v != fa[u] && v != hson[u]) {
			
			dfs2(v, v);
			
			(f[u][0] *= (f[v][0] + f[v][1])) %= mod;
			(f[u][1] *= f[v][0]) %= mod;
			(g[u][0] *= (f[v][0] + f[v][1])) %= mod;
			(g[u][1] *= f[v][0]) %= mod; 
		}
	}
}

inline LL quick(LL x, int p) {
	LL _ans = 1ll;
	while (p > 0) {
		if (p & 1) _ans = _ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return _ans;
}

inline void update(int u, int w) {
	if (w == 0) {
		Zero[u][0]++;
	} else Zero[u][0]--; // We use array Zero to record the num of 0.
	
	_Matrix Before, After;
	
	while (u != 0) {
		Before = query(1, seg[ top[u] ], seg[ End[ top[u] ] ]);
		change(1, seg[u]);
		After = query(1, seg[ top[u] ], seg[ End[ top[u] ] ]);
		
		u = fa[ top[u] ];
		
		if (After.Matrix[0][0] + After.Matrix[1][0] == 0)
			Zero[u][0]++;
		else g[u][0] = g[u][0] * (After.Matrix[0][0] + After.Matrix[1][0]) % mod;
		
		if (After.Matrix[0][0] == 0)
			Zero[u][1]++;
		else g[u][1] = g[u][1] * After.Matrix[0][0] % mod;
		
		if (Before.Matrix[0][0] + Before.Matrix[1][0] == 0)
			Zero[u][0]--;
		else g[u][0] = g[u][0] * quick(Before.Matrix[0][0] + Before.Matrix[1][0], mod - 2) % mod;
		
		if (Before.Matrix[0][0] == 0)
			Zero[u][1]--;
		else g[u][1] = g[u][1] * quick(Before.Matrix[0][0], mod - 2) % mod;
	}
}

inline void dfs(int x, int siz) {
	if (x == len + 1) {
		_Matrix Ans = query(1, seg[1], seg[ End[1] ]);
		
		if (siz & 1) (ans += mod - (Ans.Matrix[0][0] + Ans.Matrix[1][0]) % mod) %= mod;
		else (ans += Ans.Matrix[0][0] + Ans.Matrix[1][0]) %= mod;
		
		return ;
	}
	dfs(x + 1, siz);
	
	update(A[x], 0); // Choose (1, 1) and break the limitation.
	update(B[x], 0);
	
	dfs(x + 1, siz + 1);
	
	update(A[x], 1); // Return back.
	update(B[x], 1);
}

int main() {
	IOS;
	
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++)
		father[i] = i;
		
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		int fx = find(u), fy = find(v);
		if (fx != fy) {
			father[fx] = fy;
			G[u].pb(v);
			G[v].pb(u);
		}
		else {
			++len;
			A[len] = u;
			B[len] = v;
		}
	}
	
	dfs1(1, 0); dfs2(1, 1);
	build(1, 1, n);
	
	dfs(1, 0);
	
	cout << ans << endl;
	
	return 0;
}
```
完结撒花 ^_の。

---

## 作者：StarLbright40 (赞：6)

本篇题解为暴力卡常。附在[洛谷](/record/list?pid=P4426&user=128570)和 [loj](https://loj.ac/s?problemDisplayId=2496&submitter=XG0000) 的提交记录列表链接，可以此辅助阅读题解。

![](https://cdn.luogu.com.cn/upload/image_hosting/fizhex4n.png)

------------

首先记 $k=m-n+1$ 为非树边数量。

在座大伙肯定都知道树上独立集计数如何做。设 $f_{u,0/1}$ 表示钦定 $u$ 不选/选时的方案数，那么有

$$f_{u,0}=\prod_{v\in son_u}(f_{v,0}+f_{v,1}),f_{u,1}=\prod_{v\in son_u}f_{v,0}$$

对于非树边，我们钦定枚举其中一个选或不选，钦定选时则这条边的另一个点必不选，修改初值即可。这里我们钦定枚举两端点中较浅的点。于是我们获得了一个 $\mathcal O(n2^k)$ 的做法。

考虑卡常。瓶颈在于我们共要遍历 $2^k$ 次树进行 dp，于是想到记录 dfs 序，将递归搜索改为循环。

无符号数对常数取模有速度优势，所以在转移中做乘法时强制转换为 ull 而不是 ll。

众所周知数组连续访问是较快的，所以将点按 dfs 序重标号，这样就能在 dp 时连续访问 dp 数组，加快速度。

使用[数组前向星](/blog/zhjxaoini/yi-zhong-gao-xiao-de-cun-tu-fang-shi-shu-zu-qian-xiang-xing)保存树边，这样存边数组的访问也可以连续。瓶颈不在此处所以其中的排序用 sort 就可以。

另外不要忘了吸 O2。这样我们就可以获得 90pts 的高分，见洛谷提交记录第二条或 loj 提交记录第二条。

回头看看对非树边的处理，容易发现当存在一个点 $u$ 的 $f_{u,0/1}$ 初值均为 $0$ 时整棵树的方案数均为 $0$，可以直接跳过这种情况。加入此特判即可 AC 本题，见洛谷提交记录第四条或 loj 提交记录第一条。~~忘记勾选 O2~~ 不开 O2 可以获得 75pts，见洛谷提交记录第三条。

这个故事告诉我们，感谢 O2，感谢 NOILinux2.0。

思考一下这样特判的道理。去 loj 把刚才 TLE 的数据点 #19 #20 扒下来，发现它们均满足 $n=10^5,m=n+10$。拿一个 set 记录一下非树边端点，输出这个 set 的 size() 发现均为 $21$，也就是恰有一个端点作为非树边的交。这时加入上面的特判，有机会将所枚举的情况数减少 1/2 或 1/4，于是便足以通过此题。

深入思考并尝试可以发现，如果在处理非树边时钦定枚举的是较深的点，则仍获得 90pts，见 loj 提交记录第三条。所以说这种做法是不靠谱的面向数据，要走正道还是得老实写虚树。~~现在您可以回到第一页去看其他题解了。~~

![](https://cdn.luogu.com.cn/upload/image_hosting/cfs7bf1e.png)

---

## 作者：蒟蒻丁 (赞：5)

~~因为标签是虚树所以考虑树~~
看到5~6的数据点，发现图是棵树，于是快乐地把5~6数据点作为切入点

其实就是么有上司的舞会是吧

 $$f[x][0]=Σf[v][0]+f[v][1]$$
 $$f[x][1]=Σf[v][0]$$
那么我们对于一个图就直接地把图破成树好了，枚举每条边是否选择，强行跑树DP，但是边太多了所以必死无疑

~~但是考虑标签是虚树~~但是看到数据，$m$只比$n$大$11$，通过虚树可以让枚举次数大大降低，另外，因为每次只会有一些特殊的点(就是环上的点)对答案做出贡献，可以用虚树来优化

而最大的$m \leq n+11$，我们可以把这些多出来的点拎出来构建虚树，并在虚树上DP

### 注意，接下来是本题最恶心的地方
我们假设有下面这条链（这条链将被用来建立虚树，我们会在这条边上DP）
![graph.png](https://i.loli.net/2020/07/30/F1m93pizYnCPN5d.png)
dp数组向上传递是有一定规律的
 $$f[5][0]=\prod f[6][0]+f[6][1]$$
 $$f[5][1]=\prod f[6][0]$$
 $$f[4][0]=\prod f[5][0]+f[5][1]$$
 $$即$$
 $$f[4][0]=\prod (f[6][0]+f[6][1])+f[6][0]$$
 $$f[4][1]=\prod f[6][0]+f[6][1]$$
 $$f[3][0]=\prod f[4][0]+f[4][1]$$
 $$f[3][0]=\prod ((f[6][0]+f[6][1])+f[6][0])+(f[6][0]+f[6][1])$$
 $$f[3][1]=\prod f[4][0]$$
 $$f[3][1]=\prod f[6][0]+f[6][1]+f[6][0]$$
我们发现
 $$f[6][0] 和 f[6][1]$$
每次递归会传递一次这玩意，而虚树边上的点是固定的，所以这两个玩意被加上的次数是可以递归处理出来的

所以我们得到这个方程(v是x在虚树上的父亲)

 $$f[x][1]=k0[v][1]*f[v][0]+k1[v][1]*f[v][1]$$
 $$f[x][0]=k0[v][0]*f[v][0]+k1[v][0]*f[v][0]$$
预处理出k就能舒服DP

而预处理的方法比较坑

我们先考虑x原树上的一个儿子t

设在添加t（树DP的时候）前$f[x][1]$为$ovo[x][1]$
 $$f[x][1]=ovo[x][1]*[(f[v][0]*k1[v][0])+(f[v][1]*k0[v][1])]$$
 所以考虑刚才对k数组的理解
 $$k1[v][0]=ovo[x][1]*k0[v][0]$$
## 最后梳理下dp的流程
预处理出k数组

每次暴力枚举加入了哪些非树边

树DP
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define N 100020 
#define mod 998244353
using namespace std;
ll head[N],hh[N],dfn[N],dep[N],f[25][N],ff[N][3],k0[N][3],k1[N][3],dp[N][3];
ll b[25],bj[N],in[N],g[N][3],p[N],st[N];
ll n,m,cnt=1,ret,tmp,T,tt,tp,ans;
bool vis[N],en[N*2];

struct Tuck{
      ll u1,v1;
}tr[N];

struct The_World{
      ll to,nxt;
}q[N*10];

struct Star_Platinum{
      ll v,nx;
}e[N*10];

bool cmp(ll x,ll y){
      return dfn[x]<dfn[y];
}

void add(ll u,ll v){
      q[++cnt].to=v,q[cnt].nxt=head[u];
      head[u]=cnt;
      q[++cnt].to=u,q[cnt].nxt=head[v];
      head[v]=cnt;
}

void edd(ll u,ll v){
	e[++ret].v=v,e[ret].nx=hh[u];
	hh[u]=ret;
}

void dfs(ll x,ll fa){
      dfn[x]=++tmp;
      dep[x]=dep[fa]+1;
      vis[x]=1;
      for(ll i=1;i<=20&&f[i-1][x];i++){
            f[i][x]=f[i-1][f[i-1][x]];
      }
      for(ll i=head[x];i;i=q[i].nxt){
            ll v=q[i].to;
            if(v!=fa){
                  if(!vis[v]){
                        f[0][v]=x;
                        dfs(v,x);
                  }
                  else {
                        T++;
                        tr[T].u1=x,tr[T].v1=v;
                        en[i]=en[i^1]=1;
                  }
            }
      }
}

ll LYCA(ll x,ll y){
      if(dep[x]<dep[y])swap(x,y);
      for(ll i=20;i>=0;i--){
            if(dep[f[i][x]]>=dep[y]){
                  x=f[i][x];
            }
            if(x==y)return x;
      }
      for(ll i=20;i>=0;i--){
            if(f[i][x]!=f[i][y]){
                  x=f[i][x];
                  y=f[i][y];
            }
      }
      return f[0][x];
}

void build_vtree(ll x){
      if(tt==1){
            st[++tt]=x;
            return ;
      }
      ll lca=LYCA(st[tt],x);
      while(tt>1&&dfn[st[tt-1]]>=dfn[lca]){
            edd(st[tt-1],st[tt]);
            tt--;
      }
      if(st[tt]!=lca){
            in[lca]=1;
            edd(lca,st[tt]);
            st[tt]=lca;
      }
      st[++tt]=x;
}

void dp1(ll x,ll o){
      ff[x][0]=ff[x][1]=1;
      in[x]=1;
      for(ll i=head[x];i;i=q[i].nxt){
            ll v=q[i].to;
            if(v==f[0][x]||v==o||in[v]||en[i])continue;
            dp1(v,o);
            ff[x][0]=ff[x][0]*(ff[v][0]+ff[v][1])%mod;
            ff[x][1]=ff[x][1]*ff[v][0]%mod;
      }
}

void getk(ll x,ll y){
      k0[x][0]=1,k1[x][1]=1;
      for(ll i=x;f[0][i]!=y;i=f[0][i]){
            dp1(f[0][i],i);
            ll t0=k0[x][0],t1=k1[x][0];
            k0[x][0]=ff[f[0][i]][0]*(k0[x][0]+k0[x][1])%mod;
            k1[x][0]=ff[f[0][i]][0]*(k1[x][0]+k1[x][1])%mod;
            k0[x][1]=ff[f[0][i]][1]*t0%mod;
            k1[x][1]=ff[f[0][i]][1]*t1%mod;
      }
}

void yu_work(ll x){
      for(ll i=hh[x];i;i=e[i].nx){
            ll v=e[i].v;
            yu_work(v),getk(v,x);
      }
      ff[x][0]=ff[x][1]=1;
      for(ll i=head[x];i;i=q[i].nxt){
            ll v=q[i].to;
            if(in[v]||en[i]||v==f[0][x])continue;
            dp1(v,0);
            ff[x][0]=ff[x][0]*(ff[v][0]+ff[v][1])%mod;
            ff[x][1]=ff[x][1]*ff[v][0]%mod;
      }
}

void DP2(ll x){
      g[x][0]=ff[x][0],g[x][1]=ff[x][1];
      for(ll i=hh[x];i;i=e[i].nx){
            ll v=e[i].v;
            if(v!=f[0][x]){
                  DP2(v);
                  ll f0=(k0[v][0]*g[v][0]%mod+k1[v][0]*g[v][1]%mod)%mod;
                  ll f1=(k0[v][1]*g[v][0]%mod+k1[v][1]*g[v][1]%mod)%mod;
                  g[x][0]=g[x][0]*(f0+f1)%mod;
                  g[x][1]=g[x][1]*f0%mod;
            }
      }
      if(bj[x]==1)g[x][0]=0;
      if(bj[x]==-1)g[x][1]=0;
}

int main(){
      scanf("%lld%lld",&n,&m);
      for(ll i=1;i<=m;i++){
            ll a1,a2;
            scanf("%lld%lld",&a1,&a2);
            add(a1,a2);
      }
      dfs(1,0);
      for(ll i=1;i<=T;i++){
            if(!in[tr[i].u1])in[tr[i].u1]=1,p[++tp]=tr[i].u1;
            if(!in[tr[i].v1])in[tr[i].v1]=1,p[++tp]=tr[i].v1;
      }
      sort(p+1,p+1+tp,cmp);
      st[tt=1]=1;
      for(ll i=1;i<=tp;i++){
            if(p[i]==1)continue;
            build_vtree(p[i]);
      }
      while(tt>1){
            edd(st[tt-1],st[tt]);
            tt--;
      }
      yu_work(1);
      b[1]=1;
      for(ll i=2;i<=tp+1;i++)b[i]=b[i-1]*2;
      for(ll i=0;i<b[tp+1];i++){
            for(ll j=1;j<=tp;j++){
                  if(i&b[j])bj[p[j]]=1;
                  else bj[p[j]]=-1;
            }
            bool pool=0;
            for(ll j=1;j<=T;j++){
                if(bj[tr[j].u1]==1&&bj[tr[j].v1]==1){
                      pool=1;break;
                }
            }
          if(pool)continue;
          DP2(1);
          ans=(ans+(g[1][0]+g[1][1])%mod)%mod;
    }
    printf("%lld",ans);
}
```

---

## 作者：chen_qian (赞：4)

蒟蒻这道题做了很久，这篇题解其实是对 @Soulist 大佬的代码的补充。补充了系数的推导，以及一些细节问题。可以搭配着大佬的食用。所以我省略了可以找系数的过程的推导。

首先找出所有的非树边，对这些非树边的端点进行去重，建立虚树。接下来我们需要处理两个东西：

1. 虚树上的节点，除过有关键点的子树，其其他子树的总答案。

2. 找到每个点向父亲转移时的系数。

关于 1. 我们可以直接 $\text{DP}$ 解决。所以最主要的问题就是 2.

以下图为例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/cgie420z.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们假设 $1,5$ 时虚树上的节点，$2,3,4$ 是被缩到边上的节点，显然 $2,3,4$ 除过这些链上的节点所在的子树之外，还有其他子树，可以预处理出记为 $g_{x,0/1}$，其所有子树的答案记为 $f_{x,0/1}$。记 $k0_{0}$ 是钦定当前计算到的节点 $x$ 的父亲不选时，$f_{1,0}$ 的系数。那么我们从 $1$ 开始向上方进行计算。也就是说最开始，$2,1$ 之间的转移，那么最早的系数，就应该是 $k0_{0}=1,k0_{1}=1,k1_{0}=1,k1_{1}=0$。然后我们开始向上转移，现在考虑的是 $3$ 的系数，比如说 $k0_0$ 。其方程应该是$f_{3,0}=g_{3,0} \times (f_{2,0}+f_{2,1})$，也就是说现在所谓的系数就是将 $(f_{2,0}+f_{2,1})$ 展开成带系数的方式，$f_{2,0}+f_{2,1}= g_{2,0} \times(k0_0 \times f_{1,0}+k0_1 \times f_{1,1})+g_{2,1}\times(k1_0 \times f_{1,0}+k1_1 \times f_{1,1})$，将其展开，看 $f_{1,0}$ 的系数就可以就是当前的 $k0_{0}$ ，在往上继续推，发现规律是一样的，这样就可以预处理出所有的系数。

代码也就非常简单了。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define mod 998244353
#define N 201005
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
using namespace std;
int n,m,ffa[N];
int k,h[N];
int head[N],idx,tot;
struct edge{
    int v,next;
}e[N];
void add(int u,int v){
    e[++idx].v=v;
    e[idx].next=head[u];
    head[u]=idx;
}
int k0[N][2],k1[N][2],vis[N];//k0[x][0]表示钦定 fa[x] 不选，dp[x][0] 的系数 
pii E[N];//非树边
vector<int> g[N];
int get(int x){
    if(x==ffa[x]) return x;
    return ffa[x]=get(ffa[x]);
}
int fa[N][30],dep[N],dfn[N],cnt;
void dfs(int x,int f){
    fa[x][0]=f;
    dfn[x]=++cnt;
    dep[x]=dep[f]+1;
    for(int i=1;i<=20;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
    for(auto y: g[x]){
        if(y==f) continue;
        dfs(y,x);
        vis[x]+=vis[y];
    }
}
int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;i>=0;i--) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
    if(x==y) return x;
    for(int i=20;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int stk[N],top;
bool cmp(int x,int y){
    return dfn[x]<dfn[y];
}
void build(){
    for(int i=1;i<=tot;i++) h[++k]=E[i].fi,h[++k]=E[i].se;
    sort(h+1,h+k+1);
    k=unique(h+1,h+k+1)-h-1;
    sort(h+1,h+k+1,cmp);
    stk[top=1]=1;
    for(int i=1;i<=k;i++){
        if(h[i]==1) continue;
        int lca=LCA(stk[top],h[i]);
        if(lca!=stk[top]){
            while(dfn[lca]<dfn[stk[top-1]]){
                add(stk[top-1],stk[top]);
                top--;
            }
            if(dfn[lca]!=dfn[stk[top-1]]){
                add(lca,stk[top]);
                stk[top]=lca;
            }
            else add(lca,stk[top]),top--;
        }
        stk[++top]=h[i];
    }
    for(int i=1;i<top;i++) add(stk[i],stk[i+1]);
}
int dp[N][2]; 
int f1[N][2];
void dp1(int x,int son){//辅助计算系数,也就是虚树上被缩掉的点到对应儿子那条链之外的答案
	dp[x][0]=dp[x][1]=1;
	for(auto y:g[x]){
		if(y==fa[x][0]||y==son) continue;//除开那条链不能算 
		dp1(y,x);
		dp[x][0]=(dp[x][0]*(dp[y][0]+dp[y][1])%mod)%mod;
    	dp[x][1]=(dp[x][1]*dp[y][0])%mod;
	}
} 
void calc(int x,int f){//现在计算 x-> f 这条边上的系数
	 int p=x;k0[x][0]=k0[x][1]=k1[x][0]=1;//最初的时候，这三项的系数都应该为 1
	 while(fa[p][0]!=f){//注意现在向上爬到的点时 fa[p]
	 	dp1(fa[p][0],p);
		int t0=k0[x][0],t1=k0[x][1];
		k0[x][0]=(dp[fa[p][0]][0]*t0+dp[fa[p][0]][1]*k1[x][0])%mod;
		k0[x][1]=(dp[fa[p][0]][0]*t1+dp[fa[p][0]][1]*k1[x][1])%mod;
		k1[x][1]=dp[fa[p][0]][0]*t1%mod,k1[x][0]=dp[fa[p][0]][0]*t0%mod;
		p=fa[p][0];
	 } 
}
void dp2(int x,int f){//要求计算以 x 为根的子树中，除去包含关键点的子树的答案 ，也就是每个点的DP的初值 
    f1[x][0]=f1[x][1]=1;
    for(auto y:g[x]){
    	if(y==f||vis[y]) continue;
    	dp2(y,x);
    	f1[x][0]=(f1[x][0]*(f1[y][0]+f1[y][1])%mod)%mod;
    	f1[x][1]=(f1[x][1]*f1[y][0])%mod;
	}
}
void predfs(int x,int f){//注意这里已经是虚树上了 
	dp2(x,f),h[++k]=x ; 
	if(x!=f) calc(x,f) ;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		predfs(y,x); 
	}
}
void dp3(int x){
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		dp3(y);
		dp[x][0]*=(k0[y][0]*dp[y][0]%mod+k0[y][1]*dp[y][1]%mod),dp[x][0]%=mod;
		dp[x][1]*=(k1[y][0]*dp[y][0]%mod+k1[y][1]*dp[y][1]%mod),dp[x][1]%=mod;
	}
}
int ans;
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++) ffa[i]=i;
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%lld%lld",&u,&v);
        if(get(u)!=get(v)){
            g[u].pb(v);
            g[v].pb(u);
			ffa[get(v)]=get(u);
        }
        else{
            E[++tot]=mp(u,v);
            vis[u]=vis[v]=1; 
        }
    }   
    dfs(1,0);
    build();
    int maxn=(1<<tot)-1;
	k=0; 
    predfs(1,1);
    for(int i=0;i<=maxn;i++){
		for(int i=1;i<=k;i++) dp[h[i]][0]=f1[h[i]][0],dp[h[i]][1]=f1[h[i]][1] ; 
		for(int j=1;j<=tot;j++){
			if((1<<(j-1))&i) dp[E[j].fi][0]=0, dp[E[j].se][1]=0; 
			else dp[E[j].fi][1]=0; 
		}
		dp3(1),ans=(ans+dp[1][0]+dp[1][1])%mod ;
	}
	printf("%lld\n",ans%mod) ;
    return 0;
}
```


---

## 作者：cn_lemon (赞：3)

（注意：本题解只是分享一下我的一种奇（辣）特（鸡）的思路，无法AC此题）

看到这题迟迟没有人发题解，我又看不懂网上的标算，于是我在挣扎中YY着算法，于是产生了下面这个半成品。作为高一的渣渣，我只能写出这种辣鸡做法了，65分，然后就会T。

我是这么想的，我在建树的时候会有一些边无法加入森林里，否则就会构成环。所以我就想先生成一颗树，然后把那些多余边所连接的点全都抠掉就变成了一个残余森林，我们可以先对这个残余森林先进行一次裸的DP，然后枚举那些被抠掉的点是否加入森林。最多有22个点，然后这些加入森林的点标记为必须选择再算方案，每次得到合法的森林时都会算出强行同时选择的那些多余点的方案，最后把每次的结果相加就是总方案数。

但是有一个问题就是每次判断你枚举的点加入森林是否可以合法而不构成环（如果一个点加入了森林，那么与之相关的所有边都要加进森林，当然不选的点除外）。于是我想到了一个办法，我先处理出原始森林的并查集状态，每次加入新点的时候会将并查集更新，仔细想想会发现，我们每次将并查集更新时，实际上是把一些父子同体的点的父亲变成别的点，那么我们用一个队列记录下被更新过的点，在每次完成判断后再把他们的父亲赋回它们自己。

我满怀忐忑的打完这个代码，然后发现复杂度果然不对，一个是我不知道合法的方案数会有多少，每次得到一个方案会执行一次On的dp，可能会很大，然后每次我们通过加边判断森林的合法性时，每个点所连接的边可能会很多，所以会T。

下附辣鸡代码
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define LL long long
using namespace std;
const int maxn=1e5+10;
const LL mod=998244353;
inline void read(int &x)
{
	x=0;char c=getchar();int f=1;
	while((c<'0'||c>'9')&&c!='-')c=getchar();
	if(c=='-')f=-1;
	while(c<='9'&&c>='0')x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	x=x*f;
}
int n,m;
int a[maxn],b[maxn];
int fa[maxn];
bool vis[maxn];
int s[maxn],ls;
LL dp[maxn][2],ans,sum;
int que[maxn],lq;
int q[maxn],ll;
int to[maxn<<1],nex[maxn<<1],beg[maxn],e,inq[maxn];
bool ins[maxn],intree[maxn],must[maxn];
int find(int x) {return fa[x]==x?x:fa[x]=find(fa[x]);}
inline void add(int u,int v)
{
	to[++e]=v;
	nex[e]=beg[u];
	beg[u]=e;
}
void dfsdp(int u)
{
	vis[u]=1;
	if(must[u])dp[u][1]=1,dp[u][0]=0;
	else {dp[u][1]=dp[u][0]=1;}
	for(register int i=beg[u];i;i=nex[i])
	{
		int v=to[i];
		if(vis[v]||!intree[v])continue;
		dfsdp(v);
		dp[u][0]=dp[u][0]*(dp[v][1]+dp[v][0])%mod;
		(dp[u][1]*= dp[v][0])%=mod;
	}
}
inline void pd()
{
	int flag=0;
	ll=0;
	for(register int i=1;i<=lq;++i)
	{
		int u=que[i];
		for(register int j=beg[u];j;j=nex[j])
		{
			int v=to[j];
			if(!intree[v])continue;
			if(must[u]&&must[v]){flag=1;break;}
			if(find(u)==find(v)){flag=1;break;}
			else 
			{
				q[++ll]=find(u);
				fa[find(u)]=find(v);
			}
		}
		if(flag)break;
	}
		while(ll)
		{
			fa[q[ll]]=q[ll];
			--ll;
		}
	if(flag)
	{
		/*for(register int i=1;i<=n;++i)
			if(intree[i])printf("%d ",i);
		puts("");*/
		return;
	}
	else
	{
		/*for(register int i=1;i<=n;++i)
			if(intree[i])printf("%d ",i);
		puts("");*/
		memset(vis,0,sizeof(vis));
		sum=1;
		for(register int i=1;i<=n;++i)
		if(intree[i]&&!vis[i])
		{
			dfsdp(i);
			(sum*=dp[i][0]+dp[i][1])%=mod;
		}
		(ans+=sum)%=mod;
		return;
	}
}
void dfs(int k)
{
	if(k>ls)
	{
		if(!lq)return;
		pd();
		return;
	}
	dfs(k+1);
	que[++lq]=s[k];
	intree[s[k]]=1;
	inq[s[k]]=lq;
	dfs(k+1);
	intree[s[k]]=0;
	inq[s[k]]=0;
	--lq;
}
int main()
{
	read(n),read(m);
	for(register int i=1;i<=m;++i)
		read(a[i]),read(b[i]),add(a[i],b[i]),add(b[i],a[i]);
	for(register int i=1;i<=n;++i)fa[i]=i;
	for(register int i=1;i<=m;++i)
	{
		if(find(a[i])!=find(b[i]))
		{
			fa[find(a[i])]=find(b[i]);
			vis[i]=1;
		}
	}
	for(register int i=1;i<=m;++i)
	if(!vis[i])
	{
		if(!ins[a[i]])ins[a[i]]=1,s[++ls]=a[i];
		if(!ins[b[i]])ins[b[i]]=1,s[++ls]=b[i];
	}
	for(register int i=1;i<=n;++i)
		if(!ins[i])intree[i]=1;
		else must[i]=1;
	for(register int i=1;i<=n;++i)fa[i]=i;
	for(register int i=1;i<=m;++i)
		if(intree[a[i]]&&intree[b[i]])fa[find(a[i])]=find(b[i]);
	sum=1;
	memset(vis,0,sizeof(vis));
	for(register int i=1;i<=n;++i)
		if(intree[i]&&!vis[i])
		{
			dfsdp(i);

			(sum*=dp[i][0]+dp[i][1])%=mod;
		}
	(ans+=sum)%=mod;
	if(ls)
	dfs(1);
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：Awar3ness (赞：2)

考虑直接暴力。
```cpp
f[x][1]=f[x][1]*f[y][0];
f[x][0]=f[x][0]*(f[y][0]+f[y][1]);
```
那么显然，对于一条非树边，只有两种状态，并不是三种，我们直接二进制枚举这些状态，把不合法的continue掉，卡卡常就过了。理论复杂度有2e8，但是luogu开了O2可以在1s之内跑出来。
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO
{
    const int __S=(1<<21)+5;char __buf[__S],*__H,*__T;
    inline char getc()
    {
        if(__H==__T) __T=(__H=__buf)+fread(__buf,1,__S,stdin);
        if(__H==__T) return -1;return *__H++;
    }
    template <class __I>inline void read(__I &__x)
    {
        __x=0;int __fg=1;char __c=getc();
        while(!isdigit(__c)&&__c!='-') __c=getc();
        if(__c=='-') __fg=-1,__c=getc();
        while(isdigit(__c)) __x=__x*10+__c-'0',__c=getc();
        __x*=__fg;
    }
    inline void readd(double &__x)
    {
        __x=0;double __fg=1.0;char __c=getc();
        while(!isdigit(__c)&&__c!='-') __c=getc();
        if(__c=='-') __fg=-1.0,__c=getc();
        while(isdigit(__c)) __x=__x*10.0+__c-'0',__c=getc();
        if(__c!='.'){__x=__x*__fg;return;}else while(!isdigit(__c)) __c=getc();
        double __t=1e-1;while(isdigit(__c)) __x=__x+1.0*(__c-'0')*__t,__t=__t*0.1,__c=getc();
        __x=__x*__fg;
    }
    inline void reads(char *__s,int __x)
    {
        char __c=getc();int __tot=__x-1;
        while(__c<'!'||__c>'~') __c=getc();
        while(__c>='!'&&__c<='~') __s[++__tot]=__c,__c=getc();
        __s[++__tot]='\0';
    }
    char __obuf[__S],*__oS=__obuf,*__oT=__oS+__S-1,__c,__qu[55];int __qr;
    inline void flush(){fwrite(__obuf,1,__oS-__obuf,stdout);__oS=__obuf;}
    inline void putc(char __x){*__oS++ =__x;if(__oS==__oT) flush();}
    template <class __I>inline void print(__I __x)
    {
        if(!__x) putc('0');
        if(__x<0) putc('-'),__x=-__x;
        while(__x) __qu[++__qr]=__x%10+'0',__x/=10;
        while(__qr) putc(__qu[__qr--]);
    }
    inline void prints(const char *__s,const int __x)
    {
        int __len=strlen(__s+__x);
        for(int __i=__x;__i<__len+__x;__i++) putc(__s[__i]);
    }
    inline void printd(double __x,int __d)
    {
        long long __t=(long long)floor(__x);print(__t);putc('.');__x-=(double)__t;
        while(__d--)
        {
            double __y=__x*10.0;__x*=10.0;
            int __c=(int)floor(__y);
            putc(__c+'0');__x-=floor(__y);
        }
    }
    inline void el(){putc('\n');}inline void sp(){putc(' ');}
}using namespace IO;
#define N 100100
#define P 998244353
int n,m,x,y,ok,cnt,ans,he[N],ne[N*2],to[N*2],f[N],g[N],u[N],v[N],a[N],b[N],dfn[N],d[N],I,t1,t2,t3;
void add(int x,int y){to[cnt]=y;ne[cnt]=he[x];he[x]=cnt++;}
int inc(int x,int y){return x+y>=P?x+y-P:x+y;}
void dfs(int x,int fa)
{
    dfn[x]=++I;
    for(int i=he[x],y;~i;i=ne[i]) if((y=to[i])!=fa)
    {
        if(dfn[y]&&dfn[y]<dfn[x]) a[++t1]=y,b[t1]=x,d[++t3]=y,d[++t3]=x;
        else if(!dfn[y]) u[++t2]=x,v[t2]=y,dfs(y,x);
    }
}
int main()
{
    read(n);read(m);memset(he,-1,sizeof(he));
    for(register int i=1;i<=m;i++) read(x),read(y),add(x,y),add(y,x);
    dfs(1,0);
    for(register int s=0;s<(1<<t1);s++)
    {
        for(register int i=1;i<=n;i++) f[i]=g[i]=1;
        for(register int i=1;i<=t1;i++) if((1<<(i-1))&s) g[a[i]]=0;else f[a[i]]=g[b[i]]=0;
        ok=1;for(int i=1;i<=t3;i++) if(!f[d[i]]&&!g[d[i]]){ok=0;break;}
        if(!ok) continue;
        for(register int i=n-1;i;i--) x=u[i],y=v[i],f[x]=1ll*f[x]*(f[y]+g[y])%P,g[x]=1ll*g[x]*f[y]%P;
        ans=inc(ans,inc(f[1],g[1]));
    }
    printf("%d\n",ans);
}
```

---

## 作者：Larunatrecy (赞：1)

在一些科技普及之后这个题好像就没什么意义了？

因为 $m\leq n+10$，所以根据广义串并联图的相关理论，我们可以通过 **删一度点，缩二度点，叠合重边** 的方式把原图缩成一个点数不超过 $20$，边数不超过 $30$ 的图，其中每条边代表了原图的一个连通子图，且每条边对应的连通子图与外部的点只有恰好两个点连接，因此我们记录这两个点的状态就行了。

我们可以发现：

- 删一度点相当于把某个连通子集挂在另一个点上，且之后这个子集和别的点没有任何关系

- 缩二度点相当于把两个连通子集串起来，方案数相乘再求和即可

- 叠合重边，缩二度点的过程有可能产生重边，此时相当于并起来，方案数直接相乘

对于每条边 $e$ ，设 $f_{e,0/1,0/1}$ 代表与边 $e$ 相连的两个点选的状态是 $0/1,0/1$ 时，该边对应的连通子图内的方案数，$g_{x,0/1}$ 代表 $x$ 的状态时 $0/1$ 时通过 **删一度点** 操作挂在 $x$ 上的子图内的方案数，那么上述三操作对应的 $f$ 和 $g$ 的转移是简单的。

最后剩下的图中不超过 $20$ 个点，我们 $2^{20}$ 枚举然后把系数乘起来就好了。

复杂度 $\Theta(n\log n+2^{2(m-n)}(m-n))$ ，跑不满。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+7;
map<int,int> mp[N];
int f[N][2][2],U[N],V[N];
int w[N][2],deg[N];
int n,m;
queue<int> q;
bool del[N];
inline int F(int e,int x,int c,int y,int d)
{
	if(x==U[e])return f[e][c][d];
	return f[e][d][c];
}
const int mod = 998244353;
int tmp[2][2];
int id[N],tot=0;
int seq[N],Eu[N],Ev[N],Ew[N][2][2];
int state[N];
bool ban[N];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)w[i][0]=w[i][1]=1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d",&U[i],&V[i]);
		if(mp[U[i]][V[i]])continue;
		mp[U[i]][V[i]]=i;
		mp[V[i]][U[i]]=i;
		f[i][0][0]=f[i][1][0]=f[i][0][1]=1;
		deg[U[i]]++;deg[V[i]]++;
	}
	for(int i=1;i<=n;i++)if(deg[i]<=2)q.push(i);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		if(del[x])continue;
		if(deg[x]==0)continue;
		del[x]=1;
		if(deg[x]==1)
		{
			auto A=(*mp[x].begin());mp[x].erase(mp[x].begin());
			int y=A.first,e=A.second;
			deg[y]--;mp[y].erase(x);deg[x]=0;
			ban[e]=1;
			for(int c=0;c<=1;c++)
			{
				int v=0;
				for(int d=0;d<=1;d++)
				v=(v+1ll*w[x][d]*F(e,x,d,y,c)%mod)%mod;
				w[y][c]=1ll*w[y][c]*v%mod;
			}
			if(deg[y]<=2)q.push(y);
			continue;
		}
		auto A=(*mp[x].begin());mp[x].erase(mp[x].begin());
		auto B=(*mp[x].begin());mp[x].erase(mp[x].begin());
		int yA=A.first,eA=A.second;
		int yB=B.first,eB=B.second;
		int eC=mp[yA][yB];
		deg[x]=0;
		mp[yA].erase(x);mp[yB].erase(x);
		for(int a=0;a<=1;a++)//yA
		for(int b=0;b<=1;b++)//yB
		{
			tmp[a][b]=0;
			for(int c=0;c<=1;c++)
			tmp[a][b]=(tmp[a][b]+1ll*F(eA,yA,a,x,c)*F(eB,yB,b,x,c)%mod*w[x][c]%mod)%mod;
		}
		U[eA]=yA;V[eA]=yB;
		for(int a=0;a<=1;a++)
		for(int b=0;b<=1;b++)
		f[eA][a][b]=tmp[a][b];
		mp[yA][yB]=mp[yB][yA]=eA;
		if(eC)
		{
			for(int a=0;a<=1;a++)
			for(int b=0;b<=1;b++)
			f[eA][a][b]=1ll*f[eA][a][b]*F(eC,yA,a,yB,b)%mod;
			deg[yA]--;deg[yB]--;
			if(deg[yA]<=2)q.push(yA);
			if(deg[yB]<=2)q.push(yB);
			ban[eC]=1;
		}
	}
	for(int x=1;x<=n;x++)if(!del[x])
	{
		seq[++tot]=x;
		id[x]=tot;
	}
	int C=0;
	for(int x=1;x<=n;x++)if(!del[x])
	{
		for(auto U:mp[x])
		{
			int y=U.first,e=U.second;
			if(x<y)
			{
				++C;
				Eu[C]=id[x];
				Ev[C]=id[y];
				for(int a=0;a<=1;a++)
				for(int b=0;b<=1;b++)
				Ew[C][a][b]=F(e,x,a,y,b);
			}
		}
	}
	int ans=0;
	for(int S=0;S<(1<<tot);S++)
	{
		int res=1;
		for(int i=1;i<=tot;i++)
		{
			state[i]=((S>>(i-1))&1);
			res=1ll*res*w[seq[i]][state[i]]%mod;
		}
		for(int i=1;i<=C;i++)
		res=1ll*res*Ew[i][state[Eu[i]]][state[Ev[i]]]%mod;
		ans=(ans+res)%mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Daniel2020 (赞：1)

## 前言
逛了一圈题解区没有发现将怎么具体维护系数的，至多只推了式子，对我这种刚学虚树的蒟蒻非常不友好。
  
所以在这一篇题解里，我会具体讲系数在代码中具体怎么维护。

## 正解
不难发现 $m = n-1$ 时答案即为树上独立集的数量。设 $f_i$ 表示以 $i$ 为根的子树不选 $i$ 的方案数，$g_i$ 表示以 $i$ 为根的子树选 $i$ 的方案数，则有转移方程：

$$f_u = \prod(f_v+g_v)$$

$$g_u = \prod f_v$$

发现对于所有数据点，非树边至多有 $11$ 条，考虑枚举每一条边是否合法进行容斥。~~不会容斥原理的建议先去学。~~

枚举出一组状态后，至多有 $22$ 个点强制需要被选出，但是其余的大部分的点没有约束，考虑能否预处理这些点的贡献，再“特判”被强制选出的点的贡献。

考虑虚树。即使选出所有的非树边，虚树中也至多有 $44$ 个节点（因为 $f,g$ 要在节点 $1$ 统计，所以虚树中必须有节点 $1$）。不妨只建一次虚树，使这颗虚树包含所有非树边的端点。

观察到对于虚树上一条边，如果找到它在原树上对应的链，那么除端点的“中间部分”没有变化。再次观察我们的 $DP$ 方程，发现只有两个参数 $f_i,g_i$。不妨假设对于原树上一条链 $(u,v)$，$f_u,g_u$ 形如：

$$f_u = af_v+bg_v$$

$$g_u = cf_v+dg_v$$

考虑从 $u$ 转移到 $w$（$w$ 为 $u$ 的父亲节点）。设在原树上“割去”节点 $u$ 后，$k_0 = f_w',k_1 = g_w'$。于是有：

$$f_w' = k_0(f_u+g_u) = k_0(a+c)f_v+k_1(b+d)g_v$$

$$f_w' = k_1f_u = k_1af_v+k_1bg_v$$

发现维护的系数是可以转移的，所以我们有一个模糊的想法：对虚树上的每一条边维护 $a,b,c,d$，对每一组状态进行树形 $DP$，如果一个虚树上一个点 $u$ 需要被强制选出，那么强制令 $f_u = 0$。

~~然后大部分题解就止步于此了，生气。~~

## 实现
因为只建了一次虚树，所以每一条边的 $a,b,c,d$ 都可以被预处理。对于虚树上的一条边 $(u,v)$，找到它在原树上对应的链。初始化 $a = d = 1,b = c = 0$。之后每次操作，找到 $v$ 的父亲节点 $w$，处理出 $f_w',g_w'$ 并更新 $a,b,c,d$ 即可。如果某一次操作中 $w = u$，立刻停止更新，不要计入 $f_u',g_u'$ 的贡献。

割去一个子树的贡献显然可以通过乘逆元实现。

对于每一个虚树上的节点 $u$，根据其子节点 $v$ 的状态和边上的 $a,b,c,d$ 求出新的 $f_v,g_v$ 后朴素转移即可。

还剩一个问题：每个点的初始状态是什么？一种朴素的想法是令虚树上的非叶子节点的初始状态为 $f_u = g_u = 1$，叶子节点的状态为无限制时的 $f_u,g_u$。但是这样不完全正确：如果原树上一个子树内没有一个虚树上的节点，但是接在了一个虚树上的节点上，那么这颗子树的所有节点都不会在虚树上出现，但是它依然可能对答案产生贡献。

目前这种子树的贡献还没有被计入。所以我们在建出虚树后，把所有这样的子树的贡献乘到在虚树上的对应节点的初始状态即可。这种子树的判定可以通过将所有在虚树上的节点打上标记以后进行子树查询维护。注意这种子树的根节点一定要与虚树上的一个节点直接相连。

这样做甚至不需要特判叶子节点，原因显然。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5+114;
int n,m;
int f[N],dep[N],siz[N],son[N],dfn[N],out[N],top[N],tot;
int pa[N],pb[N],pos;
bool vis[N],e[N<<1];
LL F[N],G[N],mod = 998244353;
LL Pow(LL a,LL b)
{
	LL ret = 1;
	for(;b;b >>= 1)
	{
		if(b&1) ret = ret*a%mod;
		a = a*a%mod;
	}
	return ret;
}
struct graph
{
	int cnt = 1,nxt[N<<1],v[N<<1],h[N];
	void add(int a,int b)
	{
		nxt[++cnt] = h[a];
		v[cnt] = b;
		h[a] = cnt;
	}
}A,B;
void dfs1(int x,int fa)
{
	f[x] = fa; dep[x] = dep[fa]+1;
	dfn[x] = ++tot; siz[x] = 1; vis[x] = 1;
	for(int i = A.h[x];i;i = A.nxt[i])
	{
		int y = A.v[i];
		if(y == fa || vis[y]) continue;
		e[i] = e[i^1] = 1;
		dfs1(y,x);
		siz[x] += siz[y];
		if(siz[son[x]] < siz[y])
			son[x] = y;
	}
	out[x] = tot;
}
void dfs2(int x,int t)
{
	top[x] = t;
	if(!son[x]) return;
	dfs2(son[x],t);
	for(int i = A.h[x];i;i = A.nxt[i])
	{
		int y = A.v[i];
		if(y == f[x] || y == son[x] || !e[i]) continue;
		dfs2(y,y);
	}
}
int lca(int x,int y)
{
	int fx = top[x],fy = top[y];
	while(fx != fy)
	{
		if(dep[fx] < dep[fy]) swap(fx,fy),swap(x,y);
		x = f[fx]; fx = top[x];
	}
	if(dep[x] > dep[y]) swap(x,y);
	return x;
}
void predp(int x)
{
	F[x] = G[x] = 1;
	for(int i = A.h[x];i;i = A.nxt[i])
	{
		int y = A.v[i];
		if(y == f[x] || !e[i]) continue;
		predp(y);
		F[x] = F[x]*(F[y]+G[y])%mod;
		G[x] = G[x]*F[y]%mod;
	}
}
void tarjan()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		A.add(a,b);
		A.add(b,a);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(int i = 2;i <= A.cnt;i += 2)
		if(!e[i])
		{
			pa[pos] = A.v[i];
			pb[pos] = A.v[i+1];
			pos++;
		}
}
bool cmp(int a,int b) { return dfn[a] < dfn[b]; }
int q[N],sum[N],p;
LL cp0[N],cp1[N]; 
void build()
{
	for(int j = 0;j < pos;j++)
		q[++p] = pa[j],q[++p] = pb[j];
	q[++p] = 1;
	sort(q+1,q+p+1,cmp);
	m = p;
	for(int j = 2;j <= p;j++)
		q[++m] = lca(q[j-1],q[j]);
	sort(q+1,q+m+1);
	p = unique(q+1,q+m+1)-q-1;
	sort(q+1,q+p+1,cmp);
	for(int i = 2;i <= p;i++)
	{
		int x = q[i-1],y = q[i],z = lca(x,y);
		B.add(y,z);
		B.add(z,y);
	}
	for(int i = 1;i <= p;i++)
		sum[dfn[q[i]]] = 1;
	for(int i = 1;i <= n;i++)
		sum[i] += sum[i-1];
	for(int j = 1;j <= p;j++)
	{
		int x = q[j];
		cp0[x] = cp1[x] = 1;
		for(int i = A.h[x];i;i = A.nxt[i])
		{
			int y = A.v[i];
			if(sum[out[y]]-sum[dfn[y]-1]) continue;
			cp0[x] = cp0[x]*(F[y]+G[y])%mod;
			cp1[x] = cp1[x]*F[y]%mod;
		}
	}
}
LL k0[N],k1[N],k2[N],k3[N];
void getk(int x,int y)
{
	int p = y;
	k0[p] = k3[p] = 1;
	k1[p] = k2[p] = 0;
	for(;;)
	{
		if(f[y] == x) break;
		int fa = f[y];
		LL K0 = F[fa]*Pow(F[y]+G[y],mod-2)%mod;
		LL K1 = G[fa]*Pow(F[y],mod-2)%mod;
		LL a = k2[p],b = k3[p];
		k2[p] = K1*k0[p]%mod;
		k3[p] = K1*k1[p]%mod; 
		k0[p] = K0*(k0[p]+a)%mod;
		k1[p] = K0*(k1[p]+b)%mod;
		y = fa;
	}
}
void dpk(int x,int fa)
{
	for(int i = B.h[x];i;i = B.nxt[i])
	{
		int y = B.v[i];
		if(y == fa) continue;
		getk(x,y);
		dpk(y,x);
	}
}
LL K0[N],K1[N];
bool tag[N];
void fun(int x,int fa)
{
	K0[x] = cp0[x];
	K1[x] = cp1[x];
	for(int i = B.h[x];i;i = B.nxt[i])
	{
		int y = B.v[i];
		if(y == fa) continue;
		fun(y,x);
		LL ky0 = (k0[y]*K0[y]+k1[y]*K1[y])%mod;
		LL ky1 = (k2[y]*K0[y]+k3[y]*K1[y])%mod; 
		K0[x] = K0[x]*(ky0+ky1)%mod;
		K1[x] = K1[x]*ky0%mod; 
	}
	if(tag[x]) K0[x] = 0;
}
void solve()
{
	LL ans = (F[1]+G[1])%mod;
	for(int i = 1;i < (1<<pos);i++)
	{
		int k = 0;
		for(int j = 0;j < pos;j++)
			k += ((i>>j)&1);
		for(int j = 1;j <= p;j++)
			tag[q[j]] = 0;
		for(int j = 0;j < pos;j++)
			if((i>>j)&1)
				tag[pa[j]] = tag[pb[j]] = 1;
		fun(1,0);
		LL ret = K0[1]+K1[1];
		if(k&1) ans = (ans-ret)%mod;
		else ans = (ans+ret)%mod;
	}
	ans = (ans+mod)%mod;
	printf("%lld",ans);
}
int main()
{
	tarjan();
	predp(1);
	build();
	dpk(1,0);
	solve();
 	return 0;
}
```


---

## 作者：Mobius127 (赞：1)

[题传](https://www.luogu.com.cn/problem/P4426)

纪念一手 800 AC。

DP 牛牛题，虚树 板板题。

若 $m=n-1$，则这是一棵树，那么显然有个很 easy 的动态规划，设 $f_{x, 0/1}$ 为当前子树中 不选/选 根的方案数：

$$f_{x,0}=\prod_{(x, y) \in T} (f_{y, 0}+f_{y, 1})$$

$$f_{x,1}=\prod_{(x, y) \in T} f_{y, 0}$$

发现 $m-(n-1) \le 11$，什么意思呢？我们在原图中构造一颗生成树，则非树边不超过 $11$ 条，我们弄出来这 $11$ 条边对应的点集 $D$。

考虑暴力枚举集合 $D$ 中的所有点的状态（是否在最终备选集合中），那么就珂以无视这 $11$ 条额外边了，此时仍然还是树形 DP，复杂度 $O(2^{22}n)$，显然过不去。


考虑到每次只有一堆关键点（$D$ 中的点）的限制条件被改变，这让我们联想到了虚树，那么建出虚树，考虑如何算虚树上相邻两点之间的贡献，不难发现中间这个部分还是一棵小树，且这棵树内显然是没有其他关键点的（不然就不满足虚树定义），那么我们提前将这个部分的答案预处理好，然后枚举 $D$ 状态的时候在虚树上跑一遍计数 DP 就行了。

设 $g(x, y, 0/1, 0/1)$ 为 原树上 $x-y$ 路径所在连通块中，满足 $x$ 选/不选，$y$ 选/不选 的方案数，则：

$$f_{x,ty1}=k_x\prod_y (\sum_{ty2} f_{y,ty2} \times g(x, y, ty1, ty2))$$

注意虚树上的点在原树中除了连向儿子的边外可能还有一些单链，这些构成了上式的系数 $k_x$。

[$Code$](https://loj.ac/s/1527985)

---

## 作者：劉子颺 (赞：1)

一篇毒瘤且不失精致

代码不短也不长的题解

如果问题转化为：给定一棵树每次表示某个点只能选啥

那么这不过是DDP的套路 在链分治下把矩阵改一下即可

但是实际上对于本题，边很少，那么何妨不适用暴力枚举非树边来建可不可行

那么这和DDP没有本质区别

但是问题是2^2n只有85分 所以考虑一下2^n枚举

然后DDP的时候由于是覆盖 注意转换一下标记

```
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<stack>
#include<ctime>
#include<vector>
typedef long long LL;
using namespace std;
const int N=2e5+100;
const int mod=998244353;
inline void read(int &x){
	x=0;
	int f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=f;
}
LL Quick_Pow(LL x,int k){
	LL ret=1;
	while(k){
		if(k&1)ret=ret*x%mod;
		x=x*x%mod;
		k>>=1;
	}
	return ret;
}
struct DivZero{
	LL x,cnt;
	DivZero(const LL &_x=0,const LL &_cnt=0):x(_x),cnt(_cnt){}
	LL val(){return cnt?0:x;}
	friend DivZero operator * (DivZero A,LL a){
		if(!a)A.cnt++;
		else A.x=A.x*a%mod;
		return A;
	}
	friend DivZero operator / (DivZero A,LL a){
		if(!a)A.cnt--;
		else A.x=A.x*Quick_Pow(a,mod-2)%mod;
		return A;
	}
	void Clr(){
		cnt=x=0;
	}
}F[N][2];
int n,m;
struct Front_Star{
	int u,v,nxt;
}e[N<<2];
int cnt=1;
int first[N];
void add(int u,int v){
	++cnt;
	e[cnt].u=u;
	e[cnt].v=v;
	e[cnt].nxt=first[u];
	first[u]=cnt;
}
int fa[N];
int dep[N];
int son[N];
int siz[N];
int top[N];
int bot[N];
int tree[N];
int dfn_tot=0;
void DFS1(int u,int fat,int depth){
	fa[u]=fat;
	dep[u]=depth;
	siz[u]=1;
	for(int i=first[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fat)continue;
		DFS1(v,u,depth+1);
		siz[u]+=siz[v];
		if(!son[u]||siz[son[u]]<siz[v])son[u]=v;
	}
}
void DFS2(int u,int tp){
	tree[u]=++dfn_tot;
	top[u]=tp;
	bot[tp]=u;
	if(son[u]){
		DFS2(son[u],tp);
	}
	for(int i=first[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(son[u]==v||fa[u]==v)continue;
		DFS2(v,v);
	}
}
struct Matrix{
	LL a[2][2];
	Matrix(){memset(a,0,sizeof(a));}
	friend Matrix operator * (const Matrix &A,const Matrix &B){
		Matrix ret;
		for(int i=0;i<2;++i){
			for(int j=0;j<2;++j){
				for(int k=0;k<2;++k){
					ret.a[i][j]=(ret.a[i][j]+A.a[i][k]*B.a[k][j])%mod;	
				}
			}
		}
		return ret;
	}
	void Print(){
		cout<<"G: \n";
		for(int i=0;i<2;++i){
			for(int j=0;j<2;++j){
				cout<<a[i][j]<<" ";
			}
			cout<<'\n';
		}
	}
};
struct Segment_Tree{
	#define lc (p<<1)
	#define rc (p<<1|1)
	struct Segment_Node{
		int lson,rson;
		Matrix A;
	}T[N<<2];
	void PushUp(int p){
		T[p].A=T[rc].A*T[lc].A;
	}
	void Build(int p,int l,int r){
		T[p].lson=l;
		T[p].rson=r;
		if(l==r)return;
		int mid=(l+r)>>1;
		Build(lc,l,mid);
		Build(rc,mid+1,r);
		PushUp(p);
	}
	void Update(int p,int pos,Matrix A){
		if(T[p].lson==T[p].rson){
			T[p].A=A;
			return;
		}
		int mid=(T[p].lson+T[p].rson)>>1;
		if(pos<=mid)Update(lc,pos,A);
		else Update(rc,pos,A);
		PushUp(p);
	}
	Matrix Query(int p,int l,int r){
		if(l<=T[p].lson&&T[p].rson<=r){
			return T[p].A;
		}
		int mid=(T[p].lson+T[p].rson)>>1;
		if(l<=mid&&mid>=r)return Query(lc,l,r);
		if(mid< l&&mid< r)return Query(rc,l,r);
		return Query(rc,l,r)*Query(lc,l,r);
	}
	#undef lc
	#undef rc 
}T;
void Pre(int u){
	stack<int>S;
	int x=u;
	S.push(x);
	for(;son[x];x=son[x])S.push(son[x]);
	while(!S.empty()){
		int x=S.top();
		S.pop();
		F[x][0]=DivZero(1,0);
		F[x][1]=DivZero(1,0);
		for(int i=first[x];i;i=e[i].nxt){
			int v=e[i].v;
			if(v==son[x]||v==fa[x])continue;
			Pre(v);
			Matrix now=T.Query(1,tree[top[v]],tree[bot[top[v]]]);
			F[x][0]=F[x][0]*(now.a[0][0]+now.a[0][1]);
			F[x][1]=F[x][1]*now.a[0][0];
		}
		Matrix now;
		if(son[x]){
			now.a[0][0]=F[x][0].val();
			now.a[1][0]=F[x][0].val();
			now.a[0][1]=F[x][1].val();
		}
		else{
			now.a[0][0]=now.a[0][1]=1;
		}
		T.Update(1,tree[x],now);
	}
}
int USE[N];
void Modify(int x,int opt){
	for(int u=x;fa[top[u]];u=fa[top[u]]){
		Matrix now=T.Query(1,tree[top[u]],tree[bot[top[u]]]);
		int P=fa[top[u]];
		F[P][0]=F[P][0]/(now.a[0][0]+now.a[0][1]);
		F[P][1]=F[P][1]/now.a[0][0];
		now=T.Query(1,tree[P],tree[P]);
	}
	if(son[x]){
		Matrix now=T.Query(1,tree[x],tree[x]);
		if(!opt){
			now.a[0][1]=0;
		}
		else{
			now.a[0][0]=now.a[1][0]=0;
		}
		T.Update(1,tree[x],now);
	}
	else{
		Matrix now=T.Query(1,tree[x],tree[x]);
		if(!opt){
			now.a[0][1]=0;
		}
		else now.a[0][0]=0;
		T.Update(1,tree[x],now);
	}
	for(int u=x;fa[top[u]];u=fa[top[u]]){
		Matrix now=T.Query(1,tree[top[u]],tree[bot[top[u]]]);
		int P=fa[top[u]];
		F[P][0]=F[P][0]*(now.a[0][0]+now.a[0][1]);
		F[P][1]=F[P][1]*now.a[0][0];
		now.a[0][1]=F[P][1].val();
		now.a[0][0]=now.a[1][0]=F[P][0].val();	
		if(USE[P]==0){
			now.a[0][1]=0;
		}
		if(USE[P]==1){
			now.a[0][0]=0;
			now.a[1][0]=0;
		}
		T.Update(1,tree[P],now);
	}
}
void ReBack(int x){
	USE[x]=-1;
	for(int u=x;fa[top[u]];u=fa[top[u]]){
		Matrix now=T.Query(1,tree[top[u]],tree[bot[top[u]]]);
		int P=fa[top[u]];
		F[P][0]=F[P][0]/(now.a[0][0]+now.a[0][1]);
		F[P][1]=F[P][1]/now.a[0][0];
	}
	if(son[x]){
		Matrix now;
		now.a[0][0]=F[x][0].val();
		now.a[1][0]=F[x][0].val();
		now.a[0][1]=F[x][1].val();
		T.Update(1,tree[x],now);
	}
	else{
		Matrix now;
		now.a[0][0]=now.a[0][1]=1;
		T.Update(1,tree[x],now);
	}
	for(int u=x;fa[top[u]];u=fa[top[u]]){
		Matrix now=T.Query(1,tree[top[u]],tree[bot[top[u]]]);
		int P=fa[top[u]];
		F[P][0]=F[P][0]*(now.a[0][0]+now.a[0][1]);
		F[P][1]=F[P][1]*now.a[0][0];
		now.a[0][1]=F[P][1].val();
		now.a[0][0]=now.a[1][0]=F[P][0].val();
		if(USE[P]==0){
			now.a[0][1]=0;
		}
		if(USE[P]==1){
			now.a[0][0]=0;
			now.a[1][0]=0;
		}		
		T.Update(1,tree[P],now);
	}	
}
int FA[N];
int GetFa(int x){
	if(FA[x]==x)return x;
	else return FA[x]=GetFa(FA[x]);
}
void Merge(int x,int y){
	FA[GetFa(x)]=GetFa(y);
}
vector<pair<int,int> >Gra;
LL ans=0;
int tot=0;
bool vis[21];
int A[N];
bool Judge(){
	bool GG=0;
	for(int i=0;i<tot;++i){
		USE[Gra[i].first]=USE[Gra[i].second]=-1;
	}
	for(int i=0;i<tot;++i){
		if(vis[i+1]){
			if(USE[Gra[i].first]==0)GG=1;
			USE[Gra[i].first]=1;
			if(USE[Gra[i].second]==1)GG=1;
			USE[Gra[i].second]=0;
		}
		else{
			if(USE[Gra[i].first]==1)GG=1;
			USE[Gra[i].first]=0;
		}
	}
	return GG;
}
void Check(){
	if(Judge())return;
	for(int i=1;i<=A[0];++i){
		if(USE[A[i]]==-1)continue;
		Modify(A[i],USE[A[i]]);
	}
	Matrix now=T.Query(1,tree[1],tree[bot[1]]);
	ans=(ans+now.a[0][0]+now.a[0][1])%mod;
	for(int i=1;i<=A[0];++i){
		if(USE[A[i]]==-1)continue;
		ReBack(A[i]);
	}
}
void DFS(int Id){
	if(Id==tot+1){
		Check();
		return;
	}
	vis[Id]=1;
	DFS(Id+1);
	vis[Id]=0;
	DFS(Id+1);
}
int main(){
//	freopen("P4426.in","r",stdin);
//	freopen("P4426.out","w",stdout);
	read(n);read(m); 
	for(int i=1;i<=n;++i)FA[i]=i;
	
	memset(USE,-1,sizeof(USE));
	
	for(int i=1;i<=m;++i){
		int u,v;
		read(u);read(v);
		if(GetFa(u)==GetFa(v)){
			Gra.push_back(make_pair(u,v));
			A[++A[0]]=u;
			A[++A[0]]=v;
		}
		else{
			Merge(u,v);
			add(u,v);add(v,u);	
		}	
	}
	sort(A+1,A+1+A[0]);
	A[0]=unique(A+1,A+1+A[0])-A-1;
	DFS1(1,0,1);
	DFS2(1,1);
	T.Build(1,1,n);
	Pre(1);
//	exit(0); 
	if(m==n-1){
		Matrix now=T.Query(1,tree[1],tree[bot[1]]);
		ans=(now.a[0][0]+now.a[0][1])%mod;	
	}
	else{
		tot=m-(n-1);
		DFS(1);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Leasier (赞：1)

不难想到本题可以抽象为：给定一张 $n$ 个点、$m$ 条边的无向图，求其**可空**独立集的数量 $\bmod \ 998244353$。

独立集问题是一个 NP 问题。但由于 $0 \leq m - n + 1 \leq 11$，我们可以考虑求出它的一棵生成树，并枚举非树边的两个端点是否被选中。考虑钦定其中一个端点不被选中，另一个端点任意和其中一个端点被选中和另一个端点不被选中的情况，则枚举的时间复杂度为 $O(2^{m - n + 1})$。

现在先考虑 $m = n - 1$（即原图为一棵树的情况），显然可以 dp。设 $dp_{u, 0 / 1}$ 表示 $u$ 不被 / 被选中时 $u$ 子树内的方案数。

转移：$dp_{u, 0} = \displaystyle\prod_{v \in son_u} (dp_{v, 0} + dp_{v, 1})$，$dp_{u, 1} = \displaystyle\prod_{v \in son_u} dp_{v, 0}$。

答案：$dp_{1, 0} + dp_{1, 1}$。

考虑钦定 $u$ 不被 / 被选中的情况，发现此时我们相当于钦定 $dp_{u, 1 / 0} = 0$。

于是可以动态 dp。套路地，设 $dp'_{u, 0 / 1}$ 表示 $u$ 不被 / 被选中时 $u$ 子树内（不包括 $u$ 的重儿子）的方案数。

转移：$dp'_{u, 0} = \displaystyle\prod_{v \in son_u, v \neq hs_u} (dp_{v, 0} + dp_{v, 1})$，$dp_{u, 0} = dp'_{u, 0} (dp_{hs_u, 0} + dp_{hs_u, 1})$，$dp'_{u, 1} = \displaystyle\prod_{v \in son_u, v \neq hs_u} dp_{v, 0}$，$dp_{u, 1} = dp'_{u, 1} dp_{hs_u, 0}$。

于是可以得出转移矩阵：$\begin{bmatrix} dp_{hs_u, 0}\ dp_{hs_u, 1} \end{bmatrix} \begin{bmatrix} dp'_{u, 0}\ dp'_{u, 1}\\ dp'_{u, 0}\ 0 \end{bmatrix} = \begin{bmatrix} dp_{u, 0}\ dp_{u, 1} \end{bmatrix}$。

直接上动态 dp 即可。注意乘法时可能会遇到 $0$，此时我们直接用一个栈存储更改前的状态，撤销时从栈中取出元素即可。时间复杂度为 $O(n + m + 2^{n - m + 1} \log^2 n)$。

代码：
```cpp
#include <iostream>
#include <stack>
#include <cstring>

using namespace std;

typedef long long ll;

typedef struct {
	int nxt;
	int end;
} Edge;

typedef struct Matrix_tag {
	int n;
	int m;
	ll a[3][3];
	Matrix_tag(){}
	Matrix_tag(int n_, int m_){
		n = n_;
		m = m_;
		memset(a, 0, sizeof(a));
	}
} Matrix;

typedef struct {
	int l;
	int r;
	Matrix product;
} Node;

int cnt = 0, mod = 998244353;
Matrix e(2, 2);
int root[100007], head[100007], from[17], to[17], fa[100007], depth[100007], size[100007], hs[100007], dfn[100007], rnk[100007], top[100007], bottom[100007], id[100007], mark[100007], dot[17];
ll dp1[100007][7], dp2[100007][7];
Edge edge[200007];
Node tree[400007];
stack<Matrix> s;

Matrix operator *(const Matrix a, const Matrix b){
	Matrix ans(a.n, b.m);
	for (register int i = 1; i <= a.n; i++){
		for (register int j = 1; j <= b.m; j++){
			for (register int k = 1; k <= a.m; k++){
				ans.a[i][j] = (ans.a[i][j] + a.a[i][k] * b.a[k][j] % mod) % mod;
			}
		}
	}
	return ans;
}

Matrix operator *=(Matrix &a, const Matrix b){
	return a = a * b;
}

inline void init(int n){
	e.a[1][1] = e.a[2][2] = 1;
	for (register int i = 1; i <= n; i++){
		root[i] = i;
	}
}

int get_root(int x){
	if (root[x] == x) return x;
	return root[x] = get_root(root[x]);
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs1(int u, int father){
	fa[u] = father;
	depth[u] = depth[father] + 1;
	size[u] = 1;
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != father){
			dfs1(x, u);
			size[u] += size[x];
			if (hs[u] == 0 || size[hs[u]] < size[x]) hs[u] = x;
		}
	}
}

void dfs2(int u){
	dp1[u][0] = dp1[u][1] = 1;
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != fa[u]){
			dfs2(x);
			if (x != hs[u]){
				dp1[u][0] = dp1[u][0] * (dp2[x][0] + dp2[x][1]) % mod;
				dp1[u][1] = dp1[u][1] * dp2[x][0] % mod;
			}
		}
	}
	dp2[u][0] = dp1[u][0];
	dp2[u][1] = dp1[u][1];
	if (hs[u] != 0){
		dp2[u][0] = dp2[u][0] * (dp2[hs[u]][0] + dp2[hs[u]][1]) % mod;
		dp2[u][1] = dp2[u][1] * dp2[hs[u]][0] % mod;
	}
}

void dfs3(int u, int cur_top, int &id){
	id++;
	dfn[u] = id;
	rnk[id] = u;
	top[u] = cur_top;
	if (hs[u] == 0){
		bottom[cur_top] = u;
	} else {
		dfs3(hs[u], cur_top, id);
		for (register int i = head[u]; i != 0; i = edge[i].nxt){
			int x = edge[i].end;
			if (x != fa[u] && x != hs[u]) dfs3(x, x, id);
		}
	}
}

inline void update(int x){
	tree[x].product = tree[x * 2 + 1].product * tree[x * 2].product;
}

void build(int x, int l, int r){
	tree[x].l = l;
	tree[x].r = r;
	if (l == r){
		tree[x].product = Matrix(2, 2);
		tree[x].product.a[1][1] = tree[x].product.a[2][1] = dp1[rnk[l]][0];
		tree[x].product.a[1][2] = dp1[rnk[l]][1];
		id[rnk[l]] = x;
		return;
	}
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
	update(x);
}

Matrix get_product(int x, int l, int r){
	if (l <= tree[x].l && tree[x].r <= r) return tree[x].product;
	int mid = (tree[x].l + tree[x].r) >> 1;
	Matrix ans = e;
	if (r > mid) ans *= get_product(x * 2 + 1, l, r);
	if (l <= mid) ans *= get_product(x * 2, l, r);
	return ans;
}

inline ll query(int u){
	Matrix product = get_product(1, dfn[u], dfn[bottom[top[u]]]);
	return (product.a[1][1] + product.a[1][2]) % mod;
}

void do_modify(int x, int pos, Matrix mat){
	if (tree[x].l == tree[x].r){
		tree[x].product = mat;
		return;
	}
	if (pos <= ((tree[x].l + tree[x].r) >> 1)){
		do_modify(x * 2, pos, mat);
	} else {
		do_modify(x * 2 + 1, pos, mat);
	}
	update(x);
}

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void modify(int u, Matrix mat){
	while (u != 0){
		Matrix pre = get_product(1, dfn[top[u]], dfn[bottom[top[u]]]), cur;
		do_modify(1, dfn[u], mat);
		cur = get_product(1, dfn[top[u]], dfn[bottom[top[u]]]);
		u = fa[top[u]];
		if (u == 0) break;
		mat = tree[id[u]].product;
		s.push(mat);
		mat.a[1][1] = mat.a[2][1] = mat.a[1][1] * quick_pow(pre.a[1][1] + pre.a[1][2], mod - 2, mod) % mod * (cur.a[1][1] + cur.a[1][2]) % mod;
		mat.a[1][2] = mat.a[1][2] * quick_pow(pre.a[1][1], mod - 2, mod) % mod * cur.a[1][1] % mod;
	}
}

inline void mustnot(int u){
	Matrix mat = tree[id[u]].product;
	s.push(mat);
	mat.a[1][2] = 0;
	modify(u, mat);
}

inline void must(int u){
	Matrix mat = tree[id[u]].product;
	s.push(mat);
	mat.a[1][1] = mat.a[2][1] = 0;
	modify(u, mat);
}

inline void rollback(int u){
	int cnt = 0;
	for (register int i = u; i != 0; i = fa[top[i]]){
		dot[++cnt] = i;
	}
	for (register int i = cnt; i >= 1; i--){
		Matrix cur = s.top();
		s.pop();
		do_modify(1, dfn[dot[i]], cur);
	}
}

ll dfs(int cur, int n){
	if (cur > n) return query(1);
	int cur_i = cur + 1;
	ll ans = 0;
	if (mark[from[cur]] != 2){
		int x = mark[from[cur]];
		mark[from[cur]] = 1;
		mustnot(from[cur]);
		ans = dfs(cur_i, n);
		rollback(from[cur]);
		mark[from[cur]] = x;
	}
	if (mark[from[cur]] != 1 && mark[to[cur]] != 2){
		int x = mark[from[cur]], y = mark[to[cur]];
		mark[from[cur]] = 2;
		mark[to[cur]] = 1;
		must(from[cur]);
		mustnot(to[cur]);
		ans = (ans + dfs(cur_i, n)) % mod;
		rollback(to[cur]);
		rollback(from[cur]);
		mark[from[cur]] = x;
		mark[to[cur]] = y;
	}
	return ans;
}

int main(){
	int n, m, k = 0, id = 0;
	cin >> n >> m;
	init(n);
	for (register int i = 1; i <= m; i++){
		int u, v, u_root, v_root;
		cin >> u >> v;
		u_root = get_root(u);
		v_root = get_root(v);
		if (u_root != v_root){
			root[u_root] = v_root;
			add_edge(u, v);
			add_edge(v, u);
		} else {
			k++;
			from[k] = u;
			to[k] = v;
		}
	}
	dfs1(1, 0);
	dfs2(1);
	dfs3(1, 1, id);
	build(1, 1, n);
	cout << dfs(1, k);
	return 0;
}
```

---

## 作者：Illusory_dimes (赞：1)

[不知道更好还是更坏的阅读体验](https://www.cnblogs.com/Illusory-dimes/p/15483565.html)

## Description

给定 $n$ 个点， $m$ 条约束关系 $a$ 和 $b$ ，表示 $a$ 和 $b$ 不能同时被选择。

问有多少种选择方案，答案对 998244353 取模。

题意概括：求一张图上的独立集数量（为了凸显逼格。。）

![](https://cdn.luogu.com.cn/upload/image_hosting/2wydm5kn.png)


$n \leq 10 ^ 5\ ,\ n - 1\leq m \leq n + 10$

## Analysis

这个 $m$ 的范围有点诡异，如果把图建出来，最多只会有 $11$ 条非树边，或许可以以此作为切入点呢。

一个比较正常的想法，先去想对于一个树的话，怎么做这道题。

这应该是一个基础到家了的树形 DP 吧，$F_{u, 0/1}$ 表示以 u 为根的子树里面， u 这个节点选 / 不选的方案数，最终答案就是 $F_{1, 0} + F_{1, 1}$ 。

转移式子就是：

$$
F_{u, 0} = \prod_{(u, v) \in S} {(F_{v, 0} + F_{v, 1})}
$$

$$
F_{u, 1} = \prod_{(u, v) \in S} {F_{v, 0}}
$$

然后就去要去想怎么扩展到一个非树边不超过 $11$ 个的图上。

## Solution

### Part1

由于边很少，我们甚至可以直接枚举，对于每条边 $(u, v)$ （同时钦定 $u$ 的 dfn 序小于 $v$ ）的状态就是 $(1, 0)\ ,\ (0, 1)\ ,\ (0, 0)$ （ $1$ 表示选， $0$ 表示不选），同时注意到后面两种并不排斥，可以一块计算，所以我们就可以以 $u$ 选 / 不选作为一条边的状态， $O\Big(2 ^ {m - (n - 1)}\Big)$ 的去枚举，然后 $O(n)$ 的算。

总体时间复杂度就是 $O\Big(2^{m - (n - 1)} \cdot n\Big)$ 的啦。

从数据上来看这完完全全能拿到 $70pts$ 呀！

然后写完过后实测有 $75pts$ 。。

（到这里的话，个人评价是道蓝以下的 DP 题）

### Part2 

可以感觉到每次都是进行的相同的操作，只是对于有些点可能确定了选 / 不选，不再存在贡献，就会影响了整个树整体的答案，然后我们就因此重新算了一遍，属实有点亏。

然后想起来非树边一共就 $11$ 条，考虑把所有多余的边对应的点拎出来建成虚树，那么这样的话最多会有 $22$ 个关键点，虚树大小也是 $\leq (44 + 1)$ 。

接下来考虑在虚树上预处理出来一点什么。

想到一开始的那两个式子，很显然不能直接硬算，因为虚树两个有边的点之间可能有不少被省略的点，这样就相当于一条边在原树上可能是一条链。

因为中间的点能被省略掉，说明肯定不是关键点，所以可以正常转移，那么对于原树上一条链 $u \Rightarrow x_1 \Rightarrow x_2 \Rightarrow ... \Rightarrow x_k \Rightarrow v$ ，假设 $F_{i, 0 / 1}$ 转移前的值为 $G_{i, 0 / 1}$ ，转移式子有：

$$
\left\{
\begin{aligned}
F_{x_k\ , 0}& = G_{x_k\ , 0} \cdot (F_{v, 0} + F_{v, 1})
\\
F_{x_k\ , 1}& = G_{x_k\ , 0} \cdot F_{v, 0}
\end{aligned}
\right.

\left\{
\begin{aligned}
F_{x_{k - 1}\ \ , 0}& = G_{x_{k - 1}\ \ , 0} \cdot (F_{x_k\ , 0} + F_{x_k\ , 1})
\\
F_{x_{k - 1}\ \ , 1}& = G_{x_{k - 1}\ \ , 0} \cdot F_{x_k\ , 0}
\end{aligned}
\right.
$$

合并带入有：

$$
\left\{
\begin{aligned}
F_{x_{k - 1}\ \ , 0}& = G_{x_{k - 1}\ \ , 0} \cdot (G_{x_k\ , 0} \cdot (F_{v, 0} + F_{v, 1}) + G_{x_k\ , 0} \cdot F_{v, 0})
\\
F_{x_{k - 1}\ \ , 1}& = G_{x_{k - 1}\ \ , 0} \cdot (G_{x_k\ , 0} \cdot F_{v, 0})
\end{aligned}
\right.
$$

$$
\Longrightarrow
$$

$$
\left\{
\begin{aligned}
F_{x_{k - 1}\ \ , 0}& = (2\cdot G_{x_{k - 1}\ \ , 0} \cdot G_{x_k\ , 0}) \cdot F_{v, 0} + (G_{x_{k - 1}\ \ , 0} \cdot G_{x_k\ , 0}) \cdot F_{v, 1}
\\
F_{x_{k - 1}\ \ , 1}& = (G_{x_{k - 1}\ \ , 0} \cdot G_{x_k\ , 0}) \cdot F_{v, 0}
\end{aligned}
\right.
$$

总的来说，这会转化成一个带系数 $coe$ 的式子，大概就是：

$$
\left\{
\begin{aligned}
F_{u, 0}& = coe_{0, 0} \cdot F_{v, 0} + coe_{0, 1} \cdot F_{v, 1}
\\
F_{u, 1}& = coe_{1, 0} \cdot F_{v, 0} + coe_{1, 1} \cdot F_{v, 1}
\end{aligned}
\right.
$$

那么对于虚树上任意两个相连的点，都有类似的式子，可以预处理出这个 $coe$ ，由于这玩意真的特别像 $F$ ，同样可以选择大法师处理，也是 $O(n)$ 。

同样，树上所有点的 $F$ 也不全都是 $1$ 了，因为考虑到我们处理的系数什么的都是跟虚树上的点有关，所以只要子树内不包含虚树上的点的话，至始至终答案都是一样的，就把这些点的 $F$ 按照正常的 DP 做法处理一下就可以了。

统计答案的话，还是先枚举所有非树边的选点的状态，然后按照这个把虚树上的点的初值赋好我们已经预处理好的系数，跑一遍虚树更新答案就行了。

这样按照我们前面设想的系数的含义，相当于是跳过了没有必要再次计算的非虚树点，直接一步到位，然后达到了节省时间的目的。

时间复杂度 $O\Big(n + 2^{m - (n - 1)} \cdot (m - (n - 1))\Big)$ 。

（由于实现雀食有点麻烦我还是参考了 [Soulist](https://www.luogu.com.cn/user/30036 "Soulist") 的写法，雀食非常简洁易懂）

## Code

```cpp
/*

*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const int mod = 998244353;
int n, m, num, lim, k, a[N], fst[N], tot, ifst[N], itot;
int _k, _a[N], vis[N], cnt, banx[N], bany[N];
int ft[N], fa[N][18], dfn[N], tim, dep[N], sta[N], top;
ll f[N][2], g[N][2], coe[2][N][2], ans;
struct edge {
	int nxt, to;
} e[N << 1], ie[N << 1];
inline int read() {
	char ch = getchar();
	int s = 0, w = 1;
	while (ch < '0' || ch > '9') {if(ch == '-') w = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {s = (s << 3) + (s << 1) + ch - '0'; ch = getchar();}
	return s * w;
}
inline int find(int x) {
	if (ft[x] == x) return ft[x];
	return ft[x] = find(ft[x]);
}
inline void add(int u, int v) {
	e[++tot] = (edge) {fst[u], v};
	fst[u] = tot;
}
inline void iadd(int u, int v) {
	ie[++itot] = (edge) {ifst[u], v};
	ifst[u] = itot;
}
inline void dfs1(int u, int fth) {
	dep[u] = dep[fth] + 1;
	dfn[u] = ++tim; fa[u][0] = fth;
	for (int i = 1; i <= 17; ++i) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (int i = fst[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == fth) continue;
		dfs1(v, u);
		vis[u] += vis[v];//要记得互相影响但是不在虚树上的点也不能遍历
	}
}
inline int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 17; ~i; --i) {
		if (dep[fa[u][i]] >= dep[v]) {
			u = fa[u][i];
		}
	}
	if (u == v) return v;
	for (int i = 17; ~i; --i) {
		if(fa[u][i] != fa[v][i]) {
			u = fa[u][i]; v = fa[v][i];
		}
	}
	return fa[u][0];
}
inline bool cmp(int x, int y) {
	return dfn[x] < dfn[y];
}
inline void IllusoryTree() {
	_k = k;
	for (int i = 1; i <= k; ++i) _a[i] = a[i];
	sort(a + 1, a + 1 + k, cmp);
	sta[top = 1] = 1; ifst[1] = 0;
	for (int i = 1; i <= k; ++i) {
		if (a[i] == 1) continue;
		int Lca = lca(sta[top], a[i]);
		if (sta[top] != Lca) {
			while (dfn[sta[top - 1]] > dfn[Lca]) {
				iadd(sta[top - 1], sta[top]); --top;
			}
			if (sta[top - 1] == Lca) {
				iadd(sta[top - 1], sta[top]); --top;
			}
			else {
				_a[++_k] = Lca;
				vis[Lca] = 1;
				ifst[Lca] = 0;
				iadd(Lca, sta[top]);
				sta[top] = Lca;
			}
		}
		sta[++top] = a[i]; ifst[a[i]] = 0;
	}
	for (int i = 1; i < top; ++i) {
		if (!vis[sta[i]]) {
			_a[++_k] = sta[i];
			vis[sta[i]] = 1;
		}
		iadd(sta[i], sta[i + 1]);
	}
	for (int i = 1; i <= _k; ++i) a[i] = _a[i];
	k = _k;
}
inline void dp_init(int u, int fth) {
	g[u][0] = g[u][1] = 1;
	for (int i = fst[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == fth || vis[v]) continue;
		dp_init(v, u);
		(g[u][0] *= (g[v][0] + g[v][1])) %= mod;
		(g[u][1] *= g[v][0]) %= mod;
	}
}
inline void dp_help(int u, int son) {
	f[u][0] = f[u][1] = 1;
	for (int i = fst[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == son || v == fa[u][0]) continue;
		dp_help(v, u);
		(f[u][0] *= (f[v][0] + f[v][1])) %= mod;
		(f[u][1] *= f[v][0]) %= mod;
	}
}
inline void calc_coe(int u, int fth) {
	int p = u;
	coe[0][u][0] = coe[0][u][1] = coe[1][u][0] = 1;
	while (fa[p][0] != fth) {
		int q = fa[p][0];
		dp_help(q, p);
		ll coe00 = coe[0][u][0], coe01 = coe[0][u][1];
		ll coe10 = coe[1][u][0], coe11 = coe[1][u][1];
		coe[0][u][0] = (coe00 * f[q][0] + coe10 * f[q][1]) % mod;
		coe[1][u][0] = coe00 * f[q][0] % mod;
		coe[0][u][1] = (coe01 * f[q][0] + coe11 * f[q][1]) % mod;
		coe[1][u][1] = coe01 * f[q][0] % mod;
		p = q;
	}
}
inline void dfs2(int u, int fth) {
	dp_init(u, fth); a[++k] = u; vis[u] = 1;
	if (u != fth) calc_coe(u, fth);
	for (int i = ifst[u]; i; i = ie[i].nxt) {
		int v = ie[i].to;
		if (v == fth) continue;
		dfs2(v, u);
	}
}
inline void dp_calc(int u, int fth) {
	for (int i = ifst[u]; i; i = ie[i].nxt) {
		int v = ie[i].to;
		if (v == fth) continue;
		dp_calc(v, u);
		(f[u][0] *= (coe[0][v][0] * f[v][0] + coe[0][v][1] * f[v][1]) % mod) %= mod;
		(f[u][1] *= (coe[1][v][0] * f[v][0] + coe[1][v][1] * f[v][1]) % mod) %= mod;
	}
}
int main() {
	n = read(); m = read();
	num = m - n + 1; lim = (1 << num);
	for (int i = 1; i <= n; ++i) ft[i] = i;
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		int x = find(u), y = find(v);
		if (x != y) {
			add(u, v); add(v, u);
			ft[x] = y;
		}
		else {
			if (!vis[u]) a[++k] = u, vis[u] = 1;
			if (!vis[v]) a[++k] = v, vis[v] = 1;
			banx[++cnt] = u; bany[cnt] = v;
		}
	}
	dfs1(1, 1);
	IllusoryTree();
	k = 0;
	dfs2(1, 1);
	/*if (!k) a[++k] = 1, vis[1] = k;
	sort(a + 1, a + 1 + k, cmp);*/
	for (int i = 0; i < lim; ++i) {
		for (int j = 1; j <= k; ++j) {
			f[a[j]][0] = g[a[j]][0];
			f[a[j]][1] = g[a[j]][1];
		}
		for (int j = 1; j <= cnt; ++j) {
			if ((1 << (j - 1)) & i) {
				f[banx[j]][0] = 0;
				f[bany[j]][1] = 0;
			}
			else f[banx[j]][1] = 0;
		}
		dp_calc(1, 0);
		ans += f[1][0] + f[1][1];
	}
	printf("%lld\n", ans % mod);
	return 0;
}
```

---

## 作者：hegm (赞：0)

### [[HNOI/AHOI2018]毒瘤](https://www.luogu.com.cn/problem/P4426)

考虑普通的树上独立集 dp。

$f_{i,0/1}$ 表示考虑 $i$ 的子树中，选/不选 $i$ 形成的独立集的方案数。

$f_{i,0}=\prod\limits_{u\in son_i} f_{u,0}+f_{u,1}$

$f_{i,1}=\prod\limits_{u\in son_i}f_{u,0}$

现在考虑每一条非树边的限制，假如是 $u\to v$ 那么两次考虑，$u$ 选，那么 $f_{v,1}$ 清零，重新做一遍。否则 $u$ 不选，$v$ 随意，$f_{u,1}$ 清零重新做一遍，那么又因为有 $11$ 个限制，所以是 $2^{11}\times n$ 的复杂度。

但是容易发现，更改后只有非树边的路径上的点的 $f$ 会发生变化，但这还不够，因为数量级别还是 $O(n)$ 的。

那么我们对这 $22$ 个特殊点建出虚树，那么考虑虚树上的一条边的实际上可以怎么转移，结论就是一条边（连接 $u,v$ 且 $dep_u<dep_v$）可以写成 $f_{u,0/1}=a\times f_{v,0}+b\times f_{v,1}$ 也就是一个常数倍。

一些小细节：对于虚树上的一条边，暴力跳到边顶的时候注意不能直接乘上权值。

在虚树上的点的不在虚树上的儿子要特殊统计。


### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define N 200005
#define mod 998244353
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,s[N][2][2],u[N],v[N],g[N],tot,p[N][2],q[N],cnt,ans,e[N][2];
int find(int x)
{
	if(g[x]==x)return x;
	return g[x]=find(g[x]);
}
bool vis[N][2],kl[N],awa[N];
int mul(int a,int b){return (1ll*a*b)%mod;}
int adt(int a,int b){return (1ll*a+b)%mod;}
struct fig
{
	struct node
	{
		int to,next,from;
	}k[N*2];
	int head[N],tot,dfn[N],cnt,dp[N][2],dep[N],f[N][21];
	void add(int from,int to)
	{
		k[++tot].to=to;
		k[tot].from=from;
		k[tot].next=head[from];
		head[from]=tot;
	}
	void dfs(int now,int fa)
	{
		dfn[now]=++cnt;
		f[now][0]=fa;dep[now]=dep[fa]+1;
		for(int i=1;i<=20;i++)f[now][i]=f[f[now][i-1]][i-1];
		for(int i=head[now];i;i=k[i].next)
		{
			if(k[i].to==fa)continue;
			dfs(k[i].to,now);
		}
	}
	void dne(int now)
	{
		dp[now][0]=dp[now][1]=1;
		e[now][0]=e[now][1]=1;
		for(int i=head[now];i;i=k[i].next)
		{
			if(k[i].to==f[now][0])continue;
			dne(k[i].to);
			dp[now][0]=mul(dp[now][0],adt(dp[k[i].to][0],dp[k[i].to][1]));
			dp[now][1]=mul(dp[now][1],dp[k[i].to][0]);
			if(!awa[k[i].to])
			{
				e[now][0]=mul(e[now][0],adt(dp[k[i].to][0],dp[k[i].to][1]));
				e[now][1]=mul(e[now][1],dp[k[i].to][0]);
			}
		}
	}
	void get(int u,int v)
	{
		int last=v,g=v;
		s[v][0][0]=1;s[v][1][1]=1;
		s[v][0][1]=s[v][1][0]=0;
		v=f[v][0];
		while(v!=f[u][0])
		{
			s[v][0][0]=adt(s[last][0][0],s[last][1][0]);
			s[v][0][1]=adt(s[last][0][1],s[last][1][1]);
			s[v][1][0]=s[last][0][0];
			s[v][1][1]=s[last][0][1];
			for(int i=head[v];i;i=k[i].next)
			{
				if(v==u)break;
				if(k[i].to==last||k[i].to==f[v][0]||awa[k[i].to])continue;
				s[v][1][0]=mul(s[v][1][0],dp[k[i].to][0]);
				s[v][1][1]=mul(s[v][1][1],dp[k[i].to][0]);
				s[v][0][0]=mul(s[v][0][0],adt(dp[k[i].to][0],dp[k[i].to][1]));
				s[v][0][1]=mul(s[v][0][1],adt(dp[k[i].to][0],dp[k[i].to][1]));
			}
			last=v;v=f[v][0];
		}
		s[g][0][0]=s[last][0][0];
		s[g][1][0]=s[last][1][0];
		s[g][0][1]=s[last][0][1];
		s[g][1][1]=s[last][1][1];
	}
	void solve(int now)
	{
		dp[now][0]=dp[now][1]=1;
		if(vis[now][0])dp[now][0]=0;
		if(vis[now][1])dp[now][1]=0;
		for(int i=head[now];i;i=k[i].next)
		{
			if(k[i].to==f[now][0])continue;
			solve(k[i].to);
			dp[now][0]=mul(dp[now][0],adt(mul(s[k[i].to][0][0],dp[k[i].to][0]),mul(s[k[i].to][0][1],dp[k[i].to][1])));
			dp[now][1]=mul(dp[now][1],adt(mul(s[k[i].to][1][0],dp[k[i].to][0]),mul(s[k[i].to][1][1],dp[k[i].to][1])));
		}
		dp[now][0]=mul(dp[now][0],e[now][0]);
		dp[now][1]=mul(dp[now][1],e[now][1]);
	}
	int kth(int a,int b)
	{
		for(int i=19;i>=0;i--)
		{
			if((b>>i)&1)
			a=f[a][i];
		}
		return a;
	}
	int lca(int a,int b)
	{
		if(dep[a]<dep[b])swap(a,b);
		for(int i=19;i>=0;i--)if(dep[f[a][i]]>=dep[b])a=f[a][i];
		if(a==b)return a;
		for(int i=19;i>=0;i--)if(f[a][i]!=f[b][i])a=f[a][i],b=f[b][i];
		return f[a][0];
	}
}T1,T2;
bool cmp(int a,int b)
{
	return T1.dfn[a]<T1.dfn[b];
}
signed main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)g[i]=i;
	for(int i=1;i<=m;i++)
	{
		u[i]=read();v[i]=read();
		if(find(u[i])==find(v[i]))
		{
			kl[i]=1;
			p[++tot][0]=u[i];
			p[tot][1]=v[i];
			q[++cnt]=u[i];
			q[++cnt]=v[i];
		}
		else g[g[u[i]]]=g[v[i]];
	}
	for(int i=1;i<=m;i++)
	{
		if(kl[i])continue;
		T1.add(u[i],v[i]);
		T1.add(v[i],u[i]);
	}
	T1.dfs(1,0);
	stack<int> t;t.push(1);
	sort(q+1,q+1+cnt,cmp);
	cnt=unique(q+1,q+1+cnt)-q-1;
	for(int i=1;i<=cnt;i++)
	{
		if(q[i]==1)continue;
		int last=0,x=q[i];
		while(T1.lca(t.top(),x)!=t.top())
		{
			if(last)
			{
				T2.add(t.top(),last);
				awa[T1.kth(last,T1.dep[last]-T1.dep[t.top()]-1)]=1;
			}
			last=t.top();
			t.pop();
		}
		if(last)
		{
			int y=T1.lca(last,x);
			if(y!=t.top())t.push(y);
			T2.add(t.top(),last);
			awa[T1.kth(last,T1.dep[last]-T1.dep[t.top()]-1)]=1;
		}
		t.push(x);
	}
	while(t.size()>1)
	{
		int x=t.top();t.pop();
		T2.add(t.top(),x);
		awa[T1.kth(x,T1.dep[x]-T1.dep[t.top()]-1)]=1;
	}
	T1.dne(1);
	for(int i=1;i<=T2.tot;i++)T1.get(T2.k[i].from,T2.k[i].to);
	int lim=(1<<tot)-1;
	for(int i=0;i<=lim;i++)
	{
		for(int j=1;j<=tot;j++)
		{
			if((i>>(j-1))&1)vis[p[j][0]][0]=1,vis[p[j][1]][1]=1;
			else vis[p[j][0]][1]=1;
		}
		T2.solve(1);
		ans=adt(ans,adt(T2.dp[1][0],T2.dp[1][1]));
		for(int j=1;j<=tot;j++)
		{
			if((i>>(j-1))&1)vis[p[j][0]][0]=0,vis[p[j][1]][1]=0;
			else vis[p[j][0]][1]=0;
		}
	}
	cout<<ans<<"\n";
	return 0;
}

```

---

## 作者：tzc_wk (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/P4426)

神仙虚树题。

首先考虑最 trival 的情况：$m=n-1$，也就是一棵树的情况。这个我相信刚学树形 $dp$ 的都能够秒掉罢（确信）。直接设 $dp_{i,0/1}$ 在表示 $i$ 的子树内选择，$i$ 选/不选的方案数。转移就 $dp_{u,0}=\prod\limits_{v\in son_u}(dp_{v,0}+dp_{v,1}),dp_{u,1}=\prod\limits_{v\in son_u}dp_{v,0}$ 即可。

接下来考虑有非树边的情况，首先我们一遍 DFS 找出所有非树边组成的集合 $E_t$（显然 $|E_t|=m-n+1$）注意到 $m\le n+10$，故 $|E_t|\le 11$，我们考虑暴力枚举每条非树边的选择情况——共有 $(0,0),(0,1),(1,0)$ 三种情况，但实际上我们发现如果左端点不选，那右端点就没有限制了，因此我们只需枚举左端点的情况，我们维护一个 $ban_{u,x}$ 表示点 $u$ 选/不选是否不可行，那么状态转移方程需改为 $dp_{u,0}=\prod\limits_{v\in son_u}(dp_{v,0}+dp_{v,1})\times(1-ban_{u,0}),dp_{u,1}=\prod\limits_{v\in son_u}dp_{v,0}\times(1-ban_{u,1})$。这样复杂度是 $n2^{|E_t|}$ 的，大约可以拿到 $75$ 分的好成绩。

考虑进一步优化，注意到虽然状态数很多，但满足 $ban_{u,0}=1\lor ban_{u,1}=1$ 的点并不多，最多只有 $22$ 个，因此我们考虑对这些关键点建立**虚树**，但是由于在建立虚树的过程中我们将有的链缩成了边，因此我们就不能再像之前那样转移了，我们考虑对每条虚树上的边 $e=(u,v)$（$u$ 是 $v$ 的父亲）预处理一个系数 $k_{e,0/1,0/1}$，表示 $dp_{u,0}=\prod\limits_{e\in E_u}(dp_{v,0}\times k_{e,0,0}+dp_{v,1}\times k_{e,0,1}),dp_{u,1}=\prod\limits_{e\in E_u}(dp_{v,0}\times k_{e,1,0}+dp_{v,1}\times k_{e,1,1})$（有点类似于矩阵乘法），其中 $E_u$ 为以 $u$ 为上端节点的虚链的集合，显然如果我们求出了 $k_{e,0/1,0/1}$ 就可以直接在虚树上 $dp$ 了，时间复杂度也就降到了 $|E_t|\times 2^{|E_t|}$。

于是现在我们的任务就是求出 $k_{e,0/1,0/1}$，首先对于每个虚树边 $(u,v)$ 的对应链上的点 $w$，$w$ 子树内距离 $w$ 最近的在虚树上的点是唯一的，这个点就是 $v$，因此我们再建一个数组 $dk_{w,0/1,0/1}$ 表示 $dp_{w,0}=dp_{v,0}\times dk_{w,0,0}+dp_{v,1}\times dk_{w,0,1},dp_{w,1}=dp_{v,0}\times dk_{w,1,0}+dp_{v,1}\times dk_{w,1,1}$，显然对于关键点 $u$，$dp_{u,0,0}=dp_{u,1,1}=1,dp_{u,1,0}=dp_{u,0,1}=0$。考虑怎样通过 $w$ 子树的 $dk$ 求出 $dk_w$，显然对于 $w$ 的所有儿子，有且只有一个在 $u\to v$ 这条虚链上，我们假设这个点为 $x$，那么对于其他的 $w$ 的儿子 $y\ne x$，$dp_{y,0},dp_{y,1}$ 显然是定值，根据前面的状态转移方程是直接乘上即可，即 $dk_{w,0,0/1}$ 乘上 $dp_{y,0}+dp_{y,1}$，$dk_{w,1,0/1}$ 乘上 $dp_{y,0}$。而对于 $w$ 在关键链上的儿子，根据 $dp_{x,0}=dp_{v,0}\times dk_{x,0,0}+dp_{v,1}\times dk_{x,0,1},dp_{x,1}=dp_{v,0}\times dk_{x,1,0}+dp_{v,1}\times dk_{x,1,1}$，可以得出 $x$ 对 $dp_{w,0}$ 的贡献是 $dp_{x,0}+dp_{x,1}=dp_{v,0}\times(dk_{x,0,0}+dk_{x,1,0})+dp_{v,1}\times(dk_{x,0,1}+dk_{x,1,1})$，对 $dp_{w,1}$ 的贡献是 $dp_{v,0}\times dk_{x,0,0}+dp_{v,1}\times dk_{x,0,1}$，故我们需令 $dk_{w,0,0}\leftarrow dk_{w,0,0}\times(dk_{x,0,0}+dk_{x,1,0}),dk_{w,1,0}\leftarrow dk_{w,1,0}\times dk_{x,0,0}$，这样即可求出 $k_{e,0/1,0/1}$，具体见代码罢。

```cpp
const int MAXN=1e5+10;
const int MAXK=11;
const int MOD=998244353;
int n,m,hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],ec=1,ans=0;
bool ist[MAXN+5],onv[MAXN+5];
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int dfn[MAXN+5],tim=0;pii et[MAXK+5];int ecnt=0;
void dfs1(int x,int f){
	dfn[x]=++tim;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;
		if(!dfn[y]) dfs1(y,x);
		else{
			onv[x]=onv[y]=1;ist[e>>1]=1;
			if(dfn[x]<dfn[y]) et[++ecnt]=mp(x,y);
		}
	}
}
int cnt[MAXN+5];
void dfs2(int x,int f){
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f||ist[e>>1]) continue;
		dfs2(y,x);cnt[x]+=cnt[y];
	} onv[x]|=(cnt[x]>=2);cnt[x]=!!(cnt[x]+onv[x]);
}
pii k[MAXN+5][2];int dp0[MAXN+5][2];
vector<pair<int,pair<pii,pii> > > g[MAXN+5];
pii operator +(pii lhs,pii rhs){return mp((lhs.fi+rhs.fi)%MOD,(lhs.se+rhs.se)%MOD);}
pii operator *(pii lhs,int rhs){return mp(1ll*lhs.fi*rhs%MOD,1ll*lhs.se*rhs%MOD);}
int dfs3(int x,int f){
	dp0[x][0]=dp0[x][1]=1;int z=0;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f||ist[e>>1]) continue;
		int dw=dfs3(y,x);
		if(!dw){
			dp0[x][0]=1ll*dp0[x][0]*(dp0[y][0]+dp0[y][1])%MOD;
			dp0[x][1]=1ll*dp0[x][1]*dp0[y][0]%MOD;
		} else if(onv[x]) g[x].pb(mp(dw,mp(k[y][0]+k[y][1],k[y][0])));
		else k[x][0]=k[y][0]+k[y][1],k[x][1]=k[y][0],z=dw;
	} if(onv[x]) k[x][0]=mp(1,0),k[x][1]=mp(0,1),z=x;
	else k[x][0]=k[x][0]*dp0[x][0],k[x][1]=k[x][1]*dp0[x][1];
//	printf("%d %d %d %d %d\n",x,k[x][0].fi,k[x][0].se,k[x][1].fi,k[x][1].se);
//	printf("%d %d\n",dp0[x][0],dp0[x][1]);
	return z;
}
bool ban[MAXN+5][2];int dp[MAXN+5][2];
void dfs4(int x){
	dp[x][0]=(!ban[x][0])*dp0[x][0];
	dp[x][1]=(!ban[x][1])*dp0[x][1];
	for(int i=0;i<g[x].size();i++){
		int y=g[x][i].fi;dfs4(y);
		pii p0=g[x][i].se.fi,p1=g[x][i].se.se;
		dp[x][0]=1ll*dp[x][0]*((1ll*dp[y][0]*p0.fi+1ll*dp[y][1]*p0.se)%MOD)%MOD;
		dp[x][1]=1ll*dp[x][1]*((1ll*dp[y][0]*p1.fi+1ll*dp[y][1]*p1.se)%MOD)%MOD;
	} //printf("%d %d %d\n",x,dp[x][0],dp[x][1]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),adde(u,v),adde(v,u);
	dfs1(1,0);dfs2(1,0);onv[1]=1;dfs3(1,0);
//	for(int i=1;i<=n;i++) printf("%d%c",onv[i]," \n"[i==n]);
//	for(int i=1;i<=ecnt;i++) printf("%d %d\n",et[i].fi,et[i].se);
	for(int i=0;i<(1<<ecnt);i++){
		for(int j=1;j<=ecnt;j++){
			if(i>>(j-1)&1) ban[et[j].fi][0]=1,ban[et[j].se][1]=1;
			else ban[et[j].fi][1]=1;
		} dfs4(1);ans=(ans+dp[1][0])%MOD;ans=(ans+dp[1][1])%MOD;
		for(int j=1;j<=ecnt;j++){
			if(i>>(j-1)&1) ban[et[j].fi][0]=0,ban[et[j].se][1]=0;
			else ban[et[j].fi][1]=0;
		}
	} printf("%d\n",ans);
	return 0;
}
```



---

