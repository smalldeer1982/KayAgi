# [ABC394G] Dense Buildings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc394/tasks/abc394_g

在东西南北方向被划分为 $H \times W$ 个区域的街区中，每个区域恰好建有一座大楼。  
具体来说，北起第 $i$ 行（$1 \leq i \leq H$）西起第 $j$ 列（$1 \leq j \leq W$）的区域（以下简称区域 $(i,j)$）建有一座 $F_{i,j}$ 层的大楼。

高桥君有两种移动方式。当他在区域 $(i,j)$ 大楼的 $X$ 层（$1 \leq X \leq F_{i,j}$）时，可以进行以下移动：

- 通过**楼梯**在同一大楼内移动到相邻的上一层或下一层。但无法从 $1$ 层移动到更下层，也无法从 $F_{i,j}$ 层移动到更上层。
- 通过 **（高空）通道** 移动到东西南北相邻区域中某座高度至少为 $X$ 层的大楼的 $X$ 层。

此处，区域 $(i,j)$ 与区域 $(i',j')$ 东西南北相邻的定义为 $\lvert i - i' \rvert + \lvert j - j' \rvert = 1$。

请回答 $Q$ 个查询。第 $i$ 个（$1 \leq i \leq Q$）查询内容如下：

> 请求出高桥君从区域 $(A_i, B_i)$ 大楼的 $Y_i$ 层移动到区域 $(C_i, D_i)$ 大楼的 $Z_i$ 层时，**楼梯**使用次数的最小可能值。  
> 注意：每次上下移动一层均计为一次楼梯使用（例如从某大楼 $1$ 层移动到 $6$ 层需使用 $5$ 次楼梯）。  
> 同时，通道使用次数无需最小化。

## 说明/提示

### 约束条件

- $1 \leq H \leq 500$
- $1 \leq W \leq 500$
- $1 \leq F_{i,j} \leq 10^6$
- $1 \leq Q \leq 2 \times 10^5$
- $1 \leq A_i, C_i \leq H$
- $1 \leq B_i, D_i \leq W$
- $1 \leq Y_i \leq F_{A_i,B_i}$
- $1 \leq Z_i \leq F_{C_i,D_i}$
- $(A_i, B_i, Y_i) \neq (C_i, D_i, Z_i)$
- 所有输入均为整数

### 样例解释 1

对于第 $1$ 个查询，以下移动方式共使用 $10$ 次楼梯：
- 通过通道从区域 $(1,1)$ 大楼 $10$ 层移动到区域 $(1,2)$ 大楼 $10$ 层
- 使用 $4$ 次楼梯从 $10$ 层下到 $6$ 层
- 通过通道移动到区域 $(1,3)$ 大楼 $6$ 层
- 使用 $3$ 次楼梯下到 $3$ 层
- 通过通道移动到区域 $(2,3)$ 大楼 $3$ 层
- 通过通道移动到区域 $(3,3)$ 大楼 $3$ 层
- 使用 $3$ 次楼梯上到 $6$ 层
- 通过通道移动到区域 $(3,2)$ 大楼 $6$ 层
- 通过通道移动到区域 $(3,1)$ 大楼 $6$ 层  
由于无法用 $9$ 次或更少楼梯完成移动，故输出 $10$。

对于第 $2$ 个查询，通过通道移动到区域 $(1,2)$ 大楼后，使用 $2$ 次楼梯从 $6$ 层下到 $4$ 层即可完成移动，故输出 $2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 3
12 10 6
1 1 3
8 6 7
2
1 1 10 3 1 6
1 1 6 1 2 4```

### 输出

```
10
2```

# 题解

## 作者：lao_wang (赞：13)

## 正文

读题可知主要问题是：需要找到一个起点是 $(a,b)$ 终点是 $(c,d)$ 路径使得所经过的点中 $F_{i,j}$ 的最小值最小。

一眼，整体二分模板题（赛事没切，被 continue 坑了）。

二分最小值，将边权小于 $mid$ 的两点加入并查集，使用并查集查看 $(a,b)$ 和 $(c,d)$ 是否在一个集合，不在就递归左区间，在就递归右区间。

发现并查集数组并不好记录在答案当中，所以还原并查集数组需要：

1. $solve(l,mid,L,L+tot1-1)$。
2. 还原当前所修改的并查集（需要使用栈来维持每次删除一定是之前并查集的最后一次加边）。
3. $solve(mid+1,r,L+tot1,R)$。

当然你也可以使用非递归。

## 代码


```cpp
#include<bits/stdc++.h>
#define N 1123456
#define int long long
#define mk(a,b) make_pair(a,b)
using namespace std ;
int n , m , f[N] , ans[N] , dsu[N] , cnt=0 , q , sz[N] ;
pair<int,int> ex[N] ;
struct node {
	int opt , u , v , mx , i ;
} a[N<<2],q1[N<<2],q2[N<<2];
struct huanyuan{
	int u , v , szu , szv ;
};
int find(int x) {
	return dsu[x]==x?x:find(dsu[x]) ;
}
void solve(int l,int r,int L,int R) {
	if(L>R) return ;
	if(l==r) return ;
	int mid=(l+r)>>1 , tot1=0 , tot2=0 ;
	stack<huanyuan> q ;
	for(int i=L; i<=R; i++) {
		if(a[i].opt==1) {
			if(a[i].mx>=mid) {
				int u=find(a[i].v) , v=find(a[i].u) ;
				q2[++tot2] = a[i] ;
				if(u==v) continue ; // 慎用 continue
				if(sz[u]<sz[v]) swap(u,v) ;
				q.push(huanyuan{v,dsu[v],u,sz[u]}) ;
				dsu[v] = u ;
				sz[u] += sz[v] ;
			} else q1[++tot1] = a[i] ;
		} else {
			if(find(a[i].u)!=find(a[i].v)) q1[++tot1] = a[i] ;
			else ans[a[i].i] = mid , q2[++tot2] = a[i] ;
		}
	}
	for(int i=1; i<=tot1; i++)
		a[i+L-1] = q1[i] ;
	for(int i=1; i<=tot2; i++) a[tot1+L+i-1] = q2[i] ;
	solve(l,mid,L,L+tot1-1) ;
	while(!q.empty()){
		huanyuan u=q.top() ; 
		dsu[u.u] = u.v ;
		sz[u.szu] = u.szv ;
		q.pop() ;
	}
	solve(mid+1,r,L+tot1,R) ;
}
signed main() {
	cin >> n >> m ;
	for(int i=1; i<=n*m; i++) dsu[i] = i , sz[i]=1 ;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) scanf("%lld",&f[(i-1)*m+j]) ;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			int u=(i-1)*m+j ;
			if(i<n) a[++cnt] = node {1,u,u+m,min(f[u],f[u+m]),0} ;
			if(j<m) a[++cnt] = node {1,u,u+1,min(f[u],f[u+1]),0} ;
		}
	}
	cin >> q ;
	for(int i=1; i<=q; i++) {
		int A , b , y , c , d , z ;
		scanf("%lld%lld%lld%lld%lld%lld",&A,&b,&y,&c,&d,&z) ;
		ex[i] = mk(y,z) ;
		a[++cnt] = node {2,(A-1)*m+b,(c-1)*m+d,0,i} ;
	}
	solve(0,1000001,1,cnt) ;
	for(int i=1; i<=q; i++) ans[i] = min(ans[i],min(ex[i].first,ex[i].second)) ;
	for(int i=1;i<=q;i++) printf("%lld\n",abs(ans[i]-ex[i].first)+abs(ans[i]-ex[i].second)) ;
	return 0 ;
}


