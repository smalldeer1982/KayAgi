# 题目信息

# Permutation Partitions

## 题目描述

You are given a permutation $ p_1, p_2, \ldots, p_n $ of integers from $ 1 $ to $ n $ and an integer $ k $ , such that $ 1 \leq k \leq n $ . A permutation means that every number from $ 1 $ to $ n $ is contained in $ p $ exactly once.

Let's consider all partitions of this permutation into $ k $ disjoint segments. Formally, a partition is a set of segments $ \{[l_1, r_1], [l_2, r_2], \ldots, [l_k, r_k]\} $ , such that:

- $ 1 \leq l_i \leq r_i \leq n $ for all $ 1 \leq i \leq k $ ;
- For all $ 1 \leq j \leq n $ there exists exactly one segment $ [l_i, r_i] $ , such that $ l_i \leq j \leq r_i $ .

Two partitions are different if there exists a segment that lies in one partition but not the other.

Let's calculate the partition value, defined as $ \sum\limits_{i=1}^{k} {\max\limits_{l_i \leq j \leq r_i} {p_j}} $ , for all possible partitions of the permutation into $ k $ disjoint segments. Find the maximum possible partition value over all such partitions, and the number of partitions with this value. As the second value can be very large, you should find its remainder when divided by $ 998\,244\,353 $ .

## 说明/提示

In the first test, for $ k = 2 $ , there exists only two valid partitions: $ \{[1, 1], [2, 3]\} $ and $ \{[1, 2], [3, 3]\} $ . For each partition, the partition value is equal to $ 2 + 3 = 5 $ . So, the maximum possible value is $ 5 $ and the number of partitions is $ 2 $ .

In the third test, for $ k = 3 $ , the partitions with the maximum possible partition value are $ \{[1, 2], [3, 5], [6, 7]\} $ , $ \{[1, 3], [4, 5], [6, 7]\} $ , $ \{[1, 4], [5, 5], [6, 7]\} $ , $ \{[1, 2], [3, 6], [7, 7]\} $ , $ \{[1, 3], [4, 6], [7, 7]\} $ , $ \{[1, 4], [5, 6], [7, 7]\} $ . For all of them, the partition value is equal to $ 7 + 5 + 6 = 18 $ .

The partition $ \{[1, 2], [3, 4], [5, 7]\} $ , however, has the partition value $ 7 + 3 + 6 = 16 $ . This is not the maximum possible value, so we don't count it.

## 样例 #1

### 输入

```
3 2
2 1 3```

### 输出

```
5 2```

## 样例 #2

### 输入

```
5 5
2 1 5 3 4```

### 输出

```
15 1```

## 样例 #3

### 输入

```
7 3
2 7 3 1 5 4 6```

### 输出

```
18 6```

# AI分析结果

### 题目翻译

#### 题目描述

给定一个从 $1$ 到 $n$ 的整数排列 $p_1, p_2, \ldots, p_n$ 和一个整数 $k$，其中 $1 \leq k \leq n$。排列意味着 $p$ 中每个从 $1$ 到 $n$ 的数恰好出现一次。

考虑将这个排列划分为 $k$ 个不相交的段。形式上，一个划分是一个段的集合 $\{[l_1, r_1], [l_2, r_2], \ldots, [l_k, r_k]\}$，满足：

- 对于所有 $1 \leq i \leq k$，有 $1 \leq l_i \leq r_i \leq n$；
- 对于所有 $1 \leq j \leq n$，存在恰好一个段 $[l_i, r_i]$，使得 $l_i \leq j \leq r_i$。

如果存在一个段在一个划分中但不在另一个划分中，则这两个划分不同。

定义划分的值为 $\sum\limits_{i=1}^{k} {\max\limits_{l_i \leq j \leq r_i} {p_j}}$，即每个段的最大值之和。找出所有可能的划分中，划分值的最大值，以及达到该最大值的划分数量。由于第二个值可能非常大，输出其对 $998\,244\,353$ 取模的结果。

