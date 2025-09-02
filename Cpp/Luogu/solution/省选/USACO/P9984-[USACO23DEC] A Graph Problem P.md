# [USACO23DEC] A Graph Problem P

## 题目描述

为了丰富自己的数学知识，Bessie 选修了一门图论课程，她发现她被下面的问题困住了，请帮帮她！

给出一张连通的无向图，包含编号为 $1\dots N$ 的节点和编号为 $1\dots M$（$2 \le N \le 2\cdot 10^5$，$N - 1 \le M \le 4 \cdot 10^5$）的边，下边的操作将被实施：

1. 假设集合 $S=\{v\}$，变量 $h=0$。
2. 当 $|S|<N$，重复执行：
	1. 仅有一个顶点在集合 $S$ 中的边中，找到编号最小的那条，编号记为 $e$。
    2. 将 $e$ 不在 $S$ 中的那个顶点加入集合 $S$。
    3. 将 $h$ 修改为 $10h+e$。
3. 返回 $h$ 对 $10^9+7$ 取模的值。

输出这个过程的全部返回值。

## 说明/提示

### 样例解释 2

考虑在 $i=3$ 开始执行。首先，选择 $2$ 号边，$S=\{3,4\}$，$h=2$。然后，选择 $3$ 号边，$S=\{2,3,4\}$，$h=23$。接着，选择 $1$ 号边，$S=\{1,2,3,4\}$，$h=231$。最后，选择 $5$ 号边，$S=\{1,2,3,4,5\}$，$h=2315$。因此，$i=3$ 的答案是 $2315$。

### 样例解释 3

确保答案对 $10^9+7$ 取模。

### 测试点性质

- 测试点 $4$ 满足 $N,M \le 2000$。
- 测试点 $5-6$ 满足 $N \le 2000$。
- 测试点 $7-10$ 满足 $N \le 10000$。
- 测试点 $11-14$ 满足对于所有边，有 $a_e+1=b_e$。
- 测试点 $15-23$ 没有额外限制。

## 样例 #1

### 输入

```
3 2
1 2
2 3```

### 输出

```
12
12
21```

## 样例 #2

### 输入

```
5 6
1 2
3 4
2 4
2 3
2 5
1 5```

### 输出

```
1325
1325
2315
2315
5132```

## 样例 #3

### 输入

```
15 14
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
14 15```

### 输出

```
678925929
678925929
678862929
678787329
678709839
678632097
178554320
218476543
321398766
431520989
542453212
653475435
764507558
875540761
986574081```

# 题解

## 作者：I_am_Accepted (赞：10)

按边的出现顺序建 Kruskal 重构树，一条边连接两个连通块对一个点的答案会发生：先走完其连通块内的所有边，再走这条边，再以这条边的端点为起点走另一个连通块。

也就是这个点更新后的答案为原先答案、这条边、对面端点答案三者顺次拼接。

发现把 Kruskal 树平摊后就是线段树维护区间加乘。

复杂度 $O(n\log n)$，赛时写的这个。

但是我们可以更简单一点，Kruskal 树构建的时候并查集我们带上权值，代表加乘 tag，操作顺序从底向上，此信息支持路径压缩。

这样在一条边连接两个连通块时先得到两个端点的答案，再用这两个值求出并查集两条边的边权即可。

这里能用并查集的原因是打 tag 都是对 Kruskal 树的整棵子树打 tag（所以平摊到序列强化了问题），而且顺序是由叶子向根（平摊到序列则被包含的区间 tag 时刻一定在包含的之前）。

并查集复杂度。

```cpp
using Z=mod_int<P>;
const int N=200010;
int f[N<<1],sz[N<<1],tot,n,m;
Z pw[N];
struct node{
	Z mul,ad;
	node operator+(const node&v)const{ return node{mul*v.mul,ad*v.mul+v.ad}; }
}g[N<<1];
void gf(int x){
	if(x==f[x]) return ;
	gf(f[x]);
	g[x]=g[x]+g[f[x]];
	f[x]=f[f[x]];
}
signed main(){ios::sync_with_stdio(false),cin.tie(nullptr);
    cin>>n>>m;
    tot=n;
    pw[0]=1;
    rep(i,1,n) pw[i]=pw[i-1]*10;
    iota(f+1,f+2*n,1);
    fill(g+1,g+2*n,node{1,0});
    rep(i,1,m){
    	int x,y;
    	cin>>x>>y;
    	gf(x),gf(y);
    	if(f[x]!=f[y]){
    		node xx=g[x],yy=g[y],zz={10,i};
    		g[f[x]]=zz+yy;
    		g[f[y]]=zz+xx;
    		f[f[x]]=f[f[y]]=++tot;
    	}
    }
    rep(i,1,n){
    	gf(i);
    	cout<<g[i].ad<<"\n";
    }
return 0;}
```

---

## 作者：Purslane (赞：8)

# Solution

赛时竟然不会这种萌萌题。

考虑每个时刻，集合 $S$ 必然是一个连通块，而且这个连通块必然在对整个图跑 Kruskal 求最小生成树的过程中出现过。

换句话说，我们实际上就是对整个图进行 Kruskal，然后每次合并两个连通块 $S_1$ 和 $S_2$，考虑 $u \in S_1$，他的过程实际上是这样的：

1. 在自身连通块 $S_1$ 中发育。在他填满 $S_1$ 之前，他不会找 $S_1$ 外的一个点，否则在进行 Kruskal 的过程中那个点与 $S_1$ 连的边会更早被考虑。
2. 发育到 $S_2$ 中。我们惊奇的发现，所有的 $u$ 他接触的第一个 $S_2$ 中的节点都是一样的，我们设为 $v$。
3. 在 $S_2$ 中发育。和第一种情况类似，接下来我们会从 $v$ 开始往后发育。而这样的发育过程必定和 $v$ 最开始发育的过程是一样的，原因依旧是 $S_1$ 到 $S_2$ 所有点的边都比 $v$ 到他们的小，因此可以直接利用 $v$ 的答案。

于是 $u$ 中每个点的答案会变成 $ans'_u=(10ans_u+id) \times 10^{|S_2|-1} + ans_v$。

然后你发现你只需要能维护一大堆东西乘、加、单点查询。用 Kruskal 重构树把它变成连续段就可以用线段树 2 了。

> 为啥用发育这个词。因为我觉得这个过程，很像，generals。