```

---

## 作者：Crazyouth (赞：12)

## 分析

我们只需要找纵向的最短距离而不需要横向的，所以考虑相邻的点连边，边权为两个点高度的最小值。此时相当于寻找 $(a,b)$ 到 $(c,d)$ 的最大瓶颈路，直接建立 kruskal 重构树并找两个点的最近公共祖先即可。注意特判 $(a,b)=(c,d)$（因为这个导致赛场没过）。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define hs(i,j) (i-1)*w+j
struct edge
{
	int u,v,w;
}e[500010];
const int N=250010;
int A[510][510],fa[N<<1],ch[N<<1][2],f[N<<1][21],W[N<<1],dep[N<<1];
int find(int x)
{
	if(x==fa[x]) return x;
	fa[x]=find(fa[x]);
	return fa[x];
}
int main()
{
	int h,w,ecnt=0;
	cin>>h>>w;
	for(int i=1;i<=h;i++)
	for(int j=1;j<=w;j++)
	cin>>A[i][j];
	for(int i=1;i<=h;i++)
	for(int j=1;j<=w;j++)
	{
		if(i<h)
		e[++ecnt]={hs(i,j),hs(i+1,j),min(A[i][j],A[i+1][j])};
		if(j<w)
		e[++ecnt]={hs(i,j),hs(i,j+1),min(A[i][j],A[i][j+1])};
	}
	sort(e+1,e+ecnt+1,[](edge x,edge y){return x.w>y.w;});
	for(int i=1;i<=h*w*2;i++) fa[i]=i;
	int ncnt=h*w;
	for(int i=1;i<=ecnt;i++)
	{
		int u=e[i].u,v=e[i].v,w=e[i].w;
		int fu=find(u),fv=find(v);
		if(fu==fv) continue;
		ncnt++;
		ch[ncnt][0]=fu;ch[ncnt][1]=fv;
		f[fu][0]=ncnt;f[fv][0]=ncnt;
		fa[fu]=fa[fv]=ncnt;
		W[ncnt]=w;
	}
	for(int i=0;i<=20;i++) f[ncnt][i]=ncnt;
	dep[ncnt]=1;
	for(int i=ncnt-1;i;i--)
	{
		for(int j=1;j<=20;j++) f[i][j]=f[f[i][j-1]][j-1];
		dep[i]=dep[f[i][0]]+1;
	}
	int q;
	cin>>q;
	while(q--)
	{
		int a,b,c,d,y,z;
		cin>>a>>b>>y>>c>>d>>z;
		int u=hs(a,b),v=hs(c,d);
		if(dep[u]<dep[v]) swap(u,v),swap(y,z);
		for(int i=20;~i;i--) if(dep[f[u][i]]>=dep[v]) u=f[u][i];
		if(u==v) goto E;
		for(int i=20;~i;i--) if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
		u=f[u][0];
		E:;
		if(hs(a,b)==hs(c,d)||W[u]>y||W[u]>z) cout<<abs(y-z)<<'\n';
		else cout<<y-W[u]+z-W[u]<<'\n';
	}
}

---

## 作者：Twig_K (赞：5)

我们发现，反复上下楼一定是不优的。所以我们从 $(A_i,B_i,Y_i)$ 走到 $(C_i,D_i,Z_i)$ 的策略是固定的：先下楼到 $(A_i,B_i,X_i)$，再在同一水平面内从 $(A_i,B_i)$ 移动到 $(C_i,D_i)$，最后再上楼。

最终的花费是 $|Y_i-X_i|+|Z_i-X_i|$。由于 $X_i \leq \min(Y_i,Z_i)$，所以我们只需要最大化 $X_i$。

将网格上每相邻两点（四连通）$U,V$ 连边，边权为 $\min (F_U,F_V)$，其中 $F_{i,j}$ 为楼房高度。

我们只需要找一条在新图上从 $(A,B)$ 到 $(C,D)$ 的路径，最大化沿途高度的最小值（还要和 $Y,Z$ 取 $\min$）。

于是用这些边建一棵最大生成树，每次走的就是树边。这一部分树剖求路径最小边权就可以了，不要忘了和起点和终点的高度取 $\min$。

代码见 [提交记录](https://atcoder.jp/contests/abc394/submissions/63057025)。

---

## 作者：Mr_Az (赞：4)

# [AT_abc394_g [ABC394G] Dense Buildings](https://www.luogu.com.cn/problem/AT_abc394_g)

### Algorithm:

最大生成树 + 倍增LCA / 树剖。

### Solution:

题目中横跨两个大楼之间的次数并不重要，原题目的意思转为每次可以从当前楼找一条通向终点的路径使得路径上的楼房高度最小值最大。

看到最小值最大会先想到二分答案，考虑如何 check，也就是我现在只能走到大于当前二分的值 $x$ 的楼，求是否有一条路径可以从起点走向终点。容易发现这是最大生成树，边权即为两端点权的较小者。维护路径上的最小值可以用倍增 LCA 或者树链剖分，笔者选择了后者。

### Code:

```cpp
const int M=508,N=M*M,dx[]={1,-1,0,0},dy[]={0,0,1,-1};
int T=1;
int n,m,q,ddfn;
int a[N],fa[N],dfn[N],num[N],dep[N],siz[N],top[N],son[N];
vector<int> e[N];
struct edge{int u,v,w;};
inline int id(int x,int y){return (x-1)*m+y;}
inline bool valid(int x,int y){return x>=1&&x<=n&&y>=1&&y<=m;}
inline int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
vector<edge> ed;
struct tree{
    int mn;
    #define mn(p) t[p].mn
}t[N*4];
#define mid (l+r>>1)
inline void update(int p){mn(p)=min(mn(ls),mn(rs));}
void build(int p,int l,int r){
    if(l==r){mn(p)=a[num[l]];return ;}
    build(ls,l,mid);build(rs,mid+1,r);
    update(p);
    return ;
}
int ask(int p,int l,int r,int L,int R){
    if(L<=l&&r<=R) return mn(p);
    int res=INF;
    if(L<=mid) res=min(res,ask(ls,l,mid,L,R));
    if(R>mid)  res=min(res,ask(rs,mid+1,r,L,R));
    return res;	
}
#undef mn
#undef mid
void dfs(int u,int faa){
    dep[u]=dep[faa]+1;siz[u]=1;fa[u]=faa;
    int mx=0;
    for(auto v:e[u]){
        if(v==faa) continue;
        dfs(v,u);
        if(mx<siz[v]) mx=siz[v],son[u]=v;
        siz[u]+=siz[v];
    }
}
void dfs1(int u,int fa,int t){
    top[u]=t;dfn[u]=++ddfn;num[dfn[u]]=u;
    if(son[u]) dfs1(son[u],u,t);
    for(auto v:e[u]){
        if(v!=fa&&v!=son[u]) dfs1(v,u,v);
    }
}
int ask(int x,int y){
    int res=INF;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        res=min(res,ask(1,1,n*m,dfn[top[x]],dfn[x]));
        debug(x,y,ask(1,1,n*m,dfn[top[x]],dfn[x]));
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    res=min(res,ask(1,1,n*m,dfn[x],dfn[y]));
    debug(x,y,ask(1,1,n*m,dfn[x],dfn[y]));
    return res;
}
inline void solve(){
    read(n,m);
    for(rint i=1;i<=n*m;i++) fa[i]=i;
    for(rint i=1;i<=n;i++){
        for(rint j=1;j<=m;j++){
            read(a[id(i,j)]);
        }
    }
    for(rint i=1;i<=n;i++){
        for(rint j=1;j<=m;j++){
            for(rint k=0;k<4;k++){
                int nx=i+dx[k],ny=j+dy[k];
                if(valid(nx,ny)){
                    ed.pb({id(i,j),id(nx,ny),min(a[id(i,j)],a[id(nx,ny)])});
                }
            }
        }
    }
    sort(alls(ed),[](edge A,edge B){return A.w>B.w;});
    for(auto [u,v,w]:ed){
        int fu=getfa(u),fv=getfa(v);
        if(fu!=fv){
            fa[fu]=fv;
            e[u].pb(v);e[v].pb(u);
            debug(u,v);
        }
    }
    mem(fa,0);
    dfs(1,0);dfs1(1,0,1);
    build(1,1,n*m);
    read(q);
    while(q--){
        int x,y,xx,yy,a1,a2,ans=0;
        read(x,y,a1,xx,yy,a2);
        int o=ask(id(x,y),id(xx,yy));
        ans=a1-min({a1,a2,o});
        ans+=a2-min({a1,a2,o});
        printf("%lld\n",ans);
    }
}
```

---

## 作者：Conan15 (赞：4)

## 一些闲话

~~可恶的数学害我忘记打这场 ABC。数学滚出文化课！~~\
赛后看了一下，3 min 想完大体思路，但是最后一步卡了很久，还是题做太少了。

## 题解

首先一步很显然的转化是：假设你现在在 $(x1,y1,h1)$，要去 $(x2,y2,h2)$，如果你在途中需要下楼，可以在 $(x1,y1)$ 下楼之后再走过去，到达 $(x2,y2)$ 再上下移动到目标。\
另一个很显然的贪心是：选择 $(x1,y1) \to (x2,y2)$ 的路径，使得**途径的最小楼层高度最大**。\
因为在两栋楼之间移动不需要花费时间，但上下楼需要，所以找到这样的一条路径可以尽量减少下楼次数。

有了上述转化，我们就只需要求出网格上从 $(x1,y1)$ 走到 $(x2,y2)$ 路径最小点权的最大值。\
这可能很像二分，但它长得更像一个**重构树**，不过是点权形式的。\
于是我们考虑类似 Kruskal 重构树的过程，把点权从大到小排序，每次看它四联通方格是否有比它大的，若有则从比它大的点连向它本身。\
另外我们需要维护一个并查集表示两个点是否在同一个连通块内，显然这样建出来是一棵树。

但这和**点权多叉重构树**有本质区别，因为这里要保证树上相邻的两个点在方格中也是相邻的。\
容易发现这样贪心加点，能满足我们需要的性质，因为按点权从大到小连接，显然是“尽量早”地合并两个连通块。

于是可以树上倍增求出两点之间点权最小值。\
然而马上要省选了，所以我为了练练板子写了树剖。
省选加油！

```cpp
#include <bits/stdc++.h>
using namespace std;
const int K = 515, N = 5e5 + 15, M = N << 2, INF = 0x3f3f3f3f;

int n, m, q, f[K][K], fid[N];
int id(int x, int y) { return (x - 1) * m + y; }

int h[N], e[M], ne[M], idx = 0;
void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }
void addedge(int a, int b) { puts("Wishing everyone RP++!"); add(a, b), add(b, a); }

struct node {
    int x, y, val;
} a[N];
bool cmp(node a, node b) { return a.val > b.val; }
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int rt;
int dep[N], fa[N], son[N], sz[N];
void dfs1(int u, int father) {
    fa[u] = father, sz[u] = 1, dep[u] = dep[father] + 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == father) continue;
        dfs1(v, u);
        if (!son[u] || (sz[son[u]] < sz[v])) son[u] = v;
        sz[u] += sz[v];
    }
}
int top[N], dfn[N], v[N], tot = 0;
void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++tot, v[tot] = fid[u];
    if (son[u]) dfs2(son[u], t);
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    return u;
}

struct Tree {
    int l, r;
    int Min;
} tr[N << 2];
void pushup(int u) { tr[u].Min = min(tr[u << 1].Min, tr[u << 1 | 1].Min); }
void build(int u, int l, int r) {
    tr[u].l = l, tr[u].r = r;
    if (l == r) return tr[u].Min = v[l], void();
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}
int query(int u, int l, int r) {
    if (l > r) return INF;
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].Min;
    int mid = tr[u].l + tr[u].r >> 1, res = INF;
    if (l <= mid) res = min(res, query(u << 1, l, r) );
    if (r > mid) res = min(res, query(u << 1 | 1, l, r) );
    return res;
}

int query_path(int u, int v) {
    int res = INF;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res = min(res, query(1, dfn[top[u]], dfn[u]) );
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    res = min(res, query(1, dfn[u], dfn[v]) );
    return res;
}

