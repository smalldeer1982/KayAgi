# Graph and Queries

## 题目描述

You are given an undirected graph consisting of $ n $ vertices and $ m $ edges. Initially there is a single integer written on every vertex: the vertex $ i $ has $ p_i $ written on it. All $ p_i $ are distinct integers from $ 1 $ to $ n $ .

You have to process $ q $ queries of two types:

- $ 1 $ $ v $ — among all vertices reachable from the vertex $ v $ using the edges of the graph (including the vertex $ v $ itself), find a vertex $ u $ with the largest number $ p_u $ written on it, print $ p_u $ and replace $ p_u $ with $ 0 $ ;
- $ 2 $ $ i $ — delete the $ i $ -th edge from the graph.

Note that, in a query of the first type, it is possible that all vertices reachable from $ v $ have $ 0 $ written on them. In this case, $ u $ is not explicitly defined, but since the selection of $ u $ does not affect anything, you can choose any vertex reachable from $ v $ and print its value (which is $ 0 $ ).

## 样例 #1

### 输入

```
5 4 6
1 2 5 4 3
1 2
2 3
1 3
4 5
1 1
2 1
2 3
1 1
1 2
1 2```

### 输出

```
5
1
2
0```

# 题解

## 作者：duyi (赞：22)


[来我的博客看看吧](https://www.cnblogs.com/dysyn1314/p/13753738.html)

# CF1416D Graph and Queries

## 题目大意

[题目链接](https://codeforces.com/contest/1416/problem/D)

给你一张 $n$ 个点 $m$ 条边的无向图。点有点权，每个点的点权 $p_i$ 是 $1$ 到 $n$ 的正整数且互不相同。

依次进行 $q$ 次操作，每次操作是如下两种之一：

- $1\ v$：查询 $v$ 在图上能到达的所有节点里（包括 $v$ 自己），$p_u$ 最大的点 $u$。输出 $p_u$。并将 $p_u$ 置为 $0$。
- $2\ i$：删除第 $i$ 条边。

特别地，当所有 $v$ 能到达的点点权都为 $0$ 时，$u$ 是未定义的。但此时选任意一个节点作为 $u$ 答案都是 $0$，所以你只需要输出 $0$ 即可。

数据范围：$1\leq n\leq 2\cdot10^5$，$1\leq m\leq 3\cdot 10^5$，$1\leq q\leq 5\cdot10^5$。

## 本题题解

不会删边。所以考虑离线，按时间**倒序**进行操作，**删边变成加边**。

但是遇到的麻烦是，操作 $1$ 是正序进行的，如果我们倒序操作，就不知道当前哪些点 $p_u = 0$ 了。

解决方法是，先倒序遍历一遍所有操作，按“加边”的顺序，建出**重构树**。重构树优美的性质是，对任意一个节点 $v$，在某个时刻之前和它连通的节点，恰好是重构树上 $v$ 的某个祖先的子树。并且我们可以通过树上倍增，在 $O(\log n)$ 的时间内找到这个祖先。

建出重构树后，我们回到正向的时间线。按正序处理所有询问（操作 $1$）。前面说过，在某个时刻和 $v$ 连通的节点，是 $v$ 某个祖先的子树。先倍增找到这个祖先。它的子树是 dfs 序上连续的一段。我们预处理出重构树的 dfs 序，那么问题转化为求区间最大值，支持单点修改。可以用线段树维护。

时间复杂度 $O((n+m+q)\log n)$。

## 总结

~~因为 LCT 是垃圾，所以我们不考虑它~~。那么对于删边操作，其实我们能使用的手段是很有限的。

例如，一个经典的思路是把询问分块。只维护进入本块之前的连通性，对本块内的贡献暴力计算。不过我顺着此思路思考本题并没有得到很好的结果。

另一个思路就是倒序、删边变加边了。但是本题的特殊之处在于，它的另一种操作（操作 $1$）强烈依赖正序的时间线。所以我们不是简单的倒序操作，而是先**倒序预处理出一个数据结构**，然后用这个数据结构来正序地操作和回答询问。

顺便扯一句，这道题让我想到了最近热映的一部电影：《信条》，讲的就是一条正序时间线、一条倒序时间线，交织在一起，发生的事情。而本题里的“重构树”这个工具，就好像是《信条》里未来人传送给现代人的“逆向武器”和“算法”。

## 参考代码

实际提交时，建议加上读入优化，详见本博客公告。

```cpp
// problem: CF1416D
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
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 2e5, MAXM = 3e5, MAXQ = 5e5;
const int LOG = 18;

int n, m, q, val[MAXN + 5];
bool init_in_map[MAXM + 5];
struct Edge_t {
	int u, v;
};
struct Query_t {
	int op, x;
};

Edge_t edges[MAXM + 5], edges_sorted[MAXM + 5];
Query_t queries[MAXQ + 5];
int cnt_e, tim[MAXQ + 5];

int fa[MAXN * 2 + 5], cnt_node;
inline int get_fa(int u) { return (u == fa[u]) ? u : (fa[u] = get_fa(fa[u])); }
inline int new_node() {
	++cnt_node;
	fa[cnt_node] = cnt_node;
	return cnt_node;
}

struct EDGE { int nxt, to; } edge[MAXN * 2 + 5];
int head[MAXN * 2 + 5], tot;
inline void add_edge(int u, int v) { edge[++tot].nxt = head[u]; edge[tot].to = v; head[u] = tot; }

int node_tim[MAXN * 2 + 5]; // 树上这个节点代表的加边时间
int dfn[MAXN + 5], rev[MAXN + 5], min_dfn[MAXN * 2 + 5], max_dfn[MAXN * 2 + 5], cnt_dfn;
int anc[MAXN * 2 + 5][LOG + 1];

void dfs(int u) {
	for(int i = 1; i <= LOG; ++i) {
		anc[u][i] = anc[anc[u][i - 1]][i - 1];
	}
	bool is_leaf = 1;
	min_dfn[u] = n * 2;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		is_leaf = 0;
		anc[v][0] = u;
		dfs(v);
		ckmin(min_dfn[u], min_dfn[v]);
		ckmax(max_dfn[u], max_dfn[v]);
	}
	if(is_leaf) {
		++cnt_dfn;
		min_dfn[u] = max_dfn[u] = dfn[u] = cnt_dfn;
		rev[cnt_dfn] = u;
	}
}
int get_anc(int u, int t) {
	// u 的最高的 node_tim <= t 的祖先
	int v = u;
	for(int i = LOG; i >= 0; --i) {
		if(anc[v][i] && node_tim[anc[v][i]] <= t) {
			v = anc[v][i];
		}
	}
	return v;
}

struct SegmentTree {
	int mx[MAXN * 4 + 5], mx_pos[MAXN * 4 + 5];
	void push_up(int p) {
		if(mx[p << 1] > mx[p << 1 | 1]) {
			mx[p] = mx[p << 1];
			mx_pos[p] = mx_pos[p << 1];
		} else {
			mx[p] = mx[p << 1 | 1];
			mx_pos[p] = mx_pos[p << 1 | 1];
		}
	}
	void build(int p, int l, int r) {
		if(l == r) {
			mx[p] = val[rev[l]];
			mx_pos[p] = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		push_up(p);
	}
	void point_modify(int p, int l, int r, int pos) {
		if(l == r) {
			mx[p] = 0;
			return;
		}
		int mid = (l + r) >> 1;
		if(pos <= mid) {
			point_modify(p << 1, l, mid, pos);
		} else {
			point_modify(p << 1 | 1, mid + 1, r, pos);
		}
		push_up(p);
	}
	pii query(int p, int l, int r, int ql, int qr) {
		if(ql <= l && qr >= r) {
			return make_pair(mx[p], mx_pos[p]);
		}
		int mid = (l + r) >> 1;
		pii res = mk(0, 0);
		if(ql <= mid) {
			res = query(p << 1, l, mid, ql, qr);
		}
		if(qr > mid) {
			ckmax(res, query(p << 1 | 1, mid + 1, r, ql, qr));
		}
		return res;
	}
	SegmentTree() {}
}SegT;

int main() {
	cin >> n >> m >> q;
	for(int i = 1; i <= n; ++i) {
		cin >> val[i];
	}
	for(int i = 1; i <= m; ++i) {
		cin >> edges[i].u >> edges[i].v;
		init_in_map[i] = 1;
	}
	for(int i = 1; i <= q; ++i) {
		cin >> queries[i].op >> queries[i].x;
		if(queries[i].op == 2) {
			assert(init_in_map[queries[i].x] == 1);
			init_in_map[queries[i].x] = 0;
		}
	}
	for(int i = 1; i <= m; ++i) {
		if(init_in_map[i]) {
			++cnt_e;
			edges_sorted[cnt_e] = edges[i];
		}
	}
	for(int i = q; i >= 1; --i) {
		if(queries[i].op == 2) {
			++cnt_e;
			edges_sorted[cnt_e] = edges[queries[i].x];
		} else {
			tim[i] = cnt_e;
		}
	}
	
	assert(cnt_e == m);
	for(int i = 1; i <= n; ++i) {
		new_node();
	}
	for(int i = 1; i <= m; ++i) {
		int u = get_fa(edges_sorted[i].u);
		int v = get_fa(edges_sorted[i].v);
		if(u != v) {
			int par = new_node();
			fa[u] = fa[v] = par;
			node_tim[par] = i;
			add_edge(par, u);
			add_edge(par, v);
		}
	}
	for(int i = 1; i <= cnt_node; ++i) {
		if(get_fa(i) == i) {
			dfs(i);
		}
	}
	assert(cnt_dfn == n);
	SegT.build(1, 1, n);
	for(int i = 1; i <= q; ++i) {
		if(queries[i].op == 1) {
			int u = queries[i].x;
			int v = get_anc(u, tim[i]);
			
			pii qres = SegT.query(1, 1, n, min_dfn[v], max_dfn[v]);
			cout << qres.fi << endl;
			if(qres.fi) {
				SegT.point_modify(1, 1, n, qres.se);
			}
		}
	}
	return 0;
}
```


---

## 作者：gyh20 (赞：14)

一个神奇的解法，十分好写！！！

首先，如果这条边不会影响图的连通性，那么不会造成影响，可以先从后往前找到树边。

当断掉一条树边时，整个图会变为两个连通块，此时类比启发式合并，我们倒过来做启发式合并的过程，对于分成的两个连通块，可以暴力把小的一个从大的一个删除，用两个 priority_queue 即可。

这样的复杂度有两个 $\log$ ，过不去。

考虑优化掉堆的 $\log$。

我们把堆改成 vector，在里面存下所有的连通块内的值，初始我们令整个 vector 有序，之后我们对于每个点打上属于某一个连通块的标记，相当于在之前的块中删除，这样就可以类似两个优先队列支持删除。

这样就是 $n\log n$ 的。

具体代码可以见 Fee_cle6418 的实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Query{
	int opt,x,rx,ry;
}q[500005];
int n,m,Q,fa[200005],ex[300005],ey[300005],del[300005],sz[300005],bel[200005],a[200005],used[200005];
vector<int> h[200005];
int gf(int x){
	return fa[x]==x?x:gf(fa[x]);
}
int Query(int x){
	while(h[x].size()&&(bel[h[x].back()]!=x||used[h[x].back()]))h[x].pop_back();
	if(!h[x].size())return 0;
	int r=h[x].back();
	return h[x].pop_back(),used[r]=1,r;
}
int main() {
	scanf("%d%d%d",&n,&m,&Q);
	for(int i=1,x;i<=n;i++)scanf("%d",&x),h[fa[i]=i].push_back(a[i]=x),sz[i]=1;
	for(int i=1;i<=m;i++)scanf("%d%d",&ex[i],&ey[i]);
	for(int i=1;i<=Q;i++){
		scanf("%d%d",&q[i].opt,&q[i].x);
		if(q[i].opt==2)del[q[i].x]=1;
	}
	for(int i=1;i<=m;i++){
		if(del[i])continue;
		int x=gf(ex[i]),y=gf(ey[i]);
		if(x==y)continue;
		if(sz[x]>sz[y])swap(x,y);
		for(int j:h[x])h[y].push_back(j);
		fa[x]=y,sz[y]+=sz[x];
	}
	for(int i=Q;i>=1;i--){
		int x=ex[q[i].x],y=ey[q[i].x];
		if(q[i].opt==1||gf(x)==gf(y))continue;
		x=gf(x),y=gf(y);
		if(sz[x]>sz[y])swap(x,y);
		q[i].rx=x,q[i].ry=y,fa[x]=y,sz[y]+=sz[x];
		for(int j:h[x])h[y].push_back(j);
	}
	for(int i=1;i<=n;i++)sort(h[i].begin(),h[i].end()),bel[a[i]]=gf(i);
	for(int i=1,u;i<=Q;i++){
		if(q[i].opt==1)printf("%d\n",u=Query(gf(q[i].x)));
		else if(q[i].rx){
			for(int j:h[q[i].rx])bel[j]=q[i].rx;
			fa[q[i].rx]=q[i].rx;
		}
	}
	return 0;
}
```


---

## 作者：ez_lcw (赞：9)

带删除维护最大值显然不好做，所以考虑先把最后的图建出来，再从后往前加边。

但是询问中还带修改（让 $p_u=0$），这样会影响后面的询问，所以也不能加边时就得到答案。

这里给出一种十分简单易懂的做法：

在从后往前枚举操作的时候：

1. 如果是加边 $(u,v)$ 且 $u$ 和 $v$ 不连通（设它们所在连通块的根分别为 $a$、$b$），我们就新建一个虚点连向 $a$、$b$，并且把这个虚点作为 $a$、$b$ 的父亲。

2. 如果是询问 $x$，也就是询问当前 $x$ 所在连通块内的最大值，我们就记录一下当前 $x$ 所在连通块的根。

建好新图后，我们再从前往后扫每一个询问。对于一个询问，我们直接查询我们对这个询问记录的根的子树内的最大值，然后把它置零。这些操作具体可以用 dfn 序线段树维护。

其实这个做法的巧妙之处就在于设置了一个虚点，这个虚点起到了一个类似可持久化记录和区分版本的作用。

代码如下：

```cpp
#include<bits/stdc++.h>
#include<iostream>

#define N 200010
#define M 300010
#define K 500010

using namespace std;

struct Edge
{
	int u,v;
}e[M];

struct Query
{
	int opt,x;
}q[K];

struct data
{
	int v,id;
	data(){v=-1*1*1*1;}
	data(int a,int b){v=a,id=b;}
}maxn[(N+K)<<2];

bool operator < (data a,data b)
{
	return a.v<b.v;
}

int n,m,Q,v[N+K],fa[N+K];
int cnt,head[N+K],to[N+K],nxt[N+K];
int node,idx,dfn[N+K],rk[N+K],size[N+K];
bool del[M],vis[N+K];

int find(int x)
{
	return x==fa[x]?x:(fa[x]=find(fa[x]));
}

void adde(int u,int v)
{
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}

void dfs(int u)
{
	dfn[u]=++idx;
	rk[idx]=u;
	size[u]=1;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		dfs(v);
		size[u]+=size[v];
	}
}

void up(int k)
{
	maxn[k]=max(maxn[k<<1],maxn[k<<1|1]);
}

void build(int k,int l,int r)
{
	if(l==r)
	{
		maxn[k]=data(v[rk[l]],l);
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	up(k);
}

data query(int k,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return maxn[k];
	int mid=(l+r)>>1;
	data ans;
	if(ql<=mid) ans=max(ans,query(k<<1,l,mid,ql,qr));
	if(qr>mid) ans=max(ans,query(k<<1|1,mid+1,r,ql,qr));
	return ans;
}

void update(int k,int l,int r,int x)
{
	if(l==r)
	{
		maxn[k].v=0;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) update(k<<1,l,mid,x);
	else update(k<<1|1,mid+1,r,x);
	up(k);
}

int main()
{
	scanf("%d%d%d",&n,&m,&Q);
	node=n;
	for(int i=1;i<=n;i++) 
		scanf("%d",&v[i]);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&e[i].u,&e[i].v);
	for(int i=1;i<=Q;i++)
	{
		scanf("%d%d",&q[i].opt,&q[i].x);
		if(q[i].opt==2) del[q[i].x]=1;
	}
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		if(!del[i])
		{
			int a=find(e[i].u),b=find(e[i].v);
			if(a!=b)
			{
				fa[b]=a;
				adde(a,b);
			}
		}
	}
	for(int i=Q;i>=1;i--)
	{
		if(q[i].opt==1) q[i].x=find(q[i].x);
		else
		{
			int a=find(e[q[i].x].u),b=find(e[q[i].x].v);
			if(a!=b)
			{
				++node;//新建虚点
				fa[a]=fa[b]=fa[node]=node;
				adde(node,a),adde(node,b);
			}
		}
	}
	for(int i=1;i<=node;i++)
	{
		int a=find(i);
		if(!vis[a])
		{
			vis[a]=true;
			dfs(a);
		}
	}
	build(1,1,node);
	for(int i=1;i<=Q;i++)
	{
		if(q[i].opt==1)
		{
			data ans=query(1,1,node,dfn[q[i].x],dfn[q[i].x]+size[q[i].x]-1);
			printf("%d\n",ans.v);
			update(1,1,node,ans.id);
		}
	}
	return 0;
}
```

---

## 作者：YLWang (赞：8)

重构树。

看到删边操作马上倒过来变成加边。但发现我们不好处理出每个联通块包含哪些点。

于是我们就可以考虑把他放到重构树上。具体地，每次 merge 都新建一个点 $p$，将 $f_{u}$ 与 $f_{v}$ 均设为 $p$，并在重构树上将 $p$ 的儿子设为 $u$ 和 $v$。

那么一次操作在重构树上就是一个子树操作。随便整棵线段树维护维护就行。

提交记录：https://codeforces.com/contest/1416/submission/94040207

C++11 有个 feature 就是你在结构体里头开一个很大的数组会 CTLE。解决方案是加一个空构造函数。

---

## 作者：Time_tears (赞：5)

可以用一个很新颖的算法。启发式分裂！！！

首先我们可以注意到图的限制是很强的，我们不妨处理一下把图变成树，至于怎么变嘛，就是倒着扫一边用并查集把有用的边存起来。

对于每一条要删的边，若他不是树边，那就不管了，否则我们可以把这条边在树上删掉，而这样的话复杂度无法保证，这时就要用到 “启发式分裂” 了。

我们考虑先把点按点权排序，先直接按 vector 存，对于每次删边操作，我们就暴力把 $siz$ 小的联通块给暴力提出来，这样的话复杂度就可以做到 $(n \log n) $ 了。

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<cstdio>
#include<vector>
#include<algorithm>
#define ll long long
#define N 300005
using namespace std;
struct Query {
	int opt,x,xx,yy;
} q[N<<1];
int n,m,Q,fa[N],ex[N],ey[N],dd[N],sz[N],bb[N],a[N],ud[N];
vector<int> hah[N];
inline int read() {
	int s=0,f=0;
	char ch=getchar();
	while(ch<48||ch>57)f=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58)s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
int Getprt(int x) {
	return fa[x]==x?x:Getprt(fa[x]);
}
int Query(int x) {
	while(hah[x].size()&&(bb[hah[x].back()]!=x||ud[hah[x].back()]))hah[x].pop_back();
	if(!hah[x].size())return 0;
	int ans=hah[x].back();
	return hah[x].pop_back(),ud[ans]=1,ans;
}
int main() {
	n=read(),m=read(),Q=read();
	for(int i=1; i<=n; i++)hah[fa[i]=i].push_back(a[i]=read()),sz[i]=1;
	for(int i=1; i<=m; i++)ex[i]=read(),ey[i]=read();
	for(int i=1; i<=Q; i++) {
		q[i].opt=read(),q[i].x=read();
		if(q[i].opt==2)dd[q[i].x]=1;
	}
	for(int i=1,x,y; i<=m; i++)
		if(!dd[i]&&(x=Getprt(ex[i]))!=(y=Getprt(ey[i]))) {
			((sz[x]>sz[y])?x^=y^=x^=y:0),fa[x]=y,sz[y]+=sz[x];
			for(int j=0; j<hah[x].size(); ++j)hah[y].push_back(hah[x][j]);
		}
	for(int i=Q,x,y; i>=1; i--)
		if(q[i].opt==2&&(x=Getprt(ex[q[i].x]))!=(y=Getprt(ey[q[i].x]))) {
			((sz[x]>sz[y])?x^=y^=x^=y:0),q[i].xx=x,q[i].yy=y,fa[x]=y,sz[y]+=sz[x];
			for(int j=0; j<hah[x].size(); ++j)hah[y].push_back(hah[x][j]);
		}
	for(int i=1; i<=n; i++)sort(hah[i].begin(),hah[i].end()),bb[a[i]]=Getprt(i);
	for(int i=1,u; i<=Q; i++)
		if(q[i].opt==1)printf("%d\n",u=Query(Getprt(q[i].x)));
		else if(q[i].xx) {
			for(int j=0; j<hah[q[i].xx].size(); ++j)bb[hah[q[i].xx][j]]=q[i].xx;
			fa[q[i].xx]=q[i].xx;
		}
	return 0;
}
```


