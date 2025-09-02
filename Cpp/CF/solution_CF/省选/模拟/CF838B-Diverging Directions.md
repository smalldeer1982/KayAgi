# Diverging Directions

## 题目描述

You are given a directed weighted graph with $ n $ nodes and $ 2n-2 $ edges. The nodes are labeled from $ 1 $ to $ n $ , while the edges are labeled from $ 1 $ to $ 2n-2 $ . The graph's edges can be split into two parts.

- The first $ n-1 $ edges will form a rooted spanning tree, with node $ 1 $ as the root. All these edges will point away from the root.
- The last $ n-1 $ edges will be from node $ i $ to node $ 1 $ , for all $ 2<=i<=n $ .

You are given $ q $ queries. There are two types of queries

- $ 1\ i\ w $ : Change the weight of the $ i $ -th edge to $ w $
- $ 2\ u\ v $ : Print the length of the shortest path between nodes $ u $ to $ v $

Given these queries, print the shortest path lengths.

## 样例 #1

### 输入

```
5 9
1 3 1
3 2 2
1 4 3
3 5 4
5 1 5
3 1 6
2 1 7
4 1 8
2 1 1
2 1 3
2 3 5
2 5 2
1 1 100
2 1 3
1 8 30
2 4 2
2 2 4
```

### 输出

```
0
1
4
8
100
132
10
```

# 题解

## 作者：Fading (赞：4)

### 题意

给出一个有向图，$n$个节点和$2n-2$个边。点的编号为$1\sim n$，边的编号为$1\sim2n-2$，且每条边都有权值。

这个图的边可以分为两类。

$1$类边(编号$1\sim n-1$)形成一个以$1$为根的生成树，这些边的方向为$1$向外延伸的方向(如$1$->$2$,$1$->$3$,$2$->$4$等等)。

$2$类边(编号$n\sim 2n-2$)从节点$i$($i\in[2,n]$)连向节点$1$。

有$Q$个询问。询问分为两种：

$1\ i\ w:$将第$i$条边的边权改为$w$

$2\ u\ v:$输出点$u$到$v$之间的**最短路**大小

### 输入格式

第一行两个数$n,Q(2\leq n,Q\leq 200000 )$

接下来$2n-2$行，每行三个数表示起点，

前$n-1$个数为$1$类边。

后$n-1$个数为$2$类边。

最后$Q$行表示询问。

-------------------------------------

不算特别难的一道题，但是没有翻译看错了题目。。。

求的是**最短路**长度！！！图论里两点的最短路！！！

我们来分析这个问题：

那么如果$v$是$u$的子节点，那么直接输出两点的树上距离。

否则,答案等于

$$dis[v]+min\{b[x]+(dis[x]-dis[u])\}$$

$dis[i]$是$i$到根节点的距离

$b[i]$是起点为$i$的二类边的长度 

怎么求这个$min$呢？我们转化式子：

$$=dis[v]+min\{b[x]+dis[x]\}-dis[u]$$

这样就可以用线段树(+$\texttt{dfs}$序)求子树最值了。

对于边权修改，这影响到了子树内所有节点的$dis$数组值。因此直接子树加即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long
#define mid ((lb+rb)>>1)
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,tot,head[1000001],sz[1000001];
int a[1000001],tcnt;//a数组记录这个节点连接父节点的边权。
int pre[1000001],b[1000001],dis[1000001],tpos[1000001];
struct edge{
	int to,nxt,dis;
}g[1000001];
inline void made(int from,int to,int dis){
	g[++tot].to=to;g[tot].nxt=head[from];head[from]=tot;
	g[tot].dis=dis;
}
void dfs(int u,int faa){
	sz[u]=1;tpos[u]=++tcnt;pre[tcnt]=u;
	for (int i=head[u];i;i=g[i].nxt){
		int v=g[i].to;
		if (v==faa) continue;
		dis[v]=dis[u]+g[i].dis;a[v]=g[i].dis;
		dfs(v,u);sz[u]+=sz[v];
	}
}
int seg[1000001],tag[1000001];
inline void pushup(int rt){
	seg[rt]=min(seg[rt<<1],seg[rt<<1|1]);
}
void build(int rt,int lb,int rb){
	if (lb==rb) return (void)(seg[rt]=b[pre[lb]]+dis[pre[lb]]);
	build(rt<<1|1,mid+1,rb);build(rt<<1,lb,mid);
	pushup(rt);
}
inline void pushdown(int rt,int lb,int rb){
	if (tag[rt]){
		int ls=rt<<1,rs=rt<<1|1;
		tag[ls]+=tag[rt];tag[rs]+=tag[rt];
		seg[ls]+=tag[rt];seg[rs]+=tag[rt];
		tag[rt]=0;
	}
}
int querymin(int rt,int lb,int rb,int l,int r){
	if (lb>r||rb<l) return 999999999;
	if (lb>=l&&rb<=r) return seg[rt];
	pushdown(rt,lb,rb);
	return min(querymin(rt<<1,lb,mid,l,r),querymin(rt<<1|1,mid+1,rb,l,r));
}
void update(int rt,int lb,int rb,int l,int r,int w){
	if (lb>r||rb<l) return;
	if (lb>=l&&rb<=r) return (void)(seg[rt]+=w,tag[rt]+=w);
	pushdown(rt,lb,rb);
	update(rt<<1,lb,mid,l,r,w);update(rt<<1|1,mid+1,rb,l,r,w);
	pushup(rt);
}
inline int Get(int x){//单点求值，注意这个是dis[x]+b[x]
	return querymin(1,1,n,tpos[x],tpos[x]);
}
int e[1000001];
signed main(){
	n=read(),m=read();
	for (int i=1;i<n;i++){
		int x=read(),y=read(),w=read();
		made(x,y,w);
	}
	for (int i=n;i<=2*n-2;i++){
		int x=read(),y=read(),w=read();
		b[x]=w;e[i]=x;
	}
	dfs(1,0);build(1,1,n);
	while (m--){
		int opt=read();
		if (opt==1){
			int i=read(),w=read();
			if (i>=n){
				int v=e[i];
				update(1,1,n,tpos[v],tpos[v],w-b[v]);
				b[v]=w;
			}else{
				int v=g[i].to;
				update(1,1,n,tpos[v],tpos[v]+sz[v]-1,w-a[v]);
				a[v]=w;
			}
		}else{
			int u=read(),v=read();
			if (tpos[u]<=tpos[v]&&tpos[v]<=tpos[u]+sz[u]-1){
				printf("%lld\n",Get(v)-b[v]-Get(u)+b[u]);continue;
			}
			int Ans=0;
			Ans=querymin(1,1,n,tpos[u],tpos[u]+sz[u]-1)-(Get(u)-b[u]);
			Ans+=Get(v)-b[v];		
			printf("%lld\n",Ans);	
		}
	}
	return 0;
} 
//下面奉上一组hack数据
/*
4 7
1 2 2
2 3 2
3 4 1
2 1 1
3 1 1
4 1 2

1 1 10
2 2 1
2 1 2
2 1 3
2 3 1
2 2 3
2 3 2
*/
```


---

## 作者：Arghariza (赞：2)

好像挺神奇的，也可能是我菜。

以下称前 $n-1$ 条边为「树边」，因为它们组成一棵树；后 $n-1$ 条边为「回边」，因为它们由树节点回到根。

就是对于一个询问，如果 $v$ 在 $u$ 的子树内，发现无论如何答案都要包括 $u\to v$ 的只经过树边的路径。那么只走这条路径一定是最优的，直接维护 $u$ 到根仅经过树边的距离 $d_{u}$，答案就是 $d_v-d_u$。

否则必然是 $u$ 沿着树边到子树内的点 $t$，然后从 $t$ 沿回边到达 $1$ 节点，再直接沿树边走向 $v$。那么这条路径的长度就是 $(d_t-d_u)+a_t+d_v$，$a_u$ 表示 $u$ 到 $1$ 的回边长度。

$d_u+d_v$ 是定值，线段树维护 $\min\limits_{t\in \text{sub(u)}}\{a_t+d_t\}$ 即可。修改边权相当于单点改或子树加，也可以用线段树维护。

代码很好写，跑得还挺快。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

namespace vbzIO {
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define pc putchar
	#define pi pair<int, int>
	#define tu3 tuple<int, int, int>
	#define tu4 tuple<int, int, int, int>
	#define mp make_pair
	#define mt make_tuple
	#define fi first
	#define se second
	#define pb push_back
	#define ins insert
	#define era erase
	#define clr clear
	inline int read () {
		char ch = gh();
		int x = 0;
		bool t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? ~(x - 1) : x;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}
using vbzIO::read;
using vbzIO::write;

const int maxn = 4e5 + 200;
const int inf = 1e18;
struct seg { int tg, vl; } tr[maxn << 2];
int n, m, dfc, d[maxn], b[maxn], id[maxn], sz[maxn];
vector<pi> t[maxn];
pi ed[maxn];

void dfs(int u, int fa) {
    id[u] = ++dfc, sz[u] = 1;
    for (auto p : t[u]) {
        int v = p.fi, w = p.se;
        d[v] = d[u] + w - b[u] + b[v];
        dfs(v, u), sz[u] += sz[v];
    }
}

#define ls x << 1
#define rs x << 1 | 1
#define mid ((l + r) >> 1)
void pushup(int x) { tr[x].vl = min(tr[ls].vl, tr[rs].vl); }
void pushtg(int x, int c) { tr[x].vl += c, tr[x].tg += c; }
void pushdown(int x) {
    if (!tr[x].tg) return;
    pushtg(ls, tr[x].tg), pushtg(rs, tr[x].tg);
    tr[x].tg = 0;
}
void update(int l, int r, int s, int t, int c, int x) {
    if (s <= l && r <= t) return pushtg(x, c);
    pushdown(x);
    if (s <= mid) update(l, mid, s, t, c, ls);
    if (t > mid) update(mid + 1, r, s, t, c, rs);
    pushup(x);
}

int query(int l, int r, int s, int t, int x) {
    if (s <= l && r <= t) return tr[x].vl;
    pushdown(x);
    int res = inf;
    if (s <= mid) res = min(res, query(l, mid, s, t, ls));
    if (t > mid) res = min(res, query(mid + 1, r, s, t, rs));
    return res;
}

signed main() {
	n = read(), m = read();
    for (int i = 1, u, v, w; i <= n - 1; i++) {
        u = read(), v = read(), w = read();
        t[u].pb(mp(v, w)), ed[i] = mp(v, w);
    }
    for (int i = 1, u, v, w; i <= n - 1; i++) {
        u = read(), v = read(), w = read();
        ed[i + n - 1] = mp(u, w), b[u] = w;
    }
    dfs(1, 0);
    for (int i = 2; i <= n; i++) update(1, n, id[i], id[i], d[i], 1);
    while (m--) { 
        int op = read();
        if (op == 2) {
            int u = read(), v = read();
            int duv = (query(1, n, id[v], id[v], 1) - b[v]) - (query(1, n, id[u], id[u], 1) - b[u]);
            if (id[v] >= id[u] && id[v] <= id[u] + sz[u] - 1) write(duv), puts("");
            else write(duv + query(1, n, id[u], id[u] + sz[u] - 1, 1)), puts("");
        } else {
            int p = read(), w = read();
            if (p <= n - 1) update(1, n, id[ed[p].fi], id[ed[p].fi] + sz[ed[p].fi] - 1, w - ed[p].se, 1), ed[p].se = w;
            else update(1, n, id[ed[p].fi], id[ed[p].fi], w - b[ed[p].fi], 1), b[ed[p].fi] = w;
        }
    }
	return 0;
}
```

