# 题目信息

# Cyclic Permutations

## 题目描述

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

Consider a permutation $ p $ of length $ n $ , we build a graph of size $ n $ using it as follows:

- For every $ 1 \leq i \leq n $ , find the largest $ j $ such that $ 1         \leq j < i $ and $ p_j > p_i $ , and add an undirected edge between node $ i $ and node $ j $
- For every $ 1 \leq i \leq n $ , find the smallest $ j $ such that $ i         < j \leq n $ and $ p_j > p_i $ , and add an undirected edge between node $ i $ and node $ j $

In cases where no such $ j $ exists, we make no edges. Also, note that we make edges between the corresponding indices, not the values at those indices.

For clarity, consider as an example $ n = 4 $ , and $ p =       [3,1,4,2] $ ; here, the edges of the graph are $ (1,3),(2,1),(2,3),(4,3) $ .

A permutation $ p $ is cyclic if the graph built using $ p $ has at least one simple cycle.

Given $ n $ , find the number of cyclic permutations of length $ n $ . Since the number may be very large, output it modulo $ 10^9+7 $ .

Please refer to the Notes section for the formal definition of a simple cycle

## 说明/提示

There are $ 16 $ cyclic permutations for $ n = 4 $ . $ [4,2,1,3] $ is one such permutation, having a cycle of length four: $ 4 \rightarrow 3 \rightarrow 2 \rightarrow 1 \rightarrow 4 $ .

Nodes $ v_1 $ , $ v_2 $ , $ \ldots $ , $ v_k $ form a simple cycle if the following conditions hold:

- $ k \geq 3 $ .
- $ v_i \neq v_j $ for any pair of indices $ i $ and $ j $ . ( $ 1 \leq i < j \leq k $ )
- $ v_i $ and $ v_{i+1} $ share an edge for all $ i $ ( $ 1 \leq i < k $ ), and $ v_1 $ and $ v_k $ share an edge.

## 样例 #1

### 输入

```
4```

### 输出

```
16```

## 样例 #2

### 输入

```
583291```

### 输出

```
135712853```

# AI分析结果

### 题目重写
#### 题目描述
一个长度为 $n$ 的排列是一个由 $1$ 到 $n$ 的 $n$ 个不同整数组成的数组，顺序任意。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（$2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（$n=3$ 但数组中出现了 $4$）。

考虑一个长度为 $n$ 的排列 $p$，我们根据它构建一个大小为 $n$ 的图，规则如下：

- 对于每个 $1 \leq i \leq n$，找到最大的 $j$ 使得 $1 \leq j < i$ 且 $p_j > p_i$，并在节点 $i$ 和节点 $j$ 之间添加一条无向边。
- 对于每个 $1 \leq i \leq n$，找到最小的 $j$ 使得 $i < j \leq n$ 且 $p_j > p_i$，并在节点 $i$ 和节点 $j$ 之间添加一条无向边。

如果不存在这样的 $j$，则不添加边。注意，我们是在对应的索引之间添加边，而不是这些索引处的值。

例如，当 $n = 4$，$p = [3,1,4,2]$ 时，图的边为 $(1,3),(2,1),(2,3),(4,3)$。

一个排列 $p$ 是**循环的**，如果根据 $p$ 构建的图至少包含一个简单环。

给定 $n$，求长度为 $n$ 的循环排列的数量。由于答案可能非常大，输出其对 $10^9+7$ 取模的结果。

#### 说明/提示
对于 $n = 4$，有 $16$ 个循环排列。$[4,2,1,3]$ 是其中一个，它包含一个长度为 $4$ 的环：$4 \rightarrow 3 \rightarrow 2 \rightarrow 1 \rightarrow 4$。

节点 $v_1, v_2, \ldots, v_k$ 形成一个简单环，当且仅当满足以下条件：

1. $k \geq 3$。
2. 对于任意 $i$ 和 $j$，$v_i \neq v_j$（$1 \leq i < j \leq k$）。
3. $v_i$ 和 $v_{i+1}$ 之间有一条边（$1 \leq i < k$），且 $v_1$ 和 $v_k$ 之间有一条边。

#### 样例 #1
##### 输入
```
4
```
##### 输出
```
16
```

#### 样例 #2
##### 输入
```
583291
```
##### 输出
```
135712853
```

### 算法分类
组合数学

### 题解分析与结论
本题的核心在于理解排列的循环性质与图的构建规则。通过分析，可以发现循环排列与“单峰排列”之间的关系。大多数题解通过“正难则反”的思路，先计算非循环排列的数量，再用总排列数减去非循环排列数，得到循环排列的数量。

非循环排列的特点是排列中没有“谷”，即排列是单峰的（先递增后递减）。通过组合数学的方法，可以得出非循环排列的数量为 $2^{n-1}$，而总排列数为 $n!$，因此循环排列的数量为 $n! - 2^{n-1}$。

### 所选题解
#### 题解1：寒鸽儿
**星级：5星**
**关键亮点：**
1. 详细证明了非单峰排列与循环排列的关系。
2. 通过组合数学推导出非循环排列的数量为 $2^{n-1}$。
3. 代码简洁且高效，直接计算 $n!$ 和 $2^{n-1}$ 并取模。

**个人心得：**
“通过对于顺序数据及小数据的枚举不难发现，如果是一个单峰或者单调的排列，那么就没有环，否则一定有。”

**代码核心实现：**
```cpp
ll gen(int n) {
    ll ans = 1, dd = 1;
    for(int i = 1; i <= n; ++i) ans = ans * i % p;
    for(int i = 1; i < n; ++i) dd = dd * 2 % p;
    return ((ans - dd) % p + p) % p;
}
```

#### 题解2：引领天下
**星级：4星**
**关键亮点：**
1. 通过观察排列的性质，直接得出非循环排列的数量为 $2^{n-1}$。
2. 代码简洁，直接计算 $n!$ 和 $2^{n-1}$ 并取模。

**代码核心实现：**
```cpp
register long long ans=1,res=1;
for (register int i=1;i<=n;i++)ans=1ll*ans*i%mod;
for (register int i=2;i<=n;i++)res=(res<<1)%mod;
ans=(ans+mod-res)%mod;
```

#### 题解3：tengkaize
**星级：4星**
**关键亮点：**
1. 通过分析排列的“山谷”性质，得出循环排列的数量为 $n! - 2^{n-1}$。
2. 代码简洁，直接计算 $n!$ 和 $2^{n-1}$ 并取模。

**代码核心实现：**
```cpp
for (ll i = 1; i <= n; ++i) {
    fact[i] = fact[i - 1] * i % MOD;
    p2[i] = p2[i - 1] * 2 % MOD;
}
printf("%lld\n", ((fact[n] - p2[n - 1]) % MOD + MOD) % MOD);
```

### 最优关键思路或技巧
1. **正难则反**：通过计算非循环排列的数量，再用总排列数减去非循环排列数，得到循环排列的数量。
2. **组合数学**：利用组合数学中的二项式定理，得出非循环排列的数量为 $2^{n-1}$。
3. **模运算优化**：在计算 $n!$ 和 $2^{n-1}$ 时，及时取模，避免溢出。

### 可拓展之处
1. **类似题型**：可以拓展到其他排列相关的图论问题，如排列的连通性、排列的环数等。
2. **组合数学应用**：在排列组合问题中，常常需要用到组合数学的知识，如二项式定理、容斥原理等。

### 推荐题目
1. [P3197 [HNOI2008]越狱](https://www.luogu.com.cn/problem/P3197)
2. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
3. [P1044 栈](https://www.luogu.com.cn/problem/P1044)

---
处理用时：45.09秒