---

## 作者：ZCETHAN (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF1416D)
## 题目大意
给一张图，有两种操作。
1. 查询与一个点 $v$ 联通的点中权值的最大值。输出后最大值赋为 $0$。
2. 删去一条边。

## Solution
感觉题解区用倒着加边做的人比较多，我这里给出一种比较正向的做法。

首先我摊牌了，我是为了练习克鲁斯卡尔重构树而做的，因此我拿到题我就往着上面想了。

还是一样的套路，考虑边的优劣性。由于我们希望图尽可能联通，所以在重构树的时候，要选择一条最晚被断开的路径才不会影响正确性。于是我们考虑这个只删不增的特性，先离线所有询问，这样我们就可以得到每一条边在图中存在的最晚时刻。容易证明，关于这个做最小生成树的结果正确的。

所以很显然的，构建克鲁斯卡尔重构树，然后向上找到最后一个最晚时刻小于当前时刻的，那么该节点子树中的所有叶节点，就是所有与 $v$ 联通的点。

接下来解决每次询问后把最值赋值为 $0$ 的限制。这时候我们掏出一个线段树，哦对了题目中保证权值是 $1\sim n$ 的一个排列，所以一个权值唯一对应一个节点，因此我们可以很方便的维护把最大值赋值为 $0$ 的操作，然后用线段树来做动态的区间最值就可以了。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf (1<<30)
#define INF (1ll<<60)
using namespace std;
const int MAXN=5e5+10;
struct Tree{int l,r,mx;}tr[MAXN<<2];
#define ls i<<1
#define rs i<<1|1
void pushup(int i){tr[i].mx=max(tr[ls].mx,tr[rs].mx);}
void build(int i,int l,int r){
	tr[i].l=l;tr[i].r=r;tr[i].mx=0;
	if(l==r) return;int mid=l+r>>1;
	build(ls,l,mid);build(rs,mid+1,r);
}
void upd(int i,int x,int v){
	if(tr[i].l==x&&tr[i].r==x){
		tr[i].mx=v;return;
	}int mid=tr[i].l+tr[i].r>>1;
	if(x<=mid) upd(ls,x,v);
	else upd(rs,x,v);
	pushup(i);
}
int ask(int i,int l,int r){
	if(tr[i].l>=l&&tr[i].r<=r) return tr[i].mx;
	int mid=tr[i].l+tr[i].r>>1;
	if(r<=mid) return ask(ls,l,r);
	else if(l>mid) return ask(rs,l,r);
	else return max(ask(ls,l,mid),ask(rs,mid+1,r));	
}//segment tree
struct Edge{
	int u,v,w;
	void input(){
		scanf("%d%d",&u,&v);
		w=inf;
	}bool friend operator<(Edge a,Edge b){
		return a.w>b.w;
	}
}E[MAXN];
struct Query{
	int opt,v;
	void input(int i){
		scanf("%d%d",&opt,&v);
		if(opt==2) E[v].w=i;
	}
}q[MAXN];
int p[MAXN],f[MAXN],TL[MAXN],mp[MAXN];
//TL 表示边的最晚存在时刻，mp[i] 表示权值为 i 的点编号
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
vector<int> e[MAXN];
int fa[MAXN][20],lb[MAXN],rb[MAXN],tot;
void dfs(int x,int fat){
	fa[x][0]=fat;
	for(int i=1;i<20;i++)
		fa[x][i]=fa[fa[x][i-1]][i-1];
	lb[x]=tot;
	if(!e[x].size()){
		lb[x]=tot;rb[x]=++tot;
		upd(1,tot,p[x]);return;
	}
	for(int i=0;i<e[x].size();i++)
		dfs(e[x][i],x);
	rb[x]=tot;
}
int main()
{
	int n,m,Q;
	scanf("%d%d%d",&n,&m,&Q);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]),mp[p[i]]=i;
	for(int i=1;i<=m;i++) E[i].input();
	for(int i=1;i<=Q;i++) q[i].input(i);
	for(int i=1;i<=n+m;i++) f[i]=i;
	sort(E+1,E+1+m);
	int cnt=n;
	for(int i=1;i<=m;i++){
		int fx=find(E[i].u),fy=find(E[i].v);
		if(fx==fy) continue;
		f[fx]=f[fy]=++cnt;
		e[cnt].push_back(fx);
		e[cnt].push_back(fy);
		TL[cnt]=E[i].w;
	}build(1,1,n);
	for(int i=1;i<=cnt;i++)
		if(find(i)==i)
			dfs(i,0);
	TL[0]=0;
	for(int i=1;i<=Q;i++){
		int op=q[i].opt,x=q[i].v;
		if(op==1){
			for(int j=19;j>=0;j--)
				if(TL[fa[x][j]]>=i&&fa[x][j])
					x=fa[x][j];
			int ans=ask(1,lb[x]+1,rb[x]);
			if(ans) upd(1,rb[mp[ans]],0);//这里最好判一下 ans==0，不然会 WA on test 5
			//哦你问我怎么知道的，你说呢
			//不过 build 的时候从 0 开始建大概就不用判了
			printf("%d\n",ans);
		}
	}
}
```
## End

---

## 作者：苏联小渣 (赞：3)

考虑按照时间顺序，把删去的边赋一个单调递增的权值 $1,2,...,T$，到最后为止还没有删去的边就赋值为 $T+1$。此时，操作 $1$ 就转化为了，设当前删去的边最大权值为 $x$，求出如果只保留权值 $>x$ 的边，从 $v$ 出发能到达的最大 $p_u$ 的点， 并把 $p_u$ 赋为 $0$。

---

如果不要求将 $p_u$ 赋值为 $0$，那么这个问题就变成了一个经典问题：如果只保留权值 $>x$ 的边，从 $v$ 出发能到达的最大 $p_u$。

对于这个问题，我们有两种处理方式（第一种方式实际上与本题无关，可以跳过）。第一种是离线，将所有边按照边权从大到小排序，再将询问按 $x$ 从大到小排序。对于每组询问 $(v,x)$，我们把所有边权 $>x$ 的边用并查集合并，再维护每个连通块的 max 即可。

第二种是 Kruskal 重构树。同样的，将所有边按照边权从大到小排序，构建 Kruskal 重构树，对于两个点 $x,y$，如果它们未联通，就新建一个点 $u$ 连接 $x,y$ 所在的子树的顶部结点，赋点权为 $x,y$ 之间的边权。对于询问 $(v,x)$，由于叶子结点的祖先的权值单调递减，所以我们倍增出最后一个满足权值 $>x$ 的结点 $t$，那么 $t$ 子树内所有结点都是此时 $v$ 可达的。所以，我们只需要找到 $t$ 子树的叶子结点权值的 max 即可。

---

考虑原问题。发现原问题应该是不弱于上述问题的，所以我们考虑从上述两种方法中挑选。第一种离线处理已经改变了操作的顺序了，所以肯定不行。而第二种如果权值给定的话，是可以做到在线修改、在线查询的，所以我们考虑用 Kruskal 重构树做。

延续上面第二种方法，当我们找到 $t$ 子树的 max 之后，由于叶子结点的点权是个排列，所以这个 $p_u$ 对应的 $u$ 也就可以求出来了。此时，我们需要把 $p_u$ 修改为 $0$。我们按照 dfs 的先后顺序把叶子结点赋上编号 $1,2,...,n$，那么一个子树的叶子结点的编号就是连续的，设为 $l_{t},r_{t}$，这个可以通过 dfs 预处理出来。问题就变成了，区间查询最大值及其位置，单点修改，用线段树维护即可。

注意如果区间最大值已经是 $0$ 了，那么就不用修改了。

另外，这个题有一个非常大的坑点，就是图不一定联通，也就是说，我们求出重构树可能是组成一个森林，那么注意把所有根节点都搜到即可。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define lc(x) x<<1
#define rc(x) x<<1|1
int n, m, q, p, x, tot, cnt, now, a[200010], pos[200010], f[200010], val[400010], tp[400010], h[400010], vis[400010];
int F[400010][19], id[200010], L[400010], R[400010], seg[800010];
struct edge{
	int x, y, id;
	bool operator < (const edge &A) const{
		return id > A.id;
	}
}b[300010];
struct operation{
	int op, x;
}c[500010];
struct node{
	int x, y, next;
}d[400010];
void add(int x, int y){
	d[++p].y = y, d[p].next = h[x], h[x] = p;
}
int find(int x){
	if (x != f[x]) return f[x] = find(f[x]);
	return f[x];
}
void pushup(int k){
	seg[k] = max(seg[lc(k)], seg[rc(k)]);
}
void modify(int k, int l, int r, int x, int y){
	if (l == r){
		seg[k] = y;
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid) modify(lc(k), l, mid, x, y);
	else modify(rc(k), mid+1, r, x, y);
	pushup(k);
}
int query(int k, int l, int r, int x, int y){
	if (x <= l && r <= y) return seg[k];
	int mid = l + r >> 1, ret = 0;
	if (x <= mid) ret = max(ret, query(lc(k), l, mid, x, y));
	if (y > mid) ret = max(ret, query(rc(k), mid+1, r, x, y));
	return ret;
}
void dfs(int x, int fa){
	vis[x] = 1;
	for (int i=0; i<18; i++){
		F[x][i+1] = F[F[x][i]][i];
	}
	int flag = 0;
	L[x] = 1e9;
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == fa) continue;
		F[y][0] = x;
		flag = 1;
		dfs(y, x);
		L[x] = min(L[x], L[y]);
		R[x] = max(R[x], R[y]);
	}
	if (!flag){
		id[x] = ++id[0];
		L[x] = R[x] = id[x];
		modify(1, 1, n, id[x], a[x]);
	}
}
int main(){
	scanf ("%d%d%d", &n, &m, &q);
	for (int i=1; i<=n; i++){
		scanf ("%d", &a[i]);
		f[i] = tp[i] = i;
		pos[a[i]] = i;
	}
	for (int i=1; i<=m; i++){
		scanf ("%d%d", &b[i].x, &b[i].y);
	}
	for (int i=1; i<=q; i++){
		scanf ("%d%d", &c[i].op, &c[i].x);
		if (c[i].op == 2){
			b[c[i].x].id = ++tot;
		}
	}
	tot ++;
	for (int i=1; i<=m; i++){
		if (!b[i].id) b[i].id = tot;
	}
	sort (b+1, b+m+1);
	cnt = n;
	for (int i=1; i<=m; i++){
		int fx = find(b[i].x), fy = find(b[i].y);
		if (fx != fy){
			f[fy] = fx, cnt ++;
			add(cnt, tp[fx]); add(cnt, tp[fy]);
			tp[fx] = cnt;
			val[cnt] = b[i].id;
		}
	}
	for (int i=cnt; i>=1; i--){
		if (!vis[i]){
			dfs(i, 0);
		}
	}
	for (int i=1; i<=q; i++){
		if (c[i].op == 1){
			x = c[i].x;
			for (int j=18; j>=0; j--){
				if (val[F[x][j]] > now) x = F[x][j]; 
			}
			int mx = query(1, 1, n, L[x], R[x]);
			printf ("%d\n", mx);
			if (mx == 0) continue;
			modify(1, 1, n, id[pos[mx]], 0);
		}
		else{
			now ++;
		}
	}
	return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：3)

\*2600，这DS难度不值这么高（

题解区除了两篇一眼就能看懂的启发式分裂以外，其他的各种重构树都是什么妖魔鬼怪？

本来一眼秒了个启发式分裂，想到了个复杂度又好快又好写的办法，来补一下。

------------

首先，如果不启发式分裂，我们就不好在线的维护块内元素，还是要倒序加边。

然后发现询问的东西虽然是正序，但很能势能分析，所以我们还是考虑正序处理询问。

比较关键的观察是我们只需要询问时的结构，也就是说我们只用知道询问的时候有哪些元素，倒序加边的时候采用可持久化线段树合并可以将版本信息保存下来。

对于可持久化线段树的势能分析自然的想到[套路题hlcpq](https://www.luogu.com.cn/blog/ICANTAKIOI/solution-p7712)，发现这道题真的只是找一个数删一个，没有迭代的过程，复杂度严格弱于 hlcpq。

相较于 hlcpq，我们有一个更简单的分析方法：如果能找到一个点，会花费 $O(\log)$ 的代价回退，否则遍历了可持久化树上一个节点打上标记以后不再遍历。（然后发现其实和 hlcpq 的分析一模一样

于是根据势能分析遍历次数与询问次数（$\times \log$）和可持久化的节点数有关，复杂度 $O(n\log n+q\log n)$。

[代码](https://www.luogu.com.cn/paste/svxyn3md)和 hlcpq 一样短。

---

## 作者：Logey (赞：2)

操作一的意思是求 $u$ 所在连通块中最小的 $p$，然后改成 $0$。

操作二就是删边，并且没有插入操作，也就是说每条边最多只会被删一次，那么可以知道每条边的存在时间。

维护连通性可以求一个生成树，出于贪心的想法肯定是要尽可能先加入存在时间长的边，所以就是最大生成树。

顺着思路想下去的话会想到 $\text{Kruscal}$ 重构树。

查询相当于是找到最浅的存在时间满足条件的点，然后查询子树最小值，单点修改，线段树即可。

还有一个想法是使用 $\text{LCT}$ 维护，应该也是可以的。

```c++
#include <map>
#include <set>
#include <cmath>
#include <ctime> 
#include <queue>
#include <stack>
#include <bitset> 
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

