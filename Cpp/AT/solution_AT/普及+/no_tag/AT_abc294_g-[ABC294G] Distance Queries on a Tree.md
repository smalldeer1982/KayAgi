# [ABC294G] Distance Queries on a Tree

## 题目描述

给定一颗有 $n$ 个节点的树，带边权，要进行 $Q$ 次操作，操作有两种：

`1 i w`：将第 $i$ 条边的边权改为 $w$。  
`2 u v`：询问 $u,v$ 两点的距离。

## 说明/提示

$1\le n,Q\le 2\times10^5，1\le w_i\le 10^9$

## 样例 #1

### 输入

```
5
1 2 3
1 3 6
1 4 9
4 5 10
4
2 2 3
2 1 5
1 3 1
2 1 5```

### 输出

```
9
19
11```

## 样例 #2

### 输入

```
7
1 2 1000000000
2 3 1000000000
3 4 1000000000
4 5 1000000000
5 6 1000000000
6 7 1000000000
3
2 1 6
1 1 294967296
2 1 6```

### 输出

```
5000000000
4294967296```

## 样例 #3

### 输入

```
1
1
2 1 1```

### 输出

```
0```

## 样例 #4

### 输入

```
8
1 2 105
1 3 103
2 4 105
2 5 100
5 6 101
3 7 106
3 8 100
18
2 2 8
2 3 6
1 4 108
2 3 4
2 3 5
2 5 5
2 3 1
2 4 3
1 1 107
2 3 1
2 7 6
2 3 8
2 1 5
2 7 6
2 4 7
2 1 7
2 5 3
2 8 6```

### 输出

```
308
409
313
316
0
103
313
103
525
100
215
525
421
209
318
519```

# 题解

## 作者：rui_er (赞：6)

DFS 序树状数组。

不妨以 $1$ 为根，设 $\operatorname{dep}(u)$ 表示 $u$ 到根路径的边权和，$\operatorname{dis}(u,v)$ 表示 $u,v$ 间路径的边权和，$\operatorname{LCA}(u,v)$ 表示 $u,v$ 的最近公共祖先。则显然有：$\operatorname{dis}(u,v)=\operatorname{dep}(u)+\operatorname{dep}(v)-2\times\operatorname{dep}(\operatorname{LCA}(u,v))$。只需要维护每个点的 $\operatorname{dep}$。

给一条边重新赋权值等价于给它的边权加上 $\Delta w$，这一操作会导致这条边的子节点所在子树内每个点的 $\operatorname{dep}$ 增加 $\Delta w$。使用 DFS 序即可将子树转化为区间，区间加、单点查只需要差分后树状数组维护即可。

时间复杂度 $\mathcal O((n+q)\log n)$。

```cpp
// Problem: G - Distance Queries on a Tree
// Contest: AtCoder - AtCoder Beginner Contest 294
// URL: https://atcoder.jp/contests/abc294/tasks/abc294_g
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
ll randint(ll L, ll R) {
	uniform_int_distribution<ll> dist(L, R);
	return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const ll N = 2e5+5;

ll n, m, fa[N][19], dis[N], sz[N], bottom[N], dfn[N], tms, val[N];
vector<tuple<ll, ll, ll>> e[N];

struct BIT {
	ll c[N];
	ll lowbit(ll x) {return x & (-x);}
	void add(ll x, ll k) {for(; x <= n; x += lowbit(x)) c[x] += k;}
	ll ask(ll x) {ll k = 0; for(; x; x -= lowbit(x)) k += c[x]; return k;}
}bit;

void dfs(ll u, ll f) {
	fa[u][0] = f;
	rep(i, 1, 18) fa[u][i] = fa[fa[u][i-1]][i-1];
	dis[u] = dis[f] + 1;
	dfn[u] = ++tms;
	sz[u] = 1;
	for(auto i : e[u]) {
		ll v, w, id;
		tie(v, w, id) = i;
		if(v != f) {
			dfs(v, u);
			sz[u] += sz[v];
			bottom[id] = v;
			bit.add(dfn[v], w);
			bit.add(dfn[v]+sz[v], -w);
		}
	}
}

ll LCA(ll u, ll v) {
	if(dis[u] < dis[v]) swap(u, v);
	per(i, 18, 0) if(dis[fa[u][i]] >= dis[v]) u = fa[u][i];
	if(u == v) return u;
	per(i, 18, 0) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

int main() {
	scanf("%lld", &n);
	rep(i, 1, n-1) {
		ll u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		e[u].emplace_back(v, w, i);
		e[v].emplace_back(u, w, i);
		val[i] = w;
	}
	dfs(1, 0);
	for(scanf("%lld", &m); m; m--) {
		ll op, u, v;
		scanf("%lld%lld%lld", &op, &u, &v);
		if(op == 1) {
			ll bot = bottom[u];
			bit.add(dfn[bot], v-val[u]);
			bit.add(dfn[bot]+sz[bot], val[u]-v);
			val[u] = v;
		}
		else {
			ll lca = LCA(u, v);
			printf("%lld\n", bit.ask(dfn[u])+bit.ask(dfn[v])-2*bit.ask(dfn[lca]));
		}
	}
	return 0;
}
```

---

## 作者：Pengzt (赞：6)

