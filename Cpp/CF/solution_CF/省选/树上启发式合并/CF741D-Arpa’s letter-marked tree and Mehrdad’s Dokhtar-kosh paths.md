# Arpa’s letter-marked tree and Mehrdad’s Dokhtar-kosh paths

## 题目描述

Just in case somebody missed it: we have wonderful girls in Arpa’s land.

Arpa has a rooted tree (connected acyclic graph) consisting of $ n $ vertices. The vertices are numbered $ 1 $ through $ n $ , the vertex $ 1 $ is the root. There is a letter written on each edge of this tree. Mehrdad is a fan of Dokhtar-kosh things. He call a string Dokhtar-kosh, if we can shuffle the characters in string such that it becomes palindrome.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF741D/ae6eaea25c446dd1a9c02c7621129601f3a81ec1.png)He asks Arpa, for each vertex $ v $ , what is the length of the longest simple path in subtree of $ v $ that form a Dokhtar-kosh string.

## 样例 #1

### 输入

```
4
1 s
2 a
3 s
```

### 输出

```
3 1 1 0 ```

## 样例 #2

### 输入

```
5
1 a
2 h
1 a
4 h
```

### 输出

```
4 1 0 1 0 ```

# 题解

## 作者：Soulist (赞：45)

首先一个串能重排形成是回文串当且仅当其字符数量均为偶数或者恰好有一个奇数

实际上对于任意的一条路径我们只关注其任意字符的奇偶性

因为字符只有$22$种，所以我们可以考虑将其压缩称为一个状态$0$表示此字符为偶数而$1$表示为奇

于是对于任意一条路径$(u,v)$我们考虑其状态就可以通过差分来得到：

不妨记$dis_x$表示$x$到$1$的路径上的字符所形成的状态

于是有：$dis_u \oplus dis_v\oplus dis_{lca} \oplus dis_{lca}$就是这条路径的状态

注意到异或的性质，所以$dis_u\oplus dis_v$即这个状态

于是有一条路径合法当且仅当$dis_u\oplus dis_v$为如下$23$种状态：

$$000...00$$

$$100...00$$

$$......$$

$$000...10$$

$$000...01$$

接下来我们考虑暴力求解

$1.$我们暴力枚举点对并以$O(23)$的复杂度检查

$2.$我们类似于点分治，对$2^{22}$种不同的状态开个桶

注意到一个点对$u,v$对答案造成的贡献为$dep_u+dep_v-2*dep_{lca}$

于是我们考虑从一个点$x$开始搜索

遍历其所有子树，然后对于一个状态$dis_u$与其$\oplus$得到结果合法的状态是固定的$23$种，于是我们只要检查桶内有没有合法的即可

然后对每个桶都只要维护最大的$dep$即可

复杂度$O(23*n^2)$

$3.$刚刚的暴力$2$我们采用$dsu$实现就是$O(23*n\log n)$了$qwq$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int N = 2000000 + 5 ; 
int n, cnt, idnex, L[N], R[N], head[N], dep[N], sz[N], son[N] ;
int book[N * 10], vis[N], Ans[N], dis[N], Id[N] ; 
struct E {
	int to, next, w ; 
} e[N] ;
void add( int x, int y, int w ) {
	e[++ cnt] = (E){ y, head[x], w }, head[x] = cnt ; 
}
void dfs( int x, int fa ) {
	sz[x] = 1, L[x] = ++ idnex, dep[x] = dep[fa] + 1, Id[idnex] = x ; 
	Next( i, x ) {
		int v = e[i].to ; dis[v] = dis[x] ^ e[i].w, dfs( v, x ), sz[x] += sz[v] ;
		if( sz[son[x]] < sz[v] ) son[x] = v ; 
	} R[x] = idnex ; 
}
void dfs2( int x, int keep ) {
	Next( i, x ) {
		int v = e[i].to ; if( v == son[x] ) continue ; 
		dfs2( v, 0 ), Ans[x] = max( Ans[x], Ans[v] ) ; 
	}
	if( son[x] ) dfs2( son[x], 1 ), Ans[x] = max( Ans[x], Ans[son[x]] ) ; 
	if( book[dis[x]] ) Ans[x] = max( Ans[x], book[dis[x]] - dep[x] ) ; 
	rep( i, 0, 21 ) if( book[dis[x] ^ ( 1 << i )] ) Ans[x] = max( Ans[x], book[dis[x] ^ ( 1 << i )] - dep[x] ) ; 
	book[dis[x]] = max( dep[x] , book[dis[x]] ) ;
	Next( i, x ) {
		int v = e[i].to ; if( v == son[x] ) continue ; 
		rep( j, L[v], R[v] ) {
			int u = Id[j] ; 
			if( book[dis[u]] ) Ans[x] = max( Ans[x], book[dis[u]] + dep[u] - 2 * dep[x] ) ; 
			rep( k, 0, 21 ) if( book[dis[u] ^ ( 1 << k )] ) Ans[x] = max( Ans[x], book[dis[u] ^ ( 1 << k )] + dep[u] - 2 * dep[x] ) ; 
		}
		rep( j, L[v], R[v] ) book[dis[Id[j]]] = max( book[dis[Id[j]]], dep[Id[j]] ) ; 
	}
	if( !keep ) rep( i, L[x], R[x] ) book[dis[Id[i]]] = 0 ; 
}
signed main()
{
	n = read() ; int x; char ch ; 
	rep( i, 2, n ) {
		scanf("%d", &x), cin >> ch, add( x, i, 1ll << ( ch - 'a' ) ) ; 
	}
	dfs( 1, 1 ), dfs2( 1, 1 ) ;
	rep( i, 1, n ) printf("%d ", Ans[i] ) ;
	return 0;
}
```

---

## 作者：Mihari (赞：33)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF741D)

# 题解

由树启发算法发明者出的题。

涉及回文，那么我们来想一下回文的特性：

>最多只有一种字符出现奇数次的一堆字符才会被重新排序成为一个回文串。

所以，这道题我们只需要知道，在某一条链上，有多少字符出现奇数次，而偶数次的字符我们可以忽略。

这有点想什么？是不是二进制中的**异或运算**？

那么，我们只需要将每种字符表示为二进制位上的一位，每条边的权值我们可以定义为 $2^{ch-'a'}$，而两条路的合并就可以直接用 $\oplus$ 来合并。

接下来怎么处理？

首先想清楚一个东西：对于两条路之间的异或和，我们可以这样计算
$$
\begin{aligned}
\text{dis}(u,v)&=\text{dis}(u,1)\oplus \text{dis}(\text{lca}_{u,v},1)\oplus \text{dis}(v,1)\oplus \text{dis}(\text{lca}_{u,v},1) \\
&=\text{dis}(u,1)\oplus \text{dis}(v,1)
\end{aligned}
$$
那么，我们只需要处理出每个点到 $1$ 的异或路径和，我们就能 $\mathcal O(1)$ 地处理出两点的路径异或和。

我们把这个数组记为 $\text{Xor}_u$。

接下来，我们又怎么处理？

假设现在我们处理以 $u$ 为根的子树，如果一条链从 $u$ 开始，一直连到他的某一个子树中的点，**贪心地，这个点的深度一定是所有满足条件的点中最深的**。

但是这又引出一个问题，我们怎么找这些符合条件的点，或者说这些符合条件的点需要满足什么要求呢？

由于我们需要求的路径的路径异或和为 $0$ 或者 $2^i$，那么这些符合条件的点一定满足下面等式
$$
\text{Xor}_u\oplus \text{Xor}_v=0
$$
或者
$$
\text{Xor}_u\oplus \text{Xor}_v=2^i
$$
由异或和的特性，我们可以解得 $\text{Xor}_v$ 的值
$$
\text{Xor}_v=\text{Xor}_u\space 或\space \text{Xor}_u\oplus2^i
$$
由于我们的贪心性质，我们维护一个 $f_i$ 数组，表示满足 $\text{Xor}=i$ 的点的最大深度。

这个 $f_i$ 怎么维护？

可以看一下这段，应该比较好理解

```cpp
void count(const int u,const int d,const int delta){
    if(delta==1)f[Xor[u]]=Max(f[Xor[u]],d);
    else f[Xor[u]]=0;
    erep(t,u)count(v,d+1,delta);
}
```

剩下的问题，我们考虑怎么更新一个点 $u$ 的答案 $ans_u$。

他有多种途径更新：

1. 从儿子的子树中来，这种情况 $ans_u=\min\{ans_u,ans_v\mid v\in son_u\}$；
2. 考虑和子树中的某个点连接起来，那么 $ans_u=\min\{ans_u,f_{\text{Xor}_u}-d_u,f_{\text{Xor}_u\oplus 2^i}-d_u\}$；
3. 考虑跨子树组合成一条链，这个情况我们先不考虑，后面再说；

在具体实现中，我们首先遍历每个子节点（非重儿子）并处理，之后清空子节点得到的 $f_i$ （就用刚刚的 `count()` 函数）。

然后处理重儿子，**不清空 $f_i$**，然后重新遍历轻儿子，考虑将两个儿子的 $f_i$ 进行合并，在合并之前，**我们可以先遍历一遍轻儿子子树并处理上面第三种情况**，即跨子树组合的情况，具体实现可以看一下下面的代码：

```cpp
int dfs3(const int u,const int d,const int rtd){
    int ret=0;
    if(f[Xor[u]])ret=Max(ret,f[Xor[u]]+d-(rtd<<1));
    rep(i,0,21)if(f[Xor[u]^(1<<i)])
        ret=Max(ret,f[Xor[u]^(1<<i)]+d-(rtd<<1));
    erep(t,u){
        ret=Max(ret,dfs3(v,d+1,rtd));
    }return ret;
}
```

其中 $rtd$ 表示 $u$ 的深度。

在计算完答案之后，我们再将轻儿子子树加入到 $f_i$ 即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,__l,__r) for(signed i=(__l),i##_end_=(__r);i<=i##_end_;++i)
#define fep(i,__l,__r) for(signed i=(__l),i##_end_=(__r);i>=i##_end_;--i)
#define erep(i,u) for(signed i=tail[u],v=e[i].to;i;i=e[i].nxt,v=e[i].to)
#define writc(a,b) fwrit(a),putchar(b)
#define mp(a,b) make_pair(a,b)
#define ft first
#define sd second
#define LL long long
#define ull unsigned long long
#define uint unsigned int
#define pii pair< int,int >
#define Endl putchar('\n')
// #define int long long
// #define int unsigned
// #define int unsigned long long

#ifdef _GLIBCXX_CSTDIO
#define cg (c=getchar())
template<class T>inline void qread(T& x){
    char c;bool f=0;
    while(cg<'0'||'9'<c)f|=(c=='-');
    for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
    if(f)x=-x;
}
template<class T>inline T qread(const T sample){
    T x=0;char c;bool f=0;
    while(cg<'0'||'9'<c)f|=(c=='-');
    for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
    return f?-x:x;
}
#undef cg
template<class T>void fwrit(const T x){//just short,int and long long
    if(x<0)return (void)(putchar('-'),fwrit(-x));
    if(x>9)fwrit(x/10);
    putchar(x%10^48);
}
#endif
// template<class T,class... Args>inline void qread(T& x,Args&... args){qread(x),qread(args...);}
template<class T>inline T Max(const T x,const T y){return x>y?x:y;}
template<class T>inline T Min(const T x,const T y){return x<y?x:y;}
template<class T>inline T fab(const T x){return x>0?x:-x;}
inline int gcd(const int a,const int b){return b?gcd(b,a%b):a;}
inline void getInv(int inv[],const int lim,const int MOD){
    inv[0]=inv[1]=1;for(int i=2;i<=lim;++i)inv[i]=1ll*inv[MOD%i]*(MOD-MOD/i)%MOD;
}
inline LL mulMod(const LL a,const LL b,const LL mod){//long long multiplie_mod
    return ((a*b-(LL)((long double)a/mod*b+1e-8)*mod)%mod+mod)%mod;
}

const int MAXN=5e5;
const int MAXSIZE=1<<22;
struct edge{int to,nxt,w;}e[MAXN+5];
int tail[MAXN+5],ecnt;
inline void add_edge(const int u,const int v,const int w){
    e[++ecnt]=edge{v,tail[u],w};tail[u]=ecnt;
}

int n,ans[MAXN+5];

inline void Init(){
    n=qread(1);
    char ch[5];int fa;
    rep(i,2,n){
        scanf("%d %s",&fa,ch);
        add_edge(fa,i,1<<(ch[0]-'a'));
    }
}

int wson[MAXN+5],sz[MAXN+5],Xor[MAXN+5];

int f[MAXSIZE+5];//记录从根到点异或值为 i 的点的最大深度

void dfs1(const int u){
    sz[u]=1,wson[u]=0;
    erep(t,u){
        Xor[v]=Xor[u]^e[t].w;
        dfs1(v);
        sz[u]+=sz[v];
        if(sz[v]>sz[wson[u]])wson[u]=v;
    }
}

void count(const int u,const int d,const int delta){
    if(delta==1)f[Xor[u]]=Max(f[Xor[u]],d);
    else f[Xor[u]]=0;
    erep(t,u)count(v,d+1,delta);
}

int dfs3(const int,const int,const int);

void dfs2(const int u,const int d){
    erep(t,u)if(v^wson[u]){
        dfs2(v,d+1);
        ans[u]=Max(ans[u],ans[v]);
        /*后面在把 u 加入重儿子中的时候, 也会考虑到将这个点加入轻儿子的链, 所以此处没有必要考虑
        if(cnt[Xor[u]])ans[u]=Max(ans[u],cnt[Xor[u]]-d);
        rep(i,0,21)if(cnt[Xor[u]^(1<<i)])
            ans[u]=Max(ans[u],cnt[Xor[u]^(1<<i)]-d);
        */
        count(v,d+1,-1);
    }
    if(wson[u])dfs2(wson[u],d+1),ans[u]=Max(ans[u],ans[wson[u]]);
    if(f[Xor[u]])ans[u]=Max(ans[u],f[Xor[u]]-d);
    rep(i,0,21)if(f[Xor[u]^(1<<i)])ans[u]=Max(ans[u],f[Xor[u]^(1<<i)]-d);
    f[Xor[u]]=Max(d,f[Xor[u]]);
    erep(t,u)if(v^wson[u]){
        ans[u]=Max(dfs3(v,d+1,d),ans[u]);
        count(v,d+1,1);
    }
}

int dfs3(const int u,const int d,const int rtd){
    int ret=0;
    if(f[Xor[u]])ret=Max(ret,f[Xor[u]]+d-(rtd<<1));
    rep(i,0,21)if(f[Xor[u]^(1<<i)])
        ret=Max(ret,f[Xor[u]^(1<<i)]+d-(rtd<<1));
    erep(t,u){
        ret=Max(ret,dfs3(v,d+1,rtd));
    }return ret;
}

signed main(){
    // ios::sync_with_stdio(false);
    Init();
    dfs1(1);
    dfs2(1,0);
    rep(i,1,n)printf("%d ",ans[i]);
	return 0;
}
```





