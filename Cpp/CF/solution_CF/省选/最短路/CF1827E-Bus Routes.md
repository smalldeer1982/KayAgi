# Bus Routes

## 题目描述

There is a country consisting of $ n $ cities and $ n - 1 $ bidirectional roads connecting them such that we can travel between any two cities using these roads. In other words, these cities and roads form a tree.

There are $ m $ bus routes connecting the cities together. A bus route between city $ x $ and city $ y $ allows you to travel between any two cities in the simple path between $ x $ and $ y $ with this route.

Determine if for every pair of cities $ u $ and $ v $ , you can travel from $ u $ to $ v $ using at most two bus routes.

## 说明/提示

Here are the graphs of test case $ 1 $ , $ 2 $ , and $ 4 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827E/636b5045dbd1d95c74fcfe21de52ce3103ecff1f.png) Sample 1  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827E/5e6bc53eeaf1c05a72aa8adb625cb08699ecaf80.png) Sample 2  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827E/a888d70cad2c6923d39db1e4ae24fc5352ba8193.png) Sample 4

## 样例 #1

### 输入

```
4
5 2
1 2
2 3
3 4
2 5
1 4
5 2
5 1
1 2
2 3
3 4
2 5
1 5
2 0
1 2
6 3
1 2
2 3
3 4
4 5
5 6
1 3
2 5
4 6```

### 输出

```
YES
NO
1 3
NO
1 2
NO
1 6```

# 题解

## 作者：ix35 (赞：32)

随便定一个根 $r$。

考虑一个叶子 $l$，令 $anc(l)$ 表示 $l$ 通过一条链能到达的最浅祖先。如果存在两个 $anc(l_1),anc(l_2)$ 不是祖先后代关系，那么 $l_1,l_2$ 就不能通过两条链连通，答案是 `NO`。

否则，我们只需要保留一个最深的 $anc(l)$，设为 $v$。如果存在一个点 $u$，一步到不了 $v$，那么答案就是 `NO`，否则答案就是 `YES`，有一个偷懒的办法就是直接以 $v$ 为根再求一次 $anc$，所有点的 $anc$ 都是 $v$ 的话就是 `YES`。

这导出一个简洁的 $O(n\log n)$ 做法。我们没有用到**点分治、树剖、虚树**等数据结构技巧，我们需要的最高级的技术是**求两个点的 LCA**。

---

## 作者：chlchl (赞：7)

这道题放在 E 是比较坑的，因为搞完了 C、D 之后人已经不太行了，很多人本来能想动的也已经想不动了。

本篇题解与 @ix35 大佬的思路一致，但是更加详细，且加上了（可读性较强的）代码和实现中的一些细节问题。

## Solution
无根树，先随便选定一个点为根。

接着，我们定义：若 $u$ 能够通过不超过两条路线到达 $v$，则称 $u$ 能到达 $v$。

那么，对于不能到达的两个点 $(x,y)$，若它们不是叶子节点，那么把它们换成其子树中的叶子节点，必定也不能到达（我们称为“叶节点原理”）。

并且，对于一条线路，如果一个端点 $p$ 能到达某个点 $q$，那么其线路上任何一个点都能到达 $q$。

所以，我们只需要考虑所有叶子节点能到达的情况，并且只需要考虑路线端点上的点的到达情况，而不需要考虑其他点。

对于每个叶子节点 $u$，我们求出其通过一条线路能到达的深度最小的祖先 $low_u$，这个可以一次 dfs + LCA 解决，时间复杂度 $O(n\log n)$。

显然如果 $u$ 有线路，其必定是线路的端点。

接着，如果有两个点 $u,v$，它们的 $low$ 不是祖先后代关系，那么 $u,v$ 必定不可能通过到达。

因为叶节点的线路必定是往祖先方向走的，如果不是祖先关系，不可能有任何一条路径覆盖到，否则可能有线路（比如 $u$ 走上来的时候经过的线路）可以到达另外一点。

接着，我们保留一个深度最深的 $low$（记为 $rt$），依据还是最上面的“叶节点原理”。

以它为根，则所有点通过一条线路之后都有可能到达 $rt$。再对叶子节点求一次 $low$，如果所有叶子节点的 $low$ 都是 $v$，就有解，否则无解。

只有这样，你才能保证，上面第一次求得的所有 $low$ 都能一步到达 $rt$，这样所有原叶子节点才能够两步到达，整个问题才得以解决。

思维难度还是有的，但是我觉得没有前几道题这么阴间。

## Code
写起来不能说是依托答辩，但是直接写还是挺乱的。

注意几个点：
- 当第一次判得两个点 $low_u,low_v$ 不是祖先后代关系时，你应该输出的是 $u,v$。
- 当第二次判得 $low'_u\ne rt$ 时，你应该输出的是 $u$ 和 $low_v=rt$ 的那个 $v$。
- 如果你提交上去 TLE，可以交多几次，会有测评机波动。
- 实现建议：因为无解的时候要跳出，所以建议把主代码另开函数写，不要写在主函数的多测里，代码会简洁一些。

