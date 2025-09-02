# Fracture Ray

## 题目背景

破碎的镜面里倒映着破碎的射线；

破碎的文字中隐藏着破碎的——

## 题目描述

有一个 `long long` 类型的数组 `a[]`。

在给出所有操作之前，给定上界参数 $v$。

共有 $q$ 次操作。每次操作为以下两个函数之一：

```
void modify(int u,int p)
{
    for (int i=u;i<=v;i+=count(i))
        a[i]+=p;
}
long long query(long long u)
{
    long long ret=0;
    for (int i=u;i<=v;i+=count(i))
        ret+=a[i];
    return ret;
}
```

上述程序为 C++ 代码，其中 `count(i)` 表示 $i$ 二进制下 $1$ 的个数，例如 `count(0)` 的返回值为 $0$，而 `count(10001279)` 的返回值为 $15$。

上述程序中出现的变量 `v` 即上界参数 $v$。

你需要执行上述操作，并在每次执行 `query()` 函数后，输出函数的返回值。

## 说明/提示

子任务 1（$8$ 分）：$1\leq q\leq 10^3$，$1\leq v\leq 10^4$。

子任务 2（$23$ 分）：$1\leq v\leq 10^5$。

子任务 3（$16$ 分）：$1\leq q\leq 50$。

子任务 4（$28$ 分）：$1\leq q\leq 1000$。

子任务 5（$25$ 分）：无特殊限制。

对于全部数据，$1\leq q\leq 2\times 10^5$，$1\leq u\leq v< 2^{30}$，$-10^4\leq p\leq 10^4$。

请选手注意代码实现时常数因子带来的程序效率上的影响。

已加入 hack 数据。

## 样例 #1

### 输入

```
7 19
1 3 -8
1 4 8
1 13 -1
2 2
1 1 -10
1 1 8
2 12
```

### 输出

```
-10
-10
```

## 样例 #2

### 输入

```
29 1066163924
2 680224223
1 440869582 -1203
2 993311885
1 729027357 9874
2 665374856
1 192704973 -9712
1 681750770 -1099
2 239837676
1 938998353 -109
2 174153423
1 781133679 7360
2 522379034
2 125773599
1 483114333 -376
2 723115805
2 699246389
1 527125403 9279
1 930492461 -9753
1 14775627 -3676
1 152692805 5045
1 945645197 2710
2 298593273
1 888744817 2514
1 651751441 4559
2 963653895
1 986621281 -8296
2 10216021
2 848072343
2 482342087
```

### 输出

```
0
-5264389353
181209893739
-398925734374
-431628986929
-73026998100
-298228449649
73714612345
53926122085
97102847037
96145153438
110646771673
199641765482
314932271763
```

# 题解

## 作者：mrsrz (赞：17)

