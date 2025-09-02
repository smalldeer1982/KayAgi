# 星座 3 (Constellation 3)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2020/tasks/joisc2020_g



# 题解

## 作者：Creeper_l (赞：2)

会发现题目的坐标其实是平面直角坐标系。

我们按 $y$ 坐标从小到大考虑所有的星星，假设当前考虑到了星星 $i$。我们先计算出之前所有能够影响到 $i$ 的星星的代价和为 $cost$（可以用树状数组维护）。然后分类讨论。

若 $c_i \le cost$，那么肯定直接将 $i$ 直接涂黑，因为它更容易影响到后面的星星，并且删除它的代价更小。

若 $cost < c_i$，我们可以用一种类似于反悔贪心的思路。先假设把 $cost$ 全部涂黑，然后在树状数组中的 $[l,r]$ 区间加上 $c_i-cost$（$[l,r]$ 表示 $i$ 能影响到的区间），这样之后考虑星星 $j$ 的时候，如果需要涂黑星星 $i$，那么 $cost$ 中的一部分代价也会被加回去（但是不一定全部都加回去，因为 $cost$ 中的一些星星也会影响 $j$）。如果不需要涂黑 $i$，那么肯定也不会计算到 $[l,r]$ 的贡献。

然后就做完了，维护每颗星星的 $[l,r]$ 可以用并查集做。时间复杂度 $O(n \log n)$。

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair <int,int> pii;
const int MAXN = 2e5 + 10;
int n,a[MAXN],m,x[MAXN],y[MAXN],c[MAXN];
vector <pii> v[MAXN];
vector <int> f[MAXN];  
int tree[MAXN],ans = 0,fal[MAXN],far[MAXN];
inline int Lowbit(int x) {return x & -x;}
inline void Add(int x,int c) {for(;x <= n;x += Lowbit(x)) tree[x] += c;}
inline int Query(int x) {int r = 0;for(;x;x -= Lowbit(x)) r += tree[x];return r;}
inline int Findl(int x) {if(fal[x] == x) return x;return fal[x] = Findl(fal[x]);}
inline int Findr(int x) {if(far[x] == x) return x;return far[x] = Findr(far[x]);}
signed main() {
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 0;i <= n + 1;i++) fal[i] = far[i] = i;
	for(int i = 1;i <= n;i++) f[a[i]].emplace_back(i); 
	cin >> m;
	for(int i = 1;i <= m;i++) 
		cin >> x[i] >> y[i] >> c[i],
		v[y[i]].emplace_back(make_pair(x[i],c[i]));
	for(int i = 1;i <= n;i++) {
		for(pii j : v[i]) {
			int cost = Query(j.first);
			if(j.second <= cost) ans += j.second;
			else ans += cost,
				Add(Findl(j.first) + 1,j.second - cost),
				Add(Findr(j.first),cost - j.second);
		}
		for(int j : f[i]) 
			fal[Findl(j)] = Findl(j - 1),
			far[Findr(j)] = Findr(j + 1);
	} cout << ans; return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：2)

# JOISC2020G 题解

