# Jumbled Trees

## 题目描述

You are given an undirected connected graph with $ n $ vertices and $ m $ edges. Each edge has an associated counter, initially equal to $ 0 $ . In one operation, you can choose an arbitrary spanning tree and add any value $ v $ to all edges of this spanning tree.

Determine if it's possible to make every counter equal to its target value $ x_i $ modulo prime $ p $ , and provide a sequence of operations that achieves it.

## 样例 #1

### 输入

```
3 3 101
1 2 30
2 3 40
3 1 50```

### 输出

```
3
10 1 2
20 1 3
30 2 3```

## 样例 #2

### 输入

```
2 2 37
1 2 8
1 2 15```

### 输出

```
2
8 1
15 2```

## 样例 #3

### 输入

```
5 4 5
1 3 1
2 3 2
2 5 3
4 1 4```

### 输出

```
-1```

# 题解

## 作者：Para (赞：2)

操作数不超过 $2m$ 似乎是一个非常有用的提示。

每次要找一棵生成树进行操作，于是对原图建出一棵 $\text{dfs}$ 树，那么剩下的边呢？它们可以替换掉 $\text{dfs}$ 树上的边。

比如设一条非树边为 $x$，它可以替换掉 $y$，可以通过对替换前后的两棵生成树分别进行进行操作，等价的做到 $x$ 边 $+e$，$y$ 边 $-e$，其他边权值不变。

将可以互相替换的数再连边建立新图，会形成若干个连通块，将每一个连通块中抽出一棵生成树保留，图就变成了一个森林。会发现之前对边加减 $e$ 的操作是不改变边权总和的，唯一能改变边权总和的就只有对最开始的生成树进行操作，所以只需判断一下是否能操作最开始的生成树，使得每一个连通块中的和为它们最终需要达到的和，能满足就可以构造出一组解（每棵树里面从叶子往上满足每个点需求就行了），实现的精细一点可以做到 $m$ 次操作，时间复杂度 $O(nm)$。

（~~开始和与个数模意义下均为 $0$ 没判断被卡傻了~~）

