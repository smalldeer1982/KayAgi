# Li Hua and Path

## 题目描述

Li Hua has a tree of $ n $ vertices and $ n-1 $ edges. The vertices are numbered from $ 1 $ to $ n $ .

A pair of vertices $ (u,v) $ ( $ u < v $ ) is considered cute if exactly one of the following two statements is true:

- $ u $ is the vertex with the minimum index among all vertices on the path $ (u,v) $ .
- $ v $ is the vertex with the maximum index among all vertices on the path $ (u,v) $ .

There will be $ m $ operations. In each operation, he decides an integer $ k_j $ , then inserts a vertex numbered $ n+j $ to the tree, connecting with the vertex numbered $ k_j $ .

He wants to calculate the number of cute pairs before operations and after each operation.

Suppose you were Li Hua, please solve this problem.

## 说明/提示

The initial tree is shown in the following picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797F/40030754c3599c0066765ff738689e7d545076fa.png)There are $ 11 $ cute pairs — $ (1,5),(2,3),(2,4),(2,6),(2,7),(3,4),(3,6),(3,7),(4,5),(5,7),(6,7) $ .

Similarly, we can count the cute pairs after each operation and the result is $ 15 $ and $ 19 $ .

## 样例 #1

### 输入

```
7
2 1
1 3
1 4
4 6
4 7
6 5
2
5
6```

### 输出

```
11
15
19```

# 题解

## 作者：masterhuang (赞：8)

吐槽：打这场 $\texttt{CF}$ 的时候就觉得 $F$ 不难，然后还是花了一些时间才做出来。这是 $\texttt{CN}$ 场，于是 $E,F$ 都非常套路，基本上是见过套路会做没见过不会做，希望出题人可以多考察思维。

---
首先要想到的是肯定是在原来的答案上计算修改后增加的贡献。

容易想到容斥，令 $A$ 表示 $(u,v),u<v$ 满足 $u$ 是 $u\to v$ 路径上编号最小的点构成的集合，$B$ 表示 $(u,v),u<v$ 满足 $v$ 是 $u\to v$ 路径上编号最大的点构成的集合。则答案为 $|A|+|B|-2|A\cap B|$ 。

我们先思考修改为造成什么贡献。令修改为 $(i,x),i>n$ 。对 $B$ 的影响显然是增加 $i-1$。考虑对 $A$ 的影响，令修改后的集合为 $A'$。若 $(u,x)\in A$，则显然有 $(u,i)\in A$，显然也有 $(i,x)\in A'$，其他 $(t,i)$ 都 $\not\in A'$。

我们令 $c_v$ 表示 $u$ 的个数满足 $\forall\ k$ 在 $u\to v$ 的路径上，$u\le k$。

则我们对于修改有 $c_i=c_x+1$。

容易推得 $|A\cap B|$ 的增加量和 $|A|$ 的是一样样的。于是修改的影响为：$c_i\gets c_x+1,ans\gets ans+i-1-c_i$。

---
下面只要计算最初的 $ans$ 和 $c_i$ 即可。