前两个点不注意的话你会 WA on #4。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
int T, n, m, low[N];
int dep[N], f[N][21];
vector<int> g[N], route[N];

void dfs(int u, int fa){
	f[u][0] = fa;
	for(int i=1;i<=20;i++)
		f[u][i] = f[f[u][i - 1]][i - 1];
	for(int v: g[u]){
		if(v == fa)
			continue;
		dep[v] = dep[u] + 1;
		dfs(v, u); 
	}
}

int LCA(int u, int v){
	if(dep[u] < dep[v])
		swap(u, v);
	for(int i=20;i>=0;i--)
		if(dep[f[u][i]] >= dep[v])
			u = f[u][i];
	if(v == u)
		return u;
	for(int i=20;i>=0;i--)
		if(f[u][i] != f[v][i])
			u = f[u][i], v = f[v][i];
	return f[u][0];
}

bool cmp(int a, int b){
	return dep[low[a]] < dep[low[b]];
}

void solve(){
	for(int i=1;i<=n;i++)
		g[i].clear(), route[i].clear();
	scanf("%d%d", &n, &m);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d", &u, &v);
		route[u].push_back(v);
		route[v].push_back(u);
	}
	dfs(1, 1);
	vector<int> zx;
	for(int u=1;u<=n;u++){
		low[u] = u;
		if(g[u].size() == 1){
			zx.push_back(u);
			for(int v: route[u]){
				int uu = LCA(u, v);
				if(dep[uu] < dep[low[u]])
					low[u] = uu;
			}
		}
	}
	sort(zx.begin(), zx.end(), cmp);
	for(int i=0;i<zx.size()-1;i++)
		if(LCA(low[zx[i]], low[zx[i + 1]]) != low[zx[i]])
			return printf("NO\n%d %d\n", zx[i], zx[i + 1]), void(0);
	int rt = low[zx.back()];
	dep[rt] = 0;
	dfs(rt, rt);
	for(int u: zx){
		int z = u;
		for(int v: route[u]){
			int uu = LCA(u, v);
			if(dep[uu] < dep[z])
				z = uu;
		}
		if(z != rt)
			return printf("NO\n%d %d\n", u, zx.back()), void(0);
	}
	printf("YES\n");
}

