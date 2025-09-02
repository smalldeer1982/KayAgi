# 「ZHQOI R1」划分

## 题目背景

**请注意本题特殊的空间限制。**

## 题目描述

给定一个长度为 $n$ 的序列 $a$，你需要将 $a$ 划分成若干个非空连续子段。

对于每个子段 $[l,r]$，定义其贡献 $w=(\min_{i=l}^{r}a_i)\times(\max_{i=l}^{r}a_i)$。你需要找出一种划分方式，使 $\sum w$ 的值最小，输出这个最小值。

## 说明/提示

**【样例 1 解释】**

划分方案: $ -1 $ $ 2 $ $ \bigg| $ $ -1 $ $ 2 $。

**【样例 2 解释】**

划分方案: $ -3 $ $ 4 $ $ \bigg| $ $ -9 $ $ 1 $ $ 2 $ $ 4 $。

**【数据范围】**

**本题采用捆绑测试。**

对于 $100\%$ 的数据， $1 \le n \le 10^6$，$-10^6 \le a_i \le 10^6$。

| 子任务编号 | $n\leq$ | 特殊性质 | 分值 |
| :-: | :-: | :-: | :-: |
| $1$ | $500$ | 无 | $5$ |
| $2$ | $5000$ | 无 | $10$ |
| $3$ | $10^5$ | 保证 $a_i$ 正负性相同 | $5$ |
| $4$ | $10^5$ | 保证 $a_i\in\{-1,0,1\}$ | $10$ |
| $5$ | $10^5$ | 保证 $a_i$ 随机生成 | $10$ |
| $6$ | $10^5$ | 无 | $15$ |
| $7$ | $10^6$ | 保证 $a$ 中负数个数小于 $2000$ 个 | $15$ |
| $8$ | $10^6$ | 无 | $30$ |

## 样例 #1

### 输入

```
4
-1 2 -1 2```

### 输出

```
-4```

## 样例 #2

### 输入

```
6
-3 4 -9 1 2 4
```

### 输出

```
-48```

# 题解

## 作者：Sol1 (赞：13)

如果序列里面的数全正或者全负，则容易看出最优方案是不进行任何划分，输出序列中的最大值与最小值的乘积即可。

否则可以转化为：选择若干个不交的区间 $[l_1,r_1], [l_2,r_2], \cdots, [l_k,r_k]$，最小化 $\sum a_{l_i} \times a_{r_i}$。

证明：记原问题的答案为 $A$，转化后的问题的答案为 $B$。对于序列的任何划分，我们可以对于划分的每一段找到序列中最小值和最大值的位置，并将这一段缩小到恰好以最小值和最大值为两个端点，这样就可以得到转化后的问题的一个方案。据此，我们有 $B \le A$。

对于转化后的问题的最优方案，显然其选择的每一个区间的两端点的正负性均相反，否则删除该区间一定更优。我们任意扩张区间，直到所有元素均被覆盖。在这个过程中，每一个区间的 $\min$ 会进一步减小（为绝对值更大的负值），$\max$ 会进一步增大（为绝对值更大的正值），从而 $\min \times \max$ 一定会进一步减小。从而我们得到了一个答案更小的原问题的方案。据此我们有 $A \le B$。综上，$A=B$。$\square$

转化后的问题容易使用 dp 解决：记 $f_i$ 表示序列以 $i$ 为结尾的前缀的最优答案，转移分类讨论 $i$ 是否被一个区间覆盖：

- $i$ 不被区间覆盖：转移为 $f_i\gets f_{i-1}$。
- $i$ 被区间覆盖：对所有 $j \leq i$，转移为 $f_i\gets f_{j-1}+a_ja_i$。

这个转移容易使用李超树优化：每次计算一个 $f_i$ 就将直线 $y=f_{i}+a_{i+1}x$ 加入李超树即可。复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int n;
long long a[N], f[N];

struct Line {
    long long k, b;
    Line() {}
    Line(long long k, long long b) : k(k), b(b) {}
    inline long long Eval(long long x) {return k * x + b;}
};

struct Node {
    Line l;
    Node *ls, *rs;
    Node() {}
};
Node nd[N * 2];
int top;
struct Segtree {
    Node *_root;
    //isMin = 1 => min, isMin = 0 -> max
    inline void Ins(Node *&p, long long pl, long long pr, Line nl) {
        if (!p) {
            p = &nd[++top];
            p->l = nl;
            return;
        }
        long long mid = (pl + pr) >> 1;
        if (p && nl.Eval(mid) < p->l.Eval(mid)) swap(nl, p->l);
        if (pl == pr) return;
        if (nl.k < p->l.k) Ins(p->rs, mid + 1, pr, nl);
        else Ins(p->ls, pl, mid, nl);
    }
    inline long long Query(Node *&p, long long pl, long long pr, long long x) {
        if (!p) return 3e18;
        long long mid = pl + pr >> 1;
        if (mid >= x) return min(p->l.Eval(x), Query(p->ls, pl, mid, x));
        else return min(p->l.Eval(x), Query(p->rs, mid + 1, pr, x));
    }
};
Segtree sgt;