[可能更好的体验](https://mrsrz.github.io/2020/06/18/lg5891/)

考虑对每个 $u$，暴力往上跳，这样跳过的**不同**节点的总数不会非常多，平均下来大概在 $7\times 10^7\sim 8\times 10^7$ 这样子。目前似乎无法将其卡掉。

然而实际上访问的只有 $q$ 个不同的节点，所以这个实际上的森林会有非常多的地方是一条单链。为了方便，可以将森林加一个根节点转为一棵树。

我们考虑求出这棵树的虚树，它有 $O(q)$ 个节点。然后求出 $v_x$ 表示节点 $x$ 到其虚树上父亲**在原树**的路径中的节点个数（不包括父亲）。那么对 $x$ 及其子树中到根路径加 $p$ 的操作，我们就可以把 $x$ 到其虚树上的父亲的这段直接在虚树节点 $x$ 上考虑，即直接在 $x$ 上加 $p\cdot v_x$。查询的时候也只需查询这个点在虚树上到根路径上的点的点权和即可。

由于 $v$ 数组是唯一确定的，所以链加链和可以直接使用树链剖分+线段树维护，或者使用 LCT 等数据结构即可维护。

然后关键就是建出这棵虚树。我们用一个 $2^{30}$ 的 bitset 记录每个点是否被访问过，然后对询问离线，对每个 $u$ 都暴力往上跳，找到第一个被访问过的点（或者超过 $V$），并将沿途上的点标记为访问过。那么每个 $u$ 开始和结尾的点就是可能出现在虚树中的点。求 $v_x$ 和虚树上的连边，可以通过将能出现在虚树上的点排序后，从大到小再暴力往上跳一遍，遇到访问过的节点停止。

根据上面“不同的节点总数不会非常多”的结论，上面的做法是不会超时的。

由于 $2^{30}$ 的 bitset 会 CMLE，所以需要手写一个简单的 bitset。

数据结构维护部分的复杂度为 $O(q\log^2 q)$ 或 $O(q\log q)$。空间复杂度 $O(q+V)$。

## Code：
```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;
typedef long long LL;
#define popcnt __builtin_popcount
const int N=8e5+6;
unsigned b[1<<25|1];
map<int,int>id;
int m,V,tot,head[N],fa[N],val[N],rt,sz[N],son[N],top[N],dep[N],dfn[N],idx,cnt,vval[N];
int rsc[N<<2];
LL tag[N<<2],d[N<<2];
struct edge{
	int to,nxt;
}e[N];
struct que{
	int op,u,p;
}q[N];
vector<int>vec;
inline bool test(const int&x){return b[x>>5]>>(x&31)&1;}
void dfs(int now){
	sz[now]=1;
	for(int i=head[now];i;i=e[i].nxt){
		dep[e[i].to]=dep[now]+1,dfs(e[i].to);
		sz[now]+=sz[e[i].to];
		if(!son[now]||sz[son[now]]<sz[e[i].to])son[now]=e[i].to;
	}
}
void dfs2(int now){
	dfn[now]=++idx;
	if(son[now])top[son[now]]=top[now],dfs2(son[now]);
	for(int i=head[now];i;i=e[i].nxt)if(e[i].to!=son[now])dfs2(top[e[i].to]=e[i].to);
}
void build(int l,int r,int o){
	if(l==r)rsc[o]=vval[l];else{
		const int mid=l+r>>1;
		build(l,mid,o<<1),build(mid+1,r,o<<1|1);
		rsc[o]=rsc[o<<1]+rsc[o<<1|1];
	}
}
inline void pushdown(int o){
	LL&x=tag[o];
	tag[o<<1]+=x,tag[o<<1|1]+=x;
	d[o<<1]+=x*rsc[o<<1],d[o<<1|1]+=x*rsc[o<<1|1],x=0;
}
void add(int l,int r,int o,const int&L,const int&R,const int&x){
	if(L<=l&&r<=R){
		tag[o]+=x;
		d[o]+=(LL)rsc[o]*x;
	}else{
		pushdown(o);
		const int mid=l+r>>1;
		if(L<=mid)add(l,mid,o<<1,L,R,x);
		if(mid<R)add(mid+1,r,o<<1|1,L,R,x);
		d[o]=d[o<<1]+d[o<<1|1];
	}
}
LL query(int l,int r,int o,const int&L,const int&R){
	if(L<=l&&r<=R)return d[o];
	pushdown(o);
	const int mid=l+r>>1;
	LL res=0;
	if(L<=mid)res=query(l,mid,o<<1,L,R);
	if(mid<R)res+=query(mid+1,r,o<<1|1,L,R);
	return res;
}
void Add(int x,int v){
	while(top[x]!=rt){
		add(1,idx,1,dfn[top[x]],dfn[x],v);
		x=fa[top[x]];
	}
	add(1,idx,1,1,dfn[x],v);
}
LL ask(int x){
	LL res=0;
	while(top[x]!=rt){
		res+=query(1,idx,1,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	res+=query(1,idx,1,1,dfn[x]);
	return res;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>m>>V;
	for(int i=1;i<=m;++i){
		cin>>q[i].op>>q[i].u;
		if(q[i].op==1)cin>>q[i].p;
		int x=q[i].u;
		vec.push_back(x);
		for(;x<=V&&!test(x);x+=popcnt(x))b[x>>5]|=1u<<(x&31);
		if(x<=V)vec.push_back(x);
	}
	sort(vec.begin(),vec.end());vec.erase(unique(vec.begin(),vec.end()),vec.end());
	memset(b,0,sizeof b);
	for(int i=(int)vec.size()-1;~i;--i){
		int x=vec[i];
		if(!id.count(x))id[x]=++tot;
		int pid=id[x];
		int&ct=val[pid];
		if(test(x))continue;
		ct=0;
		for(;x<=V&&!test(x);x+=popcnt(x))b[x>>5]|=1u<<(x&31),++ct;
		if(x>V)x=V+1;
		if(!id.count(x))id[x]=++tot;
		int nid=id[x];
		fa[pid]=nid;
		e[++cnt]=(edge){pid,head[nid]},head[nid]=cnt;
	}
	rt=id[V+1];
	val[rt]=0;
	top[rt]=rt;
	dfs(rt),dfs2(rt);
	for(int i=1;i<=idx;++i)vval[dfn[i]]=val[i];
	build(1,idx,1);
	for(int i=1;i<=m;++i)
	if(q[i].op==1)Add(id[q[i].u],q[i].p);
	else cout<<ask(id[q[i].u])<<'\n';
	return 0;
}
```

---

## 作者：1saunoya (赞：2)

~~暂时的最优解，我 1.36s，rk2 2.88s~~

首先考虑到这个玩意肯定是一棵树，大胆猜测这颗树的很多节点都是被反复利用的，比如说 $5 = 3+popcount(3) = 4 + popcount(4)$。

这样的话这上面的点不会太多，然后可以用 bitset 记一下哪些点出现了，哪些点没有。然后我们定义 
$[V+1, \infty)$
作为根，显然这个区间可以用一个点来表示，那么令这个点为根的话，每次操作其实就是 $root \to x$ 这个链上面整体加上 $v$，查询的时候是查询 $root \to x$。

保留有用的点的个数其实不会超过 $N \times 4$

代码有点难写。不过比较板子， LCT 和 树链剖分 都能过吧。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 8e5 + 58;
int nodes[MAXN], val[MAXN];

struct SegmentTree {
	SegmentTree() {}
	
	int N;
	vector <long long> tag, s;
	vector <int> cnt;
	void resize(int _N) {
		N = _N + 1;
		tag.resize(N << 2);
		cnt.resize(N << 2);
		s.resize(N << 2);
	}
	
	void pushup(int p) {
		s[p] = s[p << 1] + s[p << 1 | 1];
	}
	
	void build(int l, int r, int p) {
		if (l == r) {
			cnt[p] = val[l];
			return;
		}
		int mid = l + r >> 1;
		build(l, mid, p << 1);
		build(mid + 1, r, p << 1 | 1);
		cnt[p] = cnt[p << 1] + cnt[p << 1 | 1];
	}
	
	void cover(int p, int v) { tag[p] += v; s[p] += 1ll * v * cnt[p]; }
	
	void pushdown(int p) {
		if (tag[p]) {
			cover(p << 1, tag[p]);
			cover(p << 1 | 1, tag[p]);
			tag[p] = 0;
		}
	}
	
	void modify(int ql, int qr, int l, int r, int p, int v) {
		if (ql <= l && r <= qr) {
			return cover(p, v);
		}
		pushdown(p);
		int mid = l + r >> 1;
		if (ql <= mid) {
			modify(ql, qr, l, mid, p << 1, v);
		}
		if (qr > mid) {
			modify(ql, qr, mid + 1, r, p << 1 | 1, v);
		}
		pushup(p);
	}
	
	long long query(int ql, int qr, int l, int r, int p) {
		if (ql <= l && r <= qr) {
			return s[p];
		}
		pushdown(p);
		int mid = l + r >> 1;
		long long ans = 0;
		if (ql <= mid) {
			ans += query(ql, qr, l, mid, p << 1);
		}
		if (qr > mid) {
			ans += query(ql, qr, mid + 1, r, p << 1 | 1);
		}
		return ans;
	}
} smt;

struct Bitset {
unsigned used[1 << 25 | 3];
void clear() { memset(used, 0, sizeof(used)); }
void set(int x) { used[x >> 5] |= 1 << (x & 31); }
bool count(int x) { return used[x >> 5] >> (x & 31) & 1; }
} B;
unordered_map <int, int> id;
int q, V;

struct Temp { int op, x, y; } t[MAXN];
vector <int> g[MAXN];
int sz[MAXN], son[MAXN], dep[MAXN], fa[MAXN];
void dfs(int u, int p) {
	sz[u] = 1;
	son[u] = 0;
	dep[u] = dep[p] + 1;
	fa[u] = p;
	for (auto v : g[u]) {
		if (v == p) {
			continue;
		} else {
			dfs(v, u);
			sz[u] += sz[v];
			if (sz[v] > sz[son[u]]) {
				son[u] = v;
			}	
		}
	}
}

int top[MAXN], dfn[MAXN], _Index = 0;
void dfs2(int u, int t) {
	top[u] = t;
	dfn[u] = ++_Index;
	if (son[u]) {
		dfs2(son[u], t);
	}
	for (auto v : g[u]) {
		if (!top[v]) {
			dfs2(v, v);
		}
	}
}

// a path on tree add v
int cnt, root;
void modify(int p, int v) {
	while (top[p] != root) {
		smt.modify(dfn[top[p]], dfn[p], 1, cnt, 1, v);
		p = fa[top[p]];
	}
	if (p) {
		smt.modify(1, dfn[p], 1, cnt, 1, v);
	}
}

long long query(int p) {
	long long ans = 0;
	while (top[p] != root) {
		ans += smt.query(dfn[top[p]], dfn[p], 1, cnt, 1);
		p = fa[top[p]];
	}
	if (p) {
		ans += smt.query(1, dfn[p], 1, cnt, 1);
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> q >> V; ++V;
	
	vector <int> tr; // nodes in tree
	for (int i = 1; i <= q; i++) {
		int op, x, v;
		cin >> op >> x;
		if (op == 1) {
			cin >> v;
		}
		t[i] = {op, x, v};
		tr.emplace_back(x);
		for (; x < V && !B.count(x); x += __builtin_popcount(x)) {
			B.set(x);
		}
		if (x < V) {
			tr.emplace_back(x);
		}
	}
	
	sort(tr.begin(), tr.end());
	tr.resize(unique(tr.begin(), tr.end()) - tr.begin());
	B.clear();
	reverse(tr.begin(), tr.end());
	
	for (auto node : tr) {
		if (!id.count(node)) {
			id[node] = ++cnt;
		}
		int u = node;
		int &cur = nodes[id[u]];
		if (B.count(u)) {
			continue;
		}
		cur = 0;
		for (; u < V && !B.count(u); u += __builtin_popcount(u)) {
			B.set(u);
			++cur;
		}
		int p = min(u, V);
		if (!id.count(p)) {
			id[p] = ++cnt;
		}
		g[id[p]].emplace_back(id[node]);
	}
	
	root = id[V];
	nodes[root] = 0;
	dfs(root, 0);
	dfs2(root, root);
	
	for (int i = 1; i <= cnt; i++) {
		val[dfn[i]] = nodes[i];
	}
	
	smt.resize(cnt);
	smt.build(1, cnt, 1);
	for (int i = 1; i <= q; i++) {
		if (t[i].op == 1) {
			modify(id[t[i].x], t[i].y);
		} else {
			cout << query(id[t[i].x]) << '\n';
		}
	}
	return 0;
}
```

---

## 作者：Arghariza (赞：1)

2D0y a。

结论拍脸。

显然如果 $i\to i+\text{popcount(i)}$ 这样连边的话，连出来是一个森林。

结论就是 $q$ 个 $u$ 到根的路径的点，去重后的个数不超过 $8\times 10^7$。

然后 	`bitset` 维护所有走过的点，建出虚树，点数就变成 $O(q)$ 的了。

然后树剖线段树就能在 $O(q\log^2 q)$ 的时间内解决。

要手写 `bitset`。

```cpp
// Problem: P5891 Fracture Ray
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5891
// Memory Limit: 500 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second
// #define FILE

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Med;

const int N = 5e6 + 500;
const int M = 3.5e7 + 350;

map<int, int> pid;
vector<tu> qr;
vector<int> p, g[N];
int q, m, rt, tot, dfc;
int fa[N], sz[N], dep[N], son[N], id[N], top[N];
ll s[N], vl[N];

struct BIT {
	unsigned int f[M];
	void reset() { memset(f, 0, sizeof(f)); }
	void set(int x) { f[x >> 5] |= (1ll << (x & 31)); }
	int test(int x) { return (f[x >> 5] >> (x & 31)) & 1; }
} B;

struct SEG {
	ll tr[N << 2], lz[N << 2];
	#define ls x << 1
	#define rs x << 1 | 1
	#define mid ((l + r) >> 1)
	void ptg(int l, int r, ll c, int x) { tr[x] += 1ll * (s[r] - s[l - 1]) * c, lz[x] += c; }
	void pdn(int l, int r, int x) {
		if (!lz[x]) return;
		ptg(l, mid, lz[x], ls), ptg(mid + 1, r, lz[x], rs);
		lz[x] = 0;
	}
	void upd(int l, int r, int s, int t, ll c, int x) {
		if (t < s) return;
		if (s <= l && r <= t) return ptg(l, r, c, x);
		pdn(l, r, x);
		if (s <= mid) upd(l, mid, s, t, c, ls);
		if (t > mid) upd(mid + 1, r, s, t, c, rs);
		tr[x] = tr[ls] + tr[rs];
	}
	ll qry(int l, int r, int s, int t, int x) {
		if (t < s) return 0;
		if (s <= l && r <= t) return tr[x];
		pdn(l, r, x); ll res = 0;
		if (s <= mid) res += qry(l, mid, s, t, ls);
		if (t > mid) res += qry(mid + 1, r, s, t, rs);
		return res;
	}
} T;

#define pct(x) __builtin_popcountll(x)
#define gt(x, y) get<y>(x)

int gid(int u) {
	if (!pid[u]) pid[u] = ++tot;
	return pid[u];
}

void dfs1(int u) {
	sz[u] = 1, dep[u] = dep[fa[u]] + 1;
	for (int v : g[u]) {
		dfs1(v), sz[u] += sz[v];
		if (sz[v] > sz[son[u]]) son[u] = v;
	}
}

void dfs2(int u, int pr) {
	top[u] = pr, s[id[u] = ++dfc] = vl[u];
	if (son[u]) dfs2(son[u], pr);
	for (int v : g[u]) {
		if (v == son[u]) continue;
		dfs2(v, v);
	}
}

void upd(int u, int c) {
	while (u) {
		T.upd(1, dfc, id[top[u]], id[u], c, 1);
		u = fa[top[u]];
	}
}

ll qry(int u) {
	ll res = 0;
	while (u) {
		res += T.qry(1, dfc, id[top[u]], id[u], 1);
		u = fa[top[u]];
	}
	return res;
}

void solve() {
	cin >> q >> m;
	for (int i = 1, op, u, w; i <= q; i++) {
		cin >> op >> u;
		if (op == 1) cin >> w, qr.pb(mt(op, u, w));
		else qr.pb(mt(op, u, 0));
		p.pb(u);
		for (; u <= m && !B.test(u); u += pct(u)) B.set(u);
		if (u <= m) p.pb(u);
	}
	p.pb(m + 1);
	sort(p.begin(), p.end());
	p.erase(unique(p.begin(), p.end()), p.end());
	reverse(p.begin(), p.end()), B.reset();
	for (int u : p) {
		int iu = gid(u), ifa;
		if (u == m + 1) continue;
		for (; u <= m && !B.test(u); u += pct(u)) 
			vl[iu]++, B.set(u);
		if (u <= m) ifa = gid(u);
		else ifa = gid(m + 1);
		if (ifa == iu) ifa = gid(m + 1);
		g[ifa].pb(iu), fa[iu] = ifa;
	}
	rt = gid(m + 1);
	for (int i = 1; i <= tot; i++)
		if (i != rt && !fa[i])
			g[rt].pb(i), fa[i] = rt;
	dfs1(rt), dfs2(rt, rt);
	for (int i = 1; i <= dfc; i++) 
		s[i] += s[i - 1];
	for (tu p : qr) {
		if (gt(p, 0) == 1) upd(gid(gt(p, 1)), gt(p, 2));
		else cout << qry(gid(gt(p, 1))) << '\n';
	}
}

bool Mbe;
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Med - &Mbe) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("A.in", "r", stdin);
		freopen("B.out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}

```

---