#define fi first
#define se second
#define pb push_back
#define MP std::make_pair
#define PII std::pair<int, int>
#define all(x) (x).begin(), (x).end()
#define CL(a, b) memset(a, b, sizeof a)
#define rep(i, l, r) for (int i = (l); i <= (r); ++ i)
#define per(i, r, l) for (int i = (r); i >= (l); -- i)
#define PE(x, a) for (int x = head[a]; x;x = edge[x].next)

typedef long long ll;

template <class T>
inline void rd(T &x) {
    char c = getchar(), f = 0; x = 0;
    while (!isdigit(c)) f = (c == '-'), c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    x = f ? -x : x;
}

const int MAXN = 1e6 + 7;

int fa[MAXN], dfn[MAXN], sz[MAXN], f[MAXN][22], ans[MAXN], pos[MAXN];
std::vector<int> son[MAXN];
int p[MAXN], n, m, tim[MAXN], q, seq[MAXN], wei[MAXN], tot;
PII E[MAXN], Q[MAXN];

int cmax(int x, int y) {
    return p[x] == p[y] ? (x < y ? x : y) : (p[x] > p[y] ? x : y);
}

struct Node {
    int l, r;
    #define mid (l + (r - l) / 2)
    Node *lc, *rc;
    int max;
    Node(){}
    Node(int l, int r, Node *lc, Node *rc) : l(l), r(r), lc(lc), rc(rc) {}