---

## 作者：ZolaWatle (赞：2)

### CF838B 题解

我们将图中的**有向边**分为如下两种：

1. 树边：$ (u,v) $ 在图中的一棵以一号节点为根的生成树上，且 $v$ 一定在 $u$ 的子树内。这些边的编号为 $ 1 $ 至 $ n-1 $
2. 图边：形如 $ (u,1) $ 的边。编号为 $n$ 至 $2n-2$

处理询问时，我们应该回答从 $u$ 到 $v$ 的最短距离，由于图中的是有向边，所以这个距离并不与 $v$ 到 $u$ 的距离相同。

对于任意一点 $x$，我们设 $dtree_x$ 为走树边从 $x$ 到 $1$ 的**唯一距离**；设 $dgraph_x$ 为走图边从 $x$ 到 $1$ 的**唯一距离**。

现在我们分别考虑以下几种情况：

0. **若 $ u=v $：**

   最短距离显然为 $0$。

1. **若 $v$ 在 $u$ 的子树内**：

   显然，这个最短距离是树边上 $u$ 走到 $v$ 的距离。

2. **若 $v$ 不在 $u$ 的子树内**：

   我们应该明白，由于图中的边是有向边，因此从 $u$ 走到 $v$ 是一定要先从 $u$ 走回到 $1$，再从 $1$ 走树边到达 $v$。

   首先我们能很容易地得出，通过图边 $ (u,1) $ 走到 $1$，再从 $1$ 走树边到达 $v$ 是一条合法路径。

   那么它是不是最短路径呢？其实不一定。

   对于以 $u$ 为根的字数内的每一个节点 $k$，存在这样的路径：先走树边从 $u$ 到达 $k$，再从 $k$ 走图边到达 $1$。这个距离可能是比我们上面讨论的距离短的。题目中保证了每一个节点都有一条图边，因此可以保证这种路径一定合法。

接下来我们考虑如何求得最短路径。

**第 0 种情况**，显然。

**第 1 种情况**，我们可以在读完前 $n-1$ 条边后马上对这棵树进行 $\text{dfs}$，计算出每一的节点相对于根节点 $1$ 的深度、距离、从属关系等信息。我们可以使用 $\text{LCA}(u,v)=u$ 来判断 $v$ 是否在 $u$ 的子树中。最短路径 $dmin=dtree_v-dtree_u$。

**第 2 种情况**，对于以 $u$ 为根的子树，我们考虑维护一个**最小值**，为 $ \{dtree_x+dgrap_x\}_{min}, x\in subtree_u $。这个最小值减去 $dtree_u$ 再加上 $dgraph_v$ 即为所求的最短路径。

接下来我们考虑如何对边进行修改。

当一条边 $ (u,v) $ 的权值被修改时，若 $v\neq 1$，则 $ v $ 及 $ v $ 的子树内的节点走树边到达 $1$ 的距离都要改变；若 $ v=1 $，则只有节点 $u$ 走图边到达 $1$ 的距离会发生改变。但是，对数据结构引入 ”子树修改“ 较为麻烦。

我们注意到一种性质：在一棵树的任意一棵子树中，子树内节点的 $\text{dfs}$ 序是连续的。因此，我们便将 “子树修改” 转化为了 “区间修改”。我们可以考虑使用线段树维护。

我们设 $ dfn_x $ 为节点 $x$ 的 $\text{dfs}$ 序；$ mx_x $ 为节点 $x$ 的子树的最大 $\text{dfs}$ 序。可以考虑一个简单的树形 $\text{DP}$，当然也可以在回溯时记录当前的 $idx\_dfn$。设第 $i$ 条边起点为 $a_i$，终点为 $b_i$，边权为 $c_i$。

依然分两种情况讨论：

1. 若被修改的是图边，只需要对节点 $x$，即区间 $[\text{dfn}_x, \text{dfn}_x]$ 进行修改。
2. 若被修改的是树边，则需要对区间 $[\text{dfn}_x, \text{mx}_x]$ 进行修改。

我们将修改边权的问题转化为区间加，则每次增加的值为修改后的边权 $w'$ 减去该边的原边权 $w$，即 $w'-w$。在修改那条边过后，我们更新这条边的权值，方便下一次的更新操作。

当然，有了 $\text{dfs}$ 序，就没必要用 $\text{LCA}$ 判断 $v$ 是否在 $u$ 的子树中了。只需要判断 $ \text{dfn}_v\in [\text{dfn}_u, \text{mx}_u] $ 即可。

**完整代码：**

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define ll long long
using namespace std;

