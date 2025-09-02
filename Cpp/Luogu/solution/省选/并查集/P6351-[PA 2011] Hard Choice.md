# [PA 2011] Hard Choice

## 题目描述

有一个 $n$ 个点，$m$ 条边的无向图。

有 $q$ 次询问，每次询问包含一个字符 $opt$ 和两个整数 $x,y$。

若 $opt$ 为 $Z$，表示一次删除操作，删去边 $x,y$，保证 $x,y$ 这条边之前没有被删除，但不保证图上存在边（也就是说，可能会删去所有的边）。

若 $opt$ 为 $P$，表示一次询问，询问 $x,y$ 之间是否有两条完全不同的路径，这里的完全不同指没有经过相同的边，但可以经过相同的点。

## 说明/提示

$2\leq n\leq 10^5$，$1\leq m,q\leq 10^5$，保证输入数据合法且不存在重边和自环。

## 样例 #1

### 输入

```
7 8 7
1 2
1 3
1 4
2 3
3 4
3 7
7 4
5 6
Z 1 4
P 1 3
P 2 4
Z 1 3
P 1 3
Z 6 5
P 5 6
```

### 输出

```
TAK
TAK
NIE
NIE```

# 题解

## 作者：Reunite (赞：14)

早早地写出了全线性做法，因为要放模拟赛没挂题解。确定性线性做法最早于我于 $2024.8.12$ 提出。

先以每条边被删除的时间从后到前的顺序建出最小生成树，对于一个询问 $(u,v)$，把所有没被删的边在生成树上做链覆盖，若 $u,v$ 之间所有的树边都被覆盖 $\ge 2$ 次，那么 $u,v$ 之间有两条边完全不同的路径。

简单证明一下，因为是最小生成树，如果有树边没覆盖，那 $u,v$ 之间根本就不连通；如果有树边被覆盖仅 $1$ 次，那不可能是非树边覆盖到了它，只能是它自己覆盖了自己，否则可以调整说明最小生成树不合法，此时该边称为瓶颈，不存在两条边完全不同路径；否则 $u,v$ 之间一定由若干环拼成，一定可以找到两条边完全不同的路径。

到这里，有一个最朴素的 $O(n\log^2 n)$ 的做法，即求出最小生成树后，树剖一下，线段树维护区间加，区间最小值，每次暴力覆盖和询问。

但是上面的做法是没有什么前途的，注意到我们做链覆盖和链查询，最后只是为了比较链上最小覆盖次数与 $2$ 之间的大小关系，用这些数据结构很浪费。

换一种思考方式，该问题等价于我们倒着做，每一条边的存在时间是一段后缀，每次用边去做链覆盖时，如果一条树边被覆盖次数达到 $2$，就在新图上加入，询问等价于查询 $u,v$ 之间是否连通。而这些都可以用一个并查集去维护，并查集维护树上覆盖次数 $\ge 2$ 的边的连通块，每次覆盖暴力向上跳连通块，恰使得一条边达到 $2$ 时就把并查集缩起来，询问也只需在这个并查集上查询即可。

因为每条边最多只被覆盖 $2$ 次，因此后面这些复杂度是 $O(n)$。前面的最小生成树不需要排序，先考虑加入没被删除的边，然后按照删除顺序依次考虑加入即可。总复杂度 $O(n)$，最优解遥遥领先。由于 vector 常数较大，建议手写链表。

这个题很不爽的是给删除的边是以端点给出的，还要写哈希或者 umap。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

int n,m,q,tm,cnt;
int f[2000005];
int h[2000005];
int hd[2000005];
int fa[2000005];
int it[2000005];
int dep[2000005];
int dfn[2000005];
int out[2000005];
bool del[2000005];
struct node{int op,x,y;};
node e[2000005];
node g[2000005];
node opt[2000005];
bool ans[2000005];
unordered_map <long long,int> mp;

inline void add(int u,int v,int id){
    g[++cnt]={v,hd[u],id},hd[u]=cnt;
    g[++cnt]={u,hd[v],id},hd[v]=cnt;
    return ;
}

inline void in(int &n){
    n=0;
    char c=getchar();
    while(c<'0' || c>'9') c=getchar();
    while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
    return ;
}

inline int Find(int x){return f[x]==x?x:f[x]=Find(f[x]);}

inline void dfs(int u,int f){
    fa[u]=f;
    dep[u]=dep[f]+1;
    dfn[u]=++tm;
    for(int i=hd[u];i;i=g[i].x){
        int v=g[i].op,id=g[i].y;
        if(v==f) continue;
        it[v]=id;
        dfs(v,u);
    }
    out[u]=tm;
    return ;
}

inline void Cover(int u,int v){
    int l=min(dfn[u],dfn[v]),r=max(dfn[u],dfn[v]);
    int pos=Find(u);
    while(dfn[pos]>l||out[pos]<r){
        h[it[pos]]++;
        if(h[it[pos]]==2) f[pos]=Find(fa[pos]);
        pos=Find(fa[pos]);
    }
    pos=Find(v);
    while(dfn[pos]>l||out[pos]<r){
        h[it[pos]]++;
        if(h[it[pos]]==2) f[pos]=Find(fa[pos]);
        pos=Find(fa[pos]);
    }
    return ;
}

int main(){
    in(n),in(m),in(q);
    for(int i=1;i<=m;i++){
        int u,v;
        in(u),in(v);
        mp[1ll*min(u,v)*n+max(u,v)]=i;
        e[i]={1,u,v};
    }
    for(int i=1;i<=q;i++){
        char c[3];
        scanf("%s",c+1);
        if(c[1]=='Z'){
            int u,v;
            in(u),in(v);
            u=mp[1ll*min(u,v)*n+max(u,v)];
            del[u]=1;
            opt[i]=e[u];
        }
        else{
            int u,v;
            in(u),in(v);
            opt[i]={2,u,v};
        }
    }
    int tt=0;
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=m;i++){
        if(del[i]) continue;
        int u=Find(e[i].x),v=Find(e[i].y);
        if(u!=v){
            f[u]=v;
            add(e[i].x,e[i].y,++tt);
        }
    }
    for(int i=q;i>=1;i--)
        if(opt[i].op==1){
            int u=Find(opt[i].x),v=Find(opt[i].y);
            if(u!=v){
                f[u]=v;
                add(opt[i].x,opt[i].y,++tt);
            }
        }
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i,0);
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=m;i++) if(!del[i]) Cover(e[i].x,e[i].y);
    tt=0;
    for(int i=q;i>=1;i--){
        if(opt[i].op==1) Cover(opt[i].x,opt[i].y);
        else ans[++tt]=(Find(opt[i].x)==Find(opt[i].y));
    }
    for(int i=tt;i>=1;i--) puts(ans[i]?"TAK":"NIE");

    return 0;
}
```

---

## 作者：_AyachiNene (赞：6)

不用 Lct 的做法。
# 思路：
首先发现要让两个点有至少两条不同路径，这两个点必须在一个边双内，题目转化为删边和判断两个点是否在一个边双内。发现删边难以处理，可以把操作离线下来，倒序做加边。考虑如何加边，容易想到可以用并查集 dsu 暴力合并，再用一个并查集维护边双。加边时，如果没有构成环，显然直接加进去，并把小的子树重构一下，维护深度和父亲，重构每个边双内深度最小的点，为等下跳链做准备。如果构成了环，显然环上的点就构成了一个边双，直接用并查集合并两个点的路径上的所有边双，过程就和 Lca 差不多，把最小深度大的边双向上合并，合并到两个边双合并在一起就行了。发现每个点最多被加入一次边双，所以复杂度是没问题的。查询没什么好说的，直接在并查集上查就行了。复杂度 $O(n \log n \alpha(n))$。赛时唐了还写了个倍增，其实有线性做法，但我太菜了不会。
# Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+(c^48);c=getchar();}
	return res*f;
}
void write(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
struct node
{
	int nxt,to;
}e[1000005<<1];
int head[1000005],cnt_edge;
void add_edge(int u,int v)
{
	e[++cnt_edge].to=v;
	e[cnt_edge].nxt=head[u];
	head[u]=cnt_edge;
}
int n,m,q;
struct que
{
	int op,u,v;
}a[1000005<<1],tmp[1000005<<1];
int cnt;
int vis[1000005];
int ans[1000005<<1];
struct Nene
{
	int f[1000005],siz[1000005];
	int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
}ft,fc;
int dep[1000005];
int f[1000005];
pair<int,int>mn[1000005];
void dfs(int u,int fa)
{
	f[u]=fa;
	dep[u]=dep[fa]+1;
	mn[fc.find(u)]={1e9,0};
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u);
	}
	mn[fc.find(u)]=min(mn[fc.find(u)],{dep[u],u});
}
inline void mergec(int u,int v)
{
	int x=fc.find(u),y=fc.find(v);
	if(x==y) return;
	if(fc.siz[x]<fc.siz[y]) swap(x,y);
	fc.siz[x]+=fc.siz[y];fc.f[y]=x;
	mn[x]=min(mn[x],mn[y]);
}
inline void update(int x,int y)
{
	while(fc.find(x)!=fc.find(y))
	{
		if(mn[fc.find(x)].first<mn[fc.find(y)].first) swap(x,y);
		int nxt=f[mn[fc.find(x)].second];
		mergec(x,nxt);
	}
}
void merge(int x,int y)
{
	int fx=ft.find(x),fy=ft.find(y);
	if(fx==fy) 
	{
		update(x,y);
		return;
	}
	add_edge(x,y);add_edge(y,x);
	if(ft.siz[fx]<ft.siz[fy]) swap(fx,fy),swap(x,y);
	ft.f[fy]=fx;ft.siz[fx]+=ft.siz[fy];
	dfs(y,x);
}
map<int,int>id[114514];
int main()
{
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++) ft.f[i]=fc.f[i]=i,ft.siz[i]=fc.siz[i]=dep[i]=1,mn[i]={1,i};
	for(int i=1;i<=m;i++) tmp[i].u=read(),tmp[i].v=read(),tmp[i].op=1,id[tmp[i].u][tmp[i].v]=id[tmp[i].v][tmp[i].u]=i;
	for(int i=1;i<=q;i++)
	{
		char c;
		cin>>c;
		tmp[i+m].op=(c=='Z'?1:2),tmp[i+m].u=read(),tmp[i+m].v=read();
		if(tmp[i+m].op==1) vis[id[tmp[i+m].u][tmp[i+m].v]]=1;
	}
	for(int i=1;i<=m;i++) if(!vis[i]) a[++cnt]=tmp[i]; 
	for(int i=q;i;i--) a[++cnt]=tmp[i+m];
	memset(ans,-1,sizeof ans);
	for(int i=1;i<=cnt;i++)
	{
		if(a[i].op==1) merge(a[i].u,a[i].v);
		else ans[i]=fc.find(a[i].u)==fc.find(a[i].v);
	}
	for(int i=cnt;i;i--)
		if(ans[i]!=-1) puts((ans[i]?"TAK":"NIE"));
	return 0;
}

```

