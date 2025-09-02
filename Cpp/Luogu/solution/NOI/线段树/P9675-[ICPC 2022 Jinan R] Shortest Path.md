# [ICPC 2022 Jinan R] Shortest Path

## 题目描述

给定一张 $n$ 个点 $m$ 条边的无向图 $G$，边有边权。你要回答 $x$ 个问题，其中第 $i$ $(1\leqslant i\leqslant x)$ 个问题形如：

- 从结点 $1$ 出发，经过 **恰好** $i$ 条边，到达结点 $n$ 的最短路径长度为多少？

对于每个询问，若不存在这样的路径，答案应当为 $0$。一条路径可能 **多次** 经过一条边。

求出这 $x$ 个问题所对应的答案之和。输出答案对 $998244353$ 取模后的结果。

## 样例 #1

### 输入

```
4
3 2 10
1 2 5
2 3 4
3 0 1000000000
3 3 100
1 2 3
1 3 4
2 3 5
4 6 1000000000
1 2 244
1 2 325
1 4 927
3 3 248
2 4 834
3 4 285```

### 输出

```
125
0
15300
840659991```

# 题解

## 作者：Alex_Wei (赞：6)

### *[P9675 [ICPC2022 Jinan R] Shortest Path](https://www.luogu.com.cn/problem/P9675)

感性理解，当 $k$ 很大时，$1\to n$ 经过恰好 $k$ 条边的最短路会在一条权值很小的边上来回移动。考虑将这种猜想转化为严格的结论。

> **结论**
>
> 当 $k > 4n$ 时，若 $1\to n$ 经过恰好 $k$ 条边的最短路 $P_k$ 存在，则 $P_k$ 总可以形如先从 $1$ 走小于 $2n$ 条边到某个点 $u$，在 $u$ 的某条邻边 $(u, v)$ 上不断来回移动直到剩余步数小于 $2n$，然后从 $u$ 走到 $n$。
>
> **证明**
>
> 调整法。
>
> 考虑 $P_k$ 上权值最小的边 $e = (u, v)$，取 $u$ 在 $P_k$ 上的任意一次出现，将 $P_k$ 分成前后两部分。
>
> 若前半部分的长度不小于 $2n$，则可以找到两个在路径上不相交（并非点不相交）的简单环 $C_1, C_2$。若 $C_i$ 长度为偶数，则将 $C_i$ 删去，换成在 $e$ 上来回走，权值不会变大，因为 $e$ 是路径上权值最小的边。否则将 $C_1, C_2$ 同时删去，换成在 $e$ 上来回走。
>
> 后半部分同理。$\square$