[Problem Link](https://qoj.ac/problem/3558)

**题目大意**

> 给定一个 $n\times n$ 的矩形棋盘，第 $i$ 列的 $(i,1)\sim (i,a_i)$ 从棋盘上被删掉。
>
> 在现有的棋盘上有 $m$ 个点，每个星星有权值，你可以保留若干个点使得棋盘上不存在任何一个完整的矩形同时包含至少两个点，最小化删除点的权值和。
>
> 数据范围：$n,m\le 2\times 10^5$。

**思路分析**

考虑建立大根笛卡尔树，对于笛卡尔树上的一个点 $i$，$[l_i,r_i]$ 中高度 $>a_i$ 的点不能超过 $2$ 个。

因此有一个简单 dp，$dp_{i,j}$ 表示 $i$ 子树内保留若干个点，其中高度最大值为 $j$。

那么转移的时候从左右儿子转移，设 $x=\max_{j\le a_i} \{dp_{ls,j}\},y=\max_{j\le a_i}\{dp_{rs,j}\}$。

那么对于 $j>a_i$ 的 $j$ 有 $dp_{i,j}=\max\{dp_{ls,j}+y,dp_{rs,j}+x\}$。

对于 $j\le a_i$ 的 $j$，我们发现这些状态全部等价，我们只要记录其中的最大值，显然这个值是 $x+y$。

考虑整体 dp，用线段树维护，支持区间加，单点赋值，查询区间最大值，线段树合并。

时间复杂度 $\mathcal O((n+m)\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5;
struct SegmentTree {
	static const int MAXS=8e6+5;
	int ls[MAXS],rs[MAXS],tot;
	ll mx[MAXS],tag[MAXS];
	inline void psu(int p) { mx[p]=max(mx[ls[p]],mx[rs[p]]); }
	inline void adt(int p,ll v) { if(p) mx[p]+=v,tag[p]+=v; }
	inline void psd(int p) { adt(ls[p],tag[p]),adt(rs[p],tag[p]),tag[p]=0; }
	inline void ins(int u,ll v,int l,int r,int &p) {
		if(!p) p=++tot;
		if(l==r) return mx[p]=max(mx[p],v),void();
		int mid=(l+r)>>1; psd(p);
		if(u<=mid) ins(u,v,l,mid,ls[p]);
		else ins(u,v,mid+1,r,rs[p]);
		psu(p);
	}
	inline void add(int ul,int ur,ll v,int l,int r,int p) {
		if(ul<=l&&r<=ur) return adt(p,v);
		int mid=(l+r)>>1; psd(p);
		if(ul<=mid) add(ul,ur,v,l,mid,ls[p]);
		if(mid<ur) add(ul,ur,v,mid+1,r,rs[p]);
		psu(p);
	}
	inline ll qry(int ul,int ur,int l,int r,int p) {
		if(ul<=l&&r<=ur) return mx[p];
		int mid=(l+r)>>1; psd(p);
		if(ur<=mid) return qry(ul,ur,l,mid,ls[p]);
		if(mid<ul) return qry(ul,ur,mid+1,r,rs[p]);
		return max(qry(ul,ur,l,mid,ls[p]),qry(ul,ur,mid+1,r,rs[p]));
	}
	inline void merge(int l,int r,int q,int &p) {
		if(!q||!p) return p|=q,void();
		if(l==r) return mx[p]=max(mx[p],mx[q]),void();
		int mid=(l+r)>>1; psd(p),psd(q);
		merge(l,mid,ls[q],ls[p]),merge(mid+1,r,rs[q],rs[p]);
		psu(p);
	}
}	T;
int n,m,a[MAXN],st[MAXN][20],rt[MAXN];
inline int cmp(int x,int y) { return a[x]>a[y]?x:y; }
struct Node { int x,y,w; };
vector <Node> pi[MAXN];
inline int bit(int x) { return 1<<x; }
inline int qry(int l,int r) {
	int k=__lg(r-l+1);
	return cmp(st[l][k],st[r-bit(k)+1][k]);
}
inline int solve(int l,int r) {
	int p=qry(l,r);
	for(auto q:pi[p]) T.ins(q.y,q.w,1,n,rt[p]);
	auto merge=[&](int u) {
		ll x=T.qry(1,a[p],1,n,rt[p]),y=T.qry(1,a[p],1,n,rt[u]);
		if(a[p]<n) T.add(a[p]+1,n,y,1,n,rt[p]),T.add(a[p]+1,n,x,1,n,rt[u]);
		T.merge(1,n,rt[u],rt[p]),T.ins(a[p],x+y,1,n,rt[p]);
	};
	if(l<p) merge(solve(l,p-1));
	if(p<r) merge(solve(p+1,r));
	return p;
}
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),st[i][0]=i;
	for(int k=1;k<=20;++k) for(int i=1;i+bit(k-1)<=n;++i) {
		st[i][k]=cmp(st[i][k-1],st[i+bit(k-1)][k-1]);
	}
	scanf("%d",&m);
	ll sum=0;
	for(int i=1,x,y,w;i<=m;++i) scanf("%d%d%d",&x,&y,&w),pi[x].push_back({x,y,w}),sum+=w;
	printf("%lld\n",sum-T.mx[rt[solve(1,n)]]);
	return 0;
}
```



---

## 作者：Purslane (赞：1)

# Solution

考虑只有  $O(n)$ 个本质不同的矩形，他们正好符合笛卡尔树的结构。

一个点影响到的矩形，恰好是笛卡尔树上的一条链。因此问题变为：在树上选若干条互不相交的路径，使得所选中的路径的权值和最大。这是可以用树状数组解决的经典问题。

复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,m,a[MAXN],rt,sum[MAXN],fa[MAXN][20],al,sze[MAXN],dp[MAXN],dfn[MAXN],tot,tr[MAXN];
vector<int> G[MAXN];
pair<int,int> st[MAXN][20];
pair<int,int> query(int l,int r) {
	int k=log2(r-l+1);
	return max(st[l][k],st[r-(1<<k)+1][k]);	
}
int build(int l,int r) {
	if(l>r) return 0;
	int rt=query(l,r).second;
	int ls=build(l,rt-1),rs=build(rt+1,r);
	if(ls) G[rt].push_back(ls),fa[ls][0]=rt;
	if(rs) G[rt].push_back(rs),fa[rs][0]=rt;
	return rt;
}
void dfs(int u) {
	dfn[u]=++tot,sze[u]=1;
	ffor(i,1,19) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(auto v:G[u]) dfs(v),sze[u]+=sze[v];
	return ;
}
int find(int u,int lim) {
	roff(i,19,0) if(fa[u][i]&&a[fa[u][i]]<lim) u=fa[u][i];
	return u;	
}
void update(int pos,int v) {
	while(pos<=n) tr[pos]+=v,pos+=pos&-pos;
	return ;	
}
int query(int pos) {
	int ans=0;
	while(pos) ans+=tr[pos],pos-=pos&-pos;
	return ans;
}
vector<pair<int,int>> upd[MAXN];
void updd(int u,int v) {
	update(dfn[u],v),update(dfn[u]+sze[u],-v);
	return ;
}
void DFS(int u) {
	for(auto v:G[u]) DFS(v),dp[u]+=dp[v];
	if(G[u].size()==2) updd(G[u][0],dp[G[u][1]]),updd(G[u][1],dp[G[u][0]]);
	sum[u]=dp[u];
	for(auto pr:upd[u]) {
		int v=pr.first,c=pr.second;
		dp[u]=max(dp[u],query(dfn[v])+sum[v]+c);
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i],st[i][0]={a[i],i};
	ffor(len,1,19) for(int l=1,r=(1<<len);r<=n;l++,r++) st[l][len]=max(st[l][len-1],st[l+(1<<len-1)][len-1]);
	rt=build(1,n);
	dfs(rt);
	cin>>m;
	ffor(i,1,m) {
		int x,y,c;
		cin>>x>>y>>c;
		upd[find(x,y)].push_back({x,c}),al+=c;	
	}
	DFS(rt);
	cout<<al-dp[rt];
	return 0;
}
```