bool vis[K][K];
int p[N];
int find(int x) { return (p[x] == x) ? x : p[x] = find(p[x]); }

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) scanf("%d", &f[i][j]), a[id(i, j)] = (node){i, j, f[i][j]}, fid[id(i, j)] = f[i][j];
    sort(a + 1, a + 1 + n * m, cmp);
    
    for (int i = 1; i <= n * m; i++) p[i] = i;
    for (int i = 1; i <= n * m; i++) {
        int x = a[i].x, y = a[i].y, u = id(x, y);
        vis[x][y] = 1;
        for (int k = 0; k < 4; k++) {
            int xx = x + dx[k], yy = y + dy[k], v = id(xx, yy);
            if (xx < 1 || xx > n || yy < 1 || yy > m || !vis[xx][yy]) continue;
            if (find(u) == find(v)) continue;   //已经联通
            p[find(u)] = find(v);
            addedge(u, v);
        }
    }
    rt = id( a[n * m].x, a[n * m].y );
    
    dfs1(rt, 0), dfs2(rt, rt);
    
    build(1, 1, n * m);
    scanf("%d", &q);
    while (q--) {
        int x, y, t, xx, yy, tt;
        scanf("%d%d%d%d%d%d", &x, &y, &t, &xx, &yy, &tt);
        int u = id(x, y), v = id(xx, yy);
        int lim = query_path(u, v);

        int ans = 0, now = t;
        if (lim < t) ans += t - lim, now = lim;    //直接下楼
        else now = t;   //不动
        printf("%d\n", ans + abs(tt - now) );
    }
    return 0;
}
```

---

## 作者：whx2009 (赞：3)

~~本蒟蒻第一次阿克了，纪念一下。~~
## 本题思路：
这道题乍一看上去很复杂，可是仔细读一遍题目就会发现其实楼层之间相互装换是不计入最后答案的贡献的。我们完全可以先求出最多留在哪一层可以从起点楼到终点楼，如果这个值比起点楼所在楼层要大，就先在起点楼移动到当前合法楼层。然后我们可以直接移动到终点楼，对两个楼层的差统计进入答案。

那么实现两个楼相互到达的最高楼层我们可以使用边权从大到小的 kruskal 重构树（相邻的两栋房的边权就是两栋房中高度小的一个的高度），这样我们直接求一个 lca 就知道使两栋房子相互到达的最高楼层了，剩下的直接求即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int fa[2500005];
int a[505][505],id[505][505];
struct f1{int l,r,k;}b[500005];
int dep[500005],f[500005][35],dis[500005];
int find(int x){
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
bool cmp(f1 x,f1 y){
	return x.k>y.k;
}
vector<int>s[500005];
void dfs(int p,int fa){dep[p]=dep[fa]+1;
	f[p][0]=fa;for(int i=1;i<=30;i++)f[p][i]=f[f[p][i-1]][i-1];
	for(int i=0;i<s[p].size();i++){
		int y=s[p][i];
		dfs(y,p);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=30;i>=0;i--){
		if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	}
	if(x==y) return x;
	for(int i=30;i>=0;i--){
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	}
	return f[x][0];
}
signed main(){
	int h,w;cin>>h>>w;
	int cnt=0,top=0;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>a[i][j];id[i][j]=++top;
			if(i-1>=1) b[++cnt].l=id[i][j],b[cnt].r=id[i-1][j],b[cnt].k=min(a[i][j],a[i-1][j]);
			if(j-1>=1) b[++cnt].l=id[i][j],b[cnt].r=id[i][j-1],b[cnt].k=min(a[i][j],a[i][j-1]);
		}
	}
	for(int i=1;i<=top;i++) fa[i]=i,dis[i]=1e18;
	sort(b+1,b+1+cnt,cmp);
	for(int i=1;i<=cnt;i++){
		int u=find(b[i].l),v=find(b[i].r);
		if(u==v) continue;
		top++;fa[top]=top;
		s[top].push_back(u),s[top].push_back(v);
		fa[u]=fa[v]=top;
		dis[top]=b[i].k;
	} dfs(top,0);
	int q;cin>>q;
	while(q--){
		int as,bs,ys,cs,ds,zs;
		cin>>as>>bs>>ys>>cs>>ds>>zs;
		as=id[as][bs];cs=id[cs][ds];
		int lc=lca(as,cs);int ans=0;
		if(dis[lc]<ys) ans+=ys-dis[lc],ys=dis[lc];
		ans+=abs(zs-ys);
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：chenxi2009 (赞：2)

## 思路
显然从 $(A,B,Y)$ 走到 $(C,D,Z)$ 的最优路径是这样的：在 $(A,B)$ 从 $Y$ 下降到某一个高度 $X$，在这个高度上走到 $(C,D)$，再走到高度 $Z$。不考虑复杂度的情况下这是可以二分判断可达性的。

看做一个图，相邻的两个点 $(i,j)$ 和 $(k,l)$ 在高度不低于 $\min(f_{i,j},f_{k,l})$ 时连边，我们从高到低连边，可以在 $O(HW+F)$ 的时间内解决一系列离线的判定性问题：$(A,B)$ 和 $(C,D)$ 在最低高度 $X$ 为 $x$ 时是否能互相到达？

发现如果我们二分判断每一个询问，是把它拆成 $O(\log F)$ 个有序的离线判断的，而做一次并查集可以在 $O(HW+F)$ 的时间内同时判断多个询问。

所以可以**同时二分所有询问**，每次给所有询问都取自己二分域的中间高度判断 $(A_i,B_i)$ 与 $(C_i,D_i)$ 是否可达，直到所有询问的二分值域大小为 $1$。

时间复杂度根据具体实现有细微的变化，提供了 $O(\log F((HW+Q)\alpha(HW)+F))$ 的代码。
## 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
struct node{
	int u,v;
};
int h,w,f[300000],q,a,b,c,d,y[300000],z[300000],u[300000],v[300000],l[300000],r[300000],mid[300000],mx,fa[300000];
vector<int>s[2000000];
vector<node>e[2000000];
inline int min(int a,int b,int c){return min(a,min(b,c));}
inline int t(int x,int y){return (x - 1) * w + y;}//为了方便，把二维点对转成数字 
int find(int x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
int main(){
	read(h,w);
	for(int i = 1;i <= h * w;i ++) read(f[i]);
	for(int i = 1;i <= h;i ++) for(int j = 1;j < w;j ++) e[min(f[t(i,j)],f[t(i,j + 1)])].push_back({t(i,j),t(i,j + 1)});//横向的边，在下降到某个高度时连上 
	for(int i = 1;i < h;i ++) for(int j = 1;j <= w;j ++) e[min(f[t(i,j)],f[t(i + 1,j)])].push_back({t(i,j),t(i + 1,j)});
	read(q);
	for(int i = 1;i <= q;i ++){
		read(a,b,y[i],c,d,z[i]); 
		u[i] = t(a,b),v[i] = t(c,d),l[i] = 1,r[i] = 1000000;
	}
	do{//当还有询问的二分没完成时 
		for(int i = 1;i <= h * w;i ++) fa[i] = i;//并查集初始化 
		for(int i = 1;i <= q;i ++) if(l[i] < r[i]) s[l[i] + r[i] + 1 >> 1].push_back(i);//这个询问在下降到这个高度时要做判断 
		for(int i = 1000000;i;i --){
			for(auto p : e[i]) fa[find(p.u)] = find(p.v);//高度下降，连边 
			for(int chk : s[i]){//判断每一个二分这个高度的询问 
				if(find(u[chk]) == find(v[chk])) l[chk] = i;
				else r[chk] = i - 1;
			}
			s[i].clear();
		}
		mx = 0;
		for(int i = 1;i <= q;i ++) mx = max(mx,r[i] - l[i]);
	}while(mx);
	for(int i = 1;i <= q;i ++) printf("%d\n",y[i] + z[i] - 2 * min(y[i],z[i],l[i]));
	return 0;
}
```

---

## 作者：Xy_top (赞：2)

没想到 Kruskal 重构树，输？

口胡另外一个做法，显然成立。（其实是赛时没写完的做法）

观察到最优策略可以做到只用起点和终点的楼进行改变层数的操作，于是我们可以二分这个层数。

然后对于每个层数，都开一个可持久化并查集来维护连通性。

由于每条边只会被加入一次，这里的复杂度是 $O(n\log n)$ 的。对于每次二分查询连通性需要 $O(\log h\log^2 n)$ 的复杂度，总复杂度为 $O(q\log h\log^2 n)$，显然爆炸。

思考原因，发现加点复杂度过低，查询复杂度过高，于是我们需要一种加点复杂度在 $\log^2 n$ 之内的，且查询复杂度在 $\log n$ 之内的。

基于莫队加值域分块过可持久化线段树 $1$ 容易想到对于原数组分块进行可持久化操作。

具体地说，每次修改会新建常数个大小的块，并将 $\sqrt{n}$ 级别个数的块的编号存到数组里，查询可做到 $O(\log n)$。

所以最终复杂度为 $O(n\sqrt {n} + q\log n \log V)$，由于 $5$ 秒时限且按秩合并很难被卡满，笔者认为是很容易通过的。其中 $n=H\times W$。

---

## 作者：Left_i_Forever (赞：2)

$\Large{\text{Solution}}$

~~下午才帮同学调了双倍经验，晚上没看出来。~~

这题设计一个听起来高大上的~~好像比较~~冷门算法——**最小瓶颈生成树**。

大概意思就是需要一棵生成树，使得生成树上两点之间的路径上边权最大的最小。怎么求最小瓶颈生成树？其实他就是最小生成树。感性理解一下，如果你舍弃最小生成树上的边去选另外的边组成的生成树，一定会有一对点经过这条边，而他肯定是不优的。

而这题恰恰是一个**最大瓶颈生成树**。