---

## 作者：STARSczy (赞：6)

交一发完全平衡二叉树的题，严格单 log。

容易想到倒着做，将删除改为加入。

当图为一棵树，那么每条边都是一条割边。当在加入一条边时，这条边的两端点的路径都要变为非割边。容易想到当 u 到 v 中的每一条边都不是割边时，即可经过两条边不相交路径。

将不被询问的边，和被询问的边按照顺序加入生成树，即当这条边是连接两个不同连通块时加入树边，权值为零，否则将路径上的所有边边权设为一。

使用双 log 树剖完全可过此题，但是由于我们模拟赛的范围是 $10^6$，所以上述做法显然不行。可以使用完全平衡二叉树求解。

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/rope>
#define rep(i,l,r) for(int i=(l),i##end=(r);i<=i##end;++i)
#define per(i,r,l) for(int i=(r),i##end=(l);i>=i##end;--i)
#define int long long
#define double long double
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define rbtree(way) tree<way,null_type,less<way>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
const int maxn=1e5+10,maxm=1e6+10,mod=998244353,inf=1e12;

int n,m,q,tid,u[maxn],v[maxn],fl[maxn],qs1[maxn],qs2[maxn],f[maxn],ans[maxn];
int ett,rt[maxn],ls[maxn],rs[maxn],a[maxn],s[maxn],hv[maxn];
int fa[maxn],sz[maxn],lt[maxn],hs[maxn],dep[maxn];
vector<int> e[maxn];
map<pii,int> t;
char opt[maxn];

int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
void dfs(int x){
	sz[x]=1;
	for(int i:e[x]) if(i!=fa[x])
		fa[i]=x,dep[i]=dep[x]+1,dfs(i),sz[x]+=sz[i],sz[i]>sz[hs[x]]?hs[x]=i:0;
}
void dfs1(int x){
	!lt[x]?lt[x]=x:0,hs[x]?lt[hs[x]]=lt[x]:0;
	for(int i:e[x]) if(i!=fa[x]) dfs1(i);
}
int build(int l,int r){
	if(l>r) return 0;
	int x=++ett;
	return hv[x]=1+hv[ls[x]=build(l,(l+r>>1)-1)]+hv[rs[x]=build((l+r>>1)+1,r)],x;
}
void tradd(int x,int l,int r){
	if(l>r||!x) return;
	if(s[x]||r-l+1==hv[x]){
		a[x]=s[x]=1;
		return;
	}
	if(r<=hv[ls[x]]) tradd(ls[x],l,r);
	else if(l>hv[ls[x]]+1) tradd(rs[x],l-hv[ls[x]]-1,r-hv[ls[x]]-1);
	else tradd(ls[x],l,hv[ls[x]]),tradd(rs[x],1,r-hv[ls[x]]-1),a[x]=1;
	s[x]=a[x]&s[ls[x]]&s[rs[x]];
}
bool trquery(int x,int l,int r){
	if(l>r||!x||s[x]) return 1;
	if(r-l+1==hv[x]) return s[x];
	if(r<=hv[ls[x]]) return trquery(ls[x],l,r);
	else if(l>hv[ls[x]]+1) return trquery(rs[x],l-hv[ls[x]]-1,r-hv[ls[x]]-1);
	return trquery(ls[x],l,hv[ls[x]])&trquery(rs[x],1,r-hv[ls[x]]-1)&a[x];
}
void add(int u,int v){
	for(;lt[u]!=lt[v];dep[lt[u]]<dep[lt[v]]?swap(u,v),0:0,
		tradd(rt[lt[u]],1,dep[u]-dep[lt[u]]+1),u=fa[lt[u]]);
	dep[u]>dep[v]?swap(u,v),0:0,tradd(rt[lt[u]],dep[u]-dep[lt[u]]+2,dep[v]-dep[lt[v]]+1);
}
bool query(int u,int v){
	for(;lt[u]!=lt[v];u=fa[lt[u]]){
		dep[lt[u]]<dep[lt[v]]?swap(u,v),0:0;
		if(!trquery(rt[lt[u]],1,dep[u]-dep[lt[u]]+1)) return 0;
	}
	return dep[u]>dep[v]?swap(u,v),0:0,trquery(rt[lt[u]],dep[u]-dep[lt[u]]+2,dep[v]-dep[lt[v]]+1);
}

