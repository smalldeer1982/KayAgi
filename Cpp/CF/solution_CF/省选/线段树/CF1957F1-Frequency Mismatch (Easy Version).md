# Frequency Mismatch (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the two versions of this problem is the constraint on $ k $ . You can make hacks only if all versions of the problem are solved.

You are given an undirected tree of $ n $ nodes. Each node $ v $ has a value $ a_v $ written on it. You have to answer queries related to the tree.

You are given $ q $ queries. In each query, you are given $ 5 $ integers, $ u_1, v_1, u_2, v_2, k $ . Denote the count of nodes with value $ c $ on path $ u_1 \rightarrow v_1 $ with $ x_c $ , and the count of nodes with value $ c $ on path $ u_2 \rightarrow v_2 $ with $ y_c $ . If there are $ z $ such values of $ c $ such that $ x_c \neq y_c $ , output any $ \min(z, k) $ such values in any order.

## 说明/提示

For query $ 1 $ , the first path is $ 1 \rightarrow 2 \rightarrow 4 $ , coming across the multiset of values $ \{5, 2, 4\} $ . On the second path $ 4 \rightarrow 2 \rightarrow 5 $ , we have the multiset $ \{4, 2, 3\} $ . Two numbers — $ 3 $ and $ 5 $ occur a different number of times, hence we print one of them.

In query $ 2 $ , there is no difference between the paths, hence we output $ 0 $ .

In query $ 3 $ , the first path is just the node $ 5 $ , resulting in the multiset $ \{3\} $ , and the second path $ 4 \rightarrow 2 \rightarrow 1 \rightarrow 3 $ gives $ \{4, 2, 5, 3\} $ . The numbers $ 5 $ , $ 2 $ and $ 4 $ occur a different number of times.

## 样例 #1

### 输入

```
5
5 2 3 4 3
1 2
1 3
2 4
2 5
3
1 4 4 5 1
2 3 2 3 1
5 5 4 3 1```

### 输出

```
1 5
0
1 2```

# 题解

## 作者：WRuperD (赞：1)

场上不会做？思维僵硬的老年选手是这样的。

首先肯定是可以搞一个权值线段树，对于每一个颜色赋一个随机权值，每次查询直接二分查找哪些位置不一样做下去。注意到 $k$ 很小，所以我们只需要找到 $k$ 个不一样的位置就直接结束二分就可以保证复杂度。

问题是如何每次快速地领出这样的一颗权值线段树（赛时卡在这里了）。往树剖想肯定没有前途。注意到这个信息满足交换律，所以其实可以直接可持久化线段树，维护每个节点到根节点的权值线段树。查询的时候就直接差分一下就好了。


