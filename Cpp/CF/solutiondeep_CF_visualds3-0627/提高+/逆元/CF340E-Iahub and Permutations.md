# 题目信息

# Iahub and Permutations

## 题目描述

Iahub is so happy about inventing bubble sort graphs that he's staying all day long at the office and writing permutations. Iahubina is angry that she is no more important for Iahub. When Iahub goes away, Iahubina comes to his office and sabotage his research work.

The girl finds an important permutation for the research. The permutation contains $ n $ distinct integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ $ (1<=a_{i}<=n) $ . She replaces some of permutation elements with -1 value as a revenge.

When Iahub finds out his important permutation is broken, he tries to recover it. The only thing he remembers about the permutation is it didn't have any fixed point. A fixed point for a permutation is an element $ a_{k} $ which has value equal to $ k $ $ (a_{k}=k) $ . Your job is to proof to Iahub that trying to recover it is not a good idea. Output the number of permutations which could be originally Iahub's important permutation, modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

For the first test example there are two permutations with no fixed points are \[2, 5, 4, 3, 1\] and \[5, 1, 4, 3, 2\]. Any other permutation would have at least one fixed point.

## 样例 #1

### 输入

```
5
-1 -1 4 3 -1
```

### 输出

```
2
```

# AI分析结果



# 算法分类选择
动态规划或容斥原理

# 题解思路、算法要点与解决难点

## 核心思路分析
题目要求恢复被替换为-1的位置，使得最终排列是错排（无固定点）。关键在于处理两类位置：
1. **类型A**：位置i未被填且原位置是-1，填数时必须避免i。
2. **类型B**：位置i未被填但原数i已被其他位置使用，填数时无特殊限制（但必须满足错排）。

## 动态规划方法
- **状态设计**：`dp[i][j]`表示i个必须错排的位置和j个自由位置的方案数。
- **转移方程**：
  - 处理必须错排的位置：`dp[i][j] += i * dp[i-1][j]`（选一个数填入其他位置）。
  - 处理自由位置：`dp[i][j] += j * dp[i][j-1]`（自由排列剩余数）。
- **初始条件**：`dp[0][j] = j!`（全排列），`dp[i][0]`为错排数D(i)。

## 容斥原理方法
- **统计s**：可能成为固定点的数（未被使用且原位置为-1）。
- **容斥公式**：总方案为`sum_{i=0}^s (-1)^i * C(s,i) * (m-i)!`，其中m为待填数的数量。

## 解决难点
1. **正确分类位置**：区分类型A和B，避免遗漏或重复计算。
2. **状态转移设计**：动态规划需合理结合两类位置的排列方式。
3. **容斥的数学推导**：正确计算可能固定点的组合和排列情况。

# 题解评分 (≥4星)

## 1. FFTotoro（容斥原理） - 5星
- **亮点**：思路清晰，直接应用容斥公式，代码简洁高效。
- **关键代码**：
  ```cpp
  for(int i=0;i<=s;i++) 
    ans += ((-1)^i) * C(s,i) * fac[m-i];
  ```

## 2. Milmon（动态规划） - 4星
- **亮点**：状态设计巧妙，分类处理两类位置，代码可读性强。
- **核心代码**：
  ```cpp
  dp[i][j] = i * dp[i-1][j] + j * dp[i][j-1];
  ```

## 3. als kdjfhgzmxncbv（容斥） - 4星
- **亮点**：详细推导容斥过程，适合数学背景学习者。

# 最优思路或技巧提炼
- **容斥核心**：统计可能固定点的数s，通过交替加减组合方案数，避免重复计算。
- **动态规划核心**：将问题分解为必须错排和自由排列的子问题，分状态转移。

# 同类型题或类似算法套路
- **错排扩展**：当某些位置有特殊限制时，结合容斥或动态规划处理。
- **组合数学**：类似棋盘覆盖、受限排列问题，常用容斥或递推。

# 推荐题目
1. P3185（错排问题）
2. P2513（逆序对排列计数）
3. P3223（排列计数，组合+错排）

# 可视化与算法演示

## 动态规划过程可视化
- **网格动画**：以二维网格表示`dp[i][j]`，每次更新时高亮当前状态转移的来源（如`dp[i-1][j]`和`dp[i][j-1]`）。
- **颜色标记**：红色表示必须错排的位置转移，绿色表示自由位置转移。
- **步进控制**：用户可调整速度，观察每一步状态的变化。

## 容斥原理演示
- **组合选择动画**：展示从s个数中选择i个作为固定点，并计算剩余数的排列。
- **公式高亮**：在求和过程中，实时显示当前项的正负和数值变化。

## 复古像素风格设计
- **8位像素界面**：用网格和色块表示状态转移，背景音乐为8位音效。
- **音效提示**：成功转移时播放清脆音效，错误时低沉音效。

# 核心代码片段（动态规划）
```cpp
long long dp[2001][2001] = {0};
// 初始化自由位置的全排列
for (int j = 0; j <= max_m; j++) 
    dp[0][j] = fac[j];
// 处理必须错排的位置
for (int i = 1; i <= max_i; i++) {
    for (int j = 0; j <= max_j; j++) {
        if (i >= 2) 
            dp[i][0] = (i-1) * (dp[i-1][0] + dp[i-2][0]) % MOD;
        if (j >= 1) 
            dp[i][j] = (i * dp[i-1][j] + j * dp[i][j-1]) % MOD;
    }
}
```

# 总结
通过容斥或动态规划，有效处理受限排列问题。动态规划更直观适合编程实现，而容斥数学性强。关键在正确分类问题约束并设计状态转移或组合计算。

---
处理用时：464.67秒