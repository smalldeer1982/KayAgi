# Tree Queries

## 题目描述

Those who don't work don't eat. Get the things you want with your own power. But believe, the earnest and serious people are the ones who have the last laugh... But even then, I won't give you a present.

—Santa, Hayate no Gotoku!



Since Hayate didn't get any Christmas presents from Santa, he is instead left solving a tree query problem.

Hayate has a tree with $ n $ nodes.

Hayate now wants you to answer $ q $ queries. Each query consists of a node $ x $ and $ k $ other additional nodes $ a_1,a_2,\ldots,a_k $ . These $ k+1 $ nodes are guaranteed to be all distinct.

For each query, you must find the length of the longest simple path starting at node $ x^\dagger $ after removing nodes $ a_1,a_2,\ldots,a_k $ along with all edges connected to at least one of nodes $ a_1,a_2,\ldots,a_k $ .

 $ ^\dagger $ A simple path of length $ k $ starting at node $ x $ is a sequence of distinct nodes $ x=u_0,u_1,\ldots,u_k $ such that there exists a edge between nodes $ u_{i-1} $ and $ u_i $ for all $ 1 \leq i \leq k $ .

## 说明/提示

In the first example, the tree is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1904E/c5f1379037fd66e966f2028dba5fe4bd6a86c16c.png)In the first query, no nodes are missing. The longest simple path starting from node $ 2 $ is $ 2 \to 1 \to 3 \to 4 $ . Thus, the answer is $ 3 $ .

In the third query, nodes $ 1 $ and $ 6 $ are missing and the tree is shown below. The longest simple path starting from node $ 2 $ is $ 2 \to 5 $ . Thus, the answer is $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1904E/a4bba31c35c424ba9748f1f5381325841a00f680.png)

## 样例 #1

### 输入

```
7 7
1 2
1 3
3 4
2 5
2 6
6 7
2 0
2 1 1
2 2 1 6
3 1 4
3 1 1
5 0
5 2 1 6```

### 输出

```
3
2
1
4
1
4
1```

## 样例 #2

### 输入

```
4 4
1 2
1 3
2 4
2 1 3
3 1 4
2 1 4
2 3 1 3 4```

### 输出

```
1
2
2
0```

# 题解

## 作者：KazamaRuri (赞：6)

## 题意

给定一个 $ n $ 个点的树，进行 $ m $ 次询问。每次询问在删除若干个点之后，从 $ x $ 出发的最长路径长度，询问之间相互独立。

## 分析

先考虑一个弱化问题，将 $ x $ 指定为根节点。那么答案就是所有节点的深度最大值，删除一个点就等价于废除其子树内所有点的答案，dfn 序加个线段树随便秒。

发现 $ x $ 为根的时候很好做，接下来就考虑依靠离线后换根来将每一个 $ x $ 转化为根节点来解决问题，每次换根直接在线段树上对 $ x $ 的子节点的深度 $ -1 $，其他点 $ +1 $。

这样做有个问题：换根时 dfn 序就不对了，总不能从标号一次吧？明显不行，因为这样要重构线段树。那我们来分讨一下：记删除的点为 $ a_i $，当 $ a_i $ 是 $ x $ 子节点时，直接废除 $ a_i $ 的子树就行了。否则 $ x $ 出发的路径不能经过 $ a_i $，也就是只有 $ a_i $ 的**唯一包括 $ x $ 的儿子 $ son_{a_i} $ 子树内的节点是可达的**，这个点可以依靠倍增或者树剖来找。~~都写 dfn 序了当然用树剖啊。~~

## 代码

没有刻意压行，代码还是比较好写的，废除点我拿深度 $ -n $  实现了。

```cpp
#include <iostream>
#include <vector>
using namespace std;
using pii=pair<int,int>;
using ll= long long;
const int N=2e5+5,inf=1<<30; vector<int>q[N],p[N]; vector<pii>s;
int n,m,cnt,head[N],dep[N],tim,h[N],dfn[N],low[N],fa[N],top[N],siz[N],son[N],ans[N]; ll t[N<<2],tg[N<<2];
struct Edge{ int to,next; }e[N<<1];
void add_edge(int u,int v){ e[++cnt]={v,head[u]},head[u]=cnt; }
inline int lc(int x){ return x<<1; }
inline int rc(int x){ return x<<1|1; }
void push_up(int x){ t[x]=max(t[lc(x)],t[rc(x)]); }
void push_down(int x){ ll &add=tg[x]; if(!add) return ; t[lc(x)]+=add,t[rc(x)]+=add,tg[lc(x)]+=add,tg[rc(x)]+=add,add=0; }
void build(int x,int l,int r){
	if(l==r) return t[x]=dep[h[l]],void(); int mid=l+r>>1;
	build(lc(x),l,mid),build(rc(x),mid+1,r),push_up(x);
}
void upd(int x,int l,int r,int u,int v,int k){
	if(l>v||r<u||u>v) return ; if(u<=l&&r<=v) return t[x]+=k,tg[x]+=k,void(); int mid=l+r>>1;
	push_down(x),upd(lc(x),l,mid,u,v,k),upd(rc(x),mid+1,r,u,v,k),push_up(x);
}
int ask(int x,int l,int r,int u,int v){
	if(l>v||r<u) return -inf; if(u<=l&&r<=v) return t[x]; int mid=l+r>>1;
	push_down(x); return max(ask(lc(x),l,mid,u,v),ask(rc(x),mid+1,r,u,v));
}
void dfs1(int u){
	dep[u]=dep[fa[u]]+1,siz[u]=1;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to; if(v==fa[u]) continue;
		fa[v]=u,dfs1(v),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int tp){
	h[dfn[u]=++tim]=u,top[u]=tp;
	if(son[u]) dfs2(son[u],tp);
	for(int i=head[u];i;i=e[i].next){ int v=e[i].to;
		if(v==fa[u]||v==son[u]) continue; dfs2(v,v);
	} low[u]=tim;
}
int solve(int u,int v){
	while(top[u]^top[v]){ u=top[u];
		if(fa[u]==v) return u; u=fa[u];
	}  return son[v];
}
void dfs3(int u){
	for(int i:p[u]){
		for(int v:q[i])
			if(dfn[v]<=dfn[u]&&dfn[u]<=low[v]){ int w=solve(u,v);
				upd(1,1,n,1,dfn[w]-1,-n),upd(1,1,n,low[w]+1,n,-n),
				s.push_back({1,dfn[w]-1}),s.push_back({low[w]+1,n});
			}else s.push_back({dfn[v],low[v]}),upd(1,1,n,dfn[v],low[v],-n);
		ans[i]=ask(1,1,n,1,n); for(pii x:s) upd(1,1,n,x.first,x.second,n); s.clear();
	}
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to; if(v==fa[u]) continue;
		upd(1,1,n,1,n,1),upd(1,1,n,dfn[v],low[v],-2),dfs3(v),
		upd(1,1,n,1,n,-1),upd(1,1,n,dfn[v],low[v],2);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),
		add_edge(u,v),add_edge(v,u);
	for(int i=1;i<=m;i++){
		int x,k; scanf("%d%d",&x,&k);
		p[x].push_back(i);
		for(int j=0;j<k;j++)
			scanf("%d",&x),q[i].push_back(x);
	} dep[0]=-1,dfs1(1),dfs2(1,1),build(1,1,n),dfs3(1);
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：6)

## 题目大意

给定一棵树与 $m$ 次询问，每次询问给出 $x$ 与一个点集，求如果将点集删除，$x$ 能到的最远的点。

## 题目分析

典。

考虑将 $x$ 作为根，则删一个点等同于删除其子树的点，查询等同于查询剩下点的深度最大值。枚举 $x$ ，用线段树维护 dfn 序上的信息，子树转区间，可以做到 $O(n^2+\sum k\log n)$。

不难想到换根，对树 dfs，节点深度的变化就是[这道题](https://www.luogu.com.cn/problem/P3478)。然后就是简单的原树上的分类讨论，对于枚举的根 $x$，删除的点 $y$，如果 $x$ 不在 $y$ 的子树内，则直接删除 $y$ 的子树，否则 $x$ 跳祖先，跳到 $y$ 的儿子 $z$，则除了 $z$ 子树外的点都删除。

复杂度 $O((n+\sum k)\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L (x<<1)
#define R (L|1)
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =2e5+5,inf=(1LL<<30)-1;
int n=read(),m=read(),h[N],to[N<<1],nxt[N<<1],cnt,dep[N],siz[N],f[N],son[N],top[N],dfn[N],Id[N],Time;
inline void add_(int a,int b){
    to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,to[++cnt]=a,nxt[cnt]=h[b],h[b]=cnt;
}
inline void dfs(int x,int fa){
    f[x]=fa,dep[x]=dep[fa]+1,siz[x]=1;
    e(x)if(y^fa)dfs(y,x),siz[x]+=siz[y],son[x]=siz[y]>siz[son[x]]?y:son[x];
}
inline void Dfs(int x,int low){
    top[x]=low,dfn[x]=++Time,Id[Time]=x;
    if(son[x])Dfs(son[x],low);
    e(x)if(y^f[x]&&y^son[x])Dfs(y,y);
}
struct seg{
    int w,mx,laz,lazc;
}xd[N<<2];
inline void getup(int x){
    xd[x].mx=max(xd[L].mx,xd[R].mx),xd[x].w=max(xd[L].w,xd[R].w);
}
inline void insert(int x,int k){
    xd[x].w+=k,xd[x].mx+=k,xd[x].laz+=k;
}
inline void cover(int x,int k){
    xd[x].mx=k?xd[x].w:-inf;
    xd[x].lazc=k;
}
inline void pushdown(int x){
    insert(L,xd[x].laz),insert(R,xd[x].laz),xd[x].laz=0;
    if(xd[x].lazc!=-1)cover(L,xd[x].lazc),cover(R,xd[x].lazc),xd[x].lazc=-1;
}
inline void build(int x,int l,int r){
    xd[x].lazc=-1;
    if(l==r)return xd[x].w=xd[x].mx=dep[Id[l]],void();
    build(lc),build(rc),getup(x);
}
inline void modify(int x,int l,int r,int Ll,int Rr,int k,bool ty){
    if(Ll>Rr)return;
    if(OK)return ty?insert(x,k):cover(x,k),void();
    pushdown(x);
    if(Ll<=mid&&Rr>=l)modify(lc,Ll,Rr,k,ty);
    if(Ll<=r&&Rr>mid)modify(rc,Ll,Rr,k,ty);
    getup(x);
}
inline int jump(int x,int y){
    while(top[x]^top[y]){
        y=top[y];
        if(f[y]==x)return y;
        else y=f[y];
    }
    return son[x];
}
struct node{
    int id;
    vector<int>p;
};
int out[N];
vector<node>p[N];
inline bool che(int x,int y){
    return dfn[y]>=dfn[x]&&dfn[y]<=dfn[x]+siz[x]-1;
}
inline void Dfs(int x){
    E(x){
        modify(Root,1,n,1,0);
        for(auto z:y.p){
            if(che(z,x)){
                int X=jump(z,x);
                modify(Root,1,dfn[X]-1,0,0),modify(Root,dfn[X]+siz[X],n,0,0);
            }else modify(Root,dfn[z],dfn[z]+siz[z]-1,0,0);
        }
        out[y.id]=xd[1].mx-1;
    }
    e(x)if(y^f[x]){
        modify(Root,dfn[y],dfn[y]+siz[y]-1,-1,1);
        modify(Root,1,dfn[y]-1,1,1);
        modify(Root,dfn[y]+siz[y],n,1,1);
        Dfs(y);
        modify(Root,dfn[y],dfn[y]+siz[y]-1,1,1);
        modify(Root,1,dfn[y]-1,-1,1);
        modify(Root,dfn[y]+siz[y],n,-1,1);
    }
}
signed main(){
    rep(i,2,n)add_(read(),read());
    dfs(1,0),Dfs(1,1),build(Root);
    repm(i){
        node nw;
        nw.id=i;
        int x=read(),k=read();
        rep(o,1,k)nw.p.pb(read());
        p[x].pb(nw);
    }
    Dfs(1);
    repm(i)pf(out[i]),putchar('\n');
    return 0;
}
```