#### 说明/提示

在第一个测试样例中，对于 $k = 2$，只有两个有效的划分：$ \{[1, 1], [2, 3]\} $ 和 $ \{[1, 2], [3, 3]\} $。每个划分的划分值都是 $2 + 3 = 5$。因此，最大可能的划分值是 $5$，划分数量是 $2$。

在第三个测试样例中，对于 $k = 3$，达到最大划分值的划分有多个，例如 $ \{[1, 2], [3, 5], [6, 7]\} $，$ \{[1, 3], [4, 5], [6, 7]\} $，$ \{[1, 4], [5, 5], [6, 7]\} $，$ \{[1, 2], [3, 6], [7, 7]\} $，$ \{[1, 3], [4, 6], [7, 7]\} $，$ \{[1, 4], [5, 6], [7, 7]\} $。对于所有这些划分，划分值都是 $7 + 5 + 6 = 18$。

而划分 $ \{[1, 2], [3, 4], [5, 7]\} $ 的划分值是 $7 + 3 + 6 = 16$，这不是最大值，因此不计入。

#### 样例 #1

##### 输入

```
3 2
2 1 3
```

##### 输出

```
5 2
```

#### 样例 #2

##### 输入

```
5 5
2 1 5 3 4
```

##### 输出

```
15 1
```

#### 样例 #3

##### 输入

```
7 3
2 7 3 1 5 4 6
```

##### 输出

```
18 6
```

### 算法分类
贪心、组合数学

### 题解分析与结论

本题的核心在于如何将排列划分为 $k$ 个段，使得每个段的最大值之和最大，并计算达到该最大值的划分数量。所有题解都采用了贪心策略，即选择排列中前 $k$ 大的数作为每个段的最大值，从而最大化划分值。对于划分数量的计算，题解们均采用了乘法原理，通过计算相邻最大值之间的位置差来得到划分方案数。

### 精选题解

#### 题解1：do_while_true (5星)
**关键亮点**：
- 清晰地解释了贪心策略，并详细说明了如何通过排序和乘法原理计算划分数量。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
for(int i=1;i<=k;i++){
    ans1+=b[i].dis;
    c[i]=b[i].pos;
}
sort(c+1,c+k+1);
for(int i=2;i<=k;i++)
    ans2=ans2*(c[i]-c[i-1])%998244353;
```

#### 题解2：xht (5星)
**关键亮点**：
- 直接指出最大值的选择，并简洁地解释了如何通过位置差计算划分数量。
- 代码简洁，使用了`modint`类来处理模运算，增强了代码的可读性。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++)
    if (a[i] > n - k) p.pb(i);
for (ui i = 1; i < p.size(); i++)
    Ans *= p[i] - p[i-1];
```

#### 题解3：AutumnKite (4星)
**关键亮点**：
- 详细解释了贪心策略，并通过标记最大值的位置来计算划分数量。
- 代码逻辑清晰，易于理解。

**核心代码**：
```cpp
if (a[i] > n - k){
    sum += a[i];
    if (lst) ans = 1ll * ans * (i - lst) % P;
    lst = i;
}
```

### 最优关键思路
- **贪心策略**：选择排列中前 $k$ 大的数作为每个段的最大值，从而最大化划分值。
- **乘法原理**：通过计算相邻最大值之间的位置差，得到划分方案数。

### 可拓展之处
- 类似的问题可以扩展到其他类型的序列划分，如最小化划分值或最大化其他函数值。
- 可以结合动态规划或其他优化算法来处理更复杂的划分问题。

### 推荐题目
1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1040 [NOIP2003 提高组] 加分二叉树](https://www.luogu.com.cn/problem/P1040)
3. [P1063 [NOIP2006 提高组] 能量项链](https://www.luogu.com.cn/problem/P1063)

---
处理用时：41.15秒