为何？首先看到这道双倍经验——[P1967 [NOIP 2013 提高组] 货车运输](https://www.luogu.com.cn/problem/P1967)，这道题就十分明显。我们要尽量让货车经过的边边权最小值最大，那我们就找一颗最大生成树即可。之后我们可以在这棵树上通过倍增~~或树剖~~来求路径上的最大值。

而这道题，我们从一个楼层走到另一个楼层，最好的情况是直接走天桥一直走到对应楼，然后直上（反过来先下再走天桥一样）。但是会有一些楼没有足够的高度，我们就要找到**从一栋楼走向另一栋楼经过楼的高度最小值最大是多少**。

那么这道题就转换成了货车运输了。建边方式就是对于每两个相邻的楼，建一条边权为两个楼高度小的那个的边。那么这道题也就解决了。

$\Large{\text{Code}}$

```cpp
#include <bits/stdc++.h>
//#define int long long
#define x first
#define y second
using namespace std;
typedef pair <int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
typedef complex <double> cd;
const double PI = acos (-1);
const double eps = 1e-10;
const int N = 2.5e5 + 10, M = 5e5 + 10;
const int mod = 1e9 + 7;
//const int mod = 998244353;

int n, m, h[510][510];
int pos(int x, int y)
{
    return m * (x - 1) + y;
}
struct edge
{
    int u, v, w;
} e[M];
int cur;
bool cmp(edge x, edge y)
{
    return x.w > y.w;
}
int f[N];
int find(int x)
{
    if (f[x] == x) return x;
    return f[x] = find (f[x]);
}
vector <pii> v[N];
int st[N][14], minn[N][14], d[N];
void dfs(int u, int fa)
{
    for (int j = 1; j <= 13; j++)
        st[u][j] = st[st[u][j - 1]][j - 1], minn[u][j] = min (minn[u][j - 1], minn[st[u][j - 1]][j - 1]);
    for (pii t : v[u])
    {
        int j = t.first, w = t.second;
        if (j == fa) continue;
        st[j][0] = u, minn[j][0] = w;
        d[j] = d[u] + 1;
        dfs (j, u);
    }
}

int lca(int a, int b)
{
    if (d[a] < d[b]) swap (a, b);
    for (int i = 13; i >= 0; i--)
        if (d[st[a][i]] >= d[b]) a = st[a][i];
    if (a == b) return a;
    for (int i = 13; i >= 0; i--)
        if (st[a][i] != st[b][i])
            a = st[a][i], b = st[b][i];
    return st[a][0];
}

int ask(int a, int b)
{
    int LCA = lca (a, b);
    int res = 2e9;
    for (int i = 13; i >= 0; i--)
        if (d[st[a][i]] >= d[LCA])
            res = min (res, minn[a][i]), a = st[a][i];
    for (int i = 13; i >= 0; i--)
        if (d[st[b][i]] >= d[LCA])
            res = min (res, minn[b][i]), b = st[b][i];
    return res;
}

signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            cin >> h[i][j];
            if (i - 1) e[++cur] = {pos (i - 1, j), pos (i, j), min (h[i - 1][j], h[i][j])};
            if (j - 1) e[++cur] = {pos (i, j - 1), pos (i, j), min (h[i][j - 1], h[i][j])};
        }
    sort (e + 1, e + cur + 1, cmp);
    for (int i = 1; i <= n * m; i++)
        f[i] = i;
    for (int i = 1; i <= cur; i++)
    {
        int uu = find (e[i].u), vv = find (e[i].v);
        if (uu == vv) continue;
        f[uu] = vv;
        v[e[i].u].push_back ({e[i].v, e[i].w});
        v[e[i].v].push_back ({e[i].u, e[i].w});
    }
    memset (minn, 0x3f, sizeof minn);
    dfs (1, 0);
    int q;
    cin >> q;
    while (q--)
    {
        int sx, sy, sh, tx, ty, th;
        cin >> sx >> sy >> sh >> tx >> ty >> th;
        if (sx == tx && sy == ty)
        {
            cout << abs (sh - th) << "\n";
            continue;
        }
        int s = pos (sx, sy), t = pos (tx, ty);
        int z = ask (s, t);
        if (z >= min (sh, th)) cout << abs (sh - th) << "\n";
        else cout << abs (sh - z) + abs (th - z) << "\n";
    }
    return 0;
}
```

---

## 作者：lilong (赞：1)

题目要求最小化爬楼梯的次数，那么我们就要让楼层的变化尽量小，即沿线楼房高度越高越好。不难发现影响答案的是路线中的楼房高度的最小值，则需要**最大化最小值**。那么就不难用 Kruskal 重构树做了。对每个点进行唯一编号，相邻的点建**边权为较小的的楼房高度**的双向边。剩下的就是 Kruskal 的模板了。最后求解答案时有一些细节，详见代码。

时间复杂度 $O(nm\log nm+q\log^2 nm)$，当然如果使用倍增代替树链剖分，则可以做到 $O((nm+q)\log nm)$。


```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#define N 1000001

using namespace std;

vector<int> G[N];
int n,m,a[1001][1001],fa[N],cnt,cnt1,hd[N],b[N],node;
int top[N],siz[N],son[N],t[N * 4],dep[N],ans,id[N],rev[N],tot;

int getid( int i , int j )
{
    return ( i - 1 ) * m + j;
}

struct E
{
    int v,w,nxt;
}e[N * 2];

struct E1
{
    int u,v,w;
}e1[N * 2];

void addedge( int u , int v , int w )
{
    cnt ++;
    e[cnt].v = v;
    e[cnt].w = w;
    e[cnt].nxt = hd[u];
    hd[u] = cnt;

}

void add( int u , int v , int w )
{
    addedge( u , v , w );
    addedge( v , u , w );
    cnt1 ++;
    e1[cnt1] = { u , v , w };
}

bool cmp( E1 x , E1 y )
{
    return x.w > y.w;
}

int cx( int x )
{
    if( x == fa[x] ) return x;
    return fa[x] = cx( fa[x] );
}

void dfs1( int u , int ff )
{
    fa[u] = ff;
    dep[u] = dep[ff] + 1;
    siz[u] = 1;
    for( auto v : G[u] )
    {
        if( v == ff ) continue;
        dfs1( v , u );
        siz[u] += siz[v];
        if( siz[v] > siz[son[u]] )
            son[u] = v;
    }
}

void dfs2( int u , int ff , int flag )
{
    id[u] = ++ tot;
    rev[tot] = u;
    if( flag ) top[u] = u;
    else top[u] = top[ff];
    if( son[u] ) dfs2( son[u] , u , 0 );
    for( auto v : G[u] )
    {
        if( v == ff || v == son[u] ) continue;
        dfs2( v , u , 1 );
    }
}

void build( int u , int l , int r )
{
    if( l == r )
    {
        t[u] = b[rev[l]];
        return;
    }
    int mid = ( l + r ) >> 1;
    build( u << 1 , l , mid );
    build( u << 1 | 1 , mid + 1 , r );
    t[u] = min( t[u << 1] , t[u << 1 | 1] );
}

int query( int u , int l , int r , int L , int R )
{
    if( L <= l && r <= R ) return t[u];
    int mid = ( l + r ) >> 1,mi = 10000000;
    if( L <= mid ) mi = min( mi , query( u << 1 , l , mid , L , R ) );
    if( R > mid ) mi = min( mi , query( u << 1 | 1 , mid + 1 , r , L , R ) );
    return mi;
}

int que( int u , int v )
{
    int mi = 10000000;
    while( top[u] != top[v] )
    {
        if( dep[top[u]] > dep[top[v]] ) swap( u , v );
        mi = min( mi , query( 1 , 1 , node , id[top[v]] , id[v] ) );
        v = fa[top[v]];
    }
    if( dep[u] > dep[v] ) swap( u , v );
    mi = min( mi , query( 1 , 1 , node , id[u] , id[v] ) );
    return mi;
}

int main()
{
    cin >> n >> m;
    for( int i = 1 ; i <= n ; i ++ )
        for( int j = 1 ; j <= m ; j ++ )
            cin >> a[i][j],b[getid( i , j )] = a[i][j];
    for( int i = 1 ; i <= n ; i ++ )
        for( int j = 1 ; j <= m ; j ++ )
        {
            if( i - 1 >= 1 ) add( getid( i - 1 , j ) , getid( i , j ) , min( a[i - 1][j] , a[i][j] ) );
            if( i + 1 <= n ) add( getid( i + 1 , j ) , getid( i , j ) , min( a[i + 1][j] , a[i][j] ) );
            if( j - 1 >= 1 ) add( getid( i , j - 1 ) , getid( i , j ) , min( a[i][j - 1] , a[i][j] ) );
            if( j + 1 <= m ) add( getid( i , j + 1 ) , getid( i , j ) , min( a[i][j + 1] , a[i][j] ) );
        }
    sort( e1 + 1 , e1 + cnt1 + 1 , cmp );
    for( int i = 1 ; i <= n * m * 2 ; i ++ )
        fa[i] = i;
    node = n * m;
    int u,v;
    for( int i = 1 ; i <= cnt1 ; i ++ )
    {
        u = e1[i].u,v = e1[i].v;
        if( cx( u ) == cx( v ) ) continue;
        node ++;
        b[node] = e1[i].w;
        G[node].push_back( cx( u ) );
        G[node].push_back( cx( v ) );
        fa[cx( u )] = fa[cx( v )] = node;
        // cout << u << ' ' << v << ' ' << e1[i].w << '\n';
    }
    // cout << node << '\n';
    dfs1( node , 0 );
    dfs2( node , 0 , 1 );
    build( 1 , 1 , node );
    int q,x1,y1,x2,y2,h1,h2,dd;
    cin >> q;
    while( q -- )
    {
        cin >> x1 >> y1 >> h1 >> x2 >> y2 >> h2;
        u = getid( x1 , y1 ),v = getid( x2 , y2 );
        // cout << u << ' ' << v << '\n';
        ans = 0;
        if( h1 > h2 ) ans += h1 - h2,h1 = h2;//比较起点与终点高度
        dd = que( u , v );
        if( dd < h1 ) ans += h1 - dd,h1 = dd;//判断沿线是否需要向下下楼
        ans += abs( h1 - h2 );//到达终点
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：Aegleseeker_ (赞：1)

注意到路径上最低楼房高度一定越大越优，因为可以尽量避免走电梯的次数。

考虑相邻的楼房之间连边，边权为两个楼房高度的 $\min$。

于是我们转换成求一条瓶颈路，既最大化路径上最小边权，这个可以直接使用 kruskal 重构树解决。

---

## 作者：sodalyghat (赞：0)

### 思路
由于这道题要最小化纵向的步数，那么我们就要尽可能的不上下移动。然后我们分析一下可以发现，有两种情况必须上下移动，一个是起点和终点的高度差，一个就是由于你起点的楼层过高，导致必须去更低的楼层才能走到终点。第一种是可以直接算的，而第二个显然可以二分，楼层越低越容易。而直接二分会超时，直接上整体二分就好。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Luo_ty{
	const int MAXN = 505;
	int a[MAXN][MAXN];
	struct Q{
		int x1, y1, h1, x2, y2, h2, id;
	}qu[1000005];
	int ans[1000005], hi[1000005];
	int n, m;
	int id(int x, int y){
		return (x - 1) * m + y;
	}
	//需要回滚 
	int fa[1000005], sz[1000005];
	struct HIS{
		int x, y, sx, fy;
	}his[1000005];
	int cnt;
	int belong(int x){
		if(fa[x] == x) return x;
		return belong(fa[x]);
	}
	void Union(int u, int v, int &rolled){
		int x = belong(u), y = belong(v);
		if(sz[x] < sz[y]) swap(x, y);
		his[++cnt] = (HIS){x, y, sz[x], fa[y]};
		rolled++;
		if(x == y) return ;
		fa[y] = x;
		sz[x] += sz[y];
	}
	void roll(){
		HIS tmp = his[cnt--];
		fa[tmp.y] = tmp.fy;
		sz[tmp.x] = tmp.sx; 
	}
	int dx[4] = {0, 1, 0, -1};
	int dy[4] = {1, 0, -1, 0};
	struct XB{
		int x, y;
	};
	vector<XB> f[1000005]; 
	void solve(int l, int r, vector<Q> qu){
		if(!qu.size()) return ;
		if(l == r){
			for(Q i : qu){
				hi[i.id] = l;
			}
			return ;
		}
		vector<Q> L, R;
		int mid = (l + r + 1) / 2; 
		int rolled = 0;
		for(int now = r;now >= mid;now--){
			for(XB w : f[now]){
				int i = w.x, j = w.y;
				for(int k = 0;k < 4;k++){
					int x = i + dx[k], y = j + dy[k];
					if(x < 1 || x > n || y < 1 || y > m) continue;
					if(a[x][y] < mid) continue;
					Union(id(i, j), id(x, y), rolled);
				}
			}
		}
		for(Q i : qu){
			if(belong(id(i.x1, i.y1)) == belong(id(i.x2, i.y2))){
				R.push_back(i);
			}
			else{
				L.push_back(i);
			}
		}
		solve(l, mid - 1, L);
		while(rolled){
			roll();
			rolled--;
		}
		solve(mid, r, R);
	}
	vector<Q> qq;
	int main(){
		scanf("%d%d", &n, &m);
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= m;j++){
				scanf("%d", &a[i][j]);
				f[a[i][j]].push_back((XB){i, j});
			}
		} 
		int q;
		scanf("%d", &q);
		for(int i = 1;i <= q;i++){
			scanf("%d%d%d%d%d%d", &qu[i].x1, &qu[i].y1, &qu[i].h1, &qu[i].x2, &qu[i].y2, &qu[i].h2);
			qu[i].id = i;
			if(qu[i].h1 < qu[i].h2){
				ans[i] = qu[i].h2 - qu[i].h1;
				qu[i].h2 = qu[i].h1;
			}
			else{
				ans[i] = qu[i].h1 - qu[i].h2;
				qu[i].h1 = qu[i].h2;
			}
			qq.push_back(qu[i]);
		}
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= m;j++){
				fa[id(i, j)] = id(i, j);
				sz[id(i, j)] = 1;
			}
		}
		solve(1, 1000000, qq);
		for(int i = 1;i <= q;i++){
			printf("%d\n", ans[i] + 2 * max(qu[i].h1 - hi[i], 0));
		}
		return 0;
	}
}
int main(){
	return Luo_ty::main(); 
}//International Milan is the best team.
```

---

## 作者：MutU (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/AT_abc394_g)

对于某个询问，假设 $h_{low}$ 为最优路径上达到的最低楼层。

由于楼房之间的移动不算步数，所以 $h_{low}$ 直接决定答案的值。令 $h_x=$ `起点的楼层`，$h_y=$ `终点的楼层`，可以先从起点直接下降到第 $h_{low}$ 层，然后走到终点那栋楼，上到 $h_y$ 层。

这也证明了对于所有最优路径 $h_{low}$ 唯一。

考虑将相邻两栋楼连边，边权为两楼较矮那一栋的高度。表示只有高度小于等于这个值才能通过。

那么两栋楼路径中最低楼层 $=$ 两楼之间所有路径上边权最小值的最大值。

直接套用 [kruskal 重构树](https://oi-wiki.org/graph/mst/#kruskal-%E9%87%8D%E6%9E%84%E6%A0%91)，每条边按照边权从大到小排序，两点 LCA 的点权即为 $h_{low}$。

### Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000010; //如果开500注意点数最大是N*N*2 
int n,m,q,h[610][610];
struct edge{
    int nxt,to;
}e[N];
int root,head[N],cnt,id[610][610],val[N];
struct Edge{
    int u,v,w;
}E[N];
int tot;
inline void add(int u,int v){
    e[++cnt].nxt=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}
int F[N];
int find(int x){
    if(F[x]==x) return x;
    else return F[x] = find(F[x]);
}
bool cmpe(Edge a,Edge b){
    return a.w>b.w;
}
inline void build(){ 
    root=n*m;
    for(int i=1;i<=tot;i++){
        int u=E[i].u,v=E[i].v,w=E[i].w;
        int U=find(u),V=find(v);
        if(U==V) continue;
        add(++root,U);
        add(root,V);
        val[root]=w;
        F[U]=root; F[V]=root;
    }
    return;
}
int pre[N][21],dep[N];
inline void dfs(int u,int fa){ 
    pre[u][0]=fa;
    dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        dfs(v,u);
    }
    return;
}
inline void init(){
    for(int i=1;i<=20;i++) for(int j=1;j<=root;j++) pre[j][i]=pre[pre[j][i-1]][i-1];
    return;
}
int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;i>=0;i--) if(dep[pre[x][i]]>=dep[y]) x=pre[x][i];
    if(x==y) return x;
    for(int i=20;i>=0;i--) if(pre[x][i]!=pre[y][i]) x=pre[x][i],y=pre[y][i];
    return pre[x][0];
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
        cin>>h[i][j];
        id[i][j]=(i-1)*m+j;
        val[id[i][j]]=h[i][j]; 
        if(i>1) E[++tot].u=id[i-1][j],E[tot].v=id[i][j],E[tot].w=min(h[i-1][j],h[i][j]);
        if(j>1) E[++tot].u=id[i][j-1],E[tot].v=id[i][j],E[tot].w=min(h[i][j-1],h[i][j]);
    }
    sort(E+1,E+1+tot,cmpe);
    for(int i=1;i<=n*m*2;i++) F[i]=i;
    build();
    dfs(root,0);
    init();
    cin>>q;
    for(int i=1;i<=q;i++){
        int ux,uy,uz;
        int vx,vy,vz;
        cin>>ux>>uy>>uz;
        cin>>vx>>vy>>vz; 
        int k=LCA(id[ux][uy],id[vx][vy]),kh=min(val[k],min(uz,vz));
        cout<<abs(uz-kh)+abs(vz-kh)<<'\n';
    }
    return 0;
}
```

[提交记录](https://atcoder.jp/contests/abc394/submissions/63175012)

---

## 作者：wangshulin (赞：0)

# 前言
赛时口胡整体二分加可撤销并查集 $O((q+nm) \log⁡^2 (nm))$ 做法但未能战胜，赛后订正发现自己想复杂的痛！于是有了标题所述感想。
# 思路
发现对于每个问题，发现只需要求出 $(A_{i},B_{i})$ 到 $(C_{i},D_{i})$ 的路径中“经过的大楼高度最小值”的最大值即可。

于是尝试二分。

发现二分的 $check(x)$ 函数是长这样的：将比大楼高度比 $x$ 大的点全部扔出来，它们组成了若干个连通块，然后只需要判断起点和终点是否连通即可，用并查集维护。

但是每次 $check(x)$ 是 $O(nm \alpha(nm))$ 的，这很不好。

但是发现对于所有起点和终点，$x$ 相同时 $check(x)$ 函数都是一样的，于是就可以快乐地整体二分套可撤销并查集做啦！

不会整体二分看[这里](https://oi-wiki.org/misc/parallel-binsearch/)。

不会可撤销并查集看[这个 blog by 神犇](https://www.cnblogs.com/zac2010/p/17985517)，先前我也是拿这个学的。

注意可撤销并查集不能使用路径压缩，只能做到 $O(\log (nm))$。

所以时间复杂度就是 $O((q+nm) \log^{2}(nm))$。
# 代码
[AC link](https://atcoder.jp/contests/abc394/submissions/63070348)。

---

## 作者：lzyqwq (赞：0)

干瞪眼半天没想到是这个错误 /qd。

对于每组询问，考虑求出一个最大的值 $\text{ans}_i$，使得存在一条 $(a,b)$ 和 $(c,d)$ 间的路径满足路径上所有点的 $f$ 均 $\ge \text{ans}_i$。

一个暴力是，二分，然后用并查集维护所有 $f_{x,y}\ge \text{mid}$ 的点构成的连通块。单组询问的时间复杂度是 $\mathcal{O}(nm\alpha(nm)\log |V|)$。

优化就考虑整体二分，将当前点集中 $f_{x,y}>\text{mid}$ 的点加入，对每个询问查询起点终点是否连通。如果是就扔到 $[\text{mid}+1,r]$ 的区间里面，否则扔到 $[l,\text{mid}]$ 的区间里面。把点按照点权也扔到对应的区间里面。用按秩合并的可撤销并查集维护即可。

有一个问题是，一个区间 $[l,r]$ 会用到 $[r+1,|V|]$ 中的点。但是显然不能把这些点存到点集里面。解决方法是，每次先不撤销，做左区间。然后再撤销，做右区间。

最后判断一下 $Y,Z$ 和 $\text{ans}_i$ 的大小关系，如果都比她大答案就是 $Y+Z-2\text{ans}_i$，否则是 $|Y-Z|$。

时间复杂度 $\mathcal{O}((nm+q)\log nm\log |V|)$。

$\text{ans}_i$ 本质上是两点间的瓶颈路径，所以可以建最大生成树然后求路径最小值。这样是 1log。

---

## 作者：Tang_chao (赞：0)

## [ABC394G] Dense Buildings 题解


> 应该是近期 ABC 上最好想最难调的 G 题了。

最后几分钟过了 G，差点掉粪了。个人评价 F < G < E。

看起来就很套路的题。双倍经验 [P1967](https://www.luogu.com.cn/problem/P1967)。

假定 $Y \le Z$（$Y$，$Z$ 为问询层数）。  
首先分析要怎么走。显然要找到一条路径，经过的楼的高度最小值最大，这样可以尽量少的上下楼。记这个值为 $V$。
  
如果 $V \ge Y$，考虑只在 $Y$ 这层走，到了终点再上到 $Z$ 层。答案为 $Z-Y$。  
否则，考虑先下到 $V$ 这一层，到达终点后再上到 $Z$ 层。答案为 $Y+Z-2 \times V$。

接下来再说 $V$ 怎么求。

考虑按照 $2$ 操作的方式建图，边权为两栋楼的层数取 $\min$。

回顾一下 Kruskal 求最大生成树，以贪心的方式建树，能让其最小值最大。考虑建出最大生成树，那么原问题变成树上两点间路径的点权最小值。

这是一个经典问题。由于不带修改，考虑倍增预处理时顺手把点权维护好，求 lca 时再倍增求最小值即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 250009
int h,w,n,m,x[514][514],dep[N],id[N],val[N],p[N][22],mn[N][22];
struct edge{ int u,v,num; } e[N << 3];
vector<int> to[N];
bool cmp(edge a,edge b){ return a.num > b.num; }
int root(int x){
	if(id[x] == x) return x;
	else return id[x] = root(id[x]);
}
void Kruskal(){
	sort(e + 1,e + m + 1,cmp);
	for(int i = 1;i <= n;i++) id[i] = i;
	int cnt = 0;
	for(int i = 1;i <= m && cnt < n - 1;i++){
		int ru = root(e[i].u),rv = root(e[i].v);
		if(ru != rv){
			id[ru] = rv;
			cnt++;
			to[e[i].u].push_back(e[i].v);
			to[e[i].v].push_back(e[i].u);
			//cout<<e[i].u<<" "<<e[i].v<<endl;
		}
	}
}
int dx[4] = {0,0,1,-1},dy[4] = {1,-1,0,0};
int idx(int i,int j){ return (i - 1) * w + j; }
void init(int u,int fa){
	dep[u] = dep[fa] + 1;
	p[u][0] = fa; mn[u][0] = val[fa];
	for(int i = 1;i <= 20;i++){
		p[u][i] = p[p[u][i - 1]][i - 1];
		mn[u][i] = min(mn[u][i - 1],mn[p[u][i - 1]][i - 1]);
	}
	for(int i = 0;i < to[u].size();i++){
		int v = to[u][i];
		if(v == fa) continue;
		init(v,u);
	}
}
int cal(int u,int v){
	if(dep[u] < dep[v]) swap(u,v);
	int ans = min(val[u],val[v]);
	for(int i = 20;i >= 0;i--)
		if(dep[p[u][i]] >= dep[v]) ans = min(ans,mn[u][i]),u = p[u][i];
	if(u == v) return ans;
	for(int i = 20;i >= 0;i--)
		if(p[u][i] != p[v][i]) ans = min(ans,min(mn[u][i],mn[v][i])),u = p[u][i],v = p[v][i];
	return min(ans,val[p[u][0]]);
}
signed main(){
	cin>>h>>w;
	for(int i = 1;i <= h;i++)
		for(int j = 1;j <= w;j++){
			cin>>x[i][j];
			val[idx(i,j)] = x[i][j];
		}
	for(int i = 1;i <= h;i++)
		for(int j = 1;j <= w;j++){
			for(int k = 0;k < 4;k++){
				int u = i + dx[k],v = j + dy[k];
				if(u < 1 || u > h || v < 1 || v > w) continue;
				e[++m] = {idx(i,j),idx(u,v),min(x[i][j],x[u][v])};
			}
		}
	n = h * w;
	Kruskal();
	/*for(int i = 1;i <= n;i++)
		for(int j = 0;j < to[i].size();j++)
			cout<<i<<" "<<to[i][j]<<endl;*/
	init(1,0);
	int q;
	cin>>q;
	while(q--){
		int x,y,a,u,v,b;
		cin>>x>>y>>a>>u>>v>>b;
		int ans = cal(idx(x,y),idx(u,v));
		if(ans > min(a,b)) cout<<abs(a - b)<<endl;
		else cout<<abs(a - ans) + abs(b - ans)<<endl;
	}
	return 0;
}
```