const int N=2e5+1;
const ll INF=1e18;
int n,Q;
int idx,dfn[N],mx[N],to[N];
int a[N<<1],b[N<<1];
ll c[N<<1],dtree[N],dgraph[N];
vector < pair <int,ll> > E[N];
struct lwh
{
	int ls,rs;
	ll w,tag;
}sgt[N<<2];

inline int rint()
{
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
	return x*f;
}
inline ll rll()
{
	ll x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
	return x*f;
}

inline void dfs(int x,int fa)
{
	dfn[x]=++idx;
	to[dfn[x]]=x;
	int lim=E[x].size();
	for(int i=0;i<lim;i++)
	{
		int y=E[x][i].first;
		if(y==fa) continue;
		ll z=E[x][i].second;
		dtree[y]=dtree[x]+z;
		dfs(y,x);
	}
	mx[x]=idx;
}

inline void pushup(int p){sgt[p].w=min(sgt[p<<1].w,sgt[p<<1|1].w);}
inline void pushdown(int p)
{
	if(!sgt[p].tag) return;
	sgt[p<<1].w+=sgt[p].tag,sgt[p<<1].tag+=sgt[p].tag;
	sgt[p<<1|1].w+=sgt[p].tag,sgt[p<<1|1].tag+=sgt[p].tag;
	sgt[p].tag=0;
}

inline void Build(int p,int l,int r)
{
	sgt[p].ls=l,sgt[p].rs=r;
	if(l==r)
	{
		int pos=to[l];
		sgt[p].w=dtree[pos]+dgraph[pos];
		return;
	}
	int mid=(l+r)>>1;
	Build(p<<1,l,mid);
	Build(p<<1|1,mid+1,r);
	pushup(p);
}

inline void update(int p,int l,int r,ll k)
{
	if(l>sgt[p].rs||r<sgt[p].ls)
		return;
	if(l<=sgt[p].ls&&r>=sgt[p].rs)
	{
		sgt[p].w+=k;
		sgt[p].tag+=k;
		return;
	}
	pushdown(p);
	update(p<<1,l,r,k);
	update(p<<1|1,l,r,k);
	pushup(p);
}

inline ll query(int p,int l,int r)
{
	if(l>sgt[p].rs||r<sgt[p].ls)
		return INF;
	if(l<=sgt[p].ls&&r>=sgt[p].rs)
		return sgt[p].w;
	pushdown(p);
	ll lw=query(p<<1,l,r),rw=query(p<<1|1,l,r);
	pushup(p);
	return min(lw,rw);
}

inline void prework_on_tree()
{
	for(int j=0,i=1;i<n;i++)
	{
		j++;
		int x=rint(),y=rint();
		ll z=rll();
		E[x].push_back(make_pair(y,z));
		a[j]=x,b[j]=y,c[j]=z;
	}
	dfs(1,0);
}

inline void prework_on_graph()
{
	for(int j=n-1,i=1;i<n;i++)
	{
		j++;
		int x=rint(),y=rint();
		ll z=rll();
		a[j]=x,b[j]=y,c[j]=z;
		dgraph[x]=z;
	}
	Build(1,1,n);
}