signed main(){
//	freopen("graph.in","r",stdin),freopen("graph.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q,s[0]=1;
	rep(i,1,n) f[i]=i;
	rep(i,1,m) cin>>u[i]>>v[i],u[i]>v[i]?swap(u[i],v[i]),0:0,t[{u[i],v[i]}]=i;
	rep(i,1,q) cin>>opt[i]>>qs1[i]>>qs2[i],opt[i]=='Z'?
		qs1[i]>qs2[i]?swap(qs1[i],qs2[i]),0:0,fl[qs1[i]=t[{qs1[i],qs2[i]}]]=1:0;
	rep(i,1,m) !fl[i]&&find(u[i])!=find(v[i])?
		e[u[i]].pb(v[i]),e[v[i]].pb(u[i]),f[f[u[i]]]=f[v[i]]:0;
	per(i,q,1) opt[i]=='Z'&&qs1[i]?find(u[qs1[i]])!=find(v[qs1[i]])?
		f[f[u[qs1[i]]]]=f[v[qs1[i]]],e[u[qs1[i]]].pb(v[qs1[i]]),e[v[qs1[i]]].pb(u[qs1[i]]),0:0:0;
	rep(i,1,n) !fa[i]?dfs(i),dfs1(i),0:0,f[i]=i;
	rep(i,1,n) if(!hs[i]) rt[lt[i]]=build(1,dep[i]-dep[lt[i]]+1);
	rep(i,1,m) !fl[i]?find(u[i])==find(v[i])?add(u[i],v[i]),0:f[f[u[i]]]=f[v[i]]:0;
	per(i,q,1) if(opt[i]=='P') ans[i]=find(qs1[i])==find(qs2[i])&&query(qs1[i],qs2[i]);
	else qs1[i]?find(u[qs1[i]])==find(v[qs1[i]])?
		add(u[qs1[i]],v[qs1[i]]),0:f[f[u[qs1[i]]]]=f[v[qs1[i]]]:0;
	rep(i,1,q) if(opt[i]=='P') cout<<(ans[i]?"TAK\n":"NIE\n");
	return 0;
}
```

---

## 作者：Begemot (赞：2)

**本题解介绍的做法不需要会 LCT、树链剖分、线段树等技术，只要会并查集即可。**

首先正难则反转化一下，把删边变成加边。

询问 $x,y$ 之间是否有两条完全不同的路径等价于询问 $x,y$ 是否在一个边双连通分量中。

割边连接不同的边双连通分量，如果把每个边双连通分量缩成一个点，图上只保留为割边的边，那么图将被转化成一个无环图（森林）。

我们从删到最后的图开始，一步一步加边，对于每次加的边 $(a,b)$:

- 如果 $a$ 和 $b$ 已经位于同一个双连通分量中了

  那么不会有任何变化。
  
- 如果 $a$ 和 $b$ 位于不同的双连通分量中，且缩点后位于不同的树上

  那么 $(a,b)$ 就是一个新的割边，而且两棵树被合并成一颗。
  
- 如果 $a$ 和 $b$ 位于不同的双连通分量中，但是缩点后位于同一颗树上

  那么 $(a,b)$ 和一些旧的割边一起形成了一个环，生成的环要被压缩成一个新的双连通分量。

那么用什么结构来维护森林呢？答案是并查集即可，我们来看看对于每个操作在并查集上如何维护：

- 检查两个顶点是否位于同一个树/双连通分量中，普通并查集查找就可以了

- 合并两颗树，因为有可能 $(a,b)$ 都不是树的根，所以要让两棵树中的一颗换根。

  然而把一棵树的根从 $u$ 换到 $v$ 需要访问从 $u$ 到 $v$ 路径上的所有点，把他们的父亲重新定义到相反的方向，而且并查集的祖先也要更改。

  因此换根的时间复杂度估计是 $O(h)$，$h$ 是树的高度，更糟糕的估计是 $O(size)$，$size$ 是树的大小。

  我们用一种标准技术处理，每次合并，给较小的树换根。最坏的情况是两个大小相同的树合并，但这种合并每次生成一个大小两倍的新树，不会发生很多次。

  总的成本用递归表示：

   $$ T(n) = \max_{k = 1 \ldots n-1} \left\{ T(k) + T(n - k) + O(\min(k, n - k))\right\} $$ 

  $T(n)$ 是生成一个大小为 $n$ 的新树所需要的操作，大小为 $n$ 的新树可以由大小为 $k$ 的树和大小为 $n-k$ 的树合并形成。这个递归是有解的：$T(n) = O(n\log n)$。

  我们要额外维护每棵树的大小，不过这很简单。
  
- 找到加边 $(a,b)$ 形成的环，首先我们要找到 $LCA(a,b)$，因为这个环包括从 $a$ 到 LCA，从 LCA 到 $b$，再从 $b$ 到 $a$。

  找到环后，我们要遍历环，把环压缩成一个点，由于这一步复杂度和环的长度成正比，所以求 LCA 就没必要倍增了，直接朴素求，也是和环的长度成正比。

- 在树中添加环压缩后的新点，压缩要满足树的结构不会变化，所有的父亲指针和两个并查集仍然正确。

  最简单的方法就是把所有点压缩到 LCA 上，LCA 是最高的节点，所以它的父亲指针不变，而在维护双连通分量的并查集中，环中所有的点都指向 LCA。

  为了方便，我们没有按秩合并优化，所以每次询问时间复杂度是 $O(\log n)$，如果用了按秩合并，就能分摊到 $O(1)$，不过这样麻烦一点，需要按秩相应的分配父亲指针。

代码：

```cpp
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
const int MAXN = 2e5 + 5;
using namespace std;
struct Query {
	char opr;
	int x, y;
} query[MAXN];
struct Edge {
	int x, y;
} edge[MAXN];
set<pair<int, int>> s;
int n, m, q, last_visit[MAXN], lca_iteration, dsu_2ecc[MAXN], dsu_tree[MAXN], tree_sz[MAXN], par[MAXN];
vector<string> res;
vector<int> adj[MAXN];
int find_2ecc(int v) {
	if (v == -1) return -1;
	return dsu_2ecc[v] == v ? v : dsu_2ecc[v] = find_2ecc(dsu_2ecc[v]);
}
int find_tree(int v) {
	v = find_2ecc(v);
	return dsu_tree[v] == v ? v : dsu_tree[v] = find_tree(dsu_tree[v]);
}
void init() {
	for (int i = 1; i <= n; ++i) {
		dsu_2ecc[i] = dsu_tree[i] = i;
		tree_sz[i] = 1;
		par[i] = -1;
	}
}
void change_rt(int v) {
	int root = v;
	int child = -1;
	while (v != -1) {
		int p = find_2ecc(par[v]);
		dsu_tree[v] = root;
		par[v] = child;
		child = v;
		v = p;
	}
	tree_sz[root] = tree_sz[child];
}
void merge_cycle(int a, int b) {
    ++lca_iteration;
    vector<int> path_a, path_b;
    int lca = -1;
    while (lca == -1) {
    	if (a != -1) {
    		a = find_2ecc(a);
    		path_a.push_back(a);
    		if (last_visit[a] == lca_iteration) {
    			lca = a;
    			break;
    		}
    		last_visit[a] = lca_iteration;
    		a = par[a];
    	}
    	if (b != -1) {
        	b = find_2ecc(b);
    		path_b.push_back(b);
    		if (last_visit[b] == lca_iteration) {
    			lca = b;
    			break;
    		}
    		last_visit[b] = lca_iteration;
    		b = par[b];		
    	}
    }
    for (int v : path_a) {
    	dsu_2ecc[v] = lca;
    	if (v == lca) break;
    }
    for (int v : path_b) {
    	dsu_2ecc[v] = lca;
    	if (v == lca) break;
    }
}
void add_edge(int a, int b) {
	a = find_2ecc(a), b = find_2ecc(b);
	if (a == b) return;
	int tree_a = find_tree(a), tree_b = find_tree(b);
	if (tree_a != tree_b) {
		if (tree_sz[tree_a] < tree_sz[tree_b]) {
			swap(a, b);
			swap(tree_a, tree_b);
		}
		change_rt(b);
		par[b] = dsu_tree[b] = a;
		tree_sz[tree_a] += tree_sz[b];
	} else {
		merge_cycle(a, b);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m >> q;
	init();
	for (int i = 1; i <= m; ++i) {
		cin >> edge[i].x >> edge[i].y;
		if (edge[i].x > edge[i].y) swap(edge[i].x, edge[i].y);
	}
	for (int i = 1; i <= q; ++i) {
		cin >> query[i].opr >> query[i].x >> query[i].y;
		if (query[i].x > query[i].y) swap(query[i].x, query[i].y);
		if (query[i].opr == 'Z') {
			s.insert({ query[i].x, query[i].y });
		}
	}
	for (int i = 1; i <= m; ++i) {
		if (s.count({ edge[i].x, edge[i].y })) continue;
		add_edge(edge[i].x, edge[i].y);
	}
	for (int i = q; i >= 1; --i) {
		if (query[i].opr == 'Z') {
			add_edge(query[i].x, query[i].y);
		} else {
			res.push_back(find_2ecc(query[i].x) == find_2ecc(query[i].y) ? "TAK" : "NIE");
		}
	}
	reverse(res.begin(), res.end());
	for (string ele : res) cout << ele << endl;
	return 0;
}
```

---

## 作者：meyi (赞：2)

显然用 LCT 动态维护边双联通分量可以通过本题，但码量太大，于是我换了种~~码量更大的~~写法通过了本题。

删边不好处理，正难则反，考虑将询问离线，将删边变为加边，显然先加入的边不会对后加入的边造成影响，于是求出原图以加入时间为关键字的最小生成树，然后树链剖分，加边操作就是将树上两点间路径的边权全部加一，询问操作就是查询树上两点间路径的边权的最小值是否大于或等于二，线段树维护即可。

需要注意的坑点：

- 由于是边权转点权，加边操作时不要给 LCA 对应的边加一。

- 原图可能不连通，kruskal求出的可能是一个森林，要对每棵树跑一遍树链剖分。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=1e5+10;
int m,n,ql;
namespace tree{
	struct edge{
		int to,nxt;
	}e[maxn<<1];
	int hd[maxn],len;
	inline void addedge(int fr,int to){
		e[++len]={to,hd[fr]};
		hd[fr]=len;
	}
	int cnt,dep[maxn],fa[maxn],rev[maxn],seg[maxn],siz[maxn],son[maxn],top[maxn];
	void dfs1(int p,int f){
		dep[p]=dep[f]+1;
		fa[p]=f;
		siz[p]=1;
		for(ri i=hd[p];i;i=e[i].nxt)
			if(e[i].to!=f){
				dfs1(e[i].to,p);
				siz[p]+=siz[e[i].to];
				if(siz[e[i].to]>siz[son[p]])son[p]=e[i].to;
			}
	}
	void dfs2(int p,int k){
		seg[p]=++cnt;
		rev[cnt]=p;
		top[p]=k;
		if(son[p]){
			dfs2(son[p],k);
			for(ri i=hd[p];i;i=e[i].nxt)
				if(!top[e[i].to])
					dfs2(e[i].to,e[i].to);
		}
	}
	struct segment_tree{
		int l,r,v,tag;
	}t[maxn<<2];
	#define ls(p) (p<<1)
	#define rs(p) (p<<1|1)
	inline void push_up(int p){
		t[p].v=min(t[ls(p)].v,t[rs(p)].v);
	}
	inline void push_down(int p){
		if(!t[p].tag)return;
		t[ls(p)].v+=t[p].tag,t[ls(p)].tag+=t[p].tag;
		t[rs(p)].v+=t[p].tag,t[rs(p)].tag+=t[p].tag;
		t[p].tag=0;
	}
	void build(int p,int l,int r){
		t[p].l=l,t[p].r=r;
		if(l==r)return;
		int mid=l+r>>1;
		build(ls(p),l,mid);
		build(rs(p),mid+1,r);
	}
	void modify(int p,int l,int r){
		if(t[p].l>r||l>t[p].r)return;
		if(l<=t[p].l&&t[p].r<=r){
			++t[p].v,++t[p].tag;
			return;
		}
		push_down(p);
		modify(ls(p),l,r);
		modify(rs(p),l,r);
		push_up(p);
	}
	inline void modify_chain(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]])swap(x,y);
			modify(1,seg[top[x]],seg[x]);
			x=fa[top[x]];
		}
		if(x==y)return;
		if(dep[x]>dep[y])swap(x,y);
		modify(1,seg[x]+1,seg[y]);
	}
	int query(int p,int l,int r){
		if(t[p].l>r||l>t[p].r)return INT_MAX;
		if(l<=t[p].l&&t[p].r<=r)return t[p].v;
		push_down(p);
		return min(query(ls(p),l,r),query(rs(p),l,r));
	}
	inline int query_chain(int x,int y){
		ri ret=INT_MAX;
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]])swap(x,y);
			ret=min(ret,query(1,seg[top[x]],seg[x]));
			x=fa[top[x]];
		}
		if(x==y)return ret;
		if(dep[x]>dep[y])swap(x,y);
		return min(ret,query(1,seg[x]+1,seg[y]));
	}
}
namespace MST{
	struct edge{
		int fr,to,tim;
		bool mst;
		inline bool operator<(const edge &k)const{
			return tim<k.tim;
		}
	};
	vector<edge>e;
	struct dsu{
		int fa[maxn];
		inline void init(int siz){for(ri i=1;i<=siz;++i)fa[i]=i;}
		int find(int k){return k==fa[k]?k:fa[k]=find(fa[k]);}
	}d;
	inline void kruskal(){
		d.init(n);
		sort(e.begin(),e.end());
		ri tot=1;
		for(ri i=0;i<e.size();++i){
			ri x=d.find(e[i].fr),y=d.find(e[i].to);
			if(x!=y){
				d.fa[x]=y;
				tree::addedge(e[i].fr,e[i].to);
				tree::addedge(e[i].to,e[i].fr);
				e[i].mst=true;
				if(++tot==n)return;
			}
		}
	}
}
typedef pair<int,int> pii;
map<pii,int>id;
struct qry{
	char op[5];
	int x,y;
}q[maxn];
vector<bool>ans;
int main(){
	scanf("%d%d%d",&n,&m,&ql);
	for(ri i=0;i<m;++i){
		ri x,y;
		scanf("%d%d",&x,&y);
		id[pii(x,y)]=id[pii(y,x)]=MST::e.size();
		MST::e.push_back({x,y});
	}
	for(ri i=1;i<=ql;++i)scanf("%s%d%d",q[i].op,&q[i].x,&q[i].y);
	for(ri i=ql,j=1;i;--i)
		if(*q[i].op=='P')++j;
		else MST::e[id[pii(q[i].x,q[i].y)]].tim=j;
	MST::kruskal();
	for(ri i=1;i<=n;++i)
		if(!tree::top[i]){
			tree::dfs1(i,0);
			tree::dfs2(i,i);
		}
	tree::build(1,1,tree::cnt);
	MST::d.init(n);
	for(ri i=0;i<m;++i)
		if(!MST::e[i].tim){
			ri x=MST::d.find(MST::e[i].fr),y=MST::d.find(MST::e[i].to);
			if(x!=y)MST::d.fa[x]=y;
			tree::modify_chain(MST::e[i].fr,MST::e[i].to);
		}
	for(ri i=ql;i;--i)
		if(*q[i].op=='P'){
			if(MST::d.find(q[i].x)!=MST::d.find(q[i].y))ans.push_back(false);
			else ans.push_back(tree::query_chain(q[i].x,q[i].y)>1);
		}
		else{
			ri x=MST::d.find(q[i].x),y=MST::d.find(q[i].y);
			if(x!=y)MST::d.fa[x]=y;
			tree::modify_chain(q[i].x,q[i].y);
		}
	for(ri i=ans.size()-1;~i;--i)puts(ans[i]?"TAK":"NIE");
	return 0;
}
```


---

## 作者：lhm_ (赞：2)

删边操作不好处理，所以先将操作倒序，将删边转化为加边。

考虑对于两个点的询问，若这两点不连通或这两个点分别处于两个不同的边双连通分量中（两点间存在桥）时，是不满足题目要求的。

可以用$LCT$来维护原图的一个生成树，原先每条边带有边权，若在原图中或加边过程中出现了环，则在树上这两点之间的边全部边权清零。

此时如果对两点之间求路径权值和，若在原图中这两点处在一个环上，那么权值和肯定为$0$，同时用并查集维护连通性，就可以对询问进行回答了。

具体实现看代码吧。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 300010
#define mk make_pair
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,m,qu,tot;
int f[maxn],ans[maxn];
int fa[maxn],ch[maxn][2],rev[maxn],val[maxn],sum[maxn],tag[maxn];
char opt[maxn][2];
map<pair<int,int>,int> mp;
struct edge
{
    int x,y;
}e[maxn],q[maxn];
int find(int x)
{
    return f[x]==x?x:f[x]=find(f[x]);
}
bool check(int x)
{
    return ch[fa[x]][1]==x;
}
void pushup(int x)
{
    sum[x]=val[x]+sum[ch[x][0]]+sum[ch[x][1]];
}
void pushrev(int x)
{
    rev[x]^=1,swap(ch[x][0],ch[x][1]);
}
void pushtag(int x)
{
    tag[x]=1,sum[x]=val[x]=0;
}
void pushdown(int x)
{
    int ls=ch[x][0],rs=ch[x][1];
    if(rev[x]) pushrev(ls),pushrev(rs),rev[x]=0;
    if(tag[x]) pushtag(ls),pushtag(rs),tag[x]=0;
}
bool notroot(int x)
{
    return ch[fa[x]][0]==x||ch[fa[x]][1]==x;
}
void rotate(int x)
{
    int y=fa[x],z=fa[y],k=check(x),w=ch[x][k^1];
    if(notroot(y)) ch[z][check(y)]=x;
    ch[x][k^1]=y,ch[y][k]=w;
    if(w) fa[w]=y;
    fa[x]=z,fa[y]=x;
    pushup(y),pushup(x);
}
void all(int x)
{
    if(notroot(x)) all(fa[x]);
    pushdown(x);
}
void splay(int x)
{
    all(x);
    for(int y;notroot(x);rotate(x))
        if(notroot(y=fa[x]))
            rotate(check(x)^check(y)?x:y);
    pushup(x);
}
void access(int x)
{
    for(int y=0;x;y=x,x=fa[x])
        splay(x),ch[x][1]=y,pushup(x);
}
void makeroot(int x)
{
    access(x),splay(x),pushrev(x);
}
void split(int x,int y)
{
    makeroot(x),access(y),splay(y);
}
void link(int x,int y)
{
	makeroot(x),fa[x]=y;
}
void Link(int x,int y)
{
    f[find(x)]=find(y),val[++tot]=1;
    link(x,tot),link(tot,y);
}
int query(int x,int y)
{
    split(x,y);
    return sum[y];
}
int main()
{
    read(n),read(m),read(qu),tot=n;
    for(int i=1;i<=n;++i) f[i]=i;
    for(int i=1;i<=m;++i)
    {
        read(e[i].x),read(e[i].y);
        if(e[i].x>e[i].y) swap(e[i].x,e[i].y);
    }
    for(int i=1;i<=qu;++i)
    {
        scanf("%s",opt[i]),read(q[i].x),read(q[i].y);
        if(q[i].x>q[i].y) swap(q[i].x,q[i].y);
        if(opt[i][0]=='Z') mp[mk(q[i].x,q[i].y)]=1;
    }
    for(int i=1;i<=m;++i)
    {
        int x=e[i].x,y=e[i].y;
        if(mp.count(mk(x,y))||find(x)==find(y)) continue;
        mp[mk(x,y)]=1,Link(x,y);
    }
    for(int i=1;i<=m;++i)
    {
        int x=e[i].x,y=e[i].y;
        if(mp.count(mk(x,y))) continue;
        split(x,y),pushtag(y);
    }
    for(int i=qu;i;--i)
    {
        int x=q[i].x,y=q[i].y;
        if(opt[i][0]=='Z')
        {
            if(find(x)==find(y)) split(x,y),pushtag(y);
            else Link(x,y);
        }
        else
        {
            ans[i]=query(x,y);
            if(find(x)!=find(y)) ans[i]=1;
        }
    }
    for(int i=1;i<=qu;++i)
    {
        if(opt[i][0]=='P')
        {
            if(ans[i]) puts("NIE");
            else puts("TAK");
        }
    }
    return 0;
}
```

---

## 作者：qzmoot (赞：1)

# 题解：P6351 [PA2011] Hard Choice
## 题目大意
给了你一个无向图，每次要么删除一条边，要么询问你两个点是否在同一个边双内。
## 分析
上来我们就很容易想到一个 $O(NQ)$ 暴力。每次在图上删边，然后跑 tarjan。但是这个复杂度明显不对，于是考虑其他做法。

若两个点在一个边双中，有一个很重要的 trick。我们对这个图生成一个树，然后再把没有加入树的边在这个生成树上进行覆盖，若两个点间的最小覆盖次数大于等于 $2$ 的话。说明这就是一个边双。

这样我们就做到了 $O(N\log^2N)$ 的复杂度，但是我们还可以更优。

我们只在乎一条链上是否有覆盖次数最少的点的次数大于等于 $2$。所以我们的树剖明显有很多次操作都是没有必要的。又因为删除操作我们不是很好处理，每次删除都会导致一些边变成割边，于是我们反向思考，从最后一个操作往前面来考虑，删除就会变成加边操作。每次加的边如果是树边我们就啥都不干，如果不是树边，我们就做类似树剖的方法，将两点之间的链全部都覆盖，然后计入并查集，这样只用查看两点是否在同一连通块就行。

你可能会问覆盖这些链的复杂度不正确吧？不是这样的。我们覆盖一次之后，如果还会路过这，由于我们已经计入并查集的缘故，我们是可以直接跳的顶端来合并的，所以复杂度就是 $O(M)$ 的。

你可能还会问，建树操作需要排序，那复杂度不也会退化吗？其实我们求的不是最小生成树，排序是没有必要的，我们只直接按照一个优先级来建树，如果有边没有删除，那么我们肯定优先连，否则就是按照删除的从后往前的顺序来。这样的话复杂度就是 $O(M)$ 的。

但是这题的操作给出的是两个点，而不是边的编号，导致我们要使用一些奇怪的方法来记录两个点之间的边。

我懒的写哈希之类的方法，于是干脆就用 map，反正 $O(N\log N)$ 能过。
## Code
```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
using namespace std;
const int N=8e5+5,M=1e6+5;
int rd()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9')x=x*10+ch-48,ch=getchar();
	return x*f; 
}
void wr(int x)
{
	if(x<0)
		putchar('-'),x=-x;
	if(x<=9)
		putchar(x+48);
	else
		wr(x/10),putchar(x%10+48);
}
void pt(int x,char en)
{
	wr(x),putchar(en);
}
int n,m,q;
struct node{
	int u,v;
	bool fl,used;
}e[M];
map<pii,int>ma;
struct ask{
	int op,x,y;
	bool ans;
}s[M];
int fa[N];
vector<int>a[N];
void init()
{
	for(int i=1;i<=n;i++)
		fa[i]=i;
}
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]); 
}
void merge(int x,int y)
{
	x=find(x),y=find(y);
	if(x!=y)
		fa[x]=y;
}
int f[N],dep[N];
void dfs(int u,int faa)
{
	f[u]=faa,dep[u]=dep[faa]+1;
	for(auto v:a[u])
	{
		if(v==faa)
			continue;
		dfs(v,u);
	}
}
void upd(int u,int v)
{
	u=find(u),v=find(v);
	while(u!=v)
	{
		if(dep[u]<dep[v])
			swap(u,v);
		merge(u,f[u]);
		u=find(u);
	}
}
int main()
{	
	n=rd(),m=rd(),q=rd();
	for(int i=1;i<=m;i++)
		e[i]=(node){rd(),rd(),0},ma[mp(e[i].u,e[i].v)]=ma[mp(e[i].v,e[i].u)]=i;
	for(int i=1;i<=q;i++)
	{
		char op=getchar();
		while(op==' ' || op=='\n' || op=='\r')
			op=getchar();
		s[i].op=op=='Z'?1:2;
		if(s[i].op==1)
		{
			int u=rd(),v=rd();
			s[i].x=ma[mp(u,v)];
			e[s[i].x].fl=1;
		}
		else
			s[i].x=rd(),s[i].y=rd();
	}
	init();
	int cnt=0;
	for(int i=1;i<=m;i++)
	{
		int fx=find(e[i].u),fy=find(e[i].v);
		if(!e[i].fl && fx!=fy)
			cnt++,fa[fy]=fx,a[e[i].u].pb(e[i].v),a[e[i].v].pb(e[i].u),e[i].used=1;
		if(cnt==n-1)
			break;
	}
	for(int i=q;i>=1;i--)
	{
		if(s[i].op==1)
		{
			int fx=find(e[s[i].x].u),fy=find(e[s[i].x].v);
			if(fx!=fy)
				cnt++,fa[fy]=fx,a[e[s[i].x].u].pb(e[s[i].x].v),a[e[s[i].x].v].pb(e[s[i].x].u),e[s[i].x].used=1;
		}
		if(cnt==n-1)
			break;
	}
	init();
	for(int i=1;i<=n;i++)
		if(!dep[i])
			dfs(i,0);
	for(int i=1;i<=m;i++)
		if(!e[i].used && !e[i].fl)
			upd(e[i].u,e[i].v);
	for(int i=q;i>=1;i--)
	{
		if(s[i].op==2)
			s[i].ans=(find(s[i].x)==find(s[i].y));
		else if(!e[s[i].x].used)
			upd(e[s[i].x].u,e[s[i].x].v);
	}
	for(int i=1;i<=q;i++)
		if(s[i].op==2)
			puts(s[i].ans?"TAK":"NIE");
	return 0;
}
```

---

## 作者：Rem_CandleFire (赞：1)

### 题目大意

删边、查询两点是否有多条路径到达。

### 分析

显然使用**时间回溯**，把删边转换成加边，这样更容易操作。类似的经典题目有[AHOI2005航线规划](https://www.luogu.com.cn/problem/P2542)。

我们以时间为关键字使用 Kruskal 算法建出最小生成树，然后把两个操作转换成树上操作。

- Z 加边 $(x,y)$：树上两点 $x,y$ 的简单路径上的边权 $+1$。
- P 查询 $(x,y)$：求树上两点 $x,y$ 的简单路径上的最小边权，如果大于 $1$ 则输出 TAK，否则输出NLE。

转换后，显然可以使用树链剖分与线段树解决。

### 注意事项

1. 所有需要执行 Z 操作的边按照时间回溯的顺序放最后，其它边按读入顺序排列。
2. 最小生成树一直构造完，可以使用上述需要执行 Z 操作的边，否则会因为加边合并两棵树而引起树剖错乱。
3. 树剖需要边权转点权，有类似题目 [Grass Planting G](https://www.luogu.com.cn/problem/P3038)。

### 一点技巧

在时间回溯后以将边赋予时间权值时（构造生成树之前），可以使用 `map<pair<int,int>,int>` 类型来迅速对边打标记或执行其它操作，在代码中有体现。 

### code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,q,ok[N],ans_cnt;
struct edge{
	int x,y,id,tim;
}e[N],ques[N];
char opt[N];
struct b_c_j{
	int id,rk;
}bcj[N];//其实无需按秩合并
vector<int> g[N];//存生成树
typedef pair<int,int> mpi;
map< mpi,int > ret;//记录编号
bool cmp(edge a,edge b){ return a.tim<b.tim;}
int find(int x)
{
	if(bcj[x].id==x) return x;
	else return bcj[x].id=find(bcj[x].id);
}
void merge(int rx,int ry)//按秩合并
{
	if(bcj[rx].rk<=bcj[ry].rk) bcj[rx].rk+=bcj[ry].rk,bcj[ry]=bcj[rx];
	else bcj[ry].rk+=bcj[rx].rk,bcj[rx]=bcj[ry];
}
void kruskal() 
{
	sort(e+1,e+1+m,cmp);//以时间排序
	for(int i=0;i<=n;i++) bcj[i]={i,1};
	for(int i=1;i<=m;i++)
	{
		int rx=find(e[i].x),ry=find(e[i].y);
		if(rx==ry) continue; 
		merge(rx,ry);
		g[e[i].x].push_back(e[i].y); g[e[i].y].push_back(e[i].x); //add_edge
	}
}
int vis[N],dfn[N],siz[N],hson[N],dep[N],fa[N],top[N],tim;//树剖
void dfs1(int u,int las)
{
	fa[u]=las;
	siz[u]=1; dep[u]=dep[las]+1;
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==las) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[hson[u]]) hson[u]=v;
	}
}
void dfs2(int u,int topf)
{
	dfn[u]=++tim;
	top[u]=topf;
	if(hson[u]) dfs2(hson[u],topf);
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
}
int tr[N<<2],lazy[N<<2];//线段树
void push_down(int k)
{
	lazy[k<<1]+=lazy[k];
	lazy[k<<1|1]+=lazy[k];
	tr[k<<1]+=lazy[k];
	tr[k<<1|1]+=lazy[k];
	lazy[k]=0;
} 
void update(int l,int r,int k,int x,int y)
{
	if(r<x||l>y) return ; 
	if(x<=l&&r<=y)
	{
		lazy[k]++;
		tr[k]++;
		return ;
	}
	push_down(k);
	int mid=(l+r)>>1;
	update(l,mid,k<<1,x,y); update(mid+1,r,k<<1|1,x,y);
	tr[k]=min(tr[k<<1],tr[k<<1|1]);
}
void update_path(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		update(1,n,1,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(x==y) return ;
	if(dfn[x]>dfn[y]) swap(x,y);
	update(1,n,1,dfn[x]+1,dfn[y]);//边权转点权不涉及LCA
}
int query(int l,int r,int k,int x,int y)
{
	if(r<x||l>y) return 1e9;
	if(x<=l&&r<=y) return tr[k];
	push_down(k);
	int mid=(l+r)>>1;
	return min( query(l,mid,k<<1,x,y),query(mid+1,r,k<<1|1,x,y) );
}
int query_path(int x,int y)
{
	int ans=1e9;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ans=min(ans,query(1,n,1,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	} 
	if(x==y) return ans;
	if(dfn[x]>dfn[y]) swap(x,y);
	ans=min(ans,query(1,n,1,dfn[x]+1,dfn[y]));
	return ans;
}
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&e[i].x,&e[i].y);
		if(e[i].x>e[i].y) swap(e[i].x,e[i].y);
		ret[mpi(e[i].x,e[i].y)]=i;//记录编号
		e[i].tim=0;//初始时间记为0
	}
	for(int i=1;i<=q;i++)
	{
		cin>>opt[i]; scanf("%d%d",&ques[i].x,&ques[i].y);
		if(ques[i].x>ques[i].y) swap(ques[i].x,ques[i].y);
		if(opt[i]=='Z')ques[i].id=0;
		else ques[i].id=1;
	}
	for(int i=q,cnt=1;i>=1;i--)
	{
		if(ques[i].id) cnt++;
		else e[ret[mpi(ques[i].x,ques[i].y)]].tim=cnt;//时间回溯赋值
	}
	kruskal();//生成树
	for(int i=1;i<=n;i++) 
		if(!dep[i]) dfs1(i,0),dfs2(i,i);//树剖准备
	for(int i=1;i<=m;i++)//将不执行Z操作的边先更新
	{
		if(e[i].tim) continue;
		int rx=find(e[i].x),ry=find(e[i].y);
		if(rx!=ry) merge(rx,ry);
		update_path(e[i].x,e[i].y);
	}
	for(int i=q;i>=1;i--)//时间回溯 
	{
		if(ques[i].id==1) 
		{
			int ans=query_path(ques[i].x,ques[i].y);
			if(ans>1) ok[++ans_cnt]=1;
			else ok[++ans_cnt]=-1;
		}
		else 
		{
			int rx=find(ques[i].x),ry=find(ques[i].y);
			if(rx!=ry) merge(rx,ry);
			update_path(ques[i].x,ques[i].y);
		}
	}
	for(int i=ans_cnt;i>=1;i--)
	{
		if(ok[i]>0) puts("TAK");
		else puts("NIE");
	}
}
```

