# 题目信息

# Expected Power

## 题目描述

You are given an array of $ n $ integers $ a_1,a_2,\ldots,a_n $ . You are also given an array $ p_1, p_2, \ldots, p_n $ .

Let $ S $ denote the random multiset (i. e., it may contain equal elements) constructed as follows:

- Initially, $ S $ is empty.
- For each $ i $ from $ 1 $ to $ n $ , insert $ a_i $ into $ S $ with probability $ \frac{p_i}{10^4} $ . Note that each element is inserted independently.

Denote $ f(S) $ as the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of all elements of $ S $ . Please calculate the expected value of $ (f(S))^2 $ . Output the answer modulo $ 10^9 + 7 $ .

Formally, let $ M = 10^9 + 7 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test case, $ a = [1, 2] $ and each element is inserted into $ S $ with probability $ \frac{1}{2} $ , since $ p_1 = p_2 = 5000 $ and $ \frac{p_i}{10^4} = \frac{1}{2} $ . Thus, there are $ 4 $ outcomes for $ S $ , each happening with the same probability of $ \frac{1}{4} $ :

- $ S = \varnothing $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ .
- $ S = \{1\} $ . In this case, $ f(S) = 1 $ , $ (f(S))^2 = 1 $ .
- $ S = \{2\} $ . In this case, $ f(S) = 2 $ , $ (f(S))^2 = 4 $ .
- $ S = \{1,2\} $ . In this case, $ f(S) = 1 \oplus 2 = 3 $ , $ (f(S))^2 = 9 $ .

Hence, the answer is $ 0 \cdot \frac{1}{4} + 1 \cdot \frac{1}{4} + 4\cdot \frac{1}{4} + 9 \cdot \frac{1}{4} = \frac{14}{4} = \frac{7}{2} \equiv 500\,000\,007 \pmod{10^9 + 7} $ .

In the second test case, $ a = [1, 1] $ , $ a_1 $ is inserted into $ S $ with probability $ 0.1 $ , while $ a_2 $ is inserted into $ S $ with probability $ 0.2 $ . There are $ 3 $ outcomes for $ S $ :

- $ S = \varnothing $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ . This happens with probability $ (1-0.1) \cdot (1-0.2) = 0.72 $ .
- $ S = \{1\} $ . In this case, $ f(S) = 1 $ , $ (f(S))^2 = 1 $ . This happens with probability $ (1-0.1) \cdot 0.2 + 0.1 \cdot (1-0.2) = 0.26 $ .
- $ S = \{1, 1\} $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ . This happens with probability $ 0.1 \cdot 0.2 = 0.02 $ .

Hence, the answer is $ 0 \cdot 0.72 + 1 \cdot 0.26 + 0 \cdot 0.02 = 0.26 = \frac{26}{100} \equiv 820\,000\,006 \pmod{10^9 + 7} $ .

## 样例 #1

### 输入

```
4
2
1 2
5000 5000
2
1 1
1000 2000
6
343 624 675 451 902 820
6536 5326 7648 2165 9430 5428
1
1
10000```

### 输出

```
500000007
820000006
280120536
1```

# AI分析结果

### 题目内容重写

**题目描述**

给定一个包含 $n$ 个整数的数组 $a_1, a_2, \ldots, a_n$，以及一个数组 $p_1, p_2, \ldots, p_n$。

定义 $S$ 为一个随机多重集（即可能包含重复元素），其构造过程如下：

- 初始时，$S$ 为空。
- 对于每个 $i$ 从 $1$ 到 $n$，以概率 $\frac{p_i}{10^4}$ 将 $a_i$ 插入 $S$ 中。注意每个元素的插入是独立的。

定义 $f(S)$ 为 $S$ 中所有元素的**按位异或**（bitwise XOR）。请计算 $(f(S))^2$ 的期望值，并将结果对 $10^9 + 7$ 取模。

形式化地，令 $M = 10^9 + 7$。可以证明答案可以表示为一个不可约分数 $\frac{p}{q}$，其中 $p$ 和 $q$ 是整数且 $q \not \equiv 0 \pmod{M}$。输出整数 $x$，使得 $0 \le x < M$ 且 $x \cdot q \equiv p \pmod{M}$。

**说明/提示**

在第一个测试用例中，$a = [1, 2]$，每个元素被插入 $S$ 的概率为 $\frac{1}{2}$，因为 $p_1 = p_2 = 5000$ 且 $\frac{p_i}{10^4} = \frac{1}{2}$。因此，$S$ 有 $4$ 种可能的结果，每种结果的概率均为 $\frac{1}{4}$：