---

## 作者：ljy05 (赞：0)

首先，高桥的路线肯定是这样的：

1. 下楼梯到某一层
2. 走天桥到终点所在的大楼，中途**不走楼梯**
3. 上楼梯到终点

所以中途他的楼层是不变的。并且因为他不想爬楼梯，所以他应该选择经过最矮楼最高的路径。

我们把城市看成一张网格图，并求出这张图的最大生成树，高桥的最优路径[一定在这棵树上](https://oi-wiki.org/graph/mst/#%E7%93%B6%E9%A2%88%E7%94%9F%E6%88%90%E6%A0%91)。并且，因为树上两点之间不绕路的路径只有一条，所以，只需要求出这条路径上的最小点权就能算出答案。

我们可以通过在求 lca 的过程中，顺便记录最小点权来解决这个问题，具体如何实现可以参考代码。

记录：https://atcoder.jp/contests/abc394/submissions/63058685

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[250010],fa[250010],dep[250010];//分别为高度，并查集的父亲数组，点在树中的深度 
int tf[250010][30],mf[250010][30];//分别为lca的父亲数组，点到它的这个祖先经过的最小点权 
int hea[250010],nex[500010],to[500010];//邻接表数组 
int bld[250010];//用于将点按点权从大到小排序 
int a,b,u,c,d,v;
int h,w,q;
int p;
void ae(int x,int y){//加边 
	nex[++p]=hea[x];
	hea[x]=p;
	to[p]=y;
}
int gf(int x){//并查集中找到父亲 
	if(fa[x]==x) return x;
	return fa[x]=gf(fa[x]);
}
int gid(int x,int y){//为了偷懒将二维坐标压缩成一维，这是将二维映射为一维的函数 
	return (x-1)*w+y;
}
int mv(int x,int y){//移动，y为方向 
	if(y==0&&x>w) return x-w;
	else if(y==1&&x+w<=h*w) return x+w;
	else if(y==2&&x%w!=1) return x-1;
	else if(y==3&&x%w!=0) return x+1;
	else return 0;
}
int cmp(int x,int y){
	return f[x]>f[y];
}
void dfs(int x){
	for(int i=hea[x];i!=0;i=nex[i]){//枚举出边 
		if(tf[x][0]!=to[i]){
			tf[to[i]][0]=x;
			mf[to[i]][0]=min(f[x],f[to[i]]);//边权为两个点的最小点权 
			dep[to[i]]=dep[x]+1;
			dfs(to[i]);
		}
	}
}
int lca(int x,int y){//返回x到y的最小点权 
	if(dep[x]<dep[y]) swap(x,y);
	int ans=1e9;//答案 
	for(int i=20;i>=0;i--){
		if(dep[tf[x][i]]>=dep[y]){
			ans=min(ans,mf[x][i]);//更新答案 
			x=tf[x][i];
		}
	}
	if(x==y) return ans;
	for(int i=20;i>=0;i--){
		if(tf[x][i]!=tf[y][i]){
			ans=min(ans,min(mf[x][i],mf[y][i]));
			x=tf[x][i];
			y=tf[y][i];
		}
	}
	return min(ans,f[tf[x][0]]);
}
int main(){
	scanf("%d%d",&h,&w);
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++) scanf("%d",&f[gid(i,j)]);
	}
	for(int i=1;i<=h*w;i++) bld[i]=fa[i]=i;
	sort(bld+1,bld+h*w+1,cmp);//将点从大到小排序 
	for(int i=1;i<=h*w;i++){//求最大生成树 
		for(int jj=0;jj<4;jj++){
			int j=mv(bld[i],jj);
			if(j==0||f[bld[i]]>f[j]||gf(bld[i])==gf(j)) continue;//必须由小点连向大点 
			fa[gf(bld[i])]=gf(j);
			ae(bld[i],j);
			ae(j,bld[i]);
		}
	}
	dep[1]=1;
	dfs(1);
	for(int j=1;j<=20;j++){
		for(int i=1;i<=h*w;i++){
			tf[i][j]=tf[tf[i][j-1]][j-1];
			mf[i][j]=min(mf[i][j-1],mf[tf[i][j-1]][j-1]);
		}
	}
	scanf("%d",&q);
	while(q--){
		scanf("%d%d%d%d%d%d",&a,&b,&u,&c,&d,&v);
		int tmp=lca(gid(a,b),gid(c,d));
		if(tmp<u&&tmp<v) printf("%d\n",u+v-tmp*2);
		else printf("%d\n",abs(u-v));//注意，如果不用下楼，就只有从u层走到v层的代价 
	}
    return 0;
}
```

---

## 作者：Dtw_ (赞：0)

## 题意
给你 $n\times n$ 的网格，每个格子内有一栋楼，高度为 $a_{i,j}$。你可以在相邻的楼之间同层移动，即可以从当前这栋楼的第 $x$ 层移动到相邻的楼的第 $x$ 层（如果相邻的楼有第 $x$ 层的话）。你可以上下移动，求从 $(a,b)$ 的第 $x$ 层走到 $(c,d)$ 的第 $y$ 层的最小上下的次数。
## Solution
考虑我们走的路径，答案应该是从 $x$ 下降到这条路径上的最小值，然后走到终点再升上去。

又因为只关心上下移动的次数，所以直接建一个最大瓶颈生成树就好，直接在树上移动。因为最大生成树一定是最大瓶颈生成树，所以我们建最大生成树就好。

之后我们可以倍增或者树剖维护路径信息，求路径的最小值 $tmp$，然后答案就应该是 $\left | x - tmp\right | + \left | y - tmp\right |$ 但是有可能 $x,y$ 一开始就 $\leq tmp$ 此时我们直接从 $x$ 升到 $y$ 就行。
## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>

#define fi first
#define se second

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 5e2 + 10, M = 1e6 + 10, inf = 0x3f3f3f3f;

int n, m, a[N][N], cnt, p[M], f[M][21], dep[M], z[M][21], q;

int fifa(int x) { return p[x] == x ? x : p[x] = fifa(p[x]); }

struct Edge { int u, v, w; } e[M];

int fx[] = {0, 1, -1, 0}, fy[] = {1, 0, 0, -1};

void add(int i, int j, int x, int y)
{
    if (!(x >= 1 && x <= n && y >= 1 && y <= m)) return;
    e[++cnt] = {(i - 1) * m + j, (x - 1) * m + y, min(a[i][j], a[x][y])};
}

vector<pii> G[M];

void dfs(int u, int fa)
{
    f[u][0] = fa;
    dep[u] = dep[fa] + 1;
    for (auto e : G[u])
    {
        int v = e.fi, w = e.se;
        if (v == fa) continue;
        z[v][0] = w;
        dfs(v, u);
    }
}

int lca(int x, int y)
{
    if (dep[x] < dep[y]) swap(x, y);
    int res = inf;
    for (int i = 20; i >= 0; i--) if (dep[f[x][i]] >= dep[y]) res = min(res, z[x][i]), x = f[x][i];
    if (x == y) return res;
    for (int i = 20; i >= 0; i--) if (f[x][i] != f[y][i]) res = min(res, min(z[x][i], z[y][i])), x = f[x][i], y = f[y][i];
    res = min(res, min(z[x][0], z[y][0]));
    return res;
}

int main()
{
    fst
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j], p[(i - 1) * m + j] = (i - 1) * m + j;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) for (int k = 0; k < 4; k++) add(i, j, i + fx[k], j + fy[k]);
    sort (e + 1, e + cnt + 1, [] (Edge x, Edge y) { return x.w > y.w; });
    for (int i = 1; i <= cnt; i++)
    {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int fu = fifa(u), fv = fifa(v);
        if (fu == fv) continue;
        p[fu] = fv;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    memset(z, inf, sizeof z);
    dfs(1, 0);
    for (int j = 1; j <= 20; j++) for (int i = 1; i <= n * m; i++) f[i][j] = f[f[i][j - 1]][j - 1], z[i][j] = min(z[i][j - 1], z[f[i][j - 1]][j - 1]);
    cin >> q;
    for (int i = 1; i <= q; i++)
    {
        int a, b, c, d, x, y;
        cin >> a >> b >> x >> c >> d >> y;
        a = (a - 1) * m + b, c = (c - 1) * m + d;
        int tmp = lca(a, c);
        if (x <= tmp && y <= tmp) cout << abs(x - y) << "\n";
        else cout << abs(x - tmp) + abs(y - tmp) << "\n";
    }
    return 0;
}
```