```cpp
// Problem: Frequency Mismatch (Hard Version)
// URL: https://www.luogu.com.cn/problem/CF1957F2
// Writer: WRuperD
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")

const int MAX = 2e5 + 10;
std::mt19937 Rnd(std::chrono::steady_clock::now().time_since_epoch().count());

int a[MAX];
int lsh[MAX];
int m;
int hsh[MAX];

int s[MAX * 30], ls[MAX * 30], rs[MAX * 30];

int psz;

vector <int> g[MAX];

int build(int l, int r){
	int x = ++psz;
	if(l == r)	return x;
	int mid = (l + r) >> 1;
	ls[x] = build(l, mid), rs[x] = build(mid + 1, r);
	return x;
}

int add(int l, int r, int pos, int val, int prex){
	int x = ++psz;
	s[x] = s[prex] + val, ls[x] = ls[prex], rs[x] = rs[prex];
	if(l == r)	return x;
	int mid = (l + r) >> 1; 
	if(pos <= mid)	ls[x] = add(l, mid, pos, val, ls[prex]);
	else rs[x] = add(mid + 1, r, pos, val, rs[prex]);
	return x;
}	

vector <int> query(int l, int r, int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8, int ned){
	// write(l), put(), write(r), endl;
	vector <int> re;
	re.clear();
	if(s[x1] + s[x2] - s[x3] - s[x4] == s[x5] + s[x6] - s[x7] - s[x8])	return re;
	if(l == r){
		re.pb(l);
		return re;
	}	
	int mid = (l + r) >> 1;
	re = query(l, mid, ls[x1], ls[x2], ls[x3], ls[x4], ls[x5], ls[x6], ls[x7], ls[x8], ned);
	if(re.size() < ned){
		vector <int> re2 = query(mid + 1, r, rs[x1], rs[x2], rs[x3], rs[x4], rs[x5], rs[x6], rs[x7], rs[x8], ned - re.size());
		for(int u : re2)	re.pb(u);
		return re;
	}
	return re;
}

int ver[MAX];

int Fa[MAX], top[MAX], siz[MAX], son[MAX], dep[MAX];

void dfs(int u, int fa){
	Fa[u] = fa;
	siz[u] = 1;
	dep[u] = dep[fa] + 1;
	ver[u] = add(1, m, a[u], hsh[a[u]], ver[fa]);
	for(int v : g[u]){
		if(v == fa)	continue;
		dfs(v, u);
		siz[u] += siz[v];
		if(siz[son[u]] < siz[v])	son[u] = v;
	}
}

void dfs2(int u, int topu){
	top[u] = topu;
	if(son[u])	dfs2(son[u], topu);
	for(int v : g[u]){
		if(v == Fa[u] or v == son[u])	continue;
		dfs2(v, v);
	}
}

inline int lca(int u, int v){
	while(top[u] != top[v]){
		if(dep[top[u]] < dep[top[v]])	swap(u, v);
		u = Fa[top[u]];
	}
	if(dep[u] < dep[v])	return u;
	return v;
}

void solve(){
	int n = read();
	for(int i = 1; i <= n; i++){
		a[i] = read();
		lsh[i] = a[i];
	}
	sort(lsh + 1, lsh + n + 1);
	m = unique(lsh + 1, lsh + n + 1) - lsh - 1;
	ver[0] = build(1, m);
	for(int i = 1; i <= m; i++)	hsh[i] = Rnd();
	for(int i = 1; i <= n; i++){
		a[i] = lower_bound(lsh + 1, lsh + m + 1, a[i]) - lsh;
	}
	for(int i = 1; i < n; i++){
		int u = read(), v = read();
		g[u].pb(v), g[v].pb(u);
	} 
	dfs(1, 0);
	dfs2(1, 1);
	int q = read();
	while(q--){
		int u = read(), v = read(), u2 = read(), v2 = read(), k = read();
		vector <int> ans = query(1, m, ver[u], ver[v], ver[lca(u, v)], ver[Fa[lca(u, v)]], ver[u2], ver[v2], ver[lca(u2, v2)], ver[Fa[lca(u2, v2)]], k);
		if(ans.size() == 0){
			puts("0");
		}else{
			write(ans.size()), put();
			for(int u : ans)	write(lsh[u]), put();
			endl;
		}
	}
}

signed main(){
	int t = 1;
	while(t--)	solve();
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

首先考虑对于两个集合怎么找出 $k$ 个出现次数不同的数，考虑以颜色为下标建立线段树，并对每种颜色附上权值做哈希，在线段树上不断二分，直到二分出 $k$ 个值不同的位置，这么做显然是 $O(k \log n)$ 的。

考虑如何快速刻画链上的出现次数信息，考虑用主席树维护每个点到根的路径上所有颜色的出现次数信息，查询时链上差分一下即可，时间复杂度 $O((n + q \times k) \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e5+114;
const int inf = 1e5;
const int mod[2]={998244353,1000000007};
struct Hash{
	int val[2];
	Hash(int v0=0,int v1=0){
		val[0]=v0,val[1]=v1;
	}
	Hash operator+(const Hash &x){
		return Hash((val[0]+x.val[0])%mod[0],(val[1]+x.val[1])%mod[1]);
	}	
	Hash operator-(const Hash &x){
		return Hash((val[0]+mod[0]-x.val[0])%mod[0],(val[1]+mod[1]-x.val[1])%mod[1]);
	}
	bool operator==(const Hash &x){
		return (val[0]==x.val[0])&(val[1]==x.val[1]);
	}
}e;
Hash wei[maxn];
Hash tr[maxn*50];
int ls[maxn*50],rs[maxn*50];
int a[maxn],tot;
int root[maxn];
void pushup(int cur){
	tr[cur]=tr[ls[cur]]+tr[rs[cur]];
}
void ins(int lst,int cur,int lt,int rt,int pos){
	if(lt==rt){
		tr[cur]=tr[lst]+wei[lt];
		return ;
	}
	int mid=(lt+rt)>>1;
	if(pos<=mid){
		rs[cur]=rs[lst];
		ls[cur]=++tot;
		ins(ls[lst],ls[cur],lt,mid,pos);
		pushup(cur);
	}else{
		ls[cur]=ls[lst];
		rs[cur]=++tot;
		ins(rs[lst],rs[cur],mid+1,rt,pos);
		pushup(cur);
	}
}
vector<int> E[maxn];
int son[maxn],sz[maxn],top[maxn],dep[maxn],father[maxn];
void dfs1(int u,int fa){
	root[u]=++tot;
	ins(root[fa],root[u],1,inf,a[u]);
	dep[u]=dep[fa]+1;
	father[u]=fa;
	sz[u]=1;
	for(int v:E[u]){
		if(v!=fa){
			dfs1(v,u);
			sz[u]+=sz[v];
			if(sz[v]>sz[son[u]]) son[u]=v;
		}
	}
}
void dfs2(int u,int fa,int tp){
	top[u]=tp;
	if(son[u]!=0) dfs2(son[u],u,tp);
	for(int v:E[u]){
		if(v!=fa&&v!=son[u]){
			dfs2(v,u,v);
		}
	}	
}
int LCA(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=father[top[u]];
	}
	if(dep[u]<dep[v]) swap(u,v);
	return v;
}
int n,q,k;
Hash val(int u,int l,int r){
	return (a[u]>=l&&a[u]<=r)?wei[a[u]]:e; 
}
int now;
vector<int> ans;
void query(int u1,int v1,int lca1,int u2,int v2,int lca2,int p1,int p2,int lt,int rt){
	if(lt==rt){
		ans.push_back(lt);
		now++;
		return ;
	}
	int mid=(lt+rt)>>1;
	if((tr[ls[u1]]+tr[ls[v1]]-tr[ls[lca1]]-tr[ls[lca1]]+val(p1,lt,mid))==(tr[ls[u2]]+tr[ls[v2]]-tr[ls[lca2]]-tr[ls[lca2]]+val(p2,lt,mid))){
		if((tr[rs[u1]]+tr[rs[v1]]-tr[rs[lca1]]-tr[rs[lca1]]+val(p1,mid+1,rt))==(tr[rs[u2]]+tr[rs[v2]]-tr[rs[lca2]]-tr[rs[lca2]]+val(p2,mid+1,rt))) return ;
		query(rs[u1],rs[v1],rs[lca1],rs[u2],rs[v2],rs[lca2],p1,p2,mid+1,rt);		
	}else{
		query(ls[u1],ls[v1],ls[lca1],ls[u2],ls[v2],ls[lca2],p1,p2,lt,mid);
		if(now==k) return ;
		if((tr[rs[u1]]+tr[rs[v1]]-tr[rs[lca1]]-tr[rs[lca1]]+val(p1,mid+1,rt))==(tr[rs[u2]]+tr[rs[v2]]-tr[rs[lca2]]-tr[rs[lca2]]+val(p2,mid+1,rt))) return ; 
		query(rs[u1],rs[v1],rs[lca1],rs[u2],rs[v2],rs[lca2],p1,p2,mid+1,rt);
	}
}
mt19937 rd(time(0));
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=inf;i++) wei[i]=Hash(rd()%mod[0],rd()%mod[1]);
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		E[u].push_back(v),E[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	cin>>q;
	while(q--){
		ans.clear();
		now=0;
		int u1,v1,u2,v2;
		cin>>u1>>v1>>u2>>v2>>k;
		int lca1=LCA(u1,v1),lca2=LCA(u2,v2);
		query(root[u1],root[v1],root[lca1],root[u2],root[v2],root[lca2],lca1,lca2,1,inf);
		cout<<ans.size()<<' ';
		for(int x:ans) cout<<x<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：strcmp (赞：0)

不妨先去想它的弱化版（CF1957F1，满足 $k = 1$）怎么做。

首先对于这种判断出现次数相同的题，肯定想到去考虑 hash。

想一下，我们怎么判断两个路径是否出现颜色都完全相同。

一看就是哈希的形式，我们对每个颜色随机一个权值出来，然后哈希值取它们的和之类的就好。（需要满足可减性）

树上主席树对于颜色维护 $1 \to u$ 的线段树，然后随便减减就能得到路径对应的线段树。

得到了两棵线段树，每次我们递归到一个区间内就可以 $\Theta(1)$ 的时间判断两个线段树区间是否完全相同。然后递归找最小的不同出现次数颜色即可。

然后你发现就算是强化版也有 $k \le 10$，我们每次不止递归一个区间就能顺带做完了。时间复杂度 $\Theta(nk\log n)$，可以通过。

随机和哈希，感觉应该是卡不掉的。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define pb push_back
#define lb lower_bound
using namespace std;
using ld = long double;
typedef unsigned long long int ll;
using pii = pair<int, int>;
constexpr int maxn = 2e5 + 10, mx = 1e5, B = 217, mod = 1e9 + 7;
const ll inf = 1145141919810520L;
mt19937_64 rd(114514); 
struct edge { int to, nxt; } nd[maxn << 1]; int h[maxn], cnt = 0, a[maxn]; ll w[maxn];
inline void add(int u, int v) { nd[cnt].nxt = h[u], nd[cnt].to = v, h[u] = cnt++; }
struct Node { int l, r; ll s; } t[maxn * 22];
#define ls(x) (t[x].l)
#define rs(x) (t[x].r)
#define s(x) (t[x].s)
#define mid (l + r >> 1)
int rt[maxn], tot = 0, k, fa[maxn][20], d[maxn];
inline void up(int x) { s(x) = s(ls(x)) + s(rs(x)); }
void mdf(int l, int r, int u, int p, int& x) {
	x = ++tot; t[x] = t[p];
	if (l == r) return s(x) += w[l], void();
	u <= mid ? mdf(l, mid, u, ls(p), ls(x)) : mdf(mid + 1, r, u, rs(p), rs(x)); up(x);
} 
void dfs(int u, int f) {
	fa[u][0] = f; d[u] = d[f] + 1;
	for (int i = 1; i < 20; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	mdf(1, mx, a[u], rt[f], rt[u]);
	for (int i = h[u]; ~i; i = nd[i].nxt) {
		int v = nd[i].to;
		if (v != f) dfs(v, u);
	}
}
inline int lca(int u, int v) {
	if (d[u] < d[v]) swap(u, v);
	for (int i = 0; i <= 19; i++) if (d[u] - d[v] >> i & 1) u = fa[u][i];
	if (u == v) return u;
	for (int i = 19; i >= 0; i--) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
vector<int> ans;
void qry(int l, int r, int u0, int v0, int l0, int lf0, int u1, int v1, int l1, int lf1) {
	if (ans.size() == k) return;
	if (s(u0) + s(v0) - s(l0) - s(lf0) == s(u1) + s(v1) - s(l1) - s(lf1)) return;
	if (l == r) return ans.pb(l);
	qry(l, mid, ls(u0), ls(v0), ls(l0), ls(lf0), ls(u1), ls(v1), ls(l1), ls(lf1));
	qry(mid + 1, r, rs(u0), rs(v0), rs(l0), rs(lf0), rs(u1), rs(v1), rs(l1), rs(lf1));
}
int n, q;
int main() {
	memset(h, -1, sizeof(h));
	for (int i = 1; i <= mx; i++) w[i] = rd();
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	dfs(1, 0); scanf("%d", &q);
	while (q--) {
		int u0, v0, u1, v1;
		scanf("%d%d%d%d%d", &u0, &v0, &u1, &v1, &k);
		int l0 = lca(u0, v0), l1 = lca(u1, v1); ans.clear();
		qry(1, mx, rt[u0], rt[v0], rt[l0], rt[fa[l0][0]], rt[u1], rt[v1], rt[l1], rt[fa[l1][0]]);
		printf("%d ", (int)ans.size());
		for (auto x : ans) printf("%d ", x); puts("");
	}
	return 0;
}
```

