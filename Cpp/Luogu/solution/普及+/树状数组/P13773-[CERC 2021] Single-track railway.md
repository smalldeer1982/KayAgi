# [CERC 2021] Single-track railway

## 题目描述

在单轨铁路上行驶的列车只能在车站相遇。假设有一对列车同时从相反方向出发，一列从起始车站出发，另一列从终点车站（即反方向的起始车站）出发。很可能其中一列需要在某个车站等待另一列。为了最小化延误，列车应在某个车站相遇，使得等待时间最小。

我们已知每对相邻车站之间的行驶时间，且两个方向的行驶时间相同。不幸的是，由于铁路沿线施工，行驶时间会不断变化。你将获得初始的行驶时间，以及每次变更后受影响区段的最新行驶时间。请编写程序，在每次变更后，计算一对从铁路两端出发的列车可能的最短等待时间。

## 说明/提示

### 说明

一开始，两列车应在第 3 号车站相遇。第一列车到达该站需 90 分钟，第二列车需 100 分钟，因此等待时间为 10 分钟。第一次变更后，最优相遇点变为第 4 号车站，两列车都需 130 分钟到达，因此无需等待。第二次变更后，仍在第 4 号车站相遇，但先到达的列车需等待 40 分钟。

### 输入范围

- $2 \leq n \leq 200\,000$
- $0 \leq k \leq 200\,000$
- 所有行驶时间（初始和更新后）均为区间 $[1, 10^6]$ 内的整数。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
20 70 40 10 50
2
4 80
2 30```

### 输出

```
10
0
40```

# 题解

## 作者：liuchuliang666 (赞：0)

题目大意：给出 $n$ 个数（这里的 $n$ 已经事先减 $1$），多次修改，改后以及第一次修改前查询 $\displaystyle \min_{i = 1}^{n - 1}\left|\sum_{j = 1}^{i} a_j - \sum_{j = i + 1}^{n} a_j \right|$。

首先对 $a_i$ 求和，令 $s = \sum_{i = 1}^{n} a_i$，那么我们的目的是找到最大不超过 $\frac{n}{2}$ 的前/后缀和，记这个为 $\text{res}$，答案就是 $n - \text{res} \times 2$。

显然可以两次二分得到这个 $\text{res}$ 的值，那么我们需要单点修改、区间求和，树状数组即可。

代码采用了 $O(n)$ 建树，总的实现如下：

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
#define int int64_t
#define i128 __int128
#define vi vector<int>
#define pii pair<int, int>
#define vpii vector<pii>
#define Add(a, b) ((a) = (((a) + (b)) % mod + mod) % mod)
#define Mul(a, b) ((a) = (((a) * (b)) % mod + mod) % mod)
#define add(a, b) (((a) += (b)) >= mod ? (a) -= mod : (a))
#define mul(a, b) (((a) *= (b)) %= mod)
constexpr int MAXN = 2e5 + 10, inf = 1e9, mod = 998244353, MAXV = MAXN << 2;
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
int n, tr[MAXN], a[MAXN], sum, m;
void upd(int x, int v)
{
    for (; x <= n; x += lowbit(x)) tr[x] += v;
}
int qry(int x)
{
    static int res;
    for (res = 0; x; x -= lowbit(x)) res += tr[x];
    return res;
}
int qry(int l, int r) { return qry(r) - qry(l - 1); }
int lbound(int x)
{
    int ans = 0, res = 0, l = 1, r = n;
    while (l <= r)
    {
        res = qry(1, mid);
        if (res <= x)
            chkmx(ans, res), l = mid + 1;
        else
            r = mid - 1;
    }
    debug("x = %lld, lans = %lld\n", x, ans);
    return ans;
}
int rbound(int x)
{
    int ans = 0, res = 0, l = 1, r = n;
    while (l <= r)
    {
        res = qry(mid, n);
        if (res <= x)
            chkmx(ans, res), r = mid - 1;
        else
            l = mid + 1;
    }
    debug("x = %lld, rans = %lld\n", x, ans);
    return ans;
}
void modify(int p, int v) { upd(p, v - a[p]), sum += v - a[p], a[p] = v; }
int solve() { return abs(sum - (max(lbound(sum >> 1), rbound(sum >> 1)) << 1)); }
bool MED;
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    debug("Memory Used: %.2lf Mib.\n", (&MST - &MED) / 1024. / 1024.);
    cin >> n, n--;
    rep(i, 1, n) cin >> a[i], sum += a[i], a[i] += a[i - 1];
    rep(i, 1, n) tr[i] = a[i] - a[i - lowbit(i)];
    per(i, n, 1) a[i] -= a[i - 1];
    cout << solve() << endl;
    cin >> m;
    while (m--)
    {
        int p, v;
        cin >> p >> v;
        modify(p, v);
        cout << solve() << endl;
    }
    return 0;
}
```

---

