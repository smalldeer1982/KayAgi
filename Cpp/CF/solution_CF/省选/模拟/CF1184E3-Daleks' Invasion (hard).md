# Daleks' Invasion (hard)

## 题目描述

在你的帮助下，Heidi 已经制定好了陷阱布置和防御计划。然而，突然间，Doctor 从 TARDIS 里冒了出来，告诉她他已经侦查到了 Daleks 的准备情况，而且这次 Daleks 的数量比以往任何时候都多。非常时期需要非常手段，所以 Heidi 决定冒险与 Daleks 正面交锋，并且她会考虑在任意一条走廊上布置陷阱。

这意味着她再次需要你的帮助，来计算 $E_{max}(c)$ —— 即最大的 $e \le 10^9$，使得如果我们将走廊 $c$ 的能量需求改为 $e$，那么 Daleks 可能会在入侵时使用走廊 $c$ —— 这一次你需要对所有时空走廊都进行计算。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
1 2 8
2 3 3
3 1 4
```

### 输出

```
4
8
8
```

# 题解

## 作者：Tony2 (赞：7)

没人发题解？~~（才6个人通过的题目）~~

[传送门](https://www.luogu.com.cn/problem/CF1184E3)

分两种情况考虑。

1. 不在最小生成树上的边（以下简称非树边）
2. 在最小生成树上的边（以下简称树边）

### 第一种情况

非树边的两个端点在最小生成树上构成的路径上的最大值。
如何求呢？

lca闪亮登场！！！

只要用lca求一下，顺便求路径上的最大值就好了。详细请见代码。

### 第二种情况

我们发现第一种情况是判断路径上的最大值，也就是树边上的任何一个权值不能大于任何非树边的权值 **（前提是这条树边在非树边构成的路径上）**。

我们可以在算第一种情况的时候在路径上每个树边打上标记，然后这种情况直接输出即可。

如何打标记？~~总不能暴力吧~~

我们发现，可以按非树边的边权从小到大打标记，已经被打过标记的边就不用再打了，可以用并查集。已经打过标记的边就可以往上并集，这样就可以快速地跳过已经被打过标记的边了。详细请见代码。

code:

```cpp
#include <bits/stdc++.h> 
using namespace std;
const int N = 100005, M = 1000005;
int n, log2n, m;
int fa[N]/*最小生成树的并查集*/, fa2[N]/*另一个并查集*/, de[N]/*深度*/, f[N][30]/*lca*/, g[N][30]/*lca存储的最大值*/;
int nw[N];//每条树边的最大值（向上的）
struct Edge{
	int u, v, w, i;
	bool operator < (const Edge &x) const{
        return w < x.w;
	}
}eg[M];//用作排序的边
bool vis[M];
vector<pair<int, int> > e[N];//最小生成树
vector<pair<int, int> > ans;//答案
int getfa(int x){
	return (x == fa[x] ? x : fa[x] = getfa(fa[x]));
}
int getfa2(int x){
	return (x == fa2[x] ? x : fa2[x] = getfa2(fa2[x]));
}
void dfs(int u, int fa){//求出f[u][0],g[u][0],de
	f[u][0] = fa;
	for (int i = 0; i < e[u].size(); i++){
		int v = e[u][i].first, w = e[u][i].second;
		if (v == fa) continue;
		de[v] = de[u]+1;
		g[v][0] = w;
		dfs(v, u);
	}
}
pair<int, int> lca(int u, int v){//最大值，lca
	int res = -0x3f3f3f3f;
	if (de[u] < de[v]) swap(u, v);
	int k = de[u]-de[v];
	for (int i = 0; k; k >>= 1, i++) if (k&1) res = max(g[u][i], res), u = f[u][i];
	if (u == v) return {res, u};
	for (int i = log2n; i >= 0; i--) if (f[u][i] != f[v][i])
		res = max(max(g[u][i], g[v][i]), res), u = f[u][i], v = f[v][i];
	return {max(res, max(g[u][0], g[v][0])), f[u][0]};
}
int main(){
	std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	freopen("test_file/in.txt", "r", stdin);
//	freopen("test_file/out.out", "w", stdout);
	cin >> n >> m;
	log2n = log2(n);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++){
		cin >> eg[i].u >> eg[i].v >> eg[i].w;
		eg[i].i = i;
	}
	sort(eg+1, eg+1+m);
	for (int i = 1; i <= m; i++){
		int u = eg[i].u, v = eg[i].v, w = eg[i].w;
		int uu = getfa(u), vv = getfa(v);
		if (uu != vv){
			fa[uu] = vv;
			e[u].push_back({v, w});
			e[v].push_back({u, w});
			vis[i] = 1;
		}
	}
    //以上是最小生成树
	dfs(1, 0);
	for (int j = 1; j <= log2n; j++)
		for (int i = 1; i <= n; i++)
			f[i][j] = f[f[i][j-1]][j-1],
			g[i][j] = max(g[i][j-1], g[f[i][j-1]][j-1]);
	for (int i = 1; i <= n; i++) fa2[i] = i, nw[i] = 1000000000;
    //初始化
	for (int i = 1; i <= m; i++){
		int u = eg[i].u, v = eg[i].v, w = eg[i].w;
		if (!vis[i]){//如果是非树边
			pair<int, int> tmp = lca(u, v);
			ans.push_back({eg[i].i, tmp.first});
			while (de[getfa2(u)] > de[tmp.second]){//从u开始向上打标记
				int uu = getfa2(u);
				nw[uu] = w;
				fa2[uu] = getfa2(f[uu][0]);
			}
			while (de[getfa2(v)] > de[tmp.second]){//从v开始向上打标记
				int vv = getfa2(v);
				nw[vv] = w;
				fa2[vv] = getfa2(f[vv][0]);
			}
		}
	}
	for (int i = 1; i <= m; i++){
		if (!vis[i]) continue;
		int u = eg[i].u, v = eg[i].v;
		if (de[u] < de[v]) swap(u, v);
		ans.push_back({eg[i].i, nw[u]});//直接用nw
	}
	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++) cout << ans[i].second << endl;
	return 0;
}
```

---

## 作者：Hoks (赞：5)

## 前言
重剖题单里的，刚好我的[总结文章](https://www.luogu.com.cn/blog/Hok/cute-tree-decomposition)里把这题当做了练习题，就写篇题解吧。

~~这题和 CF827D 真的有区别吗/kk。~~

## 题意分析
有关题意的话，洛谷上的翻译已经写的很详细易懂了。

接着考虑怎么处理。

首先我们优先考虑造出来一颗 MST，那么一条边就有两种可能性：

1. 在 MST 上。

2. 不在 MST 上。

考虑分开考虑这两种情况，对于第一种而言：

- 若增大它的权值，它会被某些非树边代替，所以它的最大权值必须**小于能代替它的最小的非树边的权值**。

- 所以我们可以考虑对着每条非树边，考虑用他来更新树边的能被替换的最小权值。

- 这一步直接用线段树维护即可。

接着是第二种情况：

- 如果把这条边放进树中，必然会形成一个环，这个时候树就变成了基环树。

- 因为生成的是 MST，所以我们要去掉环上边权最大的一条边。

- 但我们又要保证去掉的这条边不能是非树边。

- 所以我们只需要查询这条边的两端点路径上的最大边权即可。

注意数组大小。

## 代码
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=100010,M=1e6+10,INF=0x3f3f3f3f3f3f3f3f;
struct edge{int v,nxt,w;}e[M<<1];
struct node{int x,y,w,id;}g[M];
int n,m,tot,cnt,yl;
int dfn[N],top[N],head[N],id[N],f[N],ans[M],lz[N<<2];
int fa[N],dep[N],si[N],son[N],a[N],t[N<<2],tt[N<<2];
bool mp[M];
static char buf[1000000],*paa=buf,*pd=buf;
#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
inline int read(void){
    int x(0),a(1);char fc(getchar());
    while(!isdigit(fc)){if(fc=='-') a=-1;fc=getchar();}
    while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
    return x*a;
}
inline void print(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
inline void add(int u,int v,int w){e[++tot].v=v,e[tot].nxt=head[u],head[u]=tot,e[tot].w=w;}
inline bool cmp(node x,node y){return x.w<y.w;}
inline int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
inline void dfs1(int u,int ff)
{
	dep[u]=dep[ff]+1,fa[u]=ff,si[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==ff) continue;
		dfs1(v,u);si[u]+=si[v];a[v]=e[i].w;
		if(si[v]>si[son[u]]) son[u]=v;
	}
}
inline void dfs2(int u,int topf)
{
	top[u]=topf,dfn[u]=++cnt,id[cnt]=a[u];
	if(son[u]) dfs2(son[u],topf);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
inline void pushup(int p){t[p]=max(t[ls],t[rs]);}
inline void pushdown(int p)
{
	if(lz[p]!=INF)
	{
		lz[ls]=min(lz[ls],lz[p]),lz[rs]=min(lz[rs],lz[p]);
		tt[ls]=min(tt[ls],lz[p]),tt[rs]=min(tt[rs],lz[p]);
		lz[p]=INF;
	}
}
inline void build(int p,int l,int r)
{
	if(l==r) return void(t[p]=id[l]);
	build(ls,l,mid),build(rs,mid+1,r),pushup(p);
}
inline int query(int p,int l,int r,int s,int e)
{
	if(l>=s&&r<=e) return t[p];
	int res=0;if(mid>=s) res=query(ls,l,mid,s,e);
	if(mid<e) res=max(res,query(rs,mid+1,r,s,e));
	return res;
}
inline void modify(int p,int l,int r,int s,int e,int k)
{
	if(l>=s&&r<=e) return void(lz[p]=min(lz[p],k)),void(tt[p]=min(tt[p],k));
	pushdown(p);
	if(mid>=s) modify(ls,l,mid,s,e,k);
	if(mid<e) modify(rs,mid+1,r,s,e,k);
	tt[p]=min(tt[ls],tt[rs]);
}
inline int qry(int p,int l,int r,int s,int e)
{
	if(l>=s&&r<=e) return tt[p];pushdown(p);
	int res=0;if(mid>=s) res=qry(ls,l,mid,s,e);
	if(mid<e) res=max(res,qry(rs,mid+1,r,s,e));
	return res;
}
inline void modify(int i)
{
	int x=g[i].x,y=g[i].y,w=g[i].w;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		modify(1,1,cnt,dfn[top[x]],dfn[x],w);x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	modify(1,1,n,dfn[x]+1,dfn[y],w);
}
inline int query(int i)
{
	int x=g[i].x,y=g[i].y,res=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res=max(query(1,1,cnt,dfn[top[x]],dfn[x]),res);x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	return max(res,query(1,1,n,dfn[x]+1,dfn[y]));
}
signed main()
{
	n=read(),m=read();memset(tt,0x3f,sizeof tt);memset(lz,0x3f,sizeof lz);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1,u,v,w;i<=m;i++) u=g[i].x=read(),v=g[i].y=read(),w=g[i].w=read(),g[i].id=i;
	sort(g+1,g+1+m,cmp);
	for(int i=1,u,v,w;i<=m;i++)
	{
		u=g[i].x,v=g[i].y,w=g[i].w;
		if(find(u)==find(v)) continue;
		yl++;add(u,v,w),add(v,u,w);f[find(u)]=find(v);
		mp[i]=1;if(yl==n-1) break;
	}
	dfs1(1,0),dfs2(1,1),build(1,1,cnt);
	for(int i=1;i<=m;i++) if(!mp[i]) ans[g[i].id]=query(i),modify(i);
	for(int i=1,x;i<=m;i++) if(mp[i]) x=max(dfn[g[i].x],dfn[g[i].y]),ans[g[i].id]=qry(1,1,cnt,x,x);
	for(int i=1;i<=m;i++) print(ans[i]==INF?1e9:ans[i]),puts("");
	return 0;
}
```

