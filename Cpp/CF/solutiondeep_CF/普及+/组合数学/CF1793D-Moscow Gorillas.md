# 题目信息

# Moscow Gorillas

## 题目描述

In winter, the inhabitants of the Moscow Zoo are very bored, in particular, it concerns gorillas. You decided to entertain them and brought a permutation $ p $ of length $ n $ to the zoo.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ occurs twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

The gorillas had their own permutation $ q $ of length $ n $ . They suggested that you count the number of pairs of integers $ l, r $ ( $ 1 \le l \le r \le n $ ) such that $ \operatorname{MEX}([p_l, p_{l+1}, \ldots, p_r])=\operatorname{MEX}([q_l, q_{l+1}, \ldots, q_r]) $ .

The $ \operatorname{MEX} $ of the sequence is the minimum integer positive number missing from this sequence. For example, $ \operatorname{MEX}([1, 3]) = 2 $ , $ \operatorname{MEX}([5]) = 1 $ , $ \operatorname{MEX}([3, 1, 2, 6]) = 4 $ .

You do not want to risk your health, so you will not dare to refuse the gorillas.

## 说明/提示

In the first example, two segments are correct – $ [1, 3] $ with $ \operatorname{MEX} $ equal to $ 4 $ in both arrays and $ [3, 3] $ with $ \operatorname{MEX} $ equal to $ 1 $ in both of arrays.

In the second example, for example, the segment $ [1, 4] $ is correct, and the segment $ [6, 7] $ isn't correct, because $ \operatorname{MEX}(5, 4) \neq \operatorname{MEX}(1, 4) $ .

## 样例 #1

### 输入

```
3
1 3 2
2 1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
7
7 3 6 2 1 5 4
6 7 2 5 3 1 4```

### 输出

```
16```

## 样例 #3

### 输入

```
6
1 2 3 4 5 6
6 5 4 3 2 1```

### 输出

```
11```

# AI分析结果

### 题目内容翻译
# 莫斯科大猩猩

## 题目描述
冬天，莫斯科动物园的居民们非常无聊，尤其是大猩猩。你决定逗逗它们，于是给动物园带去了一个长度为 $n$ 的排列 $p$。

长度为 $n$ 的排列是一个由 $n$ 个不同的整数组成的数组，这些整数的范围是从 $1$ 到 $n$，顺序任意。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 不是排列（数字 $2$ 在数组中出现了两次），$ [1,3,4] $ 也不是排列（$n = 3$，但数组中出现了 $4$）。

大猩猩们也有自己长度为 $n$ 的排列 $q$。它们建议你计算满足 $\operatorname{MEX}([p_l, p_{l + 1}, \ldots, p_r]) = \operatorname{MEX}([q_l, q_{l + 1}, \ldots, q_r])$ 的整数对 $l, r$（$1 \leq l \leq r \leq n$）的数量。

序列的 $\operatorname{MEX}$ 是该序列中缺失的最小正整数。例如，$\operatorname{MEX}([1, 3]) = 2$，$\operatorname{MEX}([5]) = 1$，$\operatorname{MEX}([3, 1, 2, 6]) = 4$。

你可不敢拿自己的健康冒险，所以不敢拒绝大猩猩们的要求。

## 说明/提示
在第一个样例中，有两个合法的区间：$ [1, 3] $，在两个数组中该区间的 $\operatorname{MEX}$ 都等于 $4$；$ [3, 3] $，在两个数组中该区间的 $\operatorname{MEX}$ 都等于 $1$。

在第二个样例中，例如，区间 $ [1, 4] $ 是合法的，而区间 $ [6, 7] $ 不合法，因为 $\operatorname{MEX}(5, 4) \neq \operatorname{MEX}(1, 4)$。

## 样例 #1
### 输入
```
3
1 3 2
2 1 3
```

### 输出
```
2
```

## 样例 #2
### 输入
```
7
7 3 6 2 1 5 4
6 7 2 5 3 1 4
```

### 输出
```
16
```

## 样例 #3
### 输入
```
6
1 2 3 4 5 6
6 5 4 3 2 1
```

### 输出
```
11
```

### 综合分析与结论
这些题解的核心思路都是枚举 $\text{MEX}$ 值，统计满足条件的区间数量。不同题解在实现细节和分类讨论方式上有所不同，但整体框架一致。

### 算法要点对比
- **TernaryTree**：先处理 $\text{MEX}=1$ 的情况，然后枚举 $\text{MEX}$ 从 $2$ 到 $n$，根据 $i$ 在两个排列中的位置与当前必须包含区间 $[l, r]$ 的关系分类讨论。
- **lizhous**：同样枚举 $\text{MEX}$，通过函数计算左右端点在不同取值范围下的区间个数，根据必须包含区间与 $i$ 位置的关系分类统计。
- **寻逍遥2006**：先考虑 $\text{MEX}=1$ 的情况，再依次考虑 $\text{MEX}=2$ 到 $n$ 的情况，根据 $i$ 位置与当前边界的关系分类讨论。
- **hcywoi**：枚举 $\text{MEX}$ 从 $2$ 到 $n + 1$，记录满足 $1$ 到 $\text{MEX}-1$ 都出现的最大 $l$ 和最小 $r$，以及不包含 $\text{MEX}$ 的最小 $l$ 和最大 $r$，计算贡献。
- **zac2010**：从 $1$ 到 $n$ 考虑每个数作为缺少的最小数的区间情况，同时要保证区间包含 $1$ 到 $i - 1$ 的所有数。
- **Feyn**：求出两个排列中满足 $\text{MEX}=x$ 的区间左右端点取值范围，答案为左右端点取值范围交集的乘积。
- **_Fatalis_**：枚举 $\text{MEX}$，通过双指针移动确定必须包含区间，根据 $\text{MEX}$ 位置划分序列，统计不跨越边界的区间数量。