[ABC294G](https://www.luogu.com.cn/problem/AT_abc294_g)

即给定一棵树，要求支持子树加和查询 $u, v$ 间的路径。

可以维护 $\texttt{dfs}$ 序，这样就变成了序列上的区间加。

每次求出 LCA 后，查询 $d_{dfn_u}, d_{dfn_v}, d_{dfn_{lca}}$ 即可，$d$ 是当前 $\texttt{dfs}$ 序所表示的点的深度，使用线段树维护即可。

于是只需要线段树和求 LCA 即可，我用的倍增 LCA。

时间复杂度：$\mathcal{O}({n\log n+q\log n)}$

[评测记录](https://www.luogu.com.cn/record/105362383)

鲜花：应该只有我写了 3k，想知道怎么做到 $60$ 行还不压的。

---

## 作者：CQ_Bab (赞：5)

# 思路
首先这道题是树链剖分啊。

首先了解一下什么叫 dfs 序，其实就是对于一棵树然后用 dfs 去遍历它按顺序走到的点连起来就位 dfs 序，然后我们还要知道一些东西。

$1$ 重儿子：就是对于一个节点的所有儿子中大小（就是以它为根节点的总个数最多）最大的那个。

$2$ 轻儿子：既除了重儿子以外的所有节点（根节点也是）。

$3$ 重链：从一个轻儿子开始一路沿着重儿子走，走出的那条链。

$4$ 轻链：除了重链以外的所有链。

$5.$ 时间戳：第一次遍历到这个点的时间（从 $1$ 开始计）。

然后我们将剖分和 dfs 序结合一下（先往重儿子走）然后在标出时间戳那么就能发现一条重链上的时间戳都是连续的。那么我们如果都不知道重儿子是谁那么怎么求出时间戳所以我们要两遍 dfs 第一遍求出重儿子第二遍求出时间戳。

## 第一遍dfs代码
```
void dfs1(int x,int father){
	fa[x]=father;
	dep[x]=dep[father]+1; 
	siz[x]=1;//初始化 
	int zhongson=-1; //记录重儿子 
	for(int i=h[x];~i;i=edg[i].y){
		int to=edg[i].x;
		if(to==father) continue;
		dfs(to,x);
		siz[x]+=siz[to];//更新总个数 
		if(siz[to]>zhongson){//求出x的重儿子 
			zhongson=siz[to];//记录用于比较 
			bigson[x]=to;//直接标记若后面有会直接覆盖 
		}
	}
}
```

## 第二遍dfs代码
```
void dfs2(int x,int head){
	dfn[x]=++cnt;//添加时间戳
	top[x]=head; 
	w[cnt]=v[x];//当前节点权值 
	if(!bigson[x]) return;
	dfs2(bigson[x],head);
	for(int i=h[x];~i;i=edg[i].y) {
		int to=edg[i].x;
		if(to==fa[x]||to==bigson[x]) continue;
		dfs(to,to);//to为开头了 
	}
}
```
这里我们有一个引理：除根节点以外的任何一个节点的父亲都一定在一条重链上，我们还是将头深度大的先往上面跳，这样是一定最快的，相当于就是和求最近公共祖先差不多，就是先让一条重链的头的深度较大的往上跳，然后就可以把要跳的那一条链都修改一下然后在最后那两个数一定在一条链上然后就可以去修改了。

## 求答案代码
```
int qmax(int x,int y) {
	int res=0;
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res+=qq(1,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	return res+qq(1,dfn[x]+1,dfn[y]);//边权转换成点权
}
```
然后总代吗就是这样
# 代码

```
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define ls u<<1
#define rs u<<1|1
const int N=1e6+10;
int n,head[N],cnt,m;
int a,b,tot,v[N],w[N];
int nx[N],pr[N];
int dfn[N],fa[N],son[N],top[N],siz[N],dep[N];
struct node {
	int x,y,z,l,r,maxn;
} tr[N],edg[N];
void add(int x,int y,int z) {//存边 
	edg[++tot]= {y,head[x],z};
	pr[tot]=x,nx[tot]=y;
	head[x]=tot;
}
void pushup(int u) {//线段树模板 
	tr[u].maxn=tr[u<<1].maxn+tr[u<<1|1].maxn;
}
void build(int u,int l,int r) {//线段树模板 
	tr[u]= {0,0,0,l,r};
	if(l==r) {
		tr[u].maxn=w[l];
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	pushup(u);
}
void modify(int u,int l,int r,int k) {//线段树模板 
	if(tr[u].l==tr[u].r) {
		tr[u].maxn=k;
		return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify(u<<1,l,r,k);
	else modify(u<<1|1,l,r,k);
	pushup(u);
}
int qq(int u,int l,int r) { //线段树模板 
	if(tr[u].l>=l&&tr[u].r<=r) {
		return tr[u].maxn;
	}
	int mid=tr[u].l+tr[u].r>>1,res=0;
	if(l<=mid) res=qq(ls,l,r);
	if(r>mid) res+=qq(rs,l,r);
	return res;
}
void dfs1(int x,int f) {//重儿子和深度还有大小 
	fa[x]=f;
	dep[x]=dep[f]+1;
	siz[x]=1;
	int big=0;
	for(int i=head[x]; i; i=edg[i].y) {
		int j=edg[i].x;
		if(j==f) continue;
		dfs1(j,x);
		v[j]=edg[i].z;
		siz[x]+=siz[j];
		if(siz[j]>big) {
			big=siz[j];
			son[x]=j;
		}
	}
}
void dfs2(int x,int t) {//求出时间戳 
	dfn[x]=++cnt;
	w[cnt]=v[x];
	top[x]=t;
	if(!son[x]) return;
	dfs2(son[x],t);
	for(int i=head[x]; i; i=edg[i].y) {
		int j=edg[i].x;
		if(j==fa[x]||j==son[x]) continue;
		dfs2(j,j);
	}
}
int qmax(int x,int y) {
	int res=0;
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res+=qq(1,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	return res+qq(1,dfn[x]+1,dfn[y]);
}
fire main() {
	cin>>n;
	rep(i,1,n-1) {
		int c;
		cin>>a>>b>>c;
		add(a,b,c);
		add(b,a,c);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	cin>>m;
	while(m--) {
		int op;
		int u,v;
		cin>>op;
		cin>>u>>v;
		if(op==1) {
			u<<=1;
			u--;
			if(dep[pr[u]]>dep[nx[u]]) u=pr[u]; //转换 
			else u=nx[u];
			modify(1,dfn[u],dfn[u],v);
		}else {
			cout<<qmax(u,v)<<endl;
		}
	}
	return false;
}
```

---

## 作者：dayz_break404 (赞：4)

~~终于有能写的 G 题了~~（喜

安利下自己的博客：[这里](https://www.luogu.com.cn/blog/lmzz/atabc294g-abc294g-distance-queries-on-a-tree-ti-xie)

## 题目描述

给定一颗有 $ n $ 个节点的树，带边权，要进行 $ Q $ 次操作，操作有两种：

```1 i w ```：将第 $ i $ 条边的边权改为 $ w $。

```2 u v```：询问 $ u,v $ 两点的距离。

## 题目分析

多么简洁的题面，~~爱上出题风格~~。

很典的一道题。

树上询问区间带修，树剖板子。

先用链式前向星存树，再用树剖解决更新查询问题。

另外注意边权转点权细节，树剖 + 线段树。

数组意义：
- top 数组表示重链的顶部节点。
- dep 数组表示节点深度。
- size 数组表示重链大小。
- fa 数组表示节点父亲。
- son 数组表示节点的重儿子。
- id 数组表示节点线段树中的编号。
- vl 数组表示以节点为结尾的边的边权。（这里就是边权点权啦
- w 点权在线段树中的数组。


单点修改甚至不用 lazy_tag，只是调代码~~有点~~崩溃。。。

不会请右转：[线段树板子](https://www.luogu.com.cn/problem/P3372) [树剖板子](https://www.luogu.com.cn/problem/P3384) [边权转点权](https://www.luogu.com.cn/blog/ShadderLeave/solution-p3038)

## Code

于是乎，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define maxn 200020
struct node1{
	ll val,to,next,first;
}e[maxn<<1];
ll n,head[maxn],cnt;
inline void add(ll u,ll v,ll x){//链式前向星 
	e[++cnt].to=v;
	e[cnt].next=head[u];
	e[cnt].val=x;
	e[cnt].first=u;
	head[u]=cnt;
}
//树剖部分 
ll top[maxn],dep[maxn],fa[maxn],Size[maxn],son[maxn],id[maxn],w[maxn],vl[maxn],idx;
void dfs1(ll u,ll f){
	Size[u]=1;
	son[u]=0;
	for(int i=head[u];i;i=e[i].next){
		ll v=e[i].to;
		if(v==f) continue;
		dep[v]=dep[u]+1;
		fa[v]=u;
		vl[v]=e[i].val;
		dfs1(v,u);
		Size[u]+=Size[v];
		if(Size[son[u]]<Size[v]) son[u]=v;
	}
}
void dfs2(ll u,ll f){
	id[u]=++idx;
	w[idx]=vl[u];
	top[u]=f;
	if(son[u]) dfs2(son[u],f);
	for(int i=head[u];i;i=e[i].next){
		ll v=e[i].to;
		if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
	}
}
//线段树部分 
ll tree[maxn<<2];
inline ll ls(ll x){
	return x<<1;
}
inline ll rs(ll x){
	return x<<1|1;
}
inline void push_up(ll p){//上传 
	tree[p]=tree[ls(p)]+tree[rs(p)];
} 
void build(ll p,ll l,ll r){//建树 
	if(l==r){
		tree[p]=w[l];
		return ;
	}
	ll mid=(l+r)>>1;
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	push_up(p);
}
void update(ll p,ll l,ll r,ll x,ll k){//单点修改 
	if(l==r){
		tree[p]=k;
		return ;
	}
	ll mid=(l+r)>>1;
	if(mid>=x) update(ls(p),l,mid,x,k);
	else update(rs(p),mid+1,r,x,k);
	push_up(p);
}
ll query(ll p,ll l,ll r,ll x,ll y){//查询 
	ll res=0;
	if(x<=l&&y>=r){
		return tree[p];
	}
	ll mid=(l+r)>>1;
	if(mid>=x) res+=query(ls(p),l,mid,x,y);
	if(y>mid) res+=query(rs(p),mid+1,r,x,y);
	return res;
}
void modify(ll j,ll k){//树剖对应的修改操作
	j<<=1;
	ll u=e[j].first,v=e[j].to;
	if(dep[u]<dep[v]) swap(u,v);
	update(1,1,n,id[u],k);
}
ll ask(ll u,ll v){//树剖对应的查询要求
	ll res=0;
	if(u==v) return 0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		res+=query(1,1,n,id[top[u]],id[u]);
		u=fa[top[u]];
	}
	if(dep[v]<dep[u]) swap(u,v);
	res+=query(1,1,n,id[u]+1,id[v]);
	return res;
}
int main(){
	scanf("%lld",&n); 
	ll a,b,c;
	for(int i=1;i<n;i++){
		scanf("%lld%lld%lld",&a,&b,&c);
		add(a,b,c);
		add(b,a,c);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	ll q,op;
	scanf("%lld",&q);
	while(q--){
		scanf("%lld%lld%lld",&op,&a,&b);
		if(op==1) modify(a,b); 
		else{
			printf("%lld\n",ask(a,b));
		}
	}
	return 0;
}
```
[AC code](https://www.luogu.com.cn/record/108295986)

###### ~~一些废话~~

蒟蒻的第一篇题解，大佬勿喷。若题解有问题，感谢各位神犇指导。~~管理员大大求通过啊qwq~~

~~最后不要脸求关注qwq.~~

---

## 作者：Crane_w (赞：4)

###  G
首先考虑这张图的 EulerTour,简单点说，就是 dfs 一遍，把每个点入栈出栈顺序存起来，举个例子：
```
2
1 2
2 3 
```


这棵树的 Euler Tour 就是 `1 2 3 3 2 1`。

相当于把树拍成序列，之后在上面记录每个点到根的距离。

操作一  改变某条边权值为 $w$ 相当于把这条边上入栈顺序**相对靠后**的点（son）的值改为 $w$，这个操作可以用树状数组/线段树维护。

操作二 统计答案 树上节点 $u \ v$  的距离： $\operatorname{dis}(u, v) =\operatorname{dis}(1, u) + \operatorname{dis}(1, v) - 2 \times \operatorname{dis}(1, lca(u, v))$

所以找出 $u\ v $  的 lca 统计即可。

$Code$ 

```cpp
vector<int> G[maxn];
//LCA 
int p[maxn][21];
int dep[maxn];
int in[maxn], out[maxn];
int T = 0;
void dfs(int u, int fa, int depth) {
    dep[u] = depth; p[u][0] = fa;
    in[u] = ++T;
    for (int i = 1; i <= 20; i++) p[u][i] = p[p[u][i - 1]][i - 1];
    for (int i = 0; i < G[u].size(); i++) if (G[u][i] != fa) dfs(G[u][i], u, depth + 1);
    out[u] = ++T;
}
int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 20; i >= 0; i--) if(dep[p[x][i]] >= dep[y]) x = p[x][i];
    if (x == y) return x;
    for (int i = 20; i >= 0; i--) if (p[x][i] != p[y][i]) x = p[x][i], y = p[y][i];
    return p[x][0];
}
int lf[maxn], rf[maxn];
int c[maxn], we[maxn];
void add(int x, int y) {
    for (int i = x; i <= T; i += i & (-i)) {
        c[i] += y; 
    }
    return;
}
int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= i &-i) {
        res += c[i];
    }
    return res;
}
signed main() {
    cin >> n;
    rep_(i, 1, n - 1) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].pb(v);
        G[v].pb(u);
        lf[i] = u, rf[i] = v, we[i] = w;
    }
    dfs(1, 0, 1);
    for (int i = 1; i <= n - 1; i++) {
        if (in[lf[i]] > in[rf[i]]) swap(lf[i], rf[i]);
        add(in[rf[i]], we[i]);
        add(out[rf[i]], -we[i]);    
    }
    int q; 
    cin >> q;
    rep_(i, 1, q) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 1) {
            add(in[rf[x]], -we[x] + y);
            add(out[rf[x]], we[x] - y);
            we[x] = y;
        } else {
            cout << sum(in[x]) + sum(in[y]) - 2 * sum(in[LCA(x, y)]) << endl;
        }
    }