---

## 作者：EityDawn (赞：2)

## 思路：

先对原图求最小生成树，建出来进行树剖。

分情况讨论

1. 这条边不在生成树上，断开这条边两端点之间的路径上的边，连接这条边，还是一棵树。那么如果这条边可以加入生成树之内，那么它可以修改的权值最大为两端点之间路径上边权的最大值。
2. 这条边不在生成树上，假设它在原图处在环 $S$ 上，那么什么时候它会被环 $S$ 中的非树边替代呢？答案是它 $S$ 中非树边边权的最小值小于这条边，我们修改的边权不能超过它所在环中非树边边权最小值。

那么现在要做的就是拿线段树维护这些东西。

先处理每条非树边，对于边 $(u,v,w)$，询问路径 $(u,v)$ 间最大的边权，作为答案，对路径上的树边答案 $ma_i$ 做一次 $ma_i\leftarrow \min(ma_i,w)$ 的操作，对于树边直接询问答案就 OK 了。

## code：

```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<climits>
#include<cmath>
#include<ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=1e5+10,M=1e6+10;
const int inf=1e9;
int c=0;
struct edge{
	int from,to,Value,id;
	bool operator<(const edge&a) const{return Value<a.Value;}
}e[M];
vector<edge>E;
vector<pair<int,int>>G[N];
int a[N],dfn[N],id[N],top[N];
int son[N],fa[N],siz[N],dep[N];
int Set[N],n,m,o=0,rt=1,Ans[M];
bool vis[M];
int find(int now){return Set[now]==now?now:Set[now]=find(Set[now]);}
void Kruskal()
{
	sort(E.begin(),E.end());
	for(auto [now,to,Value,id]:E)
	{
		int x=find(now),y=find(to);
		if(x==y) continue;
		Set[y]=x;vis[id]=1;
		G[now].push_back({to,Value});
		G[to].push_back({now,Value});
	}
	return;
}
void dfs(int now,int from)
{
	siz[now]=1,fa[now]=from;
	for(auto [to,Value]:G[now])
	{
		if(to==from) continue;
		a[to]=Value;dep[to]=dep[now]+1;
		dfs(to,now);
		siz[now]+=siz[to];
		if(siz[to]>siz[son[now]]) son[now]=to;
	}
}
void redfs(int now,int Top)
{
	id[dfn[now]=++o]=now,top[now]=Top;
	if(son[now]) redfs(son[now],Top);
	for(auto [to,Value]:G[now])
		if(to==fa[now]||to==son[now]) continue;
		else redfs(to,to);
	return;	
} 
int ma[N<<2],Init[N<<2];
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
void push_up(int x)
{
	ma[x]=max(ma[lc(x)],ma[rc(x)]);
	Init[x]=max(Init[lc(x)],Init[rc(x)]);
}
void push_down(int x)
{
	if(ma[x]<ma[lc(x)]) ma[lc(x)]=ma[x];
	if(ma[x]<ma[rc(x)]) ma[rc(x)]=ma[x];
}
void build(int l,int r,int x)
{
	if(l==r) return void(ma[x]=inf),void(Init[x]=a[id[l]]);
	int mid=(l+r)>>1;
	build(l,mid,lc(x)),build(mid+1,r,rc(x));
	return push_up(x);
}
void Min(int p,int q,int val,int l,int r,int x)
{
	if(p<=l&&q>=r) return void(ma[x]=min(ma[x],val));
	push_down(x);
	int mid=(l+r)>>1;
	if(p<=mid) Min(p,q,val,l,mid,lc(x));
	if(q>mid) Min(p,q,val,mid+1,r,rc(x));
	return push_up(x);
}
void Min(int x,int y,int val)
{
	int res=0;
	while(top[x]^top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		Min(dfn[top[x]],dfn[x],val,1,n,1);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	if(x!=y) Min(dfn[x]+1,dfn[y],val,1,n,1);
}
int queryInit(int p,int q,int l,int r,int x)
{
	if(p<=l&&q>=r) return Init[x];
	push_down(x);
	int mid=(l+r)>>1;
	if(q<=mid) return queryInit(p,q,l,mid,lc(x));
	if(p>mid) return queryInit(p,q,mid+1,r,rc(x));
	return max(queryInit(p,q,l,mid,lc(x)),queryInit(p,q,mid+1,r,rc(x)));
}
int queryInit(int x,int y)
{
	int res=0;
	while(top[x]^top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res=max(res,queryInit(dfn[top[x]],dfn[x],1,n,1));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	if(x!=y) res=max(res,queryInit(dfn[x]+1,dfn[y],1,n,1));
	return res;
}
int query(int p,int q,int l,int r,int x)
{
	if(p<=l&&q>=r) return ma[x];
	push_down(x);
	int mid=(l+r)>>1;
	if(q<=mid) return query(p,q,l,mid,lc(x));
	if(p>mid) return query(p,q,mid+1,r,rc(x));
	return max(query(p,q,l,mid,lc(x)),query(p,q,mid+1,r,rc(x))); 
}
int query(int x,int y)
{
	int res=0;
	while(top[x]^top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res=max(res,query(dfn[top[x]],dfn[x],1,n,1));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	if(x!=y) res=max(res,query(dfn[x]+1,dfn[y],1,n,1));
	return res;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) Set[i]=i;
	for(int i=1,x,y,z;i<=m;i++)
	{
		cin>>x>>y>>z;
		e[i]={x,y,z,i};
		E.push_back({x,y,z,i}),E.push_back({y,x,z,i});
	}
	Kruskal();dfs(rt,0);redfs(rt,rt);build(1,n,1);
	for(int i=1;i<=m;i++)
		if(!vis[i]) Ans[i]=queryInit(e[i].from,e[i].to),Min(e[i].from,e[i].to,e[i].Value);
	for(int i=1;i<=m;i++)
		if(vis[i]) Ans[i]=query(e[i].from,e[i].to);
	for(int i=1;i<=m;i++) cout<<Ans[i]<'\n';
	return 0;
}
```