int main(){
	scanf("%d", &T);
	while(T--)
		solve();
	return 0;
}
```



---

## 作者：Alex_Wei (赞：3)

### [CF1827E Bus Routes](https://www.luogu.com.cn/problem/CF1827E)

所有点两两可达当且仅当所有叶子两两可达，而两个叶子可达当且仅当以 $T_x\cup T_y \neq \varnothing$，其中 $T_x$ 表示以 $x$ 为一端的所有路径的并，即 $x$ 和以 $x$ 为一端的路径的所有另一端形成的虚树。

设 $S_x$ 表示 $x$ 和以 $x$ 为一端的路径的所有另一端形成的点集，则相当于查询是否存在一条边，使得 $S_x$ 和 $S_y$ 全部分别在边的两侧。

设 $c_{i, j}$ 表示以 $i$ 为根的子树内有多少个属于 $S_j$ 的点，可以 dsu on tree 统计，同时维护所有 $c_{i, j} = 0$ 和 $c_{i, j} = |S_j|$ 的 $j$ 的集合即可。如果用 set 维护，则时间复杂度 $\mathcal{O}(n\log ^ 2 n)$，空间复杂度线性，会 TLE。因为要求加元素删元素查询任意一个元素，用 vector + 懒惰删除维护，时空复杂度均为 $\mathcal{O}(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ull = unsigned long long;

constexpr int mod = 998244353;
void addt(int &x, int y) {x += y, x >= mod && (x -= mod);}
int add(int x, int y) {return x += y, x >= mod && (x -= mod), x;}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

bool Mbe;
constexpr int N = 5e5 + 5;
constexpr int K = N << 5;

int n, m, cnt[N];
bool leaf[N];
vector<int> e[N], f[N];

int dn, dfn[N], rev[N], sz[N], son[N];
void dfs1(int id, int ff) {
  son[id] = 0;
  sz[id] = 1;
  rev[dfn[id] = ++dn] = id;
  for(int it : e[id]) {
    if(it == ff) continue;
    dfs1(it, id), sz[id] += sz[it];
    if(sz[son[id]] < sz[it]) son[id] = it;
  }
}

int x, y, buc[N], de[N], df[N];
int E, ept[K], F, ful[K];
void ad(int x, int v) {
  for(int it : f[x]) {
    if(!leaf[it]) continue;
    if(buc[it] == 0) de[it]++;
    if(buc[it] == cnt[it]) df[it]++;
    buc[it] += v;
    if(buc[it] == 0) ept[++E] = it;
    if(buc[it] == cnt[it]) ful[++F] = it;
  }
}
  
void clear(int x, int v) {
  int l = dfn[x], r = l + sz[x] - 1;
  for(int p = l; p <= r; p++) ad(rev[p], v);
}
void dfs(int id, int ff) {
  for(int it : e[id]) {
    if(it == ff || it == son[id]) continue;
    dfs(it, id), clear(it, -1);
  }
  if(son[id]) dfs(son[id], id);
  ad(id, 1);
  for(int it : e[id]) {
    if(it == ff || it == son[id]) continue;
    clear(it, 1);
  }
  while(E && de[ept[E]]) de[ept[E--]]--;
  while(F && df[ful[F]]) df[ful[F--]]--;
  if(E && F) x = ept[E], y = ful[F];
}

void solve() {
  cin >> n >> m;
  for(int i = 1; i <= n; i++) {
    e[i].clear();
    f[i].clear();
    cnt[i] = buc[i] = de[i] = df[i] = 0;
  }
  for(int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  dn = 0, dfs1(1, 0);
  for(int i = 1; i <= n; i++) {
    leaf[i] = e[i].size() == 1;
  }
  for(int i = 1; i <= m; i++) {
    int x, y;
    cin >> x >> y;
    cnt[x]++, cnt[y]++;
    if(leaf[x]) f[y].push_back(x);
    if(leaf[y]) f[x].push_back(y);
  }
  for(int i = 1; i <= n; i++) {
    if(!leaf[i] || cnt[i]) continue;
    cout << "NO\n";
    cout << i << " " << 1 + (i == 1) << "\n";
    return;
  }
  E = F = 0;
  for(int i = 1; i <= n; i++) {
    if(!leaf[i]) continue;
    cnt[i]++, f[i].push_back(i);
    ept[++E] = i;
  }
  x = y = -1, dfs(1, 0);
  if(x == -1) cout << "YES\n";
  else cout << "NO\n" << x << " " << y << "\n";
}

bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  while(T--) solve();
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

---

## 作者：Leasier (赞：2)

倍增数组没清空调半天。哈哈哈。

------------

考虑把题目要求改成“对于任意两个**叶子**是否能通过不超过两条路径到达”。不难发现这样存在性不变。

如果两个叶子 $u, v$ 没有被一条路径直接连接，那么设 $f_i$ 表示从 $i$ 向上通过一条路径可以到达的最高点，则当 $f_u, f_v$ 互不为祖先后代关系，$u, v$ 必然互相不可只通过两条路径互相到达。

但很遗憾，这个条件只是必要而非充分的。但注意到此时所有叶子的 $f_i$ 分布在一条链上，如果每个叶子都能只通过一条路径到达最深的 $f_u$，那么原条件就被满足了。不难发现这个条件是充要的。

于是我们把这个 $r = f_u$ 拿出来当根再求一遍 $f$，若 $\forall i \in \text{leaf}, f_i = r$ 则符合条件，否则不符合。

倍增 LCA 即可。时间复杂度为 $O(\sum n \log n)$。

代码：
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt;
int head[500007], deg[500007], _log2[500007], x[500007], y[500007], fa[500007][27], in[500007], depth[500007], out[500007], low[500007], bucket[500007];
bool leaf[500007];
Edge edge[1000007];

inline void init1(int n){
	cnt = 0;
	for (register int i = 1; i <= n; i++){
		head[i] = deg[i] = 0;
	}
	for (register int i = 2; i <= n; i++){
		_log2[i] = _log2[i / 2] + 1;
	}
}

inline void init2(int n){
	int m = _log2[n];
	for (register int i = 1; i <= n; i++){
		for (register int j = 0; j <= m; j++){
			fa[i][j] = 0;
		}
	}
	for (register int i = 1; i <= n; i++){
		if (leaf[i]) low[i] = i;
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs(int u, int father, int &id){
	int t;
	in[u] = ++id;
	depth[u] = depth[father] + 1;
	t = _log2[depth[u]];
	fa[u][0] = father;
	for (register int i = 1; i <= t; i++){
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != father) dfs(x, u, id);
	}
	out[u] = id;
}

inline int lca(int u, int v){
	if (depth[u] < depth[v]) swap(u, v);
	while (depth[u] > depth[v]) u = fa[u][_log2[depth[u] - depth[v]]];
	if (u == v) return u;
	for (register int i = _log2[depth[u]]; i >= 0; i--){
		if (fa[u][i] != fa[v][i]){
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return fa[u][0];
}

inline int mymin(int a, int b){
	return depth[a] < depth[b] ? a : b;
}

inline void solve(int root, int n, int m){
	int id = 0;
	init2(n);
	dfs(root, 0, id);
	for (register int i = 1; i <= m; i++){
		int cur_lca = lca(x[i], y[i]);
		if (leaf[x[i]]) low[x[i]] = mymin(low[x[i]], cur_lca);
		if (leaf[y[i]]) low[y[i]] = mymin(low[y[i]], cur_lca);
	}
}

inline bool check(int u, int v){
	return in[u] <= in[v] && in[v] <= out[u];
}

int main(){
	int t = read();
	for (register int i = 1; i <= t; i++){
		int n = read(), m = read(), up = 0, gen_up, cnt = 0;
		bool flag = true;
		init1(n);
		for (register int j = 1; j < n; j++){
			int u = read(), v = read();
			deg[u]++;
			deg[v]++;
			add_edge(u, v);
			add_edge(v, u);
		}
		for (register int j = 1; j <= n; j++){
			leaf[j] = deg[j] == 1;
		}
		for (register int j = 1; j <= m; j++){
			x[j] = read();
			y[j] = read();
		}
		solve(1, n, m);
		for (register int j = 1; j <= n; j++){
			if (leaf[j]){
				bucket[++cnt] = j;
				if (up == 0 || depth[up] > depth[low[j]]){
					up = low[j];
					gen_up = j;
				}
			}
		}
		for (register int j = 1; j <= cnt; j++){
			if (!check(up, low[bucket[j]])){
				flag = false;
				cout << "NO" << endl;
				cout << gen_up << " " << bucket[j] << endl;
				break;
			}
		}
		if (!flag) continue;
		int root = 0, gen_root;
		for (register int j = 1; j <= cnt; j++){
			if (root == 0 || depth[root] < depth[low[bucket[j]]]){
				root = low[bucket[j]];
				gen_root = bucket[j];
			}
		}
		solve(root, n, m);
		for (register int j = 1; j <= n; j++){
			if (leaf[j] && low[j] != root){
				flag = false;
				cout << "NO" << endl;
				cout << gen_root << " " << j << endl;
				break;
			}
		}
		if (flag) cout << "YES" << endl;
	}
	return 0;
}
```