int main()
{
	n=rint(),Q=rint();
	
	prework_on_tree();
	prework_on_graph();
	
	while(Q--)
	{
		int tmp=rint();
		if(tmp==1)
		{
			int id=rint();
			ll k=rint();
			if(id<n)
			{
				update(1,dfn[b[id]],mx[b[id]],k-c[id]);
				c[id]=k;
			}
			else
			{
				update(1,dfn[a[id]],dfn[a[id]],k-c[id]);
				c[id]=k;
				dgraph[a[id]]=k;
			}
		}
		else
		{
			int u=rint(),v=rint();
			if(dfn[v]>=dfn[u]&&dfn[v]<=mx[u])
			{
				ll du=query(1,dfn[u],dfn[u])-dgraph[u],dv=query(1,dfn[v],dfn[v])-dgraph[v];
				printf("%lld\n",dv-du);
			}
			else
			{
				ll ans=query(1,dfn[u],mx[u]);
				ll du=query(1,dfn[u],dfn[u])-dgraph[u],dv=query(1,dfn[v],dfn[v])-dgraph[v];
				ans-=du,ans+=dv;
				printf("%lld\n",ans);
			}
		}
	}
	
	return 0;
}
```

------------

判词：此题思路简单，紫就紫在这码量！

---

## 作者：Kelvin2009 (赞：1)

这是一道 dfs 序加线段树。

注意到：该图上只有两种边——原 dfs 生成树上的所有特定有向边（只从父亲连向儿子）与所有的特定返祖边（只从子节点连向根节点）。

考虑操作 2：从 $u$ 走到 $v$。有向边的特性满足了走树边深度会严格递增，而返祖边相当于让一个点回到根再从根走向另一个节点。

由此分出两种情况：

1. $u$ 是 $v$ 的祖先。那么一定是从 $u$ 直接走向 $v$，因为即使让 $u$ 回到根，$u$ 仍需经过 $u$ 到 $v$ 的树上路径。
2. $u$ 不是 $v$ 的祖先。那么一定是 $u$ 先从子树中某一节点回到根，再从根直接走向 $v$，否则 $u$ 永远无法走到 $v$。

考虑情况 2，设从根走到某节点的距离为 $dis$，某节点回到根的返祖边长为 $unt$，则从 $u$ 走到 $v$ 需要 $dis_{u'}-dis_u+unt_{u'}+dis_v$。其中 $dis_u$ 和 $dis_v$ 是定值，而 $u$ 的子树上一点 $u'$ 需满足 $unt_{u'}+dis_{u'}$ 最小。

于是回到子树上的问题，用 dfs 序解决。

最小值和路径总长用线段树维护。


---

代码：

---


```cpp
#include<bits/stdc++.h>
using namespace std;
const int range=2e6+5;
const long long lim=0x3f3f3f3f3f3f3f3f;
//bool st;
int n,q;
long long sum[range],val[range<<1];
int to[range<<1],nxt[range<<1],head[range];
inline void add(int u,int v,int eid,long long w)
{
	nxt[eid]=head[u];
	to[eid]=v;
	head[u]=eid;
	val[eid]=w;
}
//bool en;
int down[range];
int tot,tl[range],tr[range],rnk[range];
void dfs(int u)
{
	tl[u]=++tot;
	rnk[tot]=u;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		sum[v]=sum[u]+val[i];
		down[i]=v;
		dfs(v);
	}
	tr[u]=tot;
	return ;
}
long long rec[range],unt[range];
inline bool in_tree(int anc,int u)
{
	return tl[anc]<=tl[u] && tr[u]<=tr[anc];
}
struct sgt
{
	struct tree
	{
		long long minn;
		long long dis,tag;
		tree()
		{
			dis=0ll;
			tag=0ll;
			minn=lim;
		}
	}tree[range<<1];
	#define lson (pos<<1)
	#define mid ((l+r)>>1)
	#define rson (pos<<1|1)
	inline void push_up(int pos)
	{
		tree[pos].minn=min(tree[lson].minn,tree[rson].minn);
		return ;
	}
	inline void push_down(int pos,int l,int r)
	{
		tree[lson].tag+=tree[pos].tag;
		tree[rson].tag+=tree[pos].tag;
		tree[lson].minn+=tree[pos].tag;
		tree[rson].minn+=tree[pos].tag;
		if(l==mid) tree[lson].dis+=tree[pos].tag;
		if(mid+1==r) tree[rson].dis+=tree[pos].tag;
		tree[pos].tag=0ll;
		return ;
	}
	void build(int pos,int l,int r)
	{
		if(l==r)
		{
			int posi=rnk[l];
			tree[pos].dis=sum[posi];
			tree[pos].minn=sum[posi]+unt[posi];
			return ;
		}
		build(lson,l,mid);
		build(rson,mid+1,r);
		push_up(pos);
		return ;
	}
	void add_dis(int pos,int l,int r,int ql,int qr,long long val)
	{
		if(ql<=l && r<=qr)
		{
			tree[pos].minn+=val;
			if(l==r) tree[pos].dis+=val;
			else tree[pos].tag+=val;
			return ;
		}
		push_down(pos,l,r);
		if(ql<=mid) add_dis(lson,l,mid,ql,qr,val);
		if(mid<qr) add_dis(rson,mid+1,r,ql,qr,val);
		push_up(pos);
		return ;
	}
	long long get_dis(int pos,int l,int r,int qpos)
	{
		if(l==r) return tree[pos].dis;
		push_down(pos,l,r);
		if(qpos<=mid) return get_dis(lson,l,mid,qpos);
		else return get_dis(rson,mid+1,r,qpos);
	}
	void add_unt(int pos,int l,int r,int qpos,long long val)
	{
		if(l==r)
		{
			tree[pos].minn+=val;
			return ;
		}
		push_down(pos,l,r);
		if(qpos<=mid) add_unt(lson,l,mid,qpos,val);
		else add_unt(rson,mid+1,r,qpos,val);
		push_up(pos);
		return ;
	}
	long long get_minn(int pos,int l,int r,int ql,int qr)
	{
		if(ql<=l && r<=qr) return tree[pos].minn;
		push_down(pos,l,r);
		long long ans=lim;
		if(ql<=mid) ans=min(ans,get_minn(lson,l,mid,ql,qr));
		if(mid<qr) ans=min(ans,get_minn(rson,mid+1,r,ql,qr));
		return ans;
	}
	#undef mid
	#undef lson
	#undef rson
}sgt;
int main()
{
	//cerr << ((&en)-(&st))/1024.0/1024 << endl;
	scanf("%d%d",&n,&q);
	for(int i=1;i<n;i++)
	{
		int u,v;
		long long w;
		scanf("%d%d%lld",&u,&v,&w);
		add(u,v,i,w);
		rec[i]=w;
	}
	dfs(1);
	for(int i=1;i<n;i++)
	{
		int u,v;
		long long w;
		scanf("%d%d%lld",&u,&v,&w);
		unt[u]=w;
		rec[i+n-1]=u;
	}
	sgt.build(1,1,n);
	while(q--)
	{
		int op;
		scanf("%d",&op);
		if(op==1)
		{
			int eid;
			long long w;
			scanf("%d%lld",&eid,&w);
			if(eid<n)
			{
				int posi=down[eid];
				sgt.add_dis(1,1,n,tl[posi],tr[posi],w-rec[eid]);
				rec[eid]=w;
			}
			else
			{
				int posi=rec[eid];
				sgt.add_unt(1,1,n,tl[posi],w-unt[posi]);
				unt[posi]=w;
			}
		}
		else
		{
			int u,v;
			scanf("%d%d",&u,&v);
			if(in_tree(u,v))
			{
				long long ans=sgt.get_dis(1,1,n,tl[v]);
				ans-=sgt.get_dis(1,1,n,tl[u]);
				printf("%lld\n",ans);
			}
			else
			{
				long long ans=sgt.get_dis(1,1,n,tl[v]);
				ans+=sgt.get_minn(1,1,n,tl[u],tr[u])-sgt.get_dis(1,1,n,tl[u]);
				printf("%lld\n",ans);
			}
		}
	}
	return 0;
}
```

---

## 作者：CDFLS_mao_zx (赞：1)

## 题解：

### 题意：

给出一个  $n$ 个点， $2n-2$ 条边的带权**有向**图。边分为两类：

1.前 $n-1$ 条边构成一颗生成树，以 $1$ 号点为根，由父亲连向儿子。

2.后 $n-1$ 条边第$i$条边由 $i+1$ 号节点连向根。

有 $m$ 次操作，每次操作为将第 $i$ 条边的边权改为 $w$ 或查询 $ u$ 到 $v$ 的最短路。

$1≤n,m≤2×10^5$，任意时刻边权 $1\leq w_i≤10^6$。

### 分析：

下文的直接走到指走树上最短路径。

我们首先发现边权是正的，所以如果终点在起点的子树内，则应该**直接**走到终点。

由于树边是往下的，所以如果不直接走到终点，要往根的方向走，就必定会由一条连向根的边回到根，回到根之后也只能向下走到终点，显然这样会再次走到起点，不如直接由起点走到终点。

如果终点不在起点的子树内，则需要先回到根再**直接**走到终点，原因同上，所以总体的走法是固定的，也就是先到根在走过去，但回到根的方法有很多，也就是可以选择起点子树下的任意一节点回到根。

我们考虑应该如何计算这样走的代价。

### 思路：

考虑树上最短路径的计算过程，先处理出根到每个节点的距离 $dep$ ，$dis(u,v)=dep[u]+dep[v]-2 * dep[lca(u,v)]$

维护一个$dep$就可以了。

我们发现一条树边的修改只会影响到其终点节点的所有子树，只需要记录原先每条树边的权值，用线段树实现区间加操作即可（一颗子树的 $dfs$ 序是连续的，用一个节点的 $dfs$ 序代表该节点即可）。

为何要记录原先的权值，因为在线段树里我们并未维护原先的值，并且其维护的值不仅仅由这个元素决定，所以我们实现不了区间赋值操作，需要将区间赋值转化为区间加减。

我们成功实现了终点在起点的子树内情况的查询，无需 $lca$，起点就是$lca$  。

考虑如何进行终点不在起点的子树内情况的查询。

由上面的分析我们可以发现这个过程分为两步，一是到根，二是由根到到终点。

由根到终点的过程和终点在起点的子树内是一样的，所以考虑如何维护到根的最短路径。

我们记一个节点 $u$ 直接回到根的代价是 $val[u]$。

我们发现要到根必然会在起点 $u$ 的子树中找一个点回到根，所以我们需要查询子树内所有 $v$ 的最小的 $dis(u,v)+val[v]$，化简一下就是$dep[u]-dep[v]+val[v]$，由于 $u$ 是固定的，所以只需要查询子树内 $dep[v]+val[v]$ 的最小值，同样的方法维护。

判断一个点是否在另一个点的子树内：

`if(dfn[y]<dfn[x]+size[x]&&dfn[y]>=dfn[x])`

$size$ 是子树大小，$dfn$  是$dfs$ 序。

### 实现：

数据结构题往往需要一个优秀的实现方式，我们选择直接维护 $dep[v]+val[v]$ ,又因为$val[v]$是直接可以查询到的，这样的常数会相对较小。

边的修改是直接告诉编号，所以有必要用一个映射数组告诉我们一个编号对应的边是什么。

修改完之后一定要记得改变记录的边权。

会爆 $int$ 记得 $long long$ 。

### 代码：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<stack>
#define next nxt
#define itn int
#define y1 y3647
#define int long long
using namespace std;
inline void read(int &x)
{
	x=0;
	int f=1;
	char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')
	ch=getchar();
	if(ch=='-')
	{
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=f;
}
//
int i,j,k,m,n,s,t;
const int N=2e5+10;
int dfn[N],rak[N],head[N],size[N];
int a[N<<2],lazy[N<<2],val[N<<1],sum[N],rk[N<<1];//第一发wa是数组开小了。 
//线段树的数组记得开4倍。 
struct fu{
	int u,v,next,val;
}edge[N<<1];
void work(int aa,int bb,int cc)
{
	edge[++k].next=head[aa];
	head[aa]=k;
	edge[k].v=bb;
	edge[k].u=aa;
	edge[k].val=cc;
}
void push_up(int rt)
{
	a[rt]=min(a[rt<<1],a[rt<<1|1]);
}
void push_down(int rt)
{
	a[rt<<1]+=lazy[rt];
	a[rt<<1|1]+=lazy[rt];
	lazy[rt<<1]+=lazy[rt];
	lazy[rt<<1|1]+=lazy[rt];
	lazy[rt]=0;
}
void updata(int l,int r,int rt,int x,int y,int c)
{
	if(x<=l&&y>=r)
	{
		a[rt]+=c;
		lazy[rt]+=c;
		return;
	}
	int mid=(l+r)/2;
	push_down(rt);
	if(x<=mid)
	updata(l,mid,rt<<1,x,y,c);
	if(y>mid)
	updata(mid+1,r,rt<<1|1,x,y,c);
	push_up(rt);
}
int quert(int l,int r,int rt,int x,int y)
{
	if(x<=l&&y>=r)
	return a[rt];
	int mid=(l+r)/2;
	int ret=1e17;
	push_down(rt);
	if(x<=mid)
	ret=min(ret,quert(l,mid,rt<<1,x,y));
	if(y>mid)
	ret=min(ret,quert(mid+1,r,rt<<1|1,x,y));
	return ret;
}
void build(int l,int r,int rt)
{
	if(l==r)
	{
		a[rt]=sum[rak[l]];
		return;
	}
	int mid=(l+r)/2;
	build(l,mid,rt<<1);
	build(mid+1,r,rt<<1|1);
	push_up(rt);
}
void dfs(int u)
{
	dfn[u]=++t;
	rak[dfn[u]]=u;
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].v;
		if(v==1)
		continue;
		sum[v]=sum[u]+edge[i].val;
		dfs(v);
		size[u]+=size[v];
	}
	sum[u]+=val[u+n];
	size[u]++;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//freopen(".ans","w",stdout);
	read(n),read(m);
	for(i=1;i<=n-1;i++)
	{
		int x,y,z;
		read(x),read(y),read(z);
		rk[i]=y;
		val[y]=z;
		work(x,y,z);
	}
	for(i=1;i<=n-1;i++)
	{
		int x,y,z;
		read(x),read(y),read(z);
		rk[i+n-1]=x;
		val[x+n]=z;
	}
	dfs(1);
	build(1,n,1);
	//val[i]：树边终点为i的权值
	//val[i+n]：i的根边的权值 
	//rk[x]：x号边连向的儿子 (x<=n-1) 
	//rk[x]：x号边起点的编号(n<=x<=2*n-2)
	for(i=1;i<=m;i++)
	{
		int op,x,y;
		read(op),read(x),read(y);
		if(op==1)
		{
			if(x<=n-1)
			{
				updata(1,n,1,dfn[rk[x]],dfn[rk[x]]+size[rk[x]]-1,y-val[rk[x]]);
				val[rk[x]]=y;
			}
			else
			{
				updata(1,n,1,dfn[rk[x]],dfn[rk[x]],y-val[rk[x]+n]);
				val[rk[x]+n]=y;	
			}
		}
		else
		{
			if(dfn[y]<dfn[x]+size[x]&&dfn[y]>=dfn[x])//注意判断是否在子树内 
			printf("%lld\n",(quert(1,n,1,dfn[y],dfn[y])-val[y+n])-(quert(1,n,1,dfn[x],dfn[x])-val[x+n]));
			else
			printf("%lld\n",quert(1,n,1,dfn[x],dfn[x]+size[x]-1)-(quert(1,n,1,dfn[x],dfn[x])-val[x+n])+(quert(1,n,1,dfn[y],dfn[y])-val[y+n]));
		}
	}
	return 0;
}```