好像是最劣解（截止 2023-12-29）。无所谓，反正人傻常数大。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--) 
using namespace std;
const int MAXN=4e5+10,MAXM=4e5+10,MOD=1e9+7;
int n,m,pw[MAXN],sze[MAXN],u[MAXM],v[MAXM],fa[MAXN],lson[MAXM],rson[MAXM],rt[MAXN],tot,dfn[MAXN],cnt,lid[MAXN],rid[MAXN];
int find(int k) {return (fa[k]==k)?k:(fa[k]=find(fa[k]));}
void dfs(int u) {
	if(u<=n) return dfn[u]=++cnt,void();	
	dfs(lson[u]),dfs(rson[u]);
	return ;
}
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
int res[MAXN<<2],mul[MAXN<<2],add[MAXN<<2];
void add_tag(int k,int l,int r,int Mul,int Add) {
	res[k]=(res[k]*Mul%MOD+(r-l+1)*Add%MOD)%MOD;
	mul[k]=mul[k]*Mul%MOD;
	add[k]=(add[k]*Mul+Add)%MOD;
	return ;
}
void push_down(int k,int l,int r) {
	add_tag(lson,l,mid,mul[k],add[k]),add_tag(rson,mid+1,r,mul[k],add[k]);
	mul[k]=1,add[k]=0;
	return ;	
}
void update(int k,int l,int r,int x,int y,int Mul,int Add) {
	if(x<=l&&r<=y) return add_tag(k,l,r,Mul,Add),void();
	push_down(k,l,r);
	if(x<=mid) update(lson,l,mid,x,y,Mul,Add);
	if(y>mid) update(rson,mid+1,r,x,y,Mul,Add);
	res[k]=(res[lson]+res[rson])%MOD;
	return ;
}
int query(int k,int l,int r,int pos) {
	if(l==r) return res[k];
	push_down(k,l,r);
	if(pos<=mid) return query(lson,l,mid,pos);
	return query(rson,mid+1,r,pos);	
}
#undef lson
#undef rson
#undef mid
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m; ffor(i,1,n) fa[i]=i,rt[i]=i; tot=n;
	pw[0]=1; ffor(i,1,n) pw[i]=pw[i-1]*10%MOD;
	ffor(i,1,m) cin>>u[i]>>v[i];
	ffor(i,1,m) if(find(u[i])!=find(v[i])) {
		int U=find(u[i]),V=find(v[i]);
		++tot,lson[tot]=rt[U],rson[tot]=rt[V],fa[V]=U,rt[U]=tot;	
	}
	dfs(tot);
	ffor(i,1,(n<<2)) mul[i]=1;
	ffor(i,1,n) fa[i]=i,sze[i]=1,lid[i]=rid[i]=dfn[i];
	ffor(i,1,m) if(find(u[i])!=find(v[i])) {
		int U=find(u[i]),V=find(v[i]);
		int oril=query(1,1,n,dfn[u[i]]),orir=query(1,1,n,dfn[v[i]]);
		update(1,1,n,min(lid[U],lid[U]),max(rid[U],rid[V]),10,i);
		update(1,1,n,lid[U],rid[U],pw[sze[V]-1],orir);
		update(1,1,n,lid[V],rid[V],pw[sze[U]-1],oril);
		fa[V]=U,lid[U]=min(lid[U],lid[V]),rid[U]=max(rid[U],rid[V]),sze[U]+=sze[V];
	}
	ffor(i,1,n) cout<<query(1,1,n,dfn[i])<<'\n';
	return 0;
}
```

---

## 作者：Leasier (赞：4)

注意到题给过程实际上就是 **Prim**。

但 Prim 不太方便我们讨论，考虑更为常见的 **Kruskal**。

Kruskal 的过程即按边权从小到大加边，每次合并两个联通块。

考虑建出重构树，设编号为 $i$ 的边 $(u, v)$ 导致了当前的合并：

- 对于 $u$ 所在联通块内的点，其序列在原有基础上加上 $i$，再加上 $v$ 在其联通块内的序列。
- 对于 $v$ 所在联通块内的点，其序列在原有基础上加上 $i$，再加上 $u$ 在其联通块内的序列。

所谓“序列拼接”操作，其本质是给所求的 hash 值乘 $k$ 加 $b$。这样的标记具有结合律，且是容易合并的。

于是我们在并查集的**边**上打标记，路径压缩时合并标记即可，这样我们也可以做到动态查询 $u, v$ 原有序列的 hash 值。

时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

typedef struct Info_tag {
	ll k;
	ll b;
	Info_tag(){}
	Info_tag(ll k_, ll b_){
		k = k_;
		b = b_;
	}
} Info;

const int mod = 1e9 + 7;
int root[400007];
Info info[400007];

Info operator +(const Info a, const Info b){
	return Info(a.k * b.k % mod, (a.b * b.k % mod + b.b) % mod);
}

void operator +=(Info &a, const Info b){
	a = a + b;
}

inline void init(int n, int m){
	for (int i = 1; i <= n; i++){
		root[i] = i;
		info[i] = Info(1, 0);
	}
}

int get_root(int x){
	if (root[x] == x) return x;
	int ans = get_root(root[x]);
	info[x] += info[root[x]];
	return root[x] = ans;
}

int main(){
	int n, m, id;
	scanf("%d %d", &n, &m);
	id = n;
	init(n * 2 - 1, n - 1);
	for (int i = 1; i <= m; i++){
		int u, v, root_u, root_v;
		scanf("%d %d", &u, &v);
		root_u = get_root(u);
		root_v = get_root(v);
		if (root_u != root_v){
			Info cur(10, i), p = info[v], q = info[u];
			root[root_u] = root[root_v] = ++id;
			info[root_u] = cur + p;
			info[root_v] = cur + q;
		}
	}
	for (int i = 1; i <= n; i++){
		get_root(i);
		printf("%lld\n", info[i].b);
	}
	return 0;
}
```

---

## 作者：Harry27182 (赞：2)

有趣的小清新数据结构题。

首先考虑这个合并每次找到最小的边的过程很类似于 Kruskal 最小生成树的合并过程，只不过每次是钦定了合并一个大联通块和一个点。由于需要从不同的起点开始考虑，也就是需要多次处理这个类似 Kruskal 的过程，自然想到 Kruskal 重构树。我们考虑建出 Kruskal 重构树，下面考虑如何在这个过程中维护出从每个点开始出发，合并到目前的答案。

考虑一次合并两个联通块的过程，我们合并两个联通块，相当于从这两个联通块中伸出来边权最小的边就是当前这条边了，也就是说，以这两个联通块内部的任何一个点为起点，合并完子树之后下一条合并的边自然就是这条边，再接下来合并的边就是另一个子树内以这条边的另一个端点为起点需要合并的边。发现这种操作对于整一个子树内需要进行的处理是相同的，所以可以想到线段树来维护区间操作。我们每次取出从这条边两个节点出发这个子树内部的答案，然后把这些操作和当前这条边的贡献挂到另一棵子树上。下面来考虑如何用一个支持快速合并的 tag 来维护这种操作。

考虑维护一个 pair $(mul,add)$ 表示如果初始值为 $x$，经过这个 tag 之后的值是 $mul*x+add$。那么两个 tag 的合并是容易的，具体来说设两个 tag 分别为 $(mul1,add1)(mul2,add2)$，那么新的 tag 就是 $(mul1*mul2,add1*mul2+add2)$，所以就解决了上述信息的快速维护，然后直接用线段树维护这个 tag 就做完了。