---

## 作者：sunkuangzheng (赞：4)

首先我们有经典结论：距离点 $x$ 最远的点是树的直径端点之一。那么我们每次只需要维护连通子图的直径。

考虑每次不能到达的点是一段连续的 dfn 区间，容易求出能到达的点范围也是 $\mathcal O(k)$ 个连续的 dfn 区间。用线段树维护区间点的直径，把每一次询问可以到的点合并起来得到直径即可。

怎么用线段树维护区间点的直径？这需要结论：两个连通块合在一起的直径端点一定是原本连通块直径的端点。据此枚举端点，取最长的保留即可。

尽量写个 $\mathcal O(1)$ 的 LCA 吧，否则合并会多带个 $\log$。用 st 表 LCA，时间复杂度 $\mathcal O(n \log n + \sum k \log n)$。

~~下面给出的代码使用倍增 LCA，时间复杂度 $\mathcal O(n \log^2 n + \sum k \log ^2 n)$，常数巨大，跑了 3.8 秒。~~

upd：倍增被 hack TLE 了，换成 st 表了。

```cpp
// LUOGU_RID: 139275498
/**
 *    author: sunkuangzheng
 *    created: 12.12.2023 07:52:35
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
using namespace std;
const int N = 5e5+5;
int n,fa[N][23],dep[N],dfn[N],nfd[N],st[N][22],tot,siz[N],m,u,v,k,x;vector<int> g[N];
int cmp(int u,int v){return dfn[u] < dfn[v] ? u : v;}
inline void dfs(int u,int f){
    fa[u][0] = f,dep[u] = dep[f] + 1,dfn[u] = ++tot,nfd[tot] = u,siz[u] = 1,st[dfn[u]][0] = f;
    for(int i = 1;i <= 22;i ++) fa[u][i] = fa[fa[u][i-1]][i-1];
    for(int v : g[u]) if(v != f) dfs(v,u),siz[u] += siz[v];
}inline int lca(int u,int v){
    if(u == v) return u;
    if((u = dfn[u]) > (v = dfn[v])) swap(u,v);
    int k = __lg(v - u);
    return cmp(st[u+1][k],st[v-(1<<k)+1][k]);
}int kfa(int u,int k){
    for(int i = 22;i >= 0;i --) if((k >> i) & 1) u = fa[u][i];
    return u;
}struct node{int u,v;}t[N*4];
inline int dis(node x){return dep[x.u] + dep[x.v] - 2 * dep[lca(x.u,x.v)];}
inline node mg(node a,node b){
    if(!a.u) return b; if(!b.u) return a;
    vector<int> acc = {a.u,b.u,a.v,b.v};int mx = -1;node ans = {0,0};
    for(int i : acc) for(int j : acc) if(auto x = ((node){i,j});dis(x) > mx) mx = dis(x),ans = x;
    return ans;
}inline void build(int s,int l,int r){
    if(l == r) return t[s] = (node){nfd[l],nfd[l]},void();
    int mid = (l + r) / 2;build(s*2,l,mid),build(s*2+1,mid+1,r);
    t[s] = mg(t[s*2],t[s*2+1]);
}inline node qry(int s,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr) return t[s];
    int mid = (l + r) / 2;
    if(qr <= mid) return qry(s*2,l,mid,ql,qr); if(ql > mid) return qry(s*2+1,mid+1,r,ql,qr);
    return mg(qry(s*2,l,mid,ql,qr),qry(s*2+1,mid+1,r,ql,qr));
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> m;vector<pair<int,int>> acc,cjr;
    for(int i = 1;i < n;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);
    dfs(1,0);
    for(int j = 1;j <= __lg(n);j ++) for(int i = 1;i + (1 << j) - 1 <= n;i ++)
        st[i][j] = cmp(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    build(1,1,n);
    auto add = [&](int l,int r){if(l <= r) acc.emplace_back(l,r);};
    while(m --){
        cin >> u >> k,acc.clear(),cjr.clear();
        while(k --){
            cin >> x;
            if(lca(u,x) == x){
                int v = kfa(u,dep[u] - dep[x] - 1);
                add(1,dfn[v] - 1),add(dfn[v] + siz[v],n);
            }else add(dfn[x],dfn[x] + siz[x] - 1); 
        }sort(acc.begin(),acc.end());
        int lst = 0;node ans = {0,0};
        for(auto [l,r] : acc){
            if(l > lst + 1) cjr.emplace_back(lst + 1,l - 1);
            lst = max(lst,r);
        }if(lst != n) cjr.emplace_back(lst+1,n);
        for(auto [l,r] : cjr) ans = mg(ans,qry(1,1,n,l,r));
        node p = (node){ans.u,u},q = (node){ans.v,u};cout << max(dis(p),dis(q)) << "\n";
    }
}
```

题外话：不知道为什么官方题解提供的两种解法都用欧拉序，dfs 序不是更好理解吗 qwq。

---

## 作者：EityDawn (赞：2)

## 思路：

离线 + 分块。

观察一下性质发现，一个点不能经过等价于将树分成两部分。

最后我们要确定 $x$ 所在联通块的范围。

对于不能经过的点 $a_i$，我们先找出在 $x$ 到 $1$ 路径上深度最深的 $a_i$，记为 $y$，如果没有 $y$ 默认为 $1$。这一步可以树上倍增来求。

$x$ 所在联通块的就是 $y$ 这棵子树的子集。

对于剩下的 $a_i$，如果 $a_i$ 在 $y$ 这棵子树内，那么 $a_i$ 这棵子树不可达，无效。

把树拍平，按照 dfs 序对应到区间上，$y$ 这棵子树对应的区间 $[l,r]$。$y$ 子树内不可达的 $a_i$ 对应的子树区间为 $[l_i,r_i]$，设这些区间的并集为 $S$，那么我们就是要询问以 $x$ 为根时，对应的区间集合 $[l,r]\setminus S$，即当 $[l,r]$ 是全集的时候，$S$ 的补集中，到 $x$ 距离最远的点。

那么如何求到 $x$ 最远的点？

考虑先求出以 $1$ 为根时所有点的距离，利用换根思想，对于根从 $u\rightarrow v$ 时，$v$ 这棵子树内的点到 $v$ 的比在原来到 $u$ 的基础上减少 $1$，这一步就是子树加减 $1$ 的操作，而对于其他点，到 $v$ 的距离比原来到 $u$ 的距离增加了 $1$，修改时直接全局加 $1$ ，子树减 $2$ 就行了。

时间复杂度为 $O(n\log n+n\sqrt n)$，如果用其他数据结构例如线段树可以 $O(n\log n)$。

## code