### 思考：

如果边是无向边，这道题又应该怎么做。  







---

## 作者：HPXXZYY (赞：0)

$\color{blue}{\texttt{[Problem Discription]}}$

给定一个 $n$ 个点，$(2n-2)$ 条边的**有向**图，每条边有边权。前 $(n-1)$ 条边构成一棵以 $1$ 为根的树，边的方向远离根；后 $(n-1)$ 条边为每个点到 $1$ 的边。每次操作修改其中一条边的边权，或求出从 $u$ 到 $v$ 的最短路。

边权为 $[1,1 \times 10^{6}]$ 间的整数。

$\color{blue}{\texttt{[Analysis]}}$

从 $u$ 到 $v$ 的路径其实很少。

1. 如果 $u$ 能沿着树上的边走到 $v$，那肯定沿着树走最优。
2. 否则 $u$ 必须先回到 $1$，再从 $1$ 沿着树走到 $v$。

维护 $1$ 沿着树到每个点的距离（基为 $\text{Len}(u)$），当修改一条树上边的时候，整棵子树内所有点的距离都将发生变化，但是变化量相同。利用树的深度优先遍历序（即 $\text{dfs}$ 序）连续的性质，可以用线段树维护这个距离。

然后第 $1$ 种情况的答案其实就是 $\text{Len}(v)-\text{Len}(u)$。

> 这里其实利用了差分的思想，将区间求和的问题转化为了前缀和相减。

考虑求出 $u$ 回到 $1$ 的最短路。

从直觉上讲，很容易以为就是后 $(n-1)$ 条边的权值。但是显然 too young too simple 了。

$u$ 虽然不能沿着树的父亲回到 $1$，但它可以先到自己的某个子孙再回到 $1$。假设 $u$ 走到子树内的节点 $w$ 再从 $w$ 回到 $1$，那么路径的长度就是：

$$l_{u,w}+\text{val}_w$$

其中 $l_{u,w}$ 表示在树上从 $u$ 到 $w$ 的距离，$\text{val}_{w}$ 表示 $w$ 到 $1$ 的边的长度。

显然这样是求不出来的。但是 $l_{u,w}=\text{Len}_{w}-\text{Len}_{u}$，于是上面式子改写成：

$$\left ( \text{Len}_{w} + \text{val}_{w} \right )-\text{Len}_{u}$$

括号内的项仅和 $w$ 有关，括号外仅和 $u$ 有关。可以用线段树维护括号内的项，这样就可以单次 $O(\log n)$ 地求出所需结果。

> 这也是一个经典的 trick。如果一个式子里含有两个变量，那一般的数据结构都是无法维护的。分离变量是一个很好的方法。

具体实现看代码。

> 北航 XCPC 春季集训第二场比赛的 D 题。
> 
> **考场上那些傻瓜错误：**
> 1. 把**有向图**看成无向图（但其实主体思路没有太大变化！）。
> 2. 没有考虑到 $u$ 可以先走到子树再回根。
> 3. 数组开太小了……

$\color{blue}{\text{[Code]}}$