写代码的时候注意区分原图中的点和建出 kruskal 重构树上的点编号和编号的 dfs 序，不要写混了。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int mul,add;}tr[2000005];
struct edge{int v,nxt;}E[2000005];
struct edge2{int u,v,w;}e[2000005],g[2000005];
int cnt,h[1000005],fa[1000005],ls[1000005],rs[1000005],n,m,tot;
bool cmp(edge2 x,edge2 y){return x.w<y.w;}
const int mod=1000000007;
void add(int u,int v){E[++cnt]={v,h[u]};h[u]=cnt;}
int find(int x){return (x==fa[x]?x:fa[x]=find(fa[x]));}
node operator *(node x,node y){return {1ll*x.mul*y.mul%mod,(1ll*x.add*y.mul%mod+y.add)%mod};}
void dfs(int u)
{
	if(u<=n){ls[u]=rs[u]=++tot;return;}
	ls[u]=0x3f3f3f3f;rs[u]=0;
	for(int i=h[u];i;i=E[i].nxt)
	{
		int v=E[i].v;dfs(v);
		ls[u]=min(ls[u],ls[v]);rs[u]=max(rs[u],rs[v]);
	}
}
void update(int k,node x){tr[k]=tr[k]*x;}
void pushdown(int k)
{
	update(k<<1,tr[k]);update(k<<1|1,tr[k]);
	tr[k]={1,0}; 
}
void build(int k,int l,int r)
{
	tr[k]={1,0};
	if(l==r)return;
	int mid=(l+r)>>1;
	build(k<<1,l,mid);build(k<<1|1,mid+1,r);
}
void change(int k,int l,int r,int x,int y,node v)
{
	if(x<=l&&r<=y){update(k,v);return;}
	int mid=(l+r)>>1;pushdown(k);
	if(x<=mid)change(k<<1,l,mid,x,y,v);
	if(y>mid)change(k<<1|1,mid+1,r,x,y,v);
}
node query(int k,int l,int r,int x)
{
	if(l==r)return tr[k];
	int mid=(l+r)>>1;pushdown(k);
	if(x<=mid)return query(k<<1,l,mid,x);
	else return query(k<<1|1,mid+1,r,x);
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++)cin>>e[i].u>>e[i].v,e[i].w=i;
    sort(e+1,e+m+1,cmp);
    for(int i=1;i<=n+n;i++)fa[i]=i;
    for(int i=1;i<=m;i++)
    {
    	int u=find(e[i].u),v=find(e[i].v);
    	if(u==v)continue;
    	g[++tot]=e[i];fa[u]=fa[v]=tot+n;add(tot+n,u);add(tot+n,v);
	}
	tot=0;dfs(2*n-1);build(1,1,n);
	for(int i=1;i<=n+n;i++)fa[i]=i;
	for(int i=1;i<n;i++)
	{
		int u=find(g[i].u),v=find(g[i].v);
		node wu=query(1,1,n,ls[g[i].u]),wv=query(1,1,n,ls[g[i].v]);
		fa[u]=fa[v]=i+n;
		wu=node{10,g[i].w}*wu;wv=node{10,g[i].w}*wv;
		change(1,1,n,ls[v],rs[v],wu);
		change(1,1,n,ls[u],rs[u],wv);
	}
	for(int i=1;i<=n;i++)
	{
		node now=query(1,1,n,ls[i]);
		cout<<now.add<<'\n';
	}
	return 0;
}