```cpp
const int N=2e5+10,M=450;
struct Query{
	int l,r,id;
	vector<pair<int,int>>Seg;
};
vector<Query>S[N];
int Be[N],L[M],R[M],ma[M],add[M];
int n,m,dep[N],rt=1;
int dfn[N],ID[N],siz[N],t=0;
int fa[N][21],Ans[N];
vector<int>G[N];
void dfs(int now,int from)
{
	ID[dfn[now]=++t]=now;siz[now]=1;	
	for(int i=1;(1<<i)<=dep[now];i++)
		fa[now][i]=fa[fa[now][i-1]][i-1];
	for(int to:G[now])
	{
		if(to==from) continue;
		dep[to]=dep[now]+1,fa[to][0]=now;
		dfs(to,now);
		siz[now]+=siz[to];
	}
	return;
}
int LCA(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;~i;i--)
		if((1<<i)<=dep[x]-dep[y]) x=fa[x][i];
	if(x==y) return x;
	for(int i=20;~i;i--)
		if(fa[x][i]^fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
#define fi(x) x.first
#define se(x) x.second
void build()
{
	int len=sqrt(n),t=n/len+bool(n%len);
	for(int i=1;i<=n;i++)
	{
		Be[i]=(i-1)/len+1;
		if(!L[Be[i]]) L[Be[i]]=i;
		R[Be[i]]=i;
	}
	for(int i=1;i<=t;i++)
		for(int j=L[i];j<=R[i];j++) ma[i]=max(ma[i],dep[ID[j]]);
	return;
}
inline int query(int l,int r)
{
	if(l>r) return -1;
	int res=0;
	if(Be[l]==Be[r]){
		for(int i=l;i<=r;i++)
			res=max(res,dep[ID[i]]+add[Be[l]]);
	}
	else{
		for(int i=l;i<=R[Be[l]];i++) res=max(res,dep[ID[i]]+add[Be[l]]);
		for(int i=L[Be[r]];i<=r;i++) res=max(res,dep[ID[i]]+add[Be[r]]);
		for(int i=Be[l]+1;i<=Be[r]-1;i++) res=max(res,ma[i]+add[i]);
	}
	return res;
}
inline void rebuild(int now)
{
	ma[now]=0;
	for(int i=L[now];i<=R[now];i++) 
		ma[now]=max(ma[now],dep[ID[i]]);
	return;
}
inline void modify(int l,int r,int val)
{
	if(Be[l]==Be[r]){
		for(int i=l;i<=r;i++)
			dep[ID[i]]+=val;
		rebuild(Be[l]);
	}
	else{
		for(int i=l;i<=R[Be[l]];i++) dep[ID[i]]+=val;
		for(int i=L[Be[r]];i<=r;i++) dep[ID[i]]+=val;
		rebuild(Be[l]);rebuild(Be[r]);
		for(int i=Be[l]+1;i<=Be[r]-1;i++) add[i]+=val;
	}
	return;
}
void calc(int now,int from)
{
	for(auto [l,r,id,Seg]:S[now])
	{
		int res=0;
		if(!Seg.size()) res=max(res,query(l,r));
        //注意特判 y 子树都合法的情况
		else{
			sort(Seg.begin(),Seg.end());
			int up=Seg.size()-1;
			int mi=n+1,ma=-1;
			for(auto [pl,pr]:Seg) mi=min(mi,pl),ma=max(ma,pr);
			if(mi>l) res=max(res,query(l,mi-1));
			if(ma<r) res=max(res,query(ma+1,r));
            //两端可能还有合法区间
			ma=se(Seg[0]);
			for(int i=1;i<=up;i++)
			{
				if(fi(Seg[i])<=ma) continue;
				res=max(res,query(ma+1,fi(Seg[i])-1));
				ma=se(Seg[i]);
			}
            //询问补集
		}
		Ans[id]=res;
	}
	for(int to:G[now])
	{
		if(to==from) continue;
		modify(dfn[to],dfn[to]+siz[to]-1,-2),modify(1,n,1);//换根
		calc(to,now);
		modify(dfn[to],dfn[to]+siz[to]-1,2),modify(1,n,-1);//记得换回来
	}
}
int main()
{
	read(n,m);
	for(int i=1,x,y;i<n;i++)
	{
		read(x,y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	dfs(rt,0);build();
	int x,k;
	for(int i=1;i<=m;i++)
	{
		read(x,k);
		vector<int>d;
		int up=dfn[rt],w=rt;
		for(int j=1,y,z;j<=k;j++)
		{
			read(y);d.push_back(y);
			if(LCA(x,y)==y){
				z=x;
				for(int p=20;~p;p--)
					if(fa[z][p]&&dep[fa[z][p]]>dep[y]) z=fa[z][p];
				if(dfn[z]>up) up=dfn[z],w=z;//倍增求 y
			}
		}
		vector<pair<int,int>>c;
		for(int to:d)
		{
			if(to==w) continue;
			if(LCA(to,w)==w)
				c.push_back({dfn[to],dfn[to]+siz[to]-1});
           	//把不可达的子树对应区间抠出来
		}	
		S[x].push_back({dfn[w],dfn[w]+siz[w]-1,i,c});
	}
	calc(rt,0);
	for(int i=1;i<=m;i++) write(Ans[i],'\n');
    return 0;
}
```

---

## 作者：toolong114514 (赞：2)