---

## 作者：Farkas_W (赞：18)

$$\text{CF741D Arpa’s letter-marked tree and Mehrdad’s Dokhtar-kosh paths}$$

$\quad$题目链接：[CF741D Arpa’s letter-marked tree and Mehrdad’s Dokhtar-kosh paths](https://www.luogu.com.cn/problem/CF741D)(洛谷的链接)

$\quad$这其实算一道 Dsu 的压轴题，据说是树上启发式合并算法的创始者出的题。

$\quad$这题确实是有些难度的，总之我一开始连题解都没有看懂。

$\quad$首先考虑回文的问题，其他题解其实讲的很清楚了，只要22个字母中最多有一个字母数量为奇数即可，也可都为偶数，所以一共23种情况，但考虑所有情况(只分奇偶)有 $2^{22}$中情况，可以用一个二进制数表示，**用 $cnt_i$ 表示二进制数为 $i$ 的结点的最大深度，二进制数指的是从这个结点到根节点的最短路径的序列，$num_x$ 表示结点 $x$ 到根节点的最短路径的序列**，请仔细理解这句话，否则之后的代码可能会看不懂。

$\quad$然后我们对于两个修改函数都讲一遍。

$\quad$第一个修改函数，就是判断是否有有符合条件的，如对于节点 $x$ 来说，和TA到根节点的序列为 $num_x$，$cnt_{num_x}$ 表示之前出现的另一条大小为 $num_x$ 序列，这样这两条路径合并后字母数就都是偶数，之后的循环枚举的是有一个字母不同的情况，这两种情况都是符合条件的。

```cpp
il void add1(int x)
{
  ans[now]=max(ans[now],dep[x]+cnt[num[x]]);
  for(re i=0;i<=21;i++)ans[now]=max(ans[now],dep[x]+cnt[(1<<i)^num[x]]);
}
```
$\quad$对于第二个修改函数，就是把这个结点 $x$ 的信息载入 $cnt$ 数组，并且为了最后的序列最长，要尽可能选深度大的，显然深度大的答案更优。

```cpp
il void add2(int x)
{cnt[num[x]]=max(cnt[num[x]],dep[x]);}
```
$\quad$注意要先做修改操作 $1$，再做修改操作 $2$，也就是说先统计这个点的答案(或一棵子树)，再载入这个点的数据(或一棵子树)，否则答案会把自己也记进去，可以仔细思考一下这个点。

$\quad$接下来我们思考一个问题，因为我们是一棵子树一棵子树为单位修改的，如果这个最优答案在子树中会怎么样？可以发现这样的答案在子树中一定被统计过了，当这条路径的两个端点的LCA被询问时就以及被记录了，所以还要跑一遍所有子树，用子树的答案来更新当前结点。

$\quad$另外我们还要注意节点 $i$ 的答案的计算公式为

$$ans_i=\max (dep_x+dep_y-2\times dep_i)$$

$\quad$这其实就是 $x$，$y$ 两点之间的距离公式( $x$,$y$ 为最短路径的两个端点)，另外可以发现最优情况下结点 $i$ 为结点 $x$ 和结点 $y$ 的LCA，因为结点 $x$ 和结点 $y$ 的在以 $i$ 为根节点的子树，若不是的话，那么答案就会算多，但这显然是错误的答案，所以我们是一棵子树一棵子树为单位修改的，这也算回答了上面的问题。

$\quad$最后来看看完整代码吧！

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
#define re register int
#define il inline
#define next nee
#define inf 1e9+5
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=5e5+5;
int n,m,next[N],go[N],head[N],tot,seg[N],son[N],father[N],now;
int size[N],rev[N],ans[N],s[N],dep[N],num[N],cnt[1<<23];
il int Max(int x,int y){return x>y?x:y;}
il void Add(int x,int y,int z)
{
  next[++tot]=head[x];
  head[x]=tot;go[tot]=y;s[tot]=z;
}
il void add1(int x)//修改操作1
{
  ans[now]=max(ans[now],dep[x]+cnt[num[x]]);
  for(re i=0;i<=21;i++)ans[now]=max(ans[now],dep[x]+cnt[(1<<i)^num[x]]);
}
il void add2(int x)//修改操作2
{cnt[num[x]]=max(cnt[num[x]],dep[x]);}
il void clear(int x)//清空操作
{
  for(re i=seg[x];i<=seg[x]+size[x]-1;i++)
    cnt[num[rev[i]]]=-inf;
}
il void dfs1(int x)
{
  dep[x]=dep[father[x]]+1;size[x]=1;seg[x]=++seg[0];rev[seg[x]]=x;
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      num[y]=num[x]^(1<<s[i]);dfs1(y);
      size[x]+=size[y];
      if(size[y]>size[son[x]])son[x]=y;
    }
}
il void dfs2(int x,int flag)
{
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==son[x])continue;
      dfs2(y,0);
    }if(son[x])dfs2(son[x],1);now=x;
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==son[x])continue;
      for(re i=seg[y];i<=seg[y]+size[y]-1;i++)add1(rev[i]);
      for(re i=seg[y];i<=seg[y]+size[y]-1;i++)add2(rev[i]);
    }add1(x),add2(x);//记得要修改x结点
  ans[x]-=(dep[x]<<1);//减去本身的深度
  for(re i=head[x],y;i,y=go[i];i=next[i])ans[x]=max(ans[x],ans[y]);
  if(!flag)clear(x);
}
signed main()
{
  n=read();char ch;
  for(re i=0;i<(1<<22);i++)cnt[i]=-inf;//一定要初始化为负值
  for(re i=2,x;i<=n;i++){x=read();father[i]=x;scanf("%c",&ch);Add(x,i,ch-'a');}
  dfs1(1);dfs2(1,1);
  for(re i=1;i<=n;i++)print(Max(ans[i],0)),putchar(' ');//可能会输出负数
  return 0;
}
```

---

## 作者：tzc_wk (赞：14)

推荐一下自己的[博客](https://www.cnblogs.com/ET2006/)，喜欢就随手点个关注哦。

难度 *2900 的 hot tea，并且竟然自己想出来了，~~更新了自己独立想出来的题目的难度上界~~（bushi）。

我们预处理出 $msk_x$，其中 $msk_x$ 是一个 22 位二进制数，第 $i$ 位是 $1$ 表示字母表中第 $i$ 个字符在 $x$ 到根节点的路径上出现了奇数次，否则表示出现了偶数次。

显然 $x$ 到 $y$ 的路径上的字符可以重排为一个回文串当且仅当 $msk_x\oplus msk_y$ 在二进制下中至多有 $1$ 位为 $1$，即 $msk_x\oplus msk_y=0,1,2^1,2^2,\dots,2^{21}$

考虑使用树上启发式合并，假设我们 dfs 到点 $u$。显然 $u$ 子树内的路径由 LCA 为点 $u$ 的路径与 LCA 不为 $u$ 的路径两部分组成，后者的最大值为 $\max\limits_{v\in son_u}ans_v$，关键是如何计算前者的答案，即对于满足 $msk_x\oplus msk_y=0,1,2^1,2^2,\dots,2^{21}$ 且 $x,y$ 在 $u$ 的不同子树中的 $x,y$，$dep_x+dep_y-2\times dep_u$ 的最大值。由于 $2\times dep_u$ 为定值，故只需求出 $dep_x+dep_y$ 的最大值。

考虑用类似于点分治的处理方式，实时维护一个 $mx_x$ 表示 $msk_u=x$ 的 $u$ 中 $dep_u$ 的最大值。依次 dfs $u$ 的每个子树，先考虑这个子树中每个点的贡献，然后更新 $mx$ 数组。计算贡献的具体方式是，考虑该子树中每一个节点 $x$，枚举 $msk_x\oplus msk_y$ 的值 $v$（显然只有 23 种可能），如果 $mx_{msk_x\oplus v}\neq 0$，就用 $mx_{msk_x\oplus v}+dep_x-2\times dep_u$ 更新 $ans_u$。这样就能保证我们算出的 $x,y$ 是属于 $u$ 的不同子树了。

还有一点，有人可能会问：这个 $mx_x$ 不是求某个东西的最大值，不满足可撤销性吗。注意，在树上启发式合并中，我们的删除操作是**全局删除**，需消除子树内所有点的贡献，所以直接把对应的 $msk$ 值赋为 $0$ 就行了，不需要画蛇添足地维护个 ```std::multiset<int>``` 之类的。

算下复杂度，dsu on tree 复杂度 1log，枚举 $msk_x\oplus msk_y$ 还有个 23 的常数。总复杂度 $23n\log n$。不知道有没有更优秀的做法。我一开始还担心能不能跑过去，不过 CF 机子可谓是神一般得快，再加上 3s 时限，跑过去没有大问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=5e5;
const int MAXV=1<<22;
int n,hd[MAXN+5],to[MAXN+5],id[MAXN+5],nxt[MAXN+5],ec=0;
void adde(int u,int v,int w){to[++ec]=v;id[ec]=w;nxt[ec]=hd[u];hd[u]=ec;}
int msk[MAXN+5],dep[MAXN+5],siz[MAXN+5],wson[MAXN+5];
int mx[MAXV+5],ans[MAXN+5];
void dfs0(int x,int f){
	siz[x]=1;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e],z=id[e];if(y==f) continue;
		dep[y]=dep[x]+1;msk[y]=msk[x]^(1<<z);dfs0(y,x);siz[x]+=siz[y];
		if(siz[y]>siz[wson[x]]) wson[x]=y;
	}
}
int pth[MAXN+5],pth_num=0;
void getpth(int x,int f){
	pth[++pth_num]=x;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;getpth(y,x);
	}
}
void add(int x,int f){
	chkmax(mx[msk[x]],dep[x]);
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;add(y,x);
	}
}
void del(int x,int f){//全局删除
	mx[msk[x]]=0;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;del(y,x);
	}
}
void dfs(int x,int f){
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f||y==wson[x]) continue;
		dfs(y,x);chkmax(ans[x],ans[y]);del(y,x);
	} if(wson[x]) dfs(wson[x],x),chkmax(ans[x],ans[wson[x]]);
	for(int i=0;i<22;i++) if(mx[msk[x]^(1<<i)])
		chkmax(ans[x],mx[msk[x]^(1<<i)]-dep[x]);
	if(mx[msk[x]]) chkmax(ans[x],mx[msk[x]]-dep[x]);
	chkmax(mx[msk[x]],dep[x]);
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f||y==wson[x]) continue;
		pth_num=0;getpth(y,x);
		for(int i=1;i<=pth_num;i++){
			for(int j=0;j<22;j++) if(mx[msk[pth[i]]^(1<<j)])
				chkmax(ans[x],mx[msk[pth[i]]^(1<<j)]+dep[pth[i]]-dep[x]*2);
			if(mx[msk[pth[i]]]) chkmax(ans[x],mx[msk[pth[i]]]+dep[pth[i]]-dep[x]*2);
		} add(y,x);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;i++){
		char c;int f;cin>>f>>c;
		adde(f,i,c-'a');
	} dfs0(1,0);dfs(1,0);
	for(int i=1;i<=n;i++) printf("%d%c",ans[i],(i==n)?'\n':' ');
	return 0;
}
```

