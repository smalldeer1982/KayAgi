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
#### [ABC378E] Mod Sigma Problem

**题目描述**

给定一个长度为 $N$ 的非负整数序列 $A = (A_1, A_2, \dots, A_N)$ 和一个正整数 $M$，求以下值：

$$
\sum_{1 \leq l \leq r \leq N} \left( \left(\sum_{l \leq i \leq r} A_i\right) \mathbin{\mathrm{mod}} M \right).
$$

其中，$X \mathbin{\mathrm{mod}} M$ 表示非负整数 $X$ 除以 $M$ 的余数。

**说明/提示**

**约束条件**

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq M \leq 2 \times 10^5$
- $0 \leq A_i \leq 10^9$

**样例解释 1**

- $A_1 \mathbin{\mathrm{mod}} M = 2$
- $(A_1+A_2) \mathbin{\mathrm{mod}} M = 3$
- $(A_1+A_2+A_3) \mathbin{\mathrm{mod}} M = 3$
- $A_2 \mathbin{\mathrm{mod}} M = 1$
- $(A_2+A_3) \mathbin{\mathrm{mod}} M = 1$
- $A_3 \mathbin{\mathrm{mod}} M = 0$

最终答案为这些值的和，即 $10$。注意，外层的求和不需要对 $M$ 取模。

**样例 #1**

**输入**

```
3 4

2 5 0
```

**输出**

```
10
```

**样例 #2**

**输入**

```
10 100

320 578 244 604 145 839 156 857 556 400
```

**输出**

```
2736
```

### 题解综合分析与结论

本题的核心在于如何高效计算所有子区间和的模 $M$ 的总和。由于直接暴力计算的复杂度为 $O(N^2)$，无法通过 $N \leq 2 \times 10^5$ 的数据规模。因此，需要利用前缀和和树状数组等数据结构进行优化。

大多数题解采用了以下思路：
1. **前缀和优化**：通过前缀和将区间和转化为前缀和的差值，即 $(sum_r - sum_{l-1}) \bmod M$。
2. **分类讨论**：根据 $sum_r$ 和 $sum_{l-1}$ 的大小关系，将结果分为两种情况：$sum_r - sum_{l-1}$ 或 $sum_r - sum_{l-1} + M$。
3. **树状数组维护**：使用树状数组统计 $sum_{l-1} > sum_r$ 的情况，从而计算需要补偿的 $M$ 的个数。

### 所选高质量题解

#### 1. 作者：fishing_cat (赞：9)  
**星级：5星**  
**关键亮点**：  
- 通过前缀和将问题转化为逆序对问题，使用树状数组高效统计逆序对个数。
- 详细推导了公式，并给出了清晰的代码实现。

**个人心得**：  
- 作者提到“每出现一次负数才会有一次加 $M$，而负数是因为出现了 $qzh_i > qzh_j$”，这种思路清晰且易于理解。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    add(rk[i], 1);
    num += i - ask(rk[i]);
}
```
**核心思想**：通过树状数组统计逆序对个数，从而计算需要补偿的 $M$ 的个数。

#### 2. 作者：yzljy (赞：3)  
**星级：4星**  
**关键亮点**：  
- 使用两个树状数组分别维护值的和与值的个数，优化了统计过程。
- 通过枚举右端点，统计左端点的贡献，思路清晰。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    int z = val[i] + 1;
    ans += cnt.query(z) * (z) - t.query(z);
    ans += (cnt.query(2e5) - cnt.query(z)) * (m + z) - (t.query(2e5) - t.query(z));
    t.update(z, z);
    cnt.update(z, 1);
}
```
**核心思想**：通过树状数组维护值的和与个数，分别统计不同情况下的贡献。

#### 3. 作者：MLE_Automaton (赞：3)  
**星级：4星**  
**关键亮点**：  
- 通过树状数组维护前缀和的逆序对，优化了统计过程。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    ans += a[i] * i - s + (i - 1 - sum(a[i] + 1)) * m;
    add(a[i] + 1, 1); s += a[i];
}
```
**核心思想**：通过树状数组统计逆序对个数，从而计算需要补偿的 $M$ 的个数。

### 最优关键思路与技巧

1. **前缀和优化**：将区间和转化为前缀和的差值，减少计算复杂度。
2. **分类讨论**：根据 $sum_r$ 和 $sum_{l-1}$ 的大小关系，将结果分为两种情况，避免负数问题。
3. **树状数组维护**：使用树状数组高效统计逆序对个数，从而计算需要补偿的 $M$ 的个数。

### 可拓展之处

- **类似问题**：其他需要统计区间和的问题，如区间和的平方和、区间和的最大值等，都可以借鉴前缀和和树状数组的思路。
- **数据结构优化**：在需要高效统计逆序对或区间贡献的问题中，树状数组和线段树是常用的数据结构。

### 推荐题目

1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P3374 树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3368 树状数组 2](https://www.luogu.com.cn/problem/P3368)

---
处理用时：52.99秒