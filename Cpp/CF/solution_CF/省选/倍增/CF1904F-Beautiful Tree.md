# Beautiful Tree

## 题目描述

Lunchbox 有一棵大小为 $n$ 的树，根节点为 $1$。每个节点都需要被赋予一个值。Lunchbox 认为这棵树是美丽的，当且仅当每个节点的值互不相同，且这些值恰好为 $1$ 到 $n$ 的一个排列。此外，一棵美丽的树还必须满足 $m$ 个关于以下两种类型的要求：

- “1 a b c” —— 在节点 $a$ 和 $b$ 之间的路径上，值最小的节点必须是 $c$。
- “2 a b c” —— 在节点 $a$ 和 $b$ 之间的路径上，值最大的节点必须是 $c$。

现在，你需要为每个节点分配一个值，使得最终的树是美丽的。如果无法做到，请输出 $-1$。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7 5
1 2
1 3
1 4
3 5
4 6
3 7
1 6 5 1
2 6 7 3
1 2 7 1
1 7 5 7
2 4 2 2```

### 输出

```
1 6 7 5 3 4 2```

## 样例 #2

### 输入

```
2 2
1 2
1 1 2 1
1 1 2 2```

### 输出

```
-1```

# 题解

## 作者：EasonLiang (赞：4)

**[CF1904F](https://www.luogu.com.cn/problem/CF1904F)**

> 给定一棵 $n$ 个点的树与 $m$ 个限制，每个限制形如 “点 $c$ 的权值在 $a$ 至 $b$ 的路径上最大/小”。试为每个点赋 $1 \sim n$ 中互不相同的权值，满足所有限制，或判断不存在。$n, m \le 2 \times 10^5$。

线段树优化建图。将每个限制转化为 “点 $c$ 大于/小于 $a$ 至 $b$ 的路径上除 $c$ 以外的所有点”的形式，树链剖分后，在线段树上将权值小的点向权值大的点连边。建好图后在新图上拓扑排序即可。**[AC Code](https://codeforces.com/contest/1904/submission/236607030)**

---

## 作者：EuphoricStar (赞：3)

大家好，我是这个。

![](https://z1.ax1x.com/2023/12/12/piWqMf1.png)

注意到可以树剖后线段树优化建图跑拓扑排序，但是空间复杂度 $O(n \log^2 n)$，大概过不了。

注意到我们只会有一个 $\text{dfn}$ 区间不是一条重链上一段前缀的形式（跨过 $\text{LCA}$ 的那个区间），于是对这个区间线段树优化建图，其他预处理重链后前缀优化建图，即可 $O(n \log n)$。

[code](https://codeforces.com/contest/1904/submission/236871354)

---

## 作者：sunkuangzheng (赞：3)

考虑这两条限制等价于，

- 对于 $u,v$ 路径上所有点 $d(d \ne c)$，有 $a_d > a_c$。

- 对于 $u,v$ 路径上所有点 $d(d \ne c)$，有 $a_d < a_c$。

那么不难想到如果 $a_d < a_c$ 就连一条 $d \to c$ 的边，然后拓扑排序定权值，有环显然无解。

但是边数是 $\mathcal O(n^2)$ 级别的，不能通过。发现连边都形如点到区间或者区间到点，那么线段树优化建图，开两个线段树一个维护点到区间的边，一个维护区间到点的边。在树上需要树剖一下。时间复杂度 $\mathcal O(n \log^2 n)$。

代码虽然比较长，但是还是很好调的。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 12.12.2023 09:34:48
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
using namespace std;
const int N = 5e5+5;
int t,n,u,v,fa[N],dep[N],siz[N],top[N],son[N],dfn[N],ff[N][23],tot,fd[N],ans[N],acnt,rc,m,k,c,d[N*8],rp[N*8];vector<int> g[N],gr[N*8];
void dfs1(int u,int f){
    fa[u] = f,siz[u] = 1,dep[u] = dep[f] + 1,ff[u][0] = f;
    for(int i = 1;i <= 22;i ++) ff[u][i] = ff[ff[u][i-1]][i-1];
    for(int v : g[u]) if(v != f) if(dfs1(v,u),siz[u] += siz[v],siz[v] > siz[son[u]]) son[u] = v;
}void dfs2(int u,int tp){
    top[u] = tp,dfn[u] = ++tot;if(son[u]) dfs2(son[u],tp);
    for(int v : g[u]) if(v != fa[u] && v != son[u]) dfs2(v,v);
}int kfa(int u,int k){
    for(int i = 22;i >= 0;i --) if(((k >> i) & 1)) u = ff[u][i];
    return u;
}int id(int s,int k){return s + k * 4 * n;}
void add(int u,int v){gr[u].push_back(v),d[v] ++;}
void build(int s,int l,int r){
    if(l == r) return fd[l] = s,rp[s] = l,add(id(s,0),id(s,1)),void();
    int mid = (l + r) / 2;build(s*2,l,mid),build(s*2+1,mid+1,r);
    add(id(s,0),id(s*2,0)),add(id(s,0),id(s*2+1,0)),add(id(s*2,1),id(s,1)),add(id(s*2+1,1),id(s,1));
}void upd(int s,int l,int r,int ql,int qr,int k,int op){
    if(ql <= l && r <= qr) return (!op ? add(k,id(s,0)) : add(id(s,1),k));
    int mid = (l + r) / 2;
    if(ql <= mid) upd(s*2,l,mid,ql,qr,k,op); if(qr > mid) upd(s*2+1,mid+1,r,ql,qr,k,op);
}void updd(int u,int v,int k,int op){
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u,v);
        upd(1,1,n,dfn[top[u]],dfn[u],k,op),u = fa[top[u]];
    }upd(1,1,n,min(dfn[u],dfn[v]),max(dfn[u],dfn[v]),k,op);
}bool ck(int u,int v){return dfn[v] >= dfn[u] && dfn[v] <= dfn[u] + siz[u] - 1;}
int lca(int u,int v){
    while(top[u] != top[v]) if(dep[top[u]] > dep[top[v]]) u = fa[top[u]]; else v = fa[top[v]];
    return (dep[u] < dep[v] ? u : v);
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> m;
    for(int i = 1;i < n;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);
    dfs1(1,0),dfs2(1,1),build(1,1,n);queue<int> q;
    while(m --){
        cin >> k >> u >> v >> c;
        if(ck(c,v)) swap(u,v);
        int d = lca(u,v),p = -1,q = -1;
        if(c != u) p = kfa(u,dep[u] - dep[c] - 1);
        if(c != d) q = fa[c];
        else if(c != v) q = kfa(v,dep[v] - dep[c] - 1);
        if(k == 1){
            if(p != -1) updd(u,p,id(fd[dfn[c]],1),0);
            if(q != -1) updd(q,v,id(fd[dfn[c]],1),0);
        }else{
            if(p != -1) updd(u,p,id(fd[dfn[c]],0),1);
            if(q != -1) updd(q,v,id(fd[dfn[c]],0),1);
        }
    }for(int i = 1;i <= n * 8;i ++) if(!d[i]) q.push(i);
    while(q.size()){
        int u = q.front();q.pop();
        if(rp[u]) ans[rp[u]] = ++acnt;
        for(int v : gr[u]) if(!(--d[v])) q.push(v);
    }for(int i = 1;i <= 8 * n;i ++) if(d[i]) rc = 1;
    if(rc) return cout << -1,0;
    for(int i = 1;i <= n;i ++) cout << ans[dfn[i]] << " ";
}
```