可以顺便看一下 [P8156](https://www.luogu.com.cn/problem/P8156)，同样的套路。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
#define inf 1e9
#define pii pair <int, int>
int mod = 1e9 + 7;
inline int read () {
	int x = 0, f = 1;
	char ch = getchar ();
	while (ch < '0' || ch > '9') f = ((ch == '-') ? -1 : f), ch = getchar ();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar ();
	return x * f;
}
inline void write (int x) {
	if (x < 0) x = -x, putchar ('-');
	if (x >= 10) write (x / 10);
	putchar (x % 10 + '0');
}
inline int quickmod (int x, int y) {
	x %= mod;
	int Ans = 1;
	while (y) {
		if (y & 1) Ans = (Ans * x) % mod;
		x = (x * x) % mod;
		y >>= 1;
	}
	return Ans;
}
inline void Add(int &x, int y) {
	x += y;
	if(x >= mod) x -= mod;
}
inline void Dec(int &x, int y) {
	x -= y;
	if(x < 0) x += mod;
}
struct UnionSet {
	int fa[1005];
	inline void makeSet(int x) {
		for(int i = 1; i <= x; i++) fa[i] = i;
	}
	int findSet(int x) {
		if(x == fa[x]) return x;
		return fa[x] = findSet(fa[x]);
	}
	void unionSet(int x, int y) {
		x = findSet(x), y = findSet(y);
		if(x == y) return ;
		fa[x] = y; 
	}
}U;
int n, m;
struct Edge {
	int u, v, e;
}edge[1005];
struct st {
	int v, id;
	st() {}
	st(int A, int B) {
		v = A, id = B;
	}
};
vector <st> G[1005];
vector <int> V[1005];
int Fa[1005], dep[1005], val[1005], vis[1005];
vector <int> bas, P;
vector <vector <int> > Ans;
int visbas[1005];
void dfs(int x, int fa) {
	Fa[x] = fa, dep[x] = dep[fa] + 1;
	vis[x] = 1;
	for(auto y : G[x]) {
		if(vis[y.v]) continue;
		bas.push_back(y.id);
		visbas[y.id] = 1;
		val[y.v] = y.id;
		dfs(y.v, x); 
	}
}
int cnt;
inline void print(int x, int y, int e) {//x += e, y -= e;
	Dec(edge[x].e, e), Add(edge[y].e, e); 
	if(visbas[x]) {
		cnt = 0; 
		P[cnt++] = (-e % mod + mod) % mod;
		for(auto i : bas) if(i != x) P[cnt++] = i;
		P[cnt++] = y;
		Ans.push_back(P);
		
		cnt = 0;
		P[cnt++] = (e % mod + mod) % mod;
		for(auto i : bas) P[cnt++] = i;
		Ans.push_back(P);
	}
	else {
		cnt = 0;
		P[cnt++] = (e % mod + mod) % mod;
		for(auto i : bas) if(i != y) P[cnt++] = i;
		P[cnt++] = x;
		Ans.push_back(P);
		
		cnt = 0;
		P[cnt++] = (-e % mod + mod) % mod;
		for(auto i : bas) P[cnt++] = i;
		Ans.push_back(P);
	}
}

inline void add(int u, int v) {
	if(U.findSet(u) == U.findSet(v)) return ;
	V[u].push_back(v);
	V[v].push_back(u);
//	printf("[%lld %lld]\n", u, v);
	U.unionSet(u, v);
}
int s[1005], op[1005];
void dfs2(int x, int fa) {
	for(auto y : V[x]) {
		if(y == fa) continue;
		dfs2(y, x);
	}
	if(fa) print(x, fa, edge[x].e);
	else if(edge[x].e) {
		puts("-1");
		exit(0);
	}
}
signed main () {
//	freopen ("1.in", "r", stdin);
//	freopen (".out", "w", stdout);
	n = read(), m = read(), mod = read();
	P.resize(n);
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(), e = read();
		edge[i].u = u, edge[i].v = v, edge[i].e = e;
		G[u].push_back(st(v, i));
		G[v].push_back(st(u, i));
	}
	dfs(1, 0);
	U.makeSet(m);
	for(int i = 1; i <= m; i++) {
		if(visbas[i]) continue;
		int u = edge[i].u, v = edge[i].v;
		while(u != v) {
			if(dep[u] < dep[v]) swap(u, v);
			add(i, val[u]);
			u = Fa[u];
		}
	}
	memset(vis, 0, sizeof vis);
	for(int i = 1; i <= m; i++) {
		op[U.findSet(i)] += visbas[i];
		Add(s[U.findSet(i)], edge[i].e);
	}
	int nd = 0;
	for(int i = 1; i <= m; i++) if(!nd) nd = s[U.findSet(i)] * quickmod(op[U.findSet(i)], mod - 2) % mod;
	for(int i = 1; i <= m; i++) if(nd * op[U.findSet(i)] % mod != s[U.findSet(i)]) return printf("-1\n") & 0;

	cnt = 0;
	P[cnt++] = (nd % mod + mod) % mod;
	for(auto i : bas) P[cnt++] = i, Dec(edge[i].e, nd);
	Ans.push_back(P);
	
	for(int i = 1; i <= m; i++) if(U.findSet(i) == i) dfs2(i, 0); 
//	return 0;
	write((int)Ans.size()), putchar('\n');
	for(auto x : Ans) {
		for(auto y : x) write(y), putchar(' ');
		putchar('\n');
	}
	return 0;
}
/*
2 2 2
1 2 1
2 1 0
*/
```

---

## 作者：Alex_Wei (赞：2)

将生成树视为长度为 $m$ 的列向量，第 $i$ 个数表示第 $i$ 条边是否在生成树内。生成树数量很大，但我们只要 $m$ 棵线性无关的生成树。或者说，求出所有生成树的 “基生成树”。

这似乎很困难，我们猜一些结论：找出任意生成树 $T$，考虑将一条树边替换为一条非树边形成的生成树 $T'$。**所有 $T'$ 的列向量组 $B$ 和所有生成树的列向量组 $A$ 列等价**。

这个结论很离谱，我不太了解它的本质。

证明：$T' - T$ 得到一个恰有一个 $1$ 和 $-1$，其它位置均为 $0$ 的向量。它表示 **边的替换**。在两条边之间相连，表示它们可相互替换，则一条边可以替换为其连通块内任意边。

- 因为 $B$ 是 $A$ 的子集，所以 $B$ 能组合出的列向量，$A$ 同样能组合出。
- 考虑形成 $T'$ 和边的替换的过程，可以看出 **同简单环内的边可相互替换**，进一步推出 **同点双内的边可相互替换**。将原图点双缩点，则对于任意生成树 $U$，它相对于 $T$ 只改变了每个点双内部的生成树形态。这说明 $U$ 一定可以由 $T$ 替换得到，所以 $A$ 的每个列向量能被 $B$ 组合出，进而证明 $A$ 能组合出的列向量，$B$ 同样能组合出。

综上，$A, B$ 列等价。

这样，我们得到 $m ^ 2$ 个生成树，还不够优秀。但注意到若 $T' - T$ 的替换关系成环，删去环上任意一条边均保留所有替换关系。用并查集维护是否成环即可。具体地，对于每条非树边 $e_i$ 和其两端之间的所有树边 $e_j$，若 $(i, j)$ 在 “替换图” 上不连通，则将 $e_j$ 替换为 $e_i$ 加入 $B$，并在替换图上连接 $(i, j)$。

这样，我们得到至多 $m - 1$ 棵生成树。加上 $T$ 本身，共有不超过 $m$ 棵生成树。高斯消元的复杂度为 $\mathcal{O}(m ^ 3)$，使用取模优化后可以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using LL = __uint128_t;
struct FastMod {
  ull b, m;
  FastMod() {}
  FastMod(ull b): b(b), m((LL(1) << 64) / b) {}
  ull R(ull a) {
    ull q = ull((LL(a) * m) >> 64);
    ull r = a - q * b;
    return r >= b ? r - b : r;
  }
} F;

constexpr int N = 1e3 + 5;
int debug, y[N];
int n, m, p;
void add(int &x, int y) {
  x += y, x >= p && (x -= p);
}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = F.R(1ll * s * a);
    a = F.R(1ll * a * a), b >>= 1;
  }
  return s;
}
int inv(int x) {
  return ksm(x, p - 2);
}

int u[N], v[N], x[N], in[N];
struct dsu {
  int fa[N];
  void init(int n) {
    for(int i = 0; i <= n; i++) fa[i] = i;
  }
  int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
  }
  bool check(int u, int v) {
    return find(u) == find(v);
  }
  void merge(int u, int v) {
    fa[find(u)] = find(v);
  }
} f;

vector<pair<int, int>> e[N];
int fa[N], dep[N], fid[N];
void dfs(int id, int ff) {
  fa[id] = ff, dep[id] = dep[ff] + 1;
  for(auto _ : e[id]) {
    int it = _.first;
    if(it == ff) continue;
    fid[it] = _.second, dfs(it, id);
  }
}

int cur = 1, A[N][N], B[N][N], Main[N];
void addTree(int ad, int de) {
  cur++;
  for(int i = 1; i <= m; i++)
    if(i == ad || (i != de && in[i]))
      A[i][cur] = 1;
}
void Gauss() {
  int r = 1;
  for(int c = 1; c <= cur + 1 && r <= m; c++) {
    for(int _r = r + 1; _r <= m && !A[r][c]; _r++) {
      if(A[_r][c]) swap(A[r], A[_r]);
    }
    if(!A[r][c]) continue;
    if(c == cur + 1) puts("-1"), exit(0);
    int iv = inv(A[r][c]);
    for(int _c = c; _c <= cur + 1; _c++) A[r][_c] = F.R(1ll * A[r][_c] * iv);
    for(int _r = 1; _r <= m; _r++) {
      if(r == _r) continue;
      for(int _c = cur + 1; _c >= c; _c--)
        add(A[_r][_c], p - F.R(1ll * A[r][_c] * A[_r][c]));
    }
    Main[r] = c, r++;
  }
}

int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
    debug = 1;
  #endif
  cin >> n >> m >> p;
  F = FastMod(p);
  f.init(n);
  for(int i = 1; i <= m; i++) {
    cin >> u[i] >> v[i] >> x[i];
    if(!f.check(u[i], v[i])) {
      in[i] = A[i][1] = 1;
      e[u[i]].push_back({v[i], i});
      e[v[i]].push_back({u[i], i});
      f.merge(u[i], v[i]);
    }
  }
  dfs(1, 0);
  f.init(m);
  for(int i = 1; i <= m; i++) {
    if(in[i]) continue;
    vector<int> arr;
    int x = u[i], y = v[i];
    while(x != y) {
      if(dep[x] < dep[y]) swap(x, y);
      arr.push_back(fid[x]), x = fa[x];
    }
    int R = arr.back();
    addTree(i, R), arr.pop_back();
    for(int it : arr) {
      if(f.check(it, R)) continue;
      f.merge(it, R), addTree(i, it);
    }
  }
  for(int i = 1; i <= m; i++) A[i][cur + 1] = x[i];
  memcpy(B, A, sizeof(B));
  Gauss();
  cout << cur << "\n";
  for(int i = 1; i <= cur; i++) {
    int v = 0;
    for(int j = 1; j <= cur; j++) {
      if(Main[j] == i) v = A[j][cur + 1];
    }
    cout << v << " ";
    for(int j = 1; j <= m; j++)
      if(B[j][i]) {
        cout << j << " ";
        add(y[j], v);
      }
    cout << "\n";
  }
  for(int i = 1; i <= m; i++) assert(x[i] == y[i]);
  if(debug) {
    cout << "compare: \n";
    for(int i = 1; i <= m; i++) cout << i << " " << x[i] << " " << y[i] << "\n";
  }
  return 0;
}
/*
g++ J.cpp -o J -std=c++14 -O2 -DALEX_WEI
*/
```