---

## 作者：Kazeno_Akina (赞：0)

> 还得是 OIFC。

我将简述做题思路。

### Hint 1：这是边双。

看题得知。主要是别看成有向边。

### Hint 2：正难则反。

你发现大部分图论相关的玩意都特别能加边，删边一般来说要比加边困难。本题没强制在线，所以离线下来倒着做。

### Hint 3：dfs 生成树覆盖求桥法

~~因为我不会Tarjan~~ 容易想到一种特别好写的求桥的方法，就是你先做一棵 dfs 生成树，然后用非树边做覆盖。为了保证复杂度，考虑差分，最后非树边显然都不是桥，树边是桥当且仅当该树边连接的儿子的子树内差分数组和为 $0$。（具体流程也可以看 [双连通分量-OI Wiki](https://oi.wiki/graph/bcc/#%E5%B7%AE%E5%88%86%E7%AE%97%E6%B3%95) ）

虽然这题你要是每次加边和查询都线性就寄了，但是你发现了覆盖边直接判这个性质。

于是你想到一个特别好做法：树剖，剖完了直接用非树边盖树边。这样做复杂度是 $O(n\log^2 n)$，足以通过本题。

不过这个地方有一些值得注意的，就是 **当加的边连接的两个点本来不连通时该怎么做**。显然这时候你要是盖边你没的盖，你也不能贸然往树里插，因为 $dfn$ 会乱成一团。

于是分化出了两个流派：

1. 合并时换根+合并，坚持剖下去
2. 想更牛的做法

下面讲更厉害的做法。

根据边双的传递性，容易想到用并查集维护。但是你发现你好像直接维护比较困难。

### Hint 4：没人告诉你不能用辅助数组维护边双性质

你考虑建立一个数组 $cnt_i$，表示在树上 $i$ 和 $fa_i$ 这条边被盖了 $0/1/>2$ 次。当 $cnt_i$ 达到 $2$ 时，合并 $i$ 和 $fa_i$。

然后你考虑怎么保证每次都先加入树边再加入非树边（否则如果有两条非树边先被加入且都盖住了一条没加入的树边那你就假飞了）。

### Hint 5：特殊的最小生成树！

考虑把边按照丢弃时间戳降序排。

这样如果非树边加入了，它连的两个点必然早就连通了，不然它自己就成树边了。

于是你获得了最终做法：建立时间最小生成树 -> 加边时向上跳边双连通块，查询时在边双连通并查集内查询连通性。

总复杂度比较逆天。

如果你最小生成树是排序做的，那这一部分复杂度是 $O(n\log n)$。但是你发现完全可以每次删边时直接往后插，那你用 `vector` 实现最劣复杂度是跑得飞快（常数在千分之一级别）的 $O(n^2)$（此处假设出题人卡你）；用链表实现复杂度是 $O(n)$。

关于你的并查集，首先整棵树每条边至多被跳 $2$ 次，合并 $1$ 次。

所以如果你为了方便写的是路径压缩+向上合并（方便找跳到的节点编号），那你复杂度是 $O(n\log n)$。如果你乐意写路径压缩+按秩合并，复杂度就是 $O(n\ \alpha(n))$。

但是还有厉害的科技，也就是 **树分块**，可以参考 [RMQ标准算法和线性树上并查集](https://ljt12138.blog.uoj.ac/blog/4874)。可以做到 $O(n)$。

因此如果你非常能写，复杂度可以做到理论线性。

~~但是我很不能写~~ 以下给出排序最小生成树+路径压缩向上合并的 $O(n\log n)$ 代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N=1e5+5;
struct edge{int u,v,ord,appe;};
struct work{int x,y;bool ans;char opt;};
int n,m,q,x,y,fa[N],cnt[N],dep[N],trfa[N];
edge e[N];
work init;
vector<int> ch[N];
vector<work> mem;
unordered_map<long long,int> mp;//处理删边标记
inline bool cmp1(edge a,edge b){return a.appe<b.appe;}
inline bool cmp2(edge a,edge b){return a.ord<b.ord;}
int find(int p){return(p==fa[p])?(p):(fa[p]=find(fa[p]));}
inline void reset(){for(int i(1);i<=n;++i) fa[i]=i;}
void dfs(int p,int fa){
    trfa[p]=fa,dep[p]=dep[fa]+1;
    for(int i(0);i<ch[p].size();++i) if(ch[p][i]!=fa) dfs(ch[p][i],p);
}
inline void merge(int u,int v){
    if(find(u)==find(v)) return;
    u=find(u),v=find(v);
    while(find(v)!=find(u)){
        if(dep[find(u)]>dep[find(v)]) swap(u,v);
        if(!cnt[v]) ++cnt[v];
        else fa[v]=find(trfa[v]);
        v=find(trfa[v]);
    }
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> n >> m >> q;
    for(int i(1);i<=m;++i) cin >> e[i].u >> e[i].v,e[i].appe=0,e[i].ord=i,mp[e[i].u*N+e[i].v]=mp[e[i].v*N+e[i].u]=i;
    while(q--){
        cin >> init.opt;
        if(init.opt=='Z') cin >> x >> y,init.x=mp[x*N+y],e[init.x].appe=q+1,mem.push_back(init);
        else cin >> init.x >> init.y,mem.push_back(init);
    }
    sort(e+1,e+m+1,cmp1),reset();//一定记得排回去！！！
    for(int i(1),u,v;i<=m;++i){
        u=e[i].u,v=e[i].v;
        if(find(u)!=find(v)) ch[u].push_back(v),ch[v].push_back(u),fa[find(u)]=find(v);
    }
    for(int i(1);i<=n;++i) if(!trfa[i]) dep[i]=1,dfs(i,0);
    sort(e+1,e+m+1,cmp2),reset();
    for(int i(1);i<=m;++i){
        if(dep[e[i].u]>dep[e[i].v]) swap(e[i].u,e[i].v);
        if(!e[i].appe) merge(e[i].u,e[i].v);
    }
    for(int i(mem.size()-1),u,v;~i;--i){
        if(mem[i].opt=='Z') merge(e[mem[i].x].u,e[mem[i].x].v);
        else mem[i].ans=(find(mem[i].x)==find(mem[i].y));
    }
    for(int i(0);i<mem.size();++i) if(mem[i].opt=='P'){
        if(mem[i].ans) cout << "TAK\n";
        else cout << "NIE\n";
    }
    return 0;
}
```

---

## 作者：keatsli (赞：0)

### 题意

给定一个无向无环图，要求维护删边以及两个点之间是否有边不相交路径。

### 两个关键性质

首先注意到动态连通性问题，删边并不好维护，于是考虑倒着做，删边改成加边。

接下来，~~如果你感觉不错~~ 一定能发现这是维护两个点是否在一个边双连通分量内部，下面我们简单证明这一点：

#### 小证明

考虑若两点间有两条 **边不相交** 路径，则割掉任意一条边都不会影响连通性，因为两条路径至少有一条是好的。

同理，若割掉一条边可以让这两个点不连通，则这两点间任意路径必须经过这条边，故只有一条 **边不相交** 路径。

### 查询

于是我们可以考虑开两个并查集分别维护连通性和边双连通分量，接下来只维护一颗生成树的结构，查询的时候直接在边双连通分量的并查集内部查询即可。

### 修改

接下来考虑如何连接两个点 $u$，$v$：

若两个点不连通，我们考虑一个类似启发式合并的过程，直接暴力把小的生成树换根，再把小的根连到大的上面，这样复杂度正确。

若这两个点连通，于是我们加了一条反祖边，则这条边跨过的所有点双连通分量、点都应该被合并进一个。

这里有一个实现上可以大幅简化的地方：我们钦定点双连通分量的代表元是最高的（换根的时候记得一并修改），这样暴力跳点双连通分量内部最高点均摊复杂度正确（每个点被跳一次之后就会被合并，以后就不会再跳了）。

复杂度 $O(q\log n)$，若实现方法优秀的话可以轻松跑到最优解前几名。

### 能不能能再给力一点？

复杂度瓶颈同时在启发式合并和并查集上，其中并查集可以直接使用 [树上并查集](https://ljt12138.blog.uoj.ac/blog/4874) 优化成线性。

启发式合并看起来没什么前途，但仔细想想其实可以避免这种合并：

我们在一开始拉生成树的时候拉比较“保险”的边，我们对 **倒着做的时候** 加入时间做最小生成树，这样每次加边都必然是 **加非树边** 或 **激活一个树边**，不需要重构树，于是我们获得了优秀的 $O(n)$ 复杂度，不过常数并不小。

---

## 作者：xiezheyuan (赞：0)

## 简要题意

给定一个 $n$ 个点 $m$ 条边的无向简单图。

有 $q$ 次操作，每次操作支持删除一条存在的边，或询问两点之间是否存在至少两条边集无交的路径。

$1\leq n,m,q\leq 10^5$。

## 思路

模拟赛的题目的弱化版。在这里就讲一个小常数 $O(n\log n)$ 做法，也许可以优化到线性。

首先不难发现所谓“存在至少两条边集无交的路径”等价于这两个点在同一个边双联通分量内，我们可以考虑建立边双树，在边双树上考虑问题。

将时光倒流，转换成加边和查询。首先求出没被删的边组成的森林，为了方便，可以直接将每条边打上被删除的时间戳，然后求一个最大生成树，这样的好处是增加的边不会合并连通块。

然后考虑如何加边，如果不考虑时间复杂度，可以新建一个点，将加边构成的路径上的所有点全部缩在这个新点上。可是构造一条链这个做法就死了。

不难想到其实我们没有必要真正的去删所有点，只需要这个点所在的“真实点”就好了。

这个可以用并查集维护。具体来说，我们维护一个并查集，通过并查集查询这个点会被缩到哪个点，然后我们钦定一条路径缩到 LCA 上。

由于并查集维护信息具备传递性，所以这样子正确性没有问题，时间复杂度由于每个点只会被访问常数次，所以是 $O(n\log n)$ 的。

## 代码

代码修改自考场代码，可能会比较丑。

```cpp
#include <bits/stdc++.h>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
using namespace std;

template <class Type>
void read (Type &x){
    char c;
    bool flag = false;
    while ((c = getchar()) < '0' || c > '9')
        c == '-' && (flag = true);
    x = c - '0';
    while ((c = getchar()) >= '0' && c <= '9')
        x = (x << 1) + (x << 3) + c - '0';
    flag && (x = ~x + 1);
}
template <class Type, class ...rest>
void read (Type &x, rest &...y) { read(x), read(y...); }
template <class Type>
void write (Type x){
    x < 0 && (putchar('-'), x = ~x + 1);
    x > 9 && (write(x / 10), 0);
    putchar('0' + x % 10);
}

const int N = 8e5 + 5, M = 1e6 + 5;
int father[N];
int n, m, q, tid;

struct edge{
	int u, v, w, id;
	bool operator<(const edge &x) const {
		return w < x.w;
	}
} g[M];

struct qrynode{
	int op, x, y;
} qry[M];

struct UnionFind{
	int fa[N];
	int find(int x){ return fa[x] == x ? x : fa[x] = find(fa[x]); }
	void init(){ iota(fa, fa + n + 1, 0); }
	void merge(int x, int y){ fa[find(x)] = find(y); }
	bool same(int x, int y){ return find(x) == find(y); }
} st;

vector<int> tree[N];
bool ontree[M];
int dep[N];

void dfs(int u, int fa){
	father[u] = fa; dep[u] = dep[fa] + 1;
	for(int v : tree[u]){
		if(fa == v) continue;
		dfs(v, u);
	}
}

void connect(int u, int v){
	vector<int> nds;
	u = st.find(u); v =  st.find(v);
	while(u != v){
		if(dep[u] < dep[v]) swap(u, v);
		nds.emplace_back(u);
		u = st.find(father[u]);
	}
	for(int i : nds) st.merge(i, u);
}

bool answer[M];

signed main(){
	read(n, m, q);
    map<pair<int,int>, int> mp;
	for(int i=1;i<=m;i++) read(g[i].u, g[i].v), g[i].id = i, mp[{g[i].u, g[i].v}] = mp[{g[i].v, g[i].u}] = i;
	for(int i=1;i<=q;i++){
        char op = getchar(); qry[i].op = (op == 'Z') ? 1 : 2;
		read(qry[i].x, qry[i].y);
		if(qry[i].op == 1) qry[i].x = mp[{qry[i].x, qry[i].y}], g[qry[i].x].w = i;
	}
	st.init();
	priority_queue<edge> pq;
	for(int i=1;i<=m;i++){
		if(!g[i].w) g[i].w = INT_MAX;
		pq.emplace(g[i]);
	}
	while(!pq.empty()){
		edge e = pq.top(); pq.pop();
		if(st.same(e.u, e.v)) continue;
		st.merge(e.u, e.v);
		tree[e.u].emplace_back(e.v);
		tree[e.v].emplace_back(e.u);
		ontree[e.id] = true;
	}
	for(int i=1;i<=n;i++){
		if(!father[i]) dfs(i, 0);
	}
	st.init();
	for(int i=1;i<=m;i++){
		if(g[i].w > q && !ontree[i]){
			connect(g[i].u, g[i].v);
		}
	}
	for(int i=q;i;i--){
		if(qry[i].op == 1){
			if(!ontree[qry[i].x]) connect(g[qry[i].x].u, g[qry[i].x].v);
		}
		else answer[i] = st.same(qry[i].x, qry[i].y);
	}
	for(int i=1;i<=q;i++){
		if(qry[i].op == 2){
			if(answer[i]) putchar('T'), putchar('A'), putchar('K');
			else putchar('N'), putchar('I'), putchar('E');
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

模拟赛放这题 $10^6$ 的版本结果我 $O(n \log n)$ 被卡常了，看来要戒 vector 了。

考虑倒着做变成加边维护边双树，显然我们要做的操作形如合并两棵树，维护深度相对关系，以及把一条路径上所有点全部合并，前者可以直接启发式合并的时候维护出来，后者直接考虑树上并查集暴力做即可，因为暴力合并一个点少一个点，所以总时间复杂度是 $O(n \log n)$ 的。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+114;
namespace IO{
    const int SIZE=1<<21;
    static char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=oS+SIZE-1;
    int qr;
    char qu[55],c;
    bool f;
    #define getchar() (IO::iS==IO::iT?(IO::iT=(IO::iS=IO::ibuf)+fread(IO::ibuf,1,IO::SIZE,stdin),(IO::iS==IO::iT?EOF:*IO::iS++)):*IO::iS++)
    #define putchar(x) *IO::oS++=x,IO::oS==IO::oT?flush():0
    #define flush() fwrite(IO::obuf,1,IO::oS-IO::obuf,stdout),IO::oS=IO::obuf
    #define puts(x) IO::Puts(x)
    template<typename T>
    inline void read(T&x){
        for(f=1,c=getchar();c<48||c>57;c=getchar())f^=c=='-';
        for(x=0;c<=57&&c>=48;c=getchar()) x=(x<<1)+(x<<3)+(c&15); 
        x=f?x:-x;
    }
    template<typename T>
    inline void write(T x){
        if(!x) putchar(48); if(x<0) putchar('-'),x=-x;
        while(x) qu[++qr]=x%10^48,x/=10;
        while(qr) putchar(qu[qr--]);
    }
    inline void Puts(const char*s){
        for(int i=0;s[i];++i)
            putchar(s[i]);
        putchar('\n');
    }
    struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}
using IO::read;
using IO::write;
int n,m,q;
int uni[maxn];//一个点被合并到哪个点上
int fa[maxn];//父亲
int found(int u){
	return uni[u]=(uni[u]==u?u:found(uni[u]));
}
int vis[maxn];//属于哪个连通块
vector<int> vec[maxn];//连通块内点集
int dep[maxn];
vector<int> E[maxn];
vector<int> emp;
void dfs(int rt,int depth){
	dep[rt]=depth;
	fa[rt]=0;
	queue<int> q;
	q.push(rt);
	while(q.size()>0){
		int u=q.front();
		q.pop();
		for(int v:E[u]){
			if(v!=fa[u]){
				fa[v]=u;
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
}
void rebuild(int u,int rt,int depth,int to){
	rt=found(rt);
	for(int v:vec[u]){
		if(found(v)==v){
			if(found(fa[v])!=0) E[found(fa[v])].push_back(v),E[v].push_back(found(fa[v]));
			emp.push_back(v);
		}
	}
	dfs(rt,depth);
	for(int x:emp) E[x].clear(),vis[x]=to,vec[to].push_back(x);
	emp.clear();
	swap(vec[u],emp);
	emp.clear();
}
int LCA(int u,int v){
	while(u!=v){
		if(dep[found(fa[u])]>=dep[found(fa[v])]) u=found(fa[u]);
		else v=found(fa[v]);
	}
	return u;
}
void merge(int u,int v){
	int lca=LCA(u,v);
	while(u!=v){
		if(dep[found(fa[u])]>=dep[found(fa[v])]) uni[found(u)]=lca,u=found(fa[u]);
		else uni[found(v)]=lca,v=found(fa[v]);
	}
	return ;
}
int X[maxn],Y[maxn];
int use[maxn];
int stk[maxn<<1],tp,ask[maxn<<1][2];
char ty[maxn<<1];
string ans[maxn<<1];
unordered_map<int,int> id[maxn];
int main(){
	read(n),read(m),read(q);
	for(int i=1;i<=m;i++) read(X[i]),read(Y[i]),id[X[i]][Y[i]]=id[Y[i]][X[i]]=i;
	for(int i=1;i<=n;i++) uni[i]=i,fa[i]=0,dep[i]=1,vec[i].push_back(i),vis[i]=i;
	for(int i=1;i<=q;i++){
		tp++;
		ty[i]=getchar();
		if(ty[i]=='Z'){
			int u,v;
			read(u),read(v);
			stk[tp]=id[u][v];
			use[stk[tp]]=1;
		}
		else read(ask[tp][0]),read(ask[tp][1]);
	}
	for(int i=1;i<=m;i++){
		if(use[i]==0){
			tp++;
			ty[tp]='Z';
			stk[tp]=i;
		}
	}
	for(int i=tp;i>=1;i--){
		if(ty[i]=='Z'){
			int u=X[stk[i]],v=Y[stk[i]];
			u=found(u),v=found(v);
			if(vis[u]!=vis[v]){
				if(vec[vis[u]].size()>vec[vis[v]].size()) swap(u,v);
				//cerr<<vec[vis[u]].size()<<' '<<vec[vis[v]].size()<<'\n';
				//u 合并到 v 上
				rebuild(vis[u],u,dep[v]+1,vis[v]);
				fa[u]=v;
				//cout<<'\n';
			}else{
				if(u!=v) merge(u,v);
			}
		}else{
			int u=ask[i][0],v=ask[i][1];
			u=found(u),v=found(v);
			ans[i]=(u==v?"TAK":"NIE");
		}
	}
	for(int i=1;i<=tp;i++){
		if(ty[i]=='P'){
			for(char c:ans[i]) putchar(c);
			putchar('\n');
		}
	}
	return 0;
}//真的卡不动了，球球给我放过去把 /ll
```

---

## 作者：xiao7_Mr_10_ (赞：0)

考虑转化问题，一个很显然的结论是两个点在同一个点双内是存在两点两条不相交的路径的充要条件。

然后我们倒着做，这样就把删边改为加边。

不难注意到实际上难以动态维护 dfs 树，不妨为每一条边设一个边权 $t_{i}$，表示在 $t_{i}$ 时刻出现。随后我们跑一遍最小生成树，我们就知道哪些边出现的时候产生了新的边双了。

然后使用并查集维护即可，我们规定做边双合并的时候，每个并查集的祖先为深度最小的节点，因为涉及并查集合并，我们可以暴力逐步合并，每次将并查集根节点深度较大的集合与其父亲所在集合合并即可。

实际上你发现不必对边排序，直接扫一遍加入再倒过来即可，时间复杂度可以认为是 $O(n+m)$ 的。

这是考试原题顺口说一句。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
struct tmper{int u,v;}a[N];
struct ques{int op,u,v;}wt[N];
struct Point{int v,val;};vector <Point> e[N];
int n,u,v,m,b[N],q,id,pos[N],cnt,dfn[N],vis[N],f[N],tim,ft[N];
int getf(int u){return f[u]==u?u:f[u]=getf(f[u]);}
void add(int u,int v,int w){
	e[u].push_back((Point){v,w});
	e[v].push_back((Point){u,w});
}
void dfs(int u,int fa){
	pos[u]=++cnt;
	for(int i = 0;i < e[u].size();i++){
		int v=e[u][i].v,val=e[u][i].val;
		if(v==fa)continue;
		b[v]=val,ft[v]=u,dfs(v,u);
	}dfn[u]=cnt;
}int col[N];
void insert(int &tlh){col[b[tlh]]++;if(col[b[tlh]]==2)f[tlh]=getf(ft[tlh]);tlh=getf(ft[tlh]);}
inline void merge(int u,int v){
    int l=min(pos[u],pos[v]),r=max(pos[u],pos[v]);
    int tlh=getf(u);
    while(pos[tlh]>l||dfn[tlh]<r)insert(tlh);tlh=getf(v);
    while(pos[tlh]>l||dfn[tlh]<r)insert(tlh);
    return ;
}int ans[N];
char op;
map <pair<int,int>,int> mp;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> n >> m >> q;
	for(int i = 1;i <= m;i++){
		cin >> a[i].u >> a[i].v;
		if(a[i].u>a[i].v)swap(a[i].u,a[i].v);
		mp[make_pair(a[i].u,a[i].v)]=i;
	}
	for(int i = 1;i <= q;i++){
		cin >> op >> u >> v;
		if(op=='Z'){
			if(u>v)swap(u,v);
			int id=mp[make_pair(u,v)];vis[id]=1;
			wt[i]=(ques){1,u,v};
		}
		else wt[i]=(ques){2,u,v};
	}
	for(int i = 1;i <= n;i++)f[i]=i;
	for(int i = 1;i <= m;i++){
		if(!vis[i]){
			if(getf(a[i].u)!=getf(a[i].v)){
				f[getf(a[i].u)]=f[getf(a[i].v)];
				add(a[i].u,a[i].v,++tim);
			}
		}
	}
	for(int i = q;i >= 1;i--){
		if(getf(wt[i].u)!=getf(wt[i].v)&&wt[i].op==1){
			f[getf(wt[i].u)]=f[getf(wt[i].v)];
			add(wt[i].u,wt[i].v,++tim);
		}
	}
	for(int i = 1;i <= n;i++){
		if(!pos[i])dfs(i,0);
		f[i]=i;
	}int len=0;
	for(int i = 1;i <= m;i++)if(!vis[i])merge(a[i].u,a[i].v);
	for(int i = q;i >= 1;i--){
		if(wt[i].op==1)merge(wt[i].u,wt[i].v);
		else ans[++len]=(bool){getf(wt[i].u)==getf(wt[i].v)};
	}for(int i = len;i >= 1;i--)cout << (ans[i]?"TAK\n":"NIE\n");
	return 0;
}
```

---

## 作者：bluewindde (赞：0)

首先想到常见套路，将操作离线，并将删边操作转换为加边操作。

现在考虑动态加边，维护边双连通分量。

考虑 Tarjan 算法，按边的被删除时间，搜出一棵最大生成树，非树边的两个端点之间的树上路径所包含的点处在同一边双连通分量。由边双连通分量的传递性，可以使用并查集维护这个过程，均摊 $O(n \alpha(n))$，但我写挂了。

考虑并查集查询两点是否属于同一边双连通分量，本质上是链覆盖、查询链颜色是否相同，树剖容易维护，时间复杂度 $O(n \log^2 n)$。

```cpp
#include <algorithm>
#include <iostream>
#include <map>
#include <string.h>
#include <vector>

using namespace std;

int n, m, q;
vector<int> vec[100005];
map<pair<int, int>, int> mp;
map<pair<int, int>, bool> intr;
struct edge {
    int u, v, tm;
} e[100005], e2[100005];
struct node {
    char op;
    int x, y;
} qs[100005];

int bel[100005];
int sz[100005];
static inline int find(int x) { return bel[x] == x ? x : bel[x] = find(bel[x]); }
static inline void merge(int u, int v) {
    int uu = find(u), vv = find(v);
    if (uu == vv)
        return;
    if (sz[uu] < sz[vv])
        swap(uu, vv);
    bel[vv] = uu;
    sz[uu] += sz[vv];
}

int f[100005];
int dfn[100005], dfn_clock;
int dep[100005];
int top[100005];
int son[100005];
int siz[100005];
static inline void dfs(int u, int fa) {
    f[u] = fa;
    dep[u] = dep[fa] + 1;
    siz[u] = 1;
    for (auto v : vec[u]) {
        if (v == fa)
            continue;
        dfs(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
            son[u] = v;
    }
}
static inline void dfs2(int u) {
    dfn[u] = ++dfn_clock;
    if (!son[u])
        return;
    top[son[u]] = top[u];
    dfs2(son[u]);
    for (auto v : vec[u]) {
        if (v == f[u] || v == son[u])
            continue;
        top[v] = v;
        dfs2(v);
    }
}

int d[400005];
int tag[400005];
static inline void pushdown(int p) {
    if (!tag[p])
        return;
    d[p << 1] = d[p << 1 | 1] = tag[p << 1] = tag[p << 1 | 1] = 1;
    tag[p] = 0;
}
static inline void update(int l, int r, int s, int t, int p) {
    if (l <= s && r >= t) {
        tag[p] = 1;
        d[p] = 1;
        return;
    }
    int mid = (s + t) >> 1;
    pushdown(p);
    if (l <= mid)
        update(l, r, s, mid, p << 1);
    if (r > mid)
        update(l, r, mid + 1, t, p << 1 | 1);
    d[p] = min(d[p << 1], d[p << 1 | 1]);
}
static inline int query(int l, int r, int s, int t, int p) {
    if (l <= s && r >= t)
        return d[p];
    int mid = (s + t) >> 1;
    pushdown(p);
    int ret = 1;
    if (l <= mid)
        ret = min(ret, query(l, r, s, mid, p << 1));
    if (r > mid)
        ret = min(ret, query(l, r, mid + 1, t, p << 1 | 1));
    return ret;
}

static inline void cover(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        update(dfn[top[u]], dfn[u], 1, dfn_clock, 1);
        u = f[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    if (u != v)
        update(dfn[u] + 1, dfn[v], 1, dfn_clock, 1);
}
static inline bool query(int u, int v) {
    int ret = 1;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ret = min(ret, query(dfn[top[u]], dfn[u], 1, dfn_clock, 1));
        u = f[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    if (u != v)
        ret = min(ret, query(dfn[u] + 1, dfn[v], 1, dfn_clock, 1));
    return ret;
}

int ans[100005], tail;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> q;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        e[i] = {u, v, q + 1};
        mp[{u, v}] = mp[{v, u}] = i;
    }
    for (int i = 1; i <= q; ++i) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'Z')
            e[mp[{x, y}]].tm = i;
        qs[i] = {op, x, y};
    }
    for (int i = 1; i <= m; ++i)
        e2[i] = e[i];
    sort(e2 + 1, e2 + m + 1, [](const edge &x, const edge &y) { return x.tm > y.tm; });
    for (int i = 1; i <= n; ++i) {
        bel[i] = i;
        sz[i] = 1;
    }
    for (int i = 1; i <= m; ++i) {
        auto [u, v, tm] = e2[i];
        if (find(u) == find(v))
            continue;
        intr[{u, v}] = intr[{v, u}] = true;
        vec[u].push_back(v);
        vec[v].push_back(u);
        merge(u, v);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) {
            dfs(i, 0);
            top[i] = i;
            dfs2(i);
        }
    for (int i = 1; i <= m; ++i) {
        auto [u, v, tm] = e[i];
        if (intr[{u, v}] || tm <= q)
            continue;
        cover(u, v);
    }
    for (int i = q; i; --i) {
        auto [op, x, y] = qs[i];
        if (op == 'Z') {
            if (!intr[{x, y}])
                cover(x, y);
        } else {
            ans[++tail] = query(x, y);
        }
    }
    for (int i = tail; i; --i)
        if (ans[i])
            cout << "TAK" << endl;
        else
            cout << "NIE" << endl;
    return 0;
}
```

---

## 作者：JimmyLee (赞：0)

# 题意

> 维护一张无向图，要求支持以下操作：
>
> - 切断一条边。
> - 查询两个点是否有有两条完全不同的路径相连。

# 分析

因为断边操作不好维护，考虑离线后将断边变为加边。

因此，我们只需要维护加边操作即可。

考虑使用 LCT。

首先，因为涉及到边权，套路地用节点代替边。

如果某一条边连接的两个点属于两个不同的连通块，那么直接连边。

如果一条边连接的两个点属于同一个连通块，我们可以在它所连接的两点的路径上将所有的节点的权值 $+1$，表示这些节点可以由两条路径连接。

查询的时候，如果两点之间的所有节点的权值都大于 $1$，那么就满足，否则不满足。

所以我们只需要支持区间加和查询最小值即可。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

namespace LCT
{
    struct node
    {
        node *ch[2], *fa;
        bool rev;
        int v, mn, tag;
        node(int x=0) {v=x, mn=x, rev=0, ch[0]=ch[1]=fa=0, tag=0;}
        bool not_root() {return fa&&(fa->ch[0]==this||fa->ch[1]==this);}
        bool is_rson() {return this==fa->ch[1];}
        void reverse() {rev^=1;swap(ch[0], ch[1]);}
        void add(int w) {tag+=w; mn+=w; v+=w;}
        void push_up()
        {
            mn=v;
            if(ch[0]) mn=min(mn, ch[0]->mn);
            if(ch[1]) mn=min(mn, ch[1]->mn);
        }
        void push_down() 
        {
            if(rev) 
            {
                if(ch[0]) ch[0]->reverse();
                if(ch[1]) ch[1]->reverse();
                rev^=1;
            }
            if(tag)
            {
                if(ch[0]) ch[0]->add(tag);
                if(ch[1]) ch[1]->add(tag);
                tag=0;
            }
        }
    };

    void rotate(node *x)
    {
        bool k=x->is_rson();
        node *y=x->fa, *z=y->fa, *w=x->ch[!k];
        if(y->not_root()) z->ch[y->is_rson()]=x;
        x->ch[!k]=y, y->ch[k]=w;
        y->fa=x, x->fa=z;
        if(w) w->fa=y;
        y->push_up();
        x->push_up();
    }

    stack<node*> s;

    void splay(node *x)
    {
        s.emplace(x);
        while(s.top()->not_root()) s.emplace(s.top()->fa);
        while(!s.empty()) s.top()->push_down(), s.pop();
        while(x->not_root())
        {
            if(x->fa->not_root())
                rotate((x->is_rson()^x->fa->is_rson())?x:x->fa);
            rotate(x);
        }
    }
    
    void access(node *x)
    {
        for(node *y=0;x;x=(y=x)->fa) 
            splay(x), x->ch[1]=y, x->push_up();
    }

    void make_root(node *x)
    {
        access(x); 
        splay(x); 
        x->reverse();
    }

    node *find_root(node *x)
    {
        access(x); 
        splay(x); 
        while(x->push_down(), x->ch[0]) 
            x=x->ch[0];
        return x;
    }

    void link(node *x, node *y)
    {
        if(find_root(x)!=find_root(y)) 
            make_root(x), x->fa=y;
    }

    void cut(node *x, node *y)
    {
        make_root(x); 
        access(y); 
        splay(y); 
        if(y->ch[0]==x) y->ch[0]=x->fa=0;
    }

    int query(node *x, node *y)
    {
        make_root(x);
        access(y);
        splay(y);
        return y->mn;
    }

    void modify(node *x, node *y)
    {
        make_root(x);
        access(y);
        splay(y);
        y->add(1);
    }
}

set<pair<int, int>> s;
LCT::node *rt[100005];
vector<tuple<int, int, int>> vc;
vector<bool> ans;

int main()
{
    int n, m, q;
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++) rt[i]=new LCT::node;
    for(int i=1, u, v;i<=m;i++)
    {
        cin>>u>>v;
        if(u>v) swap(u, v);
        s.emplace(u, v);
    }
    char c;
    for(int i=1, x, y;i<=q;i++)
    {
        cin>>c>>x>>y;
        if(c=='Z') 
        {
            vc.emplace_back(1, x, y);
            if(x>y) swap(x, y);
            s.erase({x, y});
        }
        if(c=='P') vc.emplace_back(2, x, y);
    }
    for(auto [u, v]:s)
    {
        if(find_root(rt[u])==find_root(rt[v]))
            modify(rt[u], rt[v]);
        else 
        {
            LCT::node *eg=new LCT::node;
            link(rt[u], eg), link(eg, rt[v]);
        }
    }
    for(auto [op, u, v]:views::reverse(vc))
    {
        if(op==1)
        {
            if(find_root(rt[u])==find_root(rt[v]))
                modify(rt[u], rt[v]);
            else 
            {
                LCT::node *eg=new LCT::node;
                link(rt[u], eg), link(eg, rt[v]);
            }
        }
        else
        {
            int w=0;
            if(find_root(rt[u])==find_root(rt[v]))
                w=query(rt[u], rt[v]);
            ans.emplace_back(w);
        }
    }
    for(auto op:views::reverse(ans))
        cout<<(op?"TAK\n":"NIE\n");
}
```

---

## 作者：Raisen_zx (赞：0)

为了方便将删边做成加边是显然的，第二个询问明显是在问两个点是否在一个边双里。

用 LCT 维护原图的连通块的生成树森林，先预处理剩下的边，把最后剩下的边先连起来，对于连边，先赋个正边权，如果连完后形成一个边双，可以将边双抽出来全部赋成 0 的权，判断是否在一个边双里就就看路径上的边权和是否为零，也可以抽出来后缩成一个点用并查集维护。

判断边是否被删过可以用 map ，还要判原图上是否有这条边，赋边权可以在两点间用一个点连接，赋个正点权。
```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<map>
#define ls(p) tr[(p)].son[0]
#define rs(p) tr[(p)].son[1]
#define fa(p) tr[(p)].fa
using namespace std;
int n,m,q,tot;
template<typename type>
inline void read(type &x)
{
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}
const int MAXN=2e5+10;
map<pair<int,int>,bool>de;
map<pair<int,int>,bool>vis;
char opt[MAXN][5];
int ans[MAXN];
struct BST
{
    int fa,son[2],sum,val;
    bool rev,tag;
}tr[MAXN<<1];
struct Edge 
{
    int u,v;
}e[MAXN];
struct Node
{
    int u,v;
}qu[MAXN];
inline bool nroot(int p)
{
    return (p==rs(fa(p)))||(p==ls(fa(p)));
}
inline int dire(int p)
{
    return p==rs(fa(p));
}
inline void rever(int p)
{
    if(!p) return;
    tr[p].rev^=1;
    swap(ls(p),rs(p));
}
inline void mdf(int p)
{
    if(!p) return;
    tr[p].tag=1;
    tr[p].sum=tr[p].val=0;
}
inline void push_down(int p)
{
    if(tr[p].rev)
    {   
        rever(ls(p));
        rever(rs(p));
        tr[p].rev=0;
    }
    if(tr[p].tag)
    {
        mdf(ls(p));
        mdf(rs(p));
        tr[p].tag=0;
    }
}
inline void push_up(int p)
{
    tr[p].sum=tr[ls(p)].sum+tr[rs(p)].sum+tr[p].val;
}
inline void rotate(int p)
{
	int tmpf=tr[p].fa,dir1=dire(p),tmpg=tr[tmpf].fa;
	if(nroot(tmpf))
	{
		int dir2=dire(tmpf);
		tr[tmpg].son[dir2]=p;
	}
	if(tr[p].son[dir1^1])
	{
		tr[tr[p].son[dir1^1]].fa=tmpf;
	}
	int w=tr[p].son[dir1^1];
	tr[tmpf].son[dir1]=w;
	tr[p].son[dir1^1]=tmpf;
	tr[tmpf].fa=p;
	tr[p].fa=tmpg;
	push_up(tmpf);
    push_up(p);
}
int st[MAXN],tail;
inline void update(int p)
{
	st[tail=1]=p;
	int tmp=p;
	while(nroot(tmp)) st[++tail]=tmp=tr[tmp].fa;
	while(tail) push_down(st[tail--]);
	return;
}
inline void Splay(int p)
{
    update(p);
    int tmpf;
    while(nroot(p))
    {
        tmpf=fa(p);
        if(nroot(tmpf)) rotate(dire(p)^dire(tmpf)?p:tmpf);
        rotate(p);
    }
    push_up(p);
}
inline void access(int p)
{
    for(int tmp=0;p;tmp=p,p=tr[p].fa)
    {
        Splay(p);
        rs(p)=tmp;
        push_up(p);
    }
}
inline void make_root(int p)
{
    access(p);
    Splay(p);
    rever(p);
}
inline int find_root(int p)
{
    access(p);
    Splay(p);
    push_down(p);
    while(ls(p)) p=ls(p),push_down(p);
    Splay(p);
    return p;
}
inline void split(int x,int y)
{
    make_root(x);
    access(y);
    Splay(y);
}
inline void link(int x,int y)
{
    make_root(x);
    if(find_root(y)==x)
    {
        access(y);
        Splay(y);
        mdf(y);
    } 
    else
    {
        tr[++tot].val=1;
        fa(x)=tot;
        fa(tot)=y;//可以认为加了两条虚边，split时虚边会被算进去
    }
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
#endif
    read(n),read(m),read(q);
    tot=n;
    for(int i=1,x,y;i<=m;++i)
    {
        read(x),read(y);
        if(x>y) swap(x,y);
        e[i]={x,y};
        vis[{x,y}]=1;
    }
    for(int i=1;i<=q;++i)
    {
        scanf("%s",opt[i]);
        read(qu[i].u),read(qu[i].v);
        if(qu[i].u>qu[i].v) swap(qu[i].u,qu[i].v);
        if((vis[{qu[i].u,qu[i].v}])&&(opt[i][0]=='Z')) de[{qu[i].u,qu[i].v}]=1;
    }
    for(int i=1,x,y;i<=m;++i)
    {
        x=e[i].u,y=e[i].v;
        if(de[{x,y}]==0) link(x,y);
    }
    for(int i=q,x,y;i>=1;--i)
    {
        x=qu[i].u,y=qu[i].v;
        if(opt[i][0]=='Z')
        {
            if(vis[{x,y}]) link(x,y);
        }
        else
        {
            if(find_root(x)!=find_root(y)) ans[i]=0;
            else
            {
                split(x,y);
                if(tr[y].sum==0) ans[i]=1;
                else ans[i]=0;
            }
        }
    }
    for(int i=1;i<=q;++i)
    {
        if(opt[i][0]=='P')
        {
            puts(ans[i]?"TAK":"NIE");
        }
    }
    return 0;
}
```

---