# CF1904E Tree Queries 题解
第一次见到需要换根的树上问题，记录一下。
## 题面大意
[传送门。](https://www.luogu.com.cn/problem/CF1904E)
## 解题思路
我们先考虑一个弱化的问题：在 $x$ 一定的情况下，怎么求答案？

这时，只要钦定 $x$ 为树根跑 dfs，得到的树上各点深度就是它们与 $x$ 之间的距离。对于输入的限制点 $a_i$，只要去除当前以 $a_i$ 为根的子树的贡献即可，用 dfs 序配线段树做是容易的。

这样做的时间复杂度为 $O(n\log{n})$，如果对不同的 $x$ 都跑一遍就会变成 $O(n^2\log{n})$，过不了，考虑换根。

首先将询问离线，将其挂在对应的点上，然后钦定 $1$ 号点为树根跑 dfs，每跑到一个点就处理挂在当前点的所有询问。

接下来处理换根后的深度变化。

真的去改变树的结构是不必要的，只需要基于原来的树，调整需要的信息即可。（感觉 LCT 有真正实现的可能）

我们只需讨论根从一个点变化到其子节点的影响。

向下到子节点时，容易发现其子树中的节点与其距离都减少了 $1$，而其它节点则增加了 $1$。

事实上，将树拍成 dfs 序的话，可以转成区间修改问题，用线段树维护是容易的。

从某个节点返回父亲同理，推导是简单的。

我们还需要讨论每次询问中，限制点的影响。

在钦定树根的情况下，直接抹掉其子树的贡献即可，但是在树形态不变的情况下，需要分类讨论。

### Case1：根不在限制点的子树中（最后向下走）
以样例 $1$ 为例，用图简要说明。

![](https://cdn.luogu.com.cn/upload/image_hosting/71kmqk23.png)

如图，标黑的点是“树根”，标红点为限制点。

要通往红色点所在子树中的点，必须向下走过红点，所以红色点的子树无法产生贡献，要剔除掉。

这时直接子树修改即可。
### Case1：根在限制点的子树中（最后向上走）
图还是样例 $1$ 的：

![](https://cdn.luogu.com.cn/upload/image_hosting/d3fa4siu.png)

此时的活动范围仅限于限制点的儿子中，包含黑点的子树。

其它的贡献直接剔除。

修改范围是所有点去掉这颗子树，处理是简单的。

抹去贡献的操作，就是直接对这些点的深度值 $-n$，算完答案在加回来。

最后，询问的答案即为此时所有深度的最大值。

时间复杂度约为 $O(n\log{n}+\sum{k}\log{n})$，可以通过本题。


## 参考代码
写得太乱了，凑合看着吧……

几乎没压行，跑得超慢。

~~史要分享给大家一起吃。~~

### [Code](https://www.luogu.com.cn/paste/kpq543y0)

[本代码可以通过 CF 的评测。](https://www.luogu.com.cn/record/166966568)

Written by [toolong114514](https://www.luogu.com/user/477821) on 2024/7/18.

---

## 作者：_AyachiNene (赞：2)

来一发 ddp 题解。
# 思路：
看到这道题很容易想到要先分讨一下。

第一种情况：最长路径在子树内。这种情况很简单，如果一个不能走的点在当前根的子树内，那么可以把这个点的子树的深度都赋成负无穷，最长路径显然就是查询的根的子数内的深度最大值减根的深度。线段树维护即可。

第二种情况子树外稍微复杂点。首先在根的子数内的点已经算过了，是不能走的，不妨把深度全设为负无穷。这时，答案就变成了**在选定的根到任意一个你钦定的且不会变的根上的路径上找一个点，在这个点不包含选定根的子树中找一个深度最大点。** 这么说稍微有点绕，画个图来解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/uq0ficpm.png)

假设 $1$ 为我钦定的根节点，$4$ 为我查询的点。在 $2$ 号点的时候，在以 $5$ 为根的子树中能找到最大值，为 $7$ 号或 $8$ 号，而不能找到 $6$ 号，否则不是简单路径。

之后就是怎么维护了。子树内不必多说，主要讲下子树外。首先肯定是要上树剖的，因为要维护子树和路径。然后可以推下式子。如果我查询点是的深度为 $x$，在根到这个点的路径上有一个点的深度为 $y$，在这个点中深度最大的点深度为 $z$，那么最长路径长度为 $x+z-2y$。$x$ 为定值，所以要维护 $z-2y$ 的最大值，用什么数据结构都可以，在每个点都开一个，来维护子树中最大 $z-2y$，这里推荐用双堆，因为最快。还有一个很重要的限制条件就是**找答案的子树不能包含查询点**。对于这个限制可以用树剖维护轻链解决。树剖有一个性质，就是跳一次链只会有 $\log n$ 条轻链，在每个点先维护好轻儿子的值，一次修改时，最多有 $\log n$ 个轻儿子被改，直接改即可。考虑最后统计答案，如果从一条轻链跳上去，那么这个轻儿子就不能选了，把它删了从重儿子里查即可，如果从重儿子上去，就是所有轻儿子的答案，再跳到第一个不能走的点就停下，在处理不能走的点，只用把路径外的处理了，并维护路径上深度最大的不能走的点，就做完了，复杂度 $O(n \log^2 n)$，用 lct 或全局平衡二叉树可以少只 $\log$ 但我太菜了不会。~~其实想到这里还远没做完~~。写起来是真的难写，细节是真的多，模拟赛想到思路死磕这道题导致爆零了，这里推荐建一个虚点连向钦定的根节点，这样就不用特判根节点的情况，然后就是注意下清空就行了。所有细节代码里都有提到。

# Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
struct node
{
	int nxt,to;
}e[114514<<2];
int head[114514<<1],cnt_edge;
inline void add_edge(int u,int v)
{
	e[++cnt_edge].to=v;
	e[cnt_edge].nxt=head[u];
	head[u]=cnt_edge;
}
int w[3][114514<<1];
struct Elaina
{
	struct segt
	{
		int l,r,val,tag,tmp;//tag=114为还原回初始值 
	}t[114514<<3];
	#define ls (root<<1)
	#define rs (root<<1|1)
	#define mid (t[root].l+t[root].r>>1)
	inline void update(int root){t[root].val=max(t[ls].val,t[rs].val);}
	inline void down(int root)
	{
		t[ls].tag=t[root].tag;
		t[rs].tag=t[root].tag;
		if(t[root].tag==114) t[ls].val=t[ls].tmp,t[rs].val=t[rs].tmp;
		else t[ls].val=t[root].tag,t[rs].val=t[root].tag;
		t[root].tag=0;
	}
	void bld(int l,int r,int root,int op)
	{
		t[root].l=l;t[root].r=r;
		if(l==r)
		{
			t[root].val=t[root].tmp=w[op][l];
			return;
		}
		bld(l,mid,ls,op);bld(mid+1,r,rs,op);
		update(root);
		t[root].tmp=max(t[ls].val,t[rs].val);
	}
	void cover(int x,int y,int root,int v)
	{
		if(t[root].l>=x&&t[root].r<=y)
		{
			t[root].val=v;
			t[root].tag=v;
			if(v==114) t[root].val=t[root].tmp;
			return;
		}
		if(t[root].tag) down(root);
		if(x<=mid) cover(x,y,ls,v);
		if(y>mid) cover(x,y,rs,v);
		update(root);
	}
	int query(int x,int y,int root)
	{
		if(t[root].l>=x&&t[root].r<=y) return t[root].val;
		int res=-1e9;
		if(t[root].tag) down(root);
		if(x<=mid) res=max(res,query(x,y,ls));
		if(y>mid) res=max(res,query(x,y,rs));
		return res;
	}
}ts,tf;
struct Chtholly //双堆做插入，删除，求最大，可以用multiset，只是要tle 
{
    priority_queue<int>h,d;
    inline void insert(int x){h.push(x);}
	inline void del(int x){d.push(x);}
    inline int query()
	{
        while(!d.empty()&&h.top()==d.top()) h.pop(),d.pop();
        return h.top();
    }
}heap[114514<<1];
int n,q;
int maxdep[114514<<1];
int dep[114514<<1],f[114514<<1],siz[114514<<1],son[114514<<1],top[114514<<1],dfn[114514<<1],cnt;
inline int check(int x,int y) //判断x是否在y的子树内 
{
	return dfn[x]>=dfn[y]&&dfn[x]<=dfn[y]+siz[y]-1;
}
void dfs1(int u,int fa)
{
	f[u]=fa;
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		maxdep[v]=dep[v]=dep[u]+1;
		dfs1(v,u);
		siz[u]+=siz[v];
		maxdep[u]=max(maxdep[u],maxdep[v]);
		if(siz[son[u]]<siz[v]) son[u]=v;
	}
}
void dfs2(int u,int t)
{
	top[u]=t;
	dfn[u]=++cnt;
	w[1][cnt]=dep[u];
	heap[u].insert(-1e9);
	if(son[u]) dfs2(son[u],t);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f[u]||v==son[u]) continue;
		heap[u].insert(maxdep[v]-2*dep[u]);
		dfs2(v,v);
	}
}
int opt[1145141<<1],p[1145141<<1],val[1145141<<1],tp; //记录要还原的点 
inline void del_tree(int x)
{
	while(top[x]!=top[n])
	{
		int v=f[top[x]];
		int w=ts.query(dfn[top[x]],dfn[top[x]]+siz[top[x]]-1,1)-2*dep[v];
		opt[++tp]=1;
		p[tp]=v;
		val[tp]=w;
		heap[v].del(w);
		x=v;
	}
}
inline void insert_tree(int x)
{
	while(top[x]!=top[n])
	{
		int v=f[top[x]];
		int w=ts.query(dfn[top[x]],dfn[top[x]]+siz[top[x]]-1,1)-2*dep[v];
		opt[++tp]=2,val[tp]=w,p[tp]=v;
		heap[v].insert(w);
		tf.cover(dfn[v],dfn[v],1,heap[v].query());
		x=v;
	}
}
inline int query_tree(int x,int y)
{
	int res=-1e9;
	while(top[x]!=top[y])
	{
	 	res=max(res,tf.query(dfn[top[x]],dfn[f[x]],1)); //从f[x]开始算是因为x在上一条连被算过了，且第一个点不能算 
		int v=f[top[x]];
		int tmp=ts.query(dfn[top[x]],dfn[top[x]]+siz[top[x]]-1,1)-2*dep[v]; //先删了在算重链 
		heap[v].del(tmp);
		if(v!=y) res=max(res,max(heap[v].query(),ts.query(dfn[son[v]],dfn[son[v]]+siz[son[v]]-1,1)-2*dep[v]));
		heap[v].insert(tmp);
		x=v;
 	} 
	res=max(res,max(tf.query(dfn[y]+1,dfn[f[x]],1),-dep[son[y]]));//有可能查不到值，最少答案也有路径的长度所以要加-dep[son[y]] 
	return res;
}
int a[114514<<1];
int main()
{
	freopen("ex_tree1.in","r",stdin);
	freopen("tree.out","w",stdout);
	read(n,q);
	for(int i=1;i<n;i++)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);add_edge(v,u);
	}
	++n; //建虚点 
	add_edge(n,1);add_edge(1,n);
	dfs1(n,0);dfs2(n,n);
	for(int i=1;i<n;i++) w[2][dfn[i]]=heap[i].query();
	w[1][dfn[n]]=w[2][dfn[n]]=-1e9;
 	ts.bld(1,n,1,1);
	tf.bld(1,n,1,2);
	while(q--)
	{
		tp=0;
		int x,k;
		read(x,k);
		for(int i=1;i<=k;i++) read(a[i]);
		int maxp=n;
		for(int i=1;i<=k;i++)
			if(check(a[i],x)) ts.cover(dfn[a[i]],dfn[a[i]]+siz[a[i]]-1,1,-1e9);
		int ans=ts.query(dfn[x],dfn[x]+siz[x]-1,1)-dep[x];
		for(int i=1;i<=k;i++)
			if(check(a[i],x)) ts.cover(dfn[a[i]],dfn[a[i]]+siz[a[i]]-1,1,114); //子树内 
		if(x==1) //根等于1可以不用跑 
		{	
			write(ans),putch('\n');
			continue;
		}
		del_tree(x); //子树外，先把子树内的贡献清0 
		ts.cover(dfn[x],dfn[x]+siz[x]-1,1,-1e9);
		insert_tree(x);
		for(int i=1;i<=k;i++)
		{
			if(!check(x,a[i])&&!check(a[i],x))
			{
				del_tree(a[i]);
				ts.cover(dfn[a[i]],dfn[a[i]]+siz[a[i]]-1,1,-1e9);
				insert_tree(a[i]);
			}
			if(check(x,a[i])&&dep[maxp]<dep[a[i]]) maxp=a[i]; //找第一个不能走的点 
		}
		ans=max(dep[x]+query_tree(x,maxp),ans);
		ts.cover(1,n,1,114);
		tf.cover(1,n,1,114);
		for(int i=tp;i>=1;i--)  //注意要倒序还原 
			if(opt[i]==1) heap[p[i]].insert(val[i]);
			else heap[p[i]].del(val[i]);
		write(ans),putch('\n');
	}
	flush();
	return 0;
}
```

---

## 作者：happybob (赞：1)

假如每次询问的点 $x$ 是同一个点怎么做？我们考虑将这棵无根树看作以 $x$ 为根的树，设根 $x$ 的深度为 $0$，那么每个点到 $u$ 的距离就是这个点的深度 $dep_u$。删掉一个点 $y$ 本质上就是删掉以 $y$ 为根的这棵子树，询问相当于问全局最大值。每个删除的点显然在 DFS 序上是一个区间，于是可以求出没有被删除的所有区间。于是我们容易在 $O(n \log n)$ 的时间复杂度内单次回答。

但是问题在于，$x$ 可能不同。比较显然的做法是离线换根。类似换根 DP。我们设树根为 $1$。现在我们要将根从 $u$ 变成其某个儿子 $v$。考虑深度的变化。比较套路的是以 $v$ 为子树的点深度减 $1$，其他点加 $1$。这都可以用线段树维护 DFS 序上的区间加维护。

考虑第二部分，即对于当前换到的根 $u$，删掉点 $v$ 的本质。如果 $v$ 不在 $1\sim u$ 的路径上，即 $v$ 不是 $u$ 的祖先，那么删掉的就是 $v$ 的子树，否则 $v$ 为 $u$ 的祖先。那么 $u$ 只能到 $v$ 下面往 $u$ 走一步的那个点的子树内，即相当于保留一个区间，就是删掉 $[1,n]$ 减去这个区间。于是整个题就做完了。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <array>
using namespace std;

const int N = 2e5 + 5;

vector<int> G[N];
int n, q;
int dep[N], id[N], sz[N], idx;
int fa[N][21];

struct Query
{
	vector<int> ver;
	int id;
	Query()
	{
		id = 0;
		ver.clear();
	}
	Query(vector<int>& v, int id) : ver(v), id(id) {}
};

vector<Query> qry[N];

class SegmentTree
{
public:
	struct Node
	{
		int l, r, tag, maxn;
	}tr[N << 2];
	void pushup(int u)
	{
		tr[u].maxn = max(tr[u << 1].maxn, tr[u << 1 | 1].maxn);
	}
	void pushtag(int u, int v)
	{
		tr[u].tag += v;
		tr[u].maxn += v;
	}
	void pushdown(int u)
	{
		if (tr[u].tag)
		{
			pushtag(u << 1, tr[u].tag);
			pushtag(u << 1 | 1, tr[u].tag);
			tr[u].tag = 0;
		}
	}
	void build(int u, int l, int r, int* a)
	{
		tr[u] = { l, r, 0, a[l] };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid, a);
		build(u << 1 | 1, mid + 1, r, a);
		pushup(u);
	}
	void update(int u, int l, int r, int c)
	{
		if (tr[u].l >= l and tr[u].r <= r)
		{
			pushtag(u, c);
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) update(u << 1, l, r, c);
		if (r > mid) update(u << 1 | 1, l, r, c);
		pushup(u);
	}
	int query(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r) return tr[u].maxn;
		pushdown(u);
		int res = 0, mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) res = query(u << 1, l, r);
		if (r > mid) res = max(res, query(u << 1 | 1, l, r));
		return res;
	}
}sgt;

int na[N];
array<int, N> ans;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= q; i++)
	{
		int u;
		cin >> u;
		vector<int> v;
		int k;
		cin >> k;
		for (int j = 1; j <= k; j++)
		{
			int b;
			cin >> b;
			v.emplace_back(b);
		}
		qry[u].emplace_back(Query(v, i));
	}
	auto dfs = [&](auto self, int u, int f)->void
		{
			fa[u][0] = f;
			dep[u] = dep[f] + 1;
			sz[u] = 1;
			id[u] = ++idx;
			for_each(G[u].begin(), G[u].end(), [&](const auto& j) {
				if (j != f)
				{
					self(self, j, u);
					sz[u] += sz[j];
				}
				});
		};
	dep[0] = -1;
	dfs(dfs, 1, 0);
	for (int j = 1; j <= 20; j++)
	{
		for (int i = 1; i <= n; i++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
	}
	auto kth_anc = [&](int u, int k)
		{
			int c = 0;
			while (k)
			{
				if (k & 1) u = fa[u][c];
				c++;
				k >>= 1;
			}
			return u;
		};
	for (int i = 1; i <= n; i++)
	{
		na[id[i]] = dep[i];
	}
	sgt.build(1, 1, n, na);
	auto solve = [&](auto self, int u, int f)->void
		{
			for (auto& [v, idx] : qry[u])
			{
				vector<pair<int, int>> segs;
				int ans = 0;
				int maxr = 0;
				for (auto& j : v)
				{
					if (j == u)
					{
						::ans[idx] = 0;
						goto E;
					}
					if (id[u] >= id[j] && id[u] < id[j] + sz[j])
					{
						int dis = dep[u] - dep[j];
						int sj = kth_anc(u, dis - 1);
						// 只能去 [id[sj], id[sj] + sz[sj])
						if (id[sj] != 1) segs.emplace_back(make_pair(1, id[sj] - 1));
						if (id[sj] + sz[sj] != n + 1) segs.emplace_back(make_pair(id[sj] + sz[sj], n));
					}
					else
					{
						segs.emplace_back(make_pair(id[j], id[j] + sz[j] - 1));
					}
				}
				for (auto& [l, r] : segs) maxr = max(maxr, r);
				sort(segs.begin(), segs.end());
				if (segs.size() && segs.front().first != 1) ans = sgt.query(1, 1, segs.front().first - 1);
				if (segs.size() && maxr != n) ans = max(ans, sgt.query(1, maxr + 1, n));
				if (segs.empty()) ans = max(ans, sgt.tr[1].maxn);
				maxr = 0;
				for (int k = 0; k + 1 < segs.size(); k++)
				{
					maxr = max(maxr, segs[k].second);
					if (segs[k + 1].first > maxr)
					{
						int l = maxr + 1, r = segs[k + 1].first - 1;
						if (l <= r) ans = max(ans, sgt.query(1, l, r));
					}
				}
				::ans[idx] = ans;
			E:;
			}
			for (auto& j : G[u])
			{
				if (j == f)
				{
					continue;
				}
				sgt.update(1, id[j], id[j] + sz[j] - 1, -1);
				if (id[j] != 1) sgt.update(1, 1, id[j] - 1, 1);
				if (id[j] + sz[j] <= n) sgt.update(1, id[j] + sz[j], n, 1);
				self(self, j, u);
				sgt.update(1, id[j], id[j] + sz[j] - 1, 1);
				if (id[j] != 1) sgt.update(1, 1, id[j] - 1, -1);
				if (id[j] + sz[j] <= n) sgt.update(1, id[j] + sz[j], n, -1);
			}
		};
	solve(solve, 1, 0);
	for (int i = 1; i <= q; i++)
	{
		cout << ans[i] << "\n";
	}
	return 0;
}
```


