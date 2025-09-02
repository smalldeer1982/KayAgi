# 题目信息

# Watering an Array

## 题目描述

You have an array of integers $ a_1, a_2, \ldots, a_n $ of length $ n $ . On the $ i $ -th of the next $ d $ days you are going to do exactly one of the following two actions:

- Add $ 1 $ to each of the first $ b_i $ elements of the array $ a $ (i.e., set $ a_j := a_j + 1 $ for each $ 1 \le j \le b_i $ ).
- Count the elements which are equal to their position (i.e., the $ a_j = j $ ). Denote the number of such elements as $ c $ . Then, you add $ c $ to your score, and reset the entire array $ a $ to a $ 0 $ -array of length $ n $ (i.e., set $ [a_1, a_2, \ldots, a_n] := [0, 0, \ldots, 0] $ ).

Your score is equal to $ 0 $ in the beginning. Note that on each day you should perform exactly one of the actions above: you cannot skip a day or perform both actions on the same day.

What is the maximum score you can achieve at the end?

Since $ d $ can be quite large, the sequence $ b $ is given to you in the compressed format:

- You are given a sequence of integers $ v_1, v_2, \ldots, v_k $ . The sequence $ b $ is a concatenation of infinitely many copies of $ v $ : $ b = [v_1, v_2, \ldots, v_k, v_1, v_2, \ldots, v_k, \ldots] $ .

## 说明/提示

In the first test case, the sequence $ b $ is equal to $ [1, 3, 2, 3, 1, 3, 2, 3, \ldots] $ and one of the optimal solutions for this case is as follows:

- Perform the operation of the second type on the $ 1 $ -st day: your score increases by $ 3 $ and array $ a $ becomes equal to $ [0, 0, 0] $ .
- Perform the operation of the first type on the $ 2 $ -nd day: array $ a $ becomes equal to $ [1, 1, 1] $ .
- Perform the operation of the first type on the $ 3 $ -rd day: array $ a $ becomes equal to $ [2, 2, 1] $ .
- Perform the operation of the second type on the $ 4 $ -th day: your score increases by $ 1 $ and array $ a $ becomes equal to $ [0, 0, 0] $ .

It can be shown that it is impossible to score more than $ 4 $ , so the answer is $ 4 $ .

In the second test case, the sequence $ b $ is equal to $ [6, 6, 6, 6, \ldots] $ . One of the ways to score $ 3 $ is to perform operations of the first type on the $ 1 $ -st and the $ 3 $ -rd days and to perform an operation of the second type on the $ 2 $ -nd day.

## 样例 #1

### 输入

```
5
3 4 4
1 2 3
1 3 2 3
6 2 3
6 1 2 4 1 5
6 6
5 1 1
0 5 0 5 0
5
1 1 1
1
1
3 4 6
1 2 3
1 3 2 3```

### 输出

```
4
3
0
1
5```

# AI分析结果

### 题目内容重写

#### 题目描述

你有一个长度为 $n$ 的整数数组 $a_1, a_2, \ldots, a_n$。在接下来的 $d$ 天里，你每天必须执行以下两种操作之一：

1. 将数组 $a$ 的前 $b_i$ 个元素每个都加 $1$（即对每个 $1 \le j \le b_i$，执行 $a_j := a_j + 1$）。
2. 统计数组中等于其下标的元素个数（即满足 $a_j = j$ 的元素个数），记为 $c$。然后将 $c$ 加到你的得分中，并将整个数组 $a$ 重置为长度为 $n$ 的全 $0$ 数组（即 $[a_1, a_2, \ldots, a_n] := [0, 0, \ldots, 0]$）。

你的初始得分为 $0$。注意，每天你必须执行上述两种操作之一，不能跳过某一天或在同一天执行两种操作。

由于 $d$ 可能非常大，序列 $b$ 以压缩格式给出：

- 你被给定一个整数序列 $v_1, v_2, \ldots, v_k$。序列 $b$ 是 $v$ 的无限次重复拼接：$b = [v_1, v_2, \ldots, v_k, v_1, v_2, \ldots, v_k, \ldots]$。

#### 说明/提示

在第一个测试用例中，序列 $b$ 等于 $[1, 3, 2, 3, 1, 3, 2, 3, \ldots]$，其中一个最优解如下：