---

## 作者：xuyiyang (赞：0)

### Solution
发现 $k$ 很小，猜测询问是从路径上找 $k$ 个就返回的题。对于颜色次数，可以考虑用可持久化权值线段树维护。具体的，维护根到每个节点 $id$ 的线段树 $tr_{id}$，对于每次询问，在权值线段树上二分，若两路径的颜色集合完全相同，就返回。否则若左边不相同则走左边。右边不相同就走右边。找到 $k$ 个就返回即可。对于颜色集合，考虑对每个颜色随机赋权，令 $p = lca(u,v)$，用 $tr_u+tr_v-tr_p-tr_{fa_p}$ 来判断集合是否相等。时间复杂度 $\mathcal O(nk \log n)$。注意赋权用 `mt19937`。
### Code 
```cpp
const int N = 1e5 + 10;
typedef long long LL;

mt19937 Rand(time(0));
struct Node {
	int l, r;
	LL v;
} tr[N * 18 + N * 4];
int root[N];
int n, q, idx, a[N], fa[N];
vector<int> e[N];
LL w[N];
vector<int> id;
int mi[19][N], dfn[N], dn;

int build(int l, int r) {
	int p = ++ idx;
	if (l == r) return p;
	int mid = l + r >> 1;
	tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
	return p;
}
int ins(int p, int l, int r, int x) {
	int q = ++ idx; tr[q] = tr[p];
	if (l == r) { tr[q].v += w[x]; return q; }
	int mid = l + r >> 1;
	if (x <= mid) tr[q].l = ins(tr[p].l, l, mid, x);
	else tr[q].r = ins(tr[p].r, mid + 1, r, x);
	tr[q].v = tr[tr[q].l].v + tr[tr[q].r].v; return q;
}
void dfs(int u) {
	root[u] = ins(root[fa[u]], 1, 1e5, a[u]);
	mi[0][dfn[u] = ++ dn] = fa[u];
	for (int v : e[u]) if (v != fa[u]) fa[v] = u, dfs(v);
}
int get(int x, int y) { return dfn[x] < dfn[y] ? x : y; }
int lca(int u, int v) {
	if (u == v) return u;
	if ((u = dfn[u]) > (v = dfn[v])) swap(u, v);
	int k = log(v - (u ++ )) / log(2);
	return get(mi[k][u], mi[k][v - (1 << k) + 1]);
}
struct nd { int a, b, c, d;	LL gv() { return tr[a].v + tr[b].v - tr[c].v - tr[d].v; } };
#define Lx nd{tr[x.a].l, tr[x.b].l, tr[x.c].l, tr[x.d].l}
#define Rx nd{tr[x.a].r, tr[x.b].r, tr[x.c].r, tr[x.d].r}
#define Ly nd{tr[y.a].l, tr[y.b].l, tr[y.c].l, tr[y.d].l}
#define Ry nd{tr[y.a].r, tr[y.b].r, tr[y.c].r, tr[y.d].r}
void find(nd x, nd y, int l, int r, int K) {
	if (id.size() == K || x.gv() == y.gv()) return ;
	if (l == r) return id.push_back(l), void();
	int mid = l + r >> 1;
	if (Lx.gv() != Ly.gv()) find(Lx, Ly, l, mid, K);
	if (Rx.gv() != Ry.gv()) find(Rx, Ry, mid + 1, r, K);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
	for (int i = 1; i <= 1e5; i ++ ) w[i] = Rand();
	for (int i = 1, u, v; i < n; i ++ ) {
		scanf("%d%d", &u, &v);
		e[u].push_back(v), e[v].push_back(u);
	} root[0] = build(1, 1e5); dfs(1);
	int t = log(n) / log(2) + 1;
	for (int i = 1; i < t; i ++ ) for (int j = 1; j + (1 << i) - 1 <= n; j ++ ) 
		mi[i][j] = get(mi[i - 1][j], mi[i - 1][j + (1 << (i - 1))]);
	scanf("%d", &q);
	while (q -- ) {
		int a, b, c, d, K; scanf("%d%d%d%d%d", &a, &b, &c, &d, &K); id.clear();
		nd x = {root[a], root[b], root[lca(a, b)], root[fa[lca(a, b)]]};
		nd y = {root[c], root[d], root[lca(c, d)], root[fa[lca(c, d)]]};
		find(x, y, 1, 1e5, K);
		printf("%d ", id.size()); for (int v : id) printf("%d ", v);
		puts("");
	} return 0;
}
```

---