---

## 作者：tony0530 (赞：0)

# 题解

反悔贪心。

我们按 $y$ 坐标从小到大考虑所有的星星，假设当前考虑到了星星 $i$。我们先计算出之前所有能够影响到 $i$ 的星星的代价和为 $cost$。然后分类讨论。

-  如果 $c_i \le cost$ 都不用反悔贪心，直接涂黑 $i$。
-  否则我们考虑如何反悔贪心，先把 $i$ 影响到的区间涂黑，然后将 $i$ 影响的星星区间 $[l,r]$ 加上 $c_i −cost$,这样如果要涂黑 $i$，一部分的代价就会返回，这样子就做完了。

我们计算出之前所有能够影响到 $i$ 的星星的代价和用树状数组求就好了，而 $i$ 影响的星星区间 $[l,r]$ 用并查集维护即可。

# 代码

```cpp#include <bits/stdc++.h>

#define x first
#define y second
#define int long long

using namespace std;

const int N = 2e5 + 10;

int n, m;
int a[N];
int x[N], y[N];
int c[N];
vector<pair<int, int>> v[N];
vector<int> f[N];
int tr[N];
int pl[N], pr[N];
int ans = 0;

int lowbit(int x)
{
    return x & -x;
}
void add(int x, int c)
{
    for(int i = x ; i <= n ; i += lowbit(i)) tr[i] += c;
}

int query(int x)
{
    int sum = 0;
    for(int i = x ; i >= 1 ; i -= lowbit(i)) sum += tr[i];
    return sum;
}

int findl(int x)
{
    if(pl[x] != x) pl[x] = findl(pl[x]);
    return pl[x];
}

int findr(int x)
{
    if(pr[x] != x) pr[x] = findr(pr[x]);
    return pr[x];
}

signed main()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i ++ ) cin >> a[i];
    for(int i = 0 ; i <= n + 1 ; i ++ ) pl[i] = i;
    for(int i = 0 ; i <= n + 1 ; i ++ ) pr[i] = i;
    for(int i = 1 ; i <= n ; i ++ ) f[a[i]].push_back(i);
    cin >> m;
    for(int i = 1 ; i <= m ; i ++ ) cin >> x[i] >> y[i] >> c[i];
    for(int i = 1 ; i <= m ; i ++ ) v[y[i]].push_back({x[i], c[i]});
    
    for(int i = 1 ; i <= n ; i ++ )
    {
        for(auto j : v[i])
        {
            int cost = query(j.x);
            if(j.y <= cost) ans += j.y;
            else ans += cost, add(findl(j.x) + 1, j.y - cost), add(findr(j.x), cost - j.y);
        }
        for(int j : f[i]) pl[findl(j)] = findl(j - 1), pr[findr(j)] = findr(j + 1);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

首先你要读懂题，最好看一眼原题面的样例 1 解释图。

![](https://cdn.luogu.com.cn/upload/image_hosting/tmyizeuk.png)

我们的问题是保证两两星星之间都有白色格子挡住，而要处理的关键点就是星星之间的不能共存。我们要尝试刻画这个不能共存的星星的形态。

很容易想到按 $y$ 轴扫描线，这样每次可能会被当前星星 $(x, y)$ 影响到的位置就会是一个区间，这个区间是形如以 $y$ 为单峰的白色。上面那个图中的第三个星星的区间就是 $[1,2]$，第一个星星的区间是 $[1,5]$，可以手模扫描线的过程模拟。考虑维护这个区间，每次对于 $a_i=y$ 的 $i$，尝试向左右扩展，使用并查集维护这一过程。

我们考虑一个星星要不要删掉，设当前星星代价为 $z$，你这个星星如果要选，前面某些星星可能就不能选了，设前面所有不能选的星星代价之和 $w$ ，如果 $z \le w$ 显然要删，因为当前星星会更多地使后面的位置不能选。而对于 $z > w$ 的情况就考虑反悔贪心。我们先认为保留当前的星星而不要前面的星星，在影响的区间 $[l, r]$ 中，类似差分的想法，维护树状数组，在 $l$ 处标记 $z-w$，在 $r+1$ 处标记 $w-z$，对于一个星星，$w$ 就是 $x$ 的前缀和，这样对于一个被影响的星星，他能尝试 $z-w$ 的反悔决策，而对于一个不被影响的星星，就没有这个决策了。

为什么可以直接舍弃前面的不考虑对后面的影响，因为对于扫描线上从前到后出现的 $a,b,c$ 三个星星，如果有白色挡住了 $b,c$，那 $a,c$ 或者 $a,b$ 也会被挡住，$z \le w$ 的情况大概也是这个道理。

说得可能有点抽象，可以对照代码看看。注意代码里的合法区间左右多了一个位置。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define test cerr << "test\n"
#define print(x) cout << #x << " = " << x << endl
#define file(name) freopen(name".in", "r", stdin), freopen(name".out", "w", stdout);

const int N = 2e5 + 5;
int n, m; vector <int> x[N]; vector <pair <int, int>> v[N];
int l[N], r[N], c[N]; int qwq(int x) { return x & (-x); }
int L(int x) { return l[x] == x ? x : l[x] = L(l[x]); }
int R(int x) { return r[x] == x ? x : r[x] = R(r[x]); }
void update(int x, int k) { for (; x <= n; x += qwq(x)) c[x] += k; }
int query(int x) { int a = 0; for (; x; x -= qwq(x)) a += c[x]; return a; }

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n; int ans = 0; for (int i = 0; i <= n + 1; i++) l[i] = r[i] = i;
    for (int i = 1, y; i <= n; i++) cin >> y, x[y].push_back(i);
    cin >> m; for (int x, y, z; m--; ) cin >> x >> y >> z, v[y].push_back({x, z});
    for (int y = 1; y <= n; y++) {
        for (auto [x, z] : v[y]) {
            int w = query(x); if (w >= z) ans += z;
            else ans += w, update(L(x) + 1, z - w), update(R(x), w - z);
        }
        for (int p : x[y]) l[p] = L(p - 1), r[p] = R(p + 1);
    } cout << ans;
    return 0;
}
```

