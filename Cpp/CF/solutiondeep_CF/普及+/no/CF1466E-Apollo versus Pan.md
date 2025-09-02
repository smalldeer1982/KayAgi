# 题目信息

# Apollo versus Pan

## 题目描述

Only a few know that Pan and Apollo weren't only battling for the title of the GOAT musician. A few millenniums later, they also challenged each other in math (or rather in fast calculations). The task they got to solve is the following:

Let $ x_1, x_2, \ldots, x_n $ be the sequence of $ n $ non-negative integers. Find this value: $ $$$\sum_{i=1}^n \sum_{j=1}^n \sum_{k=1}^n (x_i \, \& \, x_j) \cdot (x_j \, | \, x_k) $ $ </p><p>Here  $ \\&amp; $  denotes the <a href="https://en.wikipedia.org/wiki/Bitwise_operation#AND">bitwise and,</a> and  $ | $  denotes the <a href="https://en.wikipedia.org/wiki/Bitwise_operation#OR">bitwise or.</a></p><p>Pan and Apollo could solve this in a few seconds. Can you do it too? For convenience, find the answer modulo  $ 10^9 + 7$$$.

## 样例 #1

### 输入

```
8
2
1 7
3
1 2 4
4
5 5 5 5
5
6 2 2 1 0
1
0
1
1
6
1 12 123 1234 12345 123456
5
536870912 536870911 1152921504606846975 1152921504606846974 1152921504606846973```

### 输出

```
128
91
1600
505
0
1
502811676
264880351```

# AI分析结果

### 题目翻译
只有少数人知道，潘神（Pan）和阿波罗（Apollo）的较量可不止争夺最佳音乐家的头衔。几千年后，他们还在数学（更确切地说是快速计算）领域展开了挑战。他们要解决的任务如下：

设 $x_1, x_2, \ldots, x_n$ 是由 $n$ 个非负整数组成的序列。求以下值：
$$\sum_{i=1}^n \sum_{j=1}^n \sum_{k=1}^n (x_i \, \& \, x_j) \cdot (x_j \, | \, x_k) $$
这里 $\&$ 表示[按位与](https://en.wikipedia.org/wiki/Bitwise_operation#AND)，$|$ 表示[按位或](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。

潘神和阿波罗能在几秒钟内解决这个问题。你也能做到吗？为了方便起见，请将答案对 $10^9 + 7$ 取模。

### 算法分类
位运算

### 综合分析与结论
这些题解的核心思路都是先对原式进行化简，将 $\sum_{i=1}^n \sum_{j=1}^n \sum_{k=1}^n (x_i \, \& \, x_j) \cdot (x_j \, | \, x_k)$ 化简为 $\sum_{j=1}^n (\sum_{i=1}^n (x_i \, \& \, x_j)) \cdot (\sum_{k=1}^n (x_j \, | \, x_k))$，然后利用位运算的性质拆位计算。通过预处理每一位上 $1$ 的个数，对于每个 $j$ 快速计算出 $\sum_{i=1}^n (x_i \, \& \, x_j)$ 和 $\sum_{k=1}^n (x_j \, | \, x_k)$，最后累加结果并取模。各题解的主要区别在于代码实现细节和部分变量命名，但整体思路和算法要点一致。

### 所选题解
- **do_while_true（5星）**：
    - **关键亮点**：思路清晰，详细展示了交换求和号的过程，代码规范，有自定义的快速读入函数，对取模操作处理得当。
- **lnwhl（4星）**：
    - **关键亮点**：思路简洁明了，代码结构清晰，对每一步操作有一定注释，便于理解。
- **Eibon（4星）**：
    - **关键亮点**：对按位分析的过程解释详细，代码简洁，直接实现核心逻辑。

### 重点代码
```cpp
// do_while_true 的核心代码
for(int i = 1; i <= n; ++i) {
    for(int j = 0; j <= 60; ++j)
        if((1ll << j) & a[i])
            ++sum[j];
}
for(int i = 1; i <= n; ++i) {
    ll sum1 = 0, sum2 = 0;
    for(int j = 0; j <= 60; ++j) {
        ll ss = (1ll << j) % mod;
        if((1ll << j) & a[i]) sum1 += sum[j] * ss % mod,  sum2 += n * ss % mod;
        else sum2 += sum[j] * ss % mod;
        sum1 %= mod, sum2 %= mod;
    }
    ans = (ans + sum1 * sum2 % mod) % mod;
}
```
**核心实现思想**：先预处理每一位上 $1$ 的个数存于 `sum` 数组，然后对于每个数，按位计算 $\sum_{i=1}^n (x_i \, \& \, x_j)$ 和 $\sum_{k=1}^n (x_j \, | \, x_k)$，累加到 `sum1` 和 `sum2` 中，最后将两者乘积累加到结果 `ans` 并取模。

### 关键思路或技巧
- **式子化简**：通过交换求和号将三重循环的式子化简为二重循环，降低计算复杂度。
- **拆位计算**：利用位运算的性质，将每个数拆分为二进制位，分别计算每一位的贡献，最后合并结果。
- **预处理**：预处理每一位上 $1$ 的个数，避免重复计算，提高效率。

### 拓展思路
同类型题目通常会涉及位运算的组合和化简，可能会有不同的求和式子或位运算组合。解题套路一般是先对式子进行数学化简，然后利用位运算的特点拆位计算，通过预处理减少重复计算。

### 洛谷相似题目
- [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)：涉及位运算和队列的综合应用。
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：可以通过位运算优化某些步骤。
- [P2158 [SDOI2008] 仪仗队](https://www.luogu.com.cn/problem/P2158)：需要运用数学和位运算知识解题。

### 个人心得
dead_X：“这个 E 怎么比 C 还简单啊 QAQ”，表达了对题目难度的意外感受。 

---
处理用时：33.64秒