---

## 作者：Code_星云 (赞：1)

很套路的的题吧。

首先考虑把询问离线，并把每个询问放到 $x$ 上去处理。动态维护每个点到任意点的距离可以用 dfs 序上线段树来维护。具体地，进入一个子树则子树距离减一，子树外加一。

然后考虑如何处理不能走的点。我们发现，不能走的点 $k$ 和 $x$ 有两种情况：

1. $k$ 是 $x$ 的祖先节点，那么我们则需要覆盖除了 $k$ 向 $x$ 方向的子节点以外的所有点。
2. 否则，我们只需要覆盖 $k$ 的子树即可。

上述的覆盖操作也可以用线段树简单完成。同时，为了避免覆盖打标记的操作，我们只需要使那个区间的值减去 $n$ 即可，这样那些点一定不会成为最大值。另外，判断一个点是否是另一个点的祖先以及寻找某方向的子节点可以用倍增实现，具体看代码。

总复杂度 $O((n+\sum k) \log n)$。

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define int long long
#define pb push_back
#define lc (x << 1)
#define rc (x << 1 | 1)

const int N = 200005;
struct node{int s, k, ans; vector<int> v;}; node qs[N];
int n, q, idx, sz[N], rec[N], dfn[N], dep[N], bar[N], f[N][22];
vector<int> g[N], qb[N];

namespace sgtree{
	struct segtree{
		int l, r, add, maxn;
		#define l(x) tree[x].l
		#define r(x) tree[x].r
		#define add(x) tree[x].add
		#define maxn(x) tree[x].maxn
	};
	segtree tree[N << 2];
	void pushup(int x){maxn(x) = max(maxn(lc), maxn(rc));}
	void pushadd(int x, int val){add(x) += val; maxn(x) += val;}
	void pushdown(int x){if(add(x)){pushadd(lc, add(x)); pushadd(rc, add(x)); add(x) = 0;}}
	void build(int x, int l, int r){
		l(x) = l; r(x) = r; add(x) = 0;
		if(l == r){maxn(x) = dep[rec[l]] - dep[1]; return;}
		int mid = (l + r) >> 1;
		build(lc, l, mid); build(rc, mid + 1, r);
		pushup(x);
	}
	void modify(int x, int l, int r, int val){
		if(l <= l(x) && r(x) <= r){pushadd(x, val); return;}
		pushdown(x); int mid = (l(x) + r(x)) >> 1;
		if(l <= mid) modify(lc, l, r, val);
		if(r > mid) modify(rc, l, r, val);
		pushup(x);
	}
};
using namespace sgtree;