    static Node *build(int l, int r) {
        Node *ret;
        if (l == r) {
            ret = new Node(l, r, 0, 0);
            ret->max = pos[l];
        }
        else {ret = new Node(l, r, build(l, mid), build(mid + 1, r)); ret->up();}
        return ret;
    }

    void up() {
        max = cmax(lc->max, rc->max);
    }

    void change(int p, int x) {
        if (l == r) {
            ::p[pos[l]] = x;
            max = pos[l];
            return;
        }
        if (p <= mid) lc->change(p, x);
        else rc->change(p, x);
        up();
    }

    int query(int L, int R) {
        if (l == L && r == R) return max;
        if (R <= mid) return lc->query(L, R);
        else if (L > mid) return rc->query(L, R);
        else return cmax(lc->query(L, mid), rc->query(mid + 1, R));
    }
} *root;

bool cmp(int a, int b) {
    return tim[a] > tim[b];
}

inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void dfs(int u) {
    static int ts = 0;
    dfn[u] = ++ts;
    pos[ts] = u;
    sz[u] = 1;
    for (auto v: son[u]) dfs(v), sz[u] += sz[v], f[v][0] = u;
}

int get(int u, int val) {
    per(i, 21, 0) {
        if (f[u][i] && wei[f[u][i]] >= val) u = f[u][i];
    }
    return u;
}

