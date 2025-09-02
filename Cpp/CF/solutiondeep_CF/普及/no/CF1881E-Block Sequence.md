# 题目信息

# Block Sequence

## 题目描述

Given a sequence of integers $ a $ of length $ n $ .

A sequence is called beautiful if it has the form of a series of blocks, each starting with its length, i.e., first comes the length of the block, and then its elements. For example, the sequences \[ $ \color{red}{3},\ \color{red}{3},\ \color{red}{4},\ \color{red}{5},\ \color{green}{2},\ \color{green}{6},\ \color{green}{1} $ \] and \[ $ \color{red}{1},\ \color{red}{8},\ \color{green}{4},\ \color{green}{5},\ \color{green}{2},\ \color{green}{6},\ \color{green}{1} $ \] are beautiful (different blocks are colored differently), while \[ $ 1 $ \], \[ $ 1,\ 4,\ 3 $ \], \[ $ 3,\ 2,\ 1 $ \] are not.

In one operation, you can remove any element from the sequence. What is the minimum number of operations required to make the given sequence beautiful?

## 说明/提示

In the first test case of the example, the given sequence is already beautiful, as shown in the statement.

In the second test case of the example, the sequence can only be made beautiful by removing all elements from it.

In the fifth test case of the example, the sequence can be made beautiful by removing the first and last elements. Then the sequence will become \[ $ 2,\ 3,\ 4 $ \].

## 样例 #1

### 输入

```
7
7
3 3 4 5 2 6 1
4
5 6 3 2
6
3 4 1 6 7 7
3
1 4 3
5
1 2 3 4 5
5
1 2 3 1 2
5
4 5 5 1 5```

### 输出

```
0
4
1
1
2
1
0```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个长度为 $n$ 的整数序列 $a$。

一个序列被称为“美丽”的，如果它的形式是由一系列块组成的，每个块的开头是它的长度，后面是它的元素。例如，序列 \[ $ \color{red}{3},\ \color{red}{3},\ \color{red}{4},\ \color{red}{5},\ \color{green}{2},\ \color{green}{6},\ \color{green}{1} $ \] 和 \[ $ \color{red}{1},\ \color{red}{8},\ \color{green}{4},\ \color{green}{5},\ \color{green}{2},\ \color{green}{6},\ \color{green}{1} $ \] 是美丽的（不同的块用不同的颜色标记），而 \[ $ 1 $ \], \[ $ 1,\ 4,\ 3 $ \], \[ $ 3,\ 2,\ 1 $ \] 不是。

在一次操作中，你可以删除序列中的任意一个元素。问最少需要多少次操作才能使给定的序列变得美丽？

#### 说明/提示

在第一个样例中，给定的序列已经是美丽的，如题目描述所示。

在第二个样例中，序列只能通过删除所有元素来变得美丽。

在第五个样例中，序列可以通过删除第一个和最后一个元素来变得美丽。然后序列将变为 \[ $ 2,\ 3,\ 4 $ \]。

#### 样例 #1

##### 输入

```
7
7
3 3 4 5 2 6 1
4
5 6 3 2
6
3 4 1 6 7 7
3
1 4 3
5
1 2 3 4 5
5
1 2 3 1 2
5
4 5 5 1 5
```

##### 输出

```
0
4
1
1
2
1
0
```

### 算法分类

动态规划

### 题解分析与结论

这道题的核心思路是通过动态规划（DP）来计算最少需要删除的元素数量，使得序列变得“美丽”。大多数题解都采用了从后向前递推的DP策略，状态转移方程的核心思想是：对于每个位置 $i$，可以选择删除当前元素，或者将当前元素作为某个块的起始元素，跳过接下来的 $a[i]$ 个元素。

#### 关键思路与技巧

1. **状态定义**：大多数题解定义 $dp[i]$ 为从第 $i$ 个元素到序列末尾所需的最小删除次数。
2. **状态转移**：
   - 如果删除当前元素，则 $dp[i] = dp[i+1] + 1$。
   - 如果不删除当前元素，且 $i + a[i] \leq n$，则 $dp[i] = dp[i + a[i] + 1]$。
3. **初始化**：$dp[n+1] = 0$，表示空序列不需要删除任何元素。
4. **优化**：部分题解通过优先队列或堆来优化状态转移，但整体复杂度仍为 $O(n)$。

#### 推荐题解

1. **作者：midsummer_zyl (赞：9)**
   - **星级**：5星
   - **关键亮点**：思路清晰，代码简洁，状态转移方程明确，初始化合理。
   - **核心代码**：
     ```cpp
     for (int i = n - 1; i >= 1; i--) {
         if(a[i] + i <= n)
             dp[i] = min(dp[i + 1] + 1, dp[i + a[i] + 1]);
         else dp[i] = dp[i + 1] + 1;
     }
     ```

2. **作者：NanNanzi_QvQ (赞：5)**
   - **星级**：4星
   - **关键亮点**：状态转移方程简洁，初始化合理，代码可读性强。
   - **核心代码**：
     ```cpp
     for (int i = n - 1; i >= 1; i--) {
         if (i + a[i] > n) dp[i] = dp[i + 1] + 1;
         else dp[i] = min(dp[i + 1] + 1, dp[i + a[i] + 1]);
     }
     ```

3. **作者：Jason_Harry_Song (赞：0)**
   - **星级**：4星
   - **关键亮点**：状态转移方程清晰，初始化合理，代码简洁。
   - **核心代码**：
     ```cpp
     for (int i = n; i >= 1; i--) {
         f[i] = f[i + 1] + 1;
         if (i + a[i] + 1 <= n + 1) {
             f[i] = min(f[i], f[i + a[i] + 1]);
         }
     }
     ```

### 最优关键思路

最优的思路是通过从后向前递推的DP策略，状态转移方程的核心是选择删除当前元素或将当前元素作为块的起始元素。这种思路的时间复杂度为 $O(n)$，空间复杂度为 $O(n)$，适合处理大规模数据。

### 可拓展之处

类似的问题可以通过类似的DP策略解决，例如在序列中寻找满足特定条件的最小子序列或最小删除次数。可以进一步优化状态转移，例如使用优先队列或堆来优化某些复杂的状态转移。

### 推荐题目

1. [P1049 装箱问题](https://www.luogu.com.cn/problem/P1049)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)

---
处理用时：34.42秒