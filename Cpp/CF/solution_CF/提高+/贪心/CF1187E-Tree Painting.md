# Tree Painting

## 题目描述

给定一棵包含 $n$ 个顶点的树（无向连通无环图）。你要在这棵树上玩一个游戏。

最开始所有顶点都是白色的。在游戏的第一回合，你选择一个顶点并将其染成黑色。之后的每一回合，你都可以选择一个与任意黑色顶点相邻的白色顶点，并将其染成黑色。

每当你选择一个顶点（包括第一回合），你获得的分数等于包含该顶点的、仅由白色顶点组成的连通块的大小。游戏在所有顶点都被染成黑色时结束。

来看下面这个例子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1187E/80d1bdfd9c05e38560143dd180baa827e846ec90.png)

顶点 $1$ 和 $4$ 已经被染成黑色。如果你选择顶点 $2$，你将获得 $4$ 分，因为包含顶点 $2, 3, 5, 6$ 的连通块的大小为 $4$。如果你选择顶点 $9$，你将获得 $3$ 分，因为包含顶点 $7, 8, 9$ 的连通块的大小为 $3$。

你的任务是最大化你获得的分数。

## 说明/提示

第一个示例的树如题目描述中的图片所示。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
9
1 2
2 3
2 5
2 6
1 4
4 9
9 7
9 8
```

### 输出

```
36
```

## 样例 #2

### 输入

```
5
1 2
1 3
2 4
2 5
```

### 输出

```
14
```

# 题解

## 作者：Rusalka (赞：32)

### 前言

~~您完全可以略过这段。~~

校内模拟赛的时候[一位大奆佬](https://www.luogu.com.cn/user/122641)搬了这题。

~~然后我切了。~~

个人认为这题是一道不错的换根dp，虽然略显套路。


### 题意简述

给定一棵有 $n$ 个结点的无根树，所有结点都是白色的。

第一次操作可以随意使一个结点染成黑色，之后每次操作可以使一个与黑色结点相邻的白色结点变成黑色。

每次操作可以获得的权值为被染成黑色的白色结点所在的白色连通块的结点数量。

求可以获得的最大权值。

~~感觉自己写的好绕。~~

### 题目分析与解答

不难发现只要选定了第一个被染色的结点，答案也就确定了。

所以有一个朴素做法就是以枚举每个结点为根，都做一次树形dp。

以某一结点为根，记 $f_i$ 表示以 $i$ 为根的子树中，首先把 $i$ 染成黑色的答案。

方程就是 $f_u = siz_u+\sum\limits_{v \in son_u} f_v$。

其中 $siz_u$ 表示以 $u$ 为根的子树大小，也就是染色时的白色连通块大小。

~~这部分比较好理解就不画图举例啦。~~

时间复杂度 $O(n^2)$ ，稳稳地暴毙。

然后就会~~自然而然地~~想到换根dp。

先考虑以任意一点为根，不妨记为 $rt$ ，求出 $f$ 数组。

然后记 $g_i$ 表示以 $i$ 结点为根时的答案。

显然有 $g_{rt} = f_{rt}$。

然后考虑 $g$ 数组从父亲到儿子的转移。

以样例为例：![](https://cdn.luogu.com.cn/upload/image_hosting/rsr793c3.png)

我们假设当前以 $1$ 号为根，求出了 $f$ 数组，也就是知道了 $g_1$ ，然后要求出 $g_2$ 。

考虑一下答案的组成。

首先考虑 $2$ 号结点的孩子的贡献，也就是图中蓝圈内的部分。这部分显然不会改变，贡献就是 $f_2-siz_2$ 。

然后考虑父亲方向，也就是图中红圈部分对 $g_2$ 的贡献。

那么除了以 $2$ 号结点，与 $1$ 一号结点相邻的其他子树都会对答案产生贡献，也就是说，我们只需要用以 $1$ 号结点为根时的权值减去以 $2$ 为根的子树的贡献即可，也就是 $g_1-f_2-siz_2$ 。

不要忘了加上 $n$ ，也就是初始的白色连通块大小。

综合一下上述两种方向的贡献，可以得到：$g_2=(f_2-siz_2)+(g_1-f_2-siz_2)+n = g_1 + n - siz_2 \times 2$ 。

推广到所有结点，就可以得到：  

$g_u = g_{father_u} + n - siz_u \times 2$

然后跑两遍 dfs 就愉快的解决啦。

### Code：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

typedef long long ll;
const int MAXN = 200010;

int n;
struct edge{
	int ne, to;
	edge(int N=0, int T=0):ne(N),to(T){}
}e[MAXN<<1];
int fir[MAXN], num = 0;
inline void join(int a, int b)
{
	e[++num] = edge(fir[a], b);
	fir[a] = num;
}

ll siz[MAXN], f[MAXN], g[MAXN], ans = 0;

void dfs1(int u, int fa)
{
	siz[u] = 1;
	for(int i=fir[u];i;i=e[i].ne)
	{
		int v = e[i].to;
		if(v == fa) continue;
		dfs1(v, u);
		siz[u] += siz[v];
		f[u] += f[v];
	}
	f[u] += siz[u];
}
void dfs2(int u, int fa)
{
	for(int i=fir[u];i;i=e[i].ne)
	{
		int v = e[i].to;
		if(v == fa) continue;
		g[v] = n - siz[v] + g[u] - siz[v];
		dfs2(v, u);
	}
}

int main()
{
//	freopen("stars3.in","r",stdin);
//	freopen("stars.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int a, b;
		scanf("%d%d",&a,&b);
		join(a, b);
		join(b, a);
	}
	dfs1(1, 0);	
	g[1] = f[1];
	dfs2(1, 0);
	ll ans = 0;
	for(int i=1;i<=n;i++)
		ans = max(ans, g[i]);
	printf("%lld\n",ans);
	return 0;
}
```