---

## 作者：是个汉子 (赞：12)

### Solution

​		因为要求路径上的字符重新排序后为回文串，也就是说出现次数为奇数的字符不会超过一个。我们给每个字符一个 $2^x$ 形式的权值，那么合法路径异或和要么为 $0$ ，要么为 $2^x$ 的形式。

​		设点 $x$ 到根的异或和为 $D_x$ ，由于是边权，x和y路径上的异或和可以用 $D_x~xor~D_y$ 来表示。再用一个数组 $c$ 来存储答案。其中 $c_i$ 表示 $D_x=i$ 的 $x$ 的最大深度。

​		我们可以用 $dsu~on~tree$ 来将复杂度优化到 $O(n\log~n)$ ，因为 $dsu~on~tree$ 可以利用轻重链剖分和启发式合并来更好的维护子树信息。

#### 代码

```c++
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>

using namespace std;
const int N=500010,INF=1<<30;
int n,c[1<<22],son[N],siz[N],dep[N];
int head[N],nxt[N],D[N],ans[N];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

void dfs(int u){
    siz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        D[i]^=D[u];
        dep[i]=dep[u]+1;
        dfs(i);siz[u]+=siz[i];
        if(siz[i]>siz[son[u]]) son[u]=i;
    }
}

void init(int u){
    c[D[u]]=-INF;
    for(int i=head[u];i;i=nxt[i]) init(i);
}

int o;
void up(int u){
    ans[o]=max(ans[o],dep[u]+c[D[u]]);
    for(int i=0;i<=21;i++) ans[o]=max(ans[o],dep[u]+c[1<<i^D[u]]);
    for(int i=head[u];i;i=nxt[i]) up(i);
}

void ins(int u){
    c[D[u]]=max(c[D[u]],dep[u]);
    for(int i=head[u];i;i=nxt[i]) ins(i);
}

//dsu on tree
void work(int u){
    for(int i=head[u];i;i=nxt[i])
        if(i!=son[u]) work(i),init(i);
    if(son[u]) work(son[u]); o=u;
    for(int i=head[u];i;i=nxt[i])
        if(i!=son[u]) up(i),ins(i);
    c[D[u]]=max(c[D[u]],dep[u]);
    ans[u]=max(ans[u],dep[u]+c[D[u]]);
    for(int i=0;i<=21;i++) ans[u]=max(ans[u],dep[u]+c[1<<i^D[u]]);//枚举满足条件的y
    ans[u]-=dep[u]<<1;//x-y的距离=dep[y]+dep[x]-2*dep[x]
    for(int i=head[u];i;i=nxt[i]) ans[u]=max(ans[u],ans[i]);//在子树内比较
}

int main(){
    n=read();
    for(int i=0;i<(1<<22);i++) c[i]=-INF;
    for(int i=2,x;i<=n;i++){
        x=read();
        nxt[i]=head[x];head[x]=i;
        char c=getchar();
        while(c>'v'||c<'a') c=getchar();
        D[i]=1<<(c-'a');
    }
    dfs(1);work(1);
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}
```



---

## 作者：chenxia25 (赞：6)

orz 一个 2900 D1D，不过还是被我自己想出来了（

这种关于统计所有树上路径的，应该套路地使用淀粉质。不过我只会 dsu on tree/kk，而且 yy 出来的是 $\mathrm O(22n\log n)$ 的垃圾复杂度，没想到竟然和官方题解重合？

显然一个子树内的路径，要么穿过根，要么就一定包含在一个子子树里面。于是我们可以对每个子树先算出那些穿过根的最长的符合要求的路径，最终 dfs 与儿子合并一下即可。

很自然的想到，可以预处理出每个节点处的关于每个字符出现次数奇偶性的前缀 bitmask，然后一条路径的 bitmask 显然是 $Msk_x\oplus Msk_y$。我们要统计的就是那些 $x,y$ 属于不同子子树的满足 $|Msk_x\oplus Msk_y|\leq 1$ 的路径 $x\to y$，它的长度为 $dep_x+dep_y-2dep_{a}$，其中 $a$ 是当前根。这个 $-2dep_a$ 是定值，我们只需要最大化 $dep_x+dep_y$。

不难想到这样一个暴力：对于每个 $a$，用关于子树大小的复杂度处理：实时维护一个 $mx$ 数组，$mx_{msk}$ 表示 $Msk_x=msk$ 的最大 $dep_x$。然后依次考虑每个子树，先用这个子树中每个节点贡献最大深度和，然后松弛这个 $mx$（这样能让「属于不同子子树」获得保证）。贡献的具体方式是：枚举 $Msk_x\oplus Msk_y$（显然是 $\mathrm O(22)$ 的），然后显然可以确定出 $Msk_y$，往 $mx$ 里调用一下即可。

考虑把这个暴力用 dsu on tree 进行优化。显然是可行的，而且不是那么套路的 dsu on tree，实现方式有点小变化。值得一提的是：$mx$ 这东西虽然不可撤销，但 dsu on tree 本来就不用撤销，而只需要全局清空；于是只需要赋为 $-\infty$ 而不需要换成 `set` 等数据结构。