实际上，从替换关系的角度考虑，我们可以对列使用主元法，即 $I_1x_1 + I_2x_2 = J$ 写成 $I_1(x_1 + x_2) + (I_2 - I_1) x_2$，做到 $\mathcal{O}(m)$ 求解方程。但构造方案使得复杂度下界为 $\mathcal{O}(nm)$。

---

## 作者：Tony2 (赞：1)

考虑先在原图上 dfs 出一棵生成树，这样会剩下一些非树边，并且都是返祖边。

能够发现这张图的任意一个生成树都可以通过 dfs 出来的树调整得到，调整有：

1. 树边换成非树边
2. 非树边换成另一个非树边

其中因为第二种操作需要两个非树边包含，所以最终可以写成第一种操作。

第一种操作可以写成对一个树边权值 $-e$，对于一个非树边权值 $+e$。

分析到这里可以利用这个操作开始贪心。考虑目标是把所有的边的权值清空，而对原来 dfs 树的操作的权值并不确定，可以设为未知数 $x$。

因为考虑贪心，对于每个树边找到包含它的最深的非树边。最深指的是非树边顶点的深度最深。而对于每个非树边，接收完树边的权值后把自己的权值加到顶点往下的那条边上。显然这种贪心是最优的。

当一条树边没找到包含自己的非树边时，就进行判定，解出 $x$ 或者报告无解（$x$ 和之前的不同或 $kx+b=0$ 中 $k=0,b\neq0$）。