```


---

## 作者：bloodstalk (赞：4)

## Description
有一个节点数为 $N$ 的树。边 $i$ 连接 $u_i$ 和 $v_i$，边的权值为 $w_i$。

$Q$ 次询问，询问一共有两种。

```1 i w``` ：改变第 $i$ 条边的权值为 $w$。

```2 u v``` ：输出 $u$ 到 $v$ 的路径距离。

数据范围：

$1 \leq N \leq 2 \times 10^5$

$1 \leq u_i,v_i \leq N$

$1 \leq w_i \leq 10^9$

$1 \leq Q \leq 2 \times 10^5$

## Solution
经典树剖。如果不会树剖，移步[模板题](https://www.luogu.com.cn/problem/P3384)，还有[边权转点权trick](https://www.luogu.com.cn/blog/ShadderLeave/solution-p3038)。

学完树剖后，这个题其实就一眼了。这个题更改权值时只更新一条边，不需要懒标记，给个数组存储一下第 $i$ 条边的 $u_i,v_i$，暴力修改即可。

求路径距离的时候注意一下 LCA 处的权值不属于路径，要减去。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define next nxt
#define re register
#define il inline
const int N = 2e5 + 5;
const int M = 2e5 + 5;	
using namespace std;
int max(int x,int y){return x > y ? x : y;}
int min(int x,int y){return x < y ? x : y;}

struct node{
	int u,v,w,next;
}edge[M<<1],e[M<<1]; int head[N],num_edge;
int w[N],wt[N];
int n,m,u,v,ww,x,y,k,op;
int tree[N<<2];
int son[N],id[N],fa[N],tot,dep[N],siz[N],top[N];

il int read()
{
	int f=0,s=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
	for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
	return f ? -s : s;
}

il void add(int from,int to,int dis)
{
	edge[++num_edge] = (node){from,to,dis,head[from]};
	head[from] = num_edge;
}

#define lc p<<1
#define rc p<<1|1

il void build(int p,int l,int r)
{
	if(l == r)
	{
		tree[p] = wt[l];
		return ;
	}
	int mid = (l+r) >> 1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	tree[p] = tree[lc] + tree[rc];
}

il void Modify(int nl,int nr,int l,int r,int p,int k)
{
	if(l >= nl && r <= nr)
	{
		tree[p] = k;
		return ;
	}
	int mid = (l+r) >> 1;
	if(nl <= mid) Modify(nl,nr,l,mid,lc,k);
	if(nr > mid) Modify(nl,nr,mid+1,r,rc,k);
	tree[p] = tree[lc] + tree[rc];
}

il int Query(int nl,int nr,int l,int r,int p)
{
	int res = 0;
	if(l >= nl && r <= nr) return tree[p];
	int mid = (l+r) >> 1;
	if(nl <= mid) res += Query(nl,nr,l,mid,lc);
	if(nr > mid) res += Query(nl,nr,mid+1,r,rc);
	return res;
}

/*------------------------------------------*/

il void dfs1(int x,int f)
{
	dep[x] = dep[f] + 1 , fa[x] = f , siz[x] = 1;
	for(re int i=head[x];i;i=edge[i].next)
	{
		int y = edge[i].v , ww = edge[i].w;
		if(y == f) continue;
		dfs1(y,x);
		w[y] = ww;
		siz[x] += siz[y];
		if(siz[son[x]] < siz[y]) son[x] = y;
	}
}

il void dfs2(int x,int topf)
{
	id[x] = ++tot , wt[tot] = w[x] , top[x] = topf;
	if(!son[x]) return ;
	dfs2(son[x],topf);
	for(re int i=head[x];i;i=edge[i].next)
	{
		int y = edge[i].v;
		if(y == fa[x] || y == son[x]) continue;
		dfs2(y,y);
	}
}

il void Modify_way(int x,int y,int k)
{
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]]) swap(x,y);
		Modify(id[top[x]],id[x],1,n,1,k);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x,y);
	if(x == y) return ;
	Modify(id[x]+1,id[y],1,n,1,k);
}

il int Query_way(int x,int y)
{
	int res = 0;
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]]) swap(x,y);
		res += Query(id[top[x]],id[x],1,n,1);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x,y);
	res += Query(id[x],id[y],1,n,1);
	res -= Query(id[x],id[x],1,n,1);
	return res;
}

signed main()
{
	n = read();
	for(re int i=1;i<=n-1;i++)
	{
		u = read() , v = read() , ww = read();
		add(u,v,ww) , add(v,u,ww);
		e[i] = (node){u,v,0,0};
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	m = read();
	for(re int i=1;i<=m;i++)
	{
		op = read() , x = read() , y = read();
		if(op == 1) Modify_way(e[x].u,e[x].v,y);
		if(op == 2) cout << Query_way(x,y) << "\n";
	}
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：4)

题意就是单边修改求链和。

树分块可以做到 $O(1)$ 修改，$O(\sqrt n)$ 查询，当然直接重剖序上每条重链单独分块也能得到同样的效果。

自然也能 $O(\sqrt n)$ 修改，$O(1)$ 查询，不过这里有一个 LCA 的瓶颈，所以需要 ST 表或 Four Russian。

普通的树剖加树状数组是最平凡的 $O(\log n)$ 修改 $O(\log^2n)$ 查询。

使用 LCT 或“全局平衡二叉树”可以做到 $O(\log n)$ 修改查询。

不过我认为常数最小且最优秀的方法是括号序差分和树状数组，同样是 $O(\log n)$ 修改查询。

当然考场上还是 LCT 最好，注意使用了化边为点，[赛时 AC 记录](https://atcoder.jp/contests/abc294/submissions/39863267)。

---

## 作者：szhqwq (赞：3)

## $\tt{Solution}$

考虑树链剖分。

~~此题较裸。~~

本题需要实现树剖的两个操作：

- 单点修改

- 区间查询总和

我们使用线段树维护总和，其次，此题给定的是树的**边权**，我们需要考虑如何将边权转移到点权上来：记录第 $i$ 边连接的两个点 $pre_i$ 和 $nxt_i$，每次修改，先将 $i \to i \cdot 2 - 1$（因为是树），再将边权统一赋值到**深度更大的点**上来，进行修改。

查询需要注意不能将两点的最近公共祖先的值算入其中。

剩下的就是模板了。

## $\tt{AC \ Code \ of}$ [$\tt{ABC294G}$](https://www.luogu.com.cn/problem/AT_abc294_g)

```cpp
#include <bits/stdc++.h>

#define int long long
//#pragma G++ optimize(2) 

using namespace std;

const int N = 2e6 + 10;

int n,q;
int a[N],wc[N],w[N];
int h[N],e[N << 1],ne[N << 1],idx;
int son[N],fa[N],siz[N],d[N],top[N],id[N],cnt = 0;
int pre[N],nxt[N];

struct node {
	int l,r;
	int val;
} tr[N << 2];

inline int read() {
	int x = 0,f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * f;
}

void add(int a,int b,int c) {
	pre[idx] = a,nxt[idx] = b;
	e[idx] = b;
	w[idx] = c;
	ne[idx] = h[a];
	h[a] = idx ++;
}

void pushup(int u) {
	tr[u].val = tr[u << 1].val + tr[u << 1 | 1].val;
}

void build(int u,int l,int r) {
	tr[u] = {l,r};
	if (l == r) {
		tr[u].val = wc[l];
		return ;
	}
	int mid = l + r >> 1;
	build(u << 1,l,mid),build(u << 1 | 1,mid + 1,r);
	pushup(u);
}

