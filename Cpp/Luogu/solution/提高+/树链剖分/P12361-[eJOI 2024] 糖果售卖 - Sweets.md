# [eJOI 2024] 糖果售卖 / Sweets

## 题目背景

Sandu 高中毕业后成为了一名糖果商人！



## 题目描述

在一座城市中有 $N$ 个市场，还有 $N-1$ 条道路连接他们。这些市场和道路构成了一个树形结构。每一天开始时，Sandu 都会来到 $1$ 号市场，开始售卖糖果。

每个市场都有技能值和困难度。当你来到这个市场时，你的技能值会增加这个市场的技能值；然后，如果你的技能值大于等于这个市场的困难度，你就可以成功售卖糖果。初始时，每座市场的技能值都是 $0$。

由于这座城市十分繁忙，所以在接下来的 $Q$ 天中，每一天都会发生一次事件，用 $u_j$ 和 $x_j$ 来描述，表示第 $u_j$ 座市场的技能值增加了 $x_j$。

在这 $Q$ 天里，每一天 Sandu 都会带着 $0$ 技能值来到市场 $1$，然后选择一个市场 $k$。然后，他会沿着从 $1$ 到 $k$ 的路径访问路径上的每一座市场（包括 $1$ 和 $k$）并尝试售卖糖果。注意：无论 Sandu 是否售卖糖果成功，他都会一直向下访问，直到到达 $k$。

现在 Sandu 想请你求出，对于每一天，他最多可以在多少个市场卖出糖果。

## 说明/提示

**【数据范围】**

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$7$|对于 $1<i\le n$，有 $p_i=1$；$N,Q\le2000$|
|$2$|$8$|$N,Q\le2000,p_i=i-1$|
|$3$|$17$|$p_i=i-1$|
|$4$|$12$|$N,Q\le2000$|
|$5$|$21$|$u_j=1$|
|$6$|$24$|$N,Q\le10^5$|
|$7$|$11$|无|

对于 $100\%$ 的数据，$1\le N,Q\le5\times10^5,0 \le t_i\le10^9,1\le x_j\le10^9,1\le u_j\le N$。

## 样例 #1

### 输入

```
12 5
1 1 3 3 1 6 7 1 9 10 11
1 2 6 3 5 4 6 5 2 3 4 5
1 1
1 1
3 2
6 3
9 6```

### 输出

```
1
2
2
3
5```

## 样例 #2

### 输入

```
5 4
1 2 3 4
1 2 5 6 7
1 1
1 2
1 1
1 2
```

### 输出

```
1
2
2
4```

## 样例 #3

### 输入

```
5 5
1 1 1 1
1 2 3 4 5
4 4
2 2
5 5
1 1
3 3```

### 输出

```
1
1
1
2
2```

# 题解

## 作者：JoyLosingK (赞：3)

# 题意

维护一棵带点权的树，初始时每个点的权值 $w_i$ 为 $0$，支持以下操作：

- 子树加 $x$。
- 询问一条以 $1$ 号点开始的路径，使得路径上的 $a_i\le w_i$ 的点的数量最多。

# 题解
刚开始看到这道题时觉得很不可做。首先想到的是分块，对每个块维护排序后的块，区间加散块暴力重构。询问时，散块暴力，整块二分答案求解。时间复杂度为 $O((n+q)\sqrt n\log n)$，貌似只有 $51$ 分。

看到 $5\times 10^5$ 的 $n$，猜测是一只 $\log$。观察题目后发现一个细节之处，就是子树加上的数是正数！这意味着当某个点 $i$ 满足 $a_i\le w_i$ 后，它将永远符合条件。

于是我们考虑势能线段树，对于线段树每个节点维护最大值，先使每个点 $i$ 的 $w_i=-a_i$。在每次子树加操作结束后递归去找新的符合条件的点。

递归过程中，若当前区间的最大值小于 $0$，那么这个区间中一定没有符合条件的点，直接返回。

最后就是统计答案，发现每个符合条件的点对答案的贡献的部分显然是以它为根的子树，直接用线段树维护即可。
最终的答案显然就是整个答案序列中的最大值。

# 时间复杂度

