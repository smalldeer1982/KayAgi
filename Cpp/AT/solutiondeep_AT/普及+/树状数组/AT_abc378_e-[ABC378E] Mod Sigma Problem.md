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

### 题目翻译
#### [ABC378E] Mod Sigma Problem

**题目描述**

给定一个长度为 $N$ 的非负整数序列 $A = (A_1, A_2, \dots, A_N)$，以及一个正整数 $M$。求以下表达式的值：

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

最终答案为这些值的和，即 $10$。注意，外层的求和结果不需要对 $M$ 取模。

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

---

### 题解分析与结论

#### 综合分析
该题的核心在于如何高效计算所有子区间和的模 $M$ 值之和。由于直接暴力计算的复杂度为 $O(N^2)$，无法通过 $N \leq 2 \times 10^5$ 的约束条件，因此需要优化。

大多数题解采用了前缀和与树状数组或线段树结合的思路，通过统计逆序对或维护值域信息来优化计算。部分题解还使用了分治或权值线段树等数据结构来进一步优化。

#### 最优关键思路
1. **前缀和与模运算**：通过前缀和将子区间和转化为前缀和之差，再利用模运算的性质进行分类讨论。
2. **树状数组/线段树**：用于统计逆序对或维护值域信息，优化计算过程。
3. **分治策略**：将问题分解为左右两部分，分别计算后再合并结果，适用于大规模数据处理。

#### 推荐题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P3368 树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3374 树状数组 1](https://www.luogu.com.cn/problem/P3374)

#### 个人心得摘录
- **调试经历**：部分题解提到在调试过程中遇到负数问题，通过加 $M$ 来修正。
- **踩坑教训**：注意树状数组下标从 $1$ 开始，避免死循环。
- **顿悟感想**：通过分类讨论和数据结构优化，成功将复杂度从 $O(N^2)$ 降低到 $O(N \log N)$。

---

### 高星题解精选

#### 题解1：作者：fishing_cat (赞：9)
**星级：★★★★★**
**关键亮点**：
- 使用前缀和与树状数组结合，统计逆序对个数，优化计算过程。
- 通过分类讨论，将问题转化为逆序对问题，思路清晰。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    ans += (2*i - n) * qzh[i].vel;
    add(rk[i], 1);
    num += i - ask(rk[i]);
}
printf("%lld", ans + num*m);
```
**实现思想**：通过树状数组统计逆序对个数，并在计算过程中动态维护前缀和。

---

#### 题解2：作者：yzljy (赞：3)
**星级：★★★★☆**
**关键亮点**：
- 使用树状数组维护值域信息，优化统计过程。
- 通过枚举右端点，统计左端点的贡献，思路清晰。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    ans += cnt.query(z) * (z) - t.query(z);
    ans += (cnt.query(2e5) - cnt.query(z)) * (m + z) - (t.query(2e5) - t.query(z));
    t.update(z, z);
    cnt.update(z, 1);
}
```
**实现思想**：通过树状数组维护值域信息，动态统计左端点的贡献。

---

#### 题解3：作者：MLE_Automaton (赞：3)
**星级：★★★★☆**
**关键亮点**：
- 使用树状数组维护前缀和的模 $M$ 值，优化统计过程。
- 通过分类讨论，将问题转化为逆序对问题，思路清晰。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    ans += a[i] * i - s + (i - 1 - sum(a[i] + 1)) * m;
    add(a[i] + 1, 1); s += a[i];
}
```
**实现思想**：通过树状数组维护前缀和的模 $M$ 值，动态统计逆序对个数。

---
处理用时：50.22秒