---

## 作者：_⁢　 (赞：2)

若 $u,v$ 不可达，则将 $u$ 向 $u\to v$ 相反方向移动后仍不可达。

若叶节点 $u,v$ 可达，则满足 $(u',v')\subseteq (u,v)$ 的 $u',v'$ 仍可达。

因此，只需判定叶节点是否两两可达，也只需考虑一端点为叶节点的 route。

**解法 1**：

考虑点分治。

设当前分治中心为 $r$，叶节点 $u$ 经过一个 route 能到达的最浅节点为 $f_u$。

至多有一个 $f_u\ne r$，否则这些 $u$ 之间两两不可达（考虑 $u$ 可达的点一定在 $f_u$ 子树内）。

否则对于叶节点 $v\ne u$，这些 $v$ 之间两两可达（以 $r$ 为中转点）。

只需判断是否所有叶节点 $v$ 都可达 $u$ 即可，可以枚举端点为 $v$ 的 route。

使用 $\mathcal{O}(n\log n)-\mathcal{O}(1)$ LCA，时间复杂度 $\mathcal{O}(n\log n)$。

**解法 2**：

考虑优化 **解法 1**。

以任意节点 $r$ 为根，设叶节点 $u$ 经过一个 route 能到达的最浅节点为 $f_u$（同 **解法 1**）。

若叶节点 $u,v$ 满足 $f_u,f_v$ 不为祖孙关系，则 $u,v$ 不可达（考虑 $u$ 可达的点一定在 $f_u$ 子树内）。

否则 $f_u$ 的虚树形成一条链，因此可以直接 dfs 一遍判断。

取 $f_u$ 最深的 $u$，若所有叶节点 $v$ 都可达 $u$，则这些 $v$ 之间两两可达（考虑路径交点）。

只需判断是否所有叶节点 $v$ 都可达 $u$ 即可，以 $r'=f_u$ 为根重新求一遍 $f'$，若 $\forall u,f'_u=r'$ 则合法。

使用离线 $\mathcal{O}(n)$ LCA，时间复杂度 $\mathcal{O}(n)$。

