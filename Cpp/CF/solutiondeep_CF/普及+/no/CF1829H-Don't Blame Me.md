# 题目信息

# Don't Blame Me

## 题目描述

Sadly, the problem setter couldn't think of an interesting story, thus he just asks you to solve the following problem.

Given an array $ a $ consisting of $ n $ positive integers, count the number of non-empty subsequences for which the bitwise $ \mathsf{AND} $ of the elements in the subsequence has exactly $ k $ set bits in its binary representation. The answer may be large, so output it modulo $ 10^9+7 $ .

Recall that the subsequence of an array $ a $ is a sequence that can be obtained from $ a $ by removing some (possibly, zero) elements. For example, $ [1, 2, 3] $ , $ [3] $ , $ [1, 3] $ are subsequences of $ [1, 2, 3] $ , but $ [3, 2] $ and $ [4, 5, 6] $ are not.

Note that $ \mathsf{AND} $ represents the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

## 样例 #1

### 输入

```
6
5 1
1 1 1 1 1
4 0
0 1 2 3
5 1
5 5 7 4 2
1 2
3
12 0
0 2 0 2 0 2 0 2 0 2 0 2
10 6
63 0 63 5 5 63 63 4 12 13```

### 输出

```
31
10
10
1
4032
15```

# AI分析结果

### 题目翻译

# 不要怪我

## 题目描述

遗憾的是，出题人没能想出一个有趣的故事，因此他只能让你解决以下问题。

给定一个由 $n$ 个正整数组成的数组 $a$，计算有多少个非空子序列，使得子序列中元素的按位与运算结果的二进制表示中恰好有 $k$ 个 $1$。由于答案可能很大，请输出其对 $10^9+7$ 取模的结果。

回忆一下，数组 $a$ 的子序列是指通过从 $a$ 中移除一些（可能为零个）元素得到的序列。例如，$[1, 2, 3]$、$[3]$、$[1, 3]$ 是 $[1, 2, 3]$ 的子序列，但 $[3, 2]$ 和 $[4, 5, 6]$ 不是。

注意，$\mathsf{AND}$ 表示[按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)。

### 算法分类
动态规划、位运算

### 题解分析与结论

该题的核心在于通过动态规划统计所有可能的子序列，并计算其按位与结果中 $1$ 的个数。由于 $a_i$ 的值域较小（$0 \leq a_i \leq 63$），可以通过状态压缩和位运算来优化计算。

#### 关键思路与技巧：
1. **状态定义**：使用 $dp_{i,j}$ 表示前 $i$ 个元素中，按位与结果为 $j$ 的子序列数量。
2. **状态转移**：对于每个元素 $a_i$，更新 $dp_{i,j}$ 和 $dp_{i,j \& a_i}$，分别表示不选和选 $a_i$ 的情况。
3. **初始化**：每个元素 $a_i$ 自身构成一个子序列，因此 $dp_{i,a_i} = 1$。
4. **结果统计**：遍历所有可能的 $j$，统计其二进制表示中 $1$ 的个数为 $k$ 的 $dp_{n,j}$ 之和。

#### 优化与拓展：
- **时间复杂度**：$O(n \times 64)$，适用于 $n \leq 2 \times 10^5$ 的规模。
- **空间优化**：可以使用滚动数组优化空间复杂度。
- **类似题目**：可以扩展到其他位运算问题，如按位或、按位异或等。

### 推荐题目
1. [P1896 [SCOI2005] 互不侵犯](https://www.luogu.com.cn/problem/P1896)
2. [P2704 [NOI2001] 炮兵阵地](https://www.luogu.com.cn/problem/P2704)
3. [P1879 [USACO06NOV] Corn Fields G](https://www.luogu.com.cn/problem/P1879)

### 精选题解

#### 题解1：SunnyYuan (5星)
**关键亮点**：
- 清晰的状态定义和转移方程。
- 代码简洁，易于理解。
- 使用了滚动数组优化空间。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    f[i][a[i]] = 1;
    for (int j = 0; j < 64; j++) {
        f[i][j] = (1ll * f[i][j] + f[i - 1][j]) % mod;
        f[i][j & a[i]] = (1ll * f[i][j & a[i]] + f[i - 1][j]) % mod;
    }
}
```

#### 题解2：YipChip (4星)
**关键亮点**：
- 使用了SOSDP（Sum Over Subsets DP）优化。
- 详细解释了集合与子集的关系。
- 代码实现较为复杂，但思路清晰。

**核心代码**：
```cpp
for (int j = 0; j < 6; j++) {
    for (int i = 0; i < 1 << 6; i++) {
        if (!(i & 1 << j)) {
            a[i] += a[i ^ 1 << j];
        }
    }
}
```

#### 题解3：Mooncrying (4星)
**关键亮点**：
- 详细的状态转移解释。
- 代码实现简洁，易于理解。
- 提供了边界条件的处理。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 64; j++) {
        dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
        dp[i][j & a[i]] = (dp[i][j & a[i]] + dp[i - 1][j]) % mod;
    }
}
```

### 个人心得
- **调试经历**：在处理边界条件时，特别注意空集的情况，尤其是当 $k=6$ 时，需要减去空集的贡献。
- **顿悟感想**：通过状态压缩和位运算，可以大大简化问题的复杂度，尤其是在处理子序列和位运算相关的问题时。

---
处理用时：44.65秒