void modify(int u,int x,int k) {
	if (tr[u].l == tr[u].r) {
		tr[u].val = k;
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if (x <= mid) modify(u << 1,x,k);
	else modify(u << 1 | 1,x,k);
	pushup(u);
}

int query(int u,int l,int r) {
	if (l <= tr[u].l && tr[u].r <= r) return tr[u].val;
	int res = 0;
	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) res += query(u << 1,l,r);
	if (mid < r) res += query(u << 1 | 1,l,r);
	return res;
}

void dfs1(int u,int f,int dep) {
	d[u] = dep;
	fa[u] = f;
	siz[u] = 1;
	int Max = 0;
	for (int i = h[u]; ~i; i = ne[i] ) {
		int j = e[i];
		if (j == f) continue;
		dfs1(j,u,dep + 1);
		siz[u] += siz[j];
		a[j] = w[i];
		if (siz[j] > Max) {
			Max = siz[j];
			son[u] = j;
		}
	}
}

void dfs2(int u,int t) {
	id[u] = ++ cnt;
	wc[cnt] = a[u];
	top[u] = t;
	if (!son[u]) return ;
	dfs2(son[u],t);
	for (int i = h[u]; ~i; i = ne[i] ) {
		int j = e[i];
		if (j == fa[u] || j == son[u]) continue;
		dfs2(j,j);
	}
}

int query_Range(int x,int y) {
	int res = 0;
	while (top[x] != top[y]) {
		if (d[top[x]] < d[top[y]]) swap(x,y);
		res += query(1,id[top[x]],id[x]);
		x = fa[top[x]];
	}
	if (d[x] > d[y]) swap(x,y);
	res += query(1,id[x] + 1,id[y]);
	return res;
}

signed main() {
	memset(h,-1,sizeof h);
	n = read();
	for (int i = 1; i < n; i ++ ) {
		int a,b,c;
		a = read(),b = read(),c = read();
		add(a,b,c);
		add(b,a,c);
	}
	dfs1(1,0,1);
	dfs2(1,1);
	build(1,1,n);
	q = read();
	while (q -- ) {
		int op,x,y;
		op = read(),x = read(),y = read();
		if (op == 1) {
			x <<= 1,x --;
			if (d[pre[x]] > d[nxt[x]]) x = pre[x];
			else x = nxt[x];
			modify(1,id[x],y);
		} else cout << query_Range(x,y) << endl;
	}
	return 0;
} 
```

---

## 作者：spider_oyster (赞：2)

~~G 怎么又是板子啊？~~

把边权算到点权（我考虑算到一条边的儿子节点）上，这便是一道树链查询，单点修改的题了。

可以用树链剖分和 dfs 序 + 树上差分做，我选后者因为代码更短。

考虑节点 $u$ 只对他的儿子节点有贡献，也就是当儿子往上经过 $u$ 时，才会加上 $u$ 的权值，而 $u$ 的子树在 dfs 序中又是一段连续的区间，我们用一个树状数组维护即可。

对于一条树链 $u-v$，我们把他拆成 $1-u$，$1-v$ 再减去两次 $1-\operatorname{lca(u,v)}$，因为 $1-\operatorname{lca(u,v)}$ 这条链被重复算了两次。

```cpp
#include<bits/stdc++.h>
#define F(i,s,t) for(register int i=(s);i<=(t);++i)
#define R(i,s,t) for(register int i=(s);i>=(t);--i)
#define ll long long
using namespace std;

const int N=2e5+5;
int n,m,u,v,w;
int cnt,a[N],to[N],st[N],ed[N],f[N][25],dep[N];
//to 记录一条边的儿子节点 
ll c[N];
struct node{int v,w,id;};
vector<node>G[N];

inline void update(int x,int k) {for(;x<=n;x+=x&-x) c[x]+=k;}
inline ll sum(int x)
{
	ll res=0;
	for(;x;x^=x&-x) res+=c[x];
	return res;
}

void dfs(int u,int fa)
{
	st[u]=++cnt,dep[u]=dep[fa]+1,f[u][0]=fa;
	F(i,1,20) f[u][i]=f[f[u][i-1]][i-1];
	for(auto i:G[u])
	{
		if(i.v==fa) continue;
		a[i.v]=i.w,to[i.id]=i.v;
		dfs(i.v,u);
	}
	ed[u]=cnt;
}