```

---

## 作者：Petit_Souris (赞：1)

感觉一上来就想着建 Kruskal 重构树，再上线段树不是什么很自然的想法。讲一下我是怎么从零开始想到整道题的做法的。

首先发现最终得到的子图为一棵树，且一定是最小生成树，否则可以替换一条边，找到一个环，环上最大边加入时一定有一条边更小，矛盾。

正着做是不好做的，感觉无论如何都得对每个点维护现在的状态，怎么也是平方的。我们不妨试着反过来考虑：比如先考虑最终状态前的最后一条边，一定是最小生成树上最大的那条边。设两端为 $(x,y)$，那么 $x$ 那一侧的点一定是在 $x$ 内部全部走完了，经过 $(x,y)$ 这条边，再从 $y$ 开始遍历整个 $y$ 一侧。

观察到这个过程中走到 $y$ 之后的顺序就和起点无关了，因为都是从 $y$ 开始的。这时候我们需要维护的信息量就可以压缩了：我们合并 $x,y$ 实际上就是在 $x$ 所在连通块所有点的序列末尾加入 $(x,y)$ 这条边，再加入 $y$ 开始遍历 $y$ 所在连通块的序列。这就不需要维护整个序列了，维护哈希即可。这个操作可以表示为 $x\to x\times 10^a+b$ 的形式。

因此我们对每个连通块都维护这个 $(a,b)$ 的懒标记，从小到大加入所有边。每次合并的时候，考虑启发式合并，重构较小的连通块。由于模数为质数，因此标记可逆，我们可以把较小连通块的哈希值统一成较大连通块的标记值。因此复杂度为启发式合并的 $\mathcal O(n\log n)$，可以通过。

可以看到我们的思路虽然是倒过来的，但是最后做法还是正着做的。感觉比凭空冒出来一个 Kruskal 重构树靠谱一点，供大家参考。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=1e6+9,Mod=1e9+7;
ll n,m,U[N],V[N];
ll fa[N],sz[N],f[N],tag1[N],tag2[N];
ll pw10[N],ipw10[N];
vector<ll>vec[N];
ll pw(ll x,ll p){
    ll res=1;
    while(p){
        if(p&1)res=res*x%Mod;
        x=x*x%Mod,p>>=1;
    }
    return res;
}
ll find(ll x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),m=read();
    rep(i,1,m)U[i]=read(),V[i]=read();
    iota(fa+1,fa+n+1,1ll),fill(sz+1,sz+n+1,1ll);
    rep(i,1,n)vec[i].push_back(i);
    pw10[0]=1;
    rep(i,1,n)pw10[i]=pw10[i-1]*10%Mod;
    ipw10[0]=1,ipw10[1]=pw(10,Mod-2);
    rep(i,2,n)ipw10[i]=ipw10[i-1]*ipw10[1]%Mod;
    rep(i,1,m){
        ll u=U[i],v=V[i],fu=find(U[i]),fv=find(V[i]);
        if(fu==fv)continue;
        if(sz[fu]>sz[fv])swap(fu,fv),swap(u,v);
        ll u1=tag1[fu]+sz[fv];
        ll u2=(tag2[fu]*pw10[sz[fv]]+i*pw10[sz[fv]-1]+(f[v]*pw10[tag1[fv]]+tag2[fv]))%Mod;
        ll v1=sz[fu]+tag1[fv];
        ll v2=(tag2[fv]*pw10[sz[fu]]+i*pw10[sz[fu]-1]+(f[u]*pw10[tag1[fu]]+tag2[fu]))%Mod;
        tag1[fu]=u1,tag2[fu]=u2,tag1[fv]=v1,tag2[fv]=v2;
        for(ll x:vec[fu]){
            ll rf=(f[x]*pw10[tag1[fu]]+tag2[fu])%Mod;
            rf=(rf-tag2[fv]+Mod)*ipw10[tag1[fv]]%Mod;
            f[x]=rf,vec[fv].push_back(x);
        }
        sz[fv]+=sz[fu],fa[fu]=fv;
    }
    rep(i,1,n)write((f[i]*pw10[tag1[find(i)]]+tag2[find(i)])%Mod),putchar('\n');
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：IamZZ (赞：1)

**P组练习总结#8**

**Benq** 出的图论题，本来看着 **Benq** 的名字下意识想跑（不是），仔细想想，好像还可以做~~实际上是第一第三题不可能自己想出来才来的~~。

stO **Benq** Orz

### 题目大意

Bessie 正在学图论！

给你一个 $n(n\leq2\times10^5)$ 个点的联通图，由 $m(n-1\leq m\leq4\times10^5)$ 条无向边连接，标号 $1\dots m$。

现在我们进行 $n$ 次操作，第 $i$ 次操作一开始有一个点集 $S$，点集一开始只有 $i$。

现在从所有一个端点在点集中而另一个不在的边中找到编号最小的 $e$ 号边，把 $e$ 在 $S$ 外的端点加入 $S$。

同时，我们记录一个值 $h_i$，初始为 0，$h_i=h_i\times10+e$，$h_i$ 对 $10^9+7$ 取模。

重复这个过程一直到所有的点都加入了 $S$。最后对于每个 $i$，输出最终的 $h_i$。

### 解题思路（部分分）

从部分分开始想，先想出关键的一些性质和条件。

首先，把选择的边连起来，最后的图应满足什么性质？是一棵树。

对于每一个 $i$，最后选择的边应该全部是相同的，也就是说，这棵树的形态对于每一个 $i$ 是一样的。

而且，这棵树是这个图的最小生成树（设边长等于编号）！

因为，这个过程，不就是最小生成树算法 Prim？那建出来的树自然是 MST 啦。

哇，这个性质很美妙，一下子我们可以快速确定最后这棵树有哪些边了。

朴素的方法已经出来了，我们对于每个点跑一遍 Prim 算法，正常的 Prim 复杂度 $\Theta(n^2)$，优化后 $\Theta(n\log_2n)$，加上枚举点，总复杂度 $\Theta(n^2\log_2n)$。

就暴力来说，这也不够优秀，部分分都没有骗完，而且对于正解帮助不大。

我们思考的时候不应该仅仅局限在 Prim，不然就被出题人局限了，除了 Prim，大多数人可能更熟悉 Kruskal，它同样可以建 MST。

我们考虑 Kruskal 的过程中，每一个点的答案：

假设现在我们要加入 $(a_i,b_i)$ 这一条边，对于 $a_i$ 目前所在的连通块，里面的任何一个点肯定会先遍历完这个连通块，因为这里面的边都比 $(a_i,b_i)$ 小。

然后跨过 $(a_i,b_i)$ 到达 $b_i$，从 $b_i$ 开始遍历 $b_i$ 的连通块，因为这边的边也是先前加进来的，应该先跑一遍。

从 $b_i$ 开始遍历……这不就是当前 $b_i$ 的答案吗？

是的！我们设 $s_i$ 为 $i$ 连通块的大小，对于每一个属于 $a_i$ 连通块的点 $p$，$h_p=(10h_p+i)\times10^{s_{b_i}-1}+h_{b_i}$，注意是 $s_{b_i}-1$，因为边数比点数少一。

对于 $b_i$ 连通块内的点，答案处理方式类似的。随着我们不断加边，我们也处理了每一个点的答案。

时间复杂度 $\Theta(n^2+m\alpha(n))$，可通过更多的测试点。

### 参考代码（部分分）

看看代码？想到这一步了，正解已经呼之欲出了！

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,d=1e9+7;
int n,m,x,y,c,f[N],_x,_y,a,b,g[N]={1},h[N],s[N];
struct edge
{
	int t,e,h;
}e[N<<1];
void add(int u,int v)
{
	++c;
	e[c].t=v;
	e[c].e=e[u].h;
	e[u].h=c;
	return ;
}
int find(int p)//kruskal 判断是否连通
{
	if(f[p]^p)
	  f[p]=find(f[p]);
	return f[p];
}
void modify(int p,int fa,int w,int v,int l)
{
	int i;
	h[p]=(10ll*h[p]%d+w)%d;//一定是先经过i号边
	h[p]=(1ll*h[p]*l%d+v)%d;//加入对面端点的答案
	for(i=e[p].h;i;i=e[i].e)
	{
		if(e[i].t==fa)
		  continue;
		modify(e[i].t,p,w,v,l);
	}
	return ;
}
int main()
{
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)
	  f[i]=i,g[i]=10ll*g[i-1]%d,s[i]=1;//处理了10的阶乘
	for(i=1;i<=m;++i)
	{
		scanf("%d%d",&x,&y);
		_x=find(x);
		_y=find(y);
		if(_x==_y)//基本kruskal
		  continue;
		a=h[x],b=h[y];//因为可能中途被更改，要记下来
		modify(y,0,i,a,g[s[_x]-1]);
		modify(x,0,i,b,g[s[_y]-1]);
		add(x,y),add(y,x);//选取了就连上边
		f[_y]=_x;//并查集同步
		s[_x]=s[_x]+s[_y];
	}
	for(i=1;i<=n;++i)
	  printf("%d\n",h[i]);
	return 0;
}
```

### 解题思路（正解）

基本的思路已经有了，处理的方式也比较优秀了。

瓶颈在于，我们仍然需要遍历两个连通块来更新答案，会使复杂度无法支持。

合并两个连通块？合并……合并，启发式合并！

没错，我们考虑用启发式合并来解决合并问题，可以把 $\Theta(n)$ 的遍历复杂度降到均摊 $\Theta(\log_2n)$。

我们发现，对于一条边一侧的连通块，答案的处理是一样的，这提示我们应该要用**懒标记**来解决这个问题。

可是，一个懒标记只能记录整个连通块的信息，而两个即将合并的连通块，处理方式却不一样。合并了之后，答案不会算错吗？

这就要体现这道题的一个性质了，答案处理的过程，是有可逆的！

我们先把集合内的元素用 vector 记下来，把较小的那个集合的懒标记下发，并将答案更新。

这时，我们可以对这些答案用合并后的懒标记**逆处理**一下，这样，当懒标记下发的时候，相当于被这次操作抵消了，我们仍然保留了正确的答案。

之后的启发式合并把小的并入大的就好啦。

具体的实现可以参考代码，时间复杂度 $\Theta(n\log_2n+m\alpha(n))$，完结撒花(●'◡'●)！

### 参考代码（正解）