void dfs(int u, int fa){
	f[u][0] = fa; dep[u] = dep[fa] + 1; rec[dfn[u] = ++ idx] = u; sz[u] = 1;
	for(int i = 1; i <= 21; i ++) f[u][i] = f[f[u][i - 1]][i - 1];
	for(auto v: g[u]){if(v == fa) continue; dfs(v, u); sz[u] += sz[v];}
}
bool isfa(int s, int t){
	if(dep[t] >= dep[s]) return false;
	for(int i = 21; i >= 0; i --) if(dep[f[s][i]] >= dep[t]) s = f[s][i];
	if(s == t) return true; else return false;
}
int getfa(int s, int d){
	if(d == dep[s]) return s;
	for(int i = 21; i >= 0; i --) if(dep[f[s][i]] >= d) s = f[s][i];
	return s; 
}
void work(int u){
	for(auto id: qb[u]){
		int s = qs[id].s; bool flag = false;
		for(auto t: qs[id].v){
			if(s == t){qs[id].ans = 0; flag = true; break;}
			if(isfa(s, t)){
				int pl = getfa(s, dep[t] + 1);
				if(1 <= dfn[pl] - 1) modify(1, 1, dfn[pl] - 1, - n);
				if(dfn[pl] + sz[pl] <= n) modify(1, dfn[pl] + sz[pl], n, - n);
			}else modify(1, dfn[t], dfn[t] + sz[t] - 1, - n); 
		}
		if(! flag) qs[id].ans = maxn(1);
		for(auto t: qs[id].v){
			if(s == t) break;
			if(isfa(s, t)){
				int pl = getfa(s, dep[t] + 1);
				if(1 <= dfn[pl] - 1) modify(1, 1, dfn[pl] - 1, n);
				if(dfn[pl] + sz[pl] <= n) modify(1, dfn[pl] + sz[pl], n, n);
			}else modify(1, dfn[t], dfn[t] + sz[t] - 1, n);
		}
	}
	for(auto v: g[u]){
		if(v == f[u][0]) continue; 
		modify(1, dfn[v], dfn[v] + sz[v] - 1, -1);
		if(1 <= dfn[v] - 1) modify(1, 1, dfn[v] - 1, 1);
		if(dfn[v] + sz[v] <= n) modify(1, dfn[v] + sz[v], n, 1);
		work(v);
		modify(1, dfn[v], dfn[v] + sz[v] - 1, 1);
		if(1 <= dfn[v] - 1) modify(1, 1, dfn[v] - 1, -1);
		if(dfn[v] + sz[v] <= n) modify(1, dfn[v] + sz[v], n, -1);
	}
}
signed main(){
	scanf("%lld %lld", &n, &q);
	for(int i = 1; i < n; i ++){
		int u, v; scanf("%lld %lld", &u, &v);
		g[u].pb(v); g[v].pb(u);
	}
	dfs(1, 0); build(1, 1, n);
	for(int i = 1; i <= q; i ++){
		scanf("%lld %lld", &qs[i].s, &qs[i].k);
		for(int j = 1; j <= qs[i].k; j ++){
			int tmp; scanf("%lld", &tmp);
			qs[i].v.pb(tmp);
		}
		qb[qs[i].s].pb(i);
    }
    work(1);
    for(int i = 1; i <= q; i ++) printf("%lld\n", qs[i].ans);
    return 0;
}
```

---

## 作者：ForgotDream_CHN (赞：1)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17892861.html)

> 给定一棵 $n$ 个节点的树与 $q$ 次询问，每次询问给出一个 $x$ 与一个大小为 $k$ 的点集 $a$，要求求出在删去了 $a$ 中的点后从 $x$ 出发的最长简单路径的长度。每次询问独立。
>
> $n, q, \sum k \le 2 \times 10^5$。

一些记号：

+ $p_i$ 表示时间戳 $i$ 对应的节点
+ $c_u$ 表示节点 $u$ 的时间戳
+ $s_u$ 表示节点 $u$ 的子树大小
+ $d_u$ 表示节点 $u$ 的深度
+ $\operatorname{in}(u) = c_u$，即在 DFS 过程中进入节点 $u$ 的时间
+ $\operatorname{out}(u) = c_u + s_u - 1$，即在 DFS 过程中离开节点 $u$ 的时间
+ $\operatorname{nxt}(u, v)$ 表示在 $u \to v$ 的路径上的第二个节点，其中 $u$ 为 $v$ 的祖先。

思考「删点」这个过程的本质，可以发现，若以每次询问的 $x$ 作为根节点，那么删点本质上就是使得某个点以及其子树内的点都无法被访问到，而「子树」这一条件则很容易让我们想到 DFS 序。于是删除点 $u$ 也就是意味着 DFS 序处在 $[\operatorname{in}(u), \operatorname{out}(u)]$ 的节点无法被访问了。

但是如果以每次询问的 $x$ 作为根节点，那就相当于每次询问都要重新构造 DFS 序，复杂度肯定是爆炸的，因此我们考虑如何在根节点固定为 $1$ 的情况下表示上述的过程。

画一个图，我们就很容易得到：对于一个点 $u$ 以及一个待删除的点 $v$，我们很容易发现，若 $v$ 为 $u$ 的祖先，那么删去 $v$ 会导致除去 $\operatorname{nxt}(v, u)$ 所在的子树外，其他的节点，也就是 DFS 序位于 $[1, \operatorname{in}(\operatorname{nxt}(v, u)) - 1]$ 以及 $[\operatorname{out}(\operatorname{nxt}(v, u)) + 1, n]$ 的节点，都无法被访问了。而如果 $v$ 不是 $u$ 的祖先，那么跟根不固定的情况没有区别，都是 DFS 位于 $[\operatorname{in}(v), \operatorname{out}(v)]$ 的节点无法被访问到。

那么很容易看出，「删点」这一操作会将**可访问的点**的 DFS 序划分成个数为 $\mathcal{O}(k)$ 级别的连续段，而 $\sum k \le 2 \times 10^5$，因此我们只需要一个能够快速求出每个连续段内的答案的方法即可。

对于一个节点 $u$，我们设 $f_i = \operatorname{dis}(p_i, u)$，那么一次询问的答案就是在 $x$ 可访问的节点对应的 DFS 序中 $f$ 的最大值。对于根节点 $1$，很显然有 $f_i = d_{p_i}$。对于节点 $u$ 与它的一个儿子节点 $v$，不难发现，对于 $v$ 子树外的点，也即是 DFS 序位于 $[1, \operatorname{in}(v) - 1]$ 与 $[\operatorname{out}(v) + 1, n]$ 的点，其到 $v$ 的距离为到 $u$ 的距离 + 1，而对于子树内的点，其到 $v$ 的距离则为到 $u$ 的距离 - 1。那么这实际上就是在 $f$ 上做区间加减的操作，而求答案则对应着区间求 $\max$ 的操作，因此可以用一棵线段树维护。

那么做法就很简单了。我们考虑将询问离线，然后在 DFS 的过程中计算每个询问的答案。在转移到当前节点儿子的时候就用上述的方法来维护当前的 $f$ 就可以了。

最后的问题就是如何得到某个询问对应的可访问的连续段。这个是经典的了，我们考虑把不合法的连续段求出来，然后按照左端点为第一关键字排序，再在扫描过程中维护当前可访问连续段的左端点即可。

[代码](https://codeforces.com/contest/1904/submission/236620352)，时间复杂度大概是 $\mathcal{O}((\sum k + n) \log n)$。


---

## 作者：EasonLiang (赞：1)

**[CF1904E](https://www.luogu.com.cn/problem/CF1904E)**

> 给定一棵 $n$ 个点的树，$q$ 次询问，每次删去 $k$ 个点 $\{a_k\}$，求 $x$ 所在连通图中距离 $x$ 最远的点，并输出该距离，询问间相互独立。$n, q, \sum k \le 2 \times 10^5$。

赛时想出了一个不同于官方题解的做法，赛后调了 1.5h 才调出来，于是决定写个题解记录一下。我的想法相当无脑：树剖 + 线段树 + 换根DP 维护树上每一个点到 $x$ 的距离，离线下来处理询问。

如果不考虑删点，让我们来看一下应该怎么维护每一个点到 $x$ 的距离。

首先无脑树剖（以1为根）。约定以下符号：

- $fa_u$ 表示 $u$ 的父亲；
- $son_u$ 表示 $u$ 在 $u$ 所在树链中的儿子；
- $top_u$ 表示 $u$ 所在树链的顶端结点；
- $subtree_u$ 表示 $u$ 所在子树内点的集合（包括 $u$）;
- $dfn_u$ 表示树剖以后 $u$ 的 dfn 序；
- $edp_u$ 表示树剖以后 $u$ 所在子树 dfn 序的最大值（即 $edp_u = \max_{v \in subtree_u} dfn_v$）
- $id_t$ 表示 dfn 序为 t 的结点编号（即 $dfn_{id_t} = t$）；
- $dis_{x,t}$ 表示 点 $x$ 到 $id_t$ 的距离。

我们先考虑 $x = 1$ 的情况（此时 $dis_{x,t}$ 即为 $id_t$ 的深度），有

$$dis_t + 1 = \sum_u [t \in subtree_u]$$

，故

$$dis_t = \sum_{u \neq 1} [t \in subtree_u]$$

对 $dis$ 建出线段树，对于树根以外的点 $u$，对 $[dfn_u, edp_u]$ 执行区间加操作，即可求出 $dis_{1,t}$。

对于 $x \neq 1$ 的情况，我们可以进行换根DP。注意到

$$dis_{u,t} = \begin{cases}
	dis_{fa_u,t} - 1, & id_t \in subtree_u \\
   dis_{fa_u,t} + 1, & id_t \notin subtree_u
\end{cases}$$

你会发现这是一个很好用线段树维护的东西，实现上我们只需要在由 $dis_{fa_u,t}$ 转移至 $dis_{u,t}$ 时，对 $[1, n]$ 区间 $+1$，对 $[dfn_u, edp_u]$ 区间 $-2$ 就可以了。（dfs 结束后，别忘了撤销操作！）

下面让我们来想一下，如果加上了删点操作，应该如何在线段树上维护 $dis$。

我们不妨换一种角度思考：在树上删点，实际上是“堵住”了 $x$ 到树上某些点的道路，我们只需要把被“堵住”的点全部找出来，在统计答案时不计入他们的 $dis$ 值就可以了。

那么，删去一个点 $v$ 会堵住点 $u$ 到哪些点的道路呢？我们可以分两种情况考虑：

1. $u$ 在 $v$ 的子树内。
   
   当 $u$ 在 $v$ 的子树内时，删去 $v$ 相当于是堵住了 $v$ 上方结点，以及不包含 $u$ 的 $v$ 的儿子的子树内所有结点。
   
   形式化地，设 $s$ 为满足
   $$ fa_s = v, u \in subtree_s$$
   的点，则所有不在 $s$ 的子树内的结点都需要被取消统计答案（即删去 $v$ 后，$u$ 只可能到达 $s$ 的子树内的结点）。
   
   实现上，相当于将 $[1, dfn_s) \cup (edp_s, n]$ 的区间取消统计答案。
   
   如何求 $s$？一种方法是从 $u$ 开始，倍增跳父亲得到；不过我更愿意介绍一种只用树剖的求法：
   
   > 初始时令 $s = u$，并不断将 $s$ 更新为 $fa_{top_s}$，同时进行如下判断：
   >
   >   - $fa_{top_s} = v$。若成立，则将 $s$ 最终更新为 $top_s$；
   >   - $top_s = top_v$ 且 $s$ 的深度大于 $v$。若成立，则将 $s$ 最终更新为 $son_v$。
   
   这个方法还有另一个好处：若更新后 $s$ 的深度小于 $v$，则可以判断出 $u$ 不在 $v$ 的子树内。

2. $u$ 不在 $v$ 的子树内。

   这种情况相比上一种就好考虑多了。此时删去点 $v$ 相当于把 $v$ 所在子树整个扔掉，而对 $v$ 的子树外的点没有影响。因此，我们只需要取消统计 $[dfn_v, edp_v]$ 的答案。

处理一个询问时，我们依次取消统计所有 删去点所“堵住”结点 的答案；当一组询问结束，我们就在线段树上恢复统计所有结点的答案，也就清除了所有的删点记录。

让我们来回忆一下线段树需要支持那哪些操作：区间加减、区间 取消/恢复 统计答案。具体实现可以参考我代码中的线段树部分。

讲到这里，这道题就差不多做完了。这个做法虽然看起来很复杂，但是代码的细节其实并不多。如果比较熟悉文中提到的三种算法的话，把代码写出来还是很容易的。最后附上我的 **[AC 代码](https://codeforces.com/contest/1904/submission/236609325)** 供大家参考。

---

## 作者：Natori (赞：1)

>[CF1904E Tree Queries](https://www.luogu.com.cn/problem/CF1904E)

这个删点好像有点烦捏，先考虑没有它的情况。

容易想到比较暴力的方法：遍历每一个询问，将这个询问的 $x$ 作为“当前点”（类似树根，但建议不要完全替换成树根）。确定“当前点”后，DFS 整棵树求出所有点的深度，取 $\max$ 即为当前询问答案。

进一步地，考虑换根。先离线询问，挂在对应的 $x$ 上。将整棵树拍到 DFS 序上，用线段树维护当前点 $u$ 到其他点的距离。

考虑从 $u$ 走到它的一个子结点 $v$ 时：

- 对于 $v$ 子树内的点（包括 $v$），它们到当前点的距离都 $-1$；

- 对于 $v$ 子树外的点，它们到当前点的距离都 $+1$。

实现时为了方便，可以先将所有节点的距离都 $+1$，然后子节点子树的距离 $-2$，注意回溯时还要加回来。

这样做时间复杂度是 $\mathcal{O}(n \log n)$ 的。

考虑删点怎么处理。枚举要删的点 $x$，当前点 $u$ 可能在它的子树内，也可能在子树外。$u$ 在 $x$ 子树之外是好办的，此时答案路径不可能经过 $x$，所以直接将 $x$ 的子树删掉即可。对于 $u$ 在 $x$ 子树内的情况，显然此时答案路径不可能经过 $x$，所以只需要找一个 $x$ 的子节点 $y$，使得 $u$ 在 $y$ 的子树中，然后将 $y$ 子树之外的点都删掉即可。可以倍增简单实现。

实现删除操作时，给线段树每个节点打一个标记表示这个节点的信息是否上传即可。总复杂度仍是 $\mathcal{O}(n \log n)$ 的。

说一下为什么不建议将“当前点”直接理解成“树根”。如果把当前点 $u$ 理解成“树根”，就比较容易陷入一个误区：所有要删除的点都在 $u$ 的子树内，直接删除就行了。这样理论上没问题，但是实际不可做。删除操作依赖的是 DFS 序，树根变化之后，不好快速求出 DFS 序的变化。而已求出的 DFS 序针对以 $1$ 为树根的情况，所以才要放到原树上分类讨论。

感觉讲得挺清楚了，代码就不放了罢（

---

## 作者：nullqtr_pwp (赞：0)

最长简单路径，不如直接说成连通块上两个点的距离，其中一个点是 $x$。

考虑用 dfs 序刻画 $x$ 所在的连通块。这其实并不是连续的，对于每个 $a_i$，找出来它与 $x$ 是否存在祖先关系，可以求出来 $1/2$ 段 dfs 序区间，使得 $x$ **不能**到达。

这些区间取并之后（组成一堆连续段），就是 $x$ 最终无法到达的 dfs 序区间。那么我们想要的，$x$ 所在的连通块就可以通过剩下这些没有被染色的 dfs 序区间来刻画出来。显然，由于每个 $a_i$ 贡献是 $O(1)$ 个区间，我们可以暴力求出来所有的 $[l_i,r_i]$（dfs 序区间）使得 $x$ 可以到达。也就是，删除掉的区间形成的连续段，中间那些空隙就是可达的。

考虑一个经典结论：连通块 $G$ 中离 $u$ 最远的节点，记为集合 $S$，那么 $G$ 任意一条直径的某个端点必然 $\in S$。

如果求出来了剩下这堆的区间构成的连通块的端点，那么我们显然就可以快速求出来答案。

考虑到，两个连通子图合并，构成新的直径时，显然只会从各自子图中的 $2$ 个端点，总共 $4$ 个端点中诞生这条直径的端点。这启发我们可以快速合并两个已知直径信息的子图。

回想到我们使用若干连续的 dfs 序区间来刻画，而且上面说的东西具有结合律，考虑线段树维护。具体地，线段树维护 $[l,r]$ 表示 dfs 序在 $[l,r]$ 中的所有的节点构成的子图，直径的两个端点以及长度。

查询的时候，求出来所有存活 dfs 序区间后直接暴力合并出来这个子图的直径即可。

每次合并子图需要求 $\text{dis}(u,v)$，用倍增求 $\text{lca}$ 会很慢。此处使用 $O(n\log n)-O(1)$ 求 $\text{lca}$，结合线段树的复杂度是 $O(n\log n)$。

[提交记录。](https://codeforces.com/contest/1904/submission/252093195)

---

## 作者：spider_oyster (赞：0)

要放假了，但不想改错，怎么办呢？当然是水博客。

---

先考虑不删点的一个 $O(n\log n)$ 做法。

假设当前在点 $u$，我们维护 $dis_i$ 表示点 $u$ 到点 $i$ 的距离。那么当前的答案就是全局取 max。

考虑往 $u$ 的儿子 $v$ 走，那么 $v$ 子树内的点到 $v$ 的距离 -2，$v$ 子树外的点到 $v$ 的距离 +1。

线段树维护区间加，全局 max。

现在考虑删除一些点，假设当前点为 $u$，要删的点为 $x$。

设 $T_x$ 表示 $x$ 的子树。

- 若 $u\in T_x$，那么我们找到一个点 $y\in son_x$，且 $u\in T_y$，保留 $T_y$。
- 否则删除 $T_x$。

对于删除操作，我们只需要在线段树上打个标记，对于标记的点不要 pushup 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int n,m,dn,ans[N],l[N],r[N],id[N],dep[N],f[N][20];
struct node{vector<int> p;int id;};
vector<int> G[N];
vector<node> q[N];

void dfs(int u,int fa)
{
    dep[u]=dep[fa]+1,f[u][0]=fa,l[u]=++dn,id[dn]=u;
    for(int i=1;i<=18;i++) f[u][i]=f[f[u][i-1]][i-1];
    for(int v:G[u]) if(v!=fa) dfs(v,u);
    r[u]=dn;
}

#define lc (k<<1)
#define rc (k<<1|1)
#define mid (l+r>>1)
int mx[N*4],add[N*4],lk[N*4];
void pushdown(int k)
{
    if(!add[k]) return;
    add[lc]+=add[k],add[rc]+=add[k];
    mx[lc]+=add[k],mx[rc]+=add[k];
    add[k]=0;
}
void pushup(int k)
{
    mx[k]=0;
    if(!lk[lc]) mx[k]=mx[lc];
    if(!lk[rc]) mx[k]=max(mx[k],mx[rc]);
}
void build(int k=1,int l=1,int r=n)
{
    if(l==r) {mx[k]=dep[id[l]];return;}
    build(lc,l,mid),build(rc,mid+1,r);
    mx[k]=max(mx[lc],mx[rc]);
}
void upd(int x,int y,int v,int k=1,int l=1,int r=n)
{
    if(l>=x&&r<=y) {mx[k]+=v,add[k]+=v;return;}
    pushdown(k);
    if(x<=mid) upd(x,y,v,lc,l,mid);
    if(mid<y) upd(x,y,v,rc,mid+1,r);
    pushup(k);
}
void upd_lk(int x,int y,int v,int k=1,int l=1,int r=n)
{
    if(y<x) return;
    if(l>=x&&r<=y) {lk[k]=v;return;}
    pushdown(k);
    if(x<=mid) upd_lk(x,y,v,lc,l,mid);
    if(mid<y) upd_lk(x,y,v,rc,mid+1,r);
    pushup(k);
}

int find(int x,int rt) {for(int i=18;~i;i--) if(dep[f[x][i]]>dep[rt]) x=f[x][i];return x;}

void dp(int u,int fa)
{
    for(auto [v,id]:q[u])
    {
        for(int x:v)
            if(l[x]<=l[u]&&r[u]<=r[x])
            {
                int p=find(u,x);
                upd_lk(1,l[p]-1,1),upd_lk(r[p]+1,n,1);
            }
            else upd_lk(l[x],r[x],1);
        ans[id]=mx[1];
        for(int x:v)
            if(l[x]<=l[u]&&r[u]<=r[x])
            {
                int p=find(u,x);
                upd_lk(1,l[p]-1,0),upd_lk(r[p]+1,n,0);
            }
            else upd_lk(l[x],r[x],0);
    }
    upd(1,n,1);
    for(int v:G[u])
    {
        if(v==fa) continue;
        upd(l[v],r[v],-2);
        dp(v,u);
        upd(l[v],r[v],2);
    }
    upd(1,n,-1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<n;i++)
    {
        int u,v;cin>>u>>v;
        G[u].push_back(v),G[v].push_back(u);
    }
    for(int i=1;i<=m;i++)
    {
        int x,k;cin>>x>>k;
        vector<int> v(k);for(int &i:v) cin>>i;
        q[x].push_back({v,i});
    }
    dfs(1,0);
    build();
    dp(1,0);
    for(int i=1;i<=m;i++) cout<<ans[i]-1<<'\n';
}
```

