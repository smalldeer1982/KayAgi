# 题目信息

# [ABC368G] Add and Multiply Queries

## 题目描述

给定两个长度为 $ N $ 的正整数序列 $ A, B $。需要处理 $ Q $ 个按顺序给出的查询。查询有以下三种类型：

- 类型 $ 1 $：格式为 `1 i x`。将 $ A_i $ 替换为 $ x $。
- 类型 $ 2 $：格式为 `2 i x`。将 $ B_i $ 替换为 $ x $。
- 类型 $ 3 $：格式为 `3 l r`。需要解决以下问题并输出答案：
  - 初始时 $ v = 0 $。依次对 $ i = l, l + 1, \dots, r $ 进行操作，每次操作将 $ v $ 替换为 $ v + A_i $ 或 $ v \times B_i $。求最终能得到的 $ v $ 的最大值。
    需要注意的是，输入中类型 $ 3 $ 的查询的答案保证在 $ 10^{18} $ 以下。

## 说明/提示

### 制約

- $ 1 \leq N \leq 10^5 $
- $ 1 \leq A_i \leq 10^9 $
- $ 1 \leq B_i \leq 10^9 $
- $ 1 \leq Q \leq 10^5 $
- 类型 $ 1 $, $ 2 $ 的查询中，$ 1 \leq i \leq N $
- 类型 $ 1 $, $ 2 $ 的查询中，$ 1 \leq x \leq 10^9 $
- 类型 $ 3 $ 的查询中，$ 1 \leq l \leq r \leq N $
- 类型 $ 3 $ 的查询中，输出值在 $ 10^{18} $ 以下

## 样例 #1

### 输入

```
3
3 2 4
1 2 2
3
3 1 3
1 1 1
3 1 3```

### 输出

```
12
7```

## 样例 #2

### 输入

```
6
65 32 12 5 8 312
4 1 3 15 16 2
6
3 2 6
3 1 5
1 5 6
2 4 9
3 2 6
3 3 5```

### 输出

```
46080
69840
27648
1728```

# AI分析结果

### 题目重写

给定两个长度为 $N$ 的正整数序列 $A$ 和 $B$。需要处理 $Q$ 个按顺序给出的查询。查询有以下三种类型：

- 类型 $1$：格式为 `1 i x`。将 $A_i$ 替换为 $x$。
- 类型 $2$：格式为 `2 i x`。将 $B_i$ 替换为 $x$。
- 类型 $3$：格式为 `3 l r`。需要解决以下问题并输出答案：
  - 初始时 $v = 0$。依次对 $i = l, l + 1, \dots, r$ 进行操作，每次操作将 $v$ 替换为 $v + A_i$ 或 $v \times B_i$。求最终能得到的 $v$ 的最大值。
    需要注意的是，输入中类型 $3$ 的查询的答案保证在 $10^{18}$ 以下。

### 题解分析与结论

该题的核心在于如何高效处理类型 $3$ 的查询，尤其是在 $N$ 和 $Q$ 都较大的情况下。由于答案保证不超过 $10^{18}$，这意味着在区间 $[l, r]$ 内，$B_i > 1$ 的位置最多只有 $\log_2 10^{18} \approx 60$ 个。因此，我们可以利用这一性质，通过维护 $B_i > 1$ 的位置，并结合树状数组或线段树来快速计算区间和，从而实现高效查询。

### 所选高分题解

#### 题解1：作者：__Allen_123__ (赞：94) - 评分：5星
**关键亮点**：
- 利用 `set` 维护所有 $B_i > 1$ 的位置，结合树状数组维护 $A_i$ 的区间和。
- 通过二分查找快速定位区间内的 $B_i > 1$ 的位置，并在这些位置进行贪心决策。
- 代码简洁且高效，时间复杂度为 $O(Q \log N \log V)$，其中 $V$ 为 $10^{18}$。

