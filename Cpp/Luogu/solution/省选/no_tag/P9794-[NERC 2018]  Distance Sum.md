# [NERC 2018]  Distance Sum

## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) D 题。

## 题目描述

给你一个 $n$ 个顶点 $m$ 条边的连通无向图，定义 $u$ 与 $v$ 的距离 $d(u, v)$ 为从 $u$ 到 $v$ 最短路径上经过的边数。

现在请你求出 $\sum_{u=1}^n \sum_{v=u+1}^n d(u,v)$。

## 说明/提示

对于所有数据保证 $1 \leq n \leq 10^5$，$n-1 \leq m \leq n + 42$，$1 \leq x_i, y_i \leq n$ 且 $x_i \neq y_i$。

样例一的图是：

![](https://cdn.luogu.com.cn/upload/image_hosting/39wue8qr.png)

其中 $d(1,2) = 1$，$d(1,3) = 1$，$d(1,4) = 2$，$d(2,3) = 1$，$d(2,3) = 2$，$d(3,4) = 1$，总和为 $1 + 1 + 2 + 1 + 2 + 1 = 8$。

样例二为：

![](https://cdn.luogu.com.cn/upload/image_hosting/89k279bd.png)

## 样例 #1

### 输入

```
4 4
1 2
2 3
3 1
3 4```

### 输出

```
8```

## 样例 #2

### 输入

```
7 10
1 2
2 6
5 3
5 4
5 7
3 6
1 7
5 1
7 4
4 1```

### 输出

```
34```

# 题解

## 作者：Alex_Wei (赞：1)

### *[P9794 [NERC2018] Distance Sum](https://www.luogu.com.cn/problem/P9794)

$m - n$ 较小，套路地求出任意一棵生成树，则非树边共有 $k = m - n + 1$ 条。

设所有非树边两端形成点集 $S$，$u, v$ 之间的最短路要么经过 $S$，要么不经过 $S$。若不经过 $S$，那么将所有非树边删掉不影响结果，此时 $u, v$ 之间的距离就等于它们的树上距离。否则 $u, v$ 之间的最短路等于 $\min_{x\in S} (d(u, x) + d(x, v))$。

进一步地，设 $S_u = \{x\in S\mid \forall y\in S, y\neq S : y\notin \mathrm{path}(x, u)\}$，即所有 $x\in S$，满足对任意不等于 $x$ 的 $y\in S$，$y$ 都不在 $x$ 到 $u$ 的树上路径上，直观理解就是 $S$ 中与 $u$ “相邻” 的元素。若 $u$ 到 $v$ 的最短路经过 $S$，则最短路可表示为
$$
\min_{x\in S_u} \min_{y\in S_v} (d(u, x) + d(x, y) + d(y, v))
$$
因为 $u$ 无法绕过 $S_u$ 到达 $S$ 中其它的点，对于 $v$ 同理。

对任意 $S\subseteq S'$，将 $S$ 替换为 $S'$ 依然成立。为什么要这样做呢？可以让 $S_u$ 变小。设 $V(S)$ 为 $S$ 的虚树上的结点，只在边上的不算。将 $S$ 替换为 $V(S)$，$S$ 的大小变为原来的不超过两倍，但 $|S_u|\leq 2$。

设落在虚树某条边上的点集为 $T$。对 $u\in T$，设 $T(u)$ 为 $u$ 以及所有 $v\notin T$ 的儿子 $v$ 的子树的并，则 $v\in T(u)$到 $v' \in T(u)$ 的任意一条路径都会经过 $u$。

考虑虚树的一条边 $(x, y)$，设 $P$ 为 $x, y$ 之间的路径，包含 $x$ 但不含 $y$。

计算 $v\to T(u)\ (u\in P)$ 的贡献。

首先算出 $X = d(v, x)$ 和 $Y = d(v, y)$，则对于 $u\in P$，$d(v, u) = \min(X + d(x, u), Y + d(y, u))$。随着 $u$ 在 $P$上移动，$d(x, u)$ 不断加 $1$，$d(y, u)$ 不断减 $1$，所以存在一个分界点 $p$ 使得 $p$ 以及 $p$ 前面 $u$ 会取到 $\min$ 的前一项，$p$ 后面的 $u$ 会取到 $\min$ 的后一项。分界点在路径上的位置可以 $\mathcal{O}(1)$ 计算。

对于 $p$ 以及 $p$ 前面的 $u$，对答案产生贡献 $|T(u)| \cdot (X + d(x, u)) + \sum_{v'\in T(u)} d(v', u)$。后面一项记为 $d_u$，容易 $\mathcal{O}(n)$ 预处理。根据计算式，可知需要对 $P$ 预处理 $|T(u)|$ 和 $|T(u)|d(x, u) + d_u$ 的前缀和。类似预处理 $|T(u)|$ 和 $|T(u)|d(v, u) + d_u$ 的后缀和。

此外，计算 $X, Y$ 需要每个点的深度以及 $S$ 内部的全源最短路（MSSP），点数和边数都是 $\mathcal{O}(k)$，使用 Dijkstra 或 Floyd 均可。

注意特殊处理 $v\in P$ 的情况，此时 $d(v, u)$ 可以不经过 $S$，将 $v\in T(u')$ 的 $u'$ 从 $P$ 中删去，$P$ 断开成两部分，根据预处理的信息足以计算这两段的贡献。

最后只剩所有 $v, v'\in T(u)$ 的贡献没算，这部分就是树上任意两点最短路之和，平凡。

可以枚举 $v\in T$ 表示计算 $T(v)\to T(u)$ 的贡献，因为对于 $T(v)$ 内部的所有点，在算它们与外界的最短路时，它们差不多是等价的。拆拆贡献就能算。代码采用这种方法。

时间复杂度 $\mathcal{O}(nk + \mathrm{MSSP})$。

进一步地，可以枚举虚树的两条边 $\mathcal{O}(1)$ 计算它们之间的贡献，即 $\forall v\in P_1, u\in P_2, T(v)\to T(u)$，考虑 $\min$ 取到哪一项，绕来绕去总共 $2\times 2 = 4$ 种情况，也能算，就是稍微有点烦。

时间复杂度 $\mathcal{O}(n + k ^ 2\log k)$，相当优秀（只是口胡，没写过）。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using pdd = pair<double, double>;
using ull = unsigned long long;
using LL = __int128_t;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;

int mod;
void addt(int &x, int y) {
  x += y, x >= mod && (x -= mod);
}
int add(int x, int y) {
  return x += y, x >= mod && (x -= mod), x;
}

struct FastMod {
  ull b, m;
  FastMod(ull b = 1) : b(b), m(ull((LL(1) << 64) / b)) {}
  ull reduce(ull a) {
    ull q = ull((LL(m) * a) >> 64);
    ull r = a - q * b; // can be proven that 0 <= r < 2 * b
    return r >= b ? r - b : r;
  }
} R;

// ---------- templates above ----------

constexpr int N = 1e5 + 5;
constexpr int M = 200 + 5;

ll dis[N], sdis[N], siz[N];
int n, m, fa[N];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
vector<int> e[N];
vector<pii> g;

int vis[N], tp[N]; // on the path, if belongs to
int node, ind[N], anc[N]; // index, lowest ancestor
int dep[N], sz[N]; // depth, size of subtree
void dfs(int id, int ff) {
  fa[id] = ff;
  dep[id] = dep[ff] + 1;
  vis[id] = tp[id];
  sz[id] = siz[id] = 1;
  int cnt = 0;
  if(ff) e[id].erase(find(e[id].begin(), e[id].end(), ff));
  for(int it : e[id]) {
    dfs(it, id);
    if(vis[it]) vis[id] = 1, cnt++;
    else siz[id] += siz[it];
    sz[id] += sz[it];
  }
  if(cnt >= 2) tp[id] = 1;
}

void dfs2(int id, int ac) {
  anc[id] = ac;
  for(int it : e[id]) {
    dfs2(it, vis[it] ? it : ac);
    if(!vis[it]) {
      sdis[ac] += 1ll * sz[it] * (siz[ac] - sz[it]);
      dis[ac] += sz[it];
    }
  }
  if(vis[id]) {
    // cout << "info " << id << " " << siz[id] << " " << dis[id] << "\n";
  }
}

int be[M], ed[M], bel[N], d[M][M];
vector<int> ch[M];
vector<pll> pre[M], suf[M];
void dfs3(int id) {
  if(tp[id]) {
    ind[id] = ++node;
    int x = id;
    do {
      ch[node].push_back(x);
      bel[x] = node;
      x = fa[x];
    } while(x && !tp[x]);
    // cout << "?? " << id << " " << x << " " << dep[id] - dep[x] << "\n";
    d[node][ind[x]] = d[ind[x]][node] = dep[id] - dep[x];
    be[node] = ch[node][0], ed[node] = x;
  }
  for(int it : e[id]) dfs3(it);
}

void solve() {
  cin >> n >> m;
  for(int i = 1; i <= n; i++) fa[i] = i;
  for(int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    if(find(u) == find(v)) {
      g.push_back({u, v});
      tp[u] = tp[v] = 1;
    }
    else {
      // cout << u << " " << v << endl;
      e[u].push_back(v);
      e[v].push_back(u);
      fa[fa[u]] = v;
    }
  }
  tp[1] = 1, dfs(1, 0), dfs2(1, 1);
  memset(d, 0x3f, sizeof(d)), dfs3(1);
  for(pii _ : g) {
    int u = ind[_.first], v = ind[_.second];
    d[u][v] = d[v][u] = 1;
  }
  for(int i = 0; i <= node; i++) d[i][i] = 0;
  for(int k = 0; k <= node; k++) {
    for(int i = 0; i <= node; i++) {
      for(int j = 0; j <= node; j++) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
  for(int i = 1; i <= node; i++) {
    int len = ch[i].size();
    pre[i].resize(len + 2), suf[i].resize(len + 2);
    for(int p = 1; p <= len; p++) {
      int id = ch[i][p - 1];
      pre[i][p] = pre[i][p - 1];
      pre[i][p].first += siz[id];
      pre[i][p].second += 1ll * (p - 1) * siz[id] + dis[id];
    }
    for(int p = len; p; p--) {
      int id = ch[i][p - 1];
      suf[i][p] = suf[i][p + 1];
      suf[i][p].first += siz[id];
      suf[i][p].second += 1ll * (len + 1 - p) * siz[id] + dis[id];
    }
  }
  ll ans = 0;
  for(int i = 1; i <= n; i++) {
    if(!vis[i]) continue;
    // cout << "------------------------\n";
    ans += 2 * sdis[i];
    // cout << "i " << sdis[i] << " ans = " << ans << endl;
    int up = ed[bel[i]], dn = be[bel[i]];
    int updis = dep[i] - dep[up], dndis = dep[dn] - dep[i];
    // cout << i << " updis = " << updis << " dndis = " << dndis << endl;
    // cout << "up = " << up << " dn = " << dn << endl;
    for(int j = 1; j <= node; j++) {
      int l = be[j], r = ed[j], len = ch[j].size();
      auto upd = [&](int l, int r, int ldis, int rdis) {
        if(l == r) return;
        // ldis + (p - l) <= rdis + (r - p)
        int p = min((rdis + r - ldis + l) >> 1, r - 1);
        // cout << "i " << i << " j " << j << " l " << l << " r " << r << " ldis " << ldis << " rdis " << rdis << " p = " << p << endl;
        pll pr = pre[j][p], su = suf[j][p + 1];
        pr.first -= pre[j][l - 1].first;
        pr.second -= pre[j][l - 1].second;
        pr.second -= pr.first * (l - 1);
        su.first -= suf[j][r].first;
        su.second -= suf[j][r].second;
        su.second -= su.first * (len + 1 - r);
        // cout << "pr.first, second = " << pr.first << ", " << pr.second << endl;
        // cout << "su.first, second = " << su.first << ", " << su.second << endl;
        ans += (pr.first + su.first) * dis[i];
        ans += (pr.second + su.second) * siz[i];
        ans += 1ll * ldis * pr.first * siz[i];
        ans += 1ll * rdis * su.first * siz[i];
        // cout << "curans = " << ans << endl;
      };
      int ldis = min(updis + d[ind[up]][ind[l]], dndis + d[ind[dn]][ind[l]]);
      int rdis = min(updis + d[ind[up]][ind[r]], dndis + d[ind[dn]][ind[r]]);
      // cout << "see ldis rdis " << i << " " << j << " " << ldis << " " << rdis << endl;
      // cout << "l, r = " << l << " " << r << endl;
      if(j != bel[i]) upd(1, len + 1, ldis, rdis);
      else {
        upd(1, dndis + 1, ldis, 0);
        upd(dndis + 2, len + 1, 1, rdis);
      }
    }
  }
  cerr << ans << endl;
  cout << ans / 2 << endl;
}
bool Med;
signed main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  int T = 1;
  // cin >> T;
  while(T--) solve();
  fprintf(stderr, "%.3lf ms\n", 1e3 * clock() / CLOCKS_PER_SEC);
  return 0;
}

/*
g++ a.cpp -o a -std=c++14 -O2 -DALEX_WEI
*/
```

---

