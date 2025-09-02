# [CEOI 2019] Dynamic Diameter

## 题目描述

有一棵树，含 $n$ 个节点，边带权。

会有 $q$ 次修改，每次会将树上的一条边的边权进行修改，在每次修改后，您需要求出每次修改后，这棵树的直径上的边权和。

**本题强制在线。**

## 说明/提示

#### 样例 1 解释

解密后的修改如下：
```
2 1030
0 1050
2 970
```
如图为树的边权变化过程，红边代表树的直径：
![](https://cdn.luogu.com.cn/upload/image_hosting/sswn0icz.png)
#### 数据范围
对于 $100\%$ 的数据，保证 $2\le n\le 10^5$，$1\le q\le 10^5$，$1\le w\le 2\times 10^{13}$，$1\le a_i,b_i\le n$，$0\le c_i,e_j<w$，$0\le d_j<n-1$。

详细子任务限制及分值如下表：

| 子任务编号 | 限制 | 分值 |
| :-: |:-:|:-:|
| 1 | $n,q\le 100$ 且 $w\le 10^4$ | $11$ | 
| 2 | $n,q\le 5\times 10^3$ 且 $w\le 10^4$ | $13$ | 
| 3 | $w\le 10^4$ 且边的形式均为 $(1,i)$ | $7$ | 
| 4 | $w\le 10^4$ 且边的形式均为 $(i,2\times i)$ 或 $(i,2\times i+1)$ | $18$ | 
| 5 | 保证有一条直径经过 $1$ 号节点 | $24$ | 
| 6 | 无特殊限制 | $27$ | 
#### 说明
本题译自 [Central-European Olympiad in Informatics 2019](https://ceoi.sk/) [Day 1](https://ceoi.sk/tasks/) [T2 Dynamic Diameter](https://ceoi.sk/static/statements/diameter-ENG.pdf)。

## 样例 #1

### 输入

```
4 3 2000
1 2 100
2 3 1000
2 4 1000
2 1030
1 1020
1 890```

### 输出

```
2030
2080
2050
```

## 样例 #2

### 输入

```
10 10 10000
1 9 1241
5 6 1630
10 5 1630
2 6 853
10 1 511
5 3 760
8 3 1076
4 10 1483
7 10 40
8 2051
5 6294
5 4168
7 1861
0 5244
6 5156
3 3001
8 5267
5 3102
8 3623```

### 输出

```
6164
7812
8385
6737
6738
7205
6641
7062
6581
5155```

# 题解

## 作者：ningago (赞：31)

朴素的 dfs 求直径好像很难拓展的样子……

DP 求直径好像动态 dp 也可以搞，但很复杂的样子……

所以考虑用数据结构优化暴力求直径！

即快速且动态地求出：

$$\max_{x=1}^n\max_{y=1}^ndis_{x,y}$$

利用树上差分基本功不难知道其等价于：

$$=\max_{x=1}^n\max_{y=1}^n(dep_x+dep_y-2\cdot dep_{lca(x,y)})$$

既然 $lca$ 是关于 $x,y$ 的二元函数，那可不可以把它转化成代数语言呢？

联想 [$O(1)$ 求 lca 算法](https://oi-wiki.org/graph/lca/#%E7%94%A8%E6%AC%A7%E6%8B%89%E5%BA%8F%E5%88%97%E8%BD%AC%E5%8C%96%E4%B8%BA-rmq-%E9%97%AE%E9%A2%98)，利用欧拉序可以将 lca 转化成 RMQ 问题。即：

$$\mathrm{first}_{lca(x,y)}=\min_{\mathrm{any}_x\leq i\leq \mathrm{any}_y}(\mathrm{first}_{\mathrm{eul}_i})$$

其中，$\mathrm{first}_x$ 为 $x$ 的第一个欧拉序编号，$\mathrm{any}_x$ 为 $x$ 的任意一个欧拉序编号，$\mathrm{eul}_x$ 为欧拉序为 $x$ 的节点编号。

这样做的原因是 $\mathrm{first}_x=\min_{y\in son(x)}\mathrm{first}_y$，而注意到 $dep_x=\min_{y\in son(x)}dep_y$（其中 $son(x)$ 表示 $x$ 的子树）。所以同理可得：

$$dep_{lca(x,y)}=\min_{\mathrm{any}_x\leq i\leq \mathrm{any}_y}(dep_{\mathrm{eul}_i})$$

于是，考虑设置长度为 $2n-1$ 的序列 $a$，满足 $a_i=dep_{\mathrm{eul}_i}$。则原式等价于：

$$=\max_{x=1}^{2n-1}\max_{y=x}^{2n-1}(a_x+a_y-2\cdot (\min_{x\leq z\leq y}a_z))$$

这是显然可以线段树维护的。

具体而言，对于每个节点维护：

$$\begin{cases}ans=\max_{l\leq x\leq y\leq r}(a_x+a_y-2\cdot (\min_{x\leq z\leq y}a_z))\\
lp=\max_{l\leq x\leq r}(a_x-2\cdot (\min_{x\leq z\leq r}a_z))\\
rp=\max_{l\leq y\leq r}(a_y-2\cdot (\min_{l\leq z\leq y}a_z))\\
mx=\max_{l\leq x\leq r} a_x\\
mn=\min_{l\leq x\leq r} a_x\end{cases}$$

则转移显然为：

$$\begin{cases}
ans=\max\{ans_{ls},\ ans_{rs},\ lp_{ls}+mx_{rs},\ mx_{ls}+rp_{rs}\}\\
lp=\max\{lp_{ls},\ lp_{rs},\ mx_{ls}-2\cdot mn_{rs}\}\\
rp=\max\{rp_{ls},\ rp_{rs},\ mx_{rs}-2\cdot mn_{ls}\}
\end{cases}$$

对于边单点改，相当于是 $dep$ 子树加，记录 $\mathrm{last}_x$ 为 $x$ 的最后一个欧拉序编号，对 $\mathrm{first}_x\leq i\leq \mathrm{last}_x$ 进行区间加即可。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

#define N 200010
#define int long long
int n, m;

int h[N], e[N << 1], ne[N << 1], id[N << 1], idx = -1;
int u_[N], v_[N], w_[N];

void add_edge(int x, int y, int id_)
{
	ne[++idx] = h[x];
	h[x] = idx;
	e[idx] = y;
	id[idx] = id_;
}

void add(int x, int y, int id_)
{
	add_edge(x, y, id_);
	add_edge(y, x, id_);
}

int our[N], first[N], last[N], dis[N];

void dfs(int k, int fa)
{
	our[++our[0]] = k;
	first[k] = our[0];
	for(int i = h[k]; ~i; i = ne[i])
	{
		int nx = e[i];
		if(nx == fa)
			continue;
		u_[id[i]] = k;
		v_[id[i]] = nx;
		dis[nx] = dis[k] + w_[id[i]];
		dfs(nx, k);
		our[++our[0]] = k;
	}
	last[k] = our[0];
}

struct Tree
{
	int mx, mn;
	int lp, rp, ans;
	int lazy;
	void push(int z)
	{
		mx += z;
		mn += z;
		lazy += z;
		lp -= z;
		rp -= z;
	}
}tr[N << 2];

#define lson k << 1
#define rson k << 1 | 1

void pushup(int k)
{
	tr[k].mx = std::max(tr[lson].mx, tr[rson].mx);
	tr[k].mn = std::min(tr[lson].mn, tr[rson].mn);
	tr[k].lp = std::max({tr[lson].lp, tr[rson].lp, tr[lson].mx - 2 * tr[rson].mn});
	tr[k].rp = std::max({tr[lson].rp, tr[rson].rp, tr[rson].mx - 2 * tr[lson].mn});
	tr[k].ans = std::max({tr[lson].ans, tr[rson].ans, tr[lson].lp + tr[rson].mx, tr[lson].mx + tr[rson].rp});
}

void pushdown(int k)
{
	if(tr[k].lazy)
	{
		tr[lson].push(tr[k].lazy);
		tr[rson].push(tr[k].lazy);
		tr[k].lazy = 0;
	}
}

#define inf 0x3f3f3f3f3f3f3f3f
#define ls lson, l, mid
#define rs rson, mid + 1, r

void build(int k, int l, int r)
{
	if(l == r)
	{
		tr[k].mn = tr[k].mx = dis[our[l]];
		tr[k].lp = tr[k].rp = -dis[our[l]];
		tr[k].ans = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(ls);
	build(rs);
	pushup(k);
}

void change(int k, int l, int r, int ql, int qr, int z)
{
	if(ql <= l && r <= qr)
	{
		tr[k].push(z);
		return;
	}
	pushdown(k);
	int mid = (l + r) >> 1;
	if(ql <= mid)
		change(ls, ql, qr, z);
	if(mid < qr)
		change(rs, ql, qr, z);
	pushup(k);
}

#define root 1, 1, n * 2 - 1

int W;

#undef int
int main()
{
#define int long long
	memset(h, -1, sizeof(h));
	scanf("%lld%lld%lld", &n, &m, &W);
	for(int i = 1; i < n; i++)
	{
		scanf("%lld%lld%lld", &u_[i], &v_[i], &w_[i]);
		add(u_[i], v_[i], i);
	}
	dfs(1, 0);
	build(root);
	int lastans = 0;
	for(int i = 1, x, y; i <= m; i++)
	{
		scanf("%lld%lld", &x, &y);
		x = (x + lastans) % (n - 1) + 1;
		y = (y + lastans) % W;
		int v = v_[x];
		int w = w_[x];
		change(root, first[v], last[v], y - w);
		printf("%lld\n", tr[1].ans);
		w_[x] = y;
		lastans = tr[1].ans;
	}
	return 0;
}
```

---

## 作者：Star_Cried (赞：27)

## P6845 [CEOI2019] Dynamic Diameter

### 题意

一颗带权树，每次更改一条边的权，每次修改后求出最大直径。强制在线。

### 思路

$O(n\log^2n)$ 的暴力做法。

根据经典结论，对于两个点集的树上最大直径（权值非负），并集点集的树上最大直径的端点一定是原四个端点中的两个。

那么我们就可以用线段树维护点集，合并时 $O(\log n)$ 查询两点间距离合并就可以做到 $O(n\log^2n)$ 的复杂度了。

思考如何支持在线修改边权。两点间距离为 $dis(x)+dis(y)-2*dis(lca(x,y))$ 那么先树剖发现修改一条边的权实际上是将子树内 $dis$ 增加，那么子树就是区间加。我们可以用树状数组维护修改。

考虑哪些部分的线段树上的点集最大直径被改了。发现子树内和子树外的最大直径不会变化，那么我们只需要更改子树内与外之间合并的最大直径就行了。我们按照 $dfn$ 用线段树进行维护，那么我们每次只需要将子树区间重新 `pushup` 一下就可以了。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<utility>
using namespace std;
inline long long read(){
	long long x=0;int w=0;char c=getchar();
	while(!isdigit(c)) w|=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=1e5+10;
	int n,q;
	int ecnt=1,head[maxn],to[maxn<<1],nxt[maxn<<1],go[maxn];
	long long W,w[maxn],dis[maxn];
	inline void addedge(){
		int a=read(),b=read();
		to[++ecnt]=b,nxt[ecnt]=head[a],head[a]=ecnt;
		to[++ecnt]=a,nxt[ecnt]=head[b],head[b]=ecnt;
		w[ecnt>>1]=read();
	}
	int dep[maxn],fa[maxn],top[maxn],siz[maxn],son[maxn],dfn[maxn],id[maxn];
	void dfs1(int x,int f){
		fa[x]=f,dep[x]=dep[f]+1,siz[x]=1;
		for(int u,i=head[x];i;i=nxt[i]) if((u=to[i])!=f){
			dis[u]=dis[x]+w[i>>1],dfs1(u,x),go[i>>1]=u;
			if(siz[u]>siz[son[x]]) son[x]=u;
			siz[x]+=siz[u];
		}
	}
	void dfs2(int x,int topf){
		top[x]=topf,dfn[x]=++dfn[0],id[dfn[0]]=x;
		if(!son[x]) return;
		dfs2(son[x],topf);
		for(int u,i=head[x];i;i=nxt[i]) if((u=to[i])!=fa[x] and u!=son[x]) dfs2(u,u);
	}
	inline int LCA(int x,int y){
		while(top[x]!=top[y]) dep[top[x]]>dep[top[y]]?(x=fa[top[x]]):(y=fa[top[y]]);
		return dep[x]<dep[y]?x:y;
	}
	#define ls (ro<<1)
	#define rs (ro<<1|1)
	#define mid ((l+r)>>1)
	namespace S{
		long long c[maxn];
		inline void upd(int x,long long k){for(;x<=n;x+=x&-x) c[x]+=k;}
		inline long long query(int x){long long ans=dis[id[x]];for(;x;x-=x&-x) ans+=c[x];return ans;}
		inline void update(int x,int y,long long w){upd(x,w),upd(y+1,-w);}
	}
	inline long long Dis(pair<int,int> a){return S::query(dfn[a.first])+S::query(dfn[a.second])-2*S::query(dfn[LCA(a.first,a.second)]);}
	namespace T{
		pair<int,int> e[maxn<<2];
		inline pair<int,int> merge(const pair<int,int>& a,const pair<int,int>& b){
			pair<int,int> p[6]={a,b,make_pair(a.first,b.first),make_pair(a.first,b.second),make_pair(a.second,b.first),make_pair(a.second,b.second)};
			long long dis[6];
			for(int i=0;i<6;i++) dis[i]=Dis(p[i]);
			return p[max_element(dis,dis+6)-dis];
		}
		void build(int ro=1,int l=1,int r=n){
			if(l==r) return e[ro]=make_pair(id[l],id[l]),void();
			build(ls,l,mid),build(rs,mid+1,r);
			e[ro]=merge(e[ls],e[rs]);
		}
		void update(int x,int y,int ro=1,int l=1,int r=n){
			if(x==l and y==r) return;
			if(y<=mid) update(x,y,ls,l,mid);
			else if(x>mid) update(x,y,rs,mid+1,r);
			else update(x,mid,ls,l,mid),update(mid+1,y,rs,mid+1,r);
			e[ro]=merge(e[ls],e[rs]);
		}
	}
	#undef ls
	#undef rs
	#undef mid
	inline void work(){
		n=read(),q=read(),W=read();
		for(int i=1;i<n;i++) addedge();	
		dfs1(1,0),dfs2(1,1);
		T::build();
		long long ans=0;
		while(q--){
			int e=(read()+ans)%(n-1)+1;
			long long v=(read()+ans)%W;
			S::update(dfn[go[e]],dfn[go[e]]+siz[go[e]]-1,v-w[e]),w[e]=v;
			T::update(dfn[go[e]],dfn[go[e]]+siz[go[e]]-1);
			printf("%lld\n",ans=Dis(T::e[1]));
		}
	}
}
signed main(){
	star::work();
	return 0;
}
```



---

## 作者：Purslane (赞：15)

# Solution

考虑如何刻画直径。直径即为 $\max_{1\le u,v \le n} \{d_u+d_v-2d_{\text{lca}(u,v)}\}$，其中 $d$ 表示节点深度。

考虑把这棵树拍成欧拉序。那么两个点的 $d_{\text{lca}(u,v)}$ 其实就是 $[\min\{L_u,L_v\},\max\{R_u,R_v\}]$ 中的最小值，其中 $L$ 和 $R$ 表示一个节点在欧拉序列中第一次和最后一次出现的位置。

再考虑到它前面的符号是负号，所以你没取最小值而是更大一些的数会使答案更劣，不会这么做。同样的，如果我们的左端点不是 $\min\{L_u,L_v\}$，右端点不是 $\max\{R_u,R_v\}$，也不会取到更大的答案。

因此我们只需要求出：

对于一个序列 $\{a\}$，$\max_{i \le j \le k}\{a_i+a_k-2a_j\}$，这个可以用很朴素的线段树维护。

```cpp
#include<bits/stdc++.h>
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
map<pair<int,int>,int> mmp;
int n,q,w,lstans,dfn,id[MAXN],dep[MAXN],rev[MAXN],wid[MAXN],val[MAXN],tag[MAXN<<2],L[MAXN],R[MAXN];
struct INFO {int ans,mx,mn,lmx,rmx;}t[MAXN<<2];
INFO operator +(INFO A,INFO B) {return {max({A.ans,B.ans,A.lmx+B.mx,A.mx+B.rmx}),max(A.mx,B.mx),min(A.mn,B.mn),max({A.lmx,B.lmx,A.mx-2*B.mn}),max({A.rmx,B.rmx,B.mx-2*A.mn})};}
INFO operator +(INFO A,int B) {return {A.ans,A.mx+B,A.mn+B,A.lmx-B,A.rmx-B};}
void push_down(int k,int l,int r) {return t[lson]=t[lson]+tag[k],t[rson]=t[rson]+tag[k],tag[lson]=tag[lson]+tag[k],tag[rson]=tag[rson]+tag[k],tag[k]=0,void();}
void build(int k,int l,int r) {
	if(l==r) return t[k]={-0x3f3f3f3f3f3f3f3f,val[l],val[l],-0x3f3f3f3f3f3f3f3f,-0x3f3f3f3f3f3f3f3f},void();
	build(lson,l,mid),build(rson,mid+1,r);
	return t[k]=t[lson]+t[rson],void();
}
void update(int k,int l,int r,int x,int y,int tg) {
	if(x<=l&&r<=y) return tag[k]=tag[k]+tg,t[k]=t[k]+tg,void();
	push_down(k,l,r);
	if(x<=mid) update(lson,l,mid,x,y,tg);
	if(y>mid) update(rson,mid+1,r,x,y,tg);
	return t[k]=t[lson]+t[rson],void();
}
vector<pair<int,int>> G[MAXN];
void dfs(int u,int f) {id[u]=mmp[{u,f}],dep[u]=dep[f]+wid[u],rev[id[u]]=u,++dfn,L[u]=R[u]=dfn,val[dfn]=dep[u];for(auto pr:G[u]) if(pr.first!=f) wid[pr.first]=pr.second,dfs(pr.first,u),++dfn,val[dfn]=dep[u],R[u]=dfn;return ;}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q>>w; ffor(i,1,n-1) {int u,v,w;cin>>u>>v>>w,G[u].push_back({v,w}),G[v].push_back({u,w}),mmp[{u,v}]=mmp[{v,u}]=i;}
	dfs(1,0),build(1,1,dfn);
	ffor(i,1,q) {
		int d,e; cin>>d>>e,d=rev[(d+lstans)%(n-1)+1],e=(e+lstans)%w;
		update(1,1,dfn,L[d],R[d],e-wid[d]),wid[d]=e;
		cout<<(lstans=max(t[1].mx,t[1].ans))<<'\n';
	}
	return 0;
}
```

---

## 作者：居然有个高手 (赞：12)

补充一下目前在题解区中还未出现的点分树做法。（尽管很劣）

首先，题目要求在修改边权后求动态直径，有一个显然的 $O(nq)$ 做法，直接两次 dfs，一次从 $1$ 号点找出离它最远的点 $u$，再从点 $u$ 找出离它最远的点 $v$，$u,v$ 即为直径的两个端点，但显然无法通过。

考虑优化该询问过程：求出离某个点最远的点的可能答案显然是该点上级分治中心中，与该点不属于同一子树的最远点，通过此手段+线段树维护可以在 $O(\log^2 n)$ 的时间内求出最远点。

考虑边的修改：设修改的边的端点分别为 $u,v$，则二者在点分树上为祖孙关系，设 $u$ 是 $v$ 的子孙，则可以从 $u$ 不断向上跳点分树上的祖先，修改答案。

时间复杂度：$O(n\log^2n)$，空间复杂度：$O(n\log^2n)$。

然后你会发现你可能会 MLE，因为空间常数太大，考虑卡卡常数。

容易发现，我们不需要建立值域范围在 $[1,n]$ 的线段树，而是可以在本分治中心 dfs 时新编一个 $dfn$，建立值域范围 $[1,siz]$ 的线段树即可（同时也方便了去除同一子树的影响），空间复杂度优化为 $O(n\log n)$。

贴个代码，大家可以参考一下（应该是本题最劣解了）。

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,pair<int,int>>mp2;
map<pair<int,int>,long long>mp;
const int N=1e5+5;
const long long inf=1e18;
int n,q,head[N],tot,sz[N],siz[N],son[N],fa[N],rt,cnt,root[N],in[20][N],out[20][N],num,newd[N],minn[N],maxn[N];
long long v[N],type;
bool vis[N]; 
struct edge{
	int nxt,to;
	long long val;
}e[N<<1];
inline void add(int a,int b,long long c){
	e[++tot]={head[a],b,c};head[a]=tot;
}
struct node{
	long long v;
	int id;
	inline bool operator>(node b){
		if(v^b.v)return v>b.v;
		return id<b.id;
	}
};
const node g={-inf,0};
inline node Max(node& a,node b){
	return (a>b)?a:b;
}
struct tree{
	int lc,rc;
	node maxn;
	long long tag;
}t[N*35];
inline void up(int p){
	t[p].maxn=Max(t[t[p].lc].maxn,t[t[p].rc].maxn);
}
inline void add(int p,long long v){
	t[p].maxn.v+=v,t[p].tag+=v;
}
inline void spread(int p){
	if(t[p].tag){
		add(t[p].lc,t[p].tag),add(t[p].rc,t[p].tag);
		t[p].tag=0;
	}
}
inline void change(int& p,int l,int r,int ql,int qr,long long v){
	if(!p)p=++tot,t[p].maxn=g;
	if(ql<=l&&r<=qr){
		add(p,v);
		return ;
	}
	spread(p);
	int mid=l+r>>1;
	if(ql<=mid)change(t[p].lc,l,mid,ql,qr,v);
	if(qr>mid)change(t[p].rc,mid+1,r,ql,qr,v);
	up(p);
}
inline void insert(int&p,int l,int r,int pos,long long v,int id){
	if(!p)p=++tot,t[p].maxn=g;
	if(l==r){
		t[p].maxn.v=v,t[p].maxn.id=id;
		return ;
	}
	int mid=l+r>>1;
	if(pos<=mid)insert(t[p].lc,l,mid,pos,v,id);
	else insert(t[p].rc,mid+1,r,pos,v,id);
	up(p);
}
inline node query(int p,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return t[p].maxn;
	spread(p);
	int mid=l+r>>1;
	node ans=g;
	if(ql<=mid)ans=Max(ans,query(t[p].lc,l,mid,ql,qr));
	if(qr>mid)ans=Max(ans,query(t[p].rc,mid+1,r,ql,qr));
	return ans;
}
//简单的线段树 
inline void getroot(int x,int fa,int cnt){
	siz[x]=1,son[x]=0;
	for(int i = head[x],y;i;i=e[i].nxt){
		y=e[i].to;
		if(!vis[y]&&y!=fa)getroot(y,x,cnt),siz[x]+=siz[y],son[x]=max(son[x],siz[y]);
	}
	son[x]=max(son[x],cnt-siz[x]);
	if(son[x]<son[rt])rt=x;
}//正常求分治中心 
inline void solve(int x,int fa,long long dis,int id){
	in[newd[id]][x]=++num,insert(root[id],1,sz[id],num,dis,x);
	minn[id]=min(minn[id],in[newd[id]-1][x]),maxn[id]=max(maxn[id],out[newd[id]-1][x]);//记录到上级节点时本子树内的点的dfn序范围 
	for(int i = head[x],y;i;i=e[i].nxt){
		y=e[i].to;
		if(!vis[y]&&y!=fa)solve(y,x,dis+e[i].val,id);
	}
	out[newd[id]][x]=num;
}//预处理本层 
inline void gettree(int x,int cnt){
	minn[x]=1e9,maxn[x]=0;
	vis[x]=1;num=0;sz[x]=cnt,solve(x,0,0,x);
	for(int i = head[x],y;i;i=e[i].nxt){
		y=e[i].to;
		if(!vis[y]){
			int now=(siz[y]<=siz[x])?siz[y]:cnt-siz[x];
			rt=0;
			getroot(y,x,now);fa[rt]=x;newd[rt]=newd[x]+1;gettree(rt,now);
		}
	}
}//正常的建点分树 
inline void cbian(int x,int y,long long v){
	if(x>y)swap(x,y);
	long long w=mp[{x,y}];mp[{x,y}]=v;
	int u = (newd[x]<newd[y])?x:y;
	while(u){
		if(in[newd[u]][x]>in[newd[u]][y])change(root[u],1,sz[u],in[newd[u]][x],out[newd[u]][x],v-w);
		else change(root[u],1,sz[u],in[newd[u]][y],out[newd[u]][y],v-w);
		u=fa[u];
	}
}//修改边 
inline node ask(int x){
	int u = x,l=0,r=0;
	node now=g,w;
	while(u){
		w=g;
		if(!l)w=query(root[u],1,sz[u],1,sz[u]);
		else{
			if(l>1)w=query(root[u],1,sz[u],1,l-1);
			if(r<sz[u])w=Max(w,query(root[u],1,sz[u],r+1,sz[u]));
		}
		w.v+=query(root[u],1,sz[u],in[newd[u]][x],in[newd[u]][x]).v;
		now=Max(now,w);
		l=minn[u],r=maxn[u];
		u=fa[u];
	}
	return now;
}//询问最远点 
int main(){
	t[0].maxn=g;
	scanf("%d%d%lld",&n,&q,&type);son[0]=N;
	for(int i = 1,x,y;i<n;i++){
		scanf("%d%d%lld",&x,&y,&v[0]),add(x,y,v[0]),add(y,x,v[0]);
		if(x>y)swap(x,y);
		mp[{x,y}]=v[0];
		mp2[i]={x,y};
	}tot=0;
	getroot(1,0,n);
	gettree(rt,n);
	int op,x,y,now=1;
	long long v,ans=0;
	while(q--){
		scanf("%d",&x);
		x=(x+ans)%(n-1)+1;
		y=mp2[x].second,x=mp2[x].first;
		scanf("%lld",&v);
		v=(v+ans)%type;
		cbian(x,y,v);
		node x1=ask(1),x2=ask(x1.id);
		printf("%lld\n",ans=x2.v);
	}
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：10)

$\text{Top-Tree}$ 是一个简单实用的东西，自然是可以维护动态直径的。

如果你还不会 $\text{Top-Tree}$，可以到[这里](/blog/502410/sone1-imaglct-satt-develop-p5649)学习。

对于 $\text{Compress-Tree}$，我们维护，簇中直径、簇中到左右端点的最远距离，即可做到轻松合并，注意要记录簇链长度。

对于 $\text{Rake-Tree}$ 也很好维护，直接考虑将两棵子树最深点（相当于到左端点最远距离）组成的直径，十分方便。

合并部分代码：
```cpp
struct dat{
    ll l,m,r,ln;//左端点距离，直径长度，右端点距离，簇链长度
    dat operator+(dat z){
        return {max(l,ln+z.l),max({m,z.m,r+z.l}),max(r+z.ln,z.r),ln+z.ln};
    }
}sm[N];
dat datad(dat x,dat y){
    return {max(x.l,y.l),max({x.m,y.m,x.l+y.l})};
    //rake-tree 的合并
}
dat gdat(int x){
    if(ms)return{sm[ms].l+w[x],max(sm[ms].m,sm[ms].l+w[x]),sm[ms].l,w[x]};
    else return{w[x],w[x],0,w[x]};
    //将 rake-data 转换成 compress-data
}
void pp(int x){
    if(x>n){//rake-pushup
        if(ls&&rs)sm[x]=datad(sm[ls],sm[rs]);
        else sm[x]=sm[ls|rs];
    }else{//compress-pushup
        sm[x]=sm[ls]+gdat(x)+sm[rs];
    }
}
```

发现这就是普通的 $\text{Self-adjusting-Top-Tree}$ 操作，于是时间复杂度为 $O(q\log_2n+n)$，空间复杂度为 $O(n)$，支持在线。

劣势：常数较大，需要 $333ms$，而最优解只要 $237ms$，可能对于少数人来说并不好写，也不好调试，即使我只要一小时写，半小时调。

优势：扩展性强，欧拉序做法似乎不能支持负边权，而这个做法不仅可以支持负权，还能换父亲（暂时不知道怎么换根）。

常数大是 $\text{SATT}$ 最大的缺陷，但是这题并不需要更改树的形态，所以可以采用全局平衡二叉树，这样让常数变得优秀，只需要 $213ms$，是目前的最优解（$\text{test on 2022-11-07}$，超过了所有线段树做法）。

其实 $\text{SATT}$ 更好写！不到 $3.0K$！全局平衡二叉树由于需要预处理建树，所以时间复杂度为 $O((n+q)\log_2n)$，每次修改只要不停地跳父亲 `pushup`，常数很小。

---

## 作者：极寒神冰 (赞：9)

蒟蒻来一发支持加边删边的LCT题解。

LCT的辅助树维护树内维护的是一条链，考虑维护这条**实链**上的最浅和最深的节点到**当前子树内**的最远距离。由于轻边实际上是父亲与这棵Splay上深度最小的点连的边，设$lmx[i]$表示$i$这棵**Splay子树**内深度最小的点往下的最大深度。当然因为Splay需要支持翻转操作，我们还需要维护这棵Splay上深度最大的点往下的最大深度rmx，当将Splay翻转过来时直接$swap(lmx,rmx)$即可。

接下来考虑lmx和rmx如何转移。以lmx的转移为例。

先考虑实链的转移

有
$$
lmx[x]=\max(lmx[x],lmx[son[x][0]])
$$
即直接从原树的祖先转移下来。

以及
$$
lmx[x]=\max(lmx[x],lmx[son[x][1]]+sum[son[x][0]]+len[x])
$$
即保留子树的答案再加上祖先和自身这条边的距离。

再考虑虚子树的转移。由于实链上深度最小的点实际上也是原树上子树的根节点。所以$lmx[x]$也可以表示为**子树内深度最小的节点**到子树内一点最远距离，那么有
$$
lmx[x]=\max(lmx[x],Chain.Fir+sum[son[x][0]]+len[x])
$$
即从虚儿子中深度最大的节点转移即可，这可以使用一个可删堆或者multiset来维护。

rmx同理。

接下来考虑$mxd[i]$最长链的转移。

仍然先考虑实链的转移有
$$
mxd[x]=\max(mxd[x],rmx[son[x][0]]+lmx[son[x][1]]+len[x])
$$
即祖先深度最大的点到子树深度最小的点以及自身这条边的距离。

以及
$$
mxd[x]=\max(mxd[x],mxd[son[x][0]],mxd[son[x][1]])
$$
即祖先和子树本来就有的最长链

再考虑虚子树的转移

最长链有可能是虚子树中本来就有的一条最长链，这同样也可以使用可删堆或者multiset维护。
$$
mxd[x]=\max(mxd[x],Path.Fir)
$$
当然也有可能是两条虚子树的链和自身这条边拼起来的，所以还有：
$$
mxd[x]=\max(mxd[x],Chain.Fir+Chain.Sec+len[x])
$$
最后附上代码

```cpp
const int N=4e5+10;
int lmx[N],rmx[N],mxd[N];
int fa[N],len[N],tag[N],son[N][2];
int sum[N];
int n,m,MXW,ans,lst_ans;
vector<int>e[N];
struct inandelheap
{
	priority_queue<int>whl,del;
	inline void ist(int x){if(x!=-inf)whl.push(x);}
	inline void era(int x){if(x!=-inf)del.push(x);}
	inline int Top(){
		while(1)
		{
			if(whl.empty()) return -inf;
			if(del.empty()) return whl.top();
			if(whl.top()==del.top()) whl.pop(),del.pop();
			else return whl.top();
		}
	}
	inline int Sec() {
		int tmp=Top();era(tmp);
		int tmp2=Top();ist(tmp);
		return tmp2;
	}
}chain[N],path[N];
inline void INS(int u,int v) {chain[u].ist(lmx[v]),path[u].ist(mxd[v]);}
inline void ERA(int u,int v) {chain[u].era(lmx[v]),path[u].era(mxd[v]);}
inline int get(int x) {return x==son[fa[x]][1];}	
inline int isnotroot(int x) {return son[fa[x]][0]==x||son[fa[x]][1]==x;}
inline void push_up(int x)
{
	sum[x]=sum[son[x][0]]+sum[son[x][1]]+len[x];
	int oth=max(0ll,chain[x].Top());
	int up=max(oth,rmx[son[x][0]])+len[x];
	int dwn=max(oth,lmx[son[x][1]])+len[x];
	lmx[x]=max(lmx[son[x][0]],sum[son[x][0]]+dwn);
	rmx[x]=max(rmx[son[x][1]],sum[son[x][1]]+up);
	mxd[x]=max(lmx[son[x][1]]+up,rmx[son[x][0]]+dwn);
	mxd[x]=max(mxd[x],max(mxd[son[x][0]],mxd[son[x][1]]));
	mxd[x]=max(mxd[x],path[x].Top());
	mxd[x]=max(mxd[x],oth+max(0ll,chain[x].Sec())+len[x]);
}

inline void rotate(int x){
	int f=fa[x],gf=fa[f],wh=get(x);
	if(isnotroot(f)) son[gf][get(f)]=x;
	son[f][wh]=son[x][wh^1];
	fa[son[x][wh^1]]=f;
	son[x][wh^1]=f;
	fa[f]=x;
	fa[x]=gf;
	push_up(f);
	push_up(x);
}

inline void splay(int x)
{
	for(int f;f=fa[x],isnotroot(x);rotate(x))
		if(isnotroot(f)) rotate(get(x)==get(f)?f:x);
}
inline int access(int x)
{
	int y;
	for(y=0;x;y=x,x=fa[x]) {splay(x);if(y)ERA(x,y);if(son[x][1])INS(x,son[x][1]);son[x][1]=y,push_up(x);}
	return y;
}
void dfs1(int u) 
{
	for(int v:e[u]) if(v^fa[u])
	{
		fa[v]=u;
		dfs1(v);
		INS(u,v);
	}
	push_up(u);
}

inline void modify(int u,int d)
{	
	access(u);
	splay(u);
	len[u]=d;
	push_up(u);
	ans=mxd[u];
}

signed main()
{
	n=read(),m=read(),MXW=read();
	int u,v,d;
	R(i,1,n-1)
	{
		u=read(),v=read(),d=read();
		e[u].pb(i+n),e[i+n].pb(u);
		e[v].pb(i+n),e[i+n].pb(v);
		len[i+n]=d;
	}
	dfs1(1);
	while(m--)
	{
		u=read(),d=read();
		u=(u+lst_ans)%(n-1)+1;
		d=(d+lst_ans)%MXW;
		//printf("u:%lld val:%lld\n",u,d);
		modify(u+n,d);
		writeln(lst_ans=ans);
	}
}
```




---

## 作者：escapist404 (赞：9)

# Solution to P6845 [CEOI2019] Dynamic Diameter

## Statement

给你一棵有 $n$ 个结点的树，边带权。

$q$ 次操作，每次修改一个边权，修改完后求树的直径。

保证 $2\le n\le 10^5$，$1\le q\le 10^5$，$1\le w\le 2\times 10^{13}$，$1\le a_i,b_i\le n$，$0\le c_i,e_j<w$，$0\le d_j<n-1$。

**本题强制在线**。

## Solution

前置知识：欧拉序，线段树。

对一棵树我们定义 $d_u$ 表示结点 $u$ 到根节点的距离。

考虑直径的定义即

$$
\max{\{d_u + d_v - 2 \cdot d_{\mathrm{lca}(u, v)}\}}, u \in T, v \in T
$$

每次修改一条边的边权 $w \gets w'$，必定影响这条边所连子树上的点的信息，效果是 $d_u \gets d_u + w' - w$。

因此考虑将 $d_i$ 拍到欧拉序上维护。

由欧拉序的性质，发现 $\mathrm{lca}(u, v)$ 至少会在 $u, v$ 之间出现一次，且 $\mathrm{lca}(u, v)$ 对应的 $d$ 是 $u, v$ 所在区间最小的。

所以设 $s$ 为欧拉序 $e$ 的长度，令序列 $a_i=d_{e_i}$，答案就是

$$
\max_{l=1}^{s} \max_{r=l}^{s}{\{a_l + a_r - 2 \cdot \min_{i=l}^{r} {a_i}\}}
$$

考虑怎么维护这个式子，就叫它直径 $d$ 吧。

想象一下我们有一个区间 $\mathbf{x} = [l, r)$，它有儿子们 $\mathbf{ls} = [l, m)$ 和 $\mathbf{rs} = [m, r)$。分类一下：

* $a_l$ 和 $\min_{i=l}^{r} {a_i}$ 出现在 $[l, m)$，$a_r$ 出现在 $[m, r)$。
* $a_l$ 出现在 $[l, m)$，$a_r$ 和 $\min_{i=l}^{r} {a_i}$ 出现在 $[m, r)$。

那我们对每一个区间设两个式子

$$
\mathrm{poly}(l) = \max_{i=l}^{r} \{a_i - 2 \cdot \min_{j=i}^{r} a_j\}
$$
$$
\mathrm{poly}(r) = \max_{i=r}^{l} \{a_i - 2 \cdot \min_{j=i}^{l} a_j\}
$$

含义分别是某个区间，选了一个 $a_i$ 后在 $a_i$ 的右边（$\mathrm{poly}(l)$）或左边（$\mathrm{poly}(r)$）选择最小值，整个式子的最大值。有了这个东西我们就能够维护 $d$

$$
d_{\mathbf{x}} =
\max\begin{cases}
d_{\mathbf{ls}}\\
d_{\mathbf{rs}}\\
\mathrm{poly}(l)_{\mathbf{ls}} + \mathrm{max}_{\mathbf{rs}}\\
\mathrm{max}_{\mathbf{ls}} + \mathrm{poly}(r)_{\mathrm{rs}}
\end{cases}
$$

怎么维护 $\mathrm{poly}(l)$ 和 $\mathrm{poly}(r)$？

不难看出我们在左儿子选一个最大值，在右儿子选一个最小值，加上原来两个区间的值就能维护 $\mathrm{poly}(l)$ 了，对于 $\mathrm{poly}(r)$ 同理。

$$
\mathrm{poly}(l)_{\mathbf{x}} =
\max\begin{cases}
\mathrm{poly}(l)_{\mathbf{ls}}\\
\mathrm{poly}(l)_{\mathbf{rs}}\\
\mathrm{max}_{\mathbf{ls}} + \mathrm{min}_{\mathbf{rs}}
\end{cases}
$$

$$
\mathrm{poly}(r)_{\mathbf{x}} =
\max\begin{cases}
\mathrm{poly}(r)_{\mathbf{ls}}\\
\mathrm{poly}(r)_{\mathbf{rs}}\\
\mathrm{min}_{\mathbf{ls}} + \mathrm{max}_{\mathbf{rs}}
\end{cases}
$$

最后维护 $\max$ 和 $\min$，我们就能维护出一个 $d$ 来。

修改呢？在欧拉序上做做文章，我们把当前要修改的边，所连的较深结点的子树进行一个区间修改即可。

设边权变化量为 $k$ 的话，这里 $\max \gets \max + \space k$，$\min \gets \min + \space k$，$\mathrm{poly}(l) \gets \mathrm{poly}(l) - \space k$，$\mathrm{poly}(r) \gets \mathrm{poly}(r) - \space k$（加上 $k$ 减去 $2k$），$d$ 没有变化（不涉及对子树内部边权的修改）。

做完了！时间复杂度 $\mathcal{O}(q \log n)$。

## Code

代码中 `dmt` 代表 $d$，`lpoly` 代表 $\mathrm{poly}(l)$，`rpoly` 同理。

代码中大多数的下标是从零开始的。

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

const int _Size = 16;

class io_r {
private:
	static char buf[];
	static int p;
	FILE* f;

public:
	inline void flush() { fread(buf, sizeof(char), 1 << _Size, f), p = 0; }
	inline io_r& operator>>(char& ch) {
		if (p == (1 << _Size)) flush();
		ch = buf[p++];
		return *this;
	}
	template <typename T>
	inline io_r& operator>>(T& x) {
		x = 0;
		short w = 1;
		char ch = 0;
		do w = ch == '-' ? -1 : w, *this >> ch;
		while (ch < '0' || ch > '9');
		do x = (x << 3) + (x << 1) + ch - '0', *this >> ch;
		while ('0' <= ch && ch <= '9');
		x *= w;
		return *this;
	}
	io_r() : f(stdin) {}
	io_r(const char* Filename, const char* Mode = "r") : f(fopen(Filename, Mode)) {
		if (!f) std::perror("File Opening Failed.");
	}
	io_r(FILE* f) : f(f) {}
};

class io_w {
private:
	static char buf[];
	static int p;
	FILE* f;

public:
	inline void flush() { fwrite(buf, p, 1, f), p = 0; }
	inline io_w& operator<<(const char c) {
		if (p == (1 << _Size)) flush();
		buf[p++] = c;
		return *this;
	}
	inline io_w& operator<<(const char* c) {
		int len = strlen(c);
		for (int i = 0; i < len; ++i) *this << c[i];
		return *this;
	}
	template <typename T>
	inline io_w& operator<<(T x) {
		if (x < 0) *this << '-', x = -x;
		static int s[50], d = 0;
		do s[++d] = x % 10, x /= 10;
		while (x);
		do *this << (char)(s[d--] + '0');
		while (d);
		return *this;
	}
	~io_w() { flush(); }
	io_w() : f(stdout) {}
	io_w(const char* Filename, const char* Mode = "w") : f(fopen(Filename, Mode)) {}
	io_w(FILE* f) : f(f) {}
};

char io_r::buf[1 << _Size];
int io_r::p = 0;
char io_w::buf[1 << _Size];
int io_w::p = 0;

// quick_io above

using i64 = long long;

struct Node {
public:
	i64 dmt, min, max, lpoly, rpoly, tag;
	Node(const i64 dmt = i64(), const i64 min = i64(), const i64 max = i64(),
		 const i64 lpoly = i64(), const i64 rpoly = i64(), const i64 tag = i64())
		: dmt(dmt), min(min), max(max), lpoly(lpoly), rpoly(rpoly), tag(tag) {}
	inline Node& operator<<(const i64 _tag) {
		return *this = Node(dmt, min + _tag, max + _tag, lpoly - _tag, rpoly - _tag, tag + _tag);
	}
};
inline Node operator+(const Node ls, const Node rs) {
	return Node(std::max({ls.dmt, rs.dmt, ls.lpoly + rs.max, ls.max + rs.rpoly}),
				std::min(ls.min, rs.min), std::max(ls.max, rs.max),
				std::max({ls.lpoly, rs.lpoly, ls.max - 2ll * rs.min}),
				std::max({ls.rpoly, rs.rpoly, rs.max - 2ll * ls.min}), i64());
}

class SegmentTree {
private:
	std::vector<i64> a;
	std::vector<Node> p;
	size_t n;
	inline size_t ls(const size_t x) { return (x << 1) + 1; }
	inline size_t rs(const size_t x) { return (x << 1) + 2; }
	inline void push_down(const size_t x) {
		p[ls(x)] << p[x].tag;
		p[rs(x)] << p[x].tag;
		p[x].tag = i64();
	}
	void build(const size_t l, const size_t r, const size_t x = 0) {
		if (r - l == 1) return p[x] << a[l], void();
		size_t mid = ((l + r) >> 1);
		build(l, mid, ls(x));
		build(mid, r, rs(x));
		p[x] = p[ls(x)] + p[rs(x)];
	}

public:
	void modify(const size_t ql, const size_t qr, const i64 k, const size_t l, const size_t r,
				const size_t x) {
		if (ql <= l && r <= qr) return p[x] << k, void();
		push_down(x);
		size_t mid = ((l + r) >> 1);
		if (ql < mid) modify(ql, qr, k, l, mid, ls(x));
		if (qr > mid) modify(ql, qr, k, mid, r, rs(x));
		p[x] = p[ls(x)] + p[rs(x)];
	}
	Node query() { return p.front(); }
	size_t size() { return a.size(); }

	SegmentTree(std::vector<i64> a) : a(a), p(a.size() << 2), n(a.size()) { build(0, n, 0); }
};

// segment tree

class Tree {
private:
	struct Edge {
		int to, nxt;
		i64 weight;
		Edge(const int to, const int nxt, const i64 weight) : to(to), nxt(nxt), weight(weight) {}
	};
	struct Edge_t {
		int father, son;
		i64 weight;
		Edge_t(const int father = int(), const int son = int(), const i64 weight = i64())
			: father(father), son(son), weight(weight) {}
	};

	int n;

	std::vector<Edge> ed;
	std::vector<int> head;
	std::vector<i64> dep;

public:
	inline void add_edge(int u, int v, i64 w) {
		ed.push_back(Edge(v, head[u], w));
		head[u] = (int)ed.size() - 1;
	}

	std::vector<Edge_t> ed_t;
	std::vector<int> euler, lbound, rbound;

	void dfs_build_euler_order(int x, int f, i64 d) {
		lbound[x] = euler.size();
		euler.push_back(x);
		dep[x] = d;
		for (int i = head[x]; ~i; i = ed[i].nxt) {
			int to = ed[i].to;
			i64 weight = ed[i].weight;
			if (to == f) continue;

			Edge_t& cur = ed_t[i >> 1];
			cur.father = x;
			cur.son = to;
			cur.weight = weight;

			dfs_build_euler_order(to, x, d + weight);
			euler.push_back(x);
		}
		rbound[x] = euler.size();
	}

	std::vector<i64> generate_dep_by_euler_order() {
		std::vector<i64> dep_t;
		for (int i : euler) {
			dep_t.push_back(dep[i]);
		}
		dep_t.pop_back();
		return dep_t;
	}

	Tree(int n) : n(n), head(n + 1, -1), dep(n + 1), ed_t(n - 1), lbound(n + 1), rbound(n + 1) {}
};

// euler order

io_r qin;
io_w qout;

int main() {
	int n, q;
	i64 w;
	qin >> n >> q >> w;

	Tree T(n);

	for (int i = 1; i < n; ++i) {
		int u, v;
		i64 w;
		qin >> u >> v >> w;
		T.add_edge(u, v, w);
		T.add_edge(v, u, w);
	}

	T.dfs_build_euler_order(1, 0, i64());

	SegmentTree S(T.generate_dep_by_euler_order());

	i64 last_ans = 0;
	while (q--) {
		int d;
		i64 e;
		qin >> d >> e;

		d = (d + last_ans) % (n - 1);
		e = (e + last_ans) % w;

		auto& cur = T.ed_t[d];
		S.modify(T.lbound[cur.son], T.rbound[cur.son], e - cur.weight, 0, S.size(), 0);
		qout << (last_ans = S.query().dmt) << '\n';
		cur.weight = e;
	}
	return 0;
}

```


---

## 作者：Seauy (赞：7)

裸的动态树直径，这题修改的则是一棵形态固定的树的边权，强制在线

这里提供两种思路

# 1. ddp

本身求直径的过程就是dp，想到动态dp也是很自然的事情

~~而且这题时限跟空间都很有迷惑性~~

但由于本人不会 $O(n\log n)$ 的全局平衡二叉树，粗略算了一下树剖的复杂度，感觉过不了就没有再推转移矩阵了

用ddp最优复杂度似乎是 $O(T(n+q\log n))$，T 是矩阵乘的复杂度，此题似乎 $T=27$

# 2. 欧拉序

本质跟ddp的思想一样，把树转换成线性问题维护

树剖是把树剖成线性的链，欧拉序则是把整棵树拉成一个序列

不懂欧拉序的同学可以[戳这里](https://blog.csdn.net/m0_37809890/article/details/82856158)，顺便了解一下怎样用欧拉序 $O(n \log n) - O(1)$ 求 LCA

这样的话我们就把求直径变成了线性维护区间的问题：

求一个区间 $[L,R]$，使得 $ A_L+A_R-2\min_{i=L}^{R} A_i $ 最大

其中 $A$ 是欧拉序每个位置上对应结点的深度构成的数列

根据树的欧拉序的性质，$ \min_{i=L}^{R} A_i $ 就是欧拉序 $L,R$ 对应结点的 LCA 深度，那么 $ A_L+A_R-2\min_{i=L}^{R} A_i $ 自然就是这两个结点的距离，距离最大化，它就是直径

由于有修改+区间问题，考虑用线段树维护，难点自然落在了维护什么、怎么维护

每个结点我们维护几个信息：

1. 整个区间的直径

2. 整个区间内深度最小的结点

3. 整个区间内深度最大的结点

4. 区间内 $ A_i-2A_j $ 的最大值（$i\leq j$）

5. 区间内 $ A_i-2A_j $ 的最大值（$i\geq j$）

6. 区间加懒标记

这里要维护区间加懒标记的原因是，当一条边的权值被修改了，仅会影响到以深度较大的端点为根的子树内的结点的深度，各信息自然也会变化

设变化量为 $\Delta $，则子树内结点的深度都要 $ +\Delta $，于是要打上区间加标记

怎样做区间合并标记下传就~~作为思考题了~~，并不是十分地难，注意分类讨论就行了。如果还是不会的话……可以私信问我

详细方法的话可以看我的代码，六个信息在结构体里依次被命名为 ans，minn，maxn，Rmax，Lmax

合并方法见结构体里的加法运算符重载，标记下放方法见 PushDown 函数

复杂度 $O(n+q\log n)$

```cpp
#include<bits/stdc++.h>
#define Lson (now<<1)
#define Rson (now<<1|1)
using namespace std;

typedef long long ll;

const int MAXN=1e5;

struct DE {int nxt;ll val;};

struct Tree
{
	int father,Beg,End;
	ll depth;
	vector<DE> E;
}node[MAXN+5];

struct UE
{
	int x,y;//x 更浅 
	ll val;
	void Scan() {scanf("%d %d %lld",&x,&y,&val);}
}Edge[MAXN+5];

struct SegNode
{
	ll LT;
	ll ans,maxn,minn;//答案与最深最浅 
	ll Lmax,Rmax;//最大的 端点-2*LCA 
	void Clean() {ans=maxn=Lmax=Rmax=LT=0;}
	SegNode operator + (const SegNode &ob)
	{
		SegNode cnt;cnt.Clean();
		cnt.maxn=max(maxn,ob.maxn);
		cnt.minn=min(minn,ob.minn);
		cnt.ans=max(max(ans,ob.ans),max(Rmax+ob.maxn,maxn+ob.Lmax));
		cnt.Lmax=max(max(Lmax,ob.Lmax),ob.maxn-2*minn);
		cnt.Rmax=max(max(Rmax,ob.Rmax),maxn-2*ob.minn);
		return cnt;
	}
	void UpDate(ll x)
	{
		LT+=x;
		maxn+=x;
		minn+=x;
		Lmax-=x;
		Rmax-=x;
	}
}SegTree[((2*MAXN)<<2)+5];

int n,q;
ll w,A[2*MAXN+5],lst;int num;

void CalMsg(int now)
{
	ll cost;
	A[++num]=node[now].depth;
	node[now].Beg=num;
	for(int i=0,rear;i<node[now].E.size();i++)
	{
		rear=node[now].E[i].nxt;
		cost=node[now].E[i].val;
		if(rear==node[now].father) continue;
		node[rear].father=now;
		node[rear].depth=node[now].depth+cost;
		CalMsg(rear);
		A[++num]=node[now].depth;
	}
	node[now].End=num;
}

void Build(int now,int L,int R)
{
	if(L==R)
	{
		SegTree[now].maxn=SegTree[now].minn=A[L];
		SegTree[now].Lmax=SegTree[now].Rmax=-A[L];
		return;
	}
	int mid=(L+R)>>1;
	Build(Lson,L    ,mid);
	Build(Rson,mid+1,R  );
	SegTree[now]=SegTree[Lson]+SegTree[Rson];
}

void PushDown(int now)
{
	if(!SegTree[now].LT) return;
	SegTree[Lson].UpDate(SegTree[now].LT);
	SegTree[Rson].UpDate(SegTree[now].LT);
	SegTree[now].LT=0;
}

void Plus(int now,int L,int R,int QL,int QR,ll v)
{
	if(QR<L || R<QL) return;
	if(QL<=L && R<=QR) {SegTree[now].UpDate(v);return;}
	PushDown(now);
	int mid=(L+R)>>1;
	Plus(Lson,L    ,mid,QL,QR,v);
	Plus(Rson,mid+1,R  ,QL,QR,v);
	SegTree[now]=SegTree[Lson]+SegTree[Rson];
}

int main()
{
	scanf("%d %d %lld",&n,&q,&w);
	for(int i=1;i<n;i++)
	{
		Edge[i].Scan();
		node[Edge[i].x].E.push_back(DE{Edge[i].y,Edge[i].val});
		node[Edge[i].y].E.push_back(DE{Edge[i].x,Edge[i].val});
	}
	CalMsg(1);
	for(int i=1;i<n;i++)
		if(node[Edge[i].x].depth>node[Edge[i].y].depth)
			swap(Edge[i].x,Edge[i].y);
	Build(1,1,num);
	for(ll d,e;q--;)
	{
		scanf("%lld %lld",&d,&e);
		d=(d+lst)%(1ll*n-1)+1;
		e=(e+lst)%w;
		Plus(1,1,num,node[Edge[d].y].Beg,node[Edge[d].y].End,e-Edge[d].val);
		printf("%lld\n",(lst=SegTree[1].ans));
		Edge[d].val=e;
	}
	return 0;
}
```


---

## 作者：云浅知处 (赞：6)

考虑按 DFS 序建线段树，每个节点维护区间直径。

那么如果修改的边是 $(x,y)$，其中 $x$ 是 $y$ 的父亲，设 $y$ 子树内 DFS 序最小值和最大值分别为 $l,r$，那么影响到的线段树节点就是所有和 $[l,r]$ 有交且不被 $[l,r]$ 包含的区间。

由线段树的性质可知这样的区间只有 $O(\log n)$ 个，暴力重新计算这些区间的信息即可。

由于 pushup 的时候需要查询链上和，所以复杂度是 $O(n\log^2n)$。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int MN=1e5+5;

int n,q,w;
int fr[MN],to[MN],val[MN];

struct BIT{
	int c[MN];
	int lowbit(int x){return x&(-x);}
	void add(int x,int k){for(int i=x;i<=n;i+=lowbit(i))c[i]+=k;}
	int sum(int x){int res=0;for(int i=x;i;i-=lowbit(i))res+=c[i];return res;}
}T;

struct Edge{
	int to,cost;
	Edge(int T,int C):to(T),cost(C){}
	Edge(){}
};

vector<Edge>G[MN];

namespace HLD{
	int dep[MN],dfn[MN],sz[MN],hson[MN],top[MN],fa[MN];
	int dis[MN],rk[MN];

	void dfs1(int u,int de){
		dep[u]=de,sz[u]=1;
		for(auto e:G[u]){
			int v=e.to,w=e.cost;
			if(v==fa[u])continue;
			dis[v]=dis[u]+w,fa[v]=u,dfs1(v,de+1),sz[u]+=sz[v];
			if(sz[v]>sz[hson[u]])hson[u]=v;
		}
	}

	int tot=0;
	void dfs2(int u,int tp){
		top[u]=tp,dfn[u]=++tot,rk[dfn[u]]=u;
		if(hson[u])dfs2(hson[u],tp);
		for(auto e:G[u]){
			int v=e.to,w=e.cost;
			if(v==fa[u]||v==hson[u])continue;
			dfs2(v,v);
		}
	}

	int LCA(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]])swap(x,y);
			x=fa[top[x]];
		}
		if(dep[x]>dep[y])swap(x,y);
		return x;
	}

	int getdis(int x){return T.sum(dfn[x]);}

	int dist(int x,int y){
		int z=LCA(x,y);
		return getdis(x)+getdis(y)-getdis(z)*2;
	}

	void build(){
		for(int i=1;i<=n;i++)T.add(i,dis[rk[i]]-dis[rk[i-1]]);
	}

	void add(int x,int k){
		int l=dfn[x],r=dfn[x]+sz[x]-1;
		T.add(l,k),T.add(r+1,-k);
	}
};

struct Node{
	int u,v;
	Node(int U,int V):u(U),v(V){}
	Node(){}
};

#define ls(p) (p<<1)
#define rs(p) (p<<1|1)

struct SegTree{
	Node d[MN<<2];

	inline void build(int l,int r,int p){
		if(l==r){
			d[p].u=d[p].v=HLD::rk[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(l,mid,ls(p)),build(mid+1,r,rs(p));
		pushup(p);
	}

	inline void pushup(int p){
		int x=d[ls(p)].u,y=d[ls(p)].v;
		int a=d[rs(p)].u,b=d[rs(p)].v;
		int mx=HLD::dist(x,y),ax=x,ay=y;
		int t=HLD::dist(x,a);if(t>mx)mx=t,ax=x,ay=a;
		t=HLD::dist(x,b);if(t>mx)mx=t,ax=x,ay=b;
		t=HLD::dist(y,a);if(t>mx)mx=t,ax=y,ay=a;
		t=HLD::dist(y,b);if(t>mx)mx=t,ax=y,ay=b;
		t=HLD::dist(a,b);if(t>mx)mx=t,ax=a,ay=b;
		d[p].u=ax,d[p].v=ay;
	}

	inline void modify(int l,int r,int ql,int qr,int p){
		if(l<=ql&&qr<=r)return ;
		int mid=(ql+qr)>>1;
		if(l<=mid)modify(l,r,ql,mid,ls(p));
		if(r>mid)modify(l,r,mid+1,qr,rs(p));
		pushup(p);
	}

	inline int get(){
		return HLD::dist(d[1].u,d[1].v);
	}
}Tree;

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif

	n=read(),q=read(),w=read();
	for(int i=1;i<=n-1;i++){
		int u=read(),v=read(),w=read();
		G[u].push_back(Edge(v,w)),G[v].push_back(Edge(u,w));
		fr[i]=u,to[i]=v,val[i]=w;
	}

	HLD::dfs1(1,1),HLD::dfs2(1,1),HLD::build();int lans=0;
	Tree.build(1,n,1);

	// cout<<HLD::getdis(1)<<" "<<HLD::getdis(2)<<" "<<HLD::getdis(3)<<" "<<HLD::getdis(4)<<endl;
	// cout<<Tree.get()<<endl;

	while(q--){
		int d=(read()+lans)%(n-1)+1,e=(read()+lans)%w;
		int u;
		if(HLD::dep[fr[d]]>HLD::dep[to[d]])u=fr[d];
		else u=to[d];
		HLD::add(u,e-val[d]);val[d]=e;
		Tree.modify(HLD::dfn[u],HLD::dfn[u]+HLD::sz[u]-1,1,n,1);
		cout<<(lans=Tree.get())<<'\n';
	}

	return 0;
}
```

---

## 作者：Starlight_Glimmer (赞：4)

[My Blog](https://www.cnblogs.com/lyttt/p/14075116.html)

[题目链接](https://www.luogu.com.cn/problem/CF1192B)

### 题目解析

唔，首先有一个比较显然的大概是$nq$级别复杂度的做法，就是暴力修改，然后$dfs$两次算出直径。

（不过这没有什么用就是了

因为有修改，我们尝试把树下下来，放到序列上，用线段树维护。

树链剖分？

不，太麻烦喏，我们知道欧拉序这个东西是可以办到的，并且我们之前就用它的性质求过$lca$：两个点对应的欧拉序区间中，深度最小的点就是这两个点的$lca$。

具体而言，设$u$在欧拉序中第一次出现的位置为$l$，$v$在欧拉序中第一次出现的位置为$r$，欧拉序数组为$E[]$，那么$lca=E[x],l<=x<=r,dep[E[x]]<=dep[E[l...r]]$

如果不知道这个结论可以看看 [这个](https://blog.csdn.net/CQBZLYTina/article/details/88660040)

那么$dist(u,v)=dis[u]+dis[v]-2\times dis[lca]$，$dis[i]$指从$1$到$i$的距离。

根据定义，树的直径是所有点对$dist$的最大值

如果用线段树维护（相当于是线段树维护与欧拉序数组对应的点的$dis$，长度为$2n-1$，完成把树变成序列的任务），那对于区间$[l,r]$的答案长这个样子：

$max\{dis[i]+dis[j]-2\times dis[lca(i,j)]\},l<=i<=j<=r$

我们注意到$lca$对于$i,j$来说是一个$rmq$问题，那......线段树套线段树？

没有必要。

具体到这道题而言，由于边权都是正数，所以$lca$也是$dis$最小的那个点，所以可以把答案化为这个样子：

$max\{dis[i]+dis[j]-2\times dis[k] \},l<=i<=k<=j<=r$

因为$dis$前面是负号，所以让这个值取$max$的那个位置一定是$dis[k]$最小的那个点，所以可以不用再维护$[i,j]$之间的最小值，而是在维护上述答案的时候自然就处理了（我感觉这里网上很多题解都没有说清楚，我看了好久）

------

接下来考虑怎么维护上述答案，主要是要便于区间合并。

我们可以把答案看成三部分：$dis[i],dis[j],-2\times dis[k]$

对于每个区间，维护：

$mx=max(dis[i]),l<=i<=r$

$mn=min(dis[i]),l<=i<=r$，（主要是为了$-2\times dis[k]$，维护$max(-dis[i])$也可

$res=max\{dis[i]+dis[j]-2\times dis[k] \},l<=i<=k<=j<=r$

为了方便左右儿子合并，也就是$i,j$可以来源于左右不同儿子，合在一起是一个更有的答案，我们还需要维护以下信息：

$rmx=max(dis[i]-2\times dis[j]),i<=j$，这个可以看成我们还需要在右边找一个右端点来组成答案。

同理，$lmx=max(dis[i]-2\times dis[j]),i<=j$

------

然后维护线段树：

$t.mx=max(lc.mx,rc.mx)$

$t.mn=min(lc.mn,rc.mn)$

$t.res=max(max(lc.res,rc.res),max(lc.rmx+rc.mx,rc.lmx+lc.mx))$

$t.rmx=max(max(lc.rmx,rc.rmx),lc.mx-2rc.mn)$

$t.lmx=max(max(lc.lmx,rc.lmx),rc.mx-2lc.mn)$

最后查询的时候是查询整棵树的直径，所以不用写$query$

------

修改的时候，答案只会对这条边深度较大的点的子树的答案产生影响，所以对子树进行更新即可（子树在欧拉序中是连续一段区间

------

### ►Code View

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
#define N 200005
#define M 200005
#define MOD 998244353
#define INF 0x3f3f3f3f
#define LL long long
LL rd()
{
	LL x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48); c=getchar();}
	return f*x;
}
struct edge{
	int nxt,v;LL w;
}e[M<<1];
int hd[N],cnt=1;
void add(int u,int v,LL w)
{
	e[++cnt].nxt=hd[u];
	e[cnt].v=v;
	e[cnt].w=w;
	hd[u]=cnt;
}

struct node{
	LL res/*直径*/,mx/*dis最大*/,mn/*dis最小*/;
	LL rmx/*dis_i-2dis_j(i<=j)的最大值 差一个右端点*/,lmx/*同理 dis_i-2dis_j(i>=j)的最大值*/;
}tree[N<<2];
LL tag[N<<2];
int n,Q;
LL W;
LL dis[N];
int E[N<<1],tim;//欧拉序 
int d1[N],d2[N];//出去进来的时间 即点i在欧拉序中的最左/最右位置 
void dfs(int u,int fa)
{
	E[++tim]=u;
	d1[u]=tim;
	for(int i=hd[u];i;i=e[i].nxt)
	{
		int v=e[i].v;LL w=e[i].w;
		if(v==fa) continue;
		dis[v]=dis[u]+w;
		dfs(v,u);
		E[++tim]=u;
	}
	d2[u]=tim;
}
node Merge(node x,node y)
{
	node t;
	t.mx=max(x.mx,y.mx);
	t.mn=min(x.mn,y.mn);
	t.rmx=max(max(x.rmx,y.rmx),x.mx-2*y.mn);
	t.lmx=max(max(x.lmx,y.lmx),y.mx-2*x.mn);
	t.res=max(max(x.res,y.res),max(x.mx+y.lmx,y.mx+x.rmx));
	return t;
}
void PushUp(int i)
{
	tree[i]=Merge(tree[i<<1],tree[i<<1|1]);
}
void Build(int i,int l,int r)
{
	if(l==r)
	{
		int u=E[l];
		tree[i].mx=tree[i].mn=dis[u];
		tree[i].rmx=tree[i].lmx=-dis[u];//dis_u-2*dis_u=-dis_u
		tree[i].res=0;//一个点不能构成直径
		tag[i]=0;
		return ;
	}
	int mid=(l+r)>>1;
	Build(i<<1,l,mid);
	Build(i<<1|1,mid+1,r);
	PushUp(i);
	return ;
}
void Modify(int i,LL val)
{
	tree[i].mx+=val,tree[i].mn+=val;
	tree[i].lmx-=val,tree[i].rmx-=val;//delta=(dis_i-val)-2*(dis_j-val)-(dis_i-2*dis_j)
	tag[i]+=val;
}
void PushDown(int i)
{
	if(tag[i])
	{
		Modify(i<<1,tag[i]);
		Modify(i<<1|1,tag[i]);
		tag[i]=0;
	}
}
void Update(int i,int l,int r,int ql,int qr,LL val)
{
	if(ql<=l&&r<=qr)
	{
		Modify(i,val);
		return ;
	}
	PushDown(i);
	int mid=(l+r)>>1;
	if(ql<=mid) Update(i<<1,l,mid,ql,qr,val);
	if(qr>mid) Update(i<<1|1,mid+1,r,ql,qr,val);
	PushUp(i);
}
int main()
{
	n=rd(),Q=rd(),W=rd();
	for(int i=1;i<=n-1;i++)
	{
		int u=rd(),v=rd();LL w=rd();
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,0);
	Build(1,1,tim);
	LL ans=0;
	while(Q--)
	{
		int id=rd(),u;LL d=rd();
		id=(id+ans)%(n-1)+1;
		d=(d+ans)%W;
		if(dis[e[id<<1].v]<dis[e[id<<1|1].v]) id=(id<<1|1),u=e[id].v;
		else id=(id<<1),u=e[id].v;
		Update(1,1,tim,d1[u],d2[u],d-e[id].w);
		e[id].w=e[id^1].w=d;
		ans=tree[1].res;
		printf("%lld\n",ans);
	}
	return 0;
}
/*
修改是给的边的编号 这个时候还是写前向星好一点吧
(怎么感觉vector一无是处了qwq 
*/
```

---

## 作者：luogu_gza (赞：3)

懒人默认 $nq$ 同阶。

题目描述极其简单，但是题目非常的难。

首先我们考虑一个性质：有点集 $A$ 与 $B$，设其直径分别为 $(a,b)$ 和 $(c,d)$，则其合并后的直径 $(s,t)$ 满足 $s,t \in \{a,b,c,d\}$。

我们利用线段树维护点集来解决问题，每次的合并明显是 $O(\log n)$ 的，因此我们用 $O(n \log^2 n)$ 解决了这个问题（无修改）。

那么带修改呢？树剖，将距离刻画为 $dis_x+dis_y-2dis_{\operatorname{lca}(x,y)}$，我们维护 $dis$ 就会发现其实修改边权等价于子树加，容易用 BIT 解决。

考虑一下哪些 segtree 上的节点的最大直径被改变了，注意到子树内和子树外的最大直径不会变化，只需要处理一半在子树内，一半在子树外的就行了。（这部分表述参考了第一篇题解，也是本题最为重要的观察）

总结：树剖，使用 segtree 维护直径，使用 BIT 维护 dis，每次修改只处理一半在子树内，一半在子树外的就行了。

这里我采用树剖处理了 lca，并且很多实现细节参考了第一篇题解（主要是边权的处理方面），可以说我是 ctj 了！

另注：为了方便改一些东西，我们使用邻接表。

这是 $O(n \log^2 n)$ 的做法，代码如下：

```cpp
// Problem: P6845 [CEOI2019] Dynamic Diameter
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6845
// Memory Limit: 1 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
namespace gza{
	#define int long long
	#define pb push_back
	#define MT int TTT=R;while(TTT--)
	#define pc putchar
	#define R read()
	#define fo(i,a,b) for(int i=a;i<=b;i++)
	#define rep(i,a,b) for(int i=a;i>=b;i--)
	#define m1(a,b) memset(a,b,sizeof a)
	namespace IO
	{
		inline int read()
		{
		    int x=0;
		    char ch=getchar();
		    bool f=0;
		    while(!isdigit(ch)){if(ch=='-') f=1;ch=getchar();}
		    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
		    if(f) x=-x;
		    return x;    
		}
		template<typename T> inline void write(T x)
		{
		    if(x<0) pc('-'),x=-x;
		    if(x>9) write(x/10);
		    pc(x%10+'0');
		}
	};
	using namespace IO;
	
	const int N=1e5+10,M=2e5+10;
	int n,q,W;
	int h[N],w[M],e[M],ne[M],idx=1;
	int dis[N],go[N];
	void add()
	{
		int a=R,b=R;
		idx++,e[idx]=b,ne[idx]=h[a],h[a]=idx;
		idx++,e[idx]=a,ne[idx]=h[b],h[b]=idx;
		w[idx>>1]=R;
	}
	int dep[N],siz[N],fa[N],son[N],top[N],dfn[N],id[N],cnt;
	void dfs1(int u,int f)
	{
		fa[u]=f,dep[u]=dep[f]+1,siz[u]=1;
		for(int i=h[u];i;i=ne[i])
		{
			int j=e[i];
			if(j!=f)
			{
				dis[j]=dis[u]+w[i>>1],go[i>>1]=j;
				dfs1(j,u);
				if(siz[j]>siz[son[u]]) son[u]=j;
				siz[u]+=siz[j];
			}
		}
	}
	void dfs2(int u,int f)
	{
		top[u]=f,dfn[u]=++cnt,id[cnt]=u;
		if(!son[u]) return;
		dfs2(son[u],f);
		for(int i=h[u];i;i=ne[i])
		{
			int j=e[i];
			if(j!=fa[u]&&j!=son[u]) dfs2(j,j);
		}
	}
	int lca(int a,int b)
	{
		while(top[a]!=top[b])
		{
			if(dep[top[a]]<dep[top[b]]) swap(a,b);
			a=fa[top[a]];
		}
		if(dep[a]>dep[b]) swap(a,b);
		return a;
	}
	#define now tr[u]
	#define ls tr[u<<1]
	#define rs tr[u<<1|1]
	#define PII pair<int,int>
	namespace finwick_tree{
		int tr[N];
		void update(int x,int c)
		{
			for(;x<=n;x+=(x&-x)) tr[x]+=c;
		}
		int query(int x)
		{
			int res=dis[id[x]];
			for(;x;x-=(x&-x)) res+=tr[x];
			return res;
		}
		void update(int x,int y,int w)
		{
			update(x,w),update(y+1,-w);
		}
	}
	int Dis(PII a)
	{
		return finwick_tree::query(dfn[a.first])+finwick_tree::query(dfn[a.second])-2*finwick_tree::query(dfn[lca(a.first,a.second)]);
	}
	namespace segtree{
		PII tr[N<<2];
		PII merge(const PII& a,const PII& b)
		{
			pair<int,int> p[6]={a,b,{a.first,b.first},{a.first,b.second},{a.second,b.first},{a.second,b.second}};
			int dis[6];
			fo(i,0,5) dis[i]=Dis(p[i]);
			return p[max_element(dis,dis+6)-dis];
		}
		void build(int u,int l,int r)
		{
			if(l==r) tr[u]={id[l],id[r]};
			else
			{
				int mid=l+r>>1;
				build(u<<1,l,mid),build(u<<1|1,mid+1,r);
				now=merge(ls,rs);
			}
		}
		void update(int u,int nl,int nr,int l,int r)
		{
			if(nl==l&&nr==r) return;
			int mid=nl+nr>>1;
			if(r<=mid) update(u<<1,nl,mid,l,r);
			else if(l>mid) update(u<<1|1,mid+1,nr,l,r);
			else update(u<<1,nl,mid,l,mid),update(u<<1|1,mid+1,nr,mid+1,r);
			now=merge(ls,rs);
		}
	}
	void main(){
		n=R,q=R,W=R;
		fo(i,2,n) add();
		dfs1(1,0),dfs2(1,1);
		segtree::build(1,1,n);
		int last=0;
		while(q--)
		{
			int e=(R+last)%(n-1)+1;
			int v=(R+last)%W;
			finwick_tree::update(dfn[go[e]],dfn[go[e]]+siz[go[e]]-1,v-w[e]),w[e]=v;
			segtree::update(1,1,n,dfn[go[e]],dfn[go[e]]+siz[go[e]]-1);
			write(last=Dis(segtree::tr[1])),puts("");
		}
	}
}
signed main(){
	gza::main();
}
```

---

## 作者：Bulyly (赞：3)

题意即需要我们在多次修改边权的情况下动态维护树的直径。

和 [P2056 捉迷藏](https://www.luogu.com.cn/problem/P2056) 类似。我们考虑利用直径的性质通过线段树来维护直径的变化。区别在于边权不是 $1/0$。套路地，计算两点间的权值我们可以用 $d_u+d_v-2 \times d_{lca(u,v)}$ 得到。当某个边的权值改变时，他所在子树的所有节点的 $d$ 都会改变。对于修改子树，我们可以通过 $dfn$ 序变化为区间修改。笔者使用的是树状数组来差分改变区间，因为会便于查询。接下来考虑变化影起的直径变化。首先子树中的直径端点不会改变，只有子树与其他区间合并的直径会有变化。所以使子树与其他区间修改后向上合并即可。递归一遍即可实现。

复杂度略微偏大，可以考虑用 **欧拉序 + RMQ** 求 LCA 优化效率。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+10,M=N<<1;
int n,Q;
int e[M],ne[M],h[N],dep[N],sz[N],idx;
ll w[M],d[N],W,last;
int f[M][20],p[N],c[N],q[N],cnt,ts;
int calc(int x,int y){return dep[x]<dep[y]?x:y;}
void add(int a,int b,ll c) {
	e[++idx]=b,ne[idx]=h[a],w[idx]=c,h[a]=idx;
}
void dfs(int u,int fa) {
	q[++ts]=u;c[u]=ts;sz[u]=1;
	f[++cnt][0]=u,p[u]=cnt,dep[u]=dep[fa]+1;
	for(int i=h[u];i;i=ne[i]) {
		int j=e[i];
		if(j==fa)  continue;
		d[j]=d[u]+w[i];dfs(j,u);
		f[++cnt][0]=u;sz[u]+=sz[j];
	}
}
void RMQ() {
	for(int k=1;k<=20;k++)
		for(int i=1;i+(1<<k)-1<=cnt;i++)
			f[i][k]=calc(f[i][k-1],f[i+(1<<(k-1))][k-1]);
}
ll dist(int a,int b){
	int l=p[a],r=p[b];
	if(l>r)  swap(l,r);
	int k=log2(r-l+1);
	int anc=calc(f[l][k],f[r-(1<<k)+1][k]);
	return T.query(c[a])+T.query(c[b])-2*T.query(c[anc]);
}
struct BIT {
	ll tr[N];
	void update(int x,ll w) {
		for(;x<=n+1;x+=x&-x)  tr[x]+=w;
	}
	ll query(int x) {
		ll res=0;
		for(;x;x-=x&-x)  res+=tr[x];
		return res;
	}
}T;
struct SGT{
	#define ls u<<1
	#define rs u<<1|1
	struct sgt{
		int a,b;ll w,maxw;
	}tr[N<<2];
	void pushup(int u) {
		if(tr[rs].maxw<tr[ls].maxw)  tr[u].maxw=tr[ls].maxw,tr[u].a=tr[ls].a,tr[u].b=tr[ls].b;
		else  tr[u].maxw=tr[rs].maxw,tr[u].a=tr[rs].a,tr[u].b=tr[rs].b;
		int x1=tr[ls].a,x2=tr[ls].b,x3=tr[rs].a,x4=tr[rs].b;
		if(tr[u].maxw<dist(x1,x3))  tr[u].maxw=dist(x1,x3),tr[u].a=x1,tr[u].b=x3;
		if(tr[u].maxw<dist(x1,x4))  tr[u].maxw=dist(x1,x4),tr[u].a=x1,tr[u].b=x4;
		if(tr[u].maxw<dist(x2,x3))  tr[u].maxw=dist(x2,x3),tr[u].a=x2,tr[u].b=x3;
		if(tr[u].maxw<dist(x2,x4))  tr[u].maxw=dist(x2,x4),tr[u].a=x2,tr[u].b=x4;
	}
	void build(int u,int l,int r) {
		if(l==r)  tr[u].a=tr[u].b=q[l],tr[u].w=T.query(c[q[l]]),tr[u].maxw=0;	
		else {
			int mid=l+r>>1;
			build(ls,l,mid);build(rs,mid+1,r);
			pushup(u);
		}	
	}
	void modify(int u,int l,int r,int ql,int qr) {
		if(l>=ql&&r<=qr)  return;
		int mid=l+r>>1;
		if(ql<=mid)  modify(ls,l,mid,ql,qr);
		if(qr>mid) modify(rs,mid+1,r,ql,qr);
		pushup(u);
	}
}S;

int main() {
	scanf("%d%d%lld",&n,&Q,&W);
	for(int i=1;i<n;i++) {
		int a,b;ll c;
		scanf("%d%d%lld",&a,&b,&c);
		add(a,b,c),add(b,a,c);
	}
	dfs(1,0);RMQ();
	for(int i=1;i<=n;i++)  T.update(i,d[q[i]]-d[q[i-1]]);
	S.build(1,1,n);
	while(Q--) {
		int d;ll x;scanf("%d%lld",&d,&x);
		d=(d+last)%(n-1)+1;x=(x+last)%W;
		int num=d*2-1,pp=dep[e[num]]>dep[e[num+1]]?e[num]:e[num+1];
		ll dt=x-w[num];
		T.update(c[pp],dt);
		T.update(c[pp]+sz[pp],-dt);
		w[num]=w[num+1]=x;
		S.modify(1,1,n,c[pp],c[pp]+sz[pp]-1);
		printf("%lld\n",last=S.tr[1].maxw);
	}
	return 0;
}
```


---

## 作者：Lates (赞：3)

边权转点权，再放到欧拉序上以后，发现变成一个区间问题。其中每个点维护原树上到根节点的边权和。设这个序列为 $\{a\}$。

不难发现这时某两个点 $x,y$ 的 LCA 必然在对应一个在序列上的极小包含这两个点的区间上，并且权值最小。所以钦定一个最小值。若不是 LCA 贡献的，必然比答案劣。于是转换成 

$$\max_{l,r}\{ a[l] +a[l]-2 \min_{l\le i\le r} a[i]\}$$

这样一个问题。于是用线段树用类似最大子段和的方法在 $[l,r]$ 维护这样几个信息。其中 $mid = \lfloor \dfrac{l+r}{2}\rfloor$

- $\max_{l\le i \le r}a[i]$
- $\min_{l\le i \le r}a[i]$
- $\max_{l\le i\le mid,mid+1 \le j\le r}a[i]-2a[j] $
- $\max_{l\le i\le mid,mid+1 \le j\le r}-2a[i]+a[j] $
- $\max_{l,r}\{ a[l] +a[l]-2 \min_{l\le i\le r} a[i]\}$

由于每个点维护的是点到根的路径，不难发现修改一条边，也就是线段树上两个节点，会影响所谓“极小的区间”里的权值。具体体现为区间覆盖。





---

## 作者：wind_whisper (赞：3)

# $\text{Foreword}$
~~水一发题解的双倍经验~~  
[双倍经验传送门](https://www.luogu.com.cn/problem/CF1192B)  
@zhengrunzhe 大佬的矩阵做法过于神奇，蒟蒻无法理解...   
欧拉序的做法确实非常巧妙，但我也想不到这么神仙的做法...  
提供一种可能简单一些的 LCT 做法。  
由于本人 LCT 无法像大佬那么神，讲的会比较详细一些，也许对其他 LCT 平民玩家更加友好？
# $\text{Solution}$
本题有一个很关键的性质：**边权非负**。（欧拉序的做法也要基于这个性质）  
又发现修改无非改大/小，在/不在原直径上，利用非负的性质分别讨论一下，就会发现**新直径至少有一个节点和原来相同**。  
所以我们一开始暴力求出直径后，只需要不断把原直径的两端点提出来，用从二者出发新的最长路径来尝试作为新直径就行了。  
所以现在只需要动态维护**从一个点出发的最长路径**。  

常规套路，先边化点，边权化点权。  
设 $w_x$ 表示 $x$ 的点权，$sum_x$ 表示 $x$ splay子树内点权之和，$dis_x$ 表示从 $x$ **所在 splay 子树内深度最浅的节点出发**往子树延伸的最长路径。  
先不考虑 $x$ 实链父亲，尝试求出**从 $x$ 出发**往子树延伸的最长路径 $res_x$。    

一开始有： 
$$res_x=w_x$$
对于 $x$ 的虚儿子，对每个节点开一个 `std::set`  维护虚子树，进行转移：
$$res_x\gets \max_{son}dis_{son}+w_x$$
还有从 $x$ 的实儿子转移，不难发现其对应的就是 $dis_{rs_x}$：
$$res_x\gets dis_{rs_x}+w_x$$
求完 $res_x$ 后，如果 $x$ 没有左儿子，说明他就是链头，直接让 $dis_x=res_x$ 即可；否则，链头可以不使用 $res_x$ 的转移，或者使用 $res_x$ 的转移，那么还要加上 $x$ 到链头一段的权值和，分别对应 `max` 的前后两项：
$$dis_x=\max(dis_{ls_x},res_x+sum_{ls_x})$$

这样就做完了。由于转移不对称，所以我们还要镜像的处理一个 $dis'x$，在翻转时直接交换两项即可。
# $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define ok debug("OK\n")
using namespace std;

const int N=2e5+100;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)) {if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m;


#define pr pair<ll,int>
#define mkp make_pair
pr operator + (const pr &o,const ll &w){return mkp(o.first+w,o.second);}

int tr[N][2],rev[N],f[N];
ll sum[N],w[N];
pr dis1[N],dis2[N];
multiset<pr>s[N];
#define ls(x) tr[x][0]
#define rs(x) tr[x][1]
inline bool nroot(int x){return ls(f[x])==x||rs(f[x])==x;}
inline bool which(int x){return rs(f[x])==x;}

inline void pushup(int x){
  sum[x]=w[x]+sum[ls(x)]+sum[rs(x)];
  
  dis1[x]=s[x].empty()?mkp(w[x],x<=n?x:-1):(*s[x].rbegin())+w[x];
  if(rs(x)) dis1[x]=max(dis1[x],dis1[rs(x)]+w[x]);
  if(ls(x)) dis1[x]=max(dis1[ls(x)],dis1[x]+sum[ls(x)]);
  
  dis2[x]=s[x].empty()?mkp(w[x],x<=n?x:-1):(*s[x].rbegin())+w[x];
  if(ls(x)) dis2[x]=max(dis2[x],dis2[ls(x)]+w[x]);
  if(rs(x)) dis2[x]=max(dis2[rs(x)],dis2[x]+sum[rs(x)]);
  
  return;
}
inline void Rev(int x){
  if(x){
    rev[x]^=1;
    swap(ls(x),rs(x));
    swap(dis1[x],dis2[x]);
  }
  return;
}
inline void pushdown(int x){
  if(rev[x]){
    rev[x]=0;
    Rev(ls(x));
    Rev(rs(x));
  }
  return;
}
void dfs(int x){
  if(!x) return;
  pushdown(x);
  debug("x=%d f=%d ls=%d rs=%d w=%lld dis1=(%lld %d) s: ",x,f[x],ls(x),rs(x),w[x],dis1[x].first,dis1[x].second);
  for(pr o:s[x]) debug("(%lld %d) ",o.first,o.second);
  debug("\n");
  dfs(ls(x));dfs(rs(x));
}
void print(){
  for(int i=1;i<=n+n-1;i++){
    if(!nroot(i)) dfs(i);
  }
}
inline void rotate(int x){
  int fa=f[x],gfa=f[fa];
  int d=which(x),son=tr[x][d^1];
  f[x]=gfa;if(nroot(fa)) tr[gfa][which(fa)]=x;
  f[fa]=x;tr[x][d^1]=fa;
  if(son) {f[son]=fa;}tr[fa][d]=son;
  pushup(fa);pushup(x);
  return;
}
int zhan[N];
inline void splay(int x){
  int top=0,y=x;
  zhan[++top]=y;
  while(nroot(y)) zhan[++top]=y=f[y];
  while(top) pushdown(zhan[top--]);
  for(int fa;fa=f[x],nroot(x);rotate(x)){
    if(nroot(fa)) which(fa)==which(x)?rotate(fa):rotate(x);
  }
  return;
}
inline void access(int x){
  for(int y=0;x;y=x,x=f[x]){
    splay(x);
    if(rs(x)){
      s[x].insert(dis1[rs(x)]);
    }
    if(y){
      s[x].erase(s[x].find(dis1[y]));
    }
    rs(x)=y;
    pushup(x);
  }
  return;
}
inline void makeroot(int x){
  access(x);splay(x);Rev(x);
}
inline void link(int x,int y){
  makeroot(x);makeroot(y);
  f[x]=y;
  s[y].insert(dis1[x]);
  pushup(y);
  return;
}

ll mod;
ll D;
int a,b;
signed main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  #endif
  n=read();m=read();mod=read();
  for(int i=1;i<n;i++){
    int x=read(),y=read();
    w[n+i]=read();
    link(x,n+i);
    link(y,n+i);
  }
  for(int i=1;i<=n;i++){
    makeroot(i);
    if(dis1[i].first>D){
      D=dis1[i].first;
      a=i;b=dis1[i].second;
    }
  }
  ll lst=0;
  while(m--){
    ll x=(read()+lst)%(n-1)+1 +n,ww=(read()+lst)%mod;    
    makeroot(x);
    w[x]=ww;pushup(x);
    int u=a,v=b;
    D=a=b=0;

    makeroot(u);
    if(dis1[u].first>=D){
      D=dis1[u].first;
      a=u;b=dis1[u].second;
    }
    
    makeroot(v);
    if(dis1[v].first>=D){
      D=dis1[v].first;
      a=v;b=dis1[v].second;
    }

    printf("%lld\n",lst=D);
  }
  return 0;
}
/*
*/
 
```


---

## 作者：lory1608 (赞：2)

### $\text{[CEOI2019] Dynamic Diameter}$ 题解

~~为什么没有人写DDP，为什么我的DDP比欧拉序还快。~~

首先对于树的直径，我们有一个非常暴力的DP，设 $f_{u,0/1}$ 表示在 $u$ 的子树内选择一条完整的链和选择一条还可以向上走的链(并且包含向上走的那一条边)的最大权值，转移方程如下：
$$
f_{u,0}=\max{f_{v,0}+w_{fa_u,u}},f_{u,1}=\max\{f_{v,1},f_{v,0}+f_{u,0}\}
$$
我们设 $g_{u,0/1}$ 是除了 $u$ 的重儿子的贡献。

对此我们可以考虑动态DP，构造转移矩阵如下：
$$
\begin{bmatrix} 0 & -inf & g_{u,0} \\ g_{u,0} & 0 & g_{u,1} \\ -inf & -inf & 0 \end{bmatrix}
$$
转移就是：
$$
\begin{bmatrix} 0 & -inf & g_{u,0} \\ g_{u,0} & 0 & g_{u,1} \\ -inf & -inf & 0 \end{bmatrix} \times \begin{bmatrix} f_{son_u},0 \\ f_{son_u},1 \\ 0 \end{bmatrix}=\begin{bmatrix} f_{u},0 \\ f_{u},1 \\ 0 \end{bmatrix}
$$
我们用重链剖分套线段树维护这个矩阵，对于修改我们对每个节点维护两个`multiset`分别维护不为重儿子的点 $v$ 的 $f_{v,0},f_{v,1}$ 的值，这样就方便转移了（选择两条最长的链或者选择子树内最长的链）。

这样做，由于每次只会对所有跳过的点的`multiset`中的元素进行修改，所以总复杂度为 $\Theta(Tn\log^2n)$ （其中T为矩阵乘法的复杂度，为 $3^3=27$） 的，虽然看起来很不可过的样子，但是这只是理论，实践起来甚至比有的实现较劣的欧拉序+线段树还要快。

代码如下：

```cpp
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(u) for(int i=p[u];i!=-1;i=e[i].nxt)
#define ll long long
#define sz(x) (int)(x.size())
#define PII pair<int,int>
#define pb push_back
#define rd (rand()<<16^rand())
#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char buf[100000],*p1=buf,*p2=buf;
inline ll gi()
{
	ll x=0,f=1;char ch=gc;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc;}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48),ch=gc;}
	return (f==1)?x:-x;
}
const int maxn=1e5+5;
const ll inf=1e18;
int n,q,a,b;
ll W;
int u[maxn],v[maxn];
vector<pair<int,ll> >e[maxn];
ll dep[maxn],w[maxn];
struct Matrix
{
	ll a[3][3];
	inline void clear(){memset(a,0xcf,sizeof(a));}
	inline Matrix operator * (const Matrix &b)const
	{
		Matrix c;c.clear();
		FOR(k,0,2)FOR(i,0,2)FOR(j,0,2)c.a[i][j]=max(c.a[i][j],a[i][k]+b.a[k][j]);
		return c;
	}
};
///HLD
int dfn[maxn],tot,son[maxn];
ll f[maxn][2];
int fa[maxn],tp[maxn],bot[maxn],siz[maxn],rk[maxn];
inline void dfs(int u)
{
	dep[u]=dep[fa[u]]+1;
	siz[u]=1;f[u][0]=f[u][1]=0;
	for(auto x:e[u])
	{
		int v=x.first;ll w=x.second;
		if(v==fa[u])continue;
		fa[v]=u,dfs(v),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
		f[u][1]=max(f[u][1],max(f[v][1],f[u][0]+f[v][0]+w));
		f[u][0]=max(f[u][0],f[v][0]+w);
	}
	f[u][1]=max(f[u][1],f[u][0]);
}
Matrix now[maxn];
multiset<ll>s[maxn],s2[maxn]; 
ll val[maxn];
inline void work(int u)
{
	memset(now[u].a,0,sizeof(now[u].a));
	if(!son[u])return now[u].a[0][0]=val[u],void();///special
	now[u].a[0][0]=val[u];
	now[u].a[0][1]=now[u].a[2][0]=now[u].a[2][1]=-inf;
	if(!s[u].empty())now[u].a[0][2]=*(--s[u].end());
	now[u].a[1][0]=now[u].a[0][2],now[u].a[0][2]+=val[u];
	if(!s2[u].empty())now[u].a[1][2]=*(--s2[u].end());
	now[u].a[1][2]=max(now[u].a[1][2],now[u].a[1][0]);
	if(s[u].size()>=2)now[u].a[1][2]=max(now[u].a[1][2],*(--s[u].end())+(*(--(--s[u].end()))));
}
inline void dfs2(int u,int topf)
{
	s[u].clear();
	dfn[u]=++tot,rk[tot]=u;tp[u]=topf;
	if(son[u])dfs2(son[u],topf),bot[u]=bot[son[u]];
	else bot[u]=u;
	///g expect the heavy son
	for(auto x:e[u])
	{
		int v=x.first;ll w=val[v];
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
		s[u].insert(f[v][0]+w);s2[u].insert(f[v][1]);
	}
	work(u);
}
///HLD 
struct segmentree
{
	#define ls u<<1
	#define rs u<<1|1
	static const int maxn=4e5+5;
	Matrix sum[maxn];
	inline void pushup(int u)
	{
		sum[u]=sum[ls]*sum[rs];
	}
	inline void build(int u,int l,int r)
	{
		if(l==r)return sum[u]=now[rk[l]],void();
		int mid=(l+r)>>1;
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(u);
	}
	inline void update(int u,int l,int r,int x)
	{
		if(l==r)return sum[u]=now[rk[l]],void();
		int mid=(l+r)>>1;
		if(x<=mid)update(ls,l,mid,x);
		else update(rs,mid+1,r,x);
		pushup(u);
	}
	inline Matrix query(int u,int l,int r,int x,int y)
	{
		if(x<=l&&y>=r)return sum[u];
		int mid=(l+r)>>1;
		if(y<=mid)return query(ls,l,mid,x,y);
		if(x>mid)return query(rs,mid+1,r,x,y);
		return query(ls,l,mid,x,y)*query(rs,mid+1,r,x,y);
	}
}tree;
inline void update(int v,ll w)
{
	now[v].a[0][0]+=w,now[v].a[0][2]+=w;
	while(v)
	{
		Matrix temp=tree.query(1,1,n,dfn[tp[v]],dfn[bot[v]]);
		tree.update(1,1,n,dfn[v]);
		if(tp[v]!=1)
		{
			int u=v;
			Matrix temp2=tree.query(1,1,n,dfn[tp[u]],dfn[bot[u]]);
			s[fa[tp[u]]].erase(s[fa[tp[u]]].find(temp.a[0][0]));
			s[fa[tp[u]]].insert(temp2.a[0][0]);
			s2[fa[tp[u]]].erase(s2[fa[tp[u]]].find(temp.a[1][0]));
			s2[fa[tp[u]]].insert(temp2.a[1][0]);
			work(fa[tp[u]]);
		}
		v=fa[tp[v]];
	}
}
inline void init()
{

}
inline void input()
{
	n=gi(),q=gi(),W=gi();
	FOR(i,1,n-1)
	{
		u[i]=gi(),v[i]=gi(),w[i]=gi();
		e[u[i]].pb({v[i],w[i]});e[v[i]].pb({u[i],w[i]});
	}
}
inline void solve()
{
	dfs(1);
	FOR(i,1,n-1)if(dep[u[i]]>dep[v[i]])swap(u[i],v[i]);
	FOR(i,1,n-1)val[v[i]]=w[i];
	dfs2(1,1);
	tree.build(1,1,n);
	ll ans=0;
	FOR(i,1,q)
	{
		int d=gi();ll value=gi();
		d=(d+ans)%(n-1)+1,value=(value+ans)%W;
		update(v[d],value-val[v[d]]);
		val[v[d]]=value;
		ans=tree.query(1,1,n,dfn[1],dfn[bot[1]]).a[1][0];
		printf("%lld\n",ans);
	}
}
int main()
{
//	freopen("diameter.in","r",stdin);
//	freopen("diameter.out","w",stdout);
	init();
	input();
	solve();
	return 0;
}
```



---