---

## 作者：smallpeter (赞：0)

一个比较自然的做法是离线后换根处理询问。可以用 `dfs` 序的方法在换根过程中快速维护当前点到所有节点的距离：假如从 $u$ 到 $v$ （$v$ 为原树中 $u$ 的儿子节点），则相比于 $u$，到 $v$ 子树内的点的距离会 `-1`，到其他点的距离会 `+1`。接下来我们考虑对于一个新的根 $x$，若干个点 $a_i$ 被挖掉会造成什么影响。

![](https://cdn.luogu.com.cn/upload/image_hosting/duhlv2e7.png)

对于这颗树而言，给它标上 `dfs` 序后长这样（个人习惯从左往右，红色为 `dfs` 序）

![](https://cdn.luogu.com.cn/upload/image_hosting/hk7abicy.png)

对于 $x=7$，$a_i=8,2$，考虑 $a$ 对答案的影响。

首先考虑 $a_i=8$ 的情况。对于这种情况，显然只要把以 $a_i$ 为根的子树的贡献删除。在 `dfs` 序上这个东西是一个区间，即 $[dfn_{a_i},dfn_{a_i}+size_{a_i})$（$size_u$ 表示以 $u$ 为根的子树大小）。

再考虑特殊一点的情况。当 $a_i=2$ 时，我们发现它的影响变成了只保留 $a_i$ 的所有子树中包含 $x$ 的那一颗（在上面那个例子中就是只保留以节点 6 为根的子树），我们设这颗包含 $x$ 的子树的根为 $y$，则就是保留 `dfs` 序在 $[dfn_y,dfn_y+size_y)$ 中的点。为了与上面形式统一方便处理，我们改写成删除 `dfs` 序在 $[1,dfn_y)\cup[dfn_y+size_y,n]$ 中的点。

不难发现这种特殊的情况是 $a_i$ 为 $x$ 的祖先。

问题在于怎么求 $y$。我们可以考虑倍增。先预处理出每个节点的深度，设为 $dep_u$，那么就可以知道 $y$ 是 $x$ 的 $dep_x-dep_{a_i}-1$ 级祖先。

现在我们得到了若干条线段，我们对它们按左端点排序，就可以处理出所有没被删除的点组成的线段，这样的线段数量显然是 $O(\sum k)$ 的。

复杂度 $O(\sum k\times \log n+n\times \log n)$

因为作者脑抽，所以 `Segment Tree` 维护了一堆 `useless` 的操作/kk/kk/kk。

[代码](https://codeforces.com/contest/1904/submission/237134279)

---

## 作者：RockyYue (赞：0)

> Trick:
>
> 1. 树中与任意一个点距离最远的点均为其直径两端点之一。
> 2. 合并两棵树（结构合并而非点值），新树直径两端点在原先两棵树直径的四个端点中产生。
> 3. 若要求删去区间 $[l_1,r_1],[l_2,r_2],\dots [l_k,r_k]$ 后余下位置产生的答案，且问题支持离线，在考虑删除时维护答案的同时不妨考虑直接对“余下位置”所在的若干个区间进行合并得出答案。

将“不经过点 $u$”的限制看作在图中删去点 $u$，询问答案为删去所有要求不经过的点后 $x$ 所在的连通块中所有点与 $x$ 距离的最大值。这里利用 Trick1，想到要在删点的同时维护 $x$ 所在子树的直径的两端点。

最暴力的方法是对于每次询问，以 $x$ 为根处理，删掉一个点相当于删掉以其为根的子树，求最终剩下的点中深度最大者。换根的想法固然是行不通的，但这启示我们考虑每个删掉的点 $u$，对于删掉 $u$ 导致的从和 $x$ 同一颗子树中分离出去的点，观察这些点 ```dfn``` 的性质。以下记 $[l_u,r_u]$ 为 $u$ 子树（包含 $u$）的 ```dfn``` 范围。

- 若 $u$ 为 $x$ 的祖先，设 $u$ 的儿子中为 $x$ 祖先（或者 $x$）的点为 $v$，则除子树 $v$ 外的所有点不能走，即 ```dfn``` 在 $[1,l_v)\cap (r_v,n]$ 范围内的点被禁止；
- 若 $u$ 非 $x$ 的祖先，则整个子树 $u$ 内的点被禁止，即 ```dfn``` 在 $[l_u,r_u]$ 内的点被禁止。

删除一段 ```dfn``` 的同时维护子树直径是困难的，直径这种最值问题是难以撤销的，考虑以加入点的形式维护答案，利用 Trick3，对于删去这些 ```dfn``` 区间后剩下的若干个区间进行合并，每个区间都是一颗子树，合并过程中维护子树直径两端点的过程可以参考 Trick2，具体维护用到线段树。我们发现这些删除的 ```dfn``` 区间要么不交要么包含，不会出现相交的情况，那么删除后剩下的区间就是好找的，将删除区间按照 $(l,r)$ 第一维小第二维大排序，从前往后扫即可，将得到的剩余区间依次合并，得到最终 $x$ 所在子树直径两端点，判断哪个更优即可得到答案，复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimized(2)
using namespace std;
const int N=2e5+5,H=21;
struct sec{
	int l,r;
	bool operator<(const sec&rhs)const{
		if(l!=rhs.l)return l<rhs.l;
		return r>rhs.r;
	}
};
struct edge{
	int v,nxt;
}E[N<<1];
int head[N],cnt;
inline void add(int u,int v){
	E[++cnt]={v,head[u]},head[u]=cnt;
}
int dfnl[N],dfnr[N],times,fa[N][H],dep[N],dfnis[N];
void dfs0(int u,int f){
	dfnl[u]=++times;
	dfnis[times]=u;
	dep[u]=dep[f]+1;
	for(int i=1;i<H;++i)fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=head[u];i;i=E[i].nxt){
		int v=E[i].v;
		if(v!=f){
			fa[v][0]=u;
			dfs0(v,u);
		}
	}
	dfnr[u]=times;
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=H-1;i>=0;--i){
		if(dep[fa[u][i]]>=dep[v])u=fa[u][i];
	}
	if(u==v)return u;
	for(int i=H-1;i>=0;--i){
		if(fa[u][i]!=fa[v][i])u=fa[u][i],v=fa[v][i];
	}
	return fa[u][0];
}
int dis(int u,int v){
	return dep[u]+dep[v]-(dep[lca(u,v)]<<1);
}
bool is_anc(int u,int v){
	if(dep[v]<dep[u])return 0;
	int v1=v;
	for(int i=H-1;i>=0;--i){
		if(dep[fa[v][i]]>=dep[u])v=fa[v][i];
	}
	return u==v;
}
struct diam{
	int u,v,d;
};
diam t[N<<2];
inline void g(diam &x,int u,int v){
	int d=dis(u,v);
	if(d>x.d)x={u,v,d};
}
inline diam pushup(diam x,diam y){
	int u=x.u,v=x.v,p=y.u,q=y.v;
	diam res=x;
	if(y.d>x.d)res=y;
	g(res,u,p),g(res,u,q),g(res,v,p),g(res,v,q);
	return res;
}
void build(int id,int l,int r){
	if(l==r)return void(t[id]={dfnis[l],dfnis[l],0});
	int mid=(l+r)>>1;
	build(id<<1,l,mid),build(id<<1|1,mid+1,r);
	t[id]=pushup(t[id<<1],t[id<<1|1]);
}
diam qry(int id,int l,int r,int x,int y){
	if(x<=l&&r<=y)return t[id];
	int mid=(l+r)>>1;
	diam res={dfnis[x],dfnis[x],0};
	if(x<=mid)res=pushup(res,qry(id<<1,l,mid,x,y));
	if(y>mid)res=pushup(res,qry(id<<1|1,mid+1,r,x,y));
	return res;
}
int T(int u,int v){
	for(int i=H-1;i>=0;--i){
		if(dep[fa[fa[v][i]][0]]>=dep[u]){
			v=fa[v][i];
			if(dep[v]==dep[u]+1)return v;
		}
	}
	return v;
}
signed main() {
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int n,q;cin>>n>>q;
	for(int i=1;i<n;++i){
		int u,v;cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs0(1,0);
	build(1,1,n);
	while(q--){
		int x,k;cin>>x>>k;
		vector<sec> e;
		while(k--){
			int u,tt;cin>>u;
			if(is_anc(u,x))tt=T(u,x),e.push_back({1,dfnl[tt]-1}),e.push_back({dfnr[tt]+1,n});
			else e.push_back({dfnl[u],dfnr[u]});
		}
		sort(e.begin(),e.end());
		int maxr=0,lst=0;
		diam res={x,x,0};
		for(sec s:e){
			int l=s.l,r=s.r;
			if(maxr>=r||l>r)continue;
			maxr=max(maxr,r);
			if(lst+1>l-1){
				lst=r;
				continue;
			}
			res=pushup(res,qry(1,1,n,lst+1,l-1));
			lst=r;
		}
		if(lst+1<=n)res=pushup(res,qry(1,1,n,lst+1,n));
		cout<<max(dis(x,res.u),dis(x,res.v))<<'\n';
	}
	return 0;
}
```



---

