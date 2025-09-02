# [GCJ 2009 #1A] Collecting Cards

## 题目描述

你已经迷上了最新流行的集换式卡牌游戏——**PokeCraft：The Gathering**。你已经掌握了所有规则！你组建了均衡、进攻型和防御型的套牌！你在网络论坛上激烈争论各种卡牌的优劣！你参加了各种锦标赛！现在，随着官方刚刚宣布将在 2010 年推出一套巨大的新卡包，你决定要收集齐所有新卡！幸运的是，你头脑中仅存的理智还在思考：这究竟要花多少钱？

新卡包中共有 $C$ 种不同的卡牌。卡牌将以“补充包”的形式出售，每个补充包包含 $N$ 张不同种类的卡牌。补充包的组合方式有很多种，每包内不会有重复卡牌。每次你购买一个补充包，你会以等概率获得所有可能的组合之一。你会一包一包地买，直到你拥有所有 $C$ 种卡牌为止。你想知道，**平均而言，你需要买多少包补充包才能集齐所有卡牌？**

## 说明/提示

**限制条件**

- $1\leq T\leq 100$

**小数据集（10 分）**

- $1\leq N\leq C\leq 10$

**大数据集（20 分）**

- $1\leq N\leq C\leq 40$

## 样例 #1

### 输入

```
2
2 1
3 2```

### 输出

```
Case #1: 3.0000000
Case #2: 2.5000000```

# 题解

## 作者：liuchuliang666 (赞：0)

显然是期望 DP，令 $f_k$ 为当前有 $k$ 张卡时，集齐到 $C$ 的期望次数。

枚举这次新增的卡牌数 $i$，那么这个概率为：

$$p_i = \frac{\binom{C - k}{i}\binom{k}{N - i}}{\binom{C}{N}}$$

其中 $i \in [\max(0, N - k), \min(N, C - k)]$，否则 $p_i = 0$。

这其实是标准的超几何分布，解释一下，一共 $C$ 张卡牌，一次取 $N$ 张，一共就有 $\binom{C}{N}$ 种选法，在符合要求的情况中，我们从 $C - k$ 张新牌中选出 $i$ 张，再从 $k$ 张旧牌中选出 $N - i$ 张牌，因此符合要求的情况数为 $\binom{C - k}{i}\binom{k}{N - i}$。

那么我们得到关系式：

$$f_k = 1 + \sum_{i = 0}^{C - k} p_if_{k + i}$$

提出 $i = 0$ 那项，就得到转移方程：

$$f_k = \frac{1 + \sum_{i = 1}^{C - k} p_if_{k + i}}{1 - p_0}$$

其中 $f_C = 0$。

预处理组合数，$O(n ^ 2)$ 计算即可。

献上丑陋的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#endif
#define endl '\n'
#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define rep(i, l, r, ...) for (int i = (l), i##e = (r), ##__VA_ARGS__; i <= i##e; ++i)
#define per(i, r, l, ...) for (int i = (r), i##e = (l), ##__VA_ARGS__; i >= i##e; --i)
#define mst(x, val, len) memset(x, val, sizeof((x)[0]) * (int(len) + 1))
#define mcp(from, to, len) memcpy(to, from, sizeof((to)[0]) * (int(len) + 1))
#define Mst(x, val) memset(x, val, sizeof(x))
#define Mcp(from, to) memcpy(to, from, sizeof(from))
#define mid (((l) + (r)) >> 1)
#define ls ((x) << 1)
#define rs ((x) << 1 | 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define pbds __gnu_pbds
#define int ll
typedef long long ll;
#define vi vector<int>
#define pii pair<int, int>
#define vpii vector<pii>
#define Add(a, b) ((a) = (((a) + (b)) % mod + mod) % mod)
#define Mul(a, b) ((a) = (((a) * (b)) % mod + mod) % mod)
#define add(a, b) (((a) += (b)) >= mod ? (a) -= mod : (a))
#define mul(a, b) (((a) *= (b)) %= mod)
constexpr int MAXN = 40 + 10, inf = 1e9, mod = 998244353, MAXV = MAXN << 2;
template <typename T> inline void chkmx(T &a, const T b) { a = a < b ? b : a; }
template <typename T> inline void chkmn(T &a, const T b) { a = a > b ? b : a; }
int lowbit(int x) { return x & (-x); }
int qpow(int a, int b)
{
    static int res;
    for (res = 1; b; b >>= 1, mul(a, a)) ((b & 1) && mul(res, a));
    return res;
}
int inv(int x) { return qpow(x, mod - 2); }
bool MST;
int n, c, comb[MAXN][MAXN];
double f[MAXN];
void init()
{
    rep(i, 0, 40)
    {
        comb[i][0] = comb[i][i] = 1;
        rep(j, 1, i - 1) comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
    }
}
double prob(int i, int k) // 当前 k 张，抽中 i 张
{
    int imin = max(0ll, n - k);
    int imax = min(n, c - k);
    if (i < imin || i > imax) return 0.0;
    return 1.0 * comb[k][n - i] * comb[c - k][i] / comb[c][n];
}
double solve()
{
    cin >> c >> n;
    f[c] = 0;
    per(k, c - 1, 0)
    {
        f[k] = 1;
        rep(i, 1, c - k) f[k] += f[k + i] * prob(i, k);
        f[k] /= (1 - prob(0, k));
    }
    return f[0];
}
bool MED;
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    debug("Memory Used: %.2lf Mib.\n", (&MST - &MED) / 1024. / 1024.);
    init();
    int T;
    cin >> T;
    rep(i, 1, T) cout << "Case #" << i << ": " << fixed << setprecision(8) << solve() << endl;
    return 0;
}
```

---