---

## 作者：Mobius127 (赞：2)

[题传](https://www.luogu.com.cn/problem/CF1184E3)

~~三倍经验，太爽了~~

跟 CF1023F 很像，如果不想再做另外一题珂以简单看一下我的 [题解](https://www.luogu.com.cn/blog/Tomori-Nao/CF1023F)。

同样的思路，我们先把最小生成树建出来，接下来的边分为两种：


- 不是最小生成树上的边：

这似乎是个灰常经典的问题，这一条边会在最小生成树上形成一个环，我们只需要查询环上的最大值就是答案。

- 在最小生成树上的边：

其实就是反过来想，非树边本身的限制就是环上的 $\max \le w$，所以就是环 $(a, b)$ 上的所有边不得超过 $w$，直接用树剖 + 线段树弄掉就行了。

复杂度 $O(m \log m + m\log^2 n)$。


但是由于树剖实在太臭了不想写，怎么办？

对于非树边，改用 ST 表加速，复杂度 $O(n \log n+m \log n)$。

对于树边，注意到若（按边权排序后）之前已经有一条非树边覆盖了这条树边，那么我们应对下一条非树边是不需要再覆盖一次的，也就是说，珂以直接跳到另一端，使用并查集维护，每个边最多覆盖一次，复杂度 $O(m+n\alpha(n))$。


---

## 作者：_Ponder_ (赞：1)

[Daleks' Invasion](https://www.luogu.com.cn/problem/CF1184E3)

### 题目大意

给定一张无向带权图，对于每条边求一个最大的 $x$，使得将这条边的边权修改为 $x$ 后这条边能位于这张图的最小生成树上。

### 思路分析

~~没事干了就把之前写过的题拉出来水题解。~~

我们先把原图的最小生成树求出来，考虑每条边 $(u,v)$，分类讨论：

- 如果这条边不在原图最小生成树上：

容易发现，这时这条边的 $x$ 就是在最小生成树上 $u$ 到 $v$ 的最大边权 $w$。用一个随便什么东西维护就行了。（倍增，树剖套 ST 表，树剖套线段树……能用的东西太多了）

证明是容易的：

首先考虑可行性，当我们将这条边的边权修改为 $w$ 后，我们显然可以通过断掉之前最大边权所在的边，再加入这条边的方式生成一个新的合法最小生成树。

再考虑极大性，这就更显然了，由于最小生成树是一颗瓶颈生成树，也就是说最小生成树保证最大边权最小。那么如果 $x=w+1$，并且这条边还在最小生成树上的话，那么就与最小生成树的性质矛盾了，因此极大性成立。

- 如果这条边在原图的最小生成树上：

类似的，我们可以发现这条边的 $x$ 是在原图中 $u$ 到 $v$ 的**所有不经过树边的简单路径**中的最小边权 $w$。

证明也类似上文的证明，此处略去。~~读者自证不难。~~

实现方式也很多，可以先枚举所有不在最小生成树上的边 $(u,v,w)$，用树剖套线段树支持 $u$ 到 $v$ 的链对 $w$ 取 $\min$。

也可以先排个序然后将区间取 $\min$ 改为区间赋值，但其实没什么区别。

那么这题就做完了，总时间复杂度为 $O(m\log ^2n)$。

### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int N = 1001000;
#define inf 1000000000
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid ((l + r) >> 1)

int n, m, in1, in2, in3, cnt;
int fa[N], siz[N], son[N], dep[N], top[N], dfn[N], rnk[N];
int vis[N], fat[N], pw[N], ans[N], inp[N];

int find(int x){
    return fat[x] == x ? x : fat[x] = find(fat[x]);
}

struct Edge{
    int u, v, w, id;
}e[N];

vector <pair<int, int>> to[N];

void dfs_1(int s, int gr){
    dep[s] = dep[gr] + 1;
    siz[s] = 1; fa[s] = gr;
    for (auto [v, w] : to[s]) {
        if (v == gr) continue;
        dfs_1(v, s);
        siz[s] += siz[v];
        pw[v] = w;
        if (siz[son[s]] < siz[v]) son[s] = v;
    }
}

void dfs_2(int s, int tp){
    top[s] = tp; dfn[s] = ++ cnt; rnk[cnt] = s;
    if (!son[s]) return ;
    dfs_2(son[s], tp);
    for (auto [v, w] : to[s]) 
        if (v != fa[s] && v != son[s]) dfs_2(v, v);
}

struct STn{
    int maxn;
    int tag;
};
struct ST{
    STn a[N << 2];
    void build(int p, int l, int r){
        a[p].tag = inf;
        if (l == r) return a[p].maxn = inp[l], void();
        build(ls, l, mid); build(rs, mid + 1, r);
        a[p].maxn = max(a[ls].maxn, a[rs].maxn);
    }
    void min_t(int p, int k){
        a[p].maxn = min(a[p].maxn, k);
        a[p].tag = min(a[p].tag, k);
    }
    void push_down(int p){
        if (a[p].tag == inf) return ;
        min_t(ls, a[p].tag); min_t(rs, a[p].tag);
        a[p].tag = inf;
    }
    void change(int p, int l, int r, int x, int y, int k){
        if (x <= l && r <= y) return min_t(p, k);
        push_down(p);
        if (x <= mid) change(ls, l, mid, x, y, k);
        if (y > mid) change(rs, mid + 1, r, x, y, k);
        a[p].maxn = max(a[ls].maxn, a[rs].maxn);
    }
    int ask(int p, int l, int r, int x, int y){
        if (x <= l && r <= y) return a[p].maxn;
        push_down(p);
        if (y <= mid) return ask(ls, l, mid, x, y);
        if (x > mid) return ask(rs, mid + 1, r, x, y);
        return max(ask(ls, l, mid, x, y), ask(rs, mid + 1, r, x, y));
    }
}tree;

int ask(int x, int y){
    int res = -inf;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        res = max(res, tree.ask(1, 1, n, dfn[top[x]], dfn[x]));
        x = fa[top[x]]; 
    }
    if (x != y) res = max(res, tree.ask(1, 1, n, min(dfn[x], dfn[y]) + 1, max(dfn[x], dfn[y])));
    return res;
}

void change(int x, int y, int k){
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        tree.change(1, 1, n, dfn[top[x]], dfn[x], k);
        x = fa[top[x]];
    }
    if (x != y) tree.change(1, 1, n, min(dfn[x], dfn[y]) + 1, max(dfn[x], dfn[y]), k);
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i ++) fat[i] = i;
    for (int i = 1; i <= m; i ++) {
        scanf("%d %d %d", &in1, &in2, &in3);
        e[i] = Edge{in1, in2, in3, i};
    }
    sort(e + 1, e + m + 1, [](Edge a, Edge b){return a.w < b.w;});
    for (int i = 1; i <= m; i ++)
        if (find(e[i].u) != find(e[i].v)) {
            to[e[i].u].push_back({e[i].v, e[i].w});
            to[e[i].v].push_back({e[i].u, e[i].w});
            vis[e[i].id] = 1;
            fat[find(e[i].u)] = find(e[i].v);
        }
    dfs_1(1, 0); dfs_2(1, 1);
    for (int i = 1; i <= n; i ++) inp[dfn[i]] = pw[i];
    tree.build(1, 1, n);
    for (int i = 1; i <= m; i ++)
        if (!vis[e[i].id]) ans[e[i].id] = ask(e[i].u, e[i].v);
    for (int i = 1; i <= n; i ++) inp[i] = inf;
    tree.build(1, 1, n);
    for (int i = 1; i <= m; i ++)
        if (!vis[e[i].id]) change(e[i].u, e[i].v, e[i].w);
    for (int i = 1; i <= m; i ++) 
        if (vis[e[i].id]) {
            int u = e[i].u, v = e[i].v;
            if (dep[u] < dep[v]) swap(u, v);
            ans[e[i].id] = tree.ask(1, 1, n, dfn[u], dfn[u]);
        }
    for (int i = 1; i <= m; i ++) cout << ans[i] << '\n';
    return 0;
}
```

---

## 作者：729hao (赞：0)

[**luogu 传送门**](https://www.luogu.com.cn/problem/CF1184E3) [**codeforces 传送门**](https://codeforces.com/problemset/problem/1184/E3)


---

## 思路
先求出最小生成树，则可以把整个图的边划分为在树上的和不在树上的。

对于非树边，它与树边会构成一个环。如果要求最小生成树，则要删掉这个环上边权最大的边。所以这条非树边的最大边权不能超过这条边两个点在树上路径上的最大边权。

所以在最小生成树上树剖，边权转点权后用 ST 表维护最大值即可。

对于树边 $e$ ，根据刚才非树边的分析，对于一条非树边 $e'$，如果其构成的环上包含 $e$，则 $e$ 的边权不能超过 $e'$。注意这里我们无需考虑其它树边的边权，因为环中树边的边权一定不比非树边大。 

故对于一条树边，它的答案即为所有覆盖（定义一条非树边覆盖树边表示非树边的两点在树上的路径包含这条树边）了自己的非树边的边权最小值。

因为树剖每条链上的 dfn 连续，这里我们可以在每条非树边树剖跳祖先的同时，给覆盖的链打上差分标记，最后根据树剖的 dfs 序求每条树边的答案。

（感觉最后一段讲的不是很清楚……）
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace cs{
	#define LL long long
	const int N=1e5;
	const int M=1e6;
	const int INF=1e9;
	int n,m,bln[N+5],nt[M+5],cnt,ans[M+5];
	struct edges{
		int u,v,w,id;
		bool operator <(const edges &B)const{
			return w<B.w;
		}
	}e[M+5];
	int Getfa(int x){return bln[x]==x?x:bln[x]=Getfa(bln[x]);}
	struct edge{int to,id;};
	vector<edge>v[N+5];
	int fa[N+5],dep[N+5],siz[N+5],hs[N+5],top[N+5],tid[N+5],hcnt,sid[N+5],frm[N+5];
	void dfs(int rt,int prt,int depth){
		fa[rt]=prt;
		dep[rt]=depth;
		siz[rt]=1;
		for(auto u:v[rt]){
			if(u.to==prt)continue;
			frm[u.to]=u.id;
			dfs(u.to,rt,depth+1);
			siz[rt]+=siz[u.to];
			if(siz[hs[rt]]<siz[u.to])hs[rt]=u.to;
		}
	}
	void dfs2(int rt,int Top){
		top[rt]=Top;
		tid[rt]=++hcnt;
		sid[hcnt]=rt;
		if(hs[rt])dfs2(hs[rt],Top);
		else return;
		for(auto u:v[rt]){
			if(u.to==fa[rt]||u.to==hs[rt])continue;
			dfs2(u.to,u.to);
		}
	}
	int R[N+5][25];
	void ST(){
		for(int i=1;i<=n;i++){
			R[i][0]=e[frm[sid[i]]].w;
		}
		for(int j=1;1<<j<=n;j++){
			for(int i=1;i+(1<<j)-1<=n;i++){
				R[i][j]=max(R[i][j-1],R[i+(1<<j-1)][j-1]);
			}
		}
	}
	int Ask(int x,int y){
		int i=log2(y-x+1);
		return max(R[x][i],R[y-(1<<i)+1][i]);
	}
	vector<int>add[N+5],sub[N+5];//差分标记
	int getans(int u,int v,int w){
		int rtn=0;
		while(top[u]!=top[v]){
			if(dep[top[u]]>dep[top[v]]){
				rtn=max(rtn,Ask(tid[top[u]],tid[u]));
				add[tid[top[u]]].push_back(w);
				sub[tid[u]+1].push_back(w);
				u=fa[top[u]];
			}
			else{
				rtn=max(rtn,Ask(tid[top[v]],tid[v]));
				add[tid[top[v]]].push_back(w);
				sub[tid[v]+1].push_back(w);
				v=fa[top[v]];
			}
		}
		if(u==v)return rtn;
		if(tid[u]>tid[v])swap(u,v);
		rtn=max(rtn,Ask(tid[u]+1,tid[v]));
		add[tid[u]+1].push_back(w);
		sub[tid[v]+1].push_back(w);
		return rtn;
	}
	struct cs_heap{
		priority_queue<int,vector<int>,greater<int> >data,dlt;
		void insert(int x){data.push(x);}
		void erase(int x){dlt.push(x);}
		int top(){
			while(!dlt.empty()&&data.top()==dlt.top()){
				data.pop();
				dlt.pop();
			}
			return data.top();
		}
		int size(){return data.size()-dlt.size();}
		bool empty(){return size()==0;}
	}pq;
	int main(){
		ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
//		freopen("sample1.in","r",stdin);
//		freopen("easy.out","w",stdout);
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			bln[i]=i;
		}
		int f1,f2;
		for(int i=1;i<=m;i++){
			cin>>e[i].u>>e[i].v>>e[i].w;
			e[i].id=i;
		}
		sort(e+1,e+m+1);
		for(int i=1;i<=m;i++){
			f1=Getfa(e[i].u);f2=Getfa(e[i].v);
			if(f1==f2){
//				printf("nt:%d\n",i);
				nt[++cnt]=i;
			}
			else{
				bln[f1]=f2;
				v[e[i].u].push_back({e[i].v,i});
				v[e[i].v].push_back({e[i].u,i});
			}
		}
		dfs(1,0,1);
		dfs2(1,1);
		ST();
		for(int i=1;i<=cnt;i++){
			ans[e[nt[i]].id]=getans(e[nt[i]].u,e[nt[i]].v,e[nt[i]].w);
		}
		for(int i=1;i<=n;i++){//求树边的答案
			for(auto u:add[i]){
				pq.insert(u);
			}
			for(auto u:sub[i]){
				pq.erase(u);
			}
			if(pq.empty())ans[e[frm[sid[i]]].id]=INF;
			else ans[e[frm[sid[i]]].id]=pq.top();
		}
		for(int i=1;i<=m;i++){
			cout<<ans[i]<<"\n";
		}
		return 0;
	}
}
int main(){
	cs::main();
	return 0;
}
```