const int L = -1e6, R = 1e6;

int main() {
    std::ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    bool fp = 0, fn = 0;
    for (int i = 1;i <= n;i++) {
        cin >> a[i];
        if (a[i] > 0) fp = 1;
        if (a[i] < 0) fn = 1;
    }
    if (!fp || !fn) {
        long long mx = -1e9, mn = 1e9;
        for (int i = 1;i <= n;i++) {
            mx = max(mx, a[i]);
            mn = min(mn, a[i]);
        }
        cout << mx * mn << endl;
    } else {
        f[0] = 0;
        for (int i = 1;i <= n;i++) {
            f[i] = min(f[i - 1], sgt.Query(sgt._root, L, R, a[i]));
            sgt.Ins(sgt._root, L, R, Line(a[i], f[i - 1]));
        }
        cout << f[n] << endl;
    }
    return 0;
}
```

---

## 作者：Edward2019 (赞：11)

### 做法 1

设 $f_i$ 表示当前这一段以 $i$ 结尾的最小 $\sum w$，直接暴力转移，时间复杂度 $O(n^3)$ 或 $O(n^2)$。

### 做法 2

注意到当 $a_i$ 正负性相同时，只分一段一定是对的，答案即 $(\min_{i=1}^{n}a_i)\times(\max_{i=1}^{n}a_i)$。

### 做法 3

$a_i\in\{-1,0,1\}$ 时，直接贪心，每当凑齐一对 $-1$ 和 $1$ 时，直接分一段。

### 做法 4

使用**做法 1**，但只从当前位置前面 100 个点转移，可以通过随机生成的数据。

### 做法 5

注意到，如果 $a_i$ 正负性不全相同，那么每一段都至少有一个正数和负数一定不劣，考虑删掉一些没用的数。

对于每一个正数段，只保留最大值、位于最大值左边的数中的最大值（若没有则不保留）、位于最大值右边的数中的最大值（若没有则不保留）。对于 sub7，这样做完之后点数显然小于 $10^4$ 个，可以直接使用**做法1**。

### 做法 6

下面只考虑 $a_i$ 正负性不全相同的情况。

考虑如果划分方案已定，那么对于一段划分方案的区间 $[L,R]$，显然一段的价值只取决于一段的最小值位置 $x$ 和最大值位置 $y$，注意到当 $L \neq 1$ 时，将 $L$ 调整到 $\min(x,y)$ 一定不劣。

设 $f_i$ 为前 $i$ 个数的答案，那么设上一段右端点为 $j$，由上述分析可知：最后一段的其中一个极值的位置为 $j+1$，此时有两种转移：第一种是继承 $i-1$ 的答案，第二种是钦定 $i$ 为另一个极值的位置，转移即可， 时间复杂度 $\Theta(n^2)$。

这么做为什么是对的呢？显然得到的答案不会优于最终答案，然后注意到最优答案的方案一定会被转移，所以是正确的。

注意到这个转移形式类似于 $f_i=\max(f_{j-1}+a_j\cdot a_i)$，直接李超树优化即可，复杂度 $\Theta(n\log n)$，代码十分简短。

```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6 + 5;
int t[N * 8], n, a[N];
ll f;
struct {
	ll k, b;
	ll operator()(ll x) { return k * x + b; }
} L[N];
void upd(int p, int l, int r, int k) {
	int m = l + r >> 1;
	bool a = L[k](l) <= L[t[p]](l), b = L[k](r) <= L[t[p]](r);
	if (a & b) return swap(t[p], k);
	if (a | b) upd(p * 2, l, m, k), upd(p * 2 + 1, m + 1, r, k);
}
ll qry(int p, int x, int l, int r) {
	int m = l + r >> 1;
	ll v = L[t[p]](x);
	if (l == r) return v;
	if (x <= m) return min(v, qry(p * 2, x, l, m));
	return min(v, qry(p * 2 + 1, x, m + 1, r));
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	auto [mn, mx] = minmax_element(a + 1, a + n + 1);
	if (*mn >= 0 || *mx <= 0) return cout << 1ll * *mn * *mx, 0;
	for (int i = 1; i <= n; ++i)
		L[i] = {a[i], f}, upd(1, -N, N, i),
		f = min(qry(1, a[i], -N, N), f);
	cout << f << '\n';
	return 0;
}
```

---

## 作者：GONGX (赞：2)

## 题意简述
给定一个序列 $a$，求将该序列划分成若干个子段后，所有子段贡献和的最小值。
## 前置知识
李超线段树优化动态规划
## 解题思路
我个人认为这道题还是有一定思维难度的。

首先我们可以设 $dp_i$ 表示考虑序列前 $i$ 个数的最小贡献和。转移时可分为两种情况讨论：对于第 $i$ 个元素属于其中一个已划分的子段，$dp_i\gets min_{j=0}^{i-1}(dp_j+(min_{k=j+1}^{i}a_k)\times (max_{k=j+1}^{i}a_k))$；对于 $i$ 不属于当前任何一个已划分的子段，$dp_{i}\gets  dp_{i - 1}$。

但是这个 DP 的时间复杂度显然是 $O(N^2)$ 的，无法通过本题。于是我们可以想到，对于第一种情况的转移，我们可以钦定 $a_i$ 为当前子段中的一个最大值或最小值，状态转移方程就改为了 $dp_i\gets min_{j=0}^{i-1}(dp_{j}+a_{i}\cdot a_{j+1})$。然后这个状态转移方程看上去就比较友好了。我们可以考虑设 $x=a_i$，$k=a_{j+1}$，$dp_j=b$，状态转移方程就转为了 $dp_i\gets min_{j=0}^{i-1}(k\cdot x+b)$ 的形式。这显然就可以斜率优化了，但我还是选择用李超线段树优化。在每次转移时查询当前最优决策点，再更新李超线段树信息即可。

但是这么做真的是对的吗？对于序列中有正数也有负数的情况，我们每次按照这个转移，$a_i$ 和 $a_{j+1}$ 一定是子段 $j+1$ 到 $i$ 的元素中的两个极值，并且一个是正数一个是负数，否则的话这个子段一定会在后面转移时继续扩大到包含至少一个正数和一个负数，这样转移出来的答案显然是最优的；但对于序列中没有正数或没有负数的情况，这样求出的答案可能永远为 $0$，因为我们这样转移时只考虑了答案不大于零的情况，这就导致我们可能没有划分出任何子段，但是题目要求至少是要将序列 $a$ 划分为一个子段的。本蒟蒻一开始一直没注意这个细节，导致一直答案错误。那么我们该怎么处理这种情况呢？对于这种情况，我们显然可以想到一个贪心策略：直接将整个序列划分为唯一的一个子段，答案便为整个序列的最大值与最小值相乘。证明：无论怎么划分子段，该序列的最大值一定要乘上序列中的另外一个值，而又由于序列中的数正负性相同或者还有零，所以最大值只有乘上最小值才能使贡献和最小，所以应将最大的元素与最小的元素划分在同一子段内，并且为了不让其他元素产生贡献，应直接将所有元素划分在同一子段中。
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e6 + 5, M = 1e6;
int n, idx;
long long a[N], dp[N];
struct line {
    long long k, b;
    long long calc(int x) {
        return k * x + b;
    }
} p[N];
void add_line(long long k, long long b) { // 添加直线
    p[++idx] = {k, b};
}
struct Segment_Tree { // 李超线段树
    int tag[M << 3 | 3]; // 由于 a[i] 取值范围是 -M ~ M，所以应开八倍空间
    void update(int u, int l, int r, int k) {
        if (!tag[u]) {
            tag[u] = k;
            return;
        }
        int mid = l + r >> 1;
        if (p[k].calc(mid) < p[tag[u]].calc(mid))
            swap(k, tag[u]);
        if (p[k].calc(l) < p[tag[u]].calc(l))
            update(u << 1, l, mid, k);
        else if (p[k].calc(r) < p[tag[u]].calc(r))
            update(u << 1 | 1, mid + 1, r, k);
    }
    long long query(int u, int l, int r, int x) {
        if (!tag[u]) return 1e18;
        long long val = p[tag[u]].calc(x);
        if (l == r) return val;
        int mid = l + r >> 1;
        if (x <= mid) return min(val, query(u << 1, l, mid, x));
        return min(val, query(u << 1 | 1, mid + 1, r, x));
    }
} tr;
int main() { // 李超线段树优化 DP
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    long long ma = -M, mi = M;
    for (int i = 1; i <= n; ++i)
        cin >> a[i], ma = max(ma, a[i]), mi = min(mi, a[i]);
    if (ma <= 0 || mi >= 0) // 对于序列 a 正负性相同时的特判
        return cout << ma * mi, 0;
    add_line(a[1], dp[0] = 0), tr.update(1, -M, M, idx);
    for (int i = 1; i <= n; ++i) {
        dp[i] = min(dp[i - 1], tr.query(1, -M, M, a[i]));
        add_line(a[i + 1], dp[i]), tr.update(1, -M, M, idx);
    }
    cout << dp[n];
    return 0;
}
/*
设 dp[i] 表示考虑序列 a 中前 i 个数的最小贡献和
1. i 属于当前其中一个划分后的子段 dp[i] <- min(dp[j] + a[j + 1] · a[i])（0 <= j < i）
2. i 不属于当前任何一个划分后的子段 dp[i] <- dp[i - 1]
*/
```

---