int main() {
    CL(ans, -1);

    rd(n), rd(m), rd(q);
    rep(i, 1, n) rd(p[i]), wei[i] = q + 1;
    rep(i, 1, 2 * n + 5) fa[i] = i;
    rep(i, 1, m) {
        rd(E[i].fi); rd(E[i].se);
        tim[i] = q + 1;
        seq[i] = i;
    }
    rep(i, 1, q) rd(Q[i].fi), rd(Q[i].se);
    rep(i, 1, q) {
        if (Q[i].fi == 2) tim[Q[i].se] = i;
    }

    std::sort(seq + 1, seq + m + 1, cmp);
    tot = n;
    rep(i, 1, m) {
        int u = E[seq[i]].fi, v = E[seq[i]].se, tt = tim[seq[i]];
        if (find(u) == find(v)) continue;
        wei[++tot] = tt;
        u = find(u), v = find(v);
        son[tot].pb(u), son[tot].pb(v);
        fa[u] = fa[v] = tot;
    }
    per(i, tot, 1) if (!dfn[i]) dfs(i);
    root = Node::build(1, tot);
    rep(j, 1, 21) rep(i, 1, tot) f[i][j] = f[f[i][j - 1]][j - 1];
    rep(i, 1, q) {
        if (Q[i].fi == 1) {
            int v = get(Q[i].se, i);
            int tmp = root->query(dfn[v], dfn[v] + sz[v] - 1);
            ans[i] = p[tmp];
            if (ans[i])
            root->change(dfn[tmp], 0);
        }
    }
    rep(i, 1, q) if (ans[i] != -1) printf("%d\n", ans[i]);
    return 0;
}