---

## 作者：yhylivedream (赞：0)

套路题，先跑出最小生成树。

分类讨论：

考虑非树边，显然答案为非树边的端点在生成树上构成的路径的边权的最大值，这个可以直接维护 $mx_{i,j}$ 表示点 $i$ 向上跳 $2^j$ 步的边权最大值，询问直接倍增。

考虑树边，对于每条树边在非树边构成的路径上的非树边，树边的权值不能大于其权值，看起来需要树剖，其实只需要将非树边按边权排序，转化为区间覆盖问题，使用并查集即可。

### Code

```cpp
// author : yhy
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using Pii = pair<int, int>;

const int kMaxN = 1e6 + 5, kL = 21;

int n, m, mn[kMaxN], vis[kMaxN], ans[kMaxN];
vector<Pii> e[kMaxN];

struct Node {
  int id, x, y, w;
  bool operator<(Node _) { return w < _.w; }
} v[kMaxN];
struct Dsu {
  int fa[kMaxN];
  void Init() { iota(fa + 1, fa + n + 1, 1); }
  void M(int x, int y) { fa[x] = y; }
  int GetRoot(int x) {
    return fa[x] == x ? x : fa[x] = GetRoot(fa[x]);
  }
} s1, s2;
struct LCA {
  int d[kMaxN], f[kMaxN][kL], mx[kMaxN][kL];
  void Init(int x = 1, int fa = 0) {
    f[x][0] = fa, d[x] = d[fa] + 1;
    for (int i = 1; i < kL; i++) {
      f[x][i] = f[f[x][i - 1]][i - 1];
      mx[x][i] = max(mx[x][i - 1], mx[f[x][i - 1]][i - 1]);
    }
    for (auto [nxt, w] : e[x]) {
      nxt != fa && (mx[nxt][0] = w, Init(nxt, x), 0);
    }
  }
  Pii Lca(int x, int y, int ans = 0) { // {Lca, 值}
    d[x] > d[y] && (swap(x, y), 0);
    for (int i = 0; i < kL; i++) {
      ((d[y] - d[x]) >> i & 1) && (ans = max(ans, mx[y][i]), y = f[y][i]);
    }
    if (x == y) return {x, ans};
    for (int i = kL - 1; i >= 0; i--) {
      f[y][i] != f[x][i] && (ans = max(ans, max(mx[x][i], mx[y][i])), x = f[x][i], y = f[y][i]);
    }
    return {f[x][0], max(ans, max(mx[x][0], mx[y][0]))};
  }
} l;

signed main() {
  cin.tie(0)->ios::sync_with_stdio(0);
  cin >> n >> m, s1.Init();
  for (int i = 1; i <= m; i++) {
    cin >> v[i].x >> v[i].y >> v[i].w, v[i].id = i;
  }
  sort(v + 1, v + m + 1);
  for (int i = 1; i <= m; i++) {
    int fx = s1.GetRoot(v[i].x), fy = s1.GetRoot(v[i].y);
    if (fx != fy) {
      s1.M(fx, fy), vis[i] = 1;
      e[v[i].x].push_back({v[i].y, v[i].w});
      e[v[i].y].push_back({v[i].x, v[i].w});
    }
  }
  l.Init(1, 0), s2.Init();
  fill(mn + 1, mn + n + 1, 1e9);
  for (int i = 1; i <= m; i++) {
    if (!vis[i]) {
      int x = s2.GetRoot(v[i].x), y = s2.GetRoot(v[i].y);
      auto [lca, mx] = l.Lca(v[i].x, v[i].y); ans[v[i].id] = mx;
      for (; l.d[x] > l.d[lca]; x = s2.GetRoot(x)) {
        mn[x] = v[i].w, s2.M(x, s2.GetRoot(l.f[x][0]));
      }
      for (; l.d[y] > l.d[lca]; y = s2.GetRoot(y)) {
        mn[y] = v[i].w, s2.M(y, s2.GetRoot(l.f[y][0]));
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    if (vis[i]) {
      ans[v[i].id] = mn[l.d[v[i].x] < l.d[v[i].y] ? v[i].y : v[i].x];
    }
  }
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
}
```

