# [ICPC 2021 Macao R] Colorful Tree

## 题目描述

你的任务是维护一棵有色树并处理查询。

一开始，树上只有一个编号为 $1$ 的顶点，颜色为 $C$。然后按顺序进行 $q$ 个操作，有两种类型：
- $0$ $x$ $c$ $d$：向树中添加一个颜色为 $c$ 的新顶点，其编号为 $(n+1)$，其中 $n$ 是当前存在的顶点数。同时，添加一条连接顶点 $x$ 和 $(n+1)$ 的长度为 $d$ 的边。
- $1$ $x$ $c$：将顶点 $x$ 的颜色更改为 $c$。

在每次操作之后，你应该找到当前树中颜色 $\textbf{不同}$ 的两个顶点 $u$ 和 $v$（$1 \le u, v \le n$），使得它们之间的距离尽可能大。

两个顶点 $u$ 和 $v$ 之间的距离是树上从 $u$ 到 $v$ 的最短路径的长度。

## 样例 #1

### 输入

```
2
1 1
0 1 1 1
5 1
0 1 1 1
0 1 2 1
0 3 3 1
1 4 1
1 3 1```

### 输出

```
0
0
2
3
2
0```

# 题解

## 作者：lzyqwq (赞：3)

**[CNBLOGS](https://www.cnblogs.com/MnZnOIerLzy/p/17870391.html)**

我永远喜欢数据结构。

**[题目传送门](https://www.luogu.com.cn/problem/P9665)**

> - 给出一棵树，初始只有一个点 $1$，其颜色为 $C$。
>
> - 有 $q$ 次操作，分为两种类型：
>
>     - $0\space x\space c\space d$，记当前树中一共有 $n$ 个点，新增一个 $n+1$，其父亲为 $x$，颜色为 $c$，两点间边权为 $d$。
>
>     - $1\space x\space c$，将点 $x$ 的颜色修改为 $c$。
>
> - 每次操作结束后，找到两个颜色不同的点，使得它们的树上距离最大。
>
> - 多测，$\sum q\le5\times 10^5$。
>
> - $\text{6.00 s / 512.00 MB}$。

本文中，点对 $(u,v)$ 可以满足 $u=v$。记 $Q=\sum q$。

可以先离线把树建出来，树上距离不变，因为两点间的唯一路径不变。

首先有个结论：

> 有两个点集 $S_1,S_2$，其中 $S_1$ 中距离最大的两个点为 $u_1,v_1$，$S_2$ 中两个距离最大的点为 $u_2,v_2$，则 $S_1\bigcup S_2$ 中两个距离最大的点 $x_1,x_2\in\{u_1,u_2,v_1,v_2\}$；在 $S_1,S_2$ 中各选一个点，使得树上距离最大的点 $y_1,y_2\in\{u_1,u_2,v_1,v_2\}$。
>
> 前者就是在后者的基础上考虑选取的两个点在同一个集合内。

因为可以证明调整之后一定不劣。我们考虑使用线段树维护。

首先对于每一种颜色开一棵动态开点线段树，维护区间 $[l,r]$ 树上距离最远的点对。可以通过上述结论合并信息。

其次维护一棵线段树 $T$，区间 $[l,r]$ 内维护两个信息：

- 在 $[l,r]$ **颜色**中的最远点对。

- 在 $[l,r]$ 颜色中**不同色**的最远点对。

第一个信息也可以通过结论维护。第二个信息，考虑这个点对是否在同一半区间内，若是则拿左 / 右儿子的信息合并，否则一定是一个点的颜色 $\le mid$，另一个 $>mid$。这等价于分别在颜色为 $[l,mid]$ 和 $[mid+1,r]$ 的点构成的点集中选一个点，使得树上距离最大。可以根据结论拿左 / 右儿子的第一个信息合并。

对于修改操作，若是加点 $u$，则在其对应颜色的动态开点线段树上，将 $u$ 对应的叶子的信息（点对）修改成 $(u,u)$。

若是改点 $u$ 的颜色，则在其原本颜色的动态开点线段树上，将 $u$ 对应的叶子信息修改为 ⌈空⌋，因为这个区间内不存在符合条件的点对。将新颜色对应的叶子的信息修改为 $(u,u)$。

每次对每种颜色的动态开点线段树维护好后，考虑 $T$ 的信息怎么变。显然只有涉及修改的颜色的叶子（及包含它的区间）发生了变化。

根据两种信息的定义，该叶子的第一种信息应该变为其对应动态开点线段树根上的信息，即这种颜色的最远点对。第二种信息应该变为 ⌈空⌋，因为显然不存在两个不同色的点。

还有一个注意点，求解 $\text{dis}(u,v)$ 的时候我们使用 $dep_u+dep_v-2\cdot dep_{\text{LCA}(u,v)}$。但是这里一次操作合并信息的次数可以到达 $\mathcal{O}(\log Q)$。而这题却出乎意料地卡了 $\mathcal{O}(Q\log^2 Q)$ 的做法。因此我们需要更快速的信息合并方式。

显然需要更高效地求 $\text{LCA}$。记 $f=\text{LCA}(u,v)$。那么记 $ed_x$ 为点 $x$ 子树中 $dfn$ 序最大的那个，显然有 $dfn_f\le dfn_u,dfn_v\le ed_f$。

特判掉 $u$ 或 $v$ 为 $f$ 的情况。我们记 $val_i$ 为 $dfn$ 序为 $i$ 的点的父亲的 $dfn$ 序。那么 $\boldsymbol{dfn_f=\min\limits_{i=dfn_u}^{dfn_v} val_i}$。此处默认 $dfn_u\le dfn_v$。

容易发现对于任意 $x$，$\forall \,i\in(dfn_x,ed_x],val_i\ge dfn_f$。你考虑 $x$ 一定能过通过不少于一条边向下走到这个范围内的点。

根据上面这个结论显然可以得到对于 $i\in[dfn_u,dfn_v],val_i\ge dfn_f$。因为 $[dfn_u,dfn_v]\subseteq (dfn_f,ed_f]$。

其次证明等号可以取到，因为 $u,v$ 一定在 $f$ 的不同子树内，由于 $dfn_u\le dfn_v$，所以 $u$ 所在子树先遍历，设 $v$ 所在子树的根为 $rt$，可以得到 $dfn_u\le  dfn_{rt}\le dfn_v$。

**你发现 $\boldsymbol{val_{dfn_{rt}}=dfn_f}$。**

所以我们可以用 ST 表做这个 RMQ 问题，这样查询是 $\mathcal{O}(1)$ 的。

其次就是这题空信息的处理比较麻烦，可能需要较多特判。一种比较通用的方式是，对于信息我再记录一个变量 $e$，表示其是否为空。定义 $\oplus$ 为合并运算，若两个信息 $a,b$ 满足 $e_b=1$，则 $a\oplus b=a$。

~~事实上好像更麻烦。~~

这样一来，时间、空间复杂度均为 $\mathcal{O}(Q\log Q)$。

**[提交记录](https://www.luogu.com.cn/record/137634076) [代码](https://www.luogu.com.cn/paste/762313vi)**

---

## 作者：Sampson_YW (赞：3)

为啥洛谷评分 J 大于 H 的啊（

有点集直径的经典结论：

两个点集 $S_1,S_2$，设 $S=S_1\cup S_2$，$D_1$ 为 $S_1$ 中距离最远的两个点的集合，$D_2$ 为 $S_2$ 中距离最远的两个点的集合，$D$ 为 $S$ 中最远的两个点的集合。那么 $D\subseteq\left(D_1\cup D_2\right)$。（$|D_1|=|D_2|=|D|=2$）

那么我们对颜色为 $i$ 的点集维护最远的两个点的集合 $D_i$，可以用动态开点线段树或平衡树维护。线段树的下标是原树上的结点编号。

然后还要维护不同颜色点对的最远点对。那么再建一棵线段树，线段树的下标是颜色。维护区间内最远点对的点集，以及维护不同颜色的最远点对的点集。

更新不同颜色的最远点对的时候，答案要么在左区间或右区间内，要么是一个在左区间，一个在右区间。枚举左区间的两个点和右区间的两个点即可。

[code](https://www.luogu.com.cn/paste/4g1kdfso)

---

## 作者：yzq_yzq (赞：1)

典题，应该没有黑。

首先这个题离线过后树就是确定的了，然后考虑怎么做。

首先考虑一个子问题，给定一棵树和一个点集 $S$。要 $S$ 动态加，删点，然后求最大的 $u,v\in S,\text{dist}(u,v)$ 。

经典结论把点集 $S,T$ 合并后变成 $U$ ，$U$ 的直径的两个端点一定是 $S,T$ 的直径的端点中的一个点。

但是这样不好做删点，考虑用一颗线段树去维护，每个节点存 $[l,r]$ 的直径，然后加上欧拉序求 lca 是单 log 的。

然后考虑原问题怎么做，令颜色为 $i$ 的点构成的点集为 $S_i$ 假如我们已经知道 $S_i$ 的直径考虑怎么求答案。

考虑以颜色为下标开一颗线段树，每个节点存 $[l,r]$ 的直径以及 $[l,r]$ 中最远的颜色不同的点对，然后 pushup 的时候只需要把左儿子的直径与右儿子的直径合并入答案，这是单 log 的。

然后只需要维护每个颜色 $S_i$ 的直径，不难发现是上边那个子问题，改成动态开点线段树即可。

总复杂度 $Q\log Q$ 。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define i16 short
#define u16 unsigned i16
#define rep(i, x, y) for(int i = (x); i <= (y); ++i)
#define drep(i, x, y) for(int i = (x); i >= (y); --i)
#define ull unsigned ll
#define pb push_back
#define pii pair<int, int>
#define fi first
#define se second
#define mem(a, b) memset((a), b, sizeof (a))
#define ALL(a) (a).begin(), (a).end()
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
template<typename T> inline void cmin(T &x, T y) { if(x > y) x = y; }
template<typename T> inline void cmax(T &x, T y) { if(x < y) x = y; }
template<typename T> struct LSH {
	vector<T> b; LSH() { b.clear(); } 
	inline void ins(T x) { b.pb(x); }
	inline void build() { sort(ALL(b)), b.erase(unique(ALL(b)), b.end()); }
	inline int q(T x) { return lower_bound(ALL(b), x) - b.begin(); }
	inline T operator [](int x) { return b[x]; }
};
const int N = 500005;
int q, col[N], n = 1, op[N], X[N], Y[N];
vector<pii> G[N];
struct RMQ {
	int st[N << 1][20], lg[N << 1], f[N], m, a[N << 1], dep[N];
	ll dis[N];
	inline void add(int x, int y, int w) {
		G[x].pb({y, w}), G[y].pb({x, w}); }
	inline void dfs(int u, int fa) {
		dep[u] = dep[fa] + 1;
		a[++m] = u, f[u] = m;
		for(auto [v, w] : G[u]) {
			if(v == fa) continue;
			dis[v] = dis[u] + w;
			dfs(v, u), a[++m] = u;
		}
	}
	inline int Max(int x, int y) { return dep[x] < dep[y] ? x : y; }
	inline void build() {
		m = 0, dfs(1, 0);
		rep(i, 2, m) lg[i] = lg[i >> 1] + 1;
		rep(i, 1, m) st[i][0] = a[i];
		rep(j, 1, lg[m]) rep(i, 1, m - (1 << j) + 1)
			st[i][j] = Max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
	}
	inline int lca(int x, int y) {
		x = f[x], y = f[y];
		if(x > y) swap(x, y);
		int s = lg[y - x];
		return Max(st[x][s], st[y - (1 << s) + 1][s]);
	}
	inline ll dist(int x, int y) {
		return dis[x] + dis[y] - (dis[lca(x, y)] << 1);
	}
} D;
struct info {
	int u, v; ll d;
	info() { u = v = d = 0; }
	info(int x) { u = v = x, d = 0; }
	info(int x, int y) { u = x, v = y, d = D.dist(x, y); }
} t[N << 2], v[N << 2], T[N << 5];
inline void print(info x) {
	cout << x.u << " " << x.v << " " << x.d;
}
inline info max(const info &x, const info &y) { return x.d < y.d ? y : x; }
inline info operator +(const info &x, const info &y) {
	if(!x.u) return y; if(!y.u) return x;
	info z = max(x, y);
	z = max(z, info(x.u, y.u));
	z = max(z, info(x.u, y.v));
	z = max(z, info(x.v, y.u));
//	cout << "Merge : ", print(x), cout << ' ', print(y), cout << '\n';
//	print(max(z, info(x.v, y.v))), cout << " %%\n";
	return max(z, info(x.v, y.v));
}
inline info operator ^(const info &x, const info &y) {
	if(!x.u || !y.u) return info();
	info z = info(x.u, y.u);
	z = max(z, info(x.u, y.v));
	z = max(z, info(x.v, y.u));
	return max(z, info(x.v, y.v));
}
int rt[N], ls[N << 5], rs[N << 5], idx = 0;
inline void upd(int &p, int x, bool f, int l = 1, int r = n) {
	if(!p) p = ++idx, ls[p] = rs[p] = 0, T[p] = info();
	if(l == r) return (f ? T[p] = info(x) : T[p] = info()), void();
	int mid = (l + r) >> 1;
	x <= mid ? upd(ls[p], x, f, l, mid) : upd(rs[p], x, f, mid + 1, r);
	T[p] = T[ls[p]] + T[rs[p]];
}
int m = 1;
inline void up(int x) {
	t[x] = t[x << 1] + t[x << 1 | 1];
	v[x] = max(v[x << 1], max(v[x << 1 | 1], t[x << 1] ^ t[x << 1 | 1]));
}
inline void update(int x, bool f) {
	int c = col[x]; 
	upd(rt[c], x, f);
	t[c + m] = T[rt[c]];
//	cout << "T : " << rt[c] << " = ", print(T[rt[c]]), cout << '\n';
	for(c += m; (c >>= 1); ) up(c);
}
int main() {
	fastio; 
	int ts; cin >> ts;
	while(ts--) {
		idx = 0;
		cin >> q >> col[1], n = 1;
		rep(i, 1, q) rt[i] = 0;
		rep(i, 1, q) {
			cin >> op[i] >> X[i] >> Y[i];
			if(!op[i]) {
				++n, col[n] = Y[i];
				int w; cin >> w;
				D.add(X[i], n, w);
			}
		}
		D.build(); m = 1;
//		cout << D.dist(1, 2) << " check distance\n";
		while(m <= q) m <<= 1;
		rep(i, 1, (m << 1)) t[i] = info(), v[i] = info();
		update(1, 1); int id = 1;
		rep(i, 1, q) {
			if(!op[i]) update(++id, 1);
			else update(X[i], 0), col[X[i]] = Y[i], update(X[i], 1);
//				cout << v[1].u << " " << v[1].v << " " << v[1].d << '\n';
			cout << v[1].d << '\n';
		}
		rep(i, 1, n) G[i].clear();
	}
	return 0;
}
```

---

## 作者：Union_Find (赞：1)

好玩的数据结构题，下次再也不折磨自己了。

首先注意到，同一种颜色的点相当于一个点集，而我们知道树上最远点对有一个基本性质。

>如果存在两个点集 $S_1,S_2$，设 $u(S)$ 和 $v(S)$ 表示点集 $S$ 的最远两个点，那么 $u(S_1 \cup S_2),v(S_1 \cup S_2) \in \{u(S_1),v(S_1),u(S_2),v(S_2)\}$

所以我们可以知道如果我们要查询不同颜色的最远点，就可以按颜色将点分成两个集合，分别求 $u(S),v(S)$，然后合并。

这种方法，要不然就是 cdq 分治，要不然就是线段树，这题很明显是线段树。

考虑线段树上的节点 $[l,r]$ 存储 $(u,v)$ 表示颜色区间 $[l,r]$ 中最远的两个点，不要求不同色。然后在存储一个 $dis$ 表示颜色区间 $[l,r]$ 中最远点对的距离，这里要求点对颜色不同。

这样子我们就可以合并了。

```cpp
ST operator + (const ST &x, const ST &y){
	ST ans, a = x, b = y;
	if (!a.u){// 如果有一个儿子没有点，就直接返回另一个
		if (col[b.u] != col[b.v]) b.dist = dis(b.u, b.v);// 如果 u 和 v 颜色不同，就可以合并
		return b;
	}if (!b.u){// 同理
		if (col[a.u] != col[a.v]) a.dist = dis(a.u, a.v);
		return a;
	}
	ll d1 = dis(a.u, a.v), d2 = dis(b.u, b.v), d3 = dis(a.u, b.u), 
		d4 = dis(a.v, b.v), d5 = dis(a.u, b.v), d6 = dis(a.v, b.u), diss = 0;
	if (d1 >= diss) ans.u = a.u, ans.v = a.v, diss = d1;
	if (d2 >= diss) ans.u = b.u, ans.v = b.v, diss = d2;
	if (d3 >= diss) ans.u = a.u, ans.v = b.u, diss = d3;
	if (d4 >= diss) ans.u = a.v, ans.v = b.v, diss = d4;
	if (d5 >= diss) ans.u = a.u, ans.v = b.v, diss = d5;
	if (d6 >= diss) ans.u = a.v, ans.v = b.u, diss = d6;
    // 以上处理 u 和 v
	ans.dist = max(a.dist, b.dist);
	if (d1 >= ans.dist && col[a.u] != col[a.v]) ans.dist = d1;
	if (d2 >= ans.dist && col[b.u] != col[b.v]) ans.dist = d2;
	if (d3 >= ans.dist) ans.dist = d3;// 因为如果分别选了两个儿子的点，颜色就一定不同
	if (d4 >= ans.dist) ans.dist = d4;
	if (d5 >= ans.dist) ans.dist = d5;
	if (d6 >= ans.dist) ans.dist = d6;
	return ans;
}
```

但是这样子怎么处理叶子节点呢？我们要知道对于一种颜色中最远的两个点。同样使用上面的性质，建立线段树。

我们称前面那个线段树是大线段树，后面那个线段树是小线段树。小线段树节点 $[l,r]$ 表示编号 $[l,r]$ 的点最远的点，用一样的方法合并儿子信息。

但是每个颜色的答案都不同，所以要使用动态开点线段树。这样子我们就支持修改一个点的颜色了。

```cpp
il void sets(int &p){p = ++ep, ls[p] = rs[p] = tr[p].u = tr[p].v = 0;}
void add(int &p, int l, int r, int x, int k){
	if (!p) sets(p);
	if (l == r) return tr[p].u = tr[p].v = k, void(0);
	int mid = (l + r) >> 1;
	if (x <= mid) add(ls[p], l, mid, x, k);
	else add(rs[p], mid + 1, r, x, k);
	if (!ls[p]) tr[p] = tr[rs[p]];// 没有儿子就不用了
	else if (!rs[p]) tr[p] = tr[ls[p]];
	else tr[p] = tr[ls[p]] + tr[rs[p]];
}
```

然后就可以在大线段树上单点修改了。

```cpp
void upd(int &p, int l, int r, int x, int u, int v){
	if (!p) sets(p);
	if (l == r) return tr[p].u = u, tr[p].v = v, void(0);
	int mid = (l + r) >> 1;
	if (x <= mid) upd(ls[p], l, mid, x, u, v);
	else upd(rs[p], mid + 1, r, x, u, v);
	if (!ls[p]) tr[p] = tr[rs[p]];
	else if (!rs[p]) tr[p] = tr[ls[p]];
	else tr[p] = tr[ls[p]] + tr[rs[p]];
}
```

为了方便处理距离，我们可以把询问离线下来，先求 LCA。当然，如果使用倍增求 LCA，时间复杂度是 $O(n \log^2 n)$ 的，所以我们要使用 ST 表和欧拉序求 LCA，这样时间复杂度就是 $O(n \log n)$ 了。

有一点写代码的建议，可以把大线段树写到动态开点线段树上，单独开一个跟用，因为大线段树的合并和小线段树几乎一样，这样子写代码和 debug 都很方便。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 500005
#define M 3000005
#define max(x, y) (x > y ? x : y)
#define min(x, y) (x < y ? x : y)
il int rd(){
	int s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
int n, m, col[N], rt[N], ls[M << 2], rs[M << 2], ep;
int head[N], nxt[N << 1], to[N << 1], ww[N << 1], en;
ll dik[N];
il void add_edge(ll u, ll v, ll w){nxt[++en] = head[u], head[u] = en, to[en] = v, ww[en] = w;}
struct LCA{
	int dfn[N], pos[N], cnt, minn[N << 1][25], lg[N << 1];
	void dfs(int u, int fa){
		minn[++cnt][0] = u, pos[u] = cnt;
		for (int i = head[u]; i; i = nxt[i]) if (to[i] != fa)
			dik[to[i]] = dik[u] + ww[i], dfs(to[i], u), minn[++cnt][0] = u;
	}il int mink(int l, int r){
		if (l > r) swap(l, r);
		int p = lg[r - l + 1], u = minn[l][p], v = minn[r - (1 << p) + 1][p];
		return dik[u] < dik[v] ? u : v;
	}il int lca(int u, int v){return mink(pos[u], pos[v]);}
	il void init(){
		for (int j = 1; (1 << j) <= cnt; j++) for (int i = 1; i + (1 << j) - 1 <= cnt; i++){
			ll u = minn[i][j - 1], v = minn[i + (1 << (j - 1))][j - 1];
			minn[i][j] = dik[u] < dik[v] ? u : v;
		}
	}
}t1;
il ll dis(int u, int v){return dik[u] + dik[v] - dik[t1.lca(u, v)] * 2;}
struct ST{
	int u, v;
	ll dist;
}tr[M << 2];
ST operator + (const ST &x, const ST &y){
	ST ans, a = x, b = y;
	if (!a.u){
		if (col[b.u] != col[b.v]) b.dist = dis(b.u, b.v);
		return b;
	}if (!b.u){
		if (col[a.u] != col[a.v]) a.dist = dis(a.u, a.v);
		return a;
	}
	ll d1 = dis(a.u, a.v), d2 = dis(b.u, b.v), d3 = dis(a.u, b.u), 
		d4 = dis(a.v, b.v), d5 = dis(a.u, b.v), d6 = dis(a.v, b.u), diss = 0;
	if (d1 >= diss) ans.u = a.u, ans.v = a.v, diss = d1;
	if (d2 >= diss) ans.u = b.u, ans.v = b.v, diss = d2;
	if (d3 >= diss) ans.u = a.u, ans.v = b.u, diss = d3;
	if (d4 >= diss) ans.u = a.v, ans.v = b.v, diss = d4;
	if (d5 >= diss) ans.u = a.u, ans.v = b.v, diss = d5;
	if (d6 >= diss) ans.u = a.v, ans.v = b.u, diss = d6;
	ans.dist = max(a.dist, b.dist);
	if (d1 >= ans.dist && col[a.u] != col[a.v]) ans.dist = d1;
	if (d2 >= ans.dist && col[b.u] != col[b.v]) ans.dist = d2;
	if (d3 >= ans.dist) ans.dist = d3;
	if (d4 >= ans.dist) ans.dist = d4;
	if (d5 >= ans.dist) ans.dist = d5;
	if (d6 >= ans.dist) ans.dist = d6;
	return ans;
}il void sets(int &p){p = ++ep, ls[p] = rs[p] = tr[p].u = tr[p].v = 0;}
void add(int &p, int l, int r, int x, int k){
	if (!p) sets(p);
	if (l == r) return tr[p].u = tr[p].v = k, void(0);
	int mid = (l + r) >> 1;
	if (x <= mid) add(ls[p], l, mid, x, k);
	else add(rs[p], mid + 1, r, x, k);
	if (!ls[p]) tr[p] = tr[rs[p]];
	else if (!rs[p]) tr[p] = tr[ls[p]];
	else tr[p] = tr[ls[p]] + tr[rs[p]];
}void upd(int &p, int l, int r, int x, int u, int v){
	if (!p) sets(p);
	if (l == r) return tr[p].u = u, tr[p].v = v, void(0);
	int mid = (l + r) >> 1;
	if (x <= mid) upd(ls[p], l, mid, x, u, v);
	else upd(rs[p], mid + 1, r, x, u, v);
	if (!ls[p]) tr[p] = tr[rs[p]];
	else if (!rs[p]) tr[p] = tr[ls[p]];
	else tr[p] = tr[ls[p]] + tr[rs[p]];
}struct Q{
	int x, c;
}q[N];
signed main(){
	for (int i = 2; i <= 1000000; i++) t1.lg[i] = t1.lg[i >> 1] + 1;
	for (int T = rd(); T--;){
		m = rd(), col[1] = rd(), n = 1, ep = t1.cnt = en = 0;
		for (int i = 1; i <= m; i++){
			int op = rd(), u = rd(), c = rd();
			if (op == 0){
				int d = rd();
				add_edge(++n, u, d), add_edge(u, n, d), q[i] = Q{n, c};
			}else q[i] = Q{u, c};
		}t1.dfs(1, 0), t1.init();
		add(rt[col[1]], 1, n, 1, 1), upd(rt[0], 1, m, col[1], 1, 1);
		for (int i = 1; i <= m; i++){
			ll u = q[i].x, c = q[i].c;
			if (col[u]) add(rt[col[u]], 1, n, u, 0), upd(rt[0], 1, m, col[u], tr[rt[col[u]]].u, tr[rt[col[u]]].v);
			col[u] = c;
			add(rt[col[u]], 1, n, u, u), upd(rt[0], 1, m, col[u], tr[rt[col[u]]].u, tr[rt[col[u]]].v);
			printf ("%lld\n", tr[rt[0]].dist);
		}for (int i = 0; i <= m + 1; i++) head[i] = rt[i] = col[i] = 0;
		for (int i = 1; i <= ep; i++) ls[i] = rs[i] = tr[i].u = tr[i].v = tr[i].dist = 0;
	}
	return 0;
}
```

---

## 作者：xxxxxzy (赞：0)

这能上黑？

首先是一个关于直径的结论，就是两对直径 $(u_1,v_1),(u_2,v_2)$ 合并，产生的新直径在这四个点选两个之中。

对于这个题，我们对于每一种颜色维护一个同色的直径，然后再用个东西把这些同色直径合并起来。

发现我们要维护这个半群信息的单点修改和全局查，考虑用一个线段树维护。

值得注意的是，异色直径合并时，同色对产生的贡献不算入答案，但是同色对产生的两个端点是可以作为新直径的两个端点的。

还需要上一个 ST 表实现 $O(1)$ 查询两点距离。

一定一定一定要注意最多有 $q+1$ 个节点。

时空复杂度 $O(n \log n)$。

---

## 作者：无名之雾 (赞：0)

很好的数据结构，使我的调试代码能力旋转。

> 维护一棵点有颜色的树，一开始只有编号为 $1$ 的节点，其颜色为 $c$，要求支持以下操作 $q$ 次：
> 
> - 给定 $x,c,d$ 添加一个编号为 $n+1$ 颜色为 $c$ 的节点，向点 $x$ 连一条长度为 $d$ 的边
> - 给定 $x,c$ 将点 $x$ 的颜色变成 $c$。
>
> 每次操作后，需要在树上选两个颜色不同的点并最大化它们之间最短简单路径的长度，并输出。
>
> $1\le q \le 1\times 10^5$。


## solution

本题不要求强制在线，而且添加节点并不会改变树的形状和边的长度。所以我们可以套路化的离线所有操作并把树建出来，将两种操作都转化为对颜色的修改。

首先考虑对同种颜色去维护直径长度是好做的。考虑一个点集经典结论：

> 考虑两个点集 $S_1,S_2$，这两个点集的直径两端的点分别是 $(x_1,y_1),(x_2,y_2)$ 那么 $S_1,S_2$ 的并集的直径两端的点一定是 $(x_1,y_1),(x_2,y_1),(x_1,y_2),(x_2,y_2),(x_2,x_1),(y_2,y_1)$ 这 $6$ 对点对中的一组。


所以我们开两种线段树。

第一种线段树为动态开点的线段树。我们对每种颜色开一颗线段树，其下标为原树上的节点编号。然后维护区间距离最短的点对，并通过上面的结论合并。

第二种线段树以每种颜色为下标，维护每种颜色的同色直径，然后通过上面的结论将直径向上合并，统计异色点对距离最大值，一直向上合并到根节点就是答案。

然后直接做的话因为需要动态求 LCA，所以时间复杂度是 $O(q \log^2 q)$ 的。这可能会被卡掉。

但是注意到我们已经离线了，所以可以直接把这棵树的 dfn 序拍到 ST 表上，$O(q \log q)-O(1)$ 求 LCA。当然如果你想，你可以写四毛子做到 $O(q)-O(1)$ LCA。

时间复杂度 $O(q \log q)$。


同时这里再提供一种神秘做法。

如果只需要考虑一组询问。我们可以使用淀粉质。

从每个分支中心出发可以得到一个三元组 $(a,b,c)$ 分别表示分支中心到目标点的长度，目标点颜色，和目标点所在子树。问题转化为选择两个三元组 $(a_1,b_1,c_1),(a_2,b_2,c_2)$ 最大化 $a_1+a_2$。显然是容易维护的。

然后对于本题，我们可以考虑淀粉树。每次修改颜色重做 $\log n$ 个分治中心的结果。注意到我们只需要支持单点改全局查，所以只需要对于每个分治中心开一个线段树解决。

## code

给出第一种做法的代码。~~我的淀粉质太差了没调出来。~~

代码写的有点丑和史山。但是还是比较清晰的。

```cpp
#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define ll long long
inline ll read(){
    ll s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void out(int x){
    if(x==0){putchar('0');return;}
    int len=0,k1=x,c[10005];
    if(k1<0)k1=-k1,putchar('-');
    while(k1)c[len++]=k1%10+'0',k1/=10;
    while(len--)putchar(c[len]);
}
const int N=5e5+5,M=2e7+5;
int color[N],fa[N],n,q;
struct qry{int op,c;ll d;int id;}qry[N];
vector<pair<int,int>>r[N];
struct LCA{
    int st[20][N],in[N],l[N],timer;ll d[N];
    void dfs(int x){
        in[x]=++timer,st[0][in[x]]=x;
        for(auto v:r[x]){
            l[v.first]=l[x]+1;
            d[v.first]=d[x]+v.second;
            dfs(v.first);
        }
    }
    inline void cout_dfs(){
        printf("%d\nrec:\n",timer);
        printf("\nin:\n");
        for(int i=1;i<=timer;i++)printf("%d ",in[i]);
        printf("\nout:\n");
        printf("\nlevel:\n");
        for(int i=1;i<=timer;i++)printf("%d ",l[i]);
        printf("\nd:\n");
        for(int i=1;i<=timer;i++)printf("%d ",d[i]);
        printf("\n");
    }
    int chkmin(int u,int v){return l[u]<l[v]?u:v;}
    void init(){
        for(int i=1;i<=19;i++){
            for(int j=1;j<=n-(1<<i)+1;j++){
                st[i][j]=chkmin(st[i-1][j],st[i-1][j+(1<<i-1)]);
            }
        }
    }
    void cout_st(){
        printf("st:\n");
        for(int i=0;i<=ceil(log2(500000));i++){
            printf("%d\n\n",i);
            for(int j=1;j<=n-(1<<i)-1;j++)
                printf("%d %d\n",j,st[i][j]);
        }
    }
    int get(int u,int v){
        if(u==v)return u;
        u=in[u];v=in[v];
        if(u>v)swap(u,v);int len=__lg(v-u);
        return fa[chkmin(st[len][u+1],st[len][v-(1<<len)+1])];
    }
    ll dis(int u,int v){
        ll cnt=(u==0)+(v==0);
        if(cnt>0)return -cnt;
        return d[u]+d[v]-2ll*d[get(u,v)];
    }
}lca;
struct dia{pair<int,int>fur;};
dia chkmax(dia ans,int x,int y){
    ll dist=lca.dis(x,y);
    if(lca.dis(ans.fur.first,ans.fur.second)<dist)ans.fur={x,y};
    return ans;
}
struct SGT1{
    dia merge(dia u,dia v){
        dia ans=u;
        ans=chkmax(ans,v.fur.first,v.fur.second);
        ans=chkmax(ans,u.fur.first,v.fur.first);
        ans=chkmax(ans,u.fur.first,v.fur.second);
        ans=chkmax(ans,u.fur.second,v.fur.first);
        ans=chkmax(ans,u.fur.second,v.fur.second);
        return ans;
    }
    ll rt[N];int cnt;
    struct sgt1{int ls,rs;dia longst;}tr[M];
    void push_up(int x){
        if(tr[x].ls==0&&tr[x].rs==0){tr[x].longst.fur={0,0};return ;}
        if(tr[x].ls==0){tr[x].longst=tr[tr[x].rs].longst;return ;}
        if(tr[x].rs==0){tr[x].longst=tr[tr[x].ls].longst;return ;}
        tr[x].longst=merge(tr[tr[x].ls].longst,tr[tr[x].rs].longst);
    }
    int insert(int p,int l,int r,int id){
        if(!p)p=++cnt;
        if(l==r){tr[p].longst.fur={id,id};return p;}
        int mid=(l+r)>>1;
        if(id<=mid)tr[p].ls=insert(tr[p].ls,l,mid,id);
        else tr[p].rs=insert(tr[p].rs,mid+1,r,id);
        push_up(p);return p;
    }
    int del(int p,int l,int r,int id){
        if(!p)p=++cnt;
        if(l==r){tr[p].longst.fur={0,0};return p;}
        int mid=(l+r)>>1;
        if(id<=mid)tr[p].ls=del(tr[p].ls,l,mid,id);
        else tr[p].rs=del(tr[p].rs,mid+1,r,id);
        push_up(p);return p;
    }
    void init(){
        for(int i=1;i<=q+1;i++)rt[i]=0;
        for(int i=1;i<=cnt;i++){
            tr[i].ls=0;tr[i].rs=0;
            tr[i].longst.fur={0,0};
        }cnt=0;
    }
}sgt1;
struct SGT2{
    struct sgt{int l,r;dia longst[2];}tr2[N<<2];
    int ls(int p){return p<<1;}
    int rs(int p){return p<<1|1;}
    dia merge2(dia u,dia v,dia x,dia y){
        dia ans=x;
        ans=chkmax(ans,y.fur.first,y.fur.second);
        ans=chkmax(ans,u.fur.first,v.fur.first);
        ans=chkmax(ans,u.fur.first,v.fur.second);
        ans=chkmax(ans,u.fur.second,v.fur.first);
        ans=chkmax(ans,u.fur.second,v.fur.second);
        return ans;
    }
    void pushup_sgt(int u){
        tr2[u].longst[0]=sgt1.merge(tr2[ls(u)].longst[0],tr2[rs(u)].longst[0]);
        tr2[u].longst[1]=merge2(tr2[ls(u)].longst[0],tr2[rs(u)].longst[0],tr2[ls(u)].longst[1],tr2[rs(u)].longst[1]);
    }
    void build_sgt(int u,int l,int r){
        tr2[u].l=l,tr2[u].r=r;
        if(l==r)return ;
        int mid=(l+r)>>1;
        build_sgt(ls(u),l,mid);
        build_sgt(rs(u),mid+1,r);
    }
    void upd(int u,int l,int r,int c,pair<int,int> rec){
        if(l==r){
            tr2[u].longst[0].fur=rec;
            tr2[u].longst[1].fur={0,0};
            return ;
        }
        int mid=(l+r)>>1;
        if(c<=mid)upd(ls(u),l,mid,c,rec);
        else upd(rs(u),mid+1,r,c,rec);
        pushup_sgt(u);
    }
    void clear(int u,int l,int r){
        tr2[u].longst[0].fur={0,0};
        tr2[u].longst[1].fur={0,0};
        if(l==r)return ;
        int mid=(l+r)>>1;
        clear(ls(u),l,mid),clear(rs(u),mid+1,r);
    }
    inline void cout_sgt(int u){
        printf("node: %d\n%d %d\n",u,tr2[u].l,tr2[u].r);
        if(tr2[u].l==tr2[u].r)return ;
        cout_sgt(ls(u));cout_sgt(rs(u));
    }
}sgt2;
signed main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    int t=read();
    while(t--){
        q=read(),color[1]=read();n=1,sgt1.cnt=0,lca.timer=0;
        // sgt2.build_sgt(1,1,q+1);
        for(int i=1;i<=q;i++){
            int op=read();
            if(op==0){
                int x=read(),c=read();ll d=read();
                fa[++n]=x;qry[i]={op,c,d,n};
                r[x].push_back({n,d});
            }
            else{
                int x=read(),c=read();
                qry[i]={op,c,0,x};
            }
        }lca.dfs(1);lca.init();
        sgt1.rt[color[1]]=sgt1.insert(sgt1.rt[color[1]],1,q+1,1);
		sgt2.upd(1,1,q+1,color[1],sgt1.tr[sgt1.rt[color[1]]].longst.fur);
        for(int i=1;i<=q;i++){
			if(qry[i].op==0){
				color[qry[i].id]=qry[i].c;
				sgt1.rt[qry[i].c]=sgt1.insert(sgt1.rt[color[qry[i].id]],1,q+1,qry[i].id);
                // cout<<color[qry[i].id]<<" "<<sgt1.rt[qry[i].c]<<"\n";
				// printf("%d %d\n",sgt1.tr[sgt1.rt[color[qry[i].id]]].longst.fur.first,sgt1.tr[sgt1.rt[color[qry[i].id]]].longst.fur.second);
                sgt2.upd(1,1,q+1,color[qry[i].id],sgt1.tr[sgt1.rt[color[qry[i].id]]].longst.fur);
                // cout<<color[qry[i].id]<<" "<<sgt1.tr[sgt1.rt[color[qry[i].id]]].longst.fur.first<<" "<<sgt1.tr[sgt1.rt[color[qry[i].id]]].longst.fur.second<<"\n";
			}
			else{
				sgt1.rt[color[qry[i].id]]=sgt1.del(sgt1.rt[color[qry[i].id]],1,q+1,qry[i].id);
				sgt2.upd(1,1,q+1,color[qry[i].id],sgt1.tr[sgt1.rt[color[qry[i].id]]].longst.fur);
				color[qry[i].id]=qry[i].c;
				sgt1.rt[qry[i].c]=sgt1.insert(sgt1.rt[color[qry[i].id]],1,q+1,qry[i].id);
				sgt2.upd(1,1,q+1,color[qry[i].id],sgt1.tr[sgt1.rt[color[qry[i].id]]].longst.fur);
			}
            // sgt2.cout_sgt(1);
			cout<<max(0ll,lca.dis(sgt2.tr2[1].longst[1].fur.first,sgt2.tr2[1].longst[1].fur.second))<<"\n";
            // cout<<"\n\n";
		}	
		for(int i=1;i<=n;i++)r[i].clear();sgt1.init();sgt2.clear(1,1,q+1);
    }
    return 0;
}	

```

---

## 作者：Diaоsi (赞：0)

[Colorful Tree](https://www.luogu.com.cn/problem/P9665)

给定一棵树，起始时只有一号节点有颜色，每次进行两种操作中的一种：

- 给一个没有颜色的节点加上颜色
- 修改一个节点的颜色

每次操作后，输出异色点的直径。

首先维护同色点的直径是平凡的，对于两个点集 $S$ 和 $T$，其直径端点分别为 $(x,y)$ 和 $(u,v)$，合并两个点集后新的直径的两端点一定出自这四个节点中的两个，共 $\dbinom{4}{2}=6$ 种情况，可以 $\mathcal{O}(1)$ 判断。

对于每个颜色开一个以点编号为下标的线段树，在每一层合并左右儿子的直径，这样在每次修改之后我们都可以得到当前的同色直径。

再开一个以颜色为下标的线段树，叶子节点储存每个颜色的同色直径（包括其对应的端点），然后将这些直径依次向上合并，统计合并的过程中**异色**点对的距离最大值，同样将这些最大值向上合并，根节点的最大值即是答案。

若使用 ST 表 $\mathcal{O}(n\log n)-\mathcal{O}(1)$ 地求 $\mathrm{lca}$，则时间复杂度 $\mathcal{O}(n\log n)$。

由于 CF 的机子比较卡常，所以下面的代码写的比较丑陋。

Code:

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=500010,M=3000010,INF=0x3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int head[N],ver[N<<1],edge[N<<1],Next[N<<1],tot;
ll d[N],in[N],st[N<<1][20],lg[N<<1],ts;
int T,n,m,cnt,col[N],rt[N];
struct rec{
	int op,x,c,z;
}q[N];
void add(int x,int y,int z){
	ver[++tot]=y,edge[tot]=z,Next[tot]=head[x],head[x]=tot;
}
void dfs(int x,int fa){
    in[x]=++ts;st[ts][0]=x;
    for(int i=head[x];i;i=Next[i]){
        int y=ver[i],z=edge[i];
        if(y==fa)continue;
        d[y]=d[x]+z;
        dfs(y,x);
    }
    ++ts;
    if(fa)st[ts][0]=fa;
}
void init(){
    for(int j=1;(1<<j)<=ts;j++)
        for(int i=1;i+(1<<j)-1<=ts;i++){
            int x=st[i][j-1],y=st[i+(1<<(j-1))][j-1];
            st[i][j]=(d[x]<d[y])?x:y;
        }
}
int lca(int x,int y){
    int l=in[x],r=in[y];
    if(l>r)swap(l,r);int ln=lg[r-l+1];
    return d[st[l][ln]]<d[st[r-(1<<ln)+1][ln]]?st[l][ln]:st[r-(1<<ln)+1][ln];
}
ll dist(int x,int y){
    return d[x]+d[y]-2*d[lca(x,y)];
}
struct SegmentTree{
	int l,r;
	ll dat;
	pair<int,int> h;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define h(x) tree[x].h
	#define dat(x) tree[x].dat
}tree[M<<2];
pair<int,int> merge(ll &dis,pair<int,int> u,pair<int,int> v){
	if(!u.fi){
		if(col[v.fi]!=col[v.se])
			dis=dist(v.fi,v.se);
		return v;
	}
	if(!v.fi){
		if(col[u.fi]!=col[u.se])
			dis=dist(u.fi,u.se);
		return u;
	}
	int l1=u.fi,r1=u.se;
	int l2=v.fi,r2=v.se;
	ll len=0;
	pair<int,int> res;
	ll d1=dist(l1,r1),d2=dist(l2,r2);
	ll d3=dist(l1,l2),d4=dist(r1,r2);
	ll d5=dist(l1,r2),d6=dist(r1,l2);
	if(d1>=len)len=d1,res=mp(l1,r1);
	if(d2>=len)len=d2,res=mp(l2,r2);
	if(d3>=len)len=d3,res=mp(l1,l2);
	if(d4>=len)len=d4,res=mp(r1,r2);
	if(d5>=len)len=d5,res=mp(l1,r2);
	if(d6>=len)len=d6,res=mp(r1,l2);
	if(d1>=dis&&col[l1]!=col[r1])dis=d1;
	if(d2>=dis&&col[l2]!=col[r2])dis=d2;
	if(d3>=dis)dis=d3;
	if(d4>=dis)dis=d4;
	if(d5>=dis)dis=d5;
	if(d6>=dis)dis=d6;
	return res;
}
int build(){
	int p=++cnt;
	l(p)=r(p)=dat(p)=0;
	h(p)=mp(0,0);
	return p;
}
void insert(int p,int l,int r,int pos,pair<int,int> t){
	if(l==r){h(p)=t;return;}
	int mid=(l+r)>>1;ll dis=0;
	if(pos<=mid){
		if(!l(p))l(p)=build();
		insert(l(p),l,mid,pos,t);
	}
	else{
		if(!r(p))r(p)=build();
		insert(r(p),mid+1,r,pos,t);
	}
	if(!l(p))h(p)=h(r(p));
	if(!r(p))h(p)=h(l(p));
	if(l(p)&&r(p))h(p)=merge(dis,h(l(p)),h(r(p)));
}
void change(int p,int l,int r,int pos,pair<int,int> t){
	if(l==r){h(p)=t;return;}
	int mid=(l+r)>>1;ll dis=0;
	if(pos<=mid){
		if(!l(p))l(p)=build();
		change(l(p),l,mid,pos,t);
	}
	else{
		if(!r(p))r(p)=build();
		change(r(p),mid+1,r,pos,t);
	}
	if(!l(p)){
		h(p)=h(r(p));
		dat(p)=dat(r(p));
	}
	if(!r(p)){
		h(p)=h(l(p));
		dat(p)=dat(l(p));
	}
	if(l(p)&&r(p)){
		h(p)=merge(dis,h(l(p)),h(r(p)));
		dat(p)=max(dis,max(dat(l(p)),dat(r(p))));
	}
}
void solve(){
	cnt=tot=ts=0;n=1;
	scanf("%d%d",&m,&col[1]);
	for(int i=1;i<=m;i++){
		int op,x,c,z;
		scanf("%d",&op);
		if(op&1){
			scanf("%d%d",&x,&c);
			q[i]=(rec){1,x,c,0};
		}
		else{
			++n;
			scanf("%d%d%d",&x,&c,&z);
			q[i]=(rec){0,n,c,z};
			add(x,n,z);add(n,x,z);
		}
		if(!rt[c])rt[c]=build();
	}
	dfs(1,0);
	init();
	rt[0]=build();
	rt[col[1]]=build();
	change(rt[0],1,m,col[1],mp(1,1));
	insert(rt[col[1]],1,n,1,mp(1,1));
	for(int i=1;i<=m;i++){
		int op=q[i].op,x=q[i].x,c=q[i].c;
		if(op&1){
			insert(rt[col[x]],1,n,x,mp(0,0));
			pair<int,int> t=h(rt[col[x]]);
			change(rt[0],1,m,col[x],t);
		}
		col[x]=c;
		insert(rt[col[x]],1,n,x,mp(x,x));
		pair<int,int> t=h(rt[col[x]]);
		change(rt[0],1,m,col[x],t);
		printf("%lld\n",dat(rt[0]));
	}
	for(int i=1;i<=n;i++)head[i]=col[i]=0;
	for(int i=0;i<=m;i++)rt[i]=0;
	for(int i=1;i<=cnt;i++)
		l(i)=r(i)=dat(i)=0,h(i)=mp(0,0);
}
int main(){
	for(int i=2;i<N<<1;i++)lg[i]=lg[i>>1]+1;
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：happybob (赞：0)

考虑一个类似的问题。如果要求的是相同颜色的距离最大值而非不同，应该怎么做？

显然的根据直径合并的经典性质，对于每种颜色开一棵动态开点线段树，每个节点维护区间内这种颜色的直径端点。然后搞个 `multiset` 维护每棵线段树的根的答案即可。

现在考虑原题。发现在这个思路上改改就对了。具体地，我们还是维护每种颜色的直径。然后建立一棵外层线段树，以颜色为下标，维护每个区间内的最大异色答案，以及不关心颜色是否相同的直径端点。合并仍然考虑 $\dbinom{4}{2}=6$ 种方案即可。

由于线段树进行了动态开点，我们要求 $O(n \log n)$ 次 LCA，如果使用树剖或者倍增维护 LCA，复杂度到达了 $O(n \log^2 n)$，可能有些压力。这里使用 ST 表维护欧拉序的做法就可以做到 $O(n \log n)-O(1)$ 求 LCA。总复杂度为 $O(n \log n)$。题目时限很宽松，常数大一点理应也能通过。注意多测清空。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <array>
#include <set>
#include <map>
using namespace std;

using ll = long long;

const int N = 5e5 + 5, M = 1e6 + 5;

vector<pair<int, int>> G[N];

int q, col[N];

namespace RMQ
{
	int pos[M], idx, euler[M], dep[M], ra[M];
	int st[M][20];
	int LG2[M];
	void dfs(int u, int fa, int d)
	{
		euler[++idx] = u;
		dep[idx] = d;
		ra[idx] = u;
		if (!pos[u]) pos[u] = idx;
		for (auto& [j, w] : G[u])
		{
			if (j == fa) continue;
			dfs(j, u, d + 1);
			euler[++idx] = u;
			ra[idx] = u;
			dep[idx] = d;
		}
	}
	const static inline void Init() noexcept
	{
		for (int i = 1; i <= idx; i++)
		{
			ra[i] = pos[i] = euler[i] = dep[i] = 0;
			for (int j = 0; j < 20; j++) st[i][j] = 0;
		}
		idx = 0;
		dfs(1, 0, 1);
		for (int i = 1; i <= idx; i++) st[i][0] = i;
		for (int j = 1; j < 20; j++)
		{
			for (int i = 1; i + (1 << j) - 1 <= idx; i++)
			{
				if (dep[st[i][j - 1]] < dep[st[i + (1 << (j - 1))][j - 1]]) st[i][j] = st[i][j - 1];
				else st[i][j] = st[i + (1 << (j - 1))][j - 1];
			}
		}
	}
	const inline static int query(int l, int r) noexcept
	{
		if (l > r) swap(l, r);
		int len = r - l + 1, p = LG2[len];
		int x = st[l][p], y = st[r - (1 << p) + 1][p];
		return (dep[x] < dep[y] ? ra[x] : ra[y]);
	}
	const inline static int LCA(int u, int v) noexcept
	{
		return query(pos[u], pos[v]);
	}
}

int n;
ll dis[N];

void dfs(int u, int fa)
{
	for (auto& [j, w] : G[u])
	{
		if (j ^ fa)
		{
			dis[j] = dis[u] + w;
			dfs(j, u);
		}
	}
}

struct Query
{
	int op, x, c, d;
}qry[N];

inline ll querydis(int u, int v)
{
	int L = RMQ::LCA(u, v);
	return dis[u] + dis[v] - (dis[L] << 1ll);
}

int tmp[5];

class SegmentTree1
{
public:
	int idx;
	struct Node
	{
		int ls, rs, nu, nv;
	}tr[N * 30];
	void pushup(int u)
	{
		int ls = tr[u].ls, rs = tr[u].rs;
		tr[u].nu = tr[u].nv = 0;
		tmp[1] = tr[ls].nu, tmp[2] = tr[ls].nv, tmp[3] = tr[rs].nu, tmp[4] = tr[rs].nv;
		ll maxd = -1;
		int ru = 0, rv = 0;
		for (int i = 1; i <= 4; i++)
		{
			if (!tmp[i]) continue;
			for (int j = i; j <= 4; j++)
			{
				if (!tmp[j]) continue;
				ll d = querydis(tmp[i], tmp[j]);
				if (d > maxd)
				{
					maxd = d;
					ru = tmp[i], rv = tmp[j];
				}
			}
		}
		tr[u].nu = ru, tr[u].nv = rv;
	}
	int ins(int u, int l, int r, int x, bool v)
	{
		if (!u)
		{
			u = ++idx;
			tr[u].ls = tr[u].rs = tr[u].nu = tr[u].nv = 0;
		}
		if (l == r)
		{
			if (v)
			{
				tr[u].nu = tr[u].nv = x;
			}
			else tr[u].nu = tr[u].nv = 0;
			return u;
		}
		int mid = l + r >> 1;
		if (x <= mid) tr[u].ls = ins(tr[u].ls, l, mid, x, v);
		else tr[u].rs = ins(tr[u].rs, mid + 1, r, x, v);
		pushup(u);
		return u;
	}
}sgt1;

class SegmentTree2
{
public:
	struct Node
	{
		int l, r, nu, nv;
		ll maxn;
	}tr[N << 2];
	void pushup(int u)
	{
		tr[u].maxn = max(tr[u << 1].maxn, tr[u << 1 | 1].maxn);
		tr[u].nu = tr[u].nv = 0;
		ll maxd = -1;
		int ru = 0, rv = 0;
		int ls = u << 1, rs = u << 1 | 1;
		tmp[1] = tr[ls].nu, tmp[2] = tr[ls].nv, tmp[3] = tr[rs].nu, tmp[4] = tr[rs].nv;
		for (int i = 1; i <= 4; i++)
		{
			if (!tmp[i]) continue;
			for (int j = i; j <= 4; j++)
			{
				if (!tmp[j]) continue;
				ll d = querydis(tmp[i], tmp[j]);
				if (col[tmp[i]] ^ col[tmp[j]])
				{
					tr[u].maxn = max(tr[u].maxn, d);
				}
				if (d > maxd)
				{
					maxd = d, ru = tmp[i], rv = tmp[j];
				}
			}
		}
		tr[u].nu = ru, tr[u].nv = rv;
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, 0, 0, 0ll };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
	}
	void update(int u, int x, int nu, int nv)
	{
		if (tr[u].l == tr[u].r)
		{
			tr[u].nu = nu, tr[u].nv = nv, tr[u].maxn = 0ll;
			return;
		}
		int mid = tr[u].l + tr[u].r >> 1;
		if (x <= mid) update(u << 1, x, nu, nv);
		else update(u << 1 | 1, x, nu, nv);
		pushup(u);
	}
	pair<int, int> query(int u, int x)
	{
		if (tr[u].l == tr[u].r) return make_pair(tr[u].nu, tr[u].nv);
		int mid = tr[u].l + tr[u].r >> 1;
		if (x <= mid) return query(u << 1, x);
		return query(u << 1 | 1, x);
	}
}sgt2;
int rt[N], t;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	for (int i = 2; i < M; i++) RMQ::LG2[i] = RMQ::LG2[i >> 1] + 1;
	cin >> t;
	while (t--)
	{
		for (int i = 1; i <= n; i++) G[i].clear(), G[i].shrink_to_fit(), col[i] = 0;
		n = 1;
		cin >> q >> col[1];
		for (int i = 1; i <= q; i++) rt[i] = 0;
		sgt1.idx = 0;
		for (int i = 1; i <= q; i++)
		{
			cin >> qry[i].op >> qry[i].x >> qry[i].c;
			if (qry[i].op == 0)
			{
				cin >> qry[i].d;
				n++;
				col[n] = qry[i].c;
				G[qry[i].x].emplace_back(n, qry[i].d);
				G[n].emplace_back(qry[i].x, qry[i].d);
			}
		}
		dfs(1, 0);
		RMQ::Init();
		int rn = n;
		rt[col[1]] = sgt1.ins(rt[col[1]], 1, n, 1, 1);
		sgt2.build(1, 1, q);
		sgt2.update(1, col[1], 1, 1);
		n = 1;
		for (int i = 1; i <= q; i++)
		{
			if (qry[i].op == 0)
			{
				n++;
				rt[col[n]] = sgt1.ins(rt[col[n]], 1, rn, n, 1);
				int nu = sgt1.tr[rt[col[n]]].nu, nv = sgt1.tr[rt[col[n]]].nv;
				sgt2.update(1, col[n], nu, nv);
			}
			else
			{
				int x = qry[i].x;
				rt[col[x]] = sgt1.ins(rt[col[x]], 1, rn, x, 0);
				int nu = sgt1.tr[rt[col[x]]].nu, nv = sgt1.tr[rt[col[x]]].nv;
				sgt2.update(1, col[x], nu, nv);
				col[x] = qry[i].c;
				rt[col[x]] = sgt1.ins(rt[col[x]], 1, rn, x, 1);
				nu = sgt1.tr[rt[col[x]]].nu, nv = sgt1.tr[rt[col[x]]].nv;
				sgt2.update(1, col[x], nu, nv);
			}
			cout << sgt2.tr[1].maxn << "\n";
		}
	}
	return 0;
}
```

---