```

---

## 作者：蒟蒻君HJT (赞：1)

**喜提（接近）洛谷最劣解。但是大概比 Kruskal 重构树好想一点（我太菜了完全想不到）**。

## 一、前置知识：线段树合并 & 分裂


这里我用到了按值域分裂线段树的操作。

## 二、解法

首先从后往前扫询问，用并查集判断一下哪些边删去后一个连通块变成了两个，而其他被删去的边我们直接在接下来的所有操作中忽略。然后对初始时的图（已经删去一些没用的边了）进行 $dfs$，求出搜索树上每个点的 $dfs$ 序和子树大小。

初始时，用线段树维护每个 $dfs$ 序的连续区间上的最大 $p_{dfn_i}$ 和对应的 $dfn_i$。

对于询问：

1.如果是删（有用的）边 $(x,y)$ 操作，假设搜索树上 $x$ 是 $y$ 父结点，那么向上倍增找到 $x$ 当前所在的根节点 $r$，在 $r$ 所代表的线段树上分裂出来 $[1,dfn_y-1]$ 和 $[dfn_y+size_y,n]$ 这两个区间并把它们合并起来归给 $r$，剩余的 $[dfn_y, dfn_y+size_y-1]$ 归给 $y$ 就 ok 了。

2.查询 $x$ 的操作。倍增向上找到最浅的结点（也就是当前 $x$ 所在连通块的根节点），这个可以这样做：每个点维护一个权值 $val$，每次删边 $(x,y)$（$y$ 是父节点）时给 $y$ 子树 $+1$，倍增到 $u$ 时若 $val_u=val_x$ 说明 $u$ 和 $x$ 仍在一个连通块中，是可行的；否则说明不可行。

时间复杂度：$O(q\log^2n)$，瓶颈是倍增求根节点，要快读才能过。空间复杂度：$O(q\log n)$，最好写一个垃圾回收。

## 三、代码

[提交记录](https://codeforces.com/contest/1416/submission/168470086)

---

## 作者：Cry_For_theMoon (赞：0)

感觉倒序加边去考虑反而繁琐。

这题上来，就很像 Kruskal 重构树。我们改改题，改成每条边带个边权，每次给定一个参数 $x$ 和一个点 $u$，在边权 $\le x$ 的图上，$u$ 所在连通块进行修改，这个就是 Kruskal 重构树板子题，只要建出重构树，然后化为子树查询，子树修改，按照 dfs 序维护 segment tree 就可以了。

这题没边权，只有时间，把边权置为它的删除时间，一直存在的边，边权就是 INF，然后就和上面一样，做完了...

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=5e5+10;
int n,m,q,p[MAXN*2],ord[MAXN],a[MAXN],b[MAXN],w[MAXN];
int op[MAXN],u[MAXN],idx[MAXN];
int fa[MAXN],val[MAXN],tot,faa[MAXN];
vector<int>e[MAXN];
int vis[MAXN],dfn[MAXN],orz[MAXN],sz[MAXN],dfntot;
int top[MAXN][20];
bool cmp(int x,int y){return (w[x]!=w[y])?(w[x]>w[y]):(x<y);}
int Find(int x){
    if(fa[x]==x)return x;
    return fa[x]=Find(fa[x]);
}
void dfs(int u){
    vis[u]=1;dfn[u]=++dfntot;sz[u]=1;orz[dfntot]=u;
    rep(i,1,19)top[u][i]=top[top[u][i-1]][i-1];
    for(auto v:e[u]){
        if(v==faa[u])continue;
        top[v][0]=u;
        dfs(v);
        sz[u]+=sz[v];
    }
}
int leap(int u,int lim){
    per(j,19,0){
        if(!top[u][j])continue;
        if(val[top[u][j]]<=lim)continue;
        u=top[u][j];
    }
    return u;
}
struct Seg{
    int maxn[MAXN<<3];
    void pushup(int x){maxn[x]=max(maxn[lc(x)],maxn[rc(x)]);}
    void build(int x,int l,int r){
        if(l==r){maxn[x]=p[orz[l]];return;}
        int mid=(l+r)>>1;build(lc(x),l,mid);build(rc(x),mid+1,r);
        pushup(x);
    }
    void upd(int x,int l,int r,int pos){
        if(l==r){maxn[x]=0;return;}
        int mid=(l+r)>>1;
        if(pos<=mid)upd(lc(x),l,mid,pos);
        else upd(rc(x),mid+1,r,pos);
        pushup(x);
    }
    int qry(int x,int l,int r,int ql,int qr){
        if(ql<=l && qr>=r)return maxn[x];
        int mid=(l+r)>>1,ret=0;
        if(ql<=mid)ret=max(ret,qry(lc(x),l,mid,ql,qr));
        if(qr>mid)ret=max(ret,qry(rc(x),mid+1,r,ql,qr));
        return ret;
    }
}t;
int main(){
    scanf("%d%d%d",&n,&m,&q);
    rep(i,1,n)scanf("%d",&p[i]),ord[p[i]]=i;
    rep(i,1,m){scanf("%d%d",&a[i],&b[i]);idx[i]=i;w[i]=q+1;}
    rep(i,1,q){
        scanf("%d%d",&op[i],&u[i]);
        if(op[i]==2)w[u[i]]=i;
    }
    sort(idx+1,idx+1+m,cmp);
    rep(i,1,n)fa[i]=i;tot=n;
    rep(u,1,m){
        int i=idx[u];
        if(Find(a[i])==Find(b[i]))continue;
        tot++;fa[tot]=tot;val[tot]=w[i];
        faa[Find(a[i])]=faa[Find(b[i])]=tot;
        e[tot].pb(Find(a[i]));
        e[tot].pb(Find(b[i]));
        fa[Find(a[i])]=fa[Find(b[i])]=tot;
    }
    rep(i,1,tot){
        if(faa[i])continue;
        dfs(i);
    }
    t.build(1,1,tot);
    rep(i,1,q){
        if(op[i]==2)continue;
        int p=leap(u[i],i);
        int l=dfn[p],r=dfn[p]+sz[p]-1;
        int val=t.qry(1,1,tot,l,r);
        printf("%d\n",val);
        if(val){
            t.upd(1,1,tot,dfn[ord[val]]);
        }
    }
    return 0;
}
```