前置知识：点权多叉重构树，不会的可以到魏老师的[博客](https://www.cnblogs.com/alex-wei/p/Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree_Tree.html)学习。

记 $x,y$ 在重构树上的 $\text{lca}$ 为原树上的路径 $x \to y$ 上的最大、小值构成的树分别为 $T_1,T_2$。

则最初的 $c_i$ 为 $i$ 在 $T_2$ 上的深度 $-1$，若 $(u,v)\in A\cap B$，则  $x$ 在 $T_1$ 上是 $y$ 的祖先，$y$ 在 $T_2$ 上是 $x$ 的祖先。

即在 $T_2$ 上 $y$ 在 $x$ 到根的路径上，在 $T_1$ 上 $dfn_x\in[dfn_y,dfn_y+sz_y)$。$\texttt{dfs}+$ 树状数组计数即可。

```cpp
void dfs1(int x,int f)
{
	ans-=2*(B.ask(mx.id[x]+mx.siz[x]-1)-B.ask(mx.id[x]-1));B.add(mx.id[x],1);
	for(int i=mn.e.head[x];i;i=mn.e.e[i].nex)
	{
		int to=mn.e.e[i].to;
		if(to!=f) dfs1(to,x);
	}B.add(mx.id[x],-1);
}
```
完整代码看[这里](https://codeforc.es/contest/1797/submission/202314367)。

---

## 作者：Luciylove (赞：7)

于 2023.5.10 更新 ： 更正了两处笔误。

考虑如下定义：

$A$ 表示满足第一种路径的 $(u,v)$ 集合。

$B$ 表示满足第二种路径的 $(u,v)$ 集合。

$C$ 表示满足前两种路径的 $(u,v)$ 集合。

然后答案显然就是 $|A| + |B| - 2|C|$。先求出这一类的答案，再解决动态挂叶子的问题。

考虑建出重构树大根小根各两颗。这样就可以解决关于两类限制的计数。

$A,B $：直接是子树内多少个点，这是显然的。

$C$：考虑在大根子树里数有多少个有多少个小根树上的父亲，这样构成一条直上直下的链。

但是直接这样做是大约两只 $\log$ 的，很劣。不如转换计数的主体，考虑枚举子树内的儿子，然后数根节点到自己路径上有多少个自己小根树上的儿子，这个是简单的，单点插入 dfs 序，区间查询，这个可以用树状数组解决。

最后考虑动态挂叶子。由于 $u'$ 编号的性质，显然的是，加入一个叶子，他就会成为一个大根树的根节点，成为一个小根树的叶子节点，然后直接考虑计算。

- $A'$：显然是没有的。

- $B'$：除了 $u'$ 的所有节点 $v$ 都可以产生一对 $(u, v)$ 的贡献.

- $C'$：数一下自己重构树上有多少个祖先就好了。

那么增加的答案就是 $|B'| - |C'|$ 就好了。

综上该问题被我们用 $O(n\log n)$ 的时间解决。

注释暂且不写了。

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define int long long

using namespace std;

const int N = 4e5 + 5, MOD = 998244353;

int n, m, ans, dfc;
int dep[N], fa[N], sz[N], st[N], ed[N];
int v[N];

vector <int> mx[N], mn[N], e[N];

void add (int u, int k) { for ( ; u <= n; u += u & -u) v[u] += k; }
int query (int u) {
	int res = 0;
	for ( ; u; u -= u & -u) res += v[u];
	return res;
}
void init () { for (int i = 1; i <= n; i ++) fa[i] = i; }
int find (int u) { if (u != fa[u]) return fa[u] = find(fa[u]); else return u; }
void merge (int u, int v) {
	u = find(u), v = find(v);
	if (u == v) return ;
	fa[v] = fa[u]; 
}
void dfs1 (int u) {
	sz[u] = 1, st[u] = ++ dfc;
	for (int v : mx[u]) dfs1(v), sz[u] += sz[v];
	ans += sz[u] - 1, ed[u] = dfc;
}
void dfs2 (int u) {
	sz[u] = 1;
	for (int v : mn[u]) dep[v] = dep[u] + 1, dfs2(v), sz[u] += sz[v];
	ans += sz[u] - 1;
}
void dfs3 (int u) { 
	ans -= 2 * (query(ed[u]) - query(st[u] - 1));
	add(st[u], 1);
	for (int v : mn[u]) dfs3(v);
	add(st[u], -1);
}	// 考虑算多少个祖先在自己的 max子树里, 1 ~ v 
signed main () {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin >> n, init();
	for (int i = 1, u, v; i < n; i ++) cin >> u >> v, e[u].pb(v), e[v].pb(u);
	for (int u = 1; u <= n; u ++) 
		for (int v : e[u]) if (v < u && find(u) != find(v)) 
			mx[u].pb(find(v)), merge(u, v); // 此时 v 属于的祖先一定是严格劣于 u 的, fv -> u 
	init(), dfs1(n);
	for (int u = n; u; u --) 
		for (int v : e[u]) if (v > u && find(u) != find(v)) 
			mn[u].pb(find(v)), merge(u, v);	
	dfs2(1), dfs3(1);
	cout << ans << endl, cin >> m;
	for (int i = 1, u; i <= m; i ++) {
		cin >> u, dep[n + i] = dep[u] + 1;
//		cout << u << endl;
		ans += n + i - dep[n + i] - 1;
		cout << ans << endl;
	}
	return 0;
}

```


---

## 作者：ZillionX (赞：4)

> 给定一棵大小为 $n$ 的树，求满足以下中恰好一个条件的点对 $(u,v)$ 的个数：1. $u$ 为 $u \to v$ 的路径上编号最小的点；2. $v$ 是 $u \to v$ 的路径上编号最大的点。  
要求支持动态挂编号为 $n+i$ 的叶子。  
$n,m \le 2\times 10^5$，2s。

这题说难吧也不难，说简单吧我赛时还只想出 $\mathcal O(n \log^2 n)$ 做法，不好评价。但是确实是套路题。

首先，我们指出，有一个显然的 $\mathcal O(n \log^2 n)$ 做法。

设 $A$ 为满足条件 1 的路径，$B$ 为满足条件 2 的路径，$C$ 为同时满足两个条件的路径，则答案为 $A+B-2C$。

我们考虑点分治，则我们可以对每个分治中心 $u$ 的子树维护三元对 $(i,\max,\min)$ 表示结点 $i \to u$ 的路径上编号的 $\max$ 和 $\min$，则 $A,B$ 容易求出，而 $C$ 为一个二维数点问题，用树状数组维护即可。

对于动态挂叶子，一个不成熟的想法是维护点分树，但是注意到和原树不同的是，现在我们每次都是挂一个编号最大的叶子，则我们设 $f_i$ 为以 $i$ 结尾的满足条件 1 的路径，则每次都有 $f_{n+i}=f_i+1$，对答案贡献为且仅为 $n+i-f_{n+i}-1$（因为 $n+i$ 不可能作为 $u$ 和前面的点满足条件 1）。而 $f_i$ 是容易求出的。那么点分的做法就容易写出了。

然而现在我们已经将原问题转化为一个静态问题，可以看出，有一个更方便且复杂度更优的 $\mathcal O(n \log n)$ 做法。

我们再次注意到，题目的限制和瓶颈路问题有很强的关系，而 Kruskal 重构树是解决瓶颈路问题的经典算法。又因为题目中的条件是点权而非边权，那么我们尝试使用 Kruskal 点权多叉重构树刻画问题。

建出 $\rm LCA$ 权值为 $u \to v$ 路径上编号最小值的重构树（下文称其为“最小树”）和最大树后，可以发现，$A$ 等价于最小树上自上而下的路径的数量，$B$ 等价于最大树上自上而下的路径的数量，$C$ 等价于在两棵树上同时自上而下的路径的数量。

那么，$A$ 和 $B$ 用子树和容易求出。对于 $C$，一个不成熟的想法是启发式合并 + 二维数点。但是我们有经典套路“状态互补”，对于这种子树合并 + 子树查询问题（即用“祖先对子树”的关系解题），可以转化为链合并（也就是单点修改）+ 链查询问题（由对称关系转换了求和主体）。

那么，现在我们就可以对本题做到 $\mathcal O(n \log n)$ 的时间复杂度。

```cpp
const int N=2e5+5;
int n,m,as,f[N],sz[N],in[N],ot[N],tim,dep[N];
vct g[N],mn[N],mx[N];
void init(){
	for(int i=1;i<=n;i++)f[i]=i;
}
int fd(int x){
	return f[x]==x?x:f[x]=fd(f[x]);
}
void mrg(int x,int y){
	x=fd(x),y=fd(y);
	if(x==y)return;
	f[y]=x;
}
void dfsmx(int u){
	sz[u]=1;
	for(int v:mx[u])dfsmx(v),sz[u]+=sz[v];
	as+=sz[u]-1;
}
void dfsmn(int u){
	sz[u]=1,in[u]=++tim;
	for(int v:mn[u])dep[v]=dep[u]+1,dfsmn(v),sz[u]+=sz[v];
	as+=sz[u]-1;
	ot[u]=tim;
}
int v[N];
void add(int x,int y){
	for(;x<=n;x+=lw(x))v[x]+=y;
}
int qry(int x){
	int sm=0;
	for(;x;x-=lw(x))sm+=v[x];
	return sm;
}
void dfs(int u){
	as-=2*(qry(ot[u])-qry(in[u]-1));
	add(in[u],1);
	for(int v:mx[u])dfs(v);
	add(in[u],-1);
}
signed main(){
	cin>>n;
	for(int i=1,u,v;i<n;i++)cin>>u>>v,g[u].pb(v),g[v].pb(u);
	init();
	for(int i=1;i<=n;i++)for(int v:g[i])if(v<i&&fd(i)!=fd(v))mx[i].pb(fd(v)),mrg(i,v);
	init();
	for(int i=n;i;i--)for(int v:g[i])if(v>i&&fd(i)!=fd(v))mn[i].pb(fd(v)),mrg(i,v);
	dfsmx(n);
	for(int i=1;i<=n;i++)sz[i]=0;
	dfsmn(1);
	for(int i=1;i<=n;i++)sz[i]=0;
	dfs(n);
	cout<<as<<endl;
	cin>>m;
	for(int i=1;i<=m;i++){
		int u;cin>>u;
		dep[n+i]=dep[u]+1;
		as+=n+i-dep[n+i]-1;
		cout<<as<<endl;
	}
	return 0;
}
/*
Coder: ZillionX
*/
```


---

## 作者：hegm (赞：2)

一个不错的题目，重新引发了我对重构树的思考。

多的不说，先看题目。

题目是让我们求解两类点对。

我们称 $A$ 集合中的点对，满足题目的 `case1`（$A$ 性质）。

$B$ 集合的点对，满足题目中的 `case2`（$B$ 性质）。

$C=A\cap B$，即同时满足 `case1` `case2` 的点对。

那么答案就是 $|A|+|B|-2\times |C|$。

先不考虑加点操作，我们只考虑一棵普通的树。

由于题目让求的类似于瓶颈路，所以我们自然的想到 $\text{Kruskal}$ 及其重构树。

我们考虑如何求解 $|A|$（$|B|$ 同理即可）。

因此本质上，我们需要对于每个节点 $x$，求出在经过不小于 $x$ 节点的情况下，能到达的点集。

由于是 $\text{Kruskal}$ 算法，我们要考虑边权是什么，考虑一条 $x\leftrightarrow y$ 的边，不管我们是从 $x\to y$，亦或是 $y\to x$，我们经过的最小节点一定是 $\min (x,y)$，因此我们自然可以将 $x\leftrightarrow y$ 的边权定为 $\min (x,y)$。

那么我们按照边权从大到小建出 $\text{Kruskal}$ 重构树，那么对于一个节点 $x$，其能到达的节点就是不断暴力向上跳父亲，直至最高的，权值为 $x$ 的节点，那么其子树内的所有节点 $x$ 都能在作为最小值的情况下到达。

其实到这里就差不多了，继续转头去处理 $|C|$ 即可，但是我发现我们这一切的前提都在权值为 $x$ 的节点在重构树上都是一个联通快的情况下。

这其实是非常好理解的，因为重构树新建节点本质是边，而边权相等的边会紧挨着依次加入，因此形成的权值为 $x$ （包括 $x$ 本身对应的节点）他们一定是联通的。

这时我又进一步的思考，可不可以将树上，权值相同的节点缩起来？

举个例子

对于原树：

![](https://cdn.luogu.com.cn/upload/image_hosting/18077zuq.png)

我们建出的朴素重构树为：

![](https://cdn.luogu.com.cn/upload/image_hosting/rsh2csmn.png)

我们不妨将点缩起来，即 $w=1,1|w=2,w|w=3,3|4$ 一共四组点，并且依然维护连边性。

![](https://cdn.luogu.com.cn/upload/image_hosting/1nli9beo.png)

其中 $1$ 为根节点，那么对于图中的任何一个节点 $i$，其子树内所有节点都可以通过走不小于 $i$ 的点到达。

这样我们就构造出了一棵 $n$ 个节点的树，并且完美的满足 $A$ 性质。

那么点对总数就是每个节点的子树 $\text{size}$ 之和。

同理我们继续求出 $|B|$ 即可。

为了方便，我们称满足 $A$ 性质的树为 $A$ 树，同理为 $B$ 树。

现在考虑如何求出 $|C|$，我们不妨枚举一个节点 $i$，考虑对于他来说有多少条以其为大端点的路径且满足性质 $C$。

这是一个偏序问题，根据上述定义我们可知，对于一个合法节点 $j$ 其要满足在 $B$ 树上是 $i$ 的孩子，且 $A$ 树上是 $i$ 的祖先。

处理这个也很简单和套路，我们不妨求出每个节点在 $B$ 树上的 $\text{dfn}$ 序，然后在 $A$ 树上 $\text{dfs}$，每次将访问新节点 $i$ 时将 $\text{dfn}_{i}$ 位置 $+1$，离开时将 $\text{dfn}_i$ 位置 $-1$。这样我们就可以保证仅在 $A$ 树上为 $i$ 祖先的节点有贡献，然后查询 $B$ 树上的 $i$ 子树总和即可。

轻松加愉快就解决了！

但是别急，我们还要处理添加新节点那。

考虑添加一个新节点 $n+i$，容易发现，他在 $B$ 树上一定为根，这是一个很好的性质，因此他对 $|B|$ 的贡献就是 $n+i$，而在 $A$ 树上，截止目前，他一定是一个叶子，因此对 $|A|$ 的贡献为其深度。

考虑 $|C|$ 的贡献，由于在 $B$
 树上，它当前是根，对于任何一个其在 $A$ 树上的祖先，也一定满足 $B$ 树上的限制，因此对 $|C|$ 的贡献一定为祖先数量，也就是其深度。

那么本题就解决了，代码很简单，但是我写麻烦了，写完才注意到新加节点对 $|C|$ 的贡献可以直接算，并且新建节点也没必要离线。
 
### CODE

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define make make_pair
#define pii pair<int,int>
#define N 400005
//n个节点的特殊重构树，适用于边权由两端点决定的情况 
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,rt[2],m,w[N];
ll ans;
pii e[N];
vector<int> v[2][N];
bool cmp1(pii a,pii b)
{
	return a.fi<b.fi;
}
bool cmp2(pii a,pii b)
{
	return a.fi>b.fi;
}
int f[N],siz[2][N],dfn[N],cnt,dep[N],qwq[N];
int find(int x)
{
	if(f[x]==x)return x;
	return f[x]=find(f[x]);
}
void solve(int p)
{
	for(int i=1;i<=n+m;i++)f[i]=i;
	for(int i=1;i<n+m;i++)
	{
		int a=find(e[i].fi),b=find(e[i].se);
		f[b]=a;v[p][a].push_back(b);
	}
}
void dfs(int p,int now)
{
	if(now<=n)siz[p][now]=1;
	if(p&&now<=n)dfn[now]=++cnt;
	for(int x:v[p][now])
	{
		dfs(p,x);
		siz[p][now]+=siz[p][x];
	}
}
#define lb(x) (x&(-x))
int tr[N];
void add(int x,int w)
{
	while(x<=n)tr[x]+=w,x+=lb(x);
}
int que(int x)
{
	int ans=0;
	while(x)ans+=tr[x],x-=lb(x);
	return ans;
}
void get(int now)
{
	if(now<=n)
	{
		add(dfn[now],1);
		ans-=2*(que(dfn[now]+siz[1][now]-1)-que(dfn[now]-1));
	}
	else
	{
		qwq[now]++;
		w[now]=+now-dep[now];
	}
	for(int x:v[0][now])
	{
		dep[x]=dep[now]+1;
		qwq[x]=qwq[now];
		get(x);
	}
	if(now<=n)add(dfn[now],-1);
}
signed main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		e[i]={read(),read()};
		if(e[i].fi>e[i].se)swap(e[i].fi,e[i].se);
	}
	m=read();
	for(int i=1;i<=m;i++)e[n-1+i]={read(),n+i};
	sort(e+1,e+n+m,cmp2);
	dep[1]=1;
	solve(0);
	dfs(0,1);
	for(int i=1;i<n+m;i++)swap(e[i].fi,e[i].se);
	sort(e+1,e+n+m,cmp1);
	solve(1);
	dfs(1,n+m);
	for(int i=1;i<=n;i++)ans+=siz[0][i]+siz[1][i];
	get(1);
	cout<<ans<<"\n";
	for(int i=1;i<=m;i++)
	{
		ans+=w[i+n];
		cout<<ans<<"\n";
	}
	return 0;
}

```

---

## 作者：Conan15 (赞：1)

看上去这个题目限制很玄学，但实际上可以通过转化变成三个简单的部分。\
即：设 $P1$ 为满足 $u$ 是 $u \to v$ 上编号最小的点对数量，$P2$ 为满足 $v$ 是 $u \to v$ 上编号最大的点对数量，$P3$ 为同时满足前两个条件的点对数量。\
则显然答案为：$P1 + P2 - 2 \times P3$。

考虑建立两棵点权 Kruskal 重构树，一棵大根一棵小根。那么对于 $P1,P2$，答案是好算的，即每个点在两棵树中的子树大小之和减去它本身 $2$ 的贡献。\
对于 $P3$，其实就是在两棵树中计算**有祖孙关系**并且**祖孙关系相反**的点对数量。\
这个可以用树状数组维护，是简单的。
于是就做完了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 15, M = N << 1;
int n, m;
vector<int> son[N];

int p[N];
int find(int x) { return (p[x] == x) ? x : p[x] = find(p[x]); }

struct BIT {
    int tr[N];
    void add(int x, int d) { for ( ; x < N; x += x & -x) tr[x] += d; }
    int ask(int x) {
        int res = 0;
        for ( ; x ; x -= x & -x) res += tr[x];
        return res;
    }
    int query(int l, int r) { return ask(r) - ask(l - 1); }
} tr;

struct Tree {
    int h[N], e[M], ne[M], idx;
    void init() { memset(h, -1, sizeof h); idx = 0, tot = 0; }
    void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }
    
    int dfn[N], dep[N], sz[N], tot;
    void dfs(int u, int father) {
        sz[u] = 1, dfn[u] = ++tot, dep[u] = dep[father] + 1;
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (v == father) continue;
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
} mn, mx;

long long ans = 0, res = 0;
void dfs(int u, int father) {
    res += tr.query(mx.dfn[u], mx.dfn[u] + mx.sz[u] - 1);
    tr.add(mx.dfn[u], 1);
    for (int i = mn.h[u]; ~i; i = mn.ne[i]) {
        int v = mn.e[i];
        if (v == father) continue;
        dfs(v, u);
    }
    tr.add(mx.dfn[u], -1);
}

int main() {
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        son[u].push_back(v);
        son[v].push_back(u);
    }
    mn.init(), mx.init();

    for (int i = 1; i <= n; i++) p[i] = i;
    for (int u = 1; u <= n; u++)
        for (int v : son[u]) if (v < u) {
            int fv = find(v);
            mx.add(u, fv), mx.add(fv, u);
            p[fv] = u;
        }
    
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int u = n; u >= 1; u--)
        for (int v : son[u]) if (v > u) {
            int fv = find(v);
            mn.add(u, fv), mn.add(fv, u);
            p[fv] = u;
        }
    mn.dfs(1, 0), mx.dfs(n, 0);
    for (int i = 1; i <= n; i++) ans += mn.sz[i] + mx.sz[i] - 2;
    dfs(1, 0), ans -= 2 * res;
    printf("%lld\n", ans);
    scanf("%d", &m);
    while (m--) {
        int x; scanf("%d", &x);
        ans += n - mn.dep[x];
        ++n, mn.dep[n] = mn.dep[x] + 1;
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：Mashu77 (赞：1)

题意：有一个由 $n$ 个顶点和 $n−1$ 条边组成的树。顶点的编号从 $1$ 到 $n$。

如果以下两种说法中恰有一种是正确的，则一对顶点  $(u,v)(u＜v)$ 被认为是可爱的：

$u$ 是路径 $(u,v)$ 上所有顶点中编号最小的顶点。

$v$ 是路径 $(u,v)$ 上所有顶点中编号最大的顶点。

将有 $m$ 个操作。在第 $j$ 个操作中，他决定一个整数 $k_j$，然后插入一个编号为 $n+j$ 的顶点到树，与编号为 $k_j$ 的顶点连接。

请计算每次操作前和操作后可爱的顶点对数量。

题解：求最大值的树 T1 + 求最小值的树 T2 + 树状数组，T1，T2 中只保存节点的儿子。

```cpp
#include "stdafx.h"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#include <vector>


using namespace std;
typedef long long LL;
const int N = 200005;

// 求最大值的树 + 求最小值的树 + 树状数组
int c[N];
int sum(int x) {
    int res = 0;
    while (x) {
        res += c[x];
        x -= x & -x;
    }
    return res;
}
void add(int x, int d, int n = 200000) {
    while (x <= n) {
        c[x] += d;
        x += x & -x;
    }
}

vector<int> G[N], T1[N], T2[N];
int p[N];
int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

int d[N], lo[N], ro[N], ck;
LL ans = 0;
// T1 是求最大值的树，
void dfs1(int u, int fa) {
    lo[u] = ++ck;// u为根的树的起始编号
    d[u] = d[fa] + 1;
	cout<<"u="<<u<<",d[u]="<<d[u]<<endl;
    ans += d[u] - 1;//  d[u] - 1 为u是其中一个端点路径的个数，路径的另外一端取最大值
    for (auto v : T1[u]) dfs1(v, u); // T1中只保存节点的儿子
    ro[u] = ck;// u为根的树的终止编号
}
 // T2 是求最小值的树
void dfs2(int u, int fa) {
    d[u] = d[fa] + 1;
	cout<<"..u="<<u<<",d[u]="<<d[u]<<endl;
    ans += d[u] - 1;//  d[u] - 1 为u是其中一个端点路径的个数，路径的另外一端取最小值

    ans -= 2 * (sum(ro[u]) - sum(lo[u] - 1));  // 在T2中u的祖先和在T1中u的子孙的交集大小
	//if(sum(ro[u]) - sum(lo[u] - 1))
			cout<<"..u="<<u<<",ro[u]="<<ro[u]<<",lo[u]="<<lo[u]<<", sum(ro[u]) - sum(lo[u] - 1)="<<sum(ro[u]) - sum(lo[u] - 1)<<endl;
    add(lo[u], 1);
    for (auto v : T2[u])  dfs2(v, u);// T2中只保存节点的儿子

    add(lo[u], -1);
}
int main() {

	FILE *fi;
	freopen_s(&fi,"CF1797Fin.txt","r",stdin);

    int n, m;
    scanf_s("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf_s("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 2; i <= n; i++) {
        for (auto j : G[i]) {
            if (j < i) {
				// T1 是求最大值的树，结果为i是find(j)的父亲
                T1[i].push_back(find(j));
					cout<<"j="<<j<<",find(j)="<<find(j)<<",i="<<i<<endl;
				p[find(j)] = i; // i是find(j)的父亲
            }
        }
    }

    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = n-1; i >= 1; i--) {
        for (auto j : G[i]) {
			// T2 是求最小值的树，结果为i是find(j)的父亲
            if (j > i) {
                T2[i].push_back(find(j));
					cout<<"..j="<<j<<",find(j)="<<find(j)<<",i="<<i<<endl;
                p[find(j)] = i;// i是find(j)的父亲
            }
        }
    }
    dfs1(n, 0);//  T1 是求最大值的树，n 为根节点
	dfs2(1, 0);//  T2 是求最小值的树，1 为根节点
    printf("%lld\n", ans);
    scanf_s("%d", &m);
    while (m--) {
        int x;
        scanf_s("%d", &x);
        d[++n] = d[x] + 1;
        // 此时的n+1是最大的，
		//  d[u] - 1 为u是其中一个端点路径的个数，路径的另外一端取最小值
		//  所以 d[n+1] = d[x] + 1; 其中路径[n+1,x],路径的另外一端x取最小值
		//  增加了n个路径，其中增加的有效路径(可爱的顶点对)个数：n-(d[n+1]-1)=n+1-d[n+1]
        ans += n - d[n];
        printf("%lld\n",ans);
    }
    return 0;
}

---