---

## 作者：未来姚班zyl (赞：3)

## 题目大意

给出一棵树，与 $m$ 条限制，每条限制为一条路径上点权最大/小的点的编号固定。

请你为图分配 $1\sim n$ 的点权使得满足所有限制。

## 题目分析

div.2 F 就考板板？

两个板子结合在一起的题。

一眼题，限制可以看成规定点点权大/于路径上的其它点，我们把 $a$ 的点权大于 $b$ 的点权的限制视作一个有向边，则有解当且仅当没有环，拓扑排序分配即可。

边数是 $O(n^2)$ 的，套个树剖线段树优化建边就可以做到 $O(n\log^2n)$。

$80$ 行整代码奉上。

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
const int N =2e5+5,M=2.5e6+5;
int n=read(),m=read(),h[N],to[N<<1],nxt[N<<1],cnt,dep[N],siz[N],dfn[N],Time,f[N],son[N],top[N],Id[N],id[M],idd[N],idu[N],rd[M],val[N];
inline void add_(int a,int b){
    to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,to[++cnt]=a,nxt[cnt]=h[b],h[b]=cnt;
}
inline void dfs(int x,int fa){
    f[x]=fa,dep[x]=dep[fa]+1,siz[x]=1;
    e(x)if(y^fa)dfs(y,x),siz[x]+=siz[y],son[x]=siz[y]>siz[son[x]]?y:son[x];
}
inline void Dfs(int x,int low){
    dfn[x]=++Time,Id[Time]=x,top[x]=low;
    if(son[x])Dfs(son[x],low);
    e(x)if(y^f[x]&&y^son[x])Dfs(y,y);
}
inline int ip(int x){
    return x+(n<<2);
}
vector<int>p[M];
inline void Add_(int x,int y){
    p[x].pb(y),rd[y]++;
}
inline void build(int x,int l,int r){
    if(l==r)return idd[Id[l]]=x,idu[Id[l]]=ip(x),id[x]=id[ip(x)]=Id[l],Add_(x,ip(x)),void();
    Add_(x,L),Add_(x,R),Add_(ip(L),ip(x)),Add_(ip(R),ip(x)),build(lc),build(rc);
}
inline void modify(int x,int l,int r,int Ll,int Rr,int fr,bool ty){
    if(Ll>Rr)return;
    if(OK)return ty?Add_(idu[fr],x):Add_(ip(x),idd[fr]),void();
    if(Ll<=mid&&Rr>=l)modify(lc,Ll,Rr,fr,ty);
    if(Ll<=r&&Rr>mid)modify(rc,Ll,Rr,fr,ty);
}
inline void sol(int l,int r,int ban,int fr,bool ty){
    if(ban>=l&&ban<=r)modify(Root,l,ban-1,fr,ty),modify(Root,ban+1,r,fr,ty);
    else modify(Root,l,r,fr,ty);
}
inline void lca(int x,int y,int z,bool ty){
    int ban=dfn[z];
    while(top[x]^top[y])dep[top[x]]>=dep[top[y]]?(sol(dfn[top[x]],dfn[x],ban,z,ty),x=f[top[x]]):(sol(dfn[top[y]],dfn[y],ban,z,ty),y=f[top[y]]);
    dep[x]<dep[y]?sol(dfn[x],dfn[y],ban,z,ty):sol(dfn[y],dfn[x],ban,z,ty);
}
inline void bfs(){
    int oo=0;
    queue<int>q;
    rep(i,1,n*8)if(!rd[i])q.push(i);
    while(!q.empty()){
        int x=q.front();q.pop();
        if(idd[id[x]]==x)val[id[x]]=++oo;
        E(x)if(!--rd[y])q.push(y);
    }
    if(oo!=n)cout <<-1,exit(0);
    repn(i)pf(val[i]),putchar(' ');
}
signed main(){ 
    rep(i,2,n)add_(read(),read());
    dfs(1,0),Dfs(1,1),build(Root);
    repm(i){
        int op=2-read(),x=read(),y=read(),z=read();
        lca(x,y,z,op);
    }
    bfs();
    return 0;
}
```


---

## 作者：Inui_Sana (赞：2)

感觉也是很 [well-known](https://www.luogu.com.cn/problem/P5344) 了吧。

对于要求 $a_x>a_y$ 这种，我们一般是考虑连 $x\to y$ 跑拓扑排序。但是这题要求一个点向一段区间或一段区间向一个点连边，怎么办？我们会优化建图。

由于是在树上，树剖+线段树优化建图常数可能偏大，考虑倍增（或称 ST 表）优化建图。由于上面的连边操作显然有可重复贡献性，每次对一条链 $(u,v)$ 连边或从一条链 $(u,v)$ 连出边，把这条链拆成 $(u,x),(y,v)$ 两个长为 $2^k$ 且并集为 $(u,v)$ 的链，找到 ST 表上对应点连边即可。

ST 表内部下传的连边是平凡的，但是这些边并没有 $x\to y$ 表示 $a_x>a_y$ 的意义，所以把这些边权设为 $0$，其他为 $1$。

连完之后跑一遍 tarjan 求出强连通分量，如果一个强连通分量内部有一条边权为 $1$ 的边，则一定无解，因为这样必然会得到形如 $a_x>a_x$ 的限制。

否则缩点跑拓扑排序。但是有一个优化时间（以及缩点时需要的额外空间）的小 trick，那就是缩点跑出来的强连通分量编号事实上是图的一个拓扑序的逆序，而我们事实上也只需要求拓扑序，所以每个点按照所在强连通分量编号，从小到大排序即可求出对应点权。

code：

```cpp
const int N=2e5+7,M=50*N,inf=0x3f3f3f3f,mod=0;
bool Mbe;
int n,m,cur,dep[N],siz[N],ans[N];
int fa[N][18],in[N][18],ot[N][18];
int idx,top,dfn[M],low[M],st[M];
int k,col[M];
bool vis[M];
pii a[N];
queue<int> q;
vector<int> E[N];
int tot,head[M];
struct node{
	int to,nxt;bool cw;
}e[M<<1];
il void add(int u,int v,int w=0){
	if(!u||!v){
		return;
	}
	e[++tot]={v,head[u],w},head[u]=tot;
}
void dfs(int u,int f){
	fa[u][0]=f,dep[u]=dep[f]+1;
	siz[u]=1,dfn[u]=++idx;
	in[u][0]=ot[u][0]=u;
	rep(i,1,17){
		fa[u][i]=fa[fa[u][i-1]][i-1];
		in[u][i]=++cur,ot[u][i]=++cur;
		add(in[u][i],in[u][i-1]);
		add(in[u][i],in[fa[u][i-1]][i-1]);
		add(ot[u][i-1],ot[u][i]);
		add(ot[fa[u][i-1]][i-1],ot[u][i]);
		if(!fa[u][i]){
			break;
		}
	}
	for(int v:E[u]){
		if(v==f){
			continue;
		}
		dfs(v,u),siz[u]+=siz[v];
	}
}
il int getLca(int u,int v){
	if(dep[u]<dep[v]){
		swap(u,v);
	}
	drep(i,17,0){
		if(dep[fa[u][i]]>=dep[v]){
			u=fa[u][i];
		}
	}
	if(u==v){
		return u;
	}
	drep(i,17,0){
		if(fa[u][i]!=fa[v][i]){
			u=fa[u][i],v=fa[v][i];
		}
	}
	return fa[u][0];
}
il int jump(int u,int k){
	drep(i,17,0){
		if((1<<i)<=k){
			k-=(1<<i);
			u=fa[u][i];
		}
	}
	return u;
}
il void updateIn(int u,int v,int x){
	int len=dep[u]-dep[v]+1,k=__lg(len);
	add(x,in[u][k],1),add(x,in[jump(u,len-(1<<k))][k],1);
}
il void updateOt(int u,int v,int x){
	int len=dep[u]-dep[v]+1,k=__lg(len);
	add(ot[u][k],x,1),add(ot[jump(u,len-(1<<k))][k],x,1);
}
il void solve(int op,int u,int v,int x){
	int w=getLca(u,v);
	if(op==1){
		updateOt(u,w,x);
		updateOt(v,w,x);
	}else{
		updateIn(u,w,x);
		updateIn(v,w,x);
	}
}
void tarjan(int u){
	dfn[u]=low[u]=++idx;
	st[++top]=u,vis[u]=1;
	go(i,u){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(vis[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		k++;
		do{
			int v=st[top];
			col[v]=k;
			vis[v]=0;
		}while(st[top--]!=u);
	}
}
void Yorushika(){
	scanf("%d%d",&n,&m),cur=n;
	rep(i,1,n-1){
		int u=read(),v=read();
		E[u].eb(v),E[v].eb(u);
	}
	dfs(1,0);
	rep(i,1,m){
		int op=read(),u=read(),v=read(),x=read();
		if(dfn[u]>=dfn[x]&&dfn[u]<dfn[x]+siz[x]){
			if(u!=x){
				solve(op,u,jump(u,dep[u]-dep[x]-1),x);
			}
		}else{
			solve(op,u,fa[x][0],x);
		}
		if(dfn[v]>=dfn[x]&&dfn[v]<dfn[x]+siz[x]){
			if(v!=x){
				solve(op,v,jump(v,dep[v]-dep[x]-1),x);
			}
		}else{
			solve(op,v,fa[x][0],x);
		}
	}
	mems(dfn,0),idx=0;
	rep(i,1,cur){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	rep(u,1,cur){
		go(i,u){
			int v=e[i].to;
			if(col[u]==col[v]){
				if(e[i].cw){
					puts("-1");
					return;
				}
			}
		}
	}
	rep(i,1,n){
		a[i]=Mp(col[i],i);
	}
	sort(a+1,a+n+1);
	rep(i,1,n){
		ans[a[i].se]=i;
	}
	rep(i,1,n){
		printf("%d ",ans[i]);
	}
}
bool Med;
signed main(){
	cerr<<(&Mbe-&Med)/1048576.0<<'\n';
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

注意开够空间！

---

## 作者：ケロシ (赞：1)

考虑拓扑排序，$u \to v$ 连边表示 $u < v$。

那么对于第一种操作，只要将 $c$ 向 $a$ 到 $b$ 路径上的除了 $c$ 的所有点连边即可，反之亦然。

使用倍增优化建图，时间空间复杂度 $O(n \log n)$。

```cpp
const int N = 2e5 + 5;
const int M = 2e7 + 5;
int n, m;
vector<int> e[N];
int d[N], f[N][20], F[N][20], G[N][20], tot;
int ru[M], fi[M], ne[M], to[M], ecnt;
int ans[N];
void add(int u, int v) {
	ne[++ ecnt] = fi[u];
	to[ecnt] = v;
	fi[u] = ecnt;
	ru[v] ++;
}
void dfs(int u, int fa) {
	FOR(i, 1, 19) {
		int v = f[u][i - 1];
		f[u][i] = f[v][i - 1];
		if(f[u][i]) {
			F[u][i] = ++ tot;
			add(tot, F[u][i - 1]);
			add(tot, F[v][i - 1]);
			G[u][i] = ++ tot;
			add(G[u][i - 1], tot);
			add(G[v][i - 1], tot);
		}
	}
	for(int v : e[u]) {
		if(v == fa) continue;
		d[v] = d[u] + 1;
		f[v][0] = u;
		F[v][0] = G[v][0] = v;
		dfs(v, u);
	}
}
int lca(int u, int v) {
	if(d[u] < d[v]) swap(u, v);
	ROF(i, 19, 0) if(d[f[u][i]] >= d[v])
		u = f[u][i];
	if(u == v) return u;
	ROF(i, 19, 0) if(f[u][i] != f[v][i])
		u = f[u][i], v = f[v][i];
	return f[u][0];
}
int get(int u, int v) {
	ROF(i, 19, 0) if(d[f[u][i]] > d[v])
		u = f[u][i];
	if(f[u][0] == v) return u;
	else return f[v][0];
}
void link(int u, int v, int x, int o) {
	ROF(i, 19, 0) if(d[f[u][i]] >= d[v]) {
		if(o == 1) add(x, F[u][i]);
		else add(G[u][i], x);
		u = f[u][i];
	}
}
void links(int u, int v, int x, int o) {
	int mid = lca(u, v);
	link(u, mid, x, o);
	link(v, mid, x, o);
	if(o == 1) add(x, mid);
	else add(mid, x);
}
void solve() {
	cin >> n >> m;
	REP(_, n - 1) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	d[1] = 1; tot = n;
	dfs(1, 0);
	REP(_, m) {
		int o, l, r, u;
		cin >> o >> l >> r >> u;
		if(l != u) links(l, get(l, u), u, o);
		if(r != u) links(r, get(r, u), u, o);
	}
	int cnt = 0;
	vector<int> q;
	FOR(i, 1, tot) if(! ru[i]) q.push_back(i);
	while(! q.empty()) {
		int u = q.back(); q.pop_back();
		if(u <= n) ans[u] = ++ cnt;
		for(int i = fi[u]; i; i = ne[i]) {
			int v = to[i];
			ru[v] --;
			if(! ru[v]) q.push_back(v);
		}
	}
	if(cnt < n) {
		cout << - 1 << endl;
		return;
	}
	FOR(i, 1, n) cout << ans[i] << " ";
	cout << endl;
}
```

---

## 作者：xyz105 (赞：1)

$$\begin{Bmatrix}\color{red}\LARGE\bold{Solution}\\\normalsize\texttt{No.011 }\bold{CF1904F}\end{Bmatrix}\times\footnotesize\texttt{ By Xyz105}$$

这里是 **倍增优化建图** 的题解。

在写这篇题解前，发现题解区大多是 树剖+线段树优化建图 的做法，而个别 倍增优化建图 的做法甚至用到了 Tarjan。相比之下本人觉得补一篇 建图后**纯拓扑**做法 是有必要的。


### 题目描述

给定一棵 $n$ 个点的树，要求给每个节点各赋一个权值。你给出的权值应满足 $m$ 个限制。限制有两种形式：
- `1 a b c`——节点 $a$ 和 $b$ 之间的简单路径中，权值**最小**的节点必须在 $c$ 节点处。
- `2 a b c`——节点 $a$ 和 $b$ 之间的简单路径中，权值**最大**的节点必须在 $c$ 节点处。

$2\le n, m\le 2\times 10^5$。


### 解题思路

考虑最暴力的想法。在这些节点中互相连若干条有向边，并规定：**若存在从 $a$ 连向 $b$ 的边，则必有 $(a$ 的权值 $)<$ $(b$ 的权值 $)$**。  
于是所有 `1 a b c` 的操作，皆被转化为 $c$ 点向 $a\sim b$ 的路径中除 $c$ 外其它点连边（**单点**连**多点**）；所有 `2 a b c` 的操作，皆被转化为 $a\sim b$ 的路径中除 $c$ 外其它点 向 $c$ 点连边（**多点**连**单点**）。  
正确性显然，但复杂度错掉是肯定的。

考虑在树上 **倍增优化建图**。  
先考虑**单点**连**多点**的情况。令编号为 $num_{u, i}$ 的**虚点**代表 $fa_{u,0}\sim fa_{u,i}$ 这条路径上的所有点（其中 $fa_{u,i}$ 表示点 $u$ 的 $2^i$ 级祖先），那么“单点连向 $O(n)$ 个点”就转化成“单点连向 $O(\log n)$ 个虚点”的操作，具体实现方式为与树上倍增同时进行：
```cpp
inline void link(int u, int v, int c) // 点 c 连向 u~v 路径上的所有点（不包括点 v），保证 v 是 u 的祖先.
{
	if (dep[u] > dep[v]) add_edge(c, u);
	for (int i = 19 - 1; i >= 0; i--)
		if (dep[fa[u][i]] > dep[v])
			add_edge(c, num[u][i]), u = fa[u][i];
}
```
在关于虚点的具体建图过程中只需要求 $num_{u,0}=fa_{u,0}$，加入所有有向边 $(num_{u,i}\to num_{u,i-1}),(num_{u,i}\to num_{fa_{u,i-1},i-1})\ (i>0)$ 即可。  
对于**多点**连**单点**的情况，容易想到可以反着建图。


### 参考代码

[Submission on Codeforces](https://codeforces.com/contest/1904/submission/284005884)。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <deque>
using namespace std;

const int MAXN = 2e5 + 10, MAXM = MAXN * 100;

int n, m;

int head2[MAXN], to2[MAXN << 1], nxt2[MAXN << 1], cnt2 = 0;
inline void add_edge2(int u, int v)
	{if (u && v && u != v) to2[++cnt2] = v, nxt2[cnt2] = head2[u], head2[u] = cnt2;}

int head[MAXM], in_deg[MAXM], to[MAXM], nxt[MAXM], cnt = 0;
inline void add_edge(int u, int v)
	{if (u && v && u != v) in_deg[v]++, to[++cnt] = v, nxt[cnt] = head[u], head[u] = cnt;}

int fa[MAXN][19], num1[MAXN][19], num2[MAXN][19], num_cnt = 0, dep[MAXN];

inline void dfs(int u, int f)
{
	fa[u][0] = f, num1[u][0] = num2[u][0] = f;
	for (int i = 1; i < 19; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1]; if (!fa[u][i]) continue;
		num1[u][i] = ++num_cnt, num2[u][i] = ++num_cnt,
		add_edge(num1[u][i], num1[u][i - 1]), add_edge(num1[u][i], num1[fa[u][i - 1]][i - 1]),
		add_edge(num2[u][i - 1], num2[u][i]), add_edge(num2[fa[u][i - 1]][i - 1], num2[u][i]);
	}
	for (int i = head2[u]; i; i = nxt2[i])
		if (to2[i] != f) dep[to2[i]] = dep[u] + 1, dfs(to2[i], u);
}


inline int lca(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	if (dep[u] > dep[v])
	{
		for (int i = 19 - 1; i >= 0; i--)
			if (dep[fa[u][i]] > dep[v]) u = fa[u][i];
		u = fa[u][0];
	}
	if (u != v)
	{
		for (int i = 19 - 1; i >= 0; i--)
			if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
		u = fa[u][0], v = fa[v][0];
	}
	return u;
}

// link1: c to [a,b]; link2: [a,b] to c.

inline void link1_1(int u, int v, int c) // c to [u,v).
{
	if (dep[u] > dep[v]) add_edge(c, u);
	for (int i = 19 - 1; i >= 0; i--)
		if (dep[fa[u][i]] > dep[v])
			add_edge(c, num1[u][i]), u = fa[u][i];
}

inline void link1(int u, int v, int c)
{
	int uv = lca(u, v);
	if (uv == c) {link1_1(u, uv, c), link1_1(v, uv, c); return;}
	if (lca(u, c) == c) link1_1(u, c, c), link1_1(fa[c][0], uv, c), link1_1(v, fa[uv][0], c);
	else link1_1(v, c, c), link1_1(fa[c][0], uv, c), link1_1(u, fa[uv][0], c);
}

inline void link2_1(int u, int v, int c) // [u,v) to c.
{
	if (dep[u] > dep[v]) add_edge(u, c);
	for (int i = 19 - 1; i >= 0; i--)
		if (dep[fa[u][i]] > dep[v])
			add_edge(num2[u][i], c), u = fa[u][i];
}

inline void link2(int u, int v, int c)
{
	int uv = lca(u, v);
	if (uv == c) {link2_1(u, uv, c), link2_1(v, uv, c); return;}
	if (lca(u, c) == c) link2_1(u, c, c), link2_1(fa[c][0], fa[uv][0], c), link2_1(v, fa[uv][0], c);
	else link2_1(v, c, c), link2_1(fa[c][0], fa[uv][0], c), link2_1(u, fa[uv][0], c);
}

deque<int> qu;

int ans[MAXN], ans_cnt = 0;

int main()
{
	scanf("%d%d", &n, &m), num_cnt = n;
	for (int i = 1, i1, i2; i < n; i++)
		scanf("%d%d", &i1, &i2), add_edge2(i1, i2), add_edge2(i2, i1);
	dep[1] = 1, dfs(1, 0);
	
	int t, a, b, c;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d%d", &t, &a, &b, &c);
		if (t == 1) link1(a, b, c); else link2(a, b, c);
	}
	
	for (int i = 1; i <= num_cnt; i++) if (!in_deg[i]) qu.push_back(i);
	int mark = 0;
	while (qu.size())
	{
		int u = qu.front(); qu.pop_front(), mark++;
		if (u <= n) ans[u] = ++ans_cnt;
		for (int i = head[u]; i; i = nxt[i])
			if (--in_deg[to[i]] == 0) qu.push_back(to[i]);
	}
	if (mark < num_cnt) cout << -1;
	else
		for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	
	return 0;
}
```

---

## 作者：tongzhenxuan (赞：1)

VP时做到的一道题。

看到这种大小关系的题目，一个很自然的想法就是把大小关系看成 **有向边**，因为这样我们可以很轻松的把不等关系的传递性转化为图上的可达性，那么我们基于这个假设就可以很好的推出，只要最后满足大小关系的图无环即可，即有向无环图，然后按拓扑序进行标定大小。

看到这种树上路径的题目，一个很自然的想法是用 **树剖** 工具把他转化为序列问题，这样路径就变成了一段连续的区间。

看到这种又有连续区间又要建边的题目，一个很自然的想法是用我们的 **线段树优化建边**，（当然在我们使用树剖的时候可能联想到线段树）。

那么问题就非常简单了。

实现细节注意：

1.	我们可以建两颗线段树分别对应大于小于两种操作

2.	我们可以在树剖的过程中把自己这个点给抠掉。

3.	由于我们用了线段树，所以要格外注意空间范围，如果您在 CF 连续把好多个有解情况判成无解，那么可以关注您的数据范围。

[Submission](https://codeforces.com/contest/1904/submission/237110951)

总的来说感觉比较板子，但是听说有更优美的倍增做法，这里因为树剖的想法过于自然，所以写了一篇树剖题解。

---

## 作者：蒟蒻君HJT (赞：0)

设点权 $v_x$。

转化一下条件，将 $a$ 到 $b$ 路径上 $c$ 两端的路径拆开来，本质是要求树上某两段路径的所有点权都小于 $v_c$ 或都大于 $v_c$。

朴素想法是对于 $v_p>v_q$ 的限制，连一条 $p\rightarrow q$ 的有向边，拓扑排序判断是否存在环即可。存在环必无解，否则根据拓扑序逆着构造一定符合要求。

想到数据结构优化建图。一段路径可以拆为树上“竖直”（即从浅到深）的两段。由于可重复贡献性，长度为 $l$ 的竖直路径可以再拆成两段长度为 $2^{\lfloor \log_2 l\rfloor}$ 的竖直路径。可以用 ST 表优化建图，类似树上倍增求 LCA。这样边数的上界是两个 ST 表的 $2n\log n+8m$ 条边，之后就可以跑线性的拓扑排序了。

---

## 作者：happybob (赞：0)

先考虑序列怎么做？由于原点权是排列，考了依次插入 $1\sim n$，每个限制 $(l,r,x)$ 形如区间 $[l,x) \cup (x,r]$ 的每个点都要在 $x$ 前或后插入。考虑线段树优化建图，存在答案当且仅当图是 DAG，构造可以考虑拓扑序。 

树上问题也很显然，使用树剖维护线段树优化建图即可。

---