```cpp
int Fa[22][N],n,dep[N],q;
int u[N<<1],v[N<<1],w[N<<1],len[N];
int End[N],rec[N],dfscnt,Trans[N];
ll Len[N];
//len[i] 表示从 i 到 1 的直接边的长度 
//Len[i] 表示初始时 1 沿着树到 i 的总长度 
 
struct Segment_Tree{
	int ls[N<<1],rs[N<<1],rt,ndcnt;
	ll sum[N<<1],tag[N<<1],minn[N<<1];
	
	void pushup(int o){
		sum[o]=sum[ls[o]]+sum[rs[o]];
		minn[o]=min(minn[ls[o]],minn[rs[o]]);
	}
	void pushdown(int o,int l,int r){
		tag[ls[o]]+=tag[o];
		tag[rs[o]]+=tag[o];
		minn[ls[o]]+=tag[o];
		minn[rs[o]]+=tag[o];
		
		int mid=(l+r)>>1;
		sum[ls[o]]+=tag[o]*(mid-l+1);
		sum[rs[o]]+=tag[o]*(r-mid);
		
		tag[o]=0;
	}
	
	void build(int &o,int l,int r,int tpe){
		o=++ndcnt;
		tag[o]=sum[o]=minn[o]=0;
		
		if (l==r){
			if (tpe==1) sum[o]=minn[o]=Len[Trans[l]];
			else sum[o]=minn[o]=Len[Trans[l]]+len[Trans[r]];
			return;
		}
		
		int mid=(l+r)>>1;
		build(ls[o],l,mid,tpe);
		build(rs[o],mid+1,r,tpe);
		
		return pushup(o);
	}
	
	void modify(int o,int l,int r,int p,int q,int v){
		if (p<=l&&r<=q){
			tag[o]+=v;
			minn[o]+=v;
			sum[o]+=1ll*v*(r-l+1);
			return;
		}
		
		if (tag[o]) pushdown(o,l,r);
		
		int mid=(l+r)>>1;
		if (p<=mid) modify(ls[o],l,mid,p,q,v);
		if (mid<q) modify(rs[o],mid+1,r,p,q,v);
		
		return pushup(o);
	}
	ll query(int o,int l,int r,int p){
		if (l==r) return sum[o];
		if (tag[o]) pushdown(o,l,r);
		
		int mid=(l+r)>>1;
		if (p<=mid) return query(ls[o],l,mid,p);
		else return query(rs[o],mid+1,r,p);
	}
	ll query(int o,int l,int r,int p,int q){
		if (p<=l&&r<=q) return minn[o];
		if (tag[o]) pushdown(o,l,r);
		
		int mid=(l+r)>>1;ll ans=1e18;
		if (p<=mid) ans=min(ans,query(ls[o],l,mid,p,q));
		if (mid<q) ans=min(ans,query(rs[o],mid+1,r,p,q));
		
		return ans;
	}
}SGT,sgt;
 
struct edge{
	int nxt,to,len;
}e[N<<1];int h[N],ecnt;
void add(int u,int v,int w){
	e[++ecnt]=(edge){h[u],v,w};h[u]=ecnt;
}
 
void dfs(int u,int fa){
	rec[u]=++dfscnt;
	Trans[dfscnt]=u;
	
	dep[u]=dep[fa]+1;
	Fa[0][u]=fa;
	
	for(int i=1;i<=20;i++)
		Fa[i][u]=Fa[i-1][Fa[i-1][u]];
	
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==fa) continue;
		
		Len[v]=Len[u]+e[i].len;
		dfs(v,u);
	}
	
	End[u]=dfscnt;//记录 dfs 序 
}
int LCA(int u,int v){
	if (dep[u]<dep[v]) swap(u,v);
	
	for(int i=20;i>=0;i--)
		if (dep[Fa[i][u]]>=dep[v])
			u=Fa[i][u];
	
	if (u==v) return u;
	
	for(int i=20;i>=0;i--)
		if (Fa[i][u]!=Fa[i][v]){
			u=Fa[i][u];
			v=Fa[i][v];
		}
	
	return Fa[0][v];
}
 
ll query(int u){
	return sgt.query(sgt.rt,1,n,rec[u],End[u])-SGT.query(SGT.rt,1,n,rec[u]);
}
ll query(int u,int v){
	ll res;
	if (u==v) return 0;
	
	if (LCA(u,v)==u) res=SGT.query(SGT.rt,1,n,rec[v])-SGT.query(SGT.rt,1,n,rec[u]);
	else res=query(u)+SGT.query(SGT.rt,1,n,rec[v]);
	
	return res;
}
 
int main(int argv,char *argc[]){
	n=read();q=read();
	for(int i=1;i<n;i++){
		u[i]=read();
		v[i]=read();
		w[i]=read();
		
		add(u[i],v[i],w[i]);
		add(v[i],u[i],w[i]);
	}
	
	for(int j=1;j<n;j++){
		int i=j+(n-1);//真实边标号 
		
		u[i]=read();
		v[i]=read();//v[i] == 1
		w[i]=read();
		
		len[u[i]]=w[i];
	}
	
	dfs(1,0);
	SGT.build(SGT.rt,1,n,1);
	sgt.build(sgt.rt,1,n,2);
	
	for(int i=1;i<=q;i++){
		int opt=read(),s=read(),t=read();
		
		if (opt==1){
			if (s<n){//修改树上的边 
				SGT.modify(SGT.rt,1,n,rec[v[s]],End[v[s]],t-w[s]);
				sgt.modify(sgt.rt,1,n,rec[v[s]],End[v[s]],t-w[s]);
				//v[s] 的子树内所有点到 1 的距离发生变化 
				
				w[s]=t;
			}
			else{
				sgt.modify(sgt.rt,1,n,rec[u[s]],rec[u[s]],t-len[u[s]]);
				len[u[s]]=t;
			}
		}
		else printf("%lld\n",query(s,t));
	}
	
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

在此警示各位遇到一眼题也要想清楚再写，~~不然就会和我一样上来搓了树剖然后写完发现根本没用到以致 duel 输了~~。
### 题意
给一棵带边权的外向树，每个点各自有跳到根的代价，支持若干次修改一条树边或一个点跳到根的代价，查询两点最短路。
### 分析
因为是外向树所以路径是很平凡的，一种是直接往子树里走就走到了，另一种是往子树里走到某个点然后跳到根再往下走到终点。

然后第一种直接维护每个点到根链长度差分一下就好了，修改树边的时候相当于子树加，dfn 序拍到序列上用 BIT 维护区间加单点查值即可。判断是否在子树内也是用 dfn 序。

第二种再维护每个点到根链加跳到根的代价，查询需要时把起点的子树 $\min$ 也加进答案里即可。同上 dfn 序拍平区间加区间 $\min$，朴素 sgt 维护。

时间复杂度 $O(n\log n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=2e5+5;
int n,q;
int a[maxn],b[maxn],len[maxn];
pii e[maxn*2];
vector<int> T[maxn];
int dfn[maxn],nfd[maxn],id[maxn],dfc;
void dfs(int u,int f){
	dfn[u]=++dfc,id[dfc]=u,len[u]=len[f]+a[u];
	for(int v:T[u]){
		if(v==f) continue;
		dfs(v,u);
	}
	nfd[u]=dfc;
}
class Fenwick_Tree{
public:
	int c[maxn];
	int lowbit(int x){return x&(-x);}
	void update(int x,int k){while(x<=n){c[x]+=k;x+=lowbit(x);}}
	int query(int x){int res=0;while(x){res+=c[x];x-=lowbit(x);}return res;}
	void add(int l,int r,int k){update(l,k),update(r+1,-k);}
}tr;
class Segment_Tree{
public:
	int mn[maxn<<2],tag[maxn<<2];
	void pushdown(int o){
		if(!tag[o]) return;
		tag[o*2]+=tag[o],mn[o*2]+=tag[o];
		tag[o*2+1]+=tag[o],mn[o*2+1]+=tag[o];
		tag[o]=0;
	}
	void pushup(int o){mn[o]=min(mn[o*2],mn[o*2+1]);}
	void build(int o,int l,int r){
		if(l==r){mn[o]=len[id[l]]+b[id[l]];return;}
		int m=(l+r)>>1;
		build(o*2,l,m);
		build(o*2+1,m+1,r);
		pushup(o);
	}
	void update(int o,int l,int r,int x,int y,int k){
		if(x<=l&&r<=y){tag[o]+=k,mn[o]+=k;return;}
		int m=(l+r)>>1;pushdown(o);
		if(x<=m) update(o*2,l,m,x,y,k);
		if(y>m) update(o*2+1,m+1,r,x,y,k);
		pushup(o);
	}
	int query(int o,int l,int r,int x,int y){
		if(x<=l&&r<=y) return mn[o];
		int m=(l+r)>>1,res=inf;pushdown(o);
		if(x<=m) res=min(res,query(o*2,l,m,x,y));
		if(y>m) res=min(res,query(o*2+1,m+1,r,x,y));
		return res;
	}
}sgt;
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read(),q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		T[u].eb(v);a[v]=w;
		e[i]=mkpr(u,v);
	}
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		b[u]=w;e[n-1+i]=mkpr(u,v);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) tr.add(dfn[i],nfd[i],a[i]);
	sgt.build(1,1,n);
	while(q--){
		int op=read();
		if(op==1){
			int x=read(),k=read();
			int u=(x<n?e[x].sec:e[x].fir);
			if(x<n) tr.add(dfn[u],nfd[u],k-a[u]),sgt.update(1,1,n,dfn[u],nfd[u],k-a[u]),a[u]=k;
			else sgt.update(1,1,n,dfn[u],dfn[u],k-b[u]),b[u]=k;
		}else{
			int u=read(),v=read();
			if(dfn[u]<=dfn[v]&&dfn[v]<=nfd[u]) cout<<tr.query(dfn[v])-tr.query(dfn[u])<<'\n';
			else cout<<sgt.query(1,1,n,dfn[u],nfd[u])-tr.query(dfn[u])+tr.query(dfn[v])<<'\n';
		}
	}
	return 0;
}
```
临近比赛，祝大家 CSP/NOIP 成功。

---

## 作者：lilong (赞：0)

一道不错的题。

首先观察这棵树，得到以下事实：

- $1$ 为树根。
- 树上的边是由父亲连向儿子的**有向边**。
- 除 $1$ 以外的节点都有一条连向 $1$ 的**有向边**。
- 边权为正。

可知任意两点间都存在最短路，且这条最短路是不难求的。假设要求从 $u$ 到 $v$ 的最短路，设 $dis1_u$ 为 $1$ 到 $u$ 的路径长度，$dis2_u$ 为 $u$ 到 $1$ 的路径长度，分以下两种情况讨论：