---

## 作者：OldDriverTree (赞：0)

# Solution

首先对原图建出 $\text{MST}$，枚举非树边 $(x,y,z)$，这条非树边的答案就为 $\text{MST}$ 上 $x$ 到 $y$ 的路径上边权的最大值，同时这条非树边会使得 $\text{MST}$ 上 $x$ 到 $y$ 的路径上的树边的答案不能超过 $z$，这个东西显然是能树剖维护的，但是由于路径修改都在查询之前，所以我们可以在倍增数组上打个 $\text{tag}$，最后将 $\text{tag}$ 下放即可，时间复杂度 $O(m\log m)$。

# Code
```c++
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
//#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
using namespace std;
//using namespace atcoder;
const int N=1e5+1,M=1e6,inf=1e9;
int n,m,ans[M],fa[N][17];
int f[N][17],g[N][17];
int dep[N],Fa[N];
vector<P> G[N];

int read() {
	int x=0; bool f=true; char c=0;
	while (!isdigit(c) ) f&=(c!='-'),c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return f?x:-x;
}
struct edge
{
	int x,y,z,id; bool use;
	bool operator <(edge o)const {
		return z<o.z;
	}
}e[M];

void kruskal()
{
	auto find=[&](auto &&self,int x)->int
	{ return Fa[x]^x?Fa[x]=self(self,Fa[x]):x; };
	sort(e,e+m); for (int i=1;i<=n;i++) Fa[i]=i;
	for (int i=0;i<m;i++) if (find(find,e[i].x)^find(find,e[i].y) )
	G[e[i].x].push_back({e[i].y,e[i].z}),G[e[i].y].push_back({e[i].x,e[i].z}),
	Fa[find(find,e[i].x)]=find(find,e[i].y),e[i].use=true;
}
void dfs(int u) {
	dep[u]=dep[fa[u][0] ]+1; for (int i=1;i<17;i++)
	fa[u][i]=fa[fa[u][i-1] ][i-1],f[u][i]=max(f[u][i-1],f[fa[u][i-1] ][i-1]);
	for (auto [v,w]:G[u]) if (v^fa[u][0]) fa[v][0]=u,f[v][0]=w,dfs(v);
}
int QAQ(int x,int y,int z)
{
	int res=0; if (dep[x]>dep[y]) swap(x,y);
	for (int i=16;~i;i--) if (dep[x]<=dep[fa[y][i] ])
	g[y][i]=min(g[y][i],z),res=max(res,f[y][i]),y=fa[y][i];
	if (x==y) return res;
	for (int i=16;~i;i--) if (fa[x][i]^fa[y][i])
	g[x][i]=min(g[x][i],z),g[y][i]=min(g[y][i],z),
	res=max({res,f[x][i],f[y][i]}),x=fa[x][i],y=fa[y][i];
	g[x][0]=min(g[x][0],z),g[y][0]=min(g[y][0],z);
	return max({res,f[x][0],f[y][0]});
}
main()
{
	n=read(),m=read();
	for (int i=0;i<m;i++)
	e[i]={read(),read(),read(),i,false};
	memset(g,0x3f,sizeof g),kruskal(),dfs(1);
	for (int i=0;i<m;i++) if (!e[i].use)
	ans[e[i].id]=QAQ(e[i].x,e[i].y,e[i].z);
	for (int j=16;j;j--)
		for (int i=1;i<=n;i++)
			g[i][j-1]=min(g[i][j-1],g[i][j]),
			g[fa[i][j-1] ][j-1]=min(g[fa[i][j-1] ][j-1],g[i][j]);
	
	for (int i=0;i<m;i++) if (e[i].use) {
		int x=e[i].x,y=e[i].y;
		if (dep[x]<dep[y]) swap(x,y);
		ans[e[i].id]=min(g[x][0],inf);
	}
	for (int i=0;i<m;i++)
	printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：TruchyR (赞：0)

讲个笑话，这三题被放在了动态规划练习里面。  

### 简单版 CF1184E1
首先把最小生成树跑一遍。

然后假设我们选上了第一条边（不算代价），再跑一遍最小生成树。  

两次结果的差就是第一条边的最大权值。  

注意如果第一条边是割边那它可以取任意值。  

### 中等版 CF1184E2
所有要计算的边都不在最小生成树上。  

对于每条边单独考虑，如果在最小生成树上再选上这条边，需要**在组成的环中**扣去权值最大的边让总权值最小。  

第二次结果中把那条边不计代价，那么那条边的最大值就是两次结果之差。  

那么如何求**加上一条边后组成的环**中的最大权值呢？  

考虑倍增，那么这个环就可以拆成两端到最近公共祖先的两条链。   

### 困难版 CF1184E3
还是做最小生成树以及倍增，树外的边在上文讨论过了。  

对于每条树边分别考虑，发现这条边割掉后树不连通，需要加一条**权值最小的满足要求的边**重新连接起来。  

考虑每条树外的边可以满足哪些树边的要求：  

容易发现，一条树外边满足树边的要求当且仅当树边在书外边两端点的路径上。  

那么只需要对于书外边更新树内边的答案即可。

这里使用了树链剖分解决这个问题。

困难版代码如下，可能有点乱：  

```cpp
#include<bits/stdc++.h>
#define MX 100005
#define INF 1000000000
#define K 17
using namespace std;
int read();
int nw[MX],fa[MX],son[MX],dep[MX],frt[MX],t[MX*4],siz[MX]; 
int n,m,dfn,res[MX*10],f[K][MX],mx[K][MX];
vector<int> v[MX];
struct eg{int a,b,w,id,cse;}e[MX*10];
bool cmp(eg X,eg Y){return X.w<Y.w;}
int find(int i){return fa[i]=(fa[i]==i?i:find(fa[i]));}
void bd(int k,int l,int r);
int sum(int k,int l,int r,int x);
void cge(int k,int l,int r,int x,int y,int v);
void linkMin(int b,int c,int d){
	while(frt[b]!=frt[c]){
		if(dep[frt[b]]<dep[frt[c]]){swap(b,c);}
		cge(1,1,n,nw[frt[b]],nw[b],d);
		b=fa[frt[b]];
	}
	if(dep[b]>dep[c]){swap(b,c);}
	cge(1,1,n,nw[b],nw[c],d);
}
int dfs1(int t){
	int Mx=0,mxid=0,sm=1;
	for(auto o:v[t]){
		int i=e[o].a+e[o].b-t,w=e[o].w;
		if(i==fa[t]){continue;}
		fa[i]=t;dep[i]=dep[t]+1;
		f[0][i]=t;mx[0][i]=w;
		int sz=dfs1(i);sm+=sz;
		if(sz>Mx){Mx=sz;mxid=i;}
	} 
	son[t]=mxid;
	return siz[t]=sm;
}
void dfs2(int t,int top){
	nw[t]=++dfn;
	frt[t]=top;
	if(!son[t]){return;}
	dfs2(son[t],top);
	for(auto o:v[t]){
		int i=e[o].a+e[o].b-t;
		if(i==fa[t]){continue;}
		if(i==son[t]){continue;}
		dfs2(i,i);
	} 
}
int solve1(int id){
	int a=e[id].a,b=e[id].b,w=e[id].w;
	if(dep[a]<dep[b]) swap(a,b);
	int tA=a,tB=b;
	int dc=dep[a]-dep[b],res=0;
	for(int i=K-1;i>=0;i--){
		if(dc&(1<<i)){
			res=max(res,mx[i][a]);
			a=f[i][a];
		}
	}
	if(a==b){
		dc--,a=tA;
		for(int i=K-1;i>=0;i--){
			if(dc&(1<<i))
				a=f[i][a];
		}linkMin(tA,a,w);
		return res;
	}
	for(int i=K-1;i>=0;i--){
		if(f[i][a]!=f[i][b]){
			res=max(res,max(mx[i][a],mx[i][b]));
			a=f[i][a],b=f[i][b];
		}
	}
	linkMin(tA,a,w);linkMin(tB,b,w);
	res=max(res,max(mx[0][a],mx[0][b]));
	return res;
}
int solve2(int id){
	int a=e[id].a,b=e[id].b;
	if(dep[a]<dep[b]) swap(a,b);
	return sum(1,1,n,nw[a]);
}
signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){fa[i]=i;}
	for(int i=1;i<=m;i++){
		e[i].a=read();e[i].b=read();
		e[i].w=read();e[i].id=i;
	}sort(e+1,e+1+m,cmp);
	for(int i=1;i<=m;i++){
		int a=find(e[i].a),b=find(e[i].b);
		if(a==b) continue;
		fa[a]=b;
		v[e[i].a].push_back(i);
		v[e[i].b].push_back(i);
		e[i].cse=1;
	}
	for(int i=1;i<=n;i++) fa[i]=0;
	fa[1]=-1,dep[1]=1;
	dfs1(1);dfs2(1,1);bd(1,1,n);
	for(int i=1;i<K;i++){
		for(int j=1;j<=n;j++){
			f[i][j]=f[i-1][f[i-1][j]];
			mx[i][j]=max(mx[i-1][j],mx[i-1][f[i-1][j]]);
		}
	}
	for(int i=1;i<=m;i++) if(!e[i].cse) res[e[i].id]=solve1(i);
	for(int i=1;i<=m;i++) if( e[i].cse) res[e[i].id]=solve2(i);
	for(int i=1;i<=m;i++){printf("%d\n",res[i]);}
	return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}