---

## 作者：SSerxhs (赞：0)

只有删边操作套路离线变为加边

类似 kruskal 重构树的思路，加边的时候建一个虚点连向两点，则可以把询问挂在某个虚点上，然后按照询问顺序每次找到该虚点子树最大值并删除即可，可以用线段树维护 dfs 序实现

```
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+2,M=3e5+2,Q=5e5+2,O=4e5+2,P=1.6e6+2;
typedef pair<int,int> pa;
typedef long long ll;
int lb[M][2],v[O],f[O],g[Q][2],fv[N],c[O][2],dfn[O],nfd[O],siz[O],l[P],r[P],ys[O],s[P];
int n,cc,i,m,q,tp,cnt,x,y,z,ans;
bool ed[O];
inline void read(int &x)
{
	cc=getchar();
	while ((cc<48)||(cc>57)) cc=getchar();
	x=cc^48;cc=getchar();
	while ((cc>=48)&&(cc<=57))
	{
		x=x*10+(cc^48);
		cc=getchar();
	}
}
inline int getf(register int x)
{
	if (f[x]==x) return x;return f[x]=getf(f[x]);
}
inline void merge(register int x,register int y)
{
	x=getf(x);y=getf(y);
	if (x==y) return;
	c[f[x]=f[y]=++n][0]=x;c[n][1]=y;
}
void dfs(int x)
{
	siz[nfd[dfn[x]=++cnt]=x]=1;
	if (c[x][0])
	{
		dfs(c[x][0]);dfs(c[x][1]);
		siz[x]+=siz[c[x][0]]+siz[c[x][1]];
	}
}
inline void pushup(const int x)
{
	s[x]=max(s[x<<1],s[x<<1|1]);
}
void build(const int x)
{
	if (l[x]==r[x]) return fv[s[x]=v[nfd[l[x]]]]=x,void();
	const int c=x<<1;
	l[c]=l[x];r[c]=l[x]+r[x]>>1;
	l[c|1]=r[c]+1;r[c|1]=r[x];
	build(c);build(c|1);
	pushup(x);
}
inline void sol(int x)
{
	if ((z<=l[x])&&(r[x]<=y)) return ans=max(ans,s[x]),void();
	if (z<=r[x<<1]) sol(x<<1);if (y>r[x<<1]) sol(x<<1|1);
}
inline void mdf(register int x)
{
	s[x]=0;while (x=x>>1) pushup(x);
}
int main()
{
	read(n);read(m);read(q);
	for (i=1;i<=n;i++) read(v[f[i]=i]);for (i=n+1;i<=n<<1;i++) f[i]=i;
	for (i=1;i<=m;i++) {read(lb[i][0]);read(lb[i][1]);}
	for (i=1;i<=q;i++) {read(g[i][0]);read(g[i][1]);if (g[i][0]==2) ed[g[i][1]]=1; else ++tp;}
	for (i=1;i<=m;i++) if (!ed[i]) merge(lb[i][0],lb[i][1]);
	for (i=q;i;i--) if (g[i][0]==2) merge(lb[g[i][1]][0],lb[g[i][1]][1]); else ys[tp--]=getf(g[i][1]);
	memset(ed+1,0,n);
	for (i=1;i<=n;i++) if (!ed[getf(i)]) {dfs(f[i]);ed[f[i]]=1;}
	r[l[1]=1]=n;build(1);
	for (i=1;i<=q;i++) if (g[i][0]==1)
	{
		ans=0;x=ys[++tp];y=(z=dfn[x])+siz[x]-1;
		sol(1);printf("%d\n",ans);mdf(fv[ans]);
	}
}
```

---