- $u$ 是 $v$ 的祖先

显然，此时的最短路即为 $u$ 到 $v$ 的路径长度。由于边权为正，因此多走其它的边一定不优。答案即为 $dis1_v - dis1_u$。

- $u$ 不是 $v$ 的祖先

由于树上的边都是由深度小的点连向深度大的点，因此 $u$ 无法只通过树上的边到达 $v$，需要先回到 $1$ 再去 $v$。而 $u$ 能通过树上的边到达的点即为以 $u$ 为根的子树。设 $z$ 为以 $u$ 为根的子树内一点，我们需要最小化 $u$ 到 $z$ 的距离加上 $z$ 到 $1$ 的距离的和，用式子表示为 $\min{dis1_z-dis1_u+dis2_z}$。$dis1_u$ 在最后处理即可，于是变为 $\min{dis1_z+dis2_z}$，转化成了子树求最小值的问题，使用 dfs 序和线段树解决即可。

接下来讨论如何处理修改操作。对于树上的边，我们观察发现会导致以边的终点为根的子树的 $dis1$ 发生改变，直接修改增量即可。如果不是树上的边，对该边的起点做单点修改即可。

注意单点查询 $dis1$ 时，由于维护的是 $dis1+dis2$，因此需要减去对应的 $dis2$（当然用两棵线段树分开维护也可以）。

时间复杂度 $O(m\log n)$。

```cpp
#include <iostream>
#include <cstdio>
#define int long long
#define N 300001
#define MAXN 30000000000000
 
using namespace std;
 
int n,T,Lx[N],Rx[N],dis1[N],dis2[N],hd[N],tot,cnt,fa[N][19],dep[N],rev[N];
 
struct E
{
	int u,v,w,nxt;
}e[N * 2];
 
struct T
{
	int lzy[N * 4],mi[N * 4],v[N * 4];
	void pushup( int u )
	{
		mi[u] = min( mi[u << 1] , mi[u << 1 | 1] );
		return;
	}
	void pushdown( int u )
	{
		if( lzy[u] )
		{
			mi[u << 1] += lzy[u];
			lzy[u << 1] += lzy[u];
			mi[u << 1 | 1] += lzy[u];
			lzy[u << 1 | 1] += lzy[u];
			lzy[u] = 0;
		}
		return;
	}
	void build( int u , int l , int r )
	{
		if( l == r )
		{
			v[u] = mi[u] = dis1[rev[l]] + dis2[rev[l]];
			return;
		}
		int mid = ( l + r ) >> 1;
		build( u << 1 , l , mid );
		build( u << 1 | 1 , mid + 1 , r );
		pushup( u );
	}
	void update( int u , int l , int r , int L , int R , int x )
	{
		if( L <= l && r <= R )
		{
			mi[u] += x;
			lzy[u] += x;
			return;
		}
		pushdown( u );
		int mid = ( l + r ) >> 1;
		if( L <= mid ) update( u << 1 , l , mid , L , R , x );
		if( R > mid ) update( u << 1 | 1 , mid + 1 , r , L , R , x );
		pushup( u );
		return;
	}
	int query1( int u , int l , int r , int L , int R )
	{
		if( L <= l && r <= R ) return mi[u];
		pushdown( u );
		int mid = ( l + r ) >> 1,res = MAXN;
		if( L <= mid ) res = min( res , query1( u << 1 , l , mid , L , R ) );
		if( R > mid ) res = min( res , query1( u << 1 | 1 , mid + 1 , r , L , R ) );
		return res;
	}
	int query2( int u , int l , int r , int x )
	{
		if( l == r ) return mi[u] - dis2[rev[l]];
		pushdown( u );
		int mid = ( l + r ) >> 1;
		if( x <= mid ) return query2( u << 1 , l , mid , x );
		else return query2( u << 1 | 1 , mid + 1 , r , x );
	}
}t;
 
void add( int u , int v , int w )
{
	tot ++;
	e[tot].u = u;
	e[tot].v = v;
	e[tot].w = w;
	e[tot].nxt = hd[u];
	hd[u] = tot;
}
 
void dfs1( int u , int ff )
{
	dep[u] = dep[ff] + 1;
	Lx[u] = ++ cnt;
	rev[cnt] = u;
	for( int i = hd[u] ; i ; i = e[i].nxt )
	{
		int v = e[i].v;
		if( Lx[v] ) continue;
		dis1[v] = dis1[u] + e[i].w;
		dfs1( v , u );
	}
	Rx[u] = cnt;
}
 
signed main()
{
	ios::sync_with_stdio( false );
	cin.tie( 0 );
	cout.tie( 0 );
	int op,u,v,w;
	cin >> n >> T;
	for( int i = 1 ; i < n ; i ++ )
	{
		cin >> u >> v >> w;
		add( u , v , w );
	}
	dfs1( 1 , 0 );
	for( int i = 1 ; i < n ; i ++ )
	{
		cin >> u >> v >> w;
		add( u , v , w );
		dis2[u] = w;
	}
	t.build( 1 , 1 , n );
	while( T -- )
	{
		cin >> op >> u >> v;
		if( op == 1 )
		{
			if( u < n ) t.update( 1 , 1 , n , Lx[e[u].v] , Rx[e[u].v] , v - e[u].w );
			else t.update( 1 , 1 , n , Lx[e[u].u] , Lx[e[u].u] , v - e[u].w ),dis2[e[u].u] = v;
			e[u].w = v;
		}
		if( op == 2 )
		{
			if( Lx[u] <= Lx[v] && Rx[v] <= Rx[u] ) cout << t.query2( 1 , 1 , n , Lx[v] ) - t.query2( 1 , 1 , n , Lx[u] ) << '\n';
			else cout << t.query1( 1 , 1 , n , Lx[u] , Rx[u] ) - t.query2( 1 , 1 , n , Lx[u] ) + t.query2( 1 , 1 , n , Lx[v] ) << '\n';
		}
	}
	return 0;
}
```

---

## 作者：wwwwwza (赞：0)

初步思路不难。

我们定义前 $n-1$ 条边是一棵树，后 $n-1$ 条边是菊花图。

- $u=v$ 

输出 $0$。

- $v$ 在 $u$ 的子树内

设 $dis_i$ 表示在树上从点 $1$ 到点 $i$ 的距离。

直接输出 $dis_v-dis_u$。

- $v$ 在 $u$ 的子树外

那么从点 $u$ 到 $v$ 的路径为 $u-w-1-v$，$w$ 是 $u$ 子树内的一点。

设 $to_i$ 表示在菊花图中点 $i$ 到点 $1$ 的距离。

答案就是 $dis_w-dis_u+to_w+dis_v$。

