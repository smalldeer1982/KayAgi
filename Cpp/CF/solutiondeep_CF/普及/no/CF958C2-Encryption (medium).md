# 题目信息

# Encryption (medium)

## 题目描述

Heidi has now broken the first level of encryption of the Death Star plans, and is staring at the screen presenting her with the description of the next code she has to enter. It looks surprisingly similar to the first one – seems like the Empire engineers were quite lazy...

Heidi is once again given a sequence $ A $ , but now she is also given two integers $ k $ and $ p $ . She needs to find out what the encryption key $ S $ is.

Let $ X $ be a sequence of integers, and $ p $ a positive integer. We define the score of $ X $ to be the sum of the elements of $ X $ modulo $ p $ .

Heidi is given a sequence $ A $ that consists of $ N $ integers, and also given integers $ k $ and $ p $ . Her goal is to split $ A $ into $ k $ part such that:

- Each part contains at least $ 1 $ element of $ A $ , and each part consists of contiguous elements of $ A $ .
- No two parts overlap.
- The total sum $ S $ of the scores of those parts is maximized.

Output the sum $ S $ – the encryption code.

## 说明/提示

In the first example, if the input sequence is split as $ (3,4) $ , $ (7) $ , $ (2) $ , the total score would be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C2/d4a5357e9a4720ebdcbfc92aa797cf51b7b836c8.png). It is easy to see that this score is maximum.

In the second example, one possible way to obtain score $ 37 $ is to make the following split: $ (16,3,24) $ , $ (13,9) $ , $ (8) $ , $ (7) $ , $ (5,12,12) $ .

## 样例 #1

### 输入

```
4 3 10
3 4 7 2
```

### 输出

```
16
```

## 样例 #2

### 输入

```
10 5 12
16 3 24 13 9 8 7 5 12 12
```

### 输出

```
37
```

# AI分析结果

### 题目内容重写

Heidi 现在破解了死星计划的第一层加密，屏幕上显示了她需要输入的下一个代码的描述。这个代码看起来与第一个非常相似——似乎帝国的工程师们相当懒惰……

Heidi 再次被给定一个序列 $A$，但现在她还被给定两个整数 $k$ 和 $p$。她需要找出加密密钥 $S$ 是什么。

设 $X$ 是一个整数序列，$p$ 是一个正整数。我们定义 $X$ 的得分为 $X$ 中所有元素的和模 $p$。

Heidi 被给定一个由 $N$ 个整数组成的序列 $A$，以及整数 $k$ 和 $p$。她的目标是将 $A$ 分成 $k$ 部分，满足以下条件：

- 每部分至少包含 $A$ 的一个元素，且每部分由 $A$ 的连续元素组成。
- 任何两部分之间没有重叠。
- 这些部分的得分总和 $S$ 最大化。

输出总和 $S$——即加密代码。

### 算法分类
动态规划

### 题解分析与结论

1. **Acfboy 的题解**（5星）
   - **关键亮点**：通过观察数据范围，利用 $p$ 较小的特点，将枚举 $k$ 的复杂度从 $O(n^2k)$ 降低到 $O(nkp)$。通过记录 $sum_k$ 对应的最大 $f_{k,j-1}$ 来优化转移。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= K; i++) {
         for (int j = 0; j < p; j++) t[j] = -INF;
         if (i == 1) t[0] = 0; 
         for (int j = 1; j <= n; j++) {
             f[i][j] = -INF;
             for (int k = 0; k < p; k++)
                 f[i][j] = std::max(f[i][j], t[k] + (sum[j] - k + p) % p);
             t[sum[j]] = std::max(t[sum[j]], f[i-1][j]);
         }
     }
     ```

2. **Tx_Lcy 的题解**（4星）
   - **关键亮点**：在暴力 DP 的基础上，加入剪枝优化，当 $f_{k,j-1}+p-1 \le f_{i,j}$ 时，提前跳出循环，减少了不必要的枚举。
   - **核心代码**：
     ```cpp
     for (int k = i - 1; k >= 1; --k) {
         if (f[j - 1][k] + p - 1 <= f[j][i]) break;
         f[j][i] = max(f[j][i], f[j - 1][k] + (sum[i] - sum[k]) % p);
     }
     ```

3. **Charlie_ljk 的题解**（4星）
   - **关键亮点**：通过观察 $f_{i,*}$ 的模 $p$ 性质，优化转移过程，直接记录最优策略，将复杂度降低到 $O(nk)$。
   - **核心代码**：
     ```cpp
     for (int i = j; i <= n; i++) {
         f[i][j & 1] = maxx + (sum[i] - sum[ans]) % p;
         if (f[i][(j - 1) & 1] > maxx) {
             maxx = f[i][(j - 1) & 1];
             ans = i;
         }
     }
     ```

### 最优关键思路或技巧
- **利用模数 $p$ 的性质**：由于 $p$ 较小，可以通过枚举 $sum_k$ 的值来优化转移，减少不必要的枚举。
- **剪枝优化**：在暴力 DP 中，通过提前判断条件，减少不必要的计算，提高效率。
- **记录最优策略**：通过记录当前最优的转移点，避免重复计算，进一步优化时间复杂度。

### 可拓展之处
- **类似问题**：类似的分段问题可以通过动态规划结合模数性质进行优化，例如在分段求和、分段最大值等问题中。
- **优化技巧**：在动态规划中，通过观察状态转移的性质，利用数据结构（如数组、线段树等）进行优化。

### 推荐题目
1. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
2. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)
3. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)

### 个人心得摘录
- **调试经历**：在优化过程中，发现直接枚举 $k$ 的复杂度太高，通过观察 $p$ 的性质，成功将复杂度降低。
- **踩坑教训**：在剪枝优化中，最初没有考虑到 $f_{k,j-1}+p-1 \le f_{i,j}$ 的条件，导致优化效果不明显，后来通过调整条件，显著提高了效率。

---
处理用时：30.23秒