---

## 作者：Union_Find (赞：0)

赛时最后十分钟，没做出来。

其实挺简单的，考虑到楼层越低，就越难被楼层高度限制。所以我们在走的时候除非到了我们要的那栋楼，我们就不向上走，这样子一定不劣列的。

然后我们发现，答案就和我们走到的最低楼层有关。设我们走过的最低楼层是 $t$，输入的楼层高度分别是 $at,bt$，那么答案就是 $at-t+bt-t=at+bt-2t$。所以我们只需要最大化我们经过的最小楼层即可。虽然是最小值最大，大师不好二分，而且这道题转化之后就类似于 [P1967 货车运输](https://www.luogu.com.cn/problem/P1967)，我们考虑使用最大生成树。

这道题没有边权，但是有点权，所以我们按照点权从大到小排序，然后向四周连边。跑出最大生成树后，问题就是树上两点直接最小点权问题了，直接倍增 LCA 求即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 505
#define M 250005
#define id(i, j) ((i - 1) * m + j)
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}const ll dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};
ll n, m, a[N][N], fa[M], f[M][35], minn[M][35], dep[M], ax, ay, bx, by, at, bt, vis[M];
vector <ll> e[M];
struct E{
	ll x, y, val;
}w[M];
il bool cmp(E a, E b){return a.val > b.val;}
il ll find(ll x){return fa[x] == x ? x : fa[x] = find(fa[x]);}
void dfs(ll u){dep[u] = dep[f[u][0]] + 1;for (int v : e[u]) if (v != f[u][0]) f[v][0] = u, dfs(v);}
il ll mink(ll u, ll v){
	if (dep[u] < dep[v]) swap(u, v);
	ll ans = 1e18;
	for (int j = 30; j >= 0; j--) if (dep[f[u][j]] >= dep[v]) ans = min(ans, minn[u][j]), u = f[u][j];
	if (u == v) return ans;
	for (int j = 30; j >= 0; j--) if (f[u][j] != f[v][j]) ans = min(ans, min(minn[u][j], minn[v][j])), u = f[u][j], v = f[v][j];
	return min(min(ans, minn[f[u][0]][0]), min(minn[u][0], minn[v][0]));
}
int main(){
	n = rd(), m = rd();
	memset (minn, 0x3f, sizeof minn);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
		a[i][j] = rd(), w[id(i, j)] = E{i, j, a[i][j]}, fa[id(i, j)] = id(i, j), minn[id(i, j)][0] = a[i][j];
	sort (w + 1, w + n * m + 1, cmp);
	for (int i = 1; i <= n * m; i++){
		ll x = w[i].x, y = w[i].y;
		vis[id(x, y)] = 1;
		for (int j = 0; j < 4; j++){
			ll vx = x + dx[j], vy = y + dy[j];
			if (vx < 1 || vx > n || vy < 1 || vy > m || !vis[id(vx, vy)]) continue;
			ll fu = find(id(x, y)), fv = find(id(vx, vy));
			if (fu != fv) e[id(x, y)].push_back(id(vx, vy)), e[id(vx, vy)].push_back(id(x, y)), fa[fu] = fv;
		}
	}dfs(1);
	for (int j = 1; j <= 30; j++) for (int i = 1; i <= n * m; i++)
		f[i][j] = f[f[i][j - 1]][j - 1], minn[i][j] = min(minn[i][j - 1], minn[f[i][j - 1]][j - 1]);
	for (int T = rd(); T--;){
		ax = rd(), ay = rd(), at = rd(), bx = rd(), by = rd(), bt = rd();
		ll t = mink(id(ax, ay), id(bx, by));
		if (t >= max(at, bt)) printf ("%lld\n", abs(at - bt));
		else printf ("%lld\n", abs(at - t) + abs(bt - t));
	}
	return 0;
}