用树链剖分将 $dis_w+to_w$ 放入线段树去处理。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+5;
const int inf=1e18;
int n,q;
struct edge{
	int u,v,w;
}r[N];
struct node{
	int v,w;
};
struct seg{
	int num,sum,minn,tag;
}tree[N<<2];
vector<node>g[N];
inline int read(){
	int n=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n*f;
}     
inline void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)write(x/10);
	putchar((x%10)^48);
	return;
}
int dfn[N],siz[N],son[N],fat[N],top[N],dep[N],val[N],cnt=0;
void dfs1(int u,int fa){
	siz[u]=1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i].v,w=g[u][i].w;
		fat[v]=u,dep[v]=dep[u]+1,val[v]=val[u]+w;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v; 
	}
}
void dfs2(int u,int topx){
	top[u]=topx;
	dfn[u]=++cnt;
	if(son[u])dfs2(son[u],topx);
	else return;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i].v;
		if(v==son[u])continue;
		dfs2(v,v);
	}
}
void add(int rt,int d){
	tree[rt].sum+=d;
	tree[rt].tag+=d;
	tree[rt].minn+=d;
}
void pushup(int rt){
	tree[rt].sum=min(tree[rt*2].sum,tree[rt*2+1].sum);
	tree[rt].minn=min(tree[rt*2].minn,tree[rt*2+1].minn);
}
void pushdown(int rt){
	if(tree[rt].tag){
		add(rt*2,tree[rt].tag);
		add(rt*2+1,tree[rt].tag);
		tree[rt].tag=0; 
	}
}
void modify(int rt,int l,int r,int x,int y,int d){
	if(x<=l&&r<=y){
		add(rt,d);
		return;
	}
	pushdown(rt);
	int mid=l+r>>1;
	if(x<=mid)modify(rt*2,l,mid,x,y,d);
	if(y>mid)modify(rt*2+1,mid+1,r,x,y,d);
	pushup(rt);
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fat[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
void update(int rt,int l,int r,int x,int d){
	if(l==r){
		tree[rt].num=d;
		tree[rt].minn=tree[rt].num+tree[rt].sum;
		return;
	}
	pushdown(rt);
	int mid=l+r>>1;
	if(x<=mid)update(rt*2,l,mid,x,d);
	else update(rt*2+1,mid+1,r,x,d);
	pushup(rt);
}
int ask(int rt,int l,int r,int x){
	if(l==r)return tree[rt].sum;
	pushdown(rt);
	int mid=l+r>>1;
	if(x<=mid)return ask(rt*2,l,mid,x);
	else return ask(rt*2+1,mid+1,r,x);
}
int query(int rt,int l,int r,int x,int y){
	if(x<=l&&r<=y)return tree[rt].minn;
	pushdown(rt);
	int mid=l+r>>1,res=inf;
	if(x<=mid)res=min(res,query(rt*2,l,mid,x,y));
	if(y>mid)res=min(res,query(rt*2+1,mid+1,r,x,y));
	return res;
}
signed main(){
	n=read(),q=read();
	for(int i=1;i<=2*n-2;i++){
		r[i]={read(),read(),read()};
		if(i<=n-1){
			g[r[i].u].push_back({r[i].v,r[i].w});
		}
	}
	dfs1(1,0);
	dfs2(1,1);
	for(int i=1;i<=n;i++){
		modify(1,1,n,dfn[i],dfn[i],val[i]);
	}
	for(int i=n;i<=2*n-2;i++){
		update(1,1,n,dfn[r[i].u],r[i].w);
	}
	while(q--){
		int opt=read();
		if(opt==1){
			int i=read(),w=read();
			if(i<=n-1){
				modify(1,1,n,dfn[r[i].v],dfn[r[i].v]+siz[r[i].v]-1,w-r[i].w);
			}else{
				update(1,1,n,dfn[r[i].u],w);
			}
			r[i].w=w;
		}else{
			int u=read(),v=read();
			if(u==v)write(0);
			else if(lca(u,v)==u){
				write(ask(1,1,n,dfn[v])-ask(1,1,n,dfn[u]));
			}else{
				int ans=query(1,1,n,dfn[u],dfn[u]+siz[u]-1)+ask(1,1,n,dfn[v])-ask(1,1,n,dfn[u]);
				write(ans);
			}
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：free_fall (赞：0)

给出 $n$ 个点，有 $2*(n-1)$ 条带权有向边，其中 $n-1$ 条为树边，连向自己的儿子，另外 $n-1$ 条边连向 $1$ 号节点，求多组 $u$ 到 $v$ 的最短路。

我们发现这个图是有以下特点的：

1. 如果 $v$ 在 $u$ 的子树中，那么 $u$ 到 $v$ 的最短路必定是只经过树边到达 $v$，因为边是正整数，所以不可能到达 $1$ 号节点再经过这些边到达 $v$ 的路径更短。

2. 如果 $v$ 不在 $u$ 的子树中，先到达 $u$ 子树中（包括 $u$）任意节点，回到 $1$ 号节点，再通过唯一最短路到达 $v$（显然 $v$ 在 $1$ 的子树中，由性质一可得）。

这样我们就可以求出 $u$ 到 $v$ 的最短路了，我们用 $d_i$ 记录 $1$ 号节点只经过树边到达 $i$ 所经过的路程，用 $a_i$ 记录 $i$ 连向 $1$ 号节点的路径长度，于是两种情况下的答案就是：

1. $d_v-d_u$

2. $\min_{i=L_u}^{i \le R_u}(d_i+a_i)-d_u+d_v$

但是我们发现第二种情况下求解一个答案的时间复杂度是 $O(n)$ 的，显然不能接受，于是我们用一颗支持区间修改，区间最值查询的线段树来维护 $d_i+a_i$ 的最小值，按 $dfs$ 序放入线段树中，这样就可以通过区间修改来修改一整颗子树中的内容。

当修改连向 $1$ 号节点的边时单点修改线段树中对应节点，因为这条边不会影响到其他点的权值。

当修改树边时，这条边会影响一整颗子树的权值，所以进行区间修改。

这样维护线段树与查询的操作都完成了，时间复杂度为 $O(n \log n)$，具体实现见代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=0x3f3f3f3f3f3f3f3f;
int n,q,a[N],u[N<<1],v[N<<1],w[N<<1],d[N],rnk[N],L[N],R[N],fa[N],cnt_dfn;
struct kk{
	int to,val;
};
vector<kk> edge[N];
struct seg_tree{
	#define ls p<<1
	#define rs p<<1|1
	int mi[N<<2],add[N<<2];
	void push_up(int p){
		mi[p]=min(mi[ls],mi[rs]);
		return;
	}
	void push_add(int p,int c){
		mi[p]+=c;
		add[p]+=c;
		return;
	}
	void push_down(int p){
		push_add(ls,add[p]);
		push_add(rs,add[p]);
		add[p]=0;
		return;
	}
	void build(int p,int l,int r){
		if(l==r){
			mi[p]=d[rnk[l]]+a[rnk[l]];
			return;
		}
		int mid=l+r>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		push_up(p);
		return;
	}
	void change(int p,int l,int r,int L,int R,int c){
		if(L<=l&&r<=R){
			push_add(p,c);
			return;
		}
		push_down(p);
		int mid=l+r>>1;
		if(L<=mid)change(ls,l,mid,L,R,c);
		if(mid<R)change(rs,mid+1,r,L,R,c);
		push_up(p);
		return;
	}
	int query(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R)return mi[p];
		push_down(p);
		int mid=l+r>>1,res=inf;
		if(L<=mid)res=min(res,query(ls,l,mid,L,R));
		if(mid<R)res=min(res,query(rs,mid+1,r,L,R));
		return res;
	}
	#undef ls
	#undef rs
}seg;
void dfs(int now){
	L[now]=++cnt_dfn;
	rnk[cnt_dfn]=now;
	for(int i=0;i<edge[now].size();i++){
		int to=edge[now][i].to,val=edge[now][i].val;
		d[to]=d[now]+val;
		fa[to]=now;
		dfs(to);
	}
	R[now]=cnt_dfn;
	return;
}
signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<n;i++){
		scanf("%lld%lld%lld",&u[i],&v[i],&w[i]);
		edge[u[i]].push_back({v[i],w[i]});
	}
	dfs(1);
	for(int i=1;i<n;i++){
		if(fa[u[i]]==v[i])swap(u[i],v[i]);
	}
	for(int i=n;i<2*n-1;i++){
		scanf("%lld%lld%lld",&u[i],&v[i],&w[i]);
		a[u[i]]=w[i];
	}
	seg.build(1,1,n);
	while(q--){
		int op,x,y;
		scanf("%lld",&op);
		if(op==1){
			scanf("%lld%lld",&x,&y);
			if(x<n){
				seg.change(1,1,n,L[v[x]],R[v[x]],y-w[x]);
				w[x]=y;
			}
			else{
				seg.change(1,1,n,L[u[x]],L[u[x]],y-w[x]);
				w[x]=a[u[x]]=y;
			}
		}
		if(op==2){
			scanf("%lld%lld",&x,&y);
			if(L[x]<=L[y]&&L[y]<=R[x])printf("%lld\n",seg.query(1,1,n,L[y],L[y])-a[y]-seg.query(1,1,n,L[x],L[x])+a[x]);
			else printf("%lld\n",seg.query(1,1,n,L[x],R[x])-seg.query(1,1,n,L[x],L[x])+a[x]+seg.query(1,1,n,L[y],L[y])-a[y]);
		}
	}
	return 0;
}
```

---