~~似乎只有我时而大括号换行，时而不换行？！~~

---

## 作者：GIFBMP (赞：24)

树形DP好题！

### 正题

我们可以发现，确定第一个点后，后面选点的顺序就不影响权值了。

所以，我们设 $g_x$ 表示先选点 $x$ 时整棵树获得的权值。

我们发现，$g_x$ 直接算比较麻烦，所以，我们定义 $f_x$ 表示选了点 $x$ 后它的**子树**对它的贡献。

易得递推式：

$$f_x=size_x+\sum_{i\in son_x}f_i$$

于是我们得出：

$$g_1=n+\sum_{\{i,1\}\in E}f_i$$

然而，怎么算其它的 $g_i$ 呢？最暴力的思想是以每个点为根重新 $dfs$，然而，这样是 $\Theta (n^2)$ 的，通过不了本题。

所以我们要使用**换根DP**。

怎么换根呢？

来看下面的图：

![graph.png](https://i.loli.net/2020/03/24/msOAt6kfMxD9R2e.png)

易得：

$$g_y=n+(n-size_y)+\sum_{i\in son_x|i\ne y}f_i+\sum_{i\in son_y}f_i$$

$$=n+(n-size_y)+\sum_{i\in son_x|i\ne y}f_i+f_y-size_y$$

$$=n+(n-size_y)+\sum_{i\in son_x}f_i-size_y$$

$$=g_x+n-2\times size_y$$

### Code:

```cpp
#include <cstdio>
#include <vector>
using namespace std ;
typedef long long ll ;
const int MAXN = 2e5 + 10 ;
int n , size[MAXN] ;
vector <int> G[MAXN] ;
ll f[MAXN] , g[MAXN] , ans ;
ll max (ll a , ll b) {
	return a > b ? a : b ;
}
void dfs1 (int x , int fa) {
	size[x] = 1 ;
	for (int i = 0 ; i < G[x].size () ; i++) {
		int v = G[x][i] ;
		if (v == fa) continue ;
		dfs1 (v , x) ;
		size[x] += size[v] ;
		f[x] += f[v] ;
	}
	f[x] += size[x] ;
} 
void dfs2 (int x , int fa) {
	if (x != 1) {
		g[x] = g[fa] + n - size[x] * 2 ;
		ans = max (ans , g[x]) ;
	}
	for (int i = 0 ; i < G[x].size () ; i++) {
		int v = G[x][i] ;
		if (v == fa) continue ;
		dfs2 (v , x) ;
	}
} 
int main () {
	scanf ("%d" , &n) ;
	for (int i = 1 ; i < n ; i++) {
		int u , v ;
		scanf ("%d %d" , &u , &v) ;
		G[u].push_back (v) ;
		G[v].push_back (u) ;
	}
	dfs1 (1 , 0) ;
	ans = g[1] = f[1] ;
	dfs2 (1 , 0) ;
	printf ("%lld" , ans) ;
	return 0 ;
}
```

---

## 作者：Daidly (赞：10)

树形dp+换根dp

- 结论：答案只与第一次选点有关，与剩余选点顺序无关。

证明：

一个点的贡献来源于以它为根的子树和它的祖先中能达到的白点数。

当这个点的父亲已被染成黑色，该点的祖先颜色已无法对该点贡献造成影响，只与子树有关，而子树不受顺序影响。

- 所以答案与除第一次选点顺序无关。

定义：

$size_i$ 为以 $1$ 为根的树中以 $i$ 为根的子树大小。

$f_i$ 为第一次选点选 $i$ 的答案。

$g_i$ 为以 $1$ 为根的树中把 $i$ 作为当前子树的根并染色 $i$ 对答案的贡献。

- 即我们要求 $f_i$ 最大值.

由定义可知：

$f_1=g_1$

$g_i=size_i+\sum_{j\in son(i)}g_j$

$O(n^2)$ 解法就出来了:

以每一个点为第一个选点做一次 `dfs` 求得 $g_i$ 更新 $f_i$ 最大值。

但不能通过这道题，由于 $f_i$ 和根有关系，考虑换根dp求 $f_i$。

![](https://cdn.luogu.com.cn/upload/image_hosting/xbyde8hs.png)

图 $1$：以 $i$ 为根的树。
                                
![](https://cdn.luogu.com.cn/upload/image_hosting/i8xv4xmx.png)

图 $2$：以 $j$ 为根的树。
                                
$j\in son(i)$，考虑怎么通过 $f_i$ 求得 $f_j$：

> $f_j=n$（第 $1$ 次选点 $j$）$+(n-size_j)$（图 $2$ 中以 $j$ 为树的根时以 $i$ 为根的子树的大小）$+\sum_{k\in son(i)|k\ne j}f_k$（图 $2$ 中 $i$ 点的儿子 $f$ 之和）$+\sum_{k\in son(j)}f_k$（图 $2$ 中 $j$ 除 $i$ 以外儿子 $f$ 之和）

结合图自己画一下很好理解。

$$\begin{aligned}
f_j&=n+(n-size_j)+\sum_{k\in son(i)|k\ne j}f_k+\sum_{k\in son(j)}f_k\\
&=n+(n-size_j)+\sum_{k\in son(i)|k\ne j}f_k+(f_j-size_j)\\
&=n+(n-size_j)+(\sum_{k\in son(i)|k\ne j}f_k+f_j)-size_j\\
&=n+(n-size_j)+\sum_{k\in son(i)}f_k-size_j\\
&=(n+\sum_{k\in son(i)}f_k)+(n-2size_j)\\
&=n+f_i-2size_j
\end{aligned}$$

这样，只需要一次 `dfs`，求出 $g_1=f_1$，用 $f_1$ 来算出其他的 $f_i$，选最大值即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

inline void print(long long x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int MAXN=2e5+5;
int n;
long long ans,f[MAXN],g[MAXN],siz[MAXN];
vector<int>e[MAXN];

void dfs1(int x,int fa){
	siz[x]=1;
	for(int i=0;i<e[x].size();++i){
		if(e[x][i]==fa)continue;
		dfs1(e[x][i],x);
		siz[x]+=siz[e[x][i]];
		g[x]+=g[e[x][i]];
	}
	g[x]+=siz[x];
}

void dfs2(int x,int fa){
	for(int i=0;i<e[x].size();++i){
		if(e[x][i]==fa)continue;
		f[e[x][i]]=n+f[x]-2*siz[e[x][i]];
		dfs2(e[x][i],x);
	}
}

int main(){
	n=read();
	for(int i=1;i<n;++i){
		int u=read(),v=read();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs1(1,0);
	f[1]=g[1];
	dfs2(1,0);
	for(int i=1;i<=n;++i){
		ans=max(ans,f[i]);
	}
	print(ans);
	return 0;
}
```
如果您觉得这篇题解讲的还不错，就点个赞吧。

---

## 作者：肖然 (赞：10)

### 题意
给定一棵n个点的树 初始全是白点

要求你做n步操作，每一次选定一个与一个黑点相隔一条边的白点，将它染成黑点，然后获得该白点被染色前所在的白色联通块大小的权值。

第一次操作可以任意选点。

求可获得的最大权值

### 题解

把操作看成黑点逐渐“蔓延”的过程。

树形DP，注意到结点u，存在2种情况：黑色从fa[u]蔓延过来，或者从某个孩子蔓延过来。

设2个DP状态（类似NOIP2018保卫王国）：

```
d[u] = 先染u，染完子树u的最大收益（包括染u的收益）
g[u] = 先染fa[u]，染完子树外的最大收益（包括染fa[u]的收益）
```

转移：
```
d[u] = sz[u] + sum{d[v]}
g[v] = (N - sz[v]) + g[u] + sum{d[v'], v'!=v};
     = (N - sz[v]) + g[u] + d[u] - sz[u] - d[v];
Ans = max{d[u] + g[u] + (N - sz[u])}
```


```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define LL long long
#define LD long double
#define INF int(1e9+7)
#define mkp make_pair
#define fir first
#define sec second
#define base int(1e9)
#define W int(9)
using namespace std;
 
int N;
vector<int> adj[MAXN];
 
int vis[MAXN], sz[MAXN], fa[MAXN];
LL d[MAXN], g[MAXN];
/*
d[u] = sz[u] + sum{d[v]}
g[v] = (N-sz[v]) + g[u] + sum{d[v'], v'!=v};
     = (N-sz[v]) + g[u] + d[u] - sz[u] - d[v];
*/ 
 
void dfs1(int u){
	vis[u] = 1;
	sz[u] = 1;
	
	int v;
	for(int k=0;k<adj[u].size();k++){
		v = adj[u][k];
		if(vis[v]) continue;
		
		fa[v] = u;
		dfs1(v);
		sz[u] += sz[v];
		d[u] += d[v];
	}
	
	d[u] += sz[u];
}
 
void dfs2(int u){
	vis[u] = 1;
	
	int v;
	for(int k=0;k<adj[u].size();k++){
		v = adj[u][k];
		if(vis[v]) continue;
		
		g[v] = (N-sz[v]) + g[u] + d[u] - sz[u] - d[v];
		dfs2(v);
	}
}
 
int main(){
	
	ios::sync_with_stdio(0);
	
	cin>>N;
	
	int u,v;
	for(int i=1;i<N;i++){
		cin>>u>>v;
		
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	dfs1(1);
	memset(vis,0,sizeof(vis));
	dfs2(1);
	
	LL ans = 0;
	for(int i=1;i<=N;i++){
		ans = max(ans, d[i] + g[i] + (N-sz[i]));
	}
	
	cout<<ans<<endl;
	
	return 0;
}

```



---

## 作者：MurataHimeko (赞：5)


------------


### 思路

我们首先定义根节点为第一次染成黑色的节点。令当前根节点为 $u$。

我们来换一个角度思考这道题目，节点 $i$ 在什么时候会贡献 1 个权值呢？显然，在 $i$ 、 $fa[i]$ 、 $fa[fa[i]]$...... 一直到 $u$ 染成黑色时，节点 $i$ 都会贡献 1 个权值。那么一共贡献了多少权值呢？ 我们发现，在 $i$ 到 $u$ 的这一条链上的所有节点被染成黑色时，节点 $i$ 都会贡献 1 个权值。也就是说，当 $u$ 为根节点时，节点 $i$ 的贡献就是当前节点 $i$ 的深度。所以问题就转换为：**试找出一点 $u$，使得以 $u$ 为根节点时，所有点的深度之和最大** 。我们可以利用换根 DP 来解决这个问题。


------------

### 疑问

那有同学可能会问了：为什么 $i$ 到 $u$ 的这一条链上的任意一个节点 $v$ 被染成黑色时，节点 $i$ 都会贡献 1 个权值，也就是 $i$ 一定会和 $v$ 在一个连通块里呢？


因为题目告诉我们：**每一次选定一个与一个黑点相隔一条边的白点，将它染成黑点**。所以我们可以保证，每个节点一定都是由它的父亲节点染成黑色（根节点除外），所以当节点 $v$ 被染成黑色时，它的子树内一定不会有黑点存在，所以节点 $v$ 在染色之前一定与节点 $i$ 联通。



------------

### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define max_(a, b) a > b ? a : b
#define min_(a, b) a < b ? a : b、
#define INF 0x3f3f3f3f
#define rep(i, f, t) for(register int i(f); i <= t; ++i)
#define nx(i, u) for(register int i(head[u]); i; i = e[i].next) 
typedef long long ll;

/***************??***************/

namespace IO {
char buf[1<<21], *p1 = buf, *p2 = buf, buf1[1<<21];
inline char gc () {return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}

#ifndef ONLINE_JUDGE
#endif

template<class I>
inline void read(I &x) {
    x = 0; I f = 1; char c = gc();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = gc(); }
    while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = gc(); }
    x *= f;
}

template<class I>
inline void write(I x) {
    if(x == 0) {putchar('0'); return;}
    I tmp = x > 0 ? x : -x;
    if(x < 0) putchar('-');
    int cnt = 0;
    while(tmp > 0) {
        buf1[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while(cnt > 0) putchar(buf1[--cnt]);
}

#define in(x) read(x)
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')

} using namespace IO;

/***************??***************/

int n;
const int maxn = 2e5+3;
int siz[maxn];

struct node {
    int to, next;
}e[maxn<<1];

int cnt, head[maxn];

inline void add (int u, int v) {
    e[++cnt] = (node){v, head[u]};
    head[u] = cnt;
}

ll ans;
int dep[maxn];
ll dp[maxn];

void dfs_1 (int u, int fa) {
    dep[u] = dep[fa] + 1;
    dp[1] += dep[u];
    siz[u] = 1;
    nx(i, u) {
        int v = e[i].to;
        if(v == fa) continue;
        dfs_1(v, u);
        siz[u] += siz[v];
    }
}

void dfs_2 (int u, int fa) {
    nx(i, u) {
        int v = e[i].to;
        if(v == fa) continue;
        dp[v] = dp[u] + n - (siz[v]<<1);
        dfs_2(v, u);
        ans = max_(ans, dp[v]);
    }
}

int u, v;

int main () {
    read(n);
    rep(i, 1, n-1) {
        read(u), read(v);
        add(u, v), add(v, u);
    }
    dfs_1(1, 0); ans = dp[1];
    dfs_2(1, 0);
    out(ans);
}
```


------------

感谢您能阅读本篇博客！


---

## 作者：SFWR (赞：3)

画图找规律

（~~不好画图~~

设A为父节点，B为子节点，C为A的子节点求和得值，D为B子节点求和得值

则有DP[A]=C+SIZE.B+N+D

DP[B]=D+N+N-SIZE.B+C

得出DB[B]=DP[A]+N-SIZE.B*2;

直接两遍DFS即可

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int nxt,to;}eg[401000];
int ne,head[201000],n,m,a,b,c;
long long dp[401000],size[401000],maxn=-1,ans;
void adde(int from,int to){eg[++ne].to=to;eg[ne].nxt=head[from];head[from]=ne;}
void dfs(int u,int f)
{
    size[u]=1;
    for(int i=head[u];i;i=eg[i].nxt)
    {	int v=eg[i].to;
        if(v==f)continue;
        dfs(v,u);
        size[u]+=size[v];
    }
    ans+=size[u];
}
void dfs2(int u,int f)
{
    for(int i=head[u];i;i=eg[i].nxt)
    {	int v=eg[i].to;
        if(v==f)continue;
        dp[v]=dp[u]+n-2*size[v];
		maxn=max(maxn,dp[v]);
        dfs2(v,u);
    }
}
int read()
{
    int ans;
    int ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){ans=ans*10+ch-'0';ch=getchar();}
    return ans;
}
int main()
{
    cin>>n;
    for(int i=1;i<n;i++){cin>>a>>b;adde(a,b);adde(b,a);}	
    dfs(1,0);
    dp[1]=ans;
    dfs2(1,0);
    cout<<maxn;
}
```


---

## 作者：xcxc82 (赞：2)

# CF1187E Tree Painting 题解

## [原题面](https://www.luogu.com.cn/problem/CF1187E)

## 前置知识: 换根$DP$

换根$DP$模板题

如果您还不会换根$DP$的话,可以先去看看UM巨佬的日报:

[#278[UltiMadow] [学习笔记]换根dp](https://sflsrick.blog.luogu.org/note-how-to-change-root)

## 大致题意


给定一棵n个点的树 初始全是白点

要求你做n步操作，每一次选定一个与一个黑点相隔一条边的白点，将它染成黑点，然后获得该白点被染色前所在的白色联通块大小的权值。

求可获得的最大权值

## 分析

几乎是一道裸的模板题了...

和P3478几乎一摸一样,只是需要一个微小的结论



![](https://cdn.luogu.com.cn/upload/image_hosting/h4z3mf0i.png)

##### PS:图中节点的编号有一点微小的错误,不过并不影响阅读

假如说我们选了图中的1号节点作为第一个涂色的点（图中蓝色的点)

那下一个涂色的节点肯定就能选择它的几个儿子了(图中深红色的点)

同时,**由于父亲节点已经被涂色了,其子节点不可能再和上面的"祖先"辈节点有联通了**
**能对其产生贡献的只有自己的子树**

因此当一个父亲节点被涂色后,其所有子树都是**相对"独立"的**，涂色顺序的变化对总贡献值无任何影响

故当**第一个节点被涂色后,剩下节点的涂色顺序均无法对总贡献值产生影响**

## 代码实现

单纯的暴力枚举每个根的位置的话照这个数据范围肯定会T飞

考虑换根DP



应该很容易状态转移方程推出:

- $dp[v] = dp[u]-2size[v]+size[1]$

具体这个方程怎么来的,我之前写的P3478的[题解](https://www.luogu.com.cn/blog/xcxc82/p3478-poi2008sta-station-ti-xie)跟前面UM巨佬的日报里也有讲



套上换根$DP$的板子即可

贴上丑陋的代码:（其实只要把P3478的代码改一行就可以了）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200010;
vector <int> son[MAXN];
int vis[MAXN],n;
long long size[MAXN];
long long f[MAXN];
void dfs(int u){
	size[u] = 1;
	vis[u] = 1;
	for(int i=0;i<son[u].size();i++){
		int v = son[u][i];
		if(!vis[v]){
			dfs(v);
			size[u]+=size[v];
		}
	}
}
void dp(int u){
	vis[u] = 1;
	for(int i=0;i<son[u].size();i++){
		int v = son[u][i];
		if(!vis[v]){
			f[v] = f[u] + size[1] - 2*size[v];
			dp(v);
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		son[u].push_back(v);
		son[v].push_back(u);
	}
	dfs(1);
	for(int i=1;i<=n;i++){
		f[1]+=size[i];
	}
   memset(vis,0,sizeof(vis));
   dp(1);
   long long ans = -0x3f;
   for(int i=1;i<=n;i++){
   	 ans = max(ans , f[i]);
   }
   printf("%lld",ans);
}
```




---

## 作者：龙翔凤翥 (赞：1)

## solution：
#### ****树形DP+换根法与二次扫描****
1. 因为这是一棵树，所以以x为根的子树根节点x所能产生的贡献为size(x)。最后生成的一棵树的总贡献便为**每个点的贡献之和**。
2. 考虑如何换根：~~显然对于每一个节点都可以成为根节点~~，我们先dfs一遍找出一棵树的贡献（假设根节点为1）。然后对于与1号连接的所有点进行转移。设f[x]表示以x为根节点所产生的代价，则对于x所连接的每个点y，有$ f[y]=f[x]-size(y)+n-size(y) $ 这个需要画图理解一下。（因为对于一次换根，x，y以外的点没有对之前的答案产生新的影响，只需要计算x，y这两个点产生贡献的变化值即可。
## code：
```
#include<bits/stdc++.h>
using namespace std;
#define RN register int
const int N=2e5+10;
#define int long long 
inline int read() {
    int x=0,o=1;
    char ch=getchar();
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-') o=-1,ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*o;
}
int t,n,w;
struct P{
	int n;
	int t;
}a[N<<1];
int tot,head[N],d[N],f[N],dp[N],maxn,ans;
inline void add(RN x,RN y)
{
	a[++tot].n=head[x];
	a[tot].t=y;
	head[x]=tot;
}
inline void dfs(int x,int fa)//一遍搜索先求出一棵树的贡献
{
	d[x]=1;
	for(RN i=head[x];i;i=a[i].n)
	{
		int y=a[i].t;
		if(y==fa)continue;
		dfs(y,x);
		d[x]+=d[y];
	}
	ans+=d[x];
}
inline void dfs2(int x,int fa)//换根
{
	for(RN i=head[x];i;i=a[i].n)
	{
		int y=a[i].t;
		if(y==fa)continue;
		dp[y]=dp[x]+n-2*d[y];
		//cout<<dp[y]<<" "<<d[y]<<" "<<n<<endl;
		maxn=max(maxn,dp[y]);
		dfs2(y,x);
	}
}
signed main()
{
	n=read();
	for(RN i=1;i<n;i++)
	{
		int x=read(),y=read();
		add(x,y);add(y,x);
	}
	dfs(1,0);
	//for(RN i=1;i<=n;i++)
	//	cout<<d[i]<<endl;//d[x]表示以x为根的子树大小
	dp[1]=ans;
	dfs2(1,0);
	cout<<maxn<<endl;
	return 0;
}
```

---

## 作者：resftlmuttmotw (赞：1)

#### 思路

典型的树形$DP$

然而并不能一次$dfs$求出答案

要用换根法

按照个人理解的话

换根法就是

在选起点做树形$DP$时

对于$ans[1]$//以$1$为起点的答案值

我们可以 通过$O(1)$ 算出$ans[sonof1]$

~~感觉就是树形$DP$嘛~~

#### 实现

对于这道题

我们先以$1$为根


容易写出
```cpp
inline void dfs(int x,int fa)
{
	size[x] = 1;
	for(reg i = head[x];i;i = edge[i].next)
	{
		int v = edge[i].v;
		if(v == fa) continue;
		dfs(v,x);
		size[x] += size[v];
	}
	ans[1] += size[x];
}
```
转移的话

先来张图

![](https://s2.ax1x.com/2019/11/07/MkpxX9.png)
对于$x$

$ans[y]=f[xson1]+f[xson2]+f[xson3]+size[x]+size[y]+f[yson1]+f[yson2]+f[yson3]$

有$size[x]=n-size[y]$

$ans[y]=ans[x]+n-size[y]-size[y]$


### $code$


开$longlong$
```cpp
#include <stack>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define reg register int
#define isdigit(x) ('0' <= x&&x <= '9')
template<typename T>
inline T Read(T Type)
{
	T x = 0,f = 1;
	char a = getchar();
	while(!isdigit(a)) {if(a == '-') f = -1;a = getchar();}
	while(isdigit(a)) {x = (x << 1) + (x << 3) + (a ^ '0');a = getchar();}
	return x * f;
}
const int MAXN = 2e5 + 10;
struct node
{
	int v,next;
}edge[MAXN << 1];
int cnt,size[MAXN],head[MAXN];
long long pr,ans[MAXN];
inline void addedge(int u,int v)
{
	edge[++cnt].v = v;
	edge[cnt].next = head[u];
	head[u] = cnt;
}
inline void dfs(int x,int fa)
{
	size[x] = 1;
	for(reg i = head[x];i;i = edge[i].next)
	{
		int v = edge[i].v;
		if(v == fa) continue;
		dfs(v,x);
		size[x] += size[v];
	}
	ans[1] += size[x];
}
inline void dfs2(int x,int fa)
{
	for(reg i = head[x];i;i = edge[i].next)
	{
		int v = edge[i].v;
		if(v == fa) continue;
		ans[v] = ans[x] + size[1] - 2 * size[v];
		pr = max(pr,ans[v]);
		dfs2(v,x);
	}
}
int main()
{
	int n = Read(1);
	for(reg i = 1;i < n;i++)
	{
		int u = Read(1),v = Read(1);
		addedge(u,v),addedge(v,u);
	}
	dfs(1,0);
	dfs2(1,0);
	printf("%lld",pr);
	return 0;
}

//f[x] = n + f[xson]

//f[y] = n + f[yson] = f[x] + n - 2 * size[y] 
```


---

## 作者：JK_LOVER (赞：0)

## 题意
给你一颗节点个数为 $n$ 的无根树，选择一个节点作为根算出最大贡献。
[QWQ](https://www.luogu.com.cn/blog/xzc/solution-cf1187e)
$$
ans =\max(ANS_{i=root}) (1\le i \le n)
$$
## 分析
如果暴力枚举根那么复杂度为 $O(n^2)$ 。考虑优化 $dp$ 过程。

![](https://cdn.luogu.com.cn/upload/image_hosting/rroc0b8e.png)
如图，如果我们规定了 $1$ 为根。那么一个点的贡献其实可以分成两部分。一部分由父亲传来，另一部分由子树传来 （如图点 $4$ ）。

- 考虑换根 $dp$ 。定义 $up[i]$ 是父亲贡献。$down[i]$ 是子树贡献， $si[i]$ 是子树大小。那么有如下 $dp$
$$
ans[i] =\text{两棵树的贡献+多出来的贡献} = up[i] + down[i] + n - si[i] 
$$
$$
up[i] =\text{父亲的父亲的贡献+除开这个儿子的贡献+父亲的贡献} 
$$
$$
up[fa] + (sum[fa] - si[fa] - sum[x]) + (n-si[x]) 
$$
$$
down[i] = \sum_{j\in son_i}down[j] + si[j]
$$
所以只需要刷两次表就行了。复杂度 $O(n)$ 。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int read()
{
	int x = 0,f = 0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int inf = 100000000;
const int N = 2100010;
int ans[N],sum[N],si[N],n;
vector<int> G[N]; 
void dfs1(int x,int fa)
{
	si[x] = 1;
	for(int i = 0;i < G[x].size();i++)
	{
		int y = G[x].at(i);
		if(y == fa) continue;
		dfs1(y,x);
		si[x] += si[y];
		sum[x] += sum[y];
	}
	sum[x] += si[x];
}
void dfs2(int x,int fa)
{
	ans[x] = ans[fa] + (n-si[x]) + sum[fa] - si[fa] - sum[x];
	for(int i = 0;i < G[x].size();i++)
	{
		int y = G[x].at(i);
		if(y == fa)continue;
		dfs2(y,x);	
	}  
}
signed main()
{
	n = read();
	for(int i = 1;i < n;i++)
	{
		int a = read(),b = read();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs1(1,1);
	for(int i = 0;i < G[1].size();i++)
	{
		int y = G[1].at(i);
		dfs2(y,1);
	}
	int ANS = 0;
	for(int i = 1;i <= n;i++)
	ANS = max(ANS,ans[i]+sum[i]+n-si[i]);
	printf("%lld\n",ANS);
	return 0; 
}
```



---

## 作者：xlqs23 (赞：0)

**大意**

给一棵树，初始时结点都为白色，然后你可以选一个点作为根节点，加上这个节点连通的白色节点数，然后把这个点染黑。下面再继续选择与黑节点相连的点，加上白色节点数，染黑。求最大的值。

 

**思路**

那么我们很容易意识到，起关键作用的就是选择了那个根节点。设dp[i]为以i为根节点的最大值。则，我们对于一个根节点，如点1，记sum[i]为i节点子树的个数，则

$dp[1]=sum[1]+sum[2]+...+sum[n]$

那么转移到下一个点，如2号点，有：

$dp[2]=sum[1]+sum[3]+sum[4]+...+sum[n]+(sum[1]-sum[2])$

很显然，每次换根后，需要 $-2*sum[to]+sum[1]$，2次搜索即可

**Code**

AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll son[200005];
ll all,ans;
vector<int>vec[200005];
void dfs1(int now,int fa,int dep){
    all+=dep;
    son[now]=1;
    for(int i=0;i<vec[now].size();i++){
        int to=vec[now][i];
        if(to!=fa){
            dfs1(to,now,dep+1);
            son[now]+=son[to];
        }
    }
}
void dfs2(int now,int fa,ll val){
    ans=max(ans,val);
    for(int i=0;i<vec[now].size();i++){
            int to=vec[now][i];
            if(to!=fa){
                dfs2(to,now,val-2ll*son[to]+son[1]);
            }
        }
}
int main(){
    all=0,ans=0;
    int n,a,b;
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);
        vec[a].push_back(b);
        vec[b].push_back(a);
    }
    dfs1(1,1,1);
    dfs2(1,1,all);
    printf("%lld\n",ans);
    return 0;

}

---