```

---

## 作者：CuteMurasame (赞：0)

我们用 $(X,Y,Z)$ 表示坐标 $(X,Y)$ 的建筑的 $Z$ 层。

假设要从 $(A,B,Y)$ 走到 $(C,D,Z)$，$L$ 为可以使用 walkway 的最高楼层，则 $L=\max\limits_{\text{paths}}\min\{F\text{ on the path}\}$。

先考虑知道 $L$ 怎么做：可以先到 $X\ (1\leq X\leq L)$ 楼，用 walkway 到目标建筑，再到目标楼层。

如果要最小化上下楼的次数 $\text{ans}$，最优策略是选择一个尽可能接近 $Y$ 和 $Z$ 的 $X$，分两种情况：

1. $L\geq \max\{Y,Z\}$，直接选一个 $X\in[Y,Z]\cap \mathbb Z$，此时 $\text{ans}=\lvert Y-Z\rvert$。
2. 否则，最优选择是 $X=L$，此时 $\text{ans}=(Y-L)+(Z-L)=Y+Z-2L$。

现在我们只需要计算 $L$ 即可。

我们可以建一个图，在相邻的建筑之间连一条边，权重 $w(u,v)=\min\{F_u,F_v\}$。因为从 $u$ 到 $v$ 时，你所处的楼层不能高于这两栋建筑的楼层。

建一棵最大生成树，最大生成树上对于任意两个节点，$L$ 正好等于这两个点路径上的最小边权。

查两个点路径上的最小边权，这个可以直接倍增，不多说了。

时间复杂度 $\mathcal O(Q\log(HW))$，可以通过。

---

## 作者：_Linver_ (赞：0)

这是一个顶点数为 $H\times W$ 的网格图。

在相邻顶点 $(x_1,y_1), (x_2,y_2)$ 之间有一条权值为 $\min(F_{x_1,y_1},F_{x_2,y_2})$ 的边。

每次查询可以转化为：最大化连接顶点  $(a,b)$ 和 和顶点 $(c,d)$ 的路径中每条边的最小权重。

答案就是 $(a,b)$ 和 $(c,d)$ 值之和减去最小权重的 $2$ 倍。

建**最大生成树**，用**重链剖分**求路径最小值。

```py
import sys
sys.setrecursionlimit(1 << 25)