inline int LCA(int x,int y)//lca板子 
{
	if(dep[x]<dep[y]) swap(x,y);
	R(i,20,0) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	R(i,20,0) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	F(i,1,n-1)
	{
		cin>>u>>v>>w;
		G[u].push_back((node){v,w,i});
		G[v].push_back((node){u,w,i});
	}                              
	dfs(1,0);
	F(i,1,n) update(st[i],a[i]),update(ed[i]+1,-a[i]);//对每个节点的子树差分 
	cin>>m;
	while(m--)
	{
		int op,u,v;cin>>op>>u>>v;
		if(op==1)//修改一条边，也就是删除原来的边在加上现在的边，记得要同时更改边权（儿子节点的点权） 
		{
			int x=to[u];
			update(st[x],-a[x]),update(ed[x]+1,a[x]);
			a[x]=v;
			update(st[x],a[x]),update(ed[x]+1,-a[x]);
		}
		else//(1->u)+(1->v)-2*(1->lca(u,v)) 
		{
			int lca=LCA(u,v);
			cout<<sum(st[u])+sum(st[v])-sum(st[lca])*2<<'\n';
		}
	}
}
```


---

## 作者：Acee (赞：1)

题意主要是让你在树上改一个边的值和求一下两的点之间的路径。

那其实就是一个树链剖分的模版题，分一下轻重儿子，然后将树剖成若干条链，只需要将边化成点，$i$ 到 $i$ 的父亲应称为 $i$ 号边。

查询：$O(\log^2(n))$。


单点修改：$O(\log_2(n))$。 

当然也可以用 LCT 来做到更优秀的 $O(\log_2(n))$，但这里采用了好调一些的树链剖分。

还有一种括号序差分的算法，虽然常数小一些不过没数据结构好想。


```cpp
#include <bits/stdc++.h>
// #include <ext/rope>
using namespace std;
// using namespace __gnu_cxx;
namespace MAIN {
	const int N = 2e5 + 5;
	int n, m, cnt, M;
	struct edge {
		int nxt, to, val;
	} e[N * 2];
	int num, h[N];
	void addedge(int x, int y, int z) {
		e[++num].nxt = h[x];
		e[num].to = y;
		e[num].val = z;
		h[x] = num;
	}
	int son[N], dep[N], fa[N], sz[N];
	int id[N], top[N], dfn[N];
	int W[N], V[N], U[N], val[N];
	long long sum[N << 2];
	void update(int p) {
		sum[p] = sum[p << 1] + sum[p << 1 | 1];
	}
	void change(int p, int l, int r, int x, int y) {
		if (l == r) {
			sum[p] = y;
			return;
		}
		int mid = (l + r) >> 1;
		if (x <= mid) change(p << 1, l, mid, x, y);
		else change(p << 1 | 1, mid + 1, r, x, y);
		update(p); 
	}
	long long query(int p, int l, int r, int x, int y) {
		if (x <= l && r <= y) return sum[p];
		int mid = (l + r) >> 1;
		long long ans = 0;
		if (x <= mid) ans += query(p << 1, l, mid, x, y);
		if (y > mid) ans += query(p << 1 | 1, mid + 1, r, x, y);
		return ans; 
	}
	void dfs1(int x, int f) {
		fa[x] = f;
		sz[x] = 1;
		dep[x] = dep[f] + 1;
		int t = -1;
		for (int i = h[x]; i; i = e[i].nxt) {
			int y = e[i].to;
			if (y == f) continue;
			val[y] = e[i].val;
			dfs1(y, x);
			sz[x] += sz[y];
			if (sz[y] > t) {
				t = sz[y];
				son[x] = y;
			}
		}
	}
	void dfs2(int x, int f) {
		top[x] = f;
		id[x] = ++cnt;
		dfn[cnt] = x;
		change(1, 1, n, id[x], val[x]);
		if (son[x] == 0) return;
		dfs2(son[x], f);
		for (int i = h[x]; i; i = e[i].nxt) {
			int y = e[i].to;
			if (y == fa[x] || y == son[x]) continue;
			dfs2(y, y);
		}
	}
	long long querypath(int x, int y) {
		if (x == y) return 0;
		long long ans = 0;
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) {
				swap(x, y);
			}
			ans += query(1, 1, n, id[top[x]], id[x]);
	//		cout << query(id[top[x]], id[x]) << ' ';
			x = fa[top[x]];
		}
	//	cout << '\n';
		if (dep[x] > dep[y]) {
			swap(x, y);
		}
	//	cout << id[x] + 1 << ' ' << id[y] << '\n';
		ans += query(1, 1, n, id[x] + 1, id[y]);
		return ans;
	}
	int main() {
		ios_base::sync_with_stdio(false);
		cin.tie(0), cout.tie(0);
		cin >> n;
		for (int i = 1; i < n; ++i) {
			cin >> U[i] >> V[i] >> W[i];
			addedge(U[i], V[i], W[i]);
			addedge(V[i], U[i], W[i]);
		}
		dfs1(1, 0);
		dfs2(1, 1);
		int q;
		cin >> q;
		for (int i = 1, x, y, s; i <= q; ++i) {
			cin >> s;
			cin >> x >> y;
			if (s == 2) {
				cout << querypath(x, y) << '\n';
			}
			else {
				int u = U[x], v = V[x];
				if (fa[v] == u) swap(u, v);
				change(1, 1, n, id[u], y);
			}
		}
		return 0; 
	}
}
int main() {
	return MAIN::main();
}
```

---

## 作者：lizhous (赞：1)

[洛谷](https://www.luogu.com.cn/problem/AT_abc294_g)

[Atcoder](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc294_g)

## 分析
树剖在这里就不详细讲了，[模板题](https://www.luogu.com.cn/problem/P3384)的题解比我讲得好。

这道题给的是边权，我们考虑转化为点权。

经典转化，把自己连向父亲的路径权值作为自己的点权，然后求路径 $u,v$ 的权值和就是求 $u\sim lca$ 的和与 $v\sim lca$ 的和的和。

但是这样转化完，$lca$ 的权值并不对答案产生贡献，需要减掉。

注意数组开到 $2\times 10^5$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q,rt,w[300001],sum[8000001],tag[8000001],u[300001],v[300001],qqw[300001];
struct edge
{
	int v,w;
};
vector<edge> g[300001];
void addtag(int o,int l,int r,int v)
{
    tag[o]=v;
    sum[o]=(r-l+1)*v;
}
void downtag(int o,int l,int r)
{
    if(tag[o]==0) return;
    int mid=r+l>>1;
    addtag((o<<1),l,mid,tag[o]);
    addtag((o<<1)+1,mid+1,r,tag[o]);
    tag[o]=0;
}
void uptag(int o)
{
    sum[o]=sum[o<<1]+sum[(o<<1)+1];
}
void add(int o,int l,int r,int x,int y,int v)
{
    if(l>y || r<x)
    {
        return;
    }
    if(x<=l && r<=y)
    {
        addtag(o,l,r,v);
        return;
    }
    int mid=r+l>>1;
    downtag(o,l,r);
    add((o<<1),l,mid,x,y,v);
    add((o<<1)+1,mid+1,r,x,y,v);
    uptag(o);
}
int get(int o,int l,int r,int x,int y)
{
    if(l>y || r<x)
    {
        return 0;   
    }
    if(x<=l && r<=y)
    {
        return sum[o];
    }
    int mid=l+r>>1;
    downtag(o,l,r);
    return (get(o<<1,l,mid,x,y)+get((o<<1)+1,mid+1,r,x,y));
}
int fat[300001],siz[300001],dep[300001],hson[300001],top[300001],cnt,dfn[300001],dis[300001];
void getdfsh(int u,int fa)
{
    fat[u]=fa;
    dep[u]=dep[fa]+1;
    int lll=0;
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i].v;
        if(v==fa) continue;
        getdfsh(v,u);
        if(siz[v]>lll)
        {
            hson[u]=v;
            lll=siz[v];
        }
        siz[u]+=siz[v];
    }
    siz[u]++;
}
void gettd(int u,int fa)
{
    dfn[u] = ++cnt;
    dis[u] = cnt;
    if(hson[fat[u]]==u)
    {
        top[u]=top[fa];
    }
    else
    {
        top[u]=u;
    }
    if(hson[u]!=0) gettd(hson[u],u); 
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i].v;
        if(v==fa||v==hson[u]) continue;
        gettd(v,u);
    }
}
int addlsum(int st,int ed,int v)
{
    if(dfn[st]<dfn[ed]) swap(st,ed);
    int u=st,re=0;
    while(1)
    {
        if(dfn[top[u]]<=dfn[ed])
        {
            add(1,1,n,dfn[ed],dfn[u],v);
            break;
        }
        add(1,1,n,dfn[top[u]],dfn[u],v);
        u=fat[top[u]];
    }
    return re;
} 
int getlsum(int st,int ed)
{
    if(dfn[st]<dfn[ed]) swap(st,ed);
    int u=st,re=0;
    while(1)
    {
        if(dfn[top[u]]<=dfn[ed])
        {
            re+=get(1,1,n,dfn[ed],dfn[u]);
            break;
        }
        re+=get(1,1,n,dfn[top[u]],dfn[u]);
        u=fat[top[u]];
    }
    return re;
} 

void getdis(int u, int fa) {
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].v;
        if (v == fa) continue;
        getdis(v, u);
        dis[u] = max(dis[u], dis[v]);
    }
}
int father[500001][21];
void getfather(int u,int fa)
{
    father[u][0]=fa;
    for(int i=1;i<=20;i++)
    {
        father[u][i]=father[father[u][i-1]][i-1]; 
    }
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i].v;
        if(v==fa) continue;
        getfather(v,u);
    }
}

int getlca(int u,int v)
{
    if(dep[u]>dep[v]) swap(u,v); 
    int mul=dep[v]-dep[u],w=0;
    while(mul)
    {
        if(mul&1) v=father[v][w];
        mul>>=1;
        w++;
    }
    if(u==v) return u;
    for(int i=20;i>=0;i--)
    {
        if(father[u][i]!=father[v][i])
        {
            u=father[u][i];
            v=father[v][i];
        }
    }
    return father[u][0];
}
void dfs1(int u,int fa)
{
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i].v,www=g[u][i].w;
		if(v==fa) continue;
		w[v]=www;
		dfs1(v,u);
	}
}
signed main()
{
    scanf("%lld",&n);
    rt=1;
    for(int i=1;i<n;i++)
    {
        scanf("%lld%lld%lld",&u[i],&v[i],&qqw[i]);
        g[u[i]].push_back((edge){v[i],qqw[i]});
        g[v[i]].push_back((edge){u[i],qqw[i]});
    }
    dfs1(rt,0);
    getdfsh(rt,0);
    gettd(rt,0);
    getdis(rt,0);
    getfather(rt,0);
    for(int i=1;i<=n;i++)
    {
        add(1,1,n,dfn[i],dfn[i],w[i]);
    }
    scanf("%lld",&q);
    for(int i=1,opt,uu,vv,w;i<=q;i++)
    {
        scanf("%lld%lld",&opt,&uu);
        if(opt==2)
        {
            scanf("%lld",&vv);
            int lca=getlca(uu,vv);
            printf("%lld\n",((getlsum(uu,lca)+getlsum(vv,lca)-2*get(1,1,n,dfn[lca],dfn[lca]))));
        }
        if(opt==1)
        {
        	vv=v[uu];
            uu=u[uu];
            int lca=getlca(uu,vv);
            scanf("%lld",&w);
			if(uu==lca) add(1,1,n,dfn[vv],dfn[vv],w);
			if(vv==lca) add(1,1,n,dfn[uu],dfn[uu],w);
        }
    }
}
```

---

## 作者：SlyCharlotte (赞：1)

