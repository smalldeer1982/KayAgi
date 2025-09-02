# [POI 2018 R2] 列车员 Conductor

## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/5069)。

## 题目描述

**题目译自 [XXV Olimpiada Informatyczna — II etap](https://sio2.mimuw.edu.pl/c/oi25-2/dashboard/) [Konduktor](https://szkopul.edu.pl/problemset/problem/lbADmW7d353d0F0iw4kXTjsl/statement/)**

Bajtazar 是拜托尼亚最热门铁路线的列车员。这条线路途经 $m$ 个车站，编号从 $1$ 至 $m$。乘客可在任意车站上下车，为确保所有人持有效票，Bajtazar 需在每对连续车站间查票，但这显然效率低下。

为此，他决定更系统地解决问题。他选出 $n$ 条最热门的乘客路线，每条路线以一对 $a_i, b_i$ 表示，意为乘客在车站 $a_i$ 上车，$b_i$ 下车。Bajtazar 希望以最少的查票次数，确保每条路线上的乘客至少被查一次，即每条路线 $a_i$ 至 $b_i$ 间至少有一次查票。查票不得在车站停靠时进行。

此外，固定查票时机不明智。常客若摸清规律，可能调整路线避开查票。因此，Bajtazar 还想知道所有可能的查票方案。两方案不同，若存在一对连续车站，在一方案中查票而在另一方案中不查。为初步了解，他需计算方案数对 $1000000007$ 取模的结果。

## 说明/提示

**样例 1 解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/y34jmqx1.png)

第一组测试需覆盖四条路线，至少查票三次。一种方案在车站 $2,6,9$ 离站后查票，其余方案为 $\{2,7,9\}, \{3,6,9\}, \{3,7,9\}, \{1,6,9\}$，共五种。第二组测试需覆盖两条路线，至少查票两次，仅一种方案。

**附加样例**

1. $n=4, m=10$。
2. $n=3000$，路线 $i$ 与 $i+1$ 相交，$i=1,\ldots,n-1$。 
3. $n=100000$，所有路线区间互不包含。
4. $n=100000$，一次查票可覆盖所有乘客。

所有附加样例中 $z=1$。

$N$ 为所有 $z$ 组测试数据的 $n$ 之和。若程序仅正确输出最少查票次数（每行仍需输出两个整数，第二个整数为 $32$ 位有符号整数），可获 $20\%$ 分数。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$    | $z \leq 10, n \leq 15$   | $10$ |
| $2$    | $z \leq 100, N \leq 5000$ | $10$ |
| $3$    | $z \leq 100, N \leq 500000$，至多三次查票可覆盖所有乘客 | $15$ |
| $4$    | $z \leq 100, N \leq 500000$，任意三路线区间交集为空 | $15$ |
| $5$    | $z \leq 100, N \leq 500000$ | $50$ |

## 样例 #1

### 输入

```
2
11 4
1 4
6 8
2 7
9 10
3 2
1 2
2 3```

### 输出

```
3 5
2 1
```

# 题解

## 作者：Iniaugoty (赞：1)

不妨先抛开计数不谈，想想这个经典的贪心题有没有什么别的性质不那么强的做法。

为了便于讨论，在 $[i, i + 1]$ 上查票称为选第 $i$ 个点。

考虑 DP。设 $f _ i$ 为考虑完 $[1, i]$，强制选 $i$ ，最少选多少点。枚举上一个选的点 $j$ 进行转移，$f _ i \gets f _ j + 1$。

这个 $j$ 需要满足什么条件，**不存在**某个路线 $[a _ k, b _ k]$，使得 $j < a _ k < b _ k \le i$（如果存在的话，这个区间没有被任何点覆盖）。也就是说，记 $l _ i = \displaystyle \max _ {b _ k \le i} a _ k$，要求 $j \ge l _ i$。

$l _ i$ 可以轻易地处理出来，这样这个做法是 $O(m ^ 2)$ 的。因为跟区间长度没有关系，把 $a _ k, b _ k, m$ 丢到一起离散化，可以做到 $O(n ^ 2)$。

注意到转移形如单点修改，求区间 $\min$。使用线段树维护，可以优化到 $O(n \log n)$。

方案数可以相当容易地和最小值一起维护的。但需要注意的是，离散化后的一个点实际上相当于原图的一段区间，这一段区间中每个点是等价的，在转移后还要乘上区间长度。

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, LL> pii;
const int N = 1e6 + 5;
const int P = 1e9 + 7;

int m, n, a[N], b[N], k, c[N], l[N]; pii dp[N];
int Add(int x, int y) { return x + y >= P ? x + y - P : x + y; }

pii t[N << 2];
pii W(pii x, pii y) {
  auto [tl, sl] = x; auto [tr, sr] = y;
  if (tl < tr) return {tl, sl};
  else if (tr < tl) return {tr, sr};
  else return {tl, Add(sl, sr)};
}
void Pushup(int u) { t[u] = W(t[u << 1], t[u << 1 | 1]); }
void Update(int x, pii k, int l, int r, int u) {
  if (l == r) return t[u] = k, void();
  int mid = l + r >> 1;
  if (x <= mid) Update(x, k, l, mid, u << 1);
  else Update(x, k, mid + 1, r, u << 1 | 1);
  Pushup(u);
}
pii Query(int ql, int qr, int l, int r, int u) {
  if (ql <= l && r <= qr) return t[u];
  int mid = l + r >> 1; pii res = {N, 0};
  if (ql <= mid) res = W(res, Query(ql, qr, l, mid, u << 1));
  if (qr > mid) res = W(res, Query(ql, qr, mid + 1, r, u << 1 | 1));
  return res;
}

void mian() {
  cin >> m >> n, c[1] = 0, c[k = 2] = m;
  F(i, 1, n) cin >> a[i] >> b[i], c[++k] = a[i], c[++k] = b[i];
  sort(c + 1, c + k + 1), k = unique(c + 1, c + k + 1) - c - 1;
  F(i, 1, n)
    a[i] = lower_bound(c + 1, c + k + 1, a[i]) - c,
    b[i] = lower_bound(c + 1, c + k + 1, b[i]) - c - 1;
  F(i, 1, k) l[i] = 1;
  F(i, 1, n) l[b[i]] = max(l[b[i]], a[i]);
  F(i, 1, k << 2) t[i] = {N, 0};
  Update(1, dp[1] = {0, 1}, 1, k, 1);
  int lim = 1;
  F(i, 2, k - 1)
    dp[i] = Query(lim, i - 1, 1, k, 1),
    ++dp[i].first, dp[i].second = 1ll * dp[i].second * (c[i + 1] - c[i]) % P,
    Update(i, dp[i], 1, k, 1), lim = max(lim, l[i]);
  dp[k] = Query(lim, k - 1, 1, k, 1);
  cout << dp[k].first << " " << dp[k].second << "\n";
}

int main() {
  // freopen("zyq.in", "r", stdin);
  // freopen("zyq.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int _; cin >> _; while (_--) mian();
  return 0;
}
```

---