注释尽量多打了，应该可以看懂吧(¬_¬ )？

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,d=1e9+7;
int n,m,x,y,f[N],_x,_y,a,b,g[N]={1},h[N],tz[N],dz[N],ig[N]={1},iv,o;//两个懒标记，tz[i]表示当前连通块要乘的值，dz[i]表示加的值
vector<int>p[N];
int find(int p)
{
	if(f[p]^p)
	  f[p]=find(f[p]);
	return f[p];
}
int quickpow(int b,int p)
{
	int w=1;
	while(p)
	{
		if(p&1)
		  w=1ll*w*b%d;
		b=1ll*b*b%d;
		p=p>>1;
	}
	return w;
}
int main()
{
	int i,j;
	scanf("%d%d",&n,&m);
	iv=quickpow(10,d-2);
	for(i=1;i<=n;++i)
	{
		tz[i]=1,f[i]=i;//乘法懒标记先设为1
		g[i]=10ll*g[i-1]%d,ig[i]=1ll*ig[i-1]*iv%d;//10的阶乘和10的逆元的阶乘
		p[i].push_back(i);//扔进vector
	}
	for(i=1;i<=m;++i)
	{
		scanf("%d%d",&x,&y);
		_x=find(x);
		_y=find(y);
		if(_x==_y)
		  continue;
		if(p[_x].size()<p[_y].size())//启发式合并比大小
		  swap(_x,_y),swap(x,y);//交换为x大y小
		a=(1ll*h[x]*tz[_x]%d+dz[_x])%d;//a是x给y的答案贡献
        b=(1ll*h[y]*tz[_y]%d+dz[_y])%d;//b是y给x的答案贡献
		a=(a+1ll*i*g[p[_x].size()-1]%d)%d;//别忘了这一条边的贡献
        b=(b+1ll*i*g[p[_y].size()-1]%d)%d;
        //懒标记打在并查集根上
		tz[_x]=1ll*tz[_x]*g[p[_y].size()]%d;//处理新的连通块的懒标记，乘法先来
		dz[_x]=(1ll*dz[_x]*g[p[_y].size()]%d+b)%d;//加法先乘后加
		for(j=0;j<p[_y].size();++j)
		{
			o=p[_y][j];
			h[o]=(1ll*h[o]*tz[_y]%d+dz[_y])%d;//懒标记下发
			h[o]=(1ll*h[o]*g[p[_x].size()]%d+a)%d;//把x的贡献拿来
			h[o]=1ll*(h[o]-dz[_x]+d)*ig[p[_x].size()+p[_y].size()-1]%d;//逆处理，先减再除（乘逆元）
		}
		for(j=0;j<p[_y].size();++j)
		  p[_x].push_back(p[_y][j]);//更新连通块，y加入x
		f[_y]=_x;//并查集更新
	}
	for(i=1;i<=n;++i)
	  printf("%d\n",(1ll*h[i]*tz[find(i)]%d+dz[find(i)])%d);//懒标记下发后的答案
	return 0;
}
```



---

## 作者：Hanghang (赞：1)

牛牛牛题

小 H 在不清醒 3h 后，意识到他会做了，很快地写完了，因为些神秘细节导致最后 ```2s``` 提交，因为 ``define int long long`` 以及不写光速幂，遗憾败北。

回到正题，把标号看成权值，那么我们只会选择最小生成树上的边，原因显然。

注意到维护的这个值就是一个固定 ```base``` 的哈希值，我们转而来维护哈希。

先看到链的部分分，感觉，非常的有趣，这种跟最大最小有关的大概率也就那几种，扫描线+单调栈，最值分治，以及小 H 想了很久才意识到的克鲁斯卡尔重构树。

具体而言，按照权值从小到大加边，每次合并两颗子树，维护每个点实时的哈希值，具体意义为这个点为起点遍历整个连通块的代价。设当前边为 $(x,y)$ ，权值为 $z$ ，我们先将两颗子树末尾加入 $z$ ，然后再互相加即可。

注意：线段树需要支持的是区间哈希值后面叠加哈希，单点查询，单点查询那么也就不需要 ```pushup``` 这样可以预处理 ```10``` 的幂不用写光速幂（不要问我怎么知道的）

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N=4e5+3,H=1e9+7;
int n,m,tim,f[N],val[N],st[N],ed[N],pos[N],dfn[N],ch[N][2];
ll pw[N];
int F(int x){return f[x]==x?x:f[x]=F(f[x]);}
struct Nod{int x,y;}a[N];
void Dfs(int x)
{
	st[x]=tim+1;
	if(!ch[x][0])tim++,pos[x]=tim,dfn[tim]=x;
	else Dfs(ch[x][0]),Dfs(ch[x][1]);
	ed[x]=tim;
}
struct Tree
{
	ll val,len;
	friend Tree operator +(Tree a,Tree b)
	{
		return {(a.val*pw[b.len]+b.val)%H,a.len+b.len};
	}
}tr[N*4],tag[N*4];
struct SegmentTree
{
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define mi ((l+r)>>1)
	void Up(int p){tr[p]=tr[ls]+tr[rs];}
	void Add(int p,Tree d){tr[p]=tr[p]+d;tag[p]=tag[p]+d;}
	void Down(int p){Add(ls,tag[p]);Add(rs,tag[p]);tag[p].val=tag[p].len=0;}
	void Upd(int L,int R,int p,int l,int r,Tree d)
	{
		if(L<=l&&r<=R){Add(p,d);return;}
		Down(p);
		if(L<=mi)Upd(L,R,ls,l,mi,d);
		if(R>mi)Upd(L,R,rs,mi+1,r,d);
	}
	Tree Ask(int k,int p,int l,int r)
	{
		if(l==r)return tr[p];
		Down(p);
		return k<=mi?Ask(k,ls,l,mi):Ask(k,rs,mi+1,r); 
	}
}T; 
int main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;ll tot=n;pw[0]=1;
	for(int i=1;i<N;i++)pw[i]=pw[i-1]*10%H;
	for(int i=1;i<=2*n;i++)f[i]=i;
	for(int i=1;i<=m;i++)cin>>a[i].x>>a[i].y;
	for(int i=1;i<=m;i++)
	{
		int x=F(a[i].x),y=F(a[i].y);
		if(F(x)==F(y))continue;
		f[x]=f[y]=++tot;val[tot]=i;
		ch[tot][0]=x;ch[tot][1]=y;
	}
	Dfs(tot);
	for(int i=n+1;i<=tot;i++)
	{
		Tree px=T.Ask(pos[a[val[i]].x],1,1,n),py=T.Ask(pos[a[val[i]].y],1,1,n);
		T.Upd(st[i],ed[i],1,1,n,{val[i],1});
		T.Upd(st[ch[i][0]],ed[ch[i][0]],1,1,n,py);
		T.Upd(st[ch[i][1]],ed[ch[i][1]],1,1,n,px);
	}
	for(int i=1;i<=n;i++)cout<<T.Ask(pos[i],1,1,n).val<<'\n'; 
}
```



---

## 作者：Little_Cancel_Sunny (赞：0)

# P9984 [USACO23DEC] A Graph Problem