### 难点对比
- 各题解的难点主要在于对不同 $\text{MEX}$ 值下区间合法性的判断和分类讨论，以及如何正确计算满足条件的区间数量。

### 评分
- **TernaryTree**：5星。思路清晰，有详细的图示和分类讨论，代码注释明确。
- **lizhous**：4星。思路和代码都比较简洁，有函数封装，便于理解。
- **寻逍遥2006**：4星。思路直观，代码实现简单易懂。

### 所选题解
- **TernaryTree（5星）**
    - **关键亮点**：思路清晰，有详细的图示和分类讨论，代码注释明确。
    - **核心代码**：
```cpp
// 处理MEX = 1的情况
int k1 = s[1], k2 = t[1];
if (k1 > k2) swap(k1, k2);
if (1 <= k1 - 1) {
    ans += k1 * (k1 - 1) / 2;
}
if (k2 + 1 <= n) {
    ans += (n - k2 + 1) * (n - k2) / 2;
}
if (k1 < k2) {
    ans += (k2 - k1 - 1) * (k2 - k1) / 2;
}
int l = k1, r = k2;
// 枚举MEX从2到n
for (int m = 2; m <= n; m++) {
    k1 = s[m], k2 = t[m];
    if (k1 > k2) swap(k1, k2);
    if (l <= k1 && k1 <= r || l <= k2 && k2 <= r) {
        l = min(l, k1);
        r = max(r, k2);
        continue;
    }
    if (k1 < l && k2 < l) {
        ans += (n - r + 1) * (l - k2);
    }
    if (k1 > r && k2 > r) {
        ans += (k1 - r) * l;
    }
    if (k1 < l && k2 > r) {
        ans += (l - k1) * (k2 - r);
    }
    l = min(l, k1);
    r = max(r, k2);
}
```
- **lizhous（4星）**
    - **关键亮点**：思路和代码都比较简洁，有函数封装，便于理解。
    - **核心代码**：
```cpp
// 计算左右端点在[l, r]内的区间计数
int get(int l, int r) {
    if (l > r) return 0;
    return (r - l + 2) * (r - l + 1) / 2;
}
// 计算左右端点在不同取值范围下的区间个数
int geter(int l1, int r1, int l2, int r2) {
    return (r1 - l1 + 1) * (r2 - l2 + 1);
}
// MEX为1的区间计数
ans += get(1, min(na[1], nb[1]) - 1);
ans += get(min(na[1], nb[1]) + 1, max(na[1], nb[1]) - 1);
ans += get(max(na[1], nb[1]) + 1, n);
l = min(na[1], nb[1]);
r = max(na[1], nb[1]);
// 枚举MEX从2到n
for (int i = 2; i <= n; i++) {
    int ll = min(na[i], nb[i]), rr = max(na[i], nb[i]);
    if (r < ll) {
        ans += geter(1, l, r, ll - 1);
    }
    if (l > ll && r < rr) {
        ans += geter(ll + 1, l, r, rr - 1);
    }
    if (l > rr) {
        ans += geter(rr + 1, l, r, n);
    }
    l = min(l, ll);
    r = max(r, rr);
}
```
- **寻逍遥2006（4星）**
    - **关键亮点**：思路直观，代码实现简单易懂。
    - **核心代码**：
```cpp
l = min(locp[1], locq[1]), r = max(locp[1], locq[1]);
ans = 1ll * l * (l - 1) / 2 + 1ll * (n - r) * (n - r + 1) / 2 + 1ll * (r - l - 1) * (r - l) / 2;
// 枚举MEX从2到n
for (int i = 2; i <= n; i++) {
    L = min(locp[i], locq[i]), R = max(locp[i], locq[i]);
    if (L < l && r < R) ans += 1ll * (l - L) * (R - r);
    else if (R < l) ans += 1ll * (l - R) * (n - r + 1);
    else if (r < L) ans += 1ll * l * (L - r);
    l = min(l, L), r = max(r, R);
}
```

### 最优关键思路和技巧
- **枚举 $\text{MEX}$**：通过枚举 $\text{MEX}$ 值，将问题转化为统计满足特定条件的区间数量，简化了问题的复杂度。
- **分类讨论**：根据不同 $\text{MEX}$ 值下，$i$ 在两个排列中的位置与必须包含区间的关系进行分类讨论，确保不重不漏地统计所有满足条件的区间。
- **双指针**：使用双指针记录满足 $1$ 到 $\text{MEX}-1$ 都出现的区间边界，方便后续计算。

### 可拓展之处
- **同类型题**：其他涉及 $\text{MEX}$ 计算的题目，如给定数组，求满足特定 $\text{MEX}$ 条件的子数组数量。
- **类似算法套路**：枚举关键值，根据关键值的性质进行分类讨论，结合双指针或其他数据结构维护区间信息。

### 推荐洛谷题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：考察区间和的计算和枚举。
- [P2004 领地选择](https://www.luogu.com.cn/problem/P2004)：涉及二维区间的枚举和计算。
- [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)：需要枚举矩形区间并计算加权和。

### 个人心得摘录与总结
- **Feyn**：考场上交了 N 发，说明在实现过程中可能遇到了一些细节问题，需要更加细心地调试代码。
- **_Fatalis_**：提到状态需要调整，希望今年能不再遗憾，体现了做题状态和心态对解题的影响，需要保持良好的状态和积极的心态。 

---
处理用时：49.83秒