**_[code](https://www.luogu.com.cn/paste/lce0cxrl)_**

---

## 作者：Infiltrator (赞：5)

[$\Large\color{#FFBBFF}\textit{Tian-Xing's blog}$](https://Tian-Xing.github.io)

------------

# Description

[传送门](http://codeforces.com/problemset/problem/741/D)

------------

# Solution

将字符串的路径看做二进制数，那么一个路径上的字符能重新调整成回文串的充要条件是从根到两个点的二进制数异或和为$0$或者$2$的幂。这是因为在一个回文串里，出现次数为奇数的字符只能有一个或者没有。

那么问题现在变成$x$的子树里找最大的$dep_a + dep_b - dep_{lca(a, b)}$。我们可以考虑钦定两个点的$lca$为$x$，最后用$x$的子树的值更新它即可。

这样我们就有了$dsu\ on\ tree$的思路。那么如何保证两个点的$lca$就是$x$点呢？只需要一条链一条链的进行处理，这样任意两点的$lca$必然就是$x$。将二进制数为$s$的最深深度记录下来，枚举一下二进制数互相异或得到的值就行了。

------------

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 500000;

int head[N + 50], num, a[N + 50], n, siz[N + 50], dep[N + 50], ans[N + 50], maxson[N + 50], s[N + 50], maxv, f[N * 20], inf;

struct Node
{
	int next, to;
} edge[N + 50];

void Addedge(int u, int v)
{
	edge[++num] = (Node){head[u], v};
	head[u] = num;
	return;
}

void Dfs1(int x, int fa)
{
	siz[x] = 1; dep[x] = dep[fa] + 1;
	if (x != 1) s[x] = s[fa] ^ (1 << a[x]);
	for (int i = head[x]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		Dfs1(v, x);
		siz[x] += siz[v];
		if (siz[v] > siz[maxson[x]]) maxson[x] = v;
	}
	return;
}

void Calc(int rt, int x)
{
	int now = s[x];
	maxv = max(maxv, f[now] + dep[x] - 2 * dep[rt]);
	if ((s[x] ^ s[rt]) == 0) maxv = max(maxv, dep[x] - dep[rt]);
	for (int i = 0; i < 22; i++)
	{
		now = (1 << i) ^ s[x];
		maxv = max(maxv, f[now] + dep[x] - 2 * dep[rt]);
		if ((s[x] ^ s[rt]) == (1 << i)) maxv = max(maxv, dep[x] - dep[rt]);
	}
	for (int i = head[x]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		Calc(rt, v);
	} 
	return;
}

void Change(int x, int k)
{
	if (k) f[s[x]] = max(f[s[x]], dep[x]);
	else f[s[x]] = inf;
	for (int i = head[x]; i; i = edge[i].next) Change(edge[i].to, k);
	return;
}

void Dfs2(int x, int remain)
{
	for (int i = head[x]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (v == maxson[x]) continue;
		Dfs2(v, 0); 
	}
	if (maxson[x]) Dfs2(maxson[x], 1);
	maxv = 0; int now = s[x];
	maxv = max(maxv, f[now] - dep[x]);
	for (int i = 0; i < 22; i++)
	{
		now = (1 << i) ^ s[x];
		maxv = max(maxv, f[now] - dep[x]);
	}
	for (int i = head[x]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (v == maxson[x]) continue;
		Calc(x, v); Change(v, 1);
	}
	ans[x] = maxv;
	if (!remain) 
	{
		for(int i = head[x]; i; i = edge[i].next)
			Change(edge[i].to, 0);
		f[s[x]] = inf; 
	}
	else f[s[x]] = max(f[s[x]], dep[x]);
	return;
}

void Erase(int x)
{
	for (int i = head[x]; i; i = edge[i].next)
	{
		int v = edge[i].to; Erase(v);
		ans[x] = max(ans[x], ans[v]);
	}
	return;
}

int main()
{
	scanf("%d", &n);
	char tmp;
	for (int i = 2, fa; i <= n; i++)
	{
		scanf("%d", &fa);
		cin >> tmp;
		Addedge(fa, i); a[i] = tmp - 'a';
	}
	Dfs1(1, 0); 
	memset(f, 128, sizeof(f)); inf = f[0];
	Dfs2(1, 0);
	Erase(1);
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	return 0;
}
```

---

## 作者：hl666 (赞：5)

题目意思很清楚了吧，那么我们从**重排回文串**的性质入手。

很容易得出，只要所有字符出现的次数都为**偶数**，或者有且只有一个字符出现为**奇数**就满足要求了。

然后想到什么，**Hash**？大可不必，可以发现字符$\in [a,v]$，一共$22$种，那么我们套路的**状压**一下即可。

题目放在一棵树上，我们不禁联想树上常用的算法——**倍增，树剖，树分治，树上莫队，LCT**，但是好像都不好做。

注意到这是一个**静态子树信息维护**，所以我们可以用一个比较冷门的算法**Dsu on Tree**（中文名叫**树上启发式合并**）

它的大体思路很简单，就是对暴力DFS的过程做了优化。先类似于**轻重剖分**那样求出轻重儿子，然后每次先暴力递归轻儿子，算完贡献然后**删去**。

然后再统计重儿子的贡献，做完**不再删去**，然后最后回溯的时候把轻儿子的再加回去。

由于每跳一次重儿子，子树规模至少减少一半，所以每一个节点最多向上合并$\log n$次，所以总复杂度是$O(n\log n)$的。

再来考虑这个问题，由于**异或以及深度**的可减性所以我们可以开一个数组统计子树内每种状态的最大深度，每次根据这个数组更新信息即可。

不过要注意这样做的答案是强制过当前根节点的，不过由于这是个**最值**问题，我们可以把子树的信息向上取$\max$。

虽然会有一个$22$的常数，但是你要坚信CF神机是可以跑过去的。

总复杂度$O(22n\log n)$，常数很小。

CODE

```cpp
#include<cstdio>
#include<cctype>
#define RI register int
#define CI const int&
#define Tp template <typename T>
#define add(x,y) e[++cnt]=(edge){y,head[x]},head[x]=cnt
using namespace std;
const int N=500005,R=22,status=(1<<R)-1,INF=1e9;
struct edge
{
    int to,nxt;
}e[N]; int fa[N],n,head[N],cnt,dep[N],prefix[N],son[N],ans[N],size[N],bit[R+5],f[(1<<R)+5]; char ch;
class FileInputOutput
{
    private:
        static const int S=1<<21;
        #define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,S,stdin),A==B)?EOF:*A++)
        #define pc(ch) (Ftop<S?Fout[Ftop++]=ch:(fwrite(Fout,1,S,stdout),Fout[(Ftop=0)++]=ch))
        char Fin[S],Fout[S],*A,*B; int Ftop,pt[15];
    public:
        Tp inline void read(T& x)
        {
            x=0; char ch; while (!isdigit(ch=tc()));
            while (x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc()));
        }
        Tp inline void write(T x)
        {
        	if (!x) return (void)(pc('0'),pc(' ')); RI ptop=0;
        	while (x) pt[++ptop]=x%10,x/=10; while (ptop) pc(pt[ptop--]+48); pc(' ');
        }
        inline void get_alpha(char& ch)
        {
        	while (!isalpha(ch=tc()));
        }
        inline void Fend(void)
        {
        	fwrite(Fout,1,Ftop,stdout);
        }
        #undef tc
        #undef pc
}F;
inline void maxer(int& x,CI y)
{
    if (y>x) x=y;
}
#define to e[i].to
inline void DFS1(CI now)
{
    size[now]=1; for (RI i=head[now];i;i=e[i].nxt)
    {
        dep[to]=dep[now]+1; prefix[to]^=prefix[now]; DFS1(to);
        size[now]+=size[to]; if (size[to]>size[son[now]]) son[now]=to;
    }
}
inline void calc(CI now,CI par)
{
    RI i; for (i=0;i<=R;++i) maxer(ans[par],dep[now]+f[prefix[now]^bit[i]]);
    for (i=head[now];i;i=e[i].nxt) calc(to,par);
}
inline void Add(CI now)
{
    maxer(f[prefix[now]],dep[now]); for (RI i=head[now];i;i=e[i].nxt) Add(to);
}
inline void Del(CI now)
{
    f[prefix[now]]=-INF; for (RI i=head[now];i;i=e[i].nxt) Del(to);
}
inline void DFS2(CI now)
{
    RI i; for (i=head[now];i;i=e[i].nxt) if (to!=son[now])
    DFS2(to),Del(to); if (son[now]) DFS2(son[now]);
    maxer(f[prefix[now]],dep[now]); for (i=0;i<=R;++i)
    maxer(ans[now],dep[now]+f[prefix[now]^bit[i]]);
    for (i=head[now];i;i=e[i].nxt) if (to!=son[now]) calc(to,now),Add(to);
}
#undef to
int main()
{
    //freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
    RI i; for (F.read(n),i=2;i<=n;++i) F.read(fa[i]),F.get_alpha(ch),
    add(fa[i],i),prefix[i]=1<<ch-'a'; for (i=0;i<=status;++i)
    f[i]=-INF; for (i=0;i<R;++i) bit[i]=1<<i;
    for (DFS1(1),DFS2(1),i=1;i<=n;++i) ans[i]-=2*dep[i];
    for (i=n;i;--i) maxer(ans[fa[i]],ans[i]); for (i=1;i<=n;++i)
    F.write(ans[i]); return F.Fend(),0;
}
```



---

## 作者：fanfansann (赞：4)

 

**Problem**


给定一棵以 $1$ 为根的有根树，每条边的权值是 `['a','v']` 的一个字母。现对于每个树上结点 $x$ ，求出结点 $x$ 的子树的最长的一条 “回文” 路径的长度。“回文” 路径的含义是将路径上所有的字母取出，任意排列后可以组成一个回文串。


$1\le n\le 5\times 10^5$


**Solution**

字符串重排后是回文串，显然该字符串内最多只有一种字符出现奇数次，其余均出现偶数次。

很容易可以想到异或操作。

统计字符串是否只有一个字符出现奇数次，显然可以将字符表示为二进制数，每条边一个字符，我们就可以将边权设为 $2^{\ ch-'a'}$ ，两条路的合并操作就可以 $O(1)$  使用 $\text{XOR}$  来合并。我们可以根据一条路径上的异或和来判断是否是回文串。


显然对于树上两条路径之间的异或和有：

$\begin{aligned} \text{dis}(u,v)&=\text{dis}(u,1)\oplus \text{dis}(\text{lca}_{u,v},1)\oplus \text{dis}(v,1)\oplus \text{dis}(\text{lca}_{u,v},1) \\ &=\text{dis}(u,1)\oplus \text{dis}(v,1) \end{aligned}$

因此，我们只需处理出每个点 $u$ 到根结点 $1$ 的路径权值的异或和 $\text{XOR}_u=\text{dis}(u,1)$，就可以 $O(1)$ 计算出两点间的路径权值异或和。 

显然一条路径合法（是回文串）当且仅当 $\text{XOR}_u\oplus \text{XOR}_v$ 的二进制数中仅有一个 $1$ 或一个都没有  ，即如下 $23$ 种状态：

```cpp
000...00  
100...00  
010...00 
 ......   
000...10   
000...01 
```

即合法路径 $(u,v)$ 为 $\text{XOR}_u\oplus \text{XOR}_v = 0$ 或者 $\text{XOR}_u\oplus \text{XOR}_v= 2^i$





我们需要求的就是以 $u$ 为根子树中的两点 $x,y$，满足 $\text{XOR}_x\oplus\text{XOR}_y=0$ 或$\text{XOR}_x\oplus\text{XOR}_y=2^i$ 的点对所有 $(x,y)$ 中的最长长度。

 

  对于以 $u$ 为根的子树，树中可能存在的最长路径显然有三种：
 1. 不经过根 $u$
 即最长路径在子树中
 2. 路径的一个端点就是根 $u$
 即子树中的一点  $v$ 与 根 $u$ 构成的路径
 3. 经过根 $u$ ，两个端点在子树中
 即两个端点在子树中，路径经过了根 $u$

 设 `f[x]` 表示当前子树中结点 $v$ 到根结点 $u$ 的路径的异或和等于 $x$ 的结点 $v$ 的最大深度。
 
 对于第一种情况，显然答案就是 $\text{ans}_u = \max\{\text{ans}_u, \text{ans}_v\}$，$v$ 是 $u$ 的子树中的一个结点。
 
 对于第二种情况，显然答案就是 $\text{ans}_u = \max\{\text{ans}_u, \max\{f[\text{XOR}_u], f[\text{XOR}_u\oplus 2^i]\} - \text{depth}[u]\}$。
 
 对于第三种情况，我们无法直接计算，此时显然可以直接进行树上启发式合并统计贡献。
 
 即先计算轻儿子，回答询问之后，清空轻儿子的贡献 $f_i$，然后处理重儿子，保留重儿子的贡献 $f_i$，然后再计算一次剩余的轻儿子，保留贡献在数组 $f_i$ 中，用于与上层合并。 此时经过根节点 $u$ 的路径 $(x,u)$的长度显然为 `max{f[XOR[x]], f[XOR[x] ^ (1 << i)]} - depth[u] + depth[x] - depth[u]`，即以 $u$ 为根的出 $x$ 子树的其他子树中与 $\text{XOR}_x$ 异或和为 $0$ 或 $2^i$ 的深度最大的结点 $y$ 之间的距离。我们先更新答案 `ans` ，退出遍历以后再更新 $f_i$ 数组，因为我们并不能自己匹配自己（

注意这里给的是边权，我们维护的时候需要再设一个数组 `id` 去区分开 $(u,v)$ 和 $(u,w)$ ，比较麻烦。但它给定的边是 $p_{i+1}$ 与 $i+1$ 连权值为 `ch` 的边，并保证 $p_{i+1}$ 一定小于 $i+1$ ，并且因为是树，没有环，所以我们可以只连单向边 $(p_{i+1},i+1)$ ，将边权作为 $i+1$ 的点权，我们从根 $1$ 开始，遍历的时候，一定是从上往下遍历的，每一个点只有一个指向的点，不会重复，就不需要区分了，一个点权就可以直接维护了。

**Code**



```cpp 
#include <bits/stdc++.h> 
using namespace std; 
const int N = 6e5 + 7, M = 3e6 + 7, INF = 0x3f3f3f3f; 
int n, m, t, k;
int ans[N];
int head[N], ver[M], nex[M], edge[M], tot;
bool vis[N];
int siz[N], depth[N];
int f[1 << 22];
int XOR[N];
int hson[N];

void add(int x, int y)
{
	ver[tot] = y;
	nex[tot] = head[x];
	head[x] = tot ++ ;
}

void dfs1(int x)
{
	siz[x] = 1;
	ans[x] = -INF;
	int h_size = 0, h_son = 0;
	for (int i = head[x]; ~i; i = nex[i]) {
		int y = ver[i];
		depth[y] = depth[x] + 1;
		XOR[y] ^= XOR[x];//到 1 的路径的异或和
		dfs1(y);
		siz[x] += siz[y];
		if(siz[y] > h_size)
			h_size = siz[y], h_son = y;
	}
	if(h_son != 0)
		hson[x] = h_son;
}

void update_ans(int x, int fa)
{
	ans[fa] = max(ans[fa], f[XOR[x]] - depth[fa] + depth[x] - depth[fa]);
	for (int i = 0; i < 22; ++ i)
		ans[fa] = max(ans[fa], f[XOR[x] ^ (1 << i)] - depth[fa] + depth[x] - depth[fa]);
	for (int i = head[x]; ~i; i = nex[i]) {
		int y = ver[i];
		update_ans(y, fa);
	}
}

void modify_f(int x, int fa)
{
	f[XOR[x]] = max(f[XOR[x]], depth[x]);
	for (int i = head[x]; ~i; i = nex[i]) {
		int y = ver[i];
		modify_f(y, x);
	}
}

void solve(int x, int h_son)
{
	f[XOR[x]] = max(f[XOR[x]], depth[x]);

	//第一种情况，不经过根 x
	for (int i = head[x]; ~i; i = nex[i]) {
		int y = ver[i];
		ans[x] = max(ans[x], ans[y]);
	}
	//第二种情况，以根 x 为端点
	ans[x] = max(ans[x], f[XOR[x]] - depth[x]);
	for (int i = 0; i < 22; ++ i)
		ans[x] = max(ans[x], f[XOR[x] ^ (1 << i)] - depth[x]);
	//第三种情况，经过根 x
	for (int i = head[x]; ~i; i = nex[i]) {
		int y = ver[i];
		if(y == h_son) continue;
		update_ans(y, x);
		modify_f(y, x);
	}
}

void init(int x)
{
    f[XOR[x]] = -INF;
    for (int i = head[x]; ~i; i = nex[i]) {
        int y = ver[i];
        init(y);
    }
}

void dsu_on_tree(int x)
{
	ans[x] = 0;
	for (int i = head[x]; ~i; i = nex[i]) {
		int y = ver[i];
		if(hson[x] == y) continue;
		dsu_on_tree(y);
		init(y);
	}
	if(hson[x] != 0)
		dsu_on_tree(hson[x]);
	solve(x, hson[x]);
}

int main()
{
	memset(head, -1, sizeof head);
	for (int i = 0; i <= (1 << 22) - 1; ++ i)
		f[i] = -INF;
	scanf("%d", &n);
	for (int i = 2; i <= n ; ++ i) {
		int u;
		char ch[10];
		scanf("%d%s", &u, ch);
		add(u, i);//u -> i 一定是小的向大的连，根为1，所以是从上往下的，我们只需要连单边，即可把边权转化为点权
		XOR[i] = 1 << (ch[0] - 'a'); 
	}
	dfs1(1);
	dsu_on_tree(1);
	for (int i = 1; i <= n; ++ i)
		printf("%d%s", ans[i], i == n ? "\n" : " ");
	return 0;
}
```


---

## 作者：大菜鸡fks (赞：4)

把一条路径上字母数量的奇偶性，转化成二进制编码。

若是能构成回文串。那么x^y必定是0或者2的幂次

由于是子树询问。可以考虑树dsu。

是板子题

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int INF=1e9,N=5e5+5;
struct edge{
	int link,next,val;
}e[N]; 
int tot,n,head[N];
inline void add_edge(int u,int v,int w){
	e[++tot]=(edge){v,head[u],w}; head[u]=tot;
}
inline void init(){
	n=read();
	for (int i=2;i<=n;i++){
		int x=read(),c=getchar()-'a';
		add_edge(x,i,c);
	}
}
int D[N],dep[N],heavy[N],sz[N];
void Dfs(int u){
	sz[u]=1;
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		D[v]=D[u]^(1<<e[i].val); dep[v]=dep[u]+1; Dfs(v); sz[u]+=sz[v];
		if (!heavy[u]||sz[heavy[u]]<sz[v]){
			heavy[u]=v;
		}
	}
}
int mx,col[1<<22],ans[N],now;
inline void cal(int u){
	if (col[D[u]]) mx=max(mx,dep[u]+col[D[u]]-now);
	for (int i=0;i<22;i++) if (col[(1<<i)^D[u]]) mx=max(mx,dep[u]+col[(1<<i)^D[u]]-now);
}
inline void up(int u){
	col[D[u]]=max(dep[u],col[D[u]]);
}
void calc(int u){
	cal(u);
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		calc(v);
	}
}
void upd(int u){
	up(u);
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		upd(v);
	}
}
void clear(int u){
	col[D[u]]=0;
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		clear(v);
	}
}
void dfs(int u,bool keep){
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (v!=heavy[u]){
			dfs(v,0);
		}
	}
	if (heavy[u]) dfs(heavy[u],1);
	now=dep[u]<<1;
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		mx=max(ans[v],mx);
	}
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (v!=heavy[u]){
			calc(v);
			upd(v);
		}
	}
	cal(u); up(u); 
	ans[u]=mx;
	if (!keep){
		clear(u);
		mx=0;
	}
}
inline void solve(){
	Dfs(1);
	dfs(1,1);
	for (int i=1;i<=n;i++) write(ans[i]),putchar(' ');
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：zac2010 (赞：3)

树上启发式合并题。

首先，要找到判断一个字符集是否存在重构成回文串的方法。

> 能重组成回文串仅当只存在**至多一种**字符的出现次数为奇数。

我们令 $a_u$ 表示 $1\to u$ 路径上的字符集的二进制状态。具体的，从右往左数第 $1$ 位表示字符 $a$ 的出现次数是否为奇数；从右往左第 $2$ 位表示字符 $b$ 的出现次数是否为奇数……以此类推。

我们发现，祖先 $p$ 到 $u$ 路径上的二进制状态等价于 $a_p\bigoplus a_u$。也就是任意点对 $(u,v)$ 路径上的二进制状态等价于 $(a_u\bigoplus a_{lca})\bigoplus (a_v\bigoplus a_{lca})=a_u\bigoplus a_v$。

这时我们就有方法统计答案的最大值了。点 $u$ 的答案等价于经过 $u$ 的最长合法路径的长度，以及其子节点的答案的最大值。维护经过 $u$ 的最长合法路径只需要维护所有的 $a_i$，之后直接树上启发式合并即可。

这题的启发式合并过程中，先遍历轻儿子，最后重儿子。轻儿子的信息清空，重儿子的不清空。对于一颗子树先查询再修改。查询：由于允许至多一种字符出现次数为奇数，所以就枚举哪种字符出现次数为奇数（或者没有字符出现次数为奇数）。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 5e5 + 10, INF = 1e9;
int n, a[N], sz[N], son[N], ans[N], dep[N], cnt[1 << 22];
vector<pair<int, int> > e[N];
void dfs(int u){
	sz[u] = 1;
	for(auto &p: e[u]){
		int v = p.first, w = p.second;
		a[p.first] = a[u] ^ (1 << w);
		dep[v] = dep[u] + 1, dfs(v), sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void Add(int u){
	cnt[a[u]] = max(cnt[a[u]], dep[u]);
	for(auto &p: e[u]) Add(p.first);
}
void Del(int u){
	cnt[a[u]] = -INF;
	for(auto &p: e[u]) Del(p.first);
}
int calc(int u, int rt){
	int ret = max(0, dep[u] + cnt[a[u]]);
	FL(i, 0, 21) ret = max(ret, dep[u] + cnt[a[u] ^ (1 << i)]);
	if(u == rt) cnt[a[u]] = max(cnt[a[u]], dep[u]);
	for(auto &p: e[u]) if(p.first != son[rt]){
		ret = max(ret, calc(p.first, rt));
		if(u == rt) Add(p.first);
	}
	return ret;
}
void solve(int u, int h){
	for(auto &p: e[u])
		if(p.first != son[u]) solve(p.first, 0);
	if(son[u]) solve(son[u], 1);
	ans[u] = calc(u, u), ans[u] = max(0, ans[u] - dep[u] * 2);
	for(auto &p: e[u]) ans[u] = max(ans[u], ans[p.first]);
	if(!h) Del(u);
}
int main(){
	scanf("%d", &n);
	FL(i, 0, (1 << 22) - 1) cnt[i] = -INF;
	FL(i, 2, n){
		int p; char c;
		scanf("%d %c", &p, &c);
		e[p].push_back({i, c - 'a'});
	}
	dfs(1), solve(1, 0);
	FL(i, 1, n) printf("%d ", ans[i]);
	return 0;
}
```


---

## 作者：duyi (赞：3)

# CF741D Arpa’s letter-marked tree and Mehrdad’s Dokhtar-kosh paths

重排后回文，相当于至多只有一个字母，出现次数为奇数。

因为只和出现次数的奇偶性有关，所以可以把出现次数，简化为一个 $22$ 位二进制 $\text{mask}$。

考虑求点 $u$ 的答案（子树里的最大合法路径）。首先可以继承 $u$ 的所有儿子，然后考虑跨过 $u$ 的路径。那么一定是两个不同儿子子树里的点，到 $u$ 的路径拼起来的。

考虑两个点 $x,y$，来自不同儿子的子树。如果记 $f_i$ 表示点 $i$ 到根路径上，这些边的 $\text{mask}$。则 $x,y$ 之间的路径的 $\text{mask}$，就等于 $f_x\operatorname{xor} f_y$，因为从 LCA 到根的部分，被异或后抵消了。

依次考虑 $u$ 的每个儿子，做启发式合并。枚举较小的集合里的一个点 $y$，那么要在另一个集合里查询一个数，与 $f_y$ 的异或值，至多只有一位二进制位为 $1$。枚举具体是哪一位为 $1$。可以用 $\texttt{std::map}$ 维护集合，支持插入和查找。时间复杂度 $O(n\log^2 n \cdot c)$。

将 $\texttt{std::map}$ 替换为 $\texttt{std::unordered_map}$，时间复杂度优化为 $O(n\log n\cdot c)$，可以通过本题。

参考代码：

```cpp
//problem:CF741D
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

template<typename T>inline void ckmax(T& x,T y){x=(y>x?y:x);}
template<typename T>inline void ckmin(T& x,T y){x=(y<x?y:x);}

/* --------------- fast io --------------- */ // begin
namespace Fread{
const int SIZE=1<<20;
char buf[SIZE],*S,*T;
inline char getchar(){
	if(S==T){
		T=(S=buf)+fread(buf,1,SIZE,stdin);
		if(S==T)return EOF;
	}
	return *S++;
}
}//namespace Fread
namespace Fwrite{
const int SIZE=1<<20;
char buf[SIZE],*S=buf,*T=buf+SIZE;
inline void flush(){
	fwrite(buf,1,S-buf,stdout);
	S=buf;
}
inline void putchar(char c){
	*S++=c;
	if(S==T)flush();
}
struct _{
	~_(){flush();}
}__;
}//namespace Fwrite

#ifdef ONLINE_JUDGE
	#define getchar Fread::getchar
	#define putchar Fwrite::putchar
#endif

template<typename T>inline void read(T& x){
	x=0;int f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+(c-'0'),c=getchar();
	x*=f;
}
template<typename T>inline void write(T x,bool _enter=0,bool _space=0){
	if (!x)putchar('0');else{
		if(x<0)putchar('-'),x=-x;
		static char dig[41];
		int top=0;
		while(x)dig[++top]=(x%10)+'0',x/=10;
		while(top)putchar(dig[top--]);
	}
	if(_enter)putchar('\n');
	if(_space)putchar(' ');
}

namespace Fastio{
struct reader{
	template<typename T>reader& operator>>(T& x){::read(x);return *this;}
	reader& operator>>(char& c){
		c=getchar();
		while(c=='\n'||c==' ')c=getchar();
		return *this;
	}
	reader& operator>>(char* str){
		int len=0;
		char c=getchar();
		while(c=='\n'||c==' ')c=getchar();
		while(c!='\n'&&c!=' ')str[len++]=c,c=getchar();
		str[len]='\0';
		return *this;
	}
}cin;
const char endl='\n';
struct writer{
	template<typename T>writer& operator<<(T x){::write(x,0,0);return *this;}
	writer& operator<<(char c){putchar(c);return *this;}
	writer& operator<<(char* str){
		int cur=0;
		while(str[cur])putchar(str[cur++]);
		return *this;
	}
	writer& operator<<(const char* str){
		int cur=0;
		while(str[cur])putchar(str[cur++]);
		return *this;
	}
}cout;
}//namespace Fastio
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
/* --------------- fast io --------------- */ // end

const int MAXN = 5e5;
const int INF = 1e9;
int n, fa[MAXN + 5];
char c[MAXN + 5];

struct EDGE {int nxt, to;} edge[MAXN+ 5];
int head[MAXN + 5], tot;
inline void add_edge(int u, int v) { edge[++tot].nxt = head[u], edge[tot].to = v, head[u] = tot; }

unordered_map<int, int> mp[MAXN + 5];
int id[MAXN + 5], dep[MAXN + 5], mask[MAXN + 5], ans[MAXN + 5];
int merge(int v, int u) {
	// v join u
	if(SZ(mp[id[v]]) > SZ(mp[id[u]])) {
		swap(id[v], id[u]);
	}
	int res = -INF;
	for(unordered_map<int,int> :: iterator it = mp[id[v]].begin(); it != mp[id[v]].end(); ++it) {
		int msk = (it -> fi);
		if(mp[id[u]].count(msk)) {
			ckmax(res, (it -> se) + mp[id[u]][msk]);
		}
		for(int j = 0; j < 22; ++j) {
			if(mp[id[u]].count(msk ^ (1 << j))) {
				ckmax(res, (it -> se) + mp[id[u]][msk ^ (1 << j)]);
			}
		}
	}
	for(unordered_map<int,int> :: iterator it = mp[id[v]].begin(); it != mp[id[v]].end(); ++it) {
		ckmax(mp[id[u]][it -> fi], it -> se);
	}
	return res;
}
void dfs(int u) {
	mp[id[u]][mask[u]] = dep[u];
	ans[u] = 0;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		dep[v] = dep[u] + 1;
		mask[v] = (mask[u] ^ (1 << (c[v] - 'a')));
		dfs(v);
		ckmax(ans[u], ans[v]);
		ckmax(ans[u], merge(v, u) - dep[u] * 2);
	}
}
int main() {
	cin >> n;
	for(int i = 2; i <= n; ++i) {
		cin >> fa[i] >> c[i];
		add_edge(fa[i], i);
	}
	for(int i = 1; i <= n; ++i) {
		id[i] = i;
	}
	dfs(1);
	for(int i = 1; i <= n; ++i) {
		cout << ans[i] << " ";
	}
	cout << endl;
	return 0;
}
```











---

## 作者：未来姚班zyl (赞：1)

## 题目大意

一颗带边权有根树，边权为 `a` 到 `v` 的 $22$ 种小写字母，对于每个点求其子树内能重排边权后组成回文串的最长路径。

## 题目分析

显然限制等同于每种字母出现的次数都是偶数，或者只有一种出现了奇数次。只与奇偶性有关，可以想到异或，值域只有 $22$，可以想到状态压缩，压缩成二进制下的 $22$ 位。路径异或和可以使用[统计前缀的技巧](https://www.luogu.com.cn/problem/P2420)。

而统计子树内容，可以想到 dsu。

记录每个权值下能达到的最大深度。注意，对于当前节点，如果最长路在同一子树内，可能会出现计算问题。方法是每个点只记录经过自己的路径，而不经过自己的已经在子树内计算好了，取个 max 就行。所以类似点分治，先查询，再插入。

这题或许还能用点分治做，to be updated...

2023/9/1 update：经过思考，发现本题是无法用点分治做的，瓶颈在于点分治也无法做到控制删除量，因为从当前中心往子树内跳时，如果其它子树是跳入的子树的点在原树中的子树（有点绕），则其它子树的信息都要删除，而找不到一个合理的选择中心的方案能保证“其它子树”的大小控制在满意的范围内。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned int 
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =5e5+5,M=5e6+5,inf=2147000000;
const double eps=1e-6;
const ll mod=1e8+7,llf=1e18;
using namespace std;
int n,h[N],to[N<<1],nxt[N<<1],w[N<<1],cnt,siz[N],son[N];
inline void add(int a,int b,int c){	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,w[cnt]=c;
} 
int f[M],st[N],top,out[N],val[N],ans,dep[N];
bool vis[M];
inline void dfs(int x){
	siz[x]=1;
	e(x)dep[y]=dep[x]+1,val[y]=val[x]^(1<<w[i]),dfs(y),siz[x]+=siz[y],son[x]=siz[y]>siz[son[x]]?y:son[x];
}
inline void add(int x,int d){
	if(!vis[x])vis[x]=1,st[++top]=x;
	f[x]=max(f[x],d);
}
inline void clear(){
	while(top)vis[st[top]]=0,f[st[top--]]=0;
	ans=0;
}
inline void ask(int x,int root){
	ans=max(ans,out[x]);
	rep(i,0,21){
		int k=val[x]^(1<<i);
		if(f[k])ans=max(ans,dep[x]+f[k]-(dep[root]<<1));
	}
	int k=val[x];
	if(f[k])ans=max(ans,dep[x]+f[k]-(dep[root]<<1));
	e(x)ask(y,root);
}
inline void ins(int x){
	add(val[x],dep[x]);
	e(x)ins(y);
}
inline void Dfs(int x){
	e(x)if(y^son[x])Dfs(y),clear();
	if(son[x])Dfs(son[x]);
	e(x)if(y^son[x])ask(y,x),ins(y);
	rep(i,0,21)ans=max(ans,f[val[x]^(1<<i)]-dep[x]);
	ans=max(ans,f[val[x]]-dep[x]);
	add(val[x],dep[x]);
	out[x]=ans;
}
int main(){
	n=read();
	int x;
	rep(i,2,n)x=read(),add(x,i,getchar()-'a'); 
	dfs(1),Dfs(1);
	rep(i,1,n)pf(out[i]),putchar(' ');
	return 0;
}
```


---

## 作者：Brilliance_Z (赞：1)

[Luogu CF741D Arpa's letter-marked tree and Mehrdad's Dokhtar-kosh paths](https://www.luogu.com.cn/problem/CF741D)

第一个难题在于如何简单地表示路径：路径上的字符经过重新排序后可以变成一个回文串 $\Leftrightarrow$ 路径上至多只有 $1$ 种字符出现次数为奇数。于是我们只关心路径上每种字符出现次数的奇偶性，所以我们可以用一个 $22$ 位的二进制串表示一条路径的状态，第 $i$ 位是 $0/1$ 表示字符 `char('a'+i)` 出现次数为偶/奇数。添加/减少一个字符使用模 $2$ 意义下的加/减法——$\operatorname{xor}$ 运算。判断一条路径是否是 Dokhtar-kosh 路径只需判断它的状态 $i$ 是否满足 $\operatorname{popcount}(i)≤1$，换言之，$i$ 是否等于 $0/2^k,(k\in[0,21])$。

设一棵子树的根节点是 $u$。子树 $u$ 内的简单路径分为 $3$ 种：不经过点 $u$ 的路径、经过点 $u$ 且两端都不是点 $u$ 的路径、经过点 $u$ 且一端是点 $u$ 的路径。第 $1$ 种可以往下递归处理，第 $3$ 种是第 $2$ 种的特殊情况，因此我们现在来讨论如何处理第 $2$ 种路径。

一个 $O(N^3)$ 的暴力方法是：对于每一棵子树的根节点 $u$ 都求出子树 $u$ 内所有一端是点 $u$ 的路径，然后把所求得的路径两两配对。

一个 $O(N^2)$ 的优化方法是：对于每一个点 $u$ 都开一个桶 $f_{u,i}$：当前以点 $u$ 为根的子树中，状态是 $i$ 的路径的长度最大值（因为答案要求最长的 Dokhtar-kosh 路径的长度。若不存在状态是 $i$ 的路径，则 $f_{u,i}=0$。）。借助异或运算的性质 $a \operatorname{xor} b=c\Leftrightarrow a=b \operatorname{xor} c$，当即将向点 $u$ 合并一条状态为 $j$ 的新路径时，让路径 $j$ 与桶里状态为 $j \operatorname{xor} 0/j \operatorname{xor} 2^k,(k\in [0,21])$ 的路径配对。

时间复杂度可以使用树上启发式合并继续优化。

但是现在面临着又一个难题：$u$ 怎么快速继承其重儿子 $son_u$ 的桶呢？如果把 $son_u$ 的桶里的所有路径的状态异或上 $w(u,son_u)$，长度加上 $1$，那么复杂度就不能保证。通过新建变量维护桶里元素的值的偏移量，就可以 $O(1)$ 继承重儿子的桶了。

时间复杂度：$O(22\times N\log N)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef pair<int,int> PII;
const int N=5e5+10,M=(1<<22)+10,INF=0x3f3f3f3f;
int n;
int ans[N];
int h[N],e[N],w[N],ne[N],idx;
int siz[N],son[N],wson[N],f[M]; //wson[u]：边(u,son[u])的权值；f[i]：桶，状态是i的路径的长度最大值
vector<PII> path;   //统计轻儿子的路径{状态,长度}
vector<int> cle;    //统计在以当前点为根的子树中修改了哪些桶的信息，辅助作为轻儿子回溯时清空桶的操作

void add(int u,int v,int wor)
{
    e[++idx]=v,w[idx]=wor,ne[idx]=h[u],h[u]=idx;
    return ;
}

//求出每个点的重儿子，为树上启发式合并作准备
void dfs1(int u,int fa)
{
    siz[u]=1;
    for(int i=h[u];i!=0;i=ne[i])
    {
        int v=e[i];
        if(v==fa) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[son[u]]<siz[v]) son[u]=v,wson[u]=w[i];
    }
    return ;
}

//暴力遍历轻儿子
void dfs3(int u,int fa,int dis,int dep)
{
    path.push_back({dis,dep});
    for(int i=h[u];i!=0;i=ne[i])
    {
        int v=e[i];
        if(v==fa) continue;
        dfs3(v,u,dis^w[i],dep+1);
    }
    return ;
}

//树上启发式合并
PII dfs2(int u,int fa)
{
    if(!son[u]) return {0,0};
    for(int i=h[u];i!=0;i=ne[i])
    {
        int v=e[i];
        if(v==fa || v==son[u]) continue;
        dfs2(v,u);
        ans[u]=max(ans[u],ans[v]);
    }
    PII res=dfs2(son[u],u); //偏移量
    ans[u]=max(ans[u],ans[son[u]]); //不经过点u的路径，往下递归处理
    f[res.x]=max(f[res.x],-res.y);
    cle.push_back(res.x);
    res.x^=wson[u];
    res.y++;
    for(int i=h[u];i!=0;i=ne[i])
    {
        int v=e[i];
        if(v==fa || v==son[u]) continue;
        path.clear();
        dfs3(v,u,w[i],1);
        for(auto it : path) //经过点u且两端都不是点u的路径
        {
            ans[u]=max(ans[u],f[(0^it.x)^res.x]+res.y+it.y);    //借助了异或运算的性质a xor b=c <-> a=b xor c
            for(int j=0;j<22;j++) ans[u]=max(ans[u],f[((1<<j)^it.x)^res.x]+res.y+it.y);
        }
        for(auto it : path)
        {
            f[it.x^res.x]=max(f[it.x^res.x],it.y-res.y);
            cle.push_back(it.x^res.x);
        }
    }
    ans[u]=max(ans[u],f[0^res.x]+res.y);    //经过点u且一端是点u的路径
    for(int i=0;i<22;i++) ans[u]=max(ans[u],f[(1<<i)^res.x]+res.y);
    if(son[fa]!=u)//作为轻儿子回溯时要清空桶
    {
        for(auto it : cle) f[it]=-INF;
        cle.clear();
    }
    return {res.x,res.y};
}

int main()
{
    scanf("%d",&n);
    for(int i=2;i<=n;i++)
    {
        int p;
        char c;
        scanf("%d %c",&p,&c);
        add(p,i,1<<(c-'a'));
    }
    dfs1(1,0);
    memset(f,-0x3f,sizeof f);
    dfs2(1,0);
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：xuyuansu (赞：1)

## 题意
给你一棵树，边上有一个字母，求每个点子树内字母重新排列可以形成回文序列的最长路径。
## 题解
这道题可以用树上启发式合并来写。

可以先考虑一下合法的情况怎么来检验。由于只有 22 个字母，所以完全可以状态压缩，表示每个字母出现了奇数或者偶数次，求出每个点到根的路径的状态，两个状态只要异或起来只剩下一个字母或者没有就是合法的。

接下来考虑如何计算答案。一个点子树内的答案有两类，一种过这个点，一种不过。其实只要考虑过这个点的路径就可以了，第二种可以直接继承儿子的答案。现在的问题在于怎样计算长度。

先开一些桶，记录每种情况下对应的节点最深的深度，把这个点子树内所有点到根的路径状态放进桶，每条路径直接找对应的结果，这个结果是当前的最大值。这个用树上启发式合并来写不难。

最后一个问题是，这样计算有可能它的 LCA 不是指定的节点，结合树上启发式合并的写法，可以这样做：在遍历轻儿子来更新当前点时，把这个儿子的子树内节点拿去更新答案，但是不立即更新对应状态的最大深度，用一个 vector 存下来，遍历完这个轻儿子再更新，这样可以保证所有的答案更新都是过指定点的。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,ver[N*2],ne[N*2],head[N],val[N*2],tot;
int dep[N],d[N],siz[N],son[N],ans[24],ma,res[N];
int t[1<<23];
vector<pair<int,int> > v;
void add(int x,int y,int z)
{
	ver[++tot]=y;ne[tot]=head[x];head[x]=tot;val[tot]=z;
}
void dfs(int x)
{
	siz[x]=1;
	for(int i=head[x];i;i=ne[i])
	{
		int y=ver[i];
		dep[y]=dep[x]^(1<<val[i]);
		d[y]=d[x]+1;dfs(y);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]]) son[x]=y;
	}
}
void clear(int x)//清空
{
	t[dep[x]]=0;
	for(int i=head[x];i;i=ne[i])
	{
		int y=ver[i];
		clear(y);
	}
}
void dfs2(int x,int f)
{
	if(t[dep[x]]) ma=max(ma,d[x]+t[dep[x]]-2*d[f]);
	for(int i=0;i<22;i++)
		if(t[dep[x]^(1<<i)]) ma=max(ma,d[x]+t[dep[x]^(1<<i)]-2*d[f]);
	v.push_back(make_pair(dep[x],d[x]));
	for(int i=head[x];i;i=ne[i])
	{
		int y=ver[i];
		dfs2(y,f);
	}
}
void dfs1(int x)
{
	for(int i=head[x];i;i=ne[i])
	{
		int y=ver[i];
		if(y==son[x]) continue;
		dfs1(y);clear(y);ma=0;
		res[x]=max(res[x],res[y]);
	}
	if(son[x]) dfs1(son[x]),res[x]=max(res[x],res[son[x]]);
	if(t[dep[x]])
		ma=max(ma,t[dep[x]]-d[x]);
	for(int i=0;i<22;i++)
		if(t[dep[x]^(1<<i)])
			ma=max(ma,t[dep[x]^(1<<i)]-d[x]);
	t[dep[x]]=max(t[dep[x]],d[x]);
	for(int i=head[x];i;i=ne[i])
	{
		int y=ver[i];
		if(y==son[x]) continue;
		dfs2(y,x);
		for(auto j : v) t[j.first]=max(t[j.first],j.second);//延迟更新
		v.clear();
	}
	res[x]=max(res[x],ma);
}
int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
	{
		int x;char c;
		scanf("%d %c",&x,&c);
		add(x,i,c-'a');
	}
	d[1]=1;dfs(1);
	dfs1(1);
	for(int i=1;i<=n;i++) printf("%d ",res[i]);
	return 0;
}

```


---

## 作者：_HL_ (赞：1)

楼上的大佬们讲的都很好 不过我觉得可能像我一样的初学 dsu on tree 的人看完了不一定能码出来 我来更细致讲一下具体实现好了 qwq

dsu on tree 经典题 做起来感觉还是有一定难度的

关于异或的路径差分和问题转化楼上大佬们讲的很清楚 我就不赘述了 我们相当于有一个 $2^{22}$ 大小的桶 而答案只有 $23$ 种

考虑问题转化后我们要维护的东西

我们记 $w_x$ 为节点 $x$ 到根所有边权值异或和 而我们要找的是一对点 $(x,y)$ 满足：

1. $w_x$ Xor $w_y$ 属于 23 种答案的一种  _包括 0_ 

2. $dep_x+dep_y-2 \cdot dep_{lca(x,y)}$ 最大

如果我们求 $lca$ 将会多一个 $\log$ 不划算且码量大

考虑 dsu on tree 实现的过程 

dsu on tree 很像分治 

1. 处理轻子树内的答案 不保存

2. 处理重子树的答案 保存

3. 再次处理轻子树 合并到重子树答案 得到更大的一颗子树

为什么不保存轻子树答案直接和重子树合并？

合并代价是桶大小 不划算 优化之后可能叫线段树合并 空间大 同时也是 $n\log n$

回到这道题上 我们子树答案为单在子树内的最长路径

按分治的做法 对于点 $x$ 假设我们已经知道所有儿子的子树答案 那么点对在同子树内的不需要处理了 因为我们已经知道它的最大值 只需要考虑跨子树的点对

跨子树点对是要过 $x$ 点的 因此天然的 $lca$ 是 $x$ 继续考虑额 dsu 的过程 现在我们已经处理完了重儿子 需要将轻儿子子树暴力插入处理 

我们的桶维护 $2^{22}$ 种状态中 每种状态的深度最大值 暴力处理子树时更新桶的信息 同时更新 23 种答案的信息 但我们发现 有可能更新后 **有可能取到同一子树的两个点 而他们 $lca$ 一定不为 $x$**

这很像 dp 状态转移时更新的顺序

为解决这个问题 **我们记一个缓存数组 记录要更新的桶和更新的值 当处理完这一子树后一起更新** 那么我们的更新便是用其他子树去更新一个子树了

更新答案即枚举轻子树每个点 求与他的点权  _即他到根路径上所有边异或和_  异或后为答案的 $23$ 个数 从桶数组里分别找到这些权值所对应点的最深深度 更新答案即可 

最终 每个点的 $ans$ 为其所有儿子的 $ans$ 和 $23$ 个数路径长度 的最大值

具体细节 桶数组清空要清为绝对值很大的负数 否则有可能根本不存在异或后为答案的值 但也更新了答案数组

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
const int N=5e5+3;
const int M=(1<<22)+3;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c<='9'&&c>='0')
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x;
}
unordered_map<char,int>mp;
struct node
{
	int to;
	int nxt;
	int w;
}e[N<<1];
int h[N],tot,w[N];
inline void add(int x,int y,int w)
{
	e[++tot].to=y;
	e[tot].nxt=h[x];
	h[x]=tot;
	e[tot].w=w;
}
int dep[N],son[N];
int dfs1(int x,int fa)
{
	int size=1;
	int maxson=-1;
	for(int i=h[x];i;i=e[i].nxt)
	{
		if(e[i].to!=fa)
		{
			w[e[i].to]=w[x]^e[i].w;
			dep[e[i].to]=dep[x]+1;
			int subsize=dfs1(e[i].to,x);
			if(subsize>maxson)
			{
				maxson=subsize;
				son[x]=e[i].to;
			}
			size+=subsize;
		}
	}
	return size;
}
int ans[N],max_dep[M],good[25],dis_good[25];
pair<int,int>change[N];
int cntw;
void dfs2(int x,int fa,int root,int realroot)
{
	if(dep[x]>max_dep[w[x]])
	{
		change[++cntw]={w[x],dep[x]};
	}
	for(int i=0;i<=22;i++)
	{
		int wt=w[x]^good[i];
		dis_good[i]=max(dis_good[i],max_dep[wt]+dep[x]-2*dep[realroot]);
	}
	for(int i=h[x];i;i=e[i].nxt)
	{
		if(e[i].to!=fa)dfs2(e[i].to,x,root,realroot);
	}
}
void clear(int x,int fa)
{
	max_dep[w[x]]=-100000;
	for(int i=h[x];i;i=e[i].nxt)
	{
		if(e[i].to!=fa)clear(e[i].to,x);
	}
}
void dsu(int x,int fa)
{
	if(!son[x])
	{
		for(int i=0;i<=22;i++)
		if(good[i]==w[x])
		{
			dis_good[i]=1;
			break;
		}
		max_dep[w[x]]=dep[x];
		ans[x]=0;
		return;
	}
	for(int i=h[x];i;i=e[i].nxt)
	{
		if(e[i].to!=fa&&e[i].to!=son[x])
		{
			dsu(e[i].to,x);
			clear(e[i].to,x);
			ans[x]=max(ans[x],ans[e[i].to]);
			for(int i=0;i<=22;i++)dis_good[i]=0;
		}
	}
	dsu(son[x],x);
	for(int i=h[x];i;i=e[i].nxt)
	{
		if(e[i].to!=fa&&e[i].to!=son[x])dfs2(e[i].to,x,e[i].to,x);
		for(int j=1;j<=cntw;j++)
		if(max_dep[change[j].first]<change[j].second)
		{
			max_dep[change[j].first]=change[j].second;
		}
		cntw=0;
	}
	for(int i=0;i<=22;i++)
	{
		int wt=w[x]^good[i];
		dis_good[i]=max(dis_good[i],max_dep[wt]-dep[x]);
	}
	if(dep[x]>max_dep[w[x]])
	{
		max_dep[w[x]]=dep[x];
	}
	ans[x]=max(ans[x],ans[son[x]]);
	for(int i=0;i<=22;i++)
	ans[x]=max(ans[x],dis_good[i]);
}
	
int main()
{
	n=read();
	for(int i=0;i<=M-2;i++)max_dep[i]=-100000;
	good[0]=0;
	good[1]=mp['a']=1;
	for(int i=1;i<22;i++)
	good[i+1]=mp['a'+i]=(1<<i);
	for(int i=1;i<n;i++)
	{
		int x=read();
		char c=getchar();
		while(c<'a'||c>'v')c=getchar();
		add(x,i+1,mp[c]);
		add(i+1,x,mp[c]);
	}
	dfs1(1,0);
	dsu(1,0);
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	return 0;
}
```



---

## 作者：billf (赞：1)

[题目传送门 CF741D](https://codeforces.com/problemset/problem/741/D)

题目大意：一棵树的边上有一些字母。对于每颗子树，要找到该子树中一条链，这条链所经过的边上字母经过调整后可以形成回文串。

---

算法：树上启发式合并 $+$ 状压优化。

可以将 $a$ 表示成 $2^0$，

将 $b$ 表示成 $2^1$，

将 $c$ 表示成 $2^2$，

......

可知路径上的字母异或后为 $0$ 或 $2^i$，

才是合法的字符串，

用 $cal_i$ 表示当前在 $u$ 的子树中从根异或到 $v$ 节点的结果为 $i$ 的最大深度。

有 $3$ 种更新答案的方法：

1.子节点的答案

2.从当前 $u$ 节点到 $u$ 的子树中

3.子树中经过 $u$ 节点的路径

对于情况 $1$，由儿子节点更新答案，

对于情况 $2.\ 3$，枚举 $u$ 的子树的每个节点。

---

### Code

```cpp
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <bitset>
using namespace std;
const int M=(1<<22)+10,N=5e5+10;
int n,tot;
int fst[N],nxt[N],to[N],wei[N],fa[N],ex[N],dep[N];
int cnt[N],hson[N],ans[N],cal[M],ord[N],dis[N],ed[N];
char op;
void add_road(int ui,int vi,int wi)
{
	to[++tot]=vi,wei[tot]=wi,
	nxt[tot]=fst[ui],fst[ui]=tot;
}
void dfs(int x)
{
	cnt[x]=1,dep[x]=dep[fa[x]]+1;
	ord[x]=++tot;
	dis[tot]=x;
	for (int i=fst[x];i;i=nxt[i])
	{
		if (to[i]==fa[x]) continue;
		ex[to[i]]=ex[x]^wei[i];
		dfs(to[i]);
		if (cnt[hson[x]]<cnt[to[i]]) hson[x]=to[i];
		cnt[x]+=cnt[to[i]];
	}
	ed[x]=tot;
}
void calc(int x)
{
	for (int i=0;i<=(1<<21);i<<=1,i+=!i)
		if (cal[i^ex[x]])
			ans[x]=max(ans[x],cal[i^ex[x]]-dep[x]);
	cal[ex[x]]=max(cal[ex[x]],dep[x]);
	for (int i=fst[x];i;i=nxt[i])
	{
		int y=to[i];
		if (y==fa[x]||y==hson[x]) continue;
		for (int j=ord[y];j<=ed[y];j++)
		{
			int z=dis[j];
			for (int q=0;q<=(1<<21);q<<=1,q+=!q)
				if (cal[q^ex[z]])
					ans[x]=max(ans[x],cal[q^ex[z]]+dep[z]-2*dep[x]);
		}
		for (int j=ord[y];j<=ed[y];j++) cal[ex[dis[j]]]=max(cal[ex[dis[j]]],dep[dis[j]]);
	}
}
void dfs(int x,bool flag)
{
	for (int i=fst[x];i;i=nxt[i])
	{
		if (to[i]==fa[x]||to[i]==hson[x]) continue;
		dfs(to[i],1),ans[x]=max(ans[x],ans[to[i]]);
	}
	if (hson[x]) dfs(hson[x],0),ans[x]=max(ans[x],ans[hson[x]]);
	calc(x);
	if (flag)
		for (int i=ord[x];i<=ed[x];i++) cal[ex[dis[i]]]=0;
}
int main()
{
	cin>>n;
	for (int i=2;i<=n;i++)
	{
		scanf("%d %c",&fa[i],&op);
		add_road(fa[i],i,1<<(op-'a'));
	}
	tot=0,dfs(1);
	dfs(1,0);
	for (int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：zrzring (赞：1)

[更好的阅读体验](http://zrzring.cn/index.php/archives/247)

首先考虑如何表示Dokhtar-kosh string，因为一个回文串最多有一个出现奇数次的字符，使用hash思想，我们把每一种字母表示成仅一位上是1且互不相同的二进制数，一个字符串的权值定义为该字符串所有字母表示的数的异或和，若一个字符串的权值在二进制下只有一个1则该字符串为Dokhtar-kosh string

记str(x,y)表示x到y的链组成的字符串的权值，考虑树上差分，str(u,v)满足上述性质，等价于str(1,u)异或str(1,v)​满足上述性质，于是预处理出所有的str(1,i)，每次在子树中匹配str(1,j)，这样复杂度是所有子树大小和为$O(n^2)$，用dsu on tree，每个节点只遍历所有轻儿子的子树，即可优化到$O(n log n)$

注意mx数组要初始化为无穷小

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
void file() {
    freopen("std.in", "r", stdin);
    freopen("wa.out", "w", stdout);
}
const int N = 1e6 + 10, V = 2e7 + 10, inf = 1e9;
inline int read() {
    bool sym = 0; int res = 0; char ch = getchar();
    while (!isdigit(ch)) sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}
struct EDGE {
    int u, v, nxt, dis;
} edge[N];
int n, m, head[N], cnt, siz[N], son[N], po[N], L[N], R[N], dis[N], ans[N], mx[V], dep[N];
char ch[N];
void add(int u, int v, int t) {edge[++cnt] = (EDGE){u, v, head[u], t}; head[u] = cnt;}
void dfs1(int u) {
    siz[u] = 1; L[u] = ++cnt; po[cnt] = u;
    for (int e = head[u]; e; e = edge[e].nxt) {
        int v = edge[e].v; dis[v] = dis[u] ^ edge[e].dis; dep[v] = dep[u] + 1;
        dfs1(v); siz[u] += siz[v]; if (siz[v] > siz[son[u]]) son[u] = v;
    }
    R[u] = cnt;
}
void dfs2(int u, bool keep) {
    for (int e = head[u]; e; e = edge[e].nxt) {
        int v = edge[e].v; if (v == son[u]) continue;
        dfs2(v, 0); ans[u] = max(ans[u], ans[v]);
    }
    if (son[u]) dfs2(son[u], 1), ans[u] = max(ans[u], ans[son[u]]);
    ans[u] = max(ans[u], mx[dis[u]] - dep[u]);
    for (int i = 0; i <= 21; i++) ans[u] = max(ans[u], mx[dis[u] ^ 1 << i] - dep[u]);
    mx[dis[u]] = max(mx[dis[u]], dep[u]);
    for (int e = head[u]; e; e = edge[e].nxt) {
        int v = edge[e].v; if (v == son[u]) continue;
        for (int i = L[v], x = po[i]; i <= R[v]; i++, x = po[i]) {
            ans[u] = max(ans[u], mx[dis[x]] + dep[x] - 2 * dep[u]);
            for (int i = 0; i <= 21; i++) ans[u] = max(ans[u], mx[dis[x] ^ 1 << i] + dep[x] - 2 * dep[u]);
        }
        for (int i = L[v], x = po[i]; i <= R[v]; i++, x = po[i]) {
            mx[dis[x]] = max(mx[dis[x]], dep[x]);
        }
    }
    if (!keep) {for (int i = L[u], x = po[i]; i <= R[u]; i++, x = po[i]) mx[dis[x]] = -inf;}
}
int main() {
    n = read(); memset(mx, 128, sizeof(mx));
    for (int v = 2; v <= n; v++) {
        int u = read(); char t = getchar(); add(u, v, 1ll << t - 'a');
    }
    dep[1] = 1; dfs1(1); dfs2(1, 1); for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
    return 0;
}
```



---

## 作者：Gaode_Sean (赞：0)

这是一道 dsu on tree 的板子题，再加上一点类似状压的思想，非常好写。

注意到字母的个数只有 $26$ 个，因此可以用一个二进制数来表示字符串的状态（例如用第 $2^0$ 位表示 $a$，第 $2^1$ 位表示 $b$）。

考虑用 $c_i$ 表示在当前 $x$ 的子树中从根异或到 $y$ 结果为 $i$ 的最大深度。

接下来我们按照启发式合并的套路，对于每个节点，先扫描一遍轻儿子，再考虑重儿子，并保留重儿子中 $c$ 数组的数据，最后再用每个轻儿子来更新答案。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,tot,ver[N],nxt[N],head[N],edge[N],dfn[N],mp[N],sz[N],d[N],s[N],ans[N],c[1<<23],son[N];
void add(int x,int y,int z){ver[++tot]=y,edge[tot]=z,nxt[tot]=head[x],head[x]=tot;}
void add(int x){c[s[x]]=max(c[s[x]],d[x]);}
void del(int x){c[s[x]]=0;}
void rise(int x)
{
	for(int i=dfn[x];i<=dfn[x]+sz[x]-1;i++) add(mp[i]);
}
void clear(int x)
{
	for(int i=dfn[x];i<=dfn[x]+sz[x]-1;i++) del(mp[i]);
}
void dfs(int x)
{
	dfn[x]=++tot,mp[tot]=x,sz[x]=1;
	int mx=0;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=ver[i];
		d[y]=d[x]+1,s[y]=s[x]^edge[i],dfs(y),sz[x]+=sz[y],mx=(sz[y]>sz[mx]?y:mx);
	}
	son[x]=mx;
}
void dsu(int x,bool flag)
{
    for(int i=head[x];i;i=nxt[i])
    {
        int y=ver[i];
        if(son[x]!=y) dsu(y,0),ans[x]=max(ans[x],ans[y]);
	}
	if(son[x]) dsu(son[x],1),ans[x]=max(ans[x],ans[son[x]]);
	for(int i=0;i<=(1<<21);i<<=1,i+=!i) if(c[i^s[x]]) ans[x]=max(ans[x],c[i^s[x]]-d[x]);
	add(x);
	for(int i=head[x];i;i=nxt[i])
	{
		int y=ver[i];
		if(y==son[x]) continue;
		for(int j=dfn[y];j<=dfn[y]+sz[y]-1;j++)
		{
			int z=mp[j];
			for(int k=0;k<=(1<<21);k<<=1,k+=!k) if(c[k^s[z]]) ans[x]=max(ans[x],c[k^s[z]]+d[z]-2*d[x]);
		}
	    rise(y);
	}
	if(!flag) clear(x);
}
int main()
{
	scanf("%d",&n); char ch;
	for(int i=2,x;i<=n;i++) scanf("%d %c",&x,&ch),add(x,i,1<<(ch-'a'));
	tot=0,d[1]=1; dfs(1);
	dsu(1,1);
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：zhang_kevin (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF741D)

[CF题目传送门](https://codeforces.com/problemset/problem/741/D)

这是一道很好的模板题。

你先要学会 DSU on Tree，[这是 CodeForces 上一篇讲 DSU on Tree 的博文](https://codeforces.com/blog/entry/44351)。

大家都知道 DSU on Tree 可以用来处理子树信息，可是有时候它也可以用来处理链上信息。

IOI 2011里有一道名叫 Race 的著名的点分治模板题，要求统计链信息，也可以用 DSU on Tree 来做，题目链接：[$Link$](https://www.luogu.com.cn/problem/P4149)。

基本思路和点分治是一样的，对于每个点 $u$，我们统计出所有经过 $u$ 的路径的信息。

于是我们有了一个非常好的思路：统计每个点 $u$ 的时候，我们记录下 $u$ 的所有子孙节点到 $u$ 的信息，放在一个数组里存储。

以这道题为例，我们把每个字符串压缩为一个二进制串，然后就可以记录 $u$ 的每个后继节点到 $u$ 的路径所形成的字符串。

但问题来了，我们要保留重儿子的信息，但是节点 $u$ 和它的重儿子之间有一个字母，我们要把这个字母加到重儿子的所有后继节点上，这就退化成了暴力了。

对于 [IOI 2011 Race](https://www.luogu.com.cn/problem/P4149) 这样的题，我们可以选择用数据结构维护，于是复杂度多了一个 $log$。

当然还有更简单的解法，对于本题和 [IOI 2011 Race](https://www.luogu.com.cn/problem/P4149) 这样的题，链上的信息是可减的，于是我们可以不保存“后继节点到点 $u$ ”的信息，而是保存“后继节点到根”的信息，然后在统计的时候再减去“ $u$ 到根的信息”。

每个节点到根的信息是不会变的，就不需要维护了，又因为路径信息可减，所以处理起来也很方便。当然，对于不可减的路径信息，可以选择用数据结构维护，维护不了的话还是写点分治吧。

[**AC代码**](https://www.luogu.com.cn/paste/q960lmrn)

---