题意不用多解释。

## 思路

首先先转化一下它的操作，我们认为每条边的权值为输入时的编号，就不难发现它的过程实际上是在进行 Prim 算法。

但是显然直接模拟是 $O(NM)$ 的，不行，需要快速维护增加权值操作。

然而 Prim 算法不太好操作，于是选用 Kurskal 算法实现它的操作。主要是因为 Prim 算法是依据每个点连出的最小权值维护的，很难优化权值增加操作，而 Kurskal 算法有其特有的重构树，然后就可以将操作转移到树上。

接下来考虑什么时候更改，怎样加速更改，显然在一个线段的两端不在同一个连通块时我们更改。

在建出重构树之后，我们需要的点的信息都在叶子节点上，并且不难发现一棵子树与另外一棵子树合并时，都是每颗子树先加上边权，在加上另外一棵子树相连点的权值，有点抽象，画个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/f2nbiwxv.png)

好的，不难发现两棵子树合并时，设边的其中一点为 $v$ 对另外一棵子树每一个叶子节点 $u$ 的贡献就为： 

$$
val[u]=(siz[v]-1)(10 \cdot val[u] + w)+val[v]
$$ 

可以发现无论对两个子树的哪两个连边，其对另外一棵子树的每一个叶子节点的贡献都是一定的。

简单说明一下，因为从一棵子树中的每个点走出该子树时，进入另外一棵子树所走的路径都是一样的，所以贡献是一定的。

子树信息，子树乘，子树加，一个 dfs 序加上线段树不就搞定了吗？

## 代码实现

还是注意细节，先乘后加。

但是聪明的小朋友就会发现 $O(2N \log 2N)$ 加上中间那么多查询，加上线段树大常数，不会 TLE 吗？