关于有向图也有类似的结论，详见我的集训队论文（[P10000](https://www.luogu.com.cn/problem/P10000) 的附件）。

对 $k\leq 4n$，直接求答案。

对 $k > 4n$，枚举每条边考虑贡献：预处理从 $1$ 和 $n$ 走 $0\leq k\leq 4n + 1$ 步到 $u$ 的最短路权值，可以对每个点 $u$ 求出从 $1$ 到 $n$ 中途经过 $u$ 且恰好走 $4n$ 和 $4n + 1$ 步的最短路权值 $F_{4n}(u)$ 和 $F_{4n + 1}(u)$。

于是，边 $(u, v)$ 对 $k > 4n$ 的答案的贡献为
$$
\begin{cases}
F_{4n}(u) + (k - 4n) w(u, v), & 2 \mid k \\
F_{4n + 1}(u) + (k - 4n - 1) w(u, v), & 2\nmid k \\
\end{cases}
$$
分成 $k$ 是奇数或偶数两种情况之后，答案来自每条边的贡献关于 $k$ 是一个等差数列，于是答案关于 $k$ 可表示为若干等差数列的 $\min$。

求若干等差数列的 $\min$ 的和的方法有很多，例如求出凸壳后使用等差数列求和公式，或者使用李超树维护每个 $k$ 的答案，然后二分出答案的每一段等差数列。时间复杂度 $O(nm)$。

将李超树替换成暴力，虽然理论复杂度变劣，但因为复杂度实际上是关于段数的，而段数一看就很难卡满，所以效率相差不大，而且非常好写。

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

constexpr int mod = 998244353;
void addt(int &x, int y) {
  x += y, x >= mod && (x -= mod);
}
int add(int x, int y) {
  return x += y, x >= mod && (x -= mod), x;
}

// ---------- templates above ----------


constexpr int N = 2e3 + 5;

int n, m, x, ans;
ll f[N << 2][N], g[N << 2][N], F[N], G[N];
vector<pii> e[N];

void solve() {
  cin >> n >> m >> x, ans = 0;
  for(int i = 1; i <= n; i++) e[i].clear();
  for(int i = 1; i <= m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    e[a].push_back({b, w});
    e[b].push_back({a, w});
  }
  for(int i = 0; i <= n * 4 + 1; i++) {
    for(int j = 0; j <= n; j++) {
      f[i][j] = g[i][j] = 2e18;
      F[j] = G[j] = 2e18;
    }
  }
  f[0][1] = g[0][n] = 0;
  for(int i = 0; i <= n * 4; i++) {
    for(int j = 1; j <= n; j++) {
      for(pii _ : e[j]) {
        int it = _.first, w = _.second;
        f[i + 1][it] = min(f[i + 1][it], f[i][j] + w);
        g[i + 1][it] = min(g[i + 1][it], g[i][j] + w);
      }
    }
  }
  for(int i = 1; i <= n; i++) {
    for(int j = 0; j <= n * 4 + 1; j++) {
      if(j <= n * 4) F[i] = min(F[i], f[j][i] + g[n * 4 - j][i]);
      G[i] = min(G[i], f[j][i] + g[n * 4 + 1 - j][i]);
    }
  }

  vector<pll> odd, even;
  for(int i = 1; i <= n; i++) {
    for(pii _ : e[i]) {
      if(i > _.first) continue;
      int w = _.second;
      if(F[i] <= 1e18) even.push_back({w, F[i] - 4ll * n * w});
      if(G[i] <= 1e18) odd.push_back({w, G[i] - (4ll * n + 1) * w});
    }
  }
  for(int i = 1; i <= x && i <= n * 4; i++) {
    if(f[i][n] <= 1e18) addt(ans, f[i][n] % mod);
  }
  if(x <= n * 4) {
    cout << ans << endl;
    return;
  }

  if(!odd.empty()) {
    auto calc = [&](int k) {
      k = k * 2 + 1;
      ll ans = LONG_LONG_MAX;
      for(pll it : odd) ans = min(ans, it.first * k + it.second);
      return ans;
    };
    int c = n * 2, lim = x - 1 >> 1;
    while(c <= lim) {
      ll v = calc(c);
      if(c == lim) {
        addt(ans, v % mod);
        break;
      }
      int l = c + 1, r = lim;
      ll d = calc(c + 1) - v;
      while(l < r) {
        int mid = l + r + 2 >> 1;
        if(calc(mid) == v + d * (mid - c)) l = mid;
        else r = mid - 1;
      }
      addt(ans, v % mod * (l - c + 1) % mod);
      addt(ans, 1ll * (l - c + 1) * (l - c) / 2 % mod * d % mod);
      c = l + 1;
    }
  }

  if(!even.empty()) {
    auto calc = [&](int k) {
      k = k * 2;
      ll ans = LONG_LONG_MAX;
      for(pll it : even) ans = min(ans, it.first * k + it.second);
      return ans;
    };

    int c = n * 2 + 1, lim = x >> 1;
    while(c <= lim) {
      ll v = calc(c);
      if(c == lim) {
        addt(ans, v % mod);
        break;
      }
      int l = c + 1, r = lim;
      ll d = calc(c + 1) - v;
      while(l < r) {
        int mid = l + r + 2 >> 1;
        if(calc(mid) == v + d * (mid - c)) l = mid;
        else r = mid - 1;
      }
      addt(ans, v % mod * (l - c + 1) % mod);
      addt(ans, 1ll * (l - c + 1) * (l - c) / 2 % mod * d % mod);
      c = l + 1;
    }
  }
  cout << ans << endl;
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
  cin >> T;
  while(T--) solve();
  fprintf(stderr, "%.3lf ms\n", 1e3 * clock() / CLOCKS_PER_SEC);
  return 0;
}

/*
g++ a.cpp -o a -std=c++14 -O2 -DALEX_WEI
*/
```

---