[提交记录](https://codeforces.com/contest/1827/submission/210845424)。


---

## 作者：tzc_wk (赞：1)

一道比较诈骗的题，放在现场最大的挑战在于做完 B2 C D 这三道不算太签的题以后还有时间开这个题。

首先特判 $n=2$。以任意一个不是叶子的点为根。那么一棵树合法，当且仅当其中所有叶子都能在 $2$ 步内互相到达，因为如果一对不能在 $2$ 步内互相到达的点 $(u,v)$ 中存在至少一个不是叶子，那把那个不是叶子的点换成其子树内任意一个叶子，这两个点肯定也不能在 $2$ 步内互相到达。

考虑对每个叶子求出其在一步内最浅能走到的点 $p_i$，那么一个性质是对于一棵合法的树，所有叶子的 $p$ 互为祖先后代关系，如果存在两个叶子的 $p$ 不是祖先后代关系那这两个点一定不合法。特判掉这种情况之后，我们发现，我们其实只用 check 那个 $p_i$ 最深的叶子是否能在 $2$ 步内到达其他所有叶子即可。假设这个叶子为 $x$，那么如果存在一个 $p$ 更浅的叶子 $y$ 不能在 $2$ 步内到达其他叶子，但是 $x$ 可以，那么假设 $y$ 是所有这样的叶子中 $p$ 最深的，并且假设 $y$ 不能到达另一个叶子 $z$，那么容易知道 $z$ 不在 $p_y$ 子树中，因为 $p_y$ 的深度比 $p_z$ 大，并且叶子的 $p$ 之间两两成祖先后代关系。也就是说 $z$ 只可能在子树外，并且任意一条从 $z$ 出发的线路都不经过 $p_y$ 子树内的点，而显然 $p_x$ 在 $p_y$ 子树内，所以 $x$ 也不可达，矛盾。

时间复杂度 $O(n\log n)$。

```cpp
const int MAXN=5e5;
const int LOG_N=18;
const int INF=0x3f3f3f3f;
int n,m,hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],ec,deg[MAXN+5],R;
struct pth{int u,v;}p[MAXN+5];
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int fa[MAXN+5][LOG_N+2],dep[MAXN+5];
void dfs(int x,int f){
	fa[x][0]=f;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f)continue;
		dep[y]=dep[x]+1;dfs(y,x);
	}
}
pii mn[MAXN+5];vector<int>vec[MAXN+5];
int getlca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=LOG_N;~i;i--)if(dep[x]-(1<<i)>=dep[y])x=fa[x][i];
	if(x==y)return x;
	for(int i=LOG_N;~i;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
bool check_anc(int x,int y){int lc=getlca(x,y);return (x==lc||y==lc);}
void clear(){for(int i=1;i<=n;i++)hd[i]=deg[i]=dep[i]=0,mn[i]=mp(INF,0),vec[i].clear();ec=R=0;}
void solve(){
	scanf("%d%d",&n,&m);clear();
	for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),adde(u,v),adde(v,u),deg[u]++,deg[v]++;
	for(int i=1;i<=m;i++)scanf("%d%d",&p[i].u,&p[i].v);
	if(n==2){
		for(int i=1;i<=m;i++)if(p[i].u!=p[i].v)return puts("YES"),void();
		puts("NO\n1 2");return;
	}
	for(int i=1;i<=n;i++)if(deg[i]>=2)R=i;dfs(R,0);
	for(int i=1;i<=LOG_N;i++)for(int j=1;j<=n;j++)fa[j][i]=fa[fa[j][i-1]][i-1];
	for(int i=1;i<=m;i++)vec[p[i].u].pb(p[i].v),vec[p[i].v].pb(p[i].u);
	vector<int>lf;
	for(int i=1;i<=n;i++)if(deg[i]==1){
		if(vec[i].empty())return printf("NO\n%d %d\n",i,R),void();
		else{int lc;for(int x:vec[i])lc=getlca(x,i),chkmin(mn[i],mp(dep[lc],lc));}
//		printf("! %d %d %d\n",i,mn[i].fi,mn[i].se);
		lf.pb(i);
	}
	sort(lf.begin(),lf.end(),[&](int x,int y){return mn[x]<mn[y];});
	for(int i=1;i<lf.size();i++)if(!check_anc(mn[lf[i-1]].se,mn[lf[i]].se))
		return printf("NO\n%d %d\n",lf[i-1],lf[i]),void();
	int x=lf.back();
	for(int i=0;i+1<lf.size();i++){
		bool flg=0;
		for(int y:vec[lf[i]])flg|=(getlca(lf[i],mn[x].se)==mn[x].se||getlca(y,mn[x].se)==mn[x].se);
		if(!flg)return printf("NO\n%d %d\n",lf[i],x),void();
	}puts("YES");
}
int main(){
	int qu;scanf("%d",&qu);while(qu--)solve();
	return 0;
}
/*
1
7 3
7 1
7 2
2 3
3 4
2 5
5 6
1 7
4 2
6 2
*/
```



---

## 作者：luogubot (赞：1)

给定一棵 $n$ 个点的树以及 $m$ 条路线，一条 $x$ 到 $y$ 的路线允许树上 $x$ 到 $y$ 路径上的点互达，判断树上任意两点是否能通过至多两条路线互达，如果不能，找到一组不符合要求的点对。

$\sum n,\sum m\leq 5\times 10^5$，2.5s。

叶子的限制强于其它点，所以只用考虑叶子是否满足条件。这么做可以让每条路线的限制可以只在端点处考虑。

对于叶子 $u$，找出以它为端点的所有路线，这些路径对应点集的并就是 $u$ 能一步到达的点，记为 $S_u$，这是一个包含 $u$ 的连通块。那么问题转化为判断任意叶子 $u,v$，是否有 $S_u\cap S_v\neq \varnothing$。

注意到连通块的交仍然是连通块，而连通块满足点数等于边数加一，那么可以用点减边容斥得到每个 $S_u$ 与多少个 $S_v$ 有交。现在需要处理的问题只有连通块加以及连通块求和。

注意到虚树结构（点集中任意两点的 LCA 也在点集中）满足其在原树上的 dfs 序即为一种欧拉序，也就是每条边恰好被经过两次，于是把这些点拉出来执行链加链求和就可以做到 $O(n\log^2n)$，但是实际上可以一起树上差分，复杂度瓶颈只有 LCA，可以做到 $O(n\log n)$。

最后处理找点对的问题，只需要找到一个不和所有叶子连通块有交的点，对每个叶子判和它是否有重合点，也可以树上差分。[Submission](https://codeforc.es/contest/1827/submission/206061492)

---

## 作者：Kubic (赞：1)

设 $u$ 能够通过不超过一条路径到达的点集为 $S_u$。

显然满足条件当且仅当 $\forall u,v,S_u\bigcap S_v\neq\varnothing$。

因为 $S_u$ 是若干条经过 $u$ 的路径的并，所以它是树上的一个连通块。

因此条件等价于 $\bigcap S_u\neq\varnothing$。

进一步地，等价于存在一个点 $x$ 满足 $\forall u,x\in S_u$。

以 $x$ 为根考虑，对于一个非叶子节点 $u$，取它子树内任意一个叶子 $v$。可以发现，如果 $x\in S_v$ 那么一定有 $x\in S_u$，因此 $x\in S_u$ 这个限制可以不用考虑。

我们可以依次考虑每个叶子 $u$，使用虚树+树上差分状物给 $S_u$ 中的每一个点的点权增加 $1$。

如果存在某个点的点权等于叶子个数，那么它就是一个合法的 $x$，答案为 Yes。

否则答案为 No。此时还需要构造一组解。

这可以通过进一步分析解决，但是这里我们介绍一种简洁的做法。

定义一个叶子的子集 $T$ 合法当且仅当 $\forall u,v\in T,S_u\bigcap S_v\neq\varnothing$。

直接沿用上面的做法，我们可以在 $O(n)$ 的时间复杂度内询问任意一个 $T$ 是否合法。

而我们可以设计一个只需要 $O(\log n)$ 次询问的算法。

具体地，将所有叶子排成一个序列 $a$。先二分出最小的 $r$ 使得 $a_{1\dots r}$ 不合法，再二分出最大的 $l$ 使得 $a_{l\dots r}$ 不合法。

可以发现，$S_{a_l}\bigcap S_{a_r}=\varnothing$。因此我们在 $O(n\log n)$ 的时间复杂度内找到了一组解。

总时间复杂度 $O(n\log n)$。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 500005
#define LIM 10000005
#define pb push_back
#define gc() (P1==P2 && (P2=(P1=buf)+fread(buf,1,LIM,stdin),P1==P2)?EOF:*P1++)
char buf[LIM],*P1=buf,*P2=buf;
int T,n,m,l,r,ps,lf[N],z[N],w[N],fa[N];vector<int> e[N],vc[N];
struct Node {int u,w;};vector<Node> vc1[N];
int dfsT;struct Point {int fa,dep,sz,hv,tp,dfn;}pt[N];
int rd()
{
	int res=0;char c=0;while(!isdigit(c)) c=gc();
	while(isdigit(c)) res=res*10+(c-48),c=gc();return res;
}
bool cmp(int x,int y) {return pt[x].dfn<pt[y].dfn;}
void dfs1(int u,int f)
{
	pt[u].fa=f;pt[u].dep=pt[f].dep+1;pt[u].sz=1;pt[u].hv=0;
	for(auto v:e[u]) if(v!=f)
	{dfs1(v,u);pt[u].sz+=pt[v].sz;if(pt[v].sz>pt[pt[u].hv].sz) pt[u].hv=v;}
}
void dfs2(int u,int f)
{
	pt[u].tp=f;pt[u].dfn=++dfsT;if(pt[u].hv) dfs2(pt[u].hv,f);
	for(auto v:e[u]) if(v!=pt[u].fa && v!=pt[u].hv) dfs2(v,v);
}
int LCA(int u,int v)
{
	while(pt[u].tp!=pt[v].tp)
	{if(pt[pt[u].tp].dep<pt[pt[v].tp].dep) swap(u,v);u=pt[pt[u].tp].fa;}
	if(pt[u].dep<pt[v].dep) swap(u,v);return v;
}
void build()
{
	vc1[lf[0]].clear();sort(z+1,z+z[0]+1,cmp);
	for(int i=1;i<=z[0];++i)
	{
		vc1[lf[0]].pb((Node) {pt[z[i]].dfn,1});
		if(i>1) vc1[lf[0]].pb((Node) {pt[LCA(z[i],z[i-1])].dfn,-1});
	}vc1[lf[0]].pb((Node) {pt[pt[LCA(z[1],z[z[0]])].fa].dfn,-1});
}
bool chk(int l,int r)
{
	fill(w,w+n+1,0);for(int i=l;i<=r;++i) for(auto j:vc1[i]) w[j.u]+=j.w;
	for(int i=n;i;--i) {if(w[i]==r-l+1) return 1;w[fa[i]]+=w[i];}return 0;
}
void slv()
{
	n=rd();m=rd();dfsT=lf[0]=0;for(int i=1;i<=n;++i) e[i].clear(),vc[i].clear();
	for(int i=1,u,v;i<n;++i) u=rd(),v=rd(),e[u].pb(v),e[v].pb(u);
	for(int i=1,u,v;i<=m;++i) u=rd(),v=rd(),vc[u].pb(v),vc[v].pb(u);
	dfs1(1,0);dfs2(1,1);for(int i=1;i<=n;++i) fa[pt[i].dfn]=pt[pt[i].fa].dfn;
	for(int i=1;i<=n;++i) if(e[i].size()==1)
	{z[0]=0;lf[++lf[0]]=z[++z[0]]=i;for(auto j:vc[i]) z[++z[0]]=j;build();}
	if(chk(1,lf[0])) {printf("Yes\n");return;}printf("No\n");l=1;r=lf[0];
	while(l<=r) {int mid=(l+r)/2;if(chk(1,mid)) l=mid+1;else r=mid-1;}
	ps=l;l=1;r=ps;
	while(l<=r) {int mid=(l+r)/2;if(chk(mid,ps)) r=mid-1;else l=mid+1;}
	printf("%d %d\n",lf[r],lf[ps]);
}
int main() {T=rd();while(T--) slv();return 0;}
```

---

## 作者：UKE_Automation (赞：0)

### CF1827E Bus Routes

[$\text{Link}$](https://codeforces.com/problemset/problem/1827/E)

首先直接做不好做，我们找一些有用的充要条件。首先容易发现的是我们只需要关注叶子节点之间能否互相到达，因为叶子之间的限制是更强的。然后考虑两个叶子何时一定不合法，不难发现，如果我们令 $anc(x)$ 表示 $x$ 一步能走到的深度最浅的点，那么若存在两个点 $x,y$ 使得 $anc(x)$ 与 $anc(y)$ 不是祖孙关系，则 $x,y$ 一定不合法。

但是这个条件只是不合法的充分条件，并不是充要条件，所以我们需要加以补充。此时我们所有的 $anc(x)$ 应该分布在一条根链上，那么我们只需要取出 $anc(x)$ 中深度最小的点，以它为根重新求一遍 $anc'(x)$。此时所有叶子节点都应该能一步走到根节点，否则不能满足题目条件；而如果可以的话，容易发现任意两个叶子节点之间一定可以在两步之内走到，所以这个条件就是充要的。

求解 $anc(x)$ 是比较简单的，在此不再赘述。时间复杂度是 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 5e5 + 5;
const int Inf = 2e9;
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int T;
int n, m;
int head[Maxn], edgenum;
struct node {
	int nxt, to;
}edge[Maxn << 1];

il void add(int u, int v) {
	edge[++edgenum] = {head[u], v}; head[u] = edgenum;
	edge[++edgenum] = {head[v], u}; head[v] = edgenum;
}

struct pth {
	int u, v;
}p[Maxn];

int dep[Maxn], siz[Maxn], son[Maxn], top[Maxn], fa[Maxn], dfn[Maxn], idx;
il void dfs1(int x, int fth) {
	dep[x] = dep[fth] + 1; fa[x] = fth;
	siz[x] = 1; son[x] = 0;
	for(int i = head[x]; i; i = edge[i].nxt) {
		int to = edge[i].to;
		if(to == fth) continue;
		dfs1(to, x);
		siz[x] += siz[to];
		if(siz[to] > siz[son[x]]) son[x] = to;
	}
}

il void dfs2(int x, int rt) {
	top[x] = rt; dfn[x] = ++idx;
	if(son[x]) dfs2(son[x], rt);
	for(int i = head[x]; i; i = edge[i].nxt) {
		int to = edge[i].to;
		if(to == fa[x] || to == son[x]) continue;
		dfs2(to, to);
	}
}

il int lca(int u, int v) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}

int anc[Maxn], id[Maxn];
il void dfs3(int x) {
	for(int i = head[x]; i; i = edge[i].nxt) {
		int to = edge[i].to;
		if(to == fa[x]) continue;
		dfs3(to);
		if(dep[anc[to]] < dep[anc[x]]) anc[x] = anc[to];
	}
}

il void init() {
	for(int i = 1; i <= n; i++) head[i] = 0;
	edgenum = idx = 0;
}

il void solve() {
	init();
	read(n), read(m);
	for(int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		add(u, v);
	}
	dfs1(1, 0), dfs2(1, 1);
	for(int i = 1; i <= n; i++) anc[i] = id[i] = i;
	for(int i = 1, u, v; i <= m; i++) {
		read(u), read(v);
		p[i] = {u, v}; int l = lca(u, v);
		if(dep[l] < dep[anc[u]]) anc[u] = l;
		if(dep[l] < dep[anc[v]]) anc[v] = l;
	}
	dfs3(1);
	sort(id + 1, id + n + 1, [](int x, int y){return dep[anc[x]] < dep[anc[y]];});
	for(int i = 1; i < n; i++) {
		int x = anc[id[i]], y = anc[id[i + 1]];
		if(dfn[x] > dfn[y] || dfn[y] > dfn[x] + siz[x] - 1) {
			puts("NO"); 
			write(id[i], 0), write(id[i + 1]);
			return ;
		} 
	}
	int rt = anc[id[n]]; idx = 0;
	dfs1(rt, 0), dfs2(rt, rt);
	for(int i = 1; i <= n; i++) anc[i] = i;
	for(int i = 1; i <= m; i++) {
		int u = p[i].u, v = p[i].v, l = lca(u, v);
		if(dep[l] < dep[anc[u]]) anc[u] = l;
		if(dep[l] < dep[anc[v]]) anc[v] = l;
	}
	dfs3(rt);
	for(int i = 1; i <= n; i++) {
		if(anc[i] != rt) {
			puts("NO");
			write(id[n], 0), write(i);
			return ;
		}
	}
	puts("YES");
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	read(T);
	while(T--) solve();
    Usd();
	return 0;
}
```

---

## 作者：zifanwang (赞：0)

**这是一道拥有 \*3400 标签的题目。**

首先很显然可以将题意中的条件转化为**任意两个度数为一的节点**都能通过不超过两条路径互相到达。接下来随便取一个度数大于一的节点作为根，如果 $n=2$ 直接判掉即可。

考虑两个叶子节点能互相到达一定需要满足什么条件，发现两个点通过一条路径能到达的最浅的节点一定是祖先关系，于是所有叶子节点能到达的最浅的节点就一定在一条链上。

然后发现答案为 `YES` 当且仅当每个叶子节点都能通过一条路径到达这条链上深度最深的节点，直接判就做完了。时间复杂度 $\mathcal O((n+m)\log n)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define mxn 500003
#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
inline int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
int t,n,m,rt,ps,mx,pt,tot,d[mxn],dfn[mxn],rs[mxn],f[mxn][20];
vector<int>g[mxn],e[mxn];
void dfs(int x,int fa){
	dfn[x]=++tot;
	d[x]=d[fa]+1,f[x][0]=fa;
	rept(i,1,19)f[x][i]=f[f[x][i-1]][i-1];
	for(int i:g[x])if(i!=fa){
		dfs(i,x);
	}
	rs[x]=tot;
}
int lca(int x,int y){
	if(d[x]<d[y])swap(x,y);
	drep(i,18,0)if(d[f[x][i]]>=d[y])x=f[x][i];
	if(x==y)return x;
	drep(i,18,0)if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}
inline bool in(int x,int y){
	return dfn[x]<=dfn[y]&&dfn[y]<=rs[x];
}
signed main(){
	t=read();
	while(t--){
		n=read(),m=read();
		rep(i,1,n)g[i].clear(),e[i].clear();
		for(int i=1,x,y;i<n;++i){
			x=read(),y=read();
			g[x].pb(y),g[y].pb(x);
		}
		for(int i=0,x,y;i<m;++i){
			x=read(),y=read();
			if(x==y)continue;
			if(g[x].size()==1)e[x].pb(y);
			if(g[y].size()==1)e[y].pb(x);
		}
		if(n==2){
			puts(e[1].size()?"YES":"NO\n1 2");
			continue;
		}
		rep(i,1,n){
			if(g[i].size()!=1)rt=i;
			else if(e[i].empty()){
				printf("NO\n%d %d\n",i,i==1?n:1);
				goto next;
			}
		}
		tot=0;
		dfs(rt,0);
		mx=pt=0;
		rep(i,1,n)if(g[i].size()==1){
			ps=0;
			for(int j:e[i]){
				int x=lca(i,j);
				if(!ps||d[x]<d[ps])ps=x;
			}
			if(!mx||d[ps]>d[mx])mx=ps,pt=i;
		}
		rep(i,1,n)if(g[i].size()==1){
			for(int j:e[i]){
				int x=lca(i,j);
				if(in(x,mx)&&(in(mx,i)||in(mx,j)))goto nxt;
			}
			printf("NO\n%d %d\n",i,pt);
			goto next;
			nxt:;
		}
		puts("YES"); 
		next:;
	}
	return 0;
}
```

---