![](https://cdn.luogu.com.cn/upload/image_hosting/l79xg0jv.png)

不是，那线段树有什么用，又过不了，别急，至少理论上是正确的，所以，**开始卡常！**

首先面对取模运算，直接变为减法运算。

其次注意空间，不要大量使用 long long，只在需要的地方用即可。

当然 $10^n$ 预处理就好了，不要写快速幂。

少用结构体，函数加 inline，别忘加快读。

最后自然就卡过去了。

![](https://cdn.luogu.com.cn/upload/image_hosting/dz94m1ub.png)

~~喜提最劣解~~

上代码，由于卡过常，所以十分丑陋，将就看吧，实现也不困难。

```cpp
#include<bits/stdc++.h>
#define lson k<<1
#define rson k<<1|1
namespace fast_IO {
#define IOSIZE 5000000
	char ibuf[IOSIZE], obuf[IOSIZE], *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
#define putchar(x) ((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
#define isdigit(ch) (ch>47&&ch<58)
#define isspace(ch) (ch<33)
	template<typename T> inline T read() { T s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s * w; }
	template<typename T> inline bool read(T &s) { s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s *= w, true; }
	template<typename T> inline void print(T x) { if (x < 0) putchar('-'), x = -x; if (x > 9) print(x / 10); putchar(x % 10 + 48); }
	inline bool read(char &s) { while (s = getchar(), isspace(s)); return true; }
	inline bool read(char *s) { char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) *s++ = ch, ch = getchar(); *s = '\000'; return true; }
	inline void print(char x) { putchar(x); }
	inline void print(char *x) { while (*x) putchar(*x++); }
	inline void print(const char *x) { for (int i = 0; x[i]; i++) putchar(x[i]); }
	inline bool read(std::string& s) { s = ""; char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) s += ch, ch = getchar(); return true; }
	inline void print(std::string x) { for (int i = 0, n = x.size(); i < n; i++) putchar(x[i]); }
	inline bool read(bool &b) { char ch; while(ch=getchar(), isspace(ch)); b=ch^48; return true; }
	inline void print(bool b) { putchar(b+48); }
	template<typename T, typename... T1> inline int read(T& a, T1&... other) { return read(a) + read(other...); }
	template<typename T, typename... T1> inline void print(T a, T1... other) { print(a), print(other...); }
	struct Fast_IO { ~Fast_IO() { fwrite(obuf, p3 - obuf, 1, stdout); } } io;
	template<typename T> Fast_IO& operator >> (Fast_IO &io, T &b) { return read(b), io; }
	template<typename T> Fast_IO& operator << (Fast_IO &io, T b) { return print(b), io; }
#define cout io
#define cin io
#define endl '\n'
} using namespace fast_IO;
#define ll long long
using namespace std;

const int N=4e5+15;
const int mod=1e9+7;

bool fl[N];
int h[N],to[N<<1],ne[N<<1],idx;
int fa[N],cnt;
int lx[N],rx[N],tim;
int siz[N];
ll pre[N];
ll sum[N<<2];
ll ad[N<<2],mul[N<<2];
int n,m,tot;
int uu[N],vv[N];

int mod_add(ll x,ll y)
{
	if(x+y>=mod)
		return x+y-mod;
	return x+y;
}

inline void push_up(int k)
{
	sum[k]=mod_add(sum[lson],sum[rson]);
}

inline void push_down(int k)
{
	if(!mul[k]&&!ad[k])
		return;
	sum[lson]=mod_add(sum[lson]*mul[k]%mod,ad[k]);
	sum[rson]=mod_add(sum[rson]*mul[k]%mod,ad[k]);
	mul[lson]=mul[lson]*mul[k]%mod;
	mul[rson]=mul[rson]*mul[k]%mod;
	ad[lson]=mod_add(ad[lson]*mul[k]%mod,ad[k]);
	ad[rson]=mod_add(ad[rson]*mul[k]%mod,ad[k]);
	mul[k]=1;
	ad[k]=0;
}

inline void update_mul(int k,int l,int r,int ln,int rn,int x)
{
	if(l>=ln&&r<=rn)
	{
		sum[k]=sum[k]*x%mod;
		ad[k]=ad[k]*x%mod;
		mul[k]=mul[k]*x%mod;
		return;
	}
	push_down(k);
	int mid=(l+r)>>1;
	if(rn<=mid)
		update_mul(lson,l,mid,ln,rn,x);
	else if(ln>mid)
		update_mul(rson,mid+1,r,ln,rn,x);
	else 
		update_mul(lson,l,mid,ln,rn,x),update_mul(rson,mid+1,r,ln,rn,x);
	push_up(k);
}

inline void update_add(int k,int l,int r,int ln,int rn,int x)
{
	if(l>=ln&&r<=rn)
	{
		sum[k]=(sum[k]+x)%mod;
		ad[k]=(ad[k]+x)%mod;
		return;
	}
	push_down(k);
	int mid=(l+r)>>1;
	if(rn<=mid)
		update_add(lson,l,mid,ln,rn,x);
	else if(ln>mid)
		update_add(rson,mid+1,r,ln,rn,x);
	else 
		update_add(lson,l,mid,ln,rn,x),update_add(rson,mid+1,r,ln,rn,x);
	push_up(k);
}

inline int query(int k,int l,int r,int x)
{
	if(l==r)
		return sum[k];
	push_down(k);
	int mid=(l+r)>>1;
	if(x<=mid)
		return query(lson,l,mid,x);
	else 
		return query(rson,mid+1,r,x);
}



inline int find(int x)
{
	if(x==fa[x])
		return x;
	return fa[x]=find(fa[x]);
}

inline void add(int u,int v)
{
	to[++idx]=v;
	ne[idx]=h[u];
	h[u]=idx;
}

inline void dfs(int u,int fa)
{
	if(u<=n)
		siz[u]=1;
	lx[u]=++tim;
	for(int i=h[u];i;i=ne[i])
	{
		int v=to[i];
		if(v==fa) continue;
		dfs(v,u);
	}
	rx[u]=tim;
}

signed main()
{
	cin>>n>>m;
	cnt=n;
	pre[0]=1;
	for(int i=1;i<=m;i++)
		cin>>uu[i]>>vv[i];
	for(int i=1;i<N;i++)
		fa[i]=i;
	for(int i=1;i<=n;i++)
		pre[i]=pre[i-1]*10%mod;
	for(int i=1;i<=m;i++)
	{
		int u=uu[i];
		int v=vv[i];
		u=find(u),v=find(v);
		if(u!=v)
		{
			cnt++;
			fa[u]=fa[v]=cnt;
			add(cnt,u);
			add(cnt,v);
		}
		else
			fl[i]=1;
	}
	dfs(cnt,0);
	tot=cnt;
	for(int i=0;i<N;i++)
		fa[i]=i;
	for(int i=0;i<N*4;i++)
		mul[i]=1;
	cnt=n;
	for(int i=1;i<=m;i++)
	{
		int u=uu[i];
		int v=vv[i];
		if(fl[i])
			continue;
		u=find(u),v=find(v);
		if(u!=v)
		{
			cnt++;
			int res1=query(1,1,tot,lx[uu[i]]);
			int res2=query(1,1,tot,lx[vv[i]]);
			update_mul(1,1,tot,lx[cnt],rx[cnt],10);
			update_add(1,1,tot,lx[cnt],rx[cnt],i);
			update_mul(1,1,tot,lx[u],rx[u],pre[siz[v]-1]);
			update_add(1,1,tot,lx[u],rx[u],res2);
			update_mul(1,1,tot,lx[v],rx[v],pre[siz[u]-1]);
			update_add(1,1,tot,lx[v],rx[v],res1);
			fa[u]=fa[v]=cnt;
			siz[cnt]=siz[u]+siz[v];
		}
	}
	for(int i=1;i<=n;i++)
		cout<<query(1,1,tot,lx[i])<<endl;
	return 0;
}
```

---

## 作者：rainygame (赞：0)

给一个 $O(n\alpha(n))$ 而且特别好写的做法！

首先发现这个算法实际上就是 Prim。注意到边权互不相同，所以 MST 是唯一的。所以只需要考虑这个 MST 即可。

这个 Prim 做法很难优化，考虑转换成 Kruskal。计算一条边对于每个节点的贡献。假设这条边是第 $i$ 条，连接了 $(u,v)$，那么对于目前 $u$ 所在的连通块，它们 Prim 的过程必定先经过所有本连通块的节点，再经过第 $i$ 条边，再通过 $v$ 走到 $v$ 所在连通块。所以设 $x,y$ 分别为 $u,v$ 连通块中的某个点，$siz$ 表示连通块大小，$v$ 和 $v^\prime$ 分别表示合并前后权值，那么有：

$$
\begin{aligned}
v^\prime_x &= 10^{siz_v}v_x+10^{siz_v-1}i+v_v\\
v^\prime_y &= 10^{siz_u}v_y+10^{siz_u-1}i+v_u
\end{aligned}
$$

考虑带权并查集，对于一次合并，先给两边都打上加法和乘法标记。然后将 $x$ 的标记统一成 $y$ 的标记，最后再合并。

对于统一标记这个过程，令 $a_1,b_1$ 分别表示 $y$ 的加法和乘法标记，$a_2,b_2$ 分别表示 $x$ 的**原**加法和乘法标记，那么统一后的标记 $a_3,b_3$ 需要满足：

$$
\begin{aligned}
a_1a_3&=a_2\\
b_3a_1+b_1&=b_2
\end{aligned}
$$

解得：

$$
\begin{aligned}
a_3&=\frac{a_2}{a_1}\\
b_3&=\frac{b_2-b_1}{a_1}
\end{aligned}
$$

> 因为 $a_1$ 形如 $10^k$，所以只需要维护 $10^k$ 及其逆元即可，不需要 $O(\log V)$ 计算。同时这也保证了 $a_1$ 不是 $10^9+7$ 的倍数。

路径压缩也是个问题。现在的并查集不保证根的标记为 $\times10^0+0$，所以不能按照普通带权并查集的方式。对于可能重复添加根标记的问题，需要特判如果父亲就是连通块的根，就不更新标记。最后计算值时再统计父亲的标记。注意需要特判是否为并查集的根。最终时间复杂度 $O(n\alpha(n))$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 200005
#define pw(x) ((x) >= 0 ? p[x] : pinv[-(x)])
#define val(x) ((x) == find(x) ? b[x] : (b[x]*pw(a[f[x]])+b[f[x]])%MOD)
const int MOD(1e9+7);
const int inv10(700000005);

int n, m;
int f[MAXN], siz[MAXN], p[MAXN], pinv[MAXN], a[MAXN], b[MAXN];

int find(int x){
    if (x ^ f[x]){
        int tp(f[x]); f[x] = find(f[x]); if (tp == f[x]) return f[x];
        a[x] += a[tp]; b[x] = (b[x]*pw(a[tp])+b[tp])%MOD;
    }
    return f[x];
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> m; iota(f+1, f+n+1, 1); for (int i(1); i<=n; ++i) siz[i] = 1;
    p[0] = pinv[0] = 1; for (int i(1); i<=n; ++i) p[i] = p[i-1]*10%MOD, pinv[i] = pinv[i-1]*inv10%MOD;
    for (int i(1), u, v; i<=m; ++i){
        cin >> u >> v; int fu(find(u)), fv(find(v)); if (fu == fv) continue; if (siz[fu] > siz[fv]) swap(fu, fv), swap(u, v);
        int valu(val(u)), valv(val(v));
        a[fu] += siz[fv]; b[fu] = (b[fu]*pw(siz[fv])+i*pw(siz[fv]-1)+valv) % MOD;
        a[fv] += siz[fu]; b[fv] = (b[fv]*pw(siz[fu])+i*pw(siz[fu]-1)+valu) % MOD;
        b[fu] = ((b[fu]-b[fv]+MOD)*pw(-a[fv])) % MOD; a[fu] -= a[fv]; siz[f[fu]=fv] += siz[fu];
    }
    for (int i(1); i<=n; ++i) cout << val(i) << '\n';

    return 0;
}
```

---

## 作者：小木虫 (赞：0)

### Preface  
比较引人入胜的题，不是很明白为什么题解区直接都能反应到是 kruskal 重构树，感觉不是很自然。  
### Problem  

为了丰富自己的数学知识，Bessie 选修了一门图论课程，她发现她被下面的问题困住了，请帮帮她！

给出一张连通的无向图，包含编号为 $1\dots N$ 的节点和编号为 $1\dots M$（$2 \le N \le 2\cdot 10^5$，$N - 1 \le M \le 4 \cdot 10^5$）的边，下边的操作将被实施：

1. 假设集合 $S=\{v\}$，变量 $h=0$。
2. 当 $|S|<N$，重复执行：
	1. 仅有一个顶点在集合 $S$ 中的边中，找到编号最小的那条，编号记为 $e$。
    2. 将 $e$ 不在 $S$ 中的那个顶点加入集合 $S$。
    3. 将 $h$ 修改为 $10h+e$。
3. 返回 $h$ 对 $10^9+7$ 取模的值。

输出这个过程的全部返回值。  
### Solution  
发现这个题目的题意实际上就是一个 Prim 算法，如果我们直接暴力计算只能得到 $O(n^2\log m)$ 的做法，得 eps 分。  
但是你又发现因为这是一个 Prim 算法，所以最后得到的边集都是一样的，如果你没有意识到这是一个 Prim 算法也可以选择自己证明，不是很难。  

优化单次计算的过程一看就十分没有前途，所以我们思考能否一起计算不同点的答案？  

自然地，我们从小到大枚举边且合并边两侧的连通块，容易发现由于我们枚举的这个边对于之前的连通块来说是瓶颈，所以一定是加入这个边后把另一个连通块全部合并后才会做其他操作。  

我们设第一个连通块为 $A$，第二个为 $B$，此时链接他们的边为 $(x,y)$。  
那么，显然地，对于连通块 $A$ 内的所有点来说，先加入 $(x,y)$ 后再接上此时点 $y$ 在 $B$ 内的所有操作。  
对于连通块 $B$ 是镜像的。  

那么现在我们实际上就做到了 $O(n^2)$，可以多过一些分。  
由于这个修改操作会同时影响两侧，所以我们没办法使用启发式合并优化这个操作，那我们还有办法使用数据结构维护连通块内部的数据吗？  

其实是可以的，因为我们有办法构造一个序列使得所有上述连通块在序列中都是一个区间，然后我们就可以使用区间数据结构进行维护了，具体来说当我们合并的时候，我们将一个连通块形成的序列接到另一个的后面，然后递归地进行这样的操作就可以了，你也可以认为这是 Kruskal 重构树的 dfn 序。  

然后我们就将问题归约为了一个区间加区间乘单点查的线段树，最终复杂度 $O(n\log n)$。  
代码：  

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10,mod=1e9+7;
int n,m,a[N],b[N],pw[N];
int ptag[N<<2],mtag[N<<2];
void pushdown(int rt){
	if(mtag[rt]!=1){
		mtag[rt<<1]*=mtag[rt];mtag[rt<<1]%=mod;
		ptag[rt<<1]*=mtag[rt];ptag[rt<<1]%=mod;
		mtag[rt<<1|1]*=mtag[rt];mtag[rt<<1|1]%=mod;
		ptag[rt<<1|1]*=mtag[rt];ptag[rt<<1|1]%=mod;
		mtag[rt]=1;
	}
	if(ptag[rt]){
		ptag[rt<<1]+=ptag[rt];ptag[rt<<1]%=mod;
		ptag[rt<<1|1]+=ptag[rt];ptag[rt<<1|1]%=mod;
		ptag[rt]=0;
	}
}
void mul(int rt,int left,int right,int L,int R,int x){
	if(left<right)pushdown(rt);
	if(left>=L&&right<=R){
		mtag[rt]*=x;mtag[rt]%=mod;
		ptag[rt]*=x;ptag[rt]%=mod;
		return ;
	}int mid=(left+right)>>1;
	if(L<=mid)mul(rt<<1,left,mid,L,R,x);
	if(mid<R)mul(rt<<1|1,mid+1,right,L,R,x);
}
void pls(int rt,int left,int right,int L,int R,int x){
	if(left<right)pushdown(rt);
	if(left>=L&&right<=R){
		ptag[rt]+=x;ptag[rt]%=mod;
		return ;
	}int mid=(left+right)>>1;
	if(L<=mid)pls(rt<<1,left,mid,L,R,x);
	if(mid<R)pls(rt<<1|1,mid+1,right,L,R,x);
}
int query(int rt,int left,int right,int x){
	if(left<right)pushdown(rt);
	if(left==right)return ptag[rt];
	int mid=(left+right)>>1;
	if(x<=mid)return query(rt<<1,left,mid,x);
	else return query(rt<<1|1,mid+1,right,x); 
}
int fa[N];
vector <int> S[N];
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
int L[N],M[N],R[N],vis[N],flg[N],root;
void merge(int x,int y,int id){
	x=find(x);y=find(y);
	if(x==y)return;vis[id]=1;
	if(S[x].size()<S[y].size())swap(x,y),flg[id]=1;
	L[id]=S[x].front();
	R[id]=S[y].back();
	M[id]=S[x].back();
	for(auto it:S[y])S[x].push_back(it);
	fa[y]=x;S[y].clear();root=x;
}
int id[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;pw[0]=1;
	for(int i=1;i<=n;i++)fa[i]=i,S[i].push_back(i);
	for(int i=1;i<=m;i++)
		cin>>a[i]>>b[i];
	for(int i=1;i<=2000000;i++)mtag[i]=1;
	for(int i=1;i<=n;i++)pw[i]=10ll*pw[i-1]%mod;
	for(int i=1;i<=m;i++)
		merge(a[i],b[i],i);
	for(int i=0;i<n;i++)
		id[S[root][i]]=i+1;
	//for(int i=1;i<=n;i++)
	//	cout<<id[i]<<" ";
	//cout<<"\n";
	for(int i=1;i<=m;i++){
		if(!vis[i])continue;
		if(flg[i])swap(a[i],b[i]);
		L[i]=id[L[i]];R[i]=id[R[i]];M[i]=id[M[i]];
		int x=query(1,1,n,id[a[i]]),y=query(1,1,n,id[b[i]]);
		int s1=M[i]-L[i]+1,s2=R[i]-M[i];
		//cout<<s1<<" "<<s2<<" "<<x<<" "<<y<<"\n";
		mul(1,1,n,L[i],M[i],pw[s2]);
		pls(1,1,n,L[i],M[i],(y+i*pw[s2-1])%mod);
		mul(1,1,n,M[i]+1,R[i],pw[s1]);
		pls(1,1,n,M[i]+1,R[i],(x+i*pw[s1-1])%mod);
	}
	for(int i=1;i<=n;i++)
		cout<<query(1,1,n,id[i])<<"\n";
	return 0;
}

```

---