具体的贪心过程为：dfs 向上回溯过程中先把到顶的非树边的权值加到树边上，删掉这些非树边，再把树边的权值加到最深非树边 或 判定解。

输出只要把上文的第一种操作写成对应的（一条树边被替换成一条非树边的）生成树即可。

```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N = 1005;
int n, m, mod;
int X = -1, c;
int log2n, f[N][25];
bool vise[N];
int qpow(int x, int y){
	int res = 1;
	while (y){
		if (y & 1) res = 1ll * res * x % mod;
		x = 1ll * x * x % mod;
		y >>= 1;
	}
	return res;
}
struct node{
	int x, y;
	node() : x(0), y(0) {}
	node(int x, int y) : x(x), y(y) {}
	friend node operator + (const node &a, const node &b){return node((a.x + b.x) % mod, (a.y + b.y) % mod);}
	node& operator += (const node &a){
		x = (x + a.x) % mod;
		y = (y + a.y) % mod;
		return *this;
	}
}w[N];
bool vis[N];
int de[N];
int bot[N], top[N];
vector<pair<int, int>> e1[N], e2[N];
vector<int> up[N], dw[N];
vector<pair<pair<int, int>, node>> tr;
int kfa(int u, int k){
	for (int i = 0; k; i++, k >>= 1)
		if (k & 1)
			u = f[u][i];
	return u;
}
void dfs1(int u, int fae){
	vis[u] = 1;
	for (int i = 1; i <= log2n; i++) f[u][i] = f[f[u][i - 1]][i - 1];
	for (auto [v, id] : e1[u])
		if (id != fae){
			if (vis[v]){
				if (de[v] < de[u]){
					up[u].push_back(id);
					bot[id] = v;
					top[id] = u;
				}else dw[kfa(v, de[v] - de[u] - 1)].push_back(id);
			}else{
				de[v] = de[u] + 1;
				e2[u].emplace_back(v, id);
				f[v][0] = u;
				vise[id] = 1;
				dfs1(v, id);
			}
		}
}
struct cmp{
	bool operator () (const int &x, const int &y) const{
		if (de[top[x]] != de[top[y]]) return de[top[x]] > de[top[y]];
		else return x > y;
	}
};
set<int, cmp> st[N];
void check(node nd){
	if (!nd.x){
		if (nd.y){
			cout << -1;
			exit(0);
		}
	}else{
		int x = (1ll * -nd.y * qpow(nd.x, mod - 2) % mod + mod) % mod;
		if (X == -1) X = x;
		else if (X != x){
			cout << -1;
			exit(0);
		}
	}
}
void dfs2(int u){
	for (auto [v, id] : e2[u]){
		dfs2(v);
		for (int id2 : up[v])
			st[v].insert(id2);
		for (int id2 : dw[v]){
			w[id] += w[id2];
			tr.push_back({{id2, id}, w[id2]});
			w[id2] = node(0, 0);
			st[v].erase(id2);
		}
		if (st[v].empty()) check(node(-1, 0) + w[id]);
		else{
			w[*st[v].begin()] += w[id] + node(-1, 0);
			tr.push_back({{id, *st[v].begin()}, w[id] + node(-1, 0)});
			w[id] = node(1, 0);
		}
		if (st[u].size() < st[v].size())
			swap(st[u], st[v]);
		for (int w : st[v]) st[u].insert(w);
		st[v].clear();
	}
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	cin >> n >> m >> mod;
	log2n = log2(n);
	for (int i = 1; i <= m; i++){
		int u, v;
		cin >> u >> v >> w[i].y;
		e1[u].emplace_back(v, i);
		e1[v].emplace_back(u, i);
	}
	dfs1(1, 0);
	dfs2(1);
	if (X == -1) X = 0;
	c = X;
	cout << tr.size() + 1 << endl;
	for (auto [p, nd] : tr){
		if (!vise[p.first]) swap(p.first, p.second);
		else{
			nd.x *= -1;
			nd.y *= -1;
		}
		int Y = ((1ll * nd.x * X + nd.y) % mod + mod) % mod;
		c = (c - Y) % mod;
		cout << Y << ' ';
		vise[p.first] ^= 1, vise[p.second] ^= 1;
		for (int i = 1; i <= m; i++)
			if (vise[i])
				cout << i << ' ';
		cout << endl;
		vise[p.first] ^= 1, vise[p.second] ^= 1;
	}
	c = (c + mod) % mod;
	cout << c << ' ';
	for (int i = 1; i <= m; i++)
		if (vise[i])
			cout << i << ' ';
	cout << endl;
//	cerr << "Yes" << endl;
	return 0;
}
```

附赠一个 checker：

```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N = 1005;
int n, m, mod;
int U[N], V[N], W[N];
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	fstream is1("in.txt", ios::in);
	is1 >> n >> m >> mod;
	for (int i = 1; i <= m; i++)
		is1 >> U[i] >> V[i] >> W[i];
	fstream is2("out.txt", ios::in);
	int k;
	is2 >> k;
	while (k--){
		int x;
		is2 >> x;
		for (int i = 1; i < n; i++){
			int e;
			is2 >> e;
			W[e] = (W[e] - x + mod) % mod;
		}
	}
	if (count(W + 1, W + 1 + m, 0) < m){
		cout << "?" << endl;
		cout << '\a';
		system("pause");
	}
	return 0;
}
```

---