def main():
    input = sys.stdin.read().split()
    ptr = 0
    H = int(input[ptr]); ptr +=1
    W = int(input[ptr]); ptr +=1
    F = []
    for _ in range(H):
        row = list(map(int, input[ptr:ptr+W]))
        ptr += W
        F.append(row)
    Q = int(input[ptr]); ptr +=1
    queries = []
    for _ in range(Q):
        A = int(input[ptr])-1; ptr +=1
        B = int(input[ptr])-1; ptr +=1
        Y = int(input[ptr]); ptr +=1
        C = int(input[ptr])-1; ptr +=1
        D = int(input[ptr])-1; ptr +=1
        Z = int(input[ptr]); ptr +=1
        queries.append( (A,B,Y,C,D,Z) )

    edges = []
    for i in range(H):
        for j in range(W):
            if i+1 < H:
                w = min(F[i][j], F[i+1][j])
                edges.append( ( -w, i*W+j, (i+1)*W+j ) )
            if j+1 < W:
                w = min(F[i][j], F[i][j+1])
                edges.append( ( -w, i*W+j, i*W+(j+1) ) )

    edges.sort()
    parent = list(range(H*W))
    rank = [1]*(H*W)
    parent_edge = [ -1 ]*(H*W)
    mst_edges = [[] for _ in range(H*W)]

    def find(u):
        while parent[u] != u:
            u = parent[u]
        return u

    for edge in edges:
        w_neg, u, v = edge
        w = -w_neg
        ru = find(u)
        rv = find(v)
        if ru != rv:
            if rank[ru] < rank[rv]:
                ru, rv = rv, ru
                u, v = v, u
            parent[rv] = ru
            if rank[ru] == rank[rv]:
                rank[ru] +=1
            mst_edges[u].append( (v, w) )
            mst_edges[v].append( (u, w) )
            parent_edge[v] = (u, w)
            parent_edge[u] = (v, w)

    LOG = 20
    up = [ [ -1 for _ in range(LOG) ] for __ in range(H*W) ]
    min_edge = [ [ 0 for _ in range(LOG) ] for __ in range(H*W) ]
    depth = [0]*(H*W)

    from collections import deque
    visited = [False]*(H*W)
    for root in range(H*W):
        if visited[root]:
            continue
        q = deque()
        q.append( (root, -1, 0) )
        visited[root] = True
        while q:
            u, p_u, d = q.popleft()
            up[u][0] = p_u
            depth[u] = d
            if p_u != -1:
                for (v, w) in mst_edges[u]:
                    if v == p_u:
                        min_edge[u][0] = w
                        break
            else:
                min_edge[u][0] = 0
            for k in range(1, LOG):
                if up[u][k-1] == -1:
                    up[u][k] = -1
                    min_edge[u][k] = 0
                else:
                    up[u][k] = up[ up[u][k-1] ][k-1]
                    min_edge[u][k] = min( min_edge[u][k-1], min_edge[ up[u][k-1] ][k-1] )
            for (v, w) in mst_edges[u]:
                if not visited[v]:
                    visited[v] = True
                    q.append( (v, u, d+1) )

    def lca(u, v):
        if depth[u] < depth[v]:
            u, v = v, u
        min_val = float('inf')
        for k in reversed(range(LOG)):
            if depth[u] - (1 << k) >= depth[v]:
                min_val = min( min_val, min_edge[u][k] )
                u = up[u][k]
        if u == v:
            return (u, min_val)
        for k in reversed(range(LOG)):
            if up[u][k] != -1 and up[u][k] != up[v][k]:
                min_val = min( min_val, min_edge[u][k], min_edge[v][k] )
                u = up[u][k]
                v = up[v][k]
        min_val = min( min_val, min_edge[u][0], min_edge[v][0] )
        return (up[u][0], min_val)

    def get_min_edge(u, v):
        l, min_val = lca(u, v)
        return min_val

    for q in queries:
        A,B,Y,C,D,Z = q
        u = A * W + B
        v = C * W + D
        if u == v:
            print( abs(Y - Z) )
            continue
        X_max = get_min_edge(u, v)
        X_opt = min( X_max, Y, Z )
        res = abs(Y - X_opt) + abs(Z - X_opt)
        print(res)

if __name__ == '__main__':
    main()
```

---

## 作者：SUNCHAOYI (赞：0)

通过观察，首先可以得出几个小结论：

1. $(a_i,b_i,y_i) \to (c_i,d_i,z_i)$ 的其中一条最优路径一定是 $(a_i,b_i,y_i) \to (a_i,b_i,w) \to (c_i,d_i,w) \to (c_i,d_i,z_i)$。
2. $w$ 越小，越有可能合法，满足单调性，因此可以二分答案，最后单组询问的答案即为 $y_i + z_i - 2 \times w$。
3. 对于单组询问，可以从高到低进行相邻块合并，因此最后的答案检测可以转换为并查集检验两点的连通性。总共的时间复杂度为 $O(QV \alpha(HW) \log (V))$（其中 $V$ 便是高度的值域）。

考虑优化，不难发现各组询问直接相互独立，且可以离线操作，所以我们可以使用整体二分。首先将每组答案的 $l_i = 1,r_i = \min (y_i,z_i)$，对于一次二分操作，若此时 $l_i \le r_i$ 仍然成立，那么我们就尝试将 $\frac{l_i + r_i}{2}$ 作为该组询问的答案。检验的过程和单组询问大致相同，可以从高到低进行相邻块合并后检验连通性即可。时间复杂度就降到了 $O(Q\alpha(HW) \log (V))$，代码如下：

```cpp
#include <bits/stdc++.h>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
using namespace std;
const int M = 1e6;
const int MAXN = 505;
const int MAXQ = 2e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,m,q,fl;
int fa[M + 5],sx[MAXQ],sy[MAXQ],sh[MAXQ],fx[MAXQ],fy[MAXQ],fh[MAXQ],l[MAXQ],r[MAXQ],ans[MAXQ],a[MAXN][MAXN];
vector <pair <int,int> > f[M + 5];
vector <int> res[M + 5];
int getfa (int u) {return fa[u] == u ? u : fa[u] = getfa (fa[u]);} 
void merge (int u,int v)
{
	u = getfa (u),v = getfa (v);
	if (u != v) fa[u] = v;
}
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();m = read ();
	for (int i = 1;i <= n;++i)
		for (int j = 1;j <= m;++j) a[i][j] = read ();
	for (int i = 1;i <= n;++i)
	{ 
		for (int j = 1;j <= m;++j)
		{
			if (i != n) f[min (a[i][j],a[i + 1][j])].push_back ({(i - 1) * m + j,i * m + j});
			if (j != m) f[min (a[i][j],a[i][j + 1])].push_back ({(i - 1) * m + j,(i - 1) * m + j + 1});//相邻块的预处理
		}
	} 		
	q = read ();
	for (int i = 1;i <= q;++i)
	{
		sx[i] = read (),sy[i] = read (),sh[i] = read ();
		fx[i] = read (),fy[i] = read (),fh[i] = read ();
		l[i] = 1,r[i] = min (sh[i],fh[i]);//边界
	}
	while (!fl) //仍然有询问需要二分
	{
		fl = 1;
		for (int i = 1;i <= q;++i)
		{
			if (l[i] > r[i]) continue;
			int mid = (l[i] + r[i]) >> 1;
			res[mid].push_back (i);
			fl = 0;
		}
		for (int i = 1;i <= M;++i) fa[i] = i;
		for (int i = M;i >= 1;--i)
		{
			for (auto item : f[i]) merge (item.first,item.second);
			for (auto p : res[i]) // 第 p 个询问答案为 i 是否成立 
			{
				int u = (sx[p] - 1) * m + sy[p],v = (fx[p] - 1) * m + fy[p];
				u = getfa (u),v = getfa (v); 
				if (u == v) ans[p] = i,l[p] = i + 1;
				else r[p] = i - 1;
			}
		}
		for (int i = 1;i <= M;++i) res[i].clear ();
	}
	for (int i = 1;i <= q;++i) printf ("%d\n",sh[i] + fh[i] - 2 * ans[i]);
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：Redshift_Shine (赞：0)

首先，注意到一个重要事实。取所有建筑的一个横截面，截面位置越低，切过的建筑就越多。这启发我们使用离线算法。

将所有建筑物的位置按照建筑物高度降序排序。按照该顺序遍历所有建筑物，并将其与之前所有遍历过的建筑物连通。由此，我们可以得到任意点对之间无代价连通的最高高度。那么如何利用这个信息呢？

这个时候要用到一个典得不能再典的算法——并查集上询问挂载。将所有的询问编号挂在各自的坐标上，每次连通两个连通块时检查是否有相同的询问编号存在。若存在，即更新答案。**合并时需要使用启发式合并，这很重要。若不使用，可能导致时间超限**。

时间复杂度 $O(HW\log HW+HW\alpha (HW)\log Q+Q)$。

```c++
// #define Redshift_Debug
// #define __GLIBCXX_DEBUG
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <chrono>
#else
#define debug(...)
#endif
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>
#include <tuple>
using namespace std;
const int N = 5e2 + 10, Q = 2e5 + 10;
int n, m, f[N * N], res[Q], a[N][N], idx, q;
set<int> st[N * N];
using t3i = tuple<int, int, int>;
bool act[N][N];
t3i ps[N * N];
const int dx[]{0, 1, 0, -1}, dy[]{1, 0, -1, 0};
struct str
{
	int a, b, y, c, d, z;
	void input()
	{
		scanf("%d%d%d%d%d%d", &a, &b, &y, &c, &d, &z);
	}
};
str qry[Q];
inline int find(int x)
{
	return x == f[x] ? x : f[x] = find(f[x]);
}
inline void merge(int x, int y, int z)
{
	x = find(x), y = find(y);
	if (x == y)
		return;
	if (st[x].size() < st[y].size())
		swap(x, y);
	for (auto &i : st[y])
	{
		if (st[x].count(i))
			st[x].erase(i), res[i] = z;
		else
			st[x].emplace(i);
	}
	f[y] = x;
	st[y].clear();
}
inline int rmp(int x, int y)
{
	return (x - 1) * m + y;
}
void run()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", a[i] + j);
			ps[++idx] = {-a[i][j], i, j};
			f[rmp(i, j)] = rmp(i, j);
		}
		// fprintf(stderr, "%d\n", i);
	}
	sort(ps + 1, ps + idx + 1);
	scanf("%d", &q);
	for (int i = 1; i <= q; i++)
	{
		qry[i].input();
		st[rmp(qry[i].a, qry[i].b)].emplace(i);
		st[rmp(qry[i].c, qry[i].d)].emplace(i);
	}
	for (int i = 1; i <= idx; i++)
	{
		auto &[va, x, y] = ps[i];
		va = -va;
		act[x][y] = true;
		for (int j = 0, nx, ny; j < 4; j++)
		{
			nx = x + dx[j], ny = y + dy[j];
			if (nx < 1 or nx > n or ny < 1 or ny > m or !act[nx][ny])
				continue;
			merge(rmp(x, y), rmp(nx, ny), va);
		}
	}
	for (int i = 1; i <= q; i++)
	{
		if (min(qry[i].y, qry[i].z) <= res[i] or (qry[i].a == qry[i].c and qry[i].b == qry[i].d))
		{
			printf("%d\n", abs(qry[i].y - qry[i].z));
			continue;
		}
		printf("%d\n", qry[i].y + qry[i].z - res[i] * 2);
	}
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	run();
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

## 作者：Judgelight (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc394_g)

---

考虑我们的走法一定是先下降到某一个楼层，然后一口气走过去，然后上升/下降到对应楼层。我们能够节约的部分只有一开始的下降过程，显然是下降得越少越好。所以我们的问题转化为找路径上的点的最大楼层最小值最大的路径，显然可以二分。二分之后转化为判定如果只能走最大楼层大于等于 $k$ 的格子是否可达。

所以我们直接整体二分，用可撤销并查集维护连通性，复杂度为 $O(n\log^2 n)$。

---

