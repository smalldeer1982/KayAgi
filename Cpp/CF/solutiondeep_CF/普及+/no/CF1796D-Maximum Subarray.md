# 题目信息

# Maximum Subarray

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , consisting of $ n $ integers. You are also given two integers $ k $ and $ x $ .

You have to perform the following operation exactly once: add $ x $ to the elements on exactly $ k $ distinct positions, and subtract $ x $ from all the others.

For example, if $ a = [2, -1, 2, 3] $ , $ k = 1 $ , $ x = 2 $ , and we have picked the first element, then after the operation the array $ a = [4, -3, 0, 1] $ .

Let $ f(a) $ be the maximum possible sum of a subarray of $ a $ . The subarray of $ a $ is a contiguous part of the array $ a $ , i. e. the array $ a_i, a_{i + 1}, \dots, a_j $ for some $ 1 \le i \le j \le n $ . An empty subarray should also be considered, it has sum $ 0 $ .

Let the array $ a' $ be the array $ a $ after applying the aforementioned operation. Apply the operation in such a way that $ f(a') $ is the maximum possible, and print the maximum possible value of $ f(a') $ .

## 样例 #1

### 输入

```
4
4 1 2
2 -1 2 3
2 2 3
-1 2
3 0 5
3 2 4
6 2 -8
4 -1 9 -3 7 -8```

### 输出

```
5
7
0
44```

# AI分析结果

### 题目内容重写（中文）

给定一个数组 $a_1, a_2, \dots, a_n$，由 $n$ 个整数组成。同时给定两个整数 $k$ 和 $x$。

你需要执行以下操作恰好一次：选择 $k$ 个不同的位置，将它们的元素加上 $x$，并将其他位置的元素减去 $x$。

例如，若 $a = [2, -1, 2, 3]$，$k = 1$，$x = 2$，且我们选择了第一个元素，则操作后的数组为 $a = [4, -3, 0, 1]$。

定义 $f(a)$ 为数组 $a$ 的最大子段和。子数组是数组的连续部分，即 $a_i, a_{i+1}, \dots, a_j$，其中 $1 \le i \le j \le n$。空子数组也应被考虑，其和为 $0$。

设 $a'$ 为操作后的数组，请找到使 $f(a')$ 最大的操作方式，并输出 $f(a')$ 的最大可能值。

### 算法分类
动态规划

### 题解分析与结论

本题的核心在于如何在操作后找到最大子段和。由于 $k$ 的限制，直接暴力枚举所有可能的操作组合是不可行的。因此，大多数题解采用了动态规划的思路，通过状态转移方程来求解最大子段和。

#### 题解对比
1. **芷陌陌吖的题解**（4星）
   - 使用动态规划，状态定义为 $f_{i,j}$ 表示前 $i$ 个元素中已选择 $j$ 个位置加上 $2x$ 的最大子段和。
   - 关键点在于状态转移方程的设计，考虑了是否在当前元素上加 $2x$ 的情况。
   - 代码清晰，逻辑严谨，时间复杂度为 $O(nk)$。

2. **Lu_xZ的题解**（4星）
   - 同样采用动态规划，状态定义为 $f_{i,j,0/1}$ 表示前 $i$ 个元素中已选择 $j$ 个位置，且当前元素是否被选择的最大子段和。
   - 通过分类讨论 $x$ 的正负情况，优化了状态转移。
   - 代码简洁，时间复杂度为 $O(nk)$。

3. **KingPowers的题解**（4星）
   - 使用动态规划，状态定义为 $f_{i,j,0/1}$ 表示前 $i$ 个元素中已选择 $j$ 个位置，且当前元素是否被选择的最大子段和。
   - 通过状态转移方程，考虑了当前元素是否被选择的情况。
   - 代码实现简洁，时间复杂度为 $O(nk)$。

#### 最优思路与技巧
- **动态规划状态设计**：通过定义 $f_{i,j}$ 或 $f_{i,j,0/1}$ 来表示前 $i$ 个元素中已选择 $j$ 个位置的最大子段和，能够有效减少问题的复杂度。
- **状态转移方程**：通过是否在当前元素上加 $2x$ 来设计状态转移方程，确保所有可能的情况都被考虑。
- **边界条件处理**：在处理边界条件时，确保状态转移的正确性，特别是在 $i = j$ 或 $i < j$ 时。

#### 扩展思路
- **单调队列优化**：可以通过单调队列进一步优化时间复杂度，将复杂度从 $O(nk)$ 降低到 $O(n)$。
- **线段树维护**：对于更复杂的情况，可以使用线段树来维护最大子段和，适用于更广泛的场景。

### 推荐题目
1. [P4513 小白逛公园](https://www.luogu.com.cn/problem/P4513) - 线段树维护最大子段和
2. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115) - 经典最大子段和问题
3. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384) - 树链剖分与动态规划结合

### 个人心得摘录
- **芷陌陌吖**：在处理边界条件时，特别注意了 $i = j$ 时的状态转移，确保 DP 数组的正确性。
- **Lu_xZ**：通过分类讨论 $x$ 的正负情况，优化了状态转移，避免了不必要的计算。
- **KingPowers**：在实现时，特别注意了边界条件的处理，确保状态转移的正确性。

### 核心代码片段
```cpp
// 芷陌陌吖的代码片段
for (int i = 1; i <= n; i++) {
    f[i][0] = max(f[i-1][0] + a[i], 0ll);
    if (i <= n - k) ans = max(ans, f[i][0]);
    for (int j = 1; j <= k; j++) {
        if (i < j) continue;
        if (i == j) f[i][j] = max(f[i-1][j-1] + a[i] + x * 2, 0ll);
        else f[i][j] = max({f[i-1][j-1] + a[i] + x * 2, f[i-1][j] + a[i], 0ll});
        if (i <= n - (k - j)) ans = max(ans, f[i][j]);
    }
}
```

这段代码通过动态规划的状态转移方程，逐步计算最大子段和，并在每一步更新答案。

---
处理用时：44.73秒