---

## 作者：myee (赞：0)

### 思路

翻转一下问题，设处于同一个合法矩形内的点可以连边，容易发现就是求最大权独立集。

考虑自下往上扫描，记录当 $p$ 列格子**还可以在上面选择**时的当前已没有白船的区间的答案以及 $p$ 列**可能已经有被选择的元素**时当前已没有白船的区间的答案。

分别设为 $f_p$，$g_p$。

则当 $p$ 处增加一颗星时，我们更新

$$g_p\leftarrow\max\{g_p,f_p+c\}$$

当 $p$ 处无白船后，设新区间为 $[l,r]$，我们更新

$$\forall l\le i<p,f_i\leftarrow f_i+\max_{p<j\le r}g_j,g_i\leftarrow g_i+\max_{p<j\le r}g_j$$

$$f_p,g_p\leftarrow\max_{l\le j<p}g_j+\max_{p<j\le r}g_j$$

$$\forall p<i\le r,f_i\leftarrow f_i+\max_{l\le j<p}g_j,g_i\leftarrow g_i+\max_{l\le j<p}g_j$$

最后 $\sum c-\max g$ 即为答案。

对 $f$ 需要区间加、单点查询，对 $g$ 需要单点修改、区间加、区间查 $\max$。显然这些都可以线段树维护。

