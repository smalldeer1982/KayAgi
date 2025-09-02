# 题目信息

# [ABC378E] Mod Sigma Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc378/tasks/abc378_e

You are given a sequence $A = (A_1, A_2, \dots, A_N)$ of $N$ non-negative integers, and a positive integer $M$.

Find the following value:

$$
 \sum_{1 \leq l \leq r \leq N} \left( \left(\sum_{l \leq i \leq r} A_i\right) \mathbin{\mathrm{mod}} M \right). 
$$

Here, $X \mathbin{\mathrm{mod}} M$ denotes the remainder when the non-negative integer $X$ is divided by $M$.

## 说明/提示

### 制約

### Constraints

-   $1 \leq N \leq 2 \times 10^5$
-   $1 \leq M \leq 2 \times 10^5$
-   $0 \leq A_i \leq 10^9$
 
### Sample Explanation 1

-   $A_1 \mathbin{\mathrm{mod}} M = 2$
-   $(A_1+A_2) \mathbin{\mathrm{mod}} M = 3$
-   $(A_1+A_2+A_3) \mathbin{\mathrm{mod}} M = 3$
-   $A_2 \mathbin{\mathrm{mod}} M = 1$
-   $(A_2+A_3) \mathbin{\mathrm{mod}} M = 1$
-   $A_3 \mathbin{\mathrm{mod}} M = 0$

The answer is the sum of these values, $10$. Note that the outer sum is not taken modulo $M$.

## 样例 #1

### 输入

```
3 4

2 5 0```

### 输出

```
10```

## 样例 #2

### 输入

```
10 100

320 578 244 604 145 839 156 857 556 400```

### 输出

```
2736```

# AI分析结果

### 题目内容重写
#### 题目描述
给定一个长度为 $N$ 的非负整数序列 $A = (A_1, A_2, \dots, A_N)$ 和一个正整数 $M$，求以下值：

$$
\sum_{1 \leq l \leq r \leq N} \left( \left(\sum_{l \leq i \leq r} A_i\right) \mathbin{\mathrm{mod}} M \right)
$$

其中，$X \mathbin{\mathrm{mod}} M$ 表示非负整数 $X$ 除以 $M$ 的余数。

#### 说明/提示
##### 约束条件
- $1 \leq N \leq 2 \times 10^5$
- $1 \leq M \leq 2 \times 10^5$
- $0 \leq A_i \leq 10^9$

##### 样例解释 1
- $A_1 \mathbin{\mathrm{mod}} M = 2$
- $(A_1+A_2) \mathbin{\mathrm{mod}} M = 3$
- $(A_1+A_2+A_3) \mathbin{\mathrm{mod}} M = 3$
- $A_2 \mathbin{\mathrm{mod}} M = 1$
- $(A_2+A_3) \mathbin{\mathrm{mod}} M = 1$
- $A_3 \mathbin{\mathrm{mod}} M = 0$

答案为这些值的和，即 $10$。注意，外层的求和结果不需要对 $M$ 取模。

##### 样例 #1
###### 输入
```
3 4
2 5 0
```
###### 输出
```
10
```

##### 样例 #2
###### 输入
```
10 100
320 578 244 604 145 839 156 857 556 400
```
###### 输出
```
2736
```

### 题解综合分析与结论
该题的核心在于如何高效计算所有子区间和模 $M$ 的总和。由于直接暴力计算的时间复杂度为 $O(N^2)$，无法通过 $N \leq 2 \times 10^5$ 的数据规模。因此，大多数题解都采用了前缀和结合树状数组或线段树的方式来优化计算。

#### 关键思路与技巧
1. **前缀和与模运算**：通过前缀和将区间和转化为两个前缀和的差，再利用模运算的性质进行分类讨论。
2. **树状数组/线段树**：用于统计前缀和模 $M$ 的逆序对数量，从而快速计算需要补偿的 $M$ 的数量。
3. **分类讨论**：根据前缀和模 $M$ 的大小关系，将区间和分为两种情况，分别计算贡献。

#### 推荐题解
1. **作者：fishing_cat**  
   - **星级：5星**  
   - **关键亮点**：思路清晰，详细解释了如何通过前缀和和逆序对数量来优化计算，代码实现简洁高效。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= n; i++) {
         ans += (2*i - n) * qzh[i].vel;
     }
     sort(qzh+1, qzh+n+1, cmp);
     for (int i = 1; i <= n; i++) {
         rk[qzh[i].it] = i;
     }
     for (int i = 1; i <= n; i++) {
         add(rk[i], 1);
         num += i - ask(rk[i]);
     }
     printf("%lld", ans + num*m);
     ```
   - **个人心得**：通过逆序对的数量来补偿 $M$ 的贡献，避免了直接计算负数的情况。

2. **作者：yzljy**  
   - **星级：4星**  
   - **关键亮点**：使用树状数组优化了统计过程，代码结构清晰，易于理解。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= n; i++) {
         int z = val[i] + 1;
         ans += cnt.query(z) * (z) - t.query(z);
         ans += (cnt.query(2e5) - cnt.query(z)) * (m + z) - (t.query(2e5) - t.query(z));
         t.update(z, z);
         cnt.update(z, 1);
     }
     ```
   - **个人心得**：通过树状数组维护前缀和模 $M$ 的统计，避免了暴力计算。

3. **作者：MLE_Automaton**  
   - **星级：4星**  
   - **关键亮点**：通过树状数组维护前缀和模 $M$ 的逆序对数量，代码简洁，思路清晰。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= n; i++) {
         ans += a[i] * i - s + (i - 1 - sum(a[i] + 1)) * m;
         add(a[i] + 1, 1); s += a[i];
     }
     ```
   - **个人心得**：通过树状数组统计逆序对数量，避免了直接计算负数的情况。

### 拓展思路与类似题目
1. **类似题目**：
   - [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：统计逆序对数量，与本题中的逆序对统计类似。
   - [P3374 树状数组 1](https://www.luogu.com.cn/problem/P3374)：树状数组的基本应用，与本题中的树状数组使用类似。
   - [P3368 树状数组 2](https://www.luogu.com.cn/problem/P3368)：树状数组的区间修改与单点查询，与本题中的树状数组使用类似。

2. **拓展思路**：
   - 可以进一步优化树状数组的实现，例如使用离散化来减少空间复杂度。
   - 可以考虑使用其他数据结构如线段树或平衡树来替代树状数组，以适应不同的需求。

---
处理用时：51.80秒