**核心代码**：
```cpp
set<int> st;
int n, a[N], b[N], q;
void add(int x, int v) {
    for (; x <= n; x += x & -x) c[x] += v;
}
int sum(int x) {
    int ans = 0;
    for (; x; x -= x & -x) ans += c[x];
    return ans;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], add(i, a[i]);
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        if (b[i] > 1) st.insert(i);
    }
    cin >> q;
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) add(l, r - a[l]), a[l] = r;
        else if (op == 2) {
            if (b[l] > 1) st.erase(l);
            b[l] = r;
            if (b[l] > 1) st.insert(l);
        } else {
            int ans = 0, p = l;
            while (p <= r) {
                auto it = st.lower_bound(p);
                if (it == st.end() || *it > r) {
                    ans += sum(r) - sum(p - 1);
                    break;
                }
                ans += sum(*it - 1) - sum(p - 1);
                ans = max(ans * b[*it], ans + a[*it]);
                p = *it + 1;
            }
            cout << ans << endl;
        }
    }
}
```

#### 题解2：作者：gesong (赞：10) - 评分：4星
**关键亮点**：
- 使用树状数组维护 $A_i$ 的区间和，并通过 `vector` 存储 $B_i > 1$ 的位置。
- 在查询时，通过二分查找快速定位区间内的 $B_i > 1$ 的位置，并在这些位置进行贪心决策。
- 代码实现较为清晰，时间复杂度为 $O(Q \log N \log V)$。

**核心代码**：
```cpp
vector<int> d;
int n, a[N], b[N], q;
void add(int i, int x) {
    for (; i <= n; i += lowbit(i)) c[i] += x;
}
int sum(int i) {
    int ans = 0;
    for (; i; i -= lowbit(i)) ans += c[i];
    return ans;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], add(i, a[i]);
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        if (b[i] > 1) d.push_back(i);
    }
    cin >> q;
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) add(l, r - a[l]), a[l] = r;
        else if (op == 2) {
            if (b[l] > 1) d.erase(lower_bound(d.begin(), d.end(), l));
            b[l] = r;
            if (b[l] > 1) d.insert(lower_bound(d.begin(), d.end(), l), l);
        } else {
            int ans = 0, p = l;
            while (p <= r) {
                auto it = lower_bound(d.begin(), d.end(), p);
                if (it == d.end() || *it > r) {
                    ans += sum(r) - sum(p - 1);
                    break;
                }
                ans += sum(*it - 1) - sum(p - 1);
                ans = max(ans * b[*it], ans + a[*it]);
                p = *it + 1;
            }
            cout << ans << endl;
        }
    }
}
```

### 最优关键思路
1. **利用 `set` 或 `vector` 维护 $B_i > 1$ 的位置**：由于 $B_i > 1$ 的位置最多只有 $\log V$ 个，因此可以通过维护这些位置来快速定位区间内的关键点。
2. **树状数组维护区间和**：通过树状数组高效计算区间 $A_i$ 的和，从而在 $B_i = 1$ 的区间内快速累加。
3. **贪心决策**：在 $B_i > 1$ 的位置，通过比较 $v + A_i$ 和 $v \times B_i$ 的大小，选择更优的操作。

### 可拓展之处
该题的思路可以拓展到其他需要处理区间操作且存在某些特殊性质的题目，例如区间内某些点的操作具有指数级影响的情况。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3368 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3368)
3. [P5490 【模板】扫描线](https://www.luogu.com.cn/problem/P5490)

### 个人心得总结
- **调试经历**：在处理类型 $3$ 的查询时，初始实现没有考虑到 $B_i > 1$ 的位置可能不连续，导致查询效率低下。通过引入 `set` 维护这些位置，显著提升了查询效率。
- **踩坑教训**：在修改 $B_i$ 时，需要同时更新 `set` 中的内容，否则会导致查询时定位错误。
- **顿悟感想**：通过分析题目中的特殊性质（如答案不超过 $10^{18}$），可以找到问题的突破口，从而设计出高效的算法。

---
处理用时：64.88秒