- 在第 $1$ 天执行第二种操作：得分增加 $3$，数组 $a$ 变为 $[0, 0, 0]$。
- 在第 $2$ 天执行第一种操作：数组 $a$ 变为 $[1, 1, 1]$。
- 在第 $3$ 天执行第一种操作：数组 $a$ 变为 $[2, 2, 1]$。
- 在第 $4$ 天执行第二种操作：得分增加 $1$，数组 $a$ 变为 $[0, 0, 0]$。

可以证明，得分不可能超过 $4$，因此答案为 $4$。

在第二个测试用例中，序列 $b$ 等于 $[6, 6, 6, 6, \ldots]$。一种得分为 $3$ 的方法是：在第 $1$ 天和第 $3$ 天执行第一种操作，在第 $2$ 天执行第二种操作。

### 题解分析与结论

#### 综合分析与结论

1. **核心思路**：所有题解都围绕如何在有限的操作次数内最大化得分展开。关键点在于如何利用初始数组和操作序列 $b$ 来最大化得分。
2. **优化策略**：大多数题解都提到，如果数组初始为全 $0$，则最优策略是交替执行操作一和操作二，每次操作二得分为 $1$。对于初始数组不为全 $0$ 的情况，题解建议枚举前 $2n$ 次操作，计算可能的得分，然后结合后续操作的得分。
3. **时间复杂度**：所有题解的时间复杂度均为 $O(n^2)$，适合题目中的 $n$ 范围。

#### 评分较高的题解

1. **作者：Phartial (赞：13)**  
   - **星级**：5星  
   - **关键亮点**：详细分析了数组初始为全 $0$ 时的最优策略，并提出了枚举前 $2n$ 次操作的思路。代码简洁，逻辑清晰。
   - **核心代码**：
     ```cpp
     for (int i = 0; i <= min(d - 1, 2 * n); ++i) {
         int c = 0;
         for (int j = 1; j <= n; ++j) {
             c += (a[j] == j);
         }
         ans = max(ans, c + (d - i - 1) / 2);
         for (int j = 1; j <= b[i % k + 1]; ++j) {
             ++a[j];
         }
     }
     ```

2. **作者：FiraCode (赞：2)**  
   - **星级**：4星  
   - **关键亮点**：提出了暴力枚举前 $2n$ 次操作的思路，并解释了为什么 $2n$ 是合理的上限。代码实现较为直观。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= 2 * n && i < d; ++i) {
         cnt[i] = 0;
         for (int j = 1; j <= v[(i - 1) % k + 1]; ++j) a[j]++;
         for (int j = 1; j <= n; ++j) cnt[i] += a[j] == j;
     }
     ```

3. **作者：Tang_poetry_syndrome (赞：1)**  
   - **星级**：4星  
   - **关键亮点**：从贪心角度出发，分析了数组初始为全 $0$ 时的最优策略，并提出了枚举前 $2n$ 次操作的思路。思路清晰，代码简洁。
   - **核心代码**：
     ```cpp
     for (int i = 0; i <= 2 * n && i < d; ++i) {
         ans = max(ans, cnt[i] + (d - i - 1) / 2);
     }
     ```

### 最优关键思路与技巧

1. **枚举前 $2n$ 次操作**：由于数组长度为 $n$，枚举前 $2n$ 次操作可以在合理的时间内找到最大得分。
2. **交替执行操作一和操作二**：当数组初始为全 $0$ 时，交替执行操作一和操作二可以最大化得分。
3. **贪心策略**：在初始数组不为全 $0$ 时，通过贪心策略枚举前 $2n$ 次操作，结合后续操作的得分，可以找到最优解。

### 拓展思路与类似题目

1. **类似题目**：
   - [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)：考察动态规划和贪心策略。
   - [P1049 装箱问题](https://www.luogu.com.cn/problem/P1049)：考察贪心算法和枚举策略。
   - [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)：考察动态规划和贪心策略。

### 个人心得总结

- **调试经历**：在枚举前 $2n$ 次操作时，需要注意数组的更新顺序，先计算得分再进行操作，否则会导致得分计算错误。
- **顿悟感想**：通过分析数组初始为全 $0$ 时的最优策略，可以简化问题，减少不必要的计算。

---
处理用时：46.81秒