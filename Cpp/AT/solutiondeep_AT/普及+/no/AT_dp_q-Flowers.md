# 题目信息

# Flowers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_q

$ N $ 本の花が横一列に並んでいます。 各 $ i $ ($ 1\ \leq\ i\ \leq\ N $) について、左から $ i $ 番目の花の高さは $ h_i $ で、美しさは $ a_i $ です。 ただし、$ h_1,\ h_2,\ \ldots,\ h_N $ はすべて相異なります。

太郎君は何本かの花を抜き去ることで、次の条件が成り立つようにしようとしています。

- 残りの花を左から順に見ると、高さが単調増加になっている。

残りの花の美しさの総和の最大値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 2\ ×\ 10^5 $
- $ 1\ \leq\ h_i\ \leq\ N $
- $ h_1,\ h_2,\ \ldots,\ h_N $ はすべて相異なる。
- $ 1\ \leq\ a_i\ \leq\ 10^9 $

### Sample Explanation 1

左から $ 2,\ 4 $ 番目の花を残せばよいです。 すると、高さは左から順に $ 1,\ 2 $ となり、単調増加になっています。 また、美しさの総和は $ 20\ +\ 40\ =\ 60 $ となります。

### Sample Explanation 2

最初から条件が成り立っています。

### Sample Explanation 3

答えは 32-bit 整数型に収まらない場合があります。

### Sample Explanation 4

左から $ 2,\ 3,\ 6,\ 8,\ 9 $ 番目の花を残せばよいです。

## 样例 #1

### 输入

```
4

3 1 4 2

10 20 30 40```

### 输出

```
60```

## 样例 #2

### 输入

```
1

1

10```

### 输出

```
10```

## 样例 #3

### 输入

```
5

1 2 3 4 5

1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
5000000000```

## 样例 #4

### 输入

```
9

4 2 5 8 3 6 1 7 9

6 8 8 4 6 3 5 7 5```

### 输出

```
31```

# AI分析结果

### 题目重写
$ N $ 朵花排成一列，每朵花有高度 $ h_i $ 和美丽值 $ a_i $，且所有花的高度互不相同。现在需要移除一些花，使得剩下的花从左到右高度单调递增，求剩下的花美丽值总和的最大值。

### 算法分类
动态规划、树状数组/线段树

### 综合分析与结论
本题的核心是动态规划，但由于数据规模较大（$ N \leq 2 \times 10^5 $），直接使用 $ O(N^2) $ 的 DP 会超时。因此，需要使用树状数组或线段树来优化 DP 的转移过程，将时间复杂度降低到 $ O(N \log N) $。

### 所选高星题解

#### 1. 作者：Orange_qwq (5星)
**关键亮点**：
- 使用树状数组优化 DP 转移，代码简洁且易于理解。
- 详细解释了树状数组的使用场景和优化思路。
- 代码中使用了 `long long` 来处理大数，避免了溢出问题。

**核心代码**：
```cpp
void add(int x, ll y) {
    for (int i = x; i <= n; i += i & (-i)) tr[i] = max(tr[i], y);
}

ll _(int x) {
    ll ans = 0;
    for (int i = x; i; i -= i & (-i)) ans = max(ans, tr[i]);
    return ans;
}
```
**实现思想**：
- `add` 函数用于更新树状数组中的最大值。
- `_` 函数用于查询区间 $[1, x]$ 的最大值。

#### 2. 作者：SIXIANG32 (4星)
**关键亮点**：
- 使用线段树优化 DP 转移，思路清晰。
- 详细解释了线段树的构建和查询过程。
- 代码中使用了 `long long` 来处理大数，避免了溢出问题。

**核心代码**：
```cpp
void updata(int l, int r, int pos, int now, int val) {
    if (l == r) {
        M[now] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) updata(l, mid, pos, ls(now), val);
    else updata(mid + 1, r, pos, rs(now), val);
    push_up(now);
}

int query(int l, int r, int s, int t, int now) {
    if (l <= s && t <= r) return M[now];
    int mid = (s + t) >> 1, res = 0;
    if (l <= mid) res = max(res, query(l, r, s, mid, ls(now)));
    if (r > mid) res = max(res, query(l, r, mid + 1, t, rs(now)));
    return res;
}
```
**实现思想**：
- `updata` 函数用于更新线段树中的最大值。
- `query` 函数用于查询区间 $[l, r]$ 的最大值。

#### 3. 作者：FelFa_1414666 (4星)
**关键亮点**：
- 使用线段树优化 DP 转移，思路清晰。
- 详细解释了线段树的构建和查询过程。
- 代码中使用了 `long long` 来处理大数，避免了溢出问题。

**核心代码**：
```cpp
void modify(int x, int p, LL v) {
    if (t[x].l == t[x].r) {
        t[x].v = v;
        return;
    }
    int mid = (t[x].l + t[x].r) >> 1;
    if (p <= mid) modify(lson(x), p, v);
    else modify(rson(x), p, v);
    t[x].v = std::max(t[lson(x)].v, t[rson(x)].v);
}

LL query(int x, int l, int r) {
    if (l <= t[x].l && t[x].r <= r) return t[x].v;
    int mid = (t[x].l + t[x].r) >> 1;
    LL s = 0;
    if (l <= mid) s = std::max(s, query(lson(x), l, r));
    if (r > mid) s = std::max(s, query(rson(x), l, r));
    return s;
}
```
**实现思想**：
- `modify` 函数用于更新线段树中的最大值。
- `query` 函数用于查询区间 $[l, r]$ 的最大值。

### 最优关键思路或技巧
- **树状数组/线段树优化**：通过树状数组或线段树来维护区间最大值，将 DP 的转移复杂度从 $ O(N^2) $ 降低到 $ O(N \log N) $。
- **离散化**：由于 $ h_i $ 的范围在 $ 1 \leq h_i \leq N $，可以直接使用 $ h_i $ 作为下标，避免了离散化的步骤。

### 可拓展之处
- **类似问题**：可以扩展到其他需要维护区间最大值或最小值的问题，如最长上升子序列（LIS）的变种。
- **数据结构选择**：根据具体问题的需求，可以选择树状数组或线段树，树状数组代码更简洁，线段树功能更强大。

### 推荐题目
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)
3. [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)

### 个人心得摘录
- **调试经历**：在使用树状数组时，需要注意更新和查询的边界条件，避免数组越界。
- **踩坑教训**：在处理大数时，务必使用 `long long` 类型，避免溢出问题。
- **顿悟感想**：通过树状数组或线段树优化 DP 转移，可以显著提高算法的效率，尤其是在处理大规模数据时。

---
处理用时：42.31秒