$n,m$ 同阶，复杂度 $O(n\log n)$。

### Code

因为一开始做复杂了所以 $f$ 也用了线段树维护，后来发现可以直接写一个 BIT 解决。

```cpp
namespace F
{
    const uint Lim=262144;
    ullt W[Lim<<1|1],Tag[Lim<<1|1];
    ullt find(uint l,uint r,uint u=1,uint n=Lim)
    {
        if(l>=r)return 0;
        if(!l&&r==n)return W[u];
        if(l<(n>>1))
            if(r<=(n>>1))return find(l,r,u<<1,n>>1)+Tag[u];
            else return std::max(find(l,n>>1,u<<1,n>>1),find(0,r-(n>>1),u<<1|1,n>>1))+Tag[u];
        else return find(l-(n>>1),r-(n>>1),u<<1|1,n>>1)+Tag[u];
    }
    voi add(uint l,uint r,ullt w,uint u=1,uint n=Lim)
    {
        if(l>=r)return;
        if(!l&&r==n){Tag[u]+=w,W[u]+=w;return;}
        if(l<(n>>1))
            if(r<=(n>>1))add(l,r,w,u<<1,n>>1);
            else add(l,n>>1,w,u<<1,n>>1),add(0,r-(n>>1),w,u<<1|1,n>>1);
        else add(l-(n>>1),r-(n>>1),w,u<<1|1,n>>1);
        W[u]=std::max(W[u<<1],W[u<<1|1])+Tag[u];
    }
};
namespace G
{
    const uint Lim=262144;
    ullt W[Lim<<1|1],Tag[Lim<<1|1];
    ullt find(uint l,uint r,uint u=1,uint n=Lim)
    {
        if(l>=r)return 0;
        if(!l&&r==n)return W[u];
        if(l<(n>>1))
            if(r<=(n>>1))return find(l,r,u<<1,n>>1)+Tag[u];
            else return std::max(find(l,n>>1,u<<1,n>>1),find(0,r-(n>>1),u<<1|1,n>>1))+Tag[u];
        else return find(l-(n>>1),r-(n>>1),u<<1|1,n>>1)+Tag[u];
    }
    voi add(uint l,uint r,ullt w,uint u=1,uint n=Lim)
    {
        if(l>=r)return;
        if(!l&&r==n){Tag[u]+=w,W[u]+=w;return;}
        if(l<(n>>1))
            if(r<=(n>>1))add(l,r,w,u<<1,n>>1);
            else add(l,n>>1,w,u<<1,n>>1),add(0,r-(n>>1),w,u<<1|1,n>>1);
        else add(l-(n>>1),r-(n>>1),w,u<<1|1,n>>1);
        W[u]=std::max(W[u<<1],W[u<<1|1])+Tag[u];
    }
    voi chg(uint p,ullt w,uint u=1,uint n=Lim)
    {
        _max(W[u],w);if(w<Tag[u]||n==1)return;
        w-=Tag[u];
        if(p<(n>>1))chg(p,w,u<<1,n>>1);else chg(p-(n>>1),w,u<<1|1,n>>1);
    }
}
std::vector<uint>A[200005];
std::vector<std::pair<uint,uint> >B[200005];
uint Pre[200005],Nxt[200005];bol S[200005];
uint pre(uint p)
{
    while(p!=Pre[p])p=Pre[p]=Pre[Pre[p]];
    return p;
}
uint nxt(uint p)
{
    while(p!=Nxt[p])p=Nxt[p]=Nxt[Nxt[p]];
    return p;
}
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    freopen("QAQ.out","w",stdout);
#endif
    uint n,m;ullt ans=0;
    scanf("%u",&n);for(uint i=0,v;i<n;i++)scanf("%u",&v),A[v-1].push_back(i),Pre[i]=Nxt[i]=i;
    scanf("%u",&m);while(m--){uint x,y,c;scanf("%u%u%u",&x,&y,&c),B[y-1].push_back({x-1,c}),ans+=c;}
    for(uint i=0;i<n;i++)
    {
        for(auto p:B[i])G::chg(p.first,p.second+F::find(p.first,p.first+1));
        for(auto p:A[i])
        {
            S[p]=true;
            if(p&&S[p-1])Pre[p]=p-1,Nxt[p-1]=p;
            if(p<n-1&&S[p+1])Nxt[p]=p+1,Pre[p+1]=p;
            uint l=pre(p),r=nxt(p);
            ullt w1=G::find(l,p),w2=G::find(p+1,r+1);
            F::add(l,p+1,w2),F::add(p,r+1,w1),G::add(l,p+1,w2),G::add(p,r+1,w1);
        }
    }
    ans-=G::find(0,n);
    printf("%llu\n",ans);
    return 0;
}
```


---