[或许更好的阅读体验？](https://zhuanlan.zhihu.com/p/615414755)
### 题意描述

给你一个节点数为 $n$ 的树，每条边给定一个边权。

有以下两种操作：

- `1 x w` 将第 $x$ 条边的边权改为 $w$。
- `2 u v` 询问点 $u$ 到 $v$ 的最短路径。

### 简要分析

我们使用 `dfs` 序将一棵树拍扁成一个序列，随后对于该序列使用线段树维护即可。

对于树上两点的距离我们可以维护一个根到点 $i$ 的距离 $dis_i$，那么 $u \rightarrow v$ 的距离为 $dis_u + dis_v - 2\times dis_{LCA(u,v)}$。

这里求 `LCA` 使用树链剖分，倍增都可。

时间复杂度 $O(n \log n)$。 

### 代码实现

```cpp
void add(int u, int v, int w, int id) { es[++tot] = (edge) {hd[u], v, w, id}, hd[u] = tot; }

void dfs(int u, int fa) {
    tI[u] = ++timer, p[u][0] = fa;
    for (int i = 1; i < S; i++)p[u][i] = p[p[u][i - 1]][i - 1];
    for (int i = hd[u], v; i; i = es[i].nxt)
        if ((v = es[i].v) != fa)
            d[v] = d[u] + 1, dfs(v, u), rf[es[i].id] = v;
    tO[u] = timer;
}

int LCA(int u, int v) {
    if (d[u] < d[v])swap(u, v);
    int dlt = d[u] - d[v];
    for (int i = 0; i < S; i++)if ((dlt >> i) & 1)u = p[u][i];
    if (u == v)return u;
    for (int i = S - 1; i >= 0; i--)if (p[u][i] != p[v][i])u = p[u][i], v = p[v][i];
    return p[u][0];
}

void upd(int x, int v) { while (x <= n)bit[x] += v, x += x & -x; }

int qry(int x) {
    int r = 0;
    while (x)r += bit[x], x -= x & -x;
    return r;
};

signed main() {
    cin >> n;
    for (int i = 1, u, v, w; i < n; i++)cin >> u >> v >> w, ew[i] = w, add(u, v, w, i), add(v, u, w, i);
    dfs(1, 0);
    for (int i = 1; i < n; i++)upd(tI[rf[i]], ew[i]), upd(tO[rf[i]] + 1, -ew[i]);
    cin >> q;
    for (int qi = 1, op, x, y, u, v; qi <= q; qi++) {
        cin >> op >> x >> y;
        if (op == 1)u = rf[x], upd(tI[u], y - ew[x]), upd(tO[u] + 1, ew[x] - y), ew[x] = y;
        else u = x, v = y, cout << qry(tI[u]) + qry(tI[v]) - 2 * qry(tI[LCA(u, v)]) << '\n';
    }
    return 0;
}

```



---

## 作者：六楼溜刘 (赞：1)

## 题意
- 给你一棵有 $n$ 个节点的树，边有边权，有 $q$ 个操作。
- 操作 $1$ 是修改某条边的权。
- 操作 $2$ 是查询某两个点之间的距离（即两点间简单路径上的边权和）。
- $n \leq 2 \times 10^5,q\leq 2 \times 10^5$

## 题解

这道题一道是比较板的单点修改树链查询，我们跑一遍[ DFS 序](https://oi-wiki.org/graph/dfs/#dfs-%E5%BA%8F%E5%88%97)，用树状数组维护树上前缀和。

具体来说，我们把每条边的权值存到对应的子节点上，这个权值会对整棵子树产生贡献，我们用一个差分树状数组维护区间操作。

对于操作 $1$，我们先找到这条边指向的子节点，回退原有的影响，再对这棵子树进行区间加。

对于操作 $2$，我们先查询 $u$ 到跟节点的距离 $dist_u$，再查询 $v$ 到根节点的距离 $dist_v$，由于两点 $\operatorname{lca}$ 到根节点的距离被多算了两遍，我们再减去 $2\cdot dist_{\operatorname{lca}(u,v)}$ 就可以啦。

预处理复杂度 $O(n\log n)$，修改查询复杂度均为 $O(\log n)$，随便过。

具体见代码。

## code
```cpp
#include<iostream>
#include<algorithm>
#include<vector> 
#define int long long
#define forup(i,s,e) for(register int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(register int i=(s);i>=(e);i--)
using namespace std;
#define gc getchar()
inline int read(){//快读
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=2e5+5,inf=0x3f3f3f3f;
struct edge{
	int v,w,pos;//pos 为边的编号
	edge(int _v=0,int _w=0,int _pos=0):v(_v),w(_w),pos(_pos){};
};
int n,q,a[N],son[N],f[N][21],dpt[N];
vector<edge> e[N];
struct Tree{
	int c[N];
	void upd(int x,int k){for(;x<=n;x+=x&-x)c[x]+=k;}
	int sum(int x){int res=0;for(;x>0;x-=x&-x)res+=c[x];return res;}
}mt;
int st[N],ed[N],TM;//DFS 序三件套
void dfs(int x,int fa){
	st[x]=++TM;f[x][0]=fa;
	dpt[x]=dpt[fa]+1;
	forup(i,1,20){
		f[x][i]=f[f[x][i-1]][i-1];
	}
	for(auto i:e[x]){
		if(i.v==fa) continue;
		a[i.v]=i.w;//把边权存到点里
		son[i.pos]=i.v;//存一下指向的子节点方便处理
		dfs(i.v,x);
	}
	ed[x]=TM;
	mt.upd(st[x],a[x]);mt.upd(ed[x]+1,-a[x]);
    //差分树状数组区间操作
}
int lca(int x,int y){
	if(dpt[x]>dpt[y]) swap(x,y);
	for(int i=20;i>=0&&dpt[y]>dpt[x];i--){
		if(dpt[f[y][i]]>=dpt[x]) y=f[y][i];
	}
	if(x==y) return x;
	for(int i=20;i>=0&&f[x][0]!=f[y][0];i--){
		if(f[y][i]!=f[x][i]){
			x=f[x][i];
			y=f[y][i];
		}
	}
	return f[x][0];
}
signed main(){
	n=read();
	forup(i,1,n-1){
		int u=read(),v=read(),w=read();
		e[u].push_back(edge(v,w,i));
		e[v].push_back(edge(u,w,i));
	}
	dfs(1,0);
	q=read();
	while(q--){
		int op=read(),u=read(),v=read();
		if(op==1){
			int x=son[u];
			mt.upd(st[x],-a[x]);mt.upd(ed[x]+1,a[x]);//先回退原有影响
			a[x]=v;
			mt.upd(st[x],a[x]);mt.upd(ed[x]+1,-a[x]);//再区间加
		}else{
			int LCA=lca(u,v);
			printf("%lld\n",mt.sum(st[u])+mt.sum(st[v])-mt.sum(st[LCA])*2);
		}
	}
}

```


---

## 作者：cwfxlh (赞：1)

# [ABC294G](https://www.luogu.com.cn/problem/AT_abc294_g)   

感觉最近的 G 题越来越典。   

题目大意是要你维护一棵边带权的树，每次会询问两点之间的距离，并且要求支持修改边权。范围在 $2\times 10^5$ 内。   

为了方便研究，我们令 $1$ 为根。

先不考虑修改，如果单纯是要询问两点之间的距离，这时有一个很显然的暴力，两者往上回溯，直到回溯到二者的 lca 为止，算出走过的路程。这样肯定是不行的，我们考虑优化。   

令 $dis_a$ 表示从 $1$ 到 $a$ 的距离，则 $ans(a,b)=dis(a)+dis(b)-2\times dis(lca(a,b))$ ，也就是说，如果我们知道了每个点的 dis 值，并且能够快速求 lca，求出答案是常数级的。lca 可以用倍增来求，而 dis 则可以预处理出来。总复杂度 $\Theta(n\log n)$。

然而本题要求支持修改，于是考虑修改一条边所造成的影响。如果修改一条从 $u$ 到 $v$ 的边，则 dis 发生改变的区域就是 $v$ 的子树。考虑使用 dfs 序来维护，因为在 dfs 序中，$v$ 的子树是连续的一段。那么就可以用树状数组区间修改，单点查询了。   

Code： 

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
int head[500003],k1,k2,k3,k4,k5;
struct Edge{
	int st;
	int ed;
	int val;
	int nxt;
	int cs;
}E[500003];
int totE=1;
int stk[500003],tot;
int l[500003],r[500003],dist[500003];
int TreeAr[500003],wz[500003],dep[500003];
int lowbit(int X){
	return (X&(-X));
}
void add(int X,int Y,int val){
	for(int i=X;i<=n;i+=lowbit(i))TreeAr[i]+=val;
	for(int i=Y+1;i<=n;i+=lowbit(i))TreeAr[i]-=val;
	return;
}
int getval(int X){
	int ret=0;
	for(int i=X;i>0;i-=lowbit(i))ret+=TreeAr[i];
	return ret;
}
void addEdge(int st,int ed,int val){
	totE++;
	E[totE].st=st;
	E[totE].ed=ed;
	E[totE].val=val;
	E[totE].nxt=head[st];
	head[st]=totE;
	return;
}
int F[500003][33];
void dfs(int now,int f){
	tot++;
	stk[tot]=now;
	l[now]=tot;
	wz[now]=tot;
	add(wz[now],wz[now],dist[now]);
	for(int i=1;;i++){
		if(F[F[now][i-1]][i-1]==0)break;
		F[now][i]=F[F[now][i-1]][i-1];
	}
	for(int i=head[now];i!=0;i=E[i].nxt){
		if(E[i].ed==f)continue;
		E[i].cs=1;
		F[E[i].ed][0]=now;
		dist[E[i].ed]=dist[now]+E[i].val;
		dep[E[i].ed]=dep[now]+1;
		dfs(E[i].ed,now);
	}
	r[now]=tot;
	return;
}
int lca(int X,int Y){
	if(dep[X]>dep[Y])swap(X,Y);
	int c=30;
	while(c>=0&&dep[X]<dep[Y]){
		while(c>=0&&(F[Y][c]==0||dep[F[Y][c]]<dep[X]))c--;
		if(c<0)break;
		Y=F[Y][c];
		c--;
	}
	c=30;
	while(c>=0&&X!=Y){
		while(c>=0&&(F[Y][c]==0||F[Y][c]==F[X][c]))c--;
		if(c<0)break;
		Y=F[Y][c];
		X=F[X][c];
		c--;
	}
	while(X!=Y){
		Y=F[Y][0];
		X=F[X][0];
	}
	return X;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<n;i++){
		scanf("%lld%lld%lld",&k1,&k2,&k3);
		addEdge(k1,k2,k3);
		addEdge(k2,k1,k3);
	}
	dfs(1,-1);
	scanf("%lld",&q);
	while(q--){
		scanf("%lld%lld%lld",&k1,&k2,&k3);
		if(k1==1){
			if(E[(k2*2)].cs){
				add(l[E[(k2*2)].ed],r[E[(k2*2)].ed],k3-E[(k2*2)].val);
				E[(k2*2)].val=k3;
				E[(k2*2)+1].val=k3;
			}
			else{
				add(l[E[(k2*2+1)].ed],r[E[(k2*2+1)].ed],k3-E[(k2*2)].val);
				E[(k2*2)].val=k3;
				E[(k2*2)+1].val=k3;
			}
		}
		else{
			printf("%lld\n",getval(wz[k2])+getval(wz[k3])-getval(wz[lca(k2,k3)])*2);
		}
	}
	return 0;
}
```

---

## 作者：lzyqwq (赞：0)

**[更好的阅读体验](https://www.cnblogs.com/MnZnOIerLzy/articles/17447388.html)**

~~唯一会的 G~~。

**[AtCoder 链接](https://atcoder.jp/contests/abc294/tasks/abc294_g "AtCoder 链接")**

**[洛谷链接](https://www.luogu.com.cn/problem/solution/AT_abc294_g "洛谷链接")**

> - 给 $n$ 个点的树，$Q$ 次操作：
>
>     - $\texttt{1 }i\texttt{ }w$，将第 $i$ 条边边权改为 $w$。
>
>     - $\texttt{2 }x\texttt{ }y$，查询 $x,y$ 之间路径的权值和。
>
> - $n,Q\le 2\times 10^5$。

树剖板子，运用边转点技巧，由于只有单点修改，套上树状数组维护即可。

[详见我的树链剖分讲解博客](https://www.cnblogs.com/MnZnOIerLzy/articles/17438805.html "详见我的树链剖分讲解博客")。

简单来说，我们先随便从一个点开始 DFS，将边权转化为其深度较大的节点的权值，然后就变成了对点的操作了。

时间复杂度为 $\mathcal{O}(Q\log^2 n)$，空间复杂度为 $\mathcal{O}(n)$。

**[评测记录](https://atcoder.jp/contests/abc294/submissions/39870783 "评测记录")**

```CPP
#include<bits/stdc++.h>
#define N 200005
#define int long long
using namespace std;
int n,q,f[N],h[N],t[N],sz[N],dfn[N],to[N],d[N],bit[N],val[N];
struct edge{
    int v,w,id;
};
vector<edge>g[N];
void modify(int x,int k){
    for(int i=x;i<=n;i+=i&(-i)){
        bit[i]+=k;
    }
}
int query(int x){
    int ret=0;
    for(int i=x;i;i-=i&(-i)){
        ret+=bit[i];
    }
    return ret;
}
void dfs1(int u,int fa){
    sz[u]=1;
    for(auto[v,w,id]:g[u]){
        if(v^fa){
            f[v]=u;
            to[id]=v;
            val[v]=w;
            d[v]=d[u]+1;
            dfs1(v,u);
            sz[u]+=sz[v];
        }        
    }
}
void dfs2(int u,int fa){
    for(auto[v,w,id]:g[u]){
        if(v^fa){
            if((sz[v]<<1)>sz[u]){
                t[v]=t[u];
                h[u]=v;
            }else{
                t[v]=v;
            }
            dfs2(v,u);
        }
    }
}
void dfs3(int u,int fa){
    ++dfn[0];
    dfn[u]=dfn[0];
    modify(dfn[u],val[u]);
    if(h[u]){
        dfs3(h[u],u);
    }
    for(auto[v,w,id]:g[u]){
        if((v^fa)&&(v^h[u])){
            dfs3(v,u);
        }
    }
}
int pathquery(int x,int y){
    int ret=0;
    while(t[x]^t[y]){
        if(d[t[x]]<d[t[y]]){
            swap(x,y);
        }
        ret+=query(dfn[x])-query(dfn[t[x]]-1);
        x=f[t[x]];
    }
    if(x^y){
        if(d[x]>d[y]){
            swap(x,y);
        }
        ret+=query(dfn[y])-query(dfn[x]);
    }
    return ret;
}
signed main(){
    scanf("%lld",&n);
    for(int i=1,u,v,w;i^n;++i){
        scanf("%lld%lld%lld",&u,&v,&w);
        g[u].push_back({v,w,i});
        g[v].push_back({u,w,i});
    }
    dfs1(1,0);
    t[1]=1;
    dfs2(1,0);
    dfs3(1,0);
    scanf("%lld",&q);
    for(int op,x,y;q--;){
        scanf("%lld%lld%lld",&op,&x,&y);
        if(op==1){
            modify(dfn[to[x]],-val[to[x]]);//修改相当于减去原值再加上新值。
            modify(dfn[to[x]],y);
            val[to[x]]=y;
        }else{
            printf("%lld\n",pathquery(x,y));
        }
    }
}
```

---

## 作者：FReQuenter (赞：0)

不难发现，修改操作仅影响那条边连接的两个点中深度较大的那个点的子树中的所有点。

所以考虑维护每个点的 dfs 序，就将一个点的子树中的所有点放到了一个可维护的区间上。

两个点之间的距离就是两个点到根的距离之和减去二倍的两个点的 LCA 到根的距离。

那么，修改操作就可以视作修改了某个点的子树中所有的点，区间加上修改的值。

而查询本质上就是查询一个点到根的距离，就是单点查询当前点被加上的值。

两个操作对应区间修改和单点查询，可以使用树状数组维护。

其实这题就是 [P3384 【模板】重链剖分/树链剖分](https://www.luogu.com.cn/problem/P3384)，同样可以树剖解决。

```cpp
#include<bits/stdc++.h>
#define MAXN 200005
#define int long long
#define lowbit(x) ((x)&(-x))
#define fi first
#define se second 
using namespace std;
int n,q,cnt,c[MAXN],dfn[MAXN],nodel[MAXN],noder[MAXN],dist[MAXN],qu[MAXN],qv[MAXN],qw[MAXN],f[MAXN][30],lg[MAXN],depth[MAXN];
vector<pair<int,int>> gv[MAXN];
void basadd(int x,int v){
	for(;x<MAXN;x+=lowbit(x)) c[x]+=v;
}
int query(int x){
	int sum=0;
	for(;x;x-=lowbit(x)) sum+=c[x];
	return sum;
} 
void add(int l,int r,int v){
	basadd(l,v);
	basadd(r+1,-v);
}
void dfs(int now,int father){
	dfn[now]=++cnt;
	nodel[now]=cnt;
	depth[now]=depth[father]+1;
	f[now][0]=father;
	for(int i=1;i<=lg[depth[now]];i++) f[now][i]=f[f[now][i-1]][i-1];
	for(int i=0;i<(int)gv[now].size();i++){
		if(gv[now][i].fi!=father){
			dist[gv[now][i].fi]=dist[now]+gv[now][i].se;
			dfs(gv[now][i].fi,now);
		}
	}
	noder[now]=cnt;
}
int lca(int x,int y){
	if(depth[x]<depth[y]) swap(x,y);
	while(depth[x]>depth[y]) x=f[x][lg[depth[x]-depth[y]]-1];
	if(x==y) return x;
	for(int i=lg[depth[x]]-1;i>=0;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
int getdis(int x,int y){
	return query(dfn[x])+query(dfn[y])-2*query(dfn[lca(x,y)]);
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		gv[u].push_back({v,w});
		gv[v].push_back({u,w});
		qu[i]=u,qv[i]=v,qw[i]=w;
	}
	for(int i=1;i<MAXN;i++) lg[i]=lg[i>>1]+1;
	dfs(1,0);
	for(int i=1;i<=n;i++) add(dfn[i],dfn[i],dist[i]);
	cin>>q;
	while(q--){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1){
			int diff=y-qw[x],u=qu[x],v=qv[x];
			if(dfn[u]<dfn[v]) swap(u,v);
			add(nodel[u],noder[u],diff);
            qw[x]=y;
		}
		else{
			cout<<getdis(x,y)<<'\n'; 
		}
	}
	return 0;
}
```

---

## 作者：hcywoi (赞：0)

## 题意
给定一颗 $n$ 个节点的**带权无向**树。

给出 $q$ 个操作：
- `1 i w`：把第 $i$ 条边的边权变成 $w$。
- `2 u v`：求 $u\to v$ 简单路径的边权和。

## 解法

根据树上差分。
		
令 $p\to \textrm{lca}(x, y)$。
		
则 $u\to v$ 简单路径的边权和为 $d(u)+d(v)-2d(p)$。
		
详见 [oi-wiki](http://oi-wiki.com/basic/prefix-sum/)。

其中 $d(i)$ 表示 $i\to r$ 边权和的差分数组，$r$ 为根节点。

本题需要支持修改操作，我们可以用树状数组/线段树来维护 $d$。
		
具体的，对于无向边 $(u, v)$ **且 $u$ 为 $v$ 的儿子**，则我们发现只对以 $u$ 为根的这颗子树的 $d$ 有影响。
		
那么我们可以先求出 dfs 序，然后就转换成了区间加，单点查询，可以用树状数组/线段树维护。

时间复杂度：$\mathcal O(n\log n+q\log n)$。

[代码。](https://atcoder.jp/contests/abc294/submissions/39907482)

---

## 作者：FastingRabble (赞：0)

~~话说 g 明显比 f 好写啊！~~ 
# Solution:
树上带修改求两点间的距离。

因为是树形结构,即两点间的路径唯一确定,将其转换为链来处理。

记录一条链的 dfs 序,即是我们需对其维护的区间编号。

因为是单点修改,树状数组即可。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define open(x) freopen(x ".in", "r", stdin);freopen(x ".out", "w", stdout);
#define pb push_back
inline int read(){int f=1;int x=0;char c=getchar();while(c<'0'||c>'9'){if(c=='-'){f=-f;}c=getchar();}while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}return x*f;}
inline void wr(int x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
#define int long long
int f[1000050][25];
int t[1000050];
int ed[1000050];
int clo = 0;
int dep[1000050];
int dfn[1000005];
vector<int> a[1000050];
int eu[1000005] ,ev[1000005] , ew[1000005];
int n,m;

inline void dfs(int x,int fa){
	dep[x] = dep[fa] + 1;
	f[x][0] = fa;
	dfn[x] = ++clo; 
	for (int i=1; i<=17; ++i) f[x][i] = f[f[x][i-1]][i-1];
	for(auto v:a[x]){
		if(v == fa) continue;
		dfs(v,x);
	}
	ed[x] = clo;
	return;
}

inline void add(int x, int y){
	for (; x<=n; x+=x&-x) t[x]+=y;
}

inline int ask(int x){
	int y=0;
	for (; x; x-=x&-x) y+=t[x];
	return y;
}

inline int lca(int x,int y){
	if(x == y) return x;
	if(dep[x] < dep[y]){
		swap(x,y);
	}
	int d = dep[x] - dep[y];
	for(int i = 17 ;i >= 0 ; --i){
		if(d & (1 << i)) x = f[x][i];
	}
	if(x == y) return x;
	for(int i = 17 ;i >= 0 ; --i){
		if(f[x][i] != f[y][i]){
			x = f[x][i];
			y = f[y][i];
		}
	}
	return f[x][0];
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i < n; ++i){
		int x,y,z;
		cin >> x >> y >> z;
		a[x].pb(y);
		a[y].pb(x); 
		eu[i] = x;
		ev[i] = y;
		ew[i] = z;
	}
	cin >> m;
	dfs(1 , 0);
	for(int i = 1 ;  i < n ; ++i){
		if (dep[eu[i]]>dep[ev[i]]) swap(eu[i],ev[i]);
		add(dfn[ev[i]],ew[i]);
		add(ed[ev[i]]+1,-ew[i]);
	}
	for(int i = 1 ;i <= m ;++i){
		int x,y,z;
		cin >> x;
		if(x == 1){
			cin >> y >> z;
			add(dfn[ev[y]] , z - ew[y]);
			add(ed[ev[y]] + 1 , ew[y] - z);
			ew[y] = z;
		}
		else{
			cin >> y >> z;
			cout << ask(dfn[y]) + ask(dfn[z]) - ask(dfn[lca(z,y)]) * 2 << "\n";
		} 
	}
	return 0;
} 
```


---

## 作者：快乐的大童 (赞：0)

### 题目大意
给定 $n$ 个点的一棵树，每条树边有一个权值，现在给定 $q$ 次询问，每次询问有以下两种类型：

- `1 x y`：表示把编号为 $x$ 的边的权值修改为 $y$。
- `2 x y`：输出节点 $x$ 到节点 $y$ 的最短路径上的所有边的权值和。


$1\le n,q\le 2\times10^5,1\le$ 任意时刻边的权值 $\le 10^9$。

### 思路

考虑最暴力的数据结构——树剖。

众所周知，树剖板子所能处理的是点权，而这是边权。所以我们考虑将边权转化点权。

实际上只需要把这条边的边权赋给深度较大的那个点上即可，因为树上一个点只有一个父亲。

然后就是树上单点修改，链上查询的板子了。

>注意查询的时候要减去两点 LCA 的权值，因为 LCA 所代表的权值的所属边不在两点最短路径上。

~~当然你也可以像我一样用两点到根节点的权值和减去 LCA 到根节点的权值和的两倍来求答案，这样就不用特判 LCA 了。~~

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int R() {
	int x=0,f=1;
	int ch=getchar();
	while(!isdigit(ch)) {
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)) {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
inline void write(int x) {
	if(x<0) {
		x=-x;
		putchar('-');
	}
	int y=0;
	char z[70];
	while(x||!y) {
		z[y++]=x%10+48;
		x/=10;
	}
	while(y--)putchar(z[y]);
}
inline void writesp(int x) {
	write(x);
	putchar(32);
}
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define graph(i,j,l) for(int i=head[j];i;i=l[i].nxt)
const int N=2e5+5;
//树剖板子
namespace shupou {//英语水平实在有限qwq
	struct edge {
		int to, nxt;
	} a[N << 1];
	int head[N << 1], cnt;
	int n, m, w[N];
	int dep[N], fa[N], son[N], siz[N];
	int top[N], dfn[N], rk[N], val[N];
	void add(int x, int y) {
		cnt++;
		a[cnt].to = y;
		a[cnt].nxt = head[x];
		head[x] = cnt;
	}
	int d[N << 2], b[N << 2];

	int leftson(int x) {
		return x << 1;
	}
	int rightson(int x) {
		return x << 1 | 1;
	}
	void build(int l, int r, int p) {
		if (l == r) {
			d[p] = val[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, leftson(p));
		build(mid + 1, r, rightson(p));
		d[p] = (d[leftson(p)] + d[rightson(p)]);
	}

	void change(int x, int l, int r, int p, int k) {
		if (l==r) {
			d[p]=k;
			return;
		}
		int mid = (l + r) >> 1;
		if (x <= mid)
			change(x, l, mid, leftson(p), k);
		else
			change(x, mid + 1, r, rightson(p), k);
		d[p] = (d[leftson(p)] + d[rightson(p)]);
	}

	int getsum(int L, int R, int l, int r, int p) {
		if (L <= l && r <= R)
			return d[p];
		int mid = (l + r) >> 1, res = 0;
		if (L <= mid)
			res = (res + getsum(L, R, l, mid, leftson(p)));
		if (R > mid)
			res = (res + getsum(L, R, mid + 1, r, rightson(p)));
		return res;
	}

	void dfs1(int x, int y) {
		dep[x] = dep[y] + 1;
		fa[x] = y;
		siz[x] = 1;
		int tmp = 0;
		for (int i = head[x]; i; i = a[i].nxt) {
			int u = a[i].to;
			if (u == y)
				continue;
			dfs1(u, x);
			siz[x] += siz[u];
			if (siz[u] > tmp) {
				tmp = siz[u];
				son[x] = u;
			}
		}
	}

	void dfs2(int x, int root) {
		dfn[x] = ++cnt;
		val[dfn[x]] = w[x];
		top[x] = root;
		if (!son[x])
			return;
		dfs2(son[x], root);
		for (int i = head[x]; i; i = a[i].nxt) {
			int u = a[i].to;
			if (u == fa[x] || u == son[x])
				continue;
			dfs2(u, u);
		}
	}

	int query(int l, int r) {
		int res = 0;
		while (top[l] != top[r]) {
			if (dep[top[l]] < dep[top[r]])
				swap(l, r);
			res = (res + getsum(dfn[top[l]], dfn[l], 1, n, 1));
			l = fa[top[l]];
		}
		if (dep[l] > dep[r])
			swap(l, r);
		res = (res + getsum(dfn[l], dfn[r], 1, n, 1));
		return res;
	}
}
using namespace shupou;
//LCA板子
namespace LCA {
	int lg[N],f[N][25];
	void dfs(int x,int y) {
		f[x][0]=y;
		rep(i,1,lg[dep[x]]) f[x][i]=f[f[x][i-1]][i-1];
		graph(i,x,a) {
			int u=a[i].to;
			if(u==y) continue;
			dfs(u,x);
		}
	}
	int lca(int x,int y) {
		if(dep[x]<dep[y]) swap(x,y);
		while(dep[x]>dep[y]) x=f[x][lg[dep[x]-dep[y]]-1];
		if(x==y) return x;
		for(int i=lg[dep[x]]-1; i>=0; i--)
			if(f[x][i]!=f[y][i])
				x=f[x][i],y=f[y][i];
		return f[x][0];
	}
	void init() {
		rep(i,1,n) lg[i]=lg[i-1]+((1<<lg[i-1])==i?1:0);
		dfs(1,0);
	}
} using namespace LCA;
int q,u[N],v[N],vv[N];
void solve_the_problem() {
	n=R();
	rep(i,1,n-1) {
		u[i]=R(),v[i]=R(),vv[i]=R();
		add(u[i],v[i]);
		add(v[i],u[i]);
	}
	cnt=0;
	dfs1(1,0);
	rep(i,1,n-1) {
		int ret=(dep[u[i]]>dep[v[i]])?u[i]:v[i];
		w[ret]=vv[i];//这里提前赋点权，为了迎合树剖板子
	}
	dfs2(1,1);
	build(1,n,1);
	init();
	q=R();
	rep(_,1,q) {
		int op=R(),l=R(),r=R();
		if(op==1) {
			int ret=(dep[u[l]]>dep[v[l]])?u[l]:v[l];
			change(dfn[ret],1,n,1,r);
		} else {
			writeln(query(1,l)+query(1,r)-query(1,lca(l,r))*2);
		}
	}
}
signed main() {
	int _=1;
	while(_--)solve_the_problem();
}

```


---

