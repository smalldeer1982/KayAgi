# 题目信息

# Array Splitting

## 题目描述

You are given a sorted array $ a_1, a_2, \dots, a_n $ (for each index $ i > 1 $ condition $ a_i \ge a_{i-1} $ holds) and an integer $ k $ .

You are asked to divide this array into $ k $ non-empty consecutive subarrays. Every element in the array should be included in exactly one subarray.

Let $ max(i) $ be equal to the maximum in the $ i $ -th subarray, and $ min(i) $ be equal to the minimum in the $ i $ -th subarray. The cost of division is equal to $ \sum\limits_{i=1}^{k} (max(i) - min(i)) $ . For example, if $ a = [2, 4, 5, 5, 8, 11, 19] $ and we divide it into $ 3 $ subarrays in the following way: $ [2, 4], [5, 5], [8, 11, 19] $ , then the cost of division is equal to $ (4 - 2) + (5 - 5) + (19 - 8) = 13 $ .

Calculate the minimum cost you can obtain by dividing the array $ a $ into $ k $ non-empty consecutive subarrays.

## 说明/提示

In the first test we can divide array $ a $ in the following way: $ [4, 8, 15, 16], [23], [42] $ .

## 样例 #1

### 输入

```
6 3
4 8 15 16 23 42
```

### 输出

```
12
```

## 样例 #2

### 输入

```
4 4
1 3 3 7
```

### 输出

```
0
```

## 样例 #3

### 输入

```
8 1
1 1 2 3 5 8 13 21
```

### 输出

```
20
```

# AI分析结果

【题目内容】
# 数组分割

## 题目描述

给定一个有序数组 $ a_1, a_2, \dots, a_n $（对于每个索引 $ i > 1 $，条件 $ a_i \ge a_{i-1} $ 成立）和一个整数 $ k $。

要求将这个数组分成 $ k $ 个非空连续子数组。数组中的每个元素必须恰好包含在一个子数组中。

设 $ max(i) $ 为第 $ i $ 个子数组中的最大值，$ min(i) $ 为第 $ i $ 个子数组中的最小值。分割的代价等于 $ \sum\limits_{i=1}^{k} (max(i) - min(i)) $。例如，如果 $ a = [2, 4, 5, 5, 8, 11, 19] $，并将其分成 $ 3 $ 个子数组：$ [2, 4], [5, 5], [8, 11, 19] $，那么分割的代价为 $ (4 - 2) + (5 - 5) + (19 - 8) = 13 $。

计算将数组 $ a $ 分成 $ k $ 个非空连续子数组时可以获得的最小代价。

## 说明/提示

在第一个测试中，可以将数组 $ a $ 分成如下子数组：$ [4, 8, 15, 16], [23], [42] $。

## 样例 #1

### 输入

```
6 3
4 8 15 16 23 42
```

### 输出

```
12
```

## 样例 #2

### 输入

```
4 4
1 3 3 7
```

### 输出

```
0
```

## 样例 #3

### 输入

```
8 1
1 1 2 3 5 8 13 21
```

### 输出

```
20
```

【算法分类】
贪心

【题解分析与结论】
本题的核心思路是通过贪心算法，选择最大的 $k-1$ 个相邻元素的差值，从而最小化分割的代价。所有题解都基于这一思路，但在实现细节上有所不同。以下是各题解的要点总结：

1. **徐敬**：通过堆优化，实时维护前 $k-1$ 个最大的差值，避免了全排序的开销。代码实现较为复杂，但效率较高。
2. **Waddles**：直接计算相邻元素的差值，排序后取前 $k-1$ 个最大的差值，思路清晰，代码简洁。
3. **Eismcs**：通过前缀和思想，将问题转化为贪心选择最大的 $k-1$ 个差值，代码实现简洁明了。
4. **Burnside**：详细推导了分割代价的数学表达式，最终通过排序选择最小的 $k-1$ 个差值，思路严谨。
5. **Believe_R_**：通过样例分析，推导出最小代价的计算公式，代码实现清晰，提供了堆优化和排序两种实现方式。
6. **_bql**：通过标记分割点，统计各段的极差，思路清晰，代码实现较为复杂。
7. **woshishei**：通过差分数组，选择最小的 $n-k$ 个差值，思路新颖，代码简洁。
8. **yizr_cnyali**：通过前缀和思想，选择最大的 $k-1$ 个差值，代码实现简洁。
9. **Heartlessly**：通过数学推导，将问题转化为选择最小的 $k-1$ 个差值，思路严谨，代码简洁。
10. **AC_Automation**：通过堆优化，选择前 $k$ 小的差值，思路清晰，代码简洁。

【评分较高的题解】
1. **Waddles**（5星）
   - 关键亮点：思路清晰，代码简洁，直接通过排序选择最大的 $k-1$ 个差值，易于理解。
   - 代码实现：
     ```cpp
     sort(s+1,s+n);
     for(int i=1;i<=n-k;i++) ans+=s[i];
     ```

2. **Eismcs**（5星）
   - 关键亮点：通过前缀和思想，将问题转化为贪心选择最大的 $k-1$ 个差值，代码实现简洁明了。
   - 代码实现：
     ```cpp
     sort(f+1,f+n);
     for(int i=1;i<k;i++) ans+=f[i];
     ```

3. **Heartlessly**（5星）
   - 关键亮点：通过数学推导，将问题转化为选择最小的 $k-1$ 个差值，思路严谨，代码简洁。
   - 代码实现：
     ```cpp
     sort(f+1,f+n+1);
     for(int i=1;i<k;i++) ans+=f[i];
     ```

【最优关键思路或技巧】
1. **贪心选择最大的 $k-1$ 个相邻元素的差值**：通过排序或堆优化，选择最大的 $k-1$ 个差值，从而最小化分割的代价。
2. **差分数组的应用**：通过差分数组，将问题转化为选择最小的 $n-k$ 个差值，思路新颖。

【可拓展之处】
1. **类似算法套路**：在需要分割数组或序列的问题中，贪心选择最大的差值或最小的差值是一种常见的优化思路。
2. **堆优化的应用**：在需要动态维护前 $k$ 个最大或最小值的场景中，堆优化是一种高效的实现方式。

【推荐题目】
1. [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

【个人心得摘录】
1. **Believe_R_**：通过样例分析，推导出最小代价的计算公式，提供了堆优化和排序两种实现方式，代码实现清晰。
2. **Heartlessly**：通过数学推导，将问题转化为选择最小的 $k-1$ 个差值，思路严谨，代码简洁。

---
处理用时：42.23秒