void bd(int k,int l,int r){
	if(l==r){
		t[k]=INF;
		return;
	}
	int mid=(l+r)/2;
	bd(k*2,l,mid);
	bd(k*2+1,mid+1,r);
	t[k]=min(t[k*2],t[k*2+1]);
}
int sum(int k,int l,int r,int x){
	if(x==l && x==r){return t[k];}
	int m=(l+r)/2;
	if(x<=m) return min(t[k],sum(k*2,l,m,x));
	else return min(t[k],sum(k*2+1,m+1,r,x));
}
void cge(int k,int l,int r,int x,int y,int v){
	if(x<=l && y>=r){t[k]=min(t[k],v);return;}
	int m=(l+r)/2;
	if(x<=m) cge(k*2,l,m,x,y,v);
	if(y>m) cge(k*2+1,m+1,r,x,y,v);
}
```

---

## 作者：SoyTony (赞：0)

易、中、难三个版本中，主要是要懂得完整难版的做法（另两题的做法也会提到）
# easy version
只询问 $1$ 条边，可以二分这条边的值，每次检验用 $\text{Kruskal}$ 最小生成树检验。

注意这里边排序的方式应当是以边权升序为第一关键字，以边的编号升序为第二关键字。

例如存在边 $(1,2,3),(1,3,4),(2,3,3)$，这里的第一条边 $(1,2,3)$ 存在于一种最小生成树中，但是不按照编号排序可能使得我们得到的最小生成树不是包含第一条边的。

时间复杂度：$O(m\log m\log a)$，只修改一条边权值每次冒泡一下也可以快一点？
# medium version
询问所有非树边。

可以画出这个无向图以及其最小生成树，发现当我们将一条非树边变成树边时，其与树形成的一个环就要断开一条边，那么当这条边权值大于等于非树边权值时，也就可以替换了。

于是对于非树边要查询的是：其在树上对应的路径中权值最大值。

静态问题，树链剖分 + $\text{ST}$ 表即可解决问题，时间复杂度：$O(m
\log m+m\log n)$
# hard version
基于上一题的做法，需要处理树边。

发现非树边要考虑的是对应树上路径的树边，那么树边考虑的就是能覆盖它的非树边，换言之是与其形成环的非树边。

需要查询：与这条树边能形成环的非树边中的最小值。

区间取 $\min$ 操作是在钓鱼，中间不查询，于是直接权值从大到小排序改成区间赋值，线段树解决。

时间复杂度：$O(m\log m+m\log^2 n)$

# 本题代码

```cpp
int n,m;
struct SegmentTree{
    #define mid ((l+r)>>1)
    #define lson rt<<1,l,mid
    #define rson rt<<1|1,mid+1,r
    int val[maxn<<2];
    void build(int rt,int l,int r){
        val[rt]=-1;
        if(l==r){
            val[rt]=1e9;
            return;
        }
        build(lson),build(rson);
    }
    inline void push_down(int rt){
        if(val[rt]!=-1){
            val[rt<<1]=val[rt<<1|1]=val[rt];
            val[rt]=-1;
        }
    }
    void update(int rt,int l,int r,int pl,int pr,int k){
        if(pl<=l&&r<=pr){
            val[rt]=k;
            return;
        }
        push_down(rt);
        if(pl<=mid) update(lson,pl,pr,k);
        if(pr>mid) update(rson,pl,pr,k);
    }
    int query(int rt,int l,int r,int p){
        if(l==r) return val[rt];
        push_down(rt);
        if(p<=mid) return query(lson,p);
        else return query(rson,p);
    }
    #undef mid
    #undef lson
    #undef rson
}S;
struct Tree{
    struct G_Edge{
        int u,v,w,id;
        bool tag;
    }GE[maxm];
    int bel[maxn];
    int find(int x){
        if(x==bel[x]) return x;
        else return bel[x]=find(bel[x]);
    }
    struct T_Edge{
        int v,w;
        T_Edge()=default;
        T_Edge(int v_,int w_):v(v_),w(w_){}
    };
    vector<T_Edge> E[maxn];
    inline void add_edge(int u,int v,int w){
        E[u].push_back(T_Edge(v,w));
    }
    inline void Krusal(){
        sort(GE+1,GE+m+1,[&](G_Edge x,G_Edge y){
            return x.w<y.w;
        });
        for(int i=1;i<=n;++i) bel[i]=i;
        int cnt=0;
        for(int i=1;i<=m;++i){
            int u=GE[i].u,v=GE[i].v,w=GE[i].w;
            int fu=find(u),fv=find(v);
            if(fu==fv) continue;
            else{
                bel[fv]=fu;
                GE[i].tag=true;
                add_edge(u,v,w);
                add_edge(v,u,w);
                // printf("%d<->%d %d\n",u,v,w);
                ++cnt;
                if(cnt==n-1) break;
            }
        }
    }
    int fa[maxn],dep[maxn],siz[maxn],son[maxn],val[maxn];
    int top[maxn],dfn[maxn],dfncnt;
    int mx[maxn][18];
    int ans[maxm];
    void dfs1(int u,int f,int d){
        fa[u]=f,dep[u]=d,siz[u]=1;
        int maxson=-1;
        for(T_Edge e:E[u]){
            int v=e.v,w=e.w;
            if(v==f) continue;
            val[v]=w;
            dfs1(v,u,d+1);
            siz[u]+=siz[v];
            if(siz[v]>maxson) maxson=siz[v],son[u]=v;
        }
    }
    void dfs2(int u,int t){
        top[u]=t,dfn[u]=++dfncnt;
        mx[dfn[u]][0]=val[u];
        if(!son[u]) return;
        dfs2(son[u],t);
        for(T_Edge e:E[u]){
            int v=e.v;
            if(v==fa[u]||v==son[u]) continue;
            dfs2(v,v);
        }
    }
    inline void build_st(){
        mx[1][0]=0;
        for(int k=1;k<=17;++k){
            for(int i=1;i+(1<<k)-1<=n;++i){
                mx[i][k]=max(mx[i][k-1],mx[i+(1<<(k-1))][k-1]);
            }
        }
    }
    inline int query_st(int l,int r){
        int k=log2(r-l+1);
        return max(mx[l][k],mx[r-(1<<k)+1][k]);
    }
    inline int query(int u,int v){
        int res=0;
        while(top[u]!=top[v]){
            if(dep[top[u]]>dep[top[v]]) swap(u,v);
            res=max(res,query_st(dfn[top[v]],dfn[v]));
            v=fa[top[v]];
        }
        if(dep[u]>dep[v]) swap(u,v);
        if(u!=v) res=max(res,query_st(dfn[u]+1,dfn[v]));
        return res;
    }
    inline void update(int u,int v,int k){
        while(top[u]!=top[v]){
            if(dep[top[u]]>dep[top[v]]) swap(u,v);
            S.update(1,1,n,dfn[top[v]],dfn[v],k);
            v=fa[top[v]];
        }
        if(dep[u]>dep[v]) swap(u,v);
        if(u!=v) S.update(1,1,n,dfn[u]+1,dfn[v],k);
    }
    inline void solve(){
        for(int i=1;i<=m;++i){
            GE[i].u=read(),GE[i].v=read(),GE[i].w=read(),GE[i].id=i;
            GE[i].tag=false;
            ans[i]=1e9;
        }
        Krusal();
        dfs1(1,0,0);
        dfs2(1,1);
        build_st();
        S.build(1,1,n);
        for(int i=1;i<=m;++i) ans[i]=1e9;
        for(int i=m;i>=1;--i){
            int u=GE[i].u,v=GE[i].v,w=GE[i].w,id=GE[i].id;
            if(!GE[i].tag){
                ans[id]=query(u,v);
                update(u,v,w);
            }
        }
        for(int i=1;i<=m;++i){
            int u=GE[i].u,v=GE[i].v,w=GE[i].w,id=GE[i].id;
            if(GE[i].tag){
                if(dep[u]>dep[v]) swap(u,v);
                ans[id]=S.query(1,1,n,dfn[v]);
            }
        }
        for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
    }
}T;
int main(){
    n=read(),m=read();
    T.solve();
    return 0;
}
```

---