由于每个点只会被更新（由不符合条件变为符合条件）一次，$n$ 个点就是 $O(n\log n)$ 的复杂度。其他普通的线段树操作也是 $O(n\log n)$ 的，所以总时间复杂度为 $O(n\log n)$ 。

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define rint register int
#define lb(i) (i&(-i))
const int N = 5e5 + 5;
int n, q, a[N], dfn[N], sz[N], rdfn[N], now;
vector<int> e[N];
char buf[83886000], *p1 = buf, *p2 = buf, ubuf[83886000], *u = ubuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,83886,stdin),p1==p2)?EOF:*p1++)
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
	return x * f;
}
struct tree1 {
	int l, r, mx, tg;
#define l1(z) t1[z].l
#define r1(z) t1[z].r
#define mx1(z) t1[z].mx
#define tg1(z) t1[z].tg
} t1[N << 2];
struct tree2 {
	int l, r, mx, tg;
#define l2(z) t2[z].l
#define r2(z) t2[z].r
#define mx2(z) t2[z].mx
#define tg2(z) t2[z].tg
} t2[N << 2];
inline void build1(int k, int l, int r) {
	l1(k) = l, r1(k) = r;
	if (l == r) return;
	int mid = l + r >> 1;
	build1(k << 1, l, mid), build1(k << 1 | 1, mid + 1, r);
}
inline void pushdown1(int k) {
	if (tg1(k)) {
		mx1(k << 1) += tg1(k), mx1(k << 1 | 1) += tg1(k),
	    tg1(k << 1) += tg1(k), tg1(k << 1 | 1) += tg1(k);
	}
	return (void)(tg1(k) = 0);
}
inline void Add1(int k, int x, int y, int v) {
	if (x <= l1(k) && r1(k) <= y) {
		mx1(k) += v, tg1(k) += v;
		return;
	}
	if (r1(k) < x || y < l1(k)) return;
	pushdown1(k), Add1(k << 1, x, y, v), Add1(k << 1 | 1, x, y, v);
	mx1(k) = max(mx1(k << 1), mx1(k << 1 | 1));
}
inline int Ans() {
	return mx1(1);
}
inline void build2(int k, int l, int r) {
	l2(k) = l, r2(k) = r;
	if (l == r) {
		mx2(k) = -a[rdfn[l]];
		return;
	}
	int mid = l + r >> 1;
	build2(k << 1, l, mid), build2(k << 1 | 1, mid + 1, r);
	mx2(k) = max(mx2(k << 1), mx2(k << 1 | 1));
}
inline void pushdown2(int k) {
	if (tg2(k)) {
		mx2(k << 1) += tg2(k), mx2(k << 1 | 1) += tg2(k),
	    tg2(k << 1) += tg2(k), tg2(k << 1 | 1) += tg2(k);
	}
	return (void)(tg2(k) = 0);
}
inline void Add2(int k, int x, int y, int v) {
	if (x <= l2(k) && r2(k) <= y) {
		mx2(k) += v, tg2(k) += v;
		return;
	}
	if (r2(k) < x || y < l2(k)) return;
	pushdown2(k), Add2(k << 1, x, y, v), Add2(k << 1 | 1, x, y, v);
	mx2(k) = max(mx2(k << 1), mx2(k << 1 | 1));
}
inline void find(int k) {
	if (mx2(k) < 0) return;
	if (l2(k) == r2(k)) {
		Add1(1, l2(k), l2(k) + sz[rdfn[l2(k)]] - 1, 1);
		return void(mx2(k) = -1e9);
	}
	pushdown2(k), find(k << 1), find(k << 1 | 1),
	mx2(k) = max(mx2(k << 1), mx2(k << 1 | 1));
}
inline void dfs(int u) {
	dfn[u] = ++now, rdfn[now] = u, sz[u] = 1;
	for (int v : e[u]) dfs(v), sz[u] += sz[v];
}
int main() {
	ios::sync_with_stdio(0);
	cout.tie(0);
	cin.tie(0);
	n = read(), q = read();
	for (int i = 2, x; i <= n; i++) x = read(), e[x].push_back(i);
	for (int i = 1; i <= n; i++) a[i] = read();
	dfs(1);
	build1(1, 1, n), build2(1, 1, n);
	for (int u, x; q--;) {
		u = read(), x = read();
		Add2(1, dfn[u], dfn[u] + sz[u] - 1, x), find(1);
		cout << Ans() << endl;
	}
	return 0;
}
```

感谢管理员的审核，也感谢读者们的阅读。求赞 qaq。

---

## 作者：Genius_Star (赞：2)

### 思路：

简单题，考虑势能，由于技能值只增不减，所以若现在能在这个地方卖出糖果，则以后肯定也可以。

故问题相当于：

- 每个点初始权值为 $w_u = 0$。

- 子树权值加。

- 显然一个点能卖出糖果当且仅当 $w_u \ge lim_u$；询问一条从根出发的路径中能卖出糖果的点的数量的最大值。

考虑线段树快速找到最新 $w_u \ge lim_u$ 的点，即初始权值为 $-lim_u$，维护区间最大值，支持区间加，若 $\ge 0$ 了则往下找；找到后赋值为 $-\inf$。

考虑若一个点 $u$ 能卖出糖果对答案的贡献，显然到 $u$ 子树内的点的答案都会增加一。

故维护两个线段树，一个维护势能找最新可以卖糖果的点，一个用来维护答案。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define ctz(x) __builtin_ctz(x)
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 5e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, q, u, x, cnt;
int fa[N], id[N], siz[N], dfn[N];
ll lim[N];
vector<int> E[N];
inline void dfs(int u){
	siz[u] = 1;
	dfn[u] = ++cnt;
	id[cnt] = u;
	for(auto v : E[u]){
		dfs(v);
		siz[u] += siz[v];
	}
}
namespace Seg{
	struct Node{
		int l, r;
		int Max, tag;
	}X[N << 2];
	inline void pushup(int k){
		X[k].Max = max(X[k << 1].Max, X[k << 1 | 1].Max);
	}
	inline void add(int k, int v){
		X[k].Max += v;
		X[k].tag += v;
	}
	inline void push_down(int k){
		if(X[k].tag){
			add(k << 1, X[k].tag);
			add(k << 1 | 1, X[k].tag);
			X[k].tag = 0;
		}
	}
	inline void build(int k, int l, int r){
		X[k].l = l, X[k].r = r;
		if(l == r)
		  return ;
		int mid = (l + r) >> 1;
		build(k << 1, l, mid);
		build(k << 1 | 1, mid + 1, r);
	}
	inline void update(int k, int l, int r, int v){
		if(X[k].l == l && r == X[k].r){
			add(k, v);
			return ;
		}
		push_down(k);
		int mid = (X[k].l + X[k].r) >> 1;
		if(r <= mid)
		  update(k << 1, l, r, v);
		else if(l > mid)
		  update(k << 1 | 1, l, r, v);
		else{
			update(k << 1, l, mid, v);
			update(k << 1 | 1, mid + 1, r, v); 
		}
		pushup(k);
	}
	inline int getmax(){
		return X[1].Max;
	}
}
inline void Add(int u, int v){
	Seg::update(1, dfn[u], dfn[u] + siz[u] - 1, v);
}
namespace Tree{
	struct Node{
		int l, r;
		ll Max, tag;
	}X[N << 2];
	inline void pushup(int k){
		X[k].Max = max(X[k << 1].Max, X[k << 1 | 1].Max);
	}
	inline void add(int k, int v){
		X[k].Max += v;
		X[k].tag += v;
	}
	inline void push_down(int k){
		if(X[k].tag){
			add(k << 1, X[k].tag);
			add(k << 1 | 1, X[k].tag);
			X[k].tag = 0;
		}
	}
	inline void build(int k, int l, int r){
		X[k].l = l, X[k].r = r;
		if(l == r){
			X[k].Max = -lim[id[l]];
			return ;
		}
		int mid = (l + r) >> 1;
		build(k << 1, l, mid);
		build(k << 1 | 1, mid + 1, r);
		pushup(k);
	}
	inline void update(int k, int l, int r, int v){
		if(l > r)
		  return ;
		if(X[k].l == l && r == X[k].r){
			add(k, v);
			return ;
		}
		push_down(k);
		int mid = (X[k].l + X[k].r) >> 1;
		if(r <= mid)
		  update(k << 1, l, r, v);
		else if(l > mid)
		  update(k << 1 | 1, l, r, v);
		else{
			update(k << 1, l, mid, v);
			update(k << 1 | 1, mid + 1, r, v); 
		}
		pushup(k);
	}
	inline void find(int k){
		if(X[k].Max < 0)
		  return ;
		if(X[k].l == X[k].r){
			Add(id[X[k].l], 1);
			X[k].Max = LONG_LONG_MIN;
			return ;
		}
		push_down(k);
		find(k << 1), find(k << 1 | 1);
		pushup(k);
	}
};
bool End;
int main(){
	n = read(), q = read();
	for(int i = 2; i <= n; ++i){
		fa[i] = read();
		E[fa[i]].push_back(i);
	}
	for(int i = 1; i <= n; ++i)
	  lim[i] = read();
	dfs(1);
	Seg::build(1, 1, n), Tree::build(1, 1, n);
	while(q--){
		u = read(), x = read();
		Tree::update(1, dfn[u], dfn[u] + siz[u] - 1, x);
		Tree::find(1);
		write(Seg::getmax());
		putchar('\n'); 
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：冷却心 (赞：1)

sto Genius_Star。题目看错导致想了一年 /tuu。

我们对每个点维护困难度和到这个点时技能值之差，即困难度与到根路径上技能值之和的差，注意到每次单点修改增量恒为正，所以问题变成支持子树**减法**，求出每个点到根的路径上小于等于 $0$ 的点个数的最大值。

因为只用支持减一个正数，所以一个数从非法变成合法点之后不会再非法，然后如果我们对每个点维护他到根上合法点的个数，那么一个点从非法变为合法的贡献就是子树加一。我们开一个线段树维护子树加一和求最大值，即答案。然后对于一个点非法到合法的维护我们用势能线段树随便做，维护 dfn 区间 $\min$，如果一个当前区间 $\min > k$ 说明当前操作在这个区间内的点都不会有贡献，于是直接打标记，否则说明这个区间内至少一个点会变为合法，那么继续递归直至到单点，我们把这个点更新为 $+\infin$ 表示已经做过贡献，然后到第一颗线段树上子树加即可。每个点至多被递归到单点一次，所以势能线段树复杂度 $O(n\log n)$，前面的子树加线段树复杂度同样 $O(n \log n)$，查询复杂度 $O(q)$ 加上前面的均摊复杂度，所以总时间复杂度 $O(n\log n+q)$。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 5e5 + 10;
int n, Q; vector<int> G[N];
LL W[N];

int dfn[N], dfncnt, inv[N], R[N];
void DFS(int u, int f) {
	dfn[u] = R[u] = ++ dfncnt; inv[dfncnt] = u;
	for (int v : G[u]) DFS(v, u), R[u] = R[v];
}

#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
namespace DS1 {
int tr[N << 2], tag[N << 2];
void f(int p, int k) { tag[p] += k; tr[p] += k; }
void pushdown(int p) { f(ls(p), tag[p]); f(rs(p), tag[p]); tag[p] = 0; }
void update(int p, int l, int r, int x, int y) {
	if (x > r || y < l) return ;
	if (x <= l && y >= r) { f(p, 1); return ; }
	int mid = (l + r) >> 1; pushdown(p);
	update(ls(p), l, mid, x, y); update(rs(p), mid + 1, r, x, y);
	tr[p] = max(tr[ls(p)], tr[rs(p)]); return ;
}
}

namespace DS2 {
LL tr[N << 2], tag[N << 2];
void f(int p, LL k) { tag[p] += k; tr[p] += k; }
void pushdown(int p) { f(ls(p), tag[p]); f(rs(p), tag[p]); tag[p] = 0; }
void build(int p, int l, int r) {
	if (l == r) { 
		tr[p] = W[inv[l]];
		if (!tr[p]) { tr[p] = 1e18; DS1::update(1, 1, n, l, R[inv[l]]); } 
		return ; 
	}
	int mid = (l + r) >> 1; 
	build(ls(p), l, mid); build(rs(p), mid + 1, r);
	tr[p] = min(tr[ls(p)], tr[rs(p)]);
}
void update(int p, int l, int r, int x, int y, LL k) {
	if (x > r || y < l) return ;
	if (x <= l && y >= r && tr[p] > k) { f(p, -k); return ; }
	if (l == r) {
		tr[p] = 1e18; DS1::update(1, 1, n, l, R[inv[l]]); return ;
	} int mid = (l + r) >> 1; pushdown(p);
	update(ls(p), l, mid, x, y, k); update(rs(p), mid + 1, r, x, y, k);
	tr[p] = min(tr[ls(p)], tr[rs(p)]); return ;
}
}

int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> Q;
	for (int i = 2, u; i <= n; i ++) cin >> u, G[u].push_back(i);
	for (int i = 1; i <= n; i ++) cin >> W[i];
	DFS(1, 0); DS2::build(1, 1, n);
	int x; LL y;
	while (Q --) {
		cin >> x >> y; 
		DS2::update(1, 1, n, dfn[x], R[x], y);
		cout << DS1::tr[1] << "\n";
	}
	return 0;
}
```

---