- $S = \varnothing$。此时 $f(S) = 0$，$(f(S))^2 = 0$。
- $S = \{1\}$。此时 $f(S) = 1$，$(f(S))^2 = 1$。
- $S = \{2\}$。此时 $f(S) = 2$，$(f(S))^2 = 4$。
- $S = \{1,2\}$。此时 $f(S) = 1 \oplus 2 = 3$，$(f(S))^2 = 9$。

因此，答案为 $0 \cdot \frac{1}{4} + 1 \cdot \frac{1}{4} + 4\cdot \frac{1}{4} + 9 \cdot \frac{1}{4} = \frac{14}{4} = \frac{7}{2} \equiv 500\,000\,007 \pmod{10^9 + 7}$。

在第二个测试用例中，$a = [1, 1]$，$a_1$ 被插入 $S$ 的概率为 $0.1$，而 $a_2$ 被插入 $S$ 的概率为 $0.2$。$S$ 有 $3$ 种可能的结果：

- $S = \varnothing$。此时 $f(S) = 0$，$(f(S))^2 = 0$。这种情况发生的概率为 $(1-0.1) \cdot (1-0.2) = 0.72$。
- $S = \{1\}$。此时 $f(S) = 1$，$(f(S))^2 = 1$。这种情况发生的概率为 $(1-0.1) \cdot 0.2 + 0.1 \cdot (1-0.2) = 0.26$。
- $S = \{1, 1\}$。此时 $f(S) = 0$，$(f(S))^2 = 0$。这种情况发生的概率为 $0.1 \cdot 0.2 = 0.02$。

因此，答案为 $0 \cdot 0.72 + 1 \cdot 0.26 + 0 \cdot 0.02 = 0.26 = \frac{26}{100} \equiv 820\,000\,006 \pmod{10^9 + 7}$。

**样例 #1**

### 输入

```
4
2
1 2
5000 5000
2
1 1
1000 2000
6
343 624 675 451 902 820
6536 5326 7648 2165 9430 5428
1
1
10000```

### 输出

```
500000007
820000006
280120536
1```

### 题解分析与结论

**题解1：Zeoykkk (Sol 1)**

- **星级：4星**
- **关键亮点：** 利用动态规划（DP）直接计算每个可能的异或和的概率，时间复杂度为 $O(Vn)$，其中 $V$ 是 $a[i]$ 的最大值（1023）。这种方法直观且易于理解，适合值域较小的情况。
- **代码实现：** 使用二维 DP 数组 `dp[i][j]` 表示前 $i$ 个元素插入后异或和为 $j$ 的概率，转移方程为 `dp[i][j] = p[i] * dp[i-1][j ^ a[i]] + q[i] * dp[i-1][j]`。

**题解2：Zeoykkk (Sol 2)**

- **星级：4星**
- **关键亮点：** 利用异或的性质，逐位计算期望值，时间复杂度为 $O(n \log^2 n)$。这种方法虽然复杂，但适用于更广泛的情况，尤其是当 $a[i]$ 的值域较大时。
- **代码实现：** 使用多维 DP 数组 `dp[i][j][k][0/1][0/1]` 表示前 $i$ 个元素插入后，异或和的第 $j$ 位和第 $k$ 位分别为 $0$ 或 $1$ 的概率。

**题解3：__3E24AC7002AD9292__**

- **星级：4星**
- **关键亮点：** 使用滚动数组优化空间复杂度，时间复杂度为 $O(Vn)$。代码简洁且高效，适合竞赛中的快速实现。
- **代码实现：** 使用滚动数组 `f[0][j]` 和 `f[1][j]` 来存储 DP 状态，转移方程为 `f[1][j] = (f[0][j] * (10000 - p[i]) + f[0][j ^ a[i]] * p[i]) % M`。

### 最优关键思路与技巧

- **动态规划（DP）**：利用 DP 计算每个可能的异或和的概率，适用于值域较小的情况。
- **滚动数组优化**：通过滚动数组减少空间复杂度，提高代码效率。
- **逐位计算期望值**：利用异或的性质，逐位计算期望值，适用于更广泛的情况。

### 推荐题目

1. **洛谷 P3811 【模板】乘法逆元**（题号：P3811）
2. **洛谷 P1886 滑动窗口**（题号：P1886）
3. **洛谷 P3372 【模板】线段树 1**（题号：P3372）

### 个人心得总结

- **调试经历**：在实现 DP 时，注意初始化条件和边界情况，避免出现未定义行为。
- **踩坑教训**：在使用滚动数组时，确保在每次迭代后正确更新数组状态，避免状态混淆。
- **顿悟感想**：逐位计算期望值的方法虽然复杂，但在处理大值域问题时非常有效，值得深入理解和掌握。

---
处理用时：62.64秒