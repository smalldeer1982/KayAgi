# 题目信息

# [ABC249D] Index Trio

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc249/tasks/abc249_d

長さ $ N $ の整数列 $ A\ =\ (A_1,\ \dots,\ A_N) $ が与えられます。

以下の条件を全て満たす整数の組 $ (i,\ j,\ k) $ の総数を求めてください。

- $ 1\ \leq\ i,\ j,\ k\ \leq\ N $
- $ \frac{A_i}{A_j}\ =\ A_k $

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 2\ \times\ 10^5\ \,\ (1\ \leq\ i\ \leq\ N) $
- 入力は全て整数

### Sample Explanation 1

$ (i,\ j,\ k)\ =\ (1,\ 2,\ 3),\ (1,\ 3,\ 2) $ が条件を満たします。

## 样例 #1

### 输入

```
3
6 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
1
2```

### 输出

```
0```

## 样例 #3

### 输入

```
10
1 3 2 4 6 8 2 2 3 7```

### 输出

```
62```

# AI分析结果



# [ABC249D] Index Trio 题解

## 题目翻译
给定一个长度为 $N$ 的整数序列 $A$，求满足以下条件的三元组 $(i, j, k)$ 的数量：
- $1 \leq i, j, k \leq N$
- $\frac{A_i}{A_j} = A_k$

**输入格式**  
第一行输入整数 $N$，第二行输入 $N$ 个整数 $A_1, \dots, A_N$。

**约束条件**  
- $1 \leq N \leq 2 \times 10^5$
- $1 \leq A_i \leq 2 \times 10^5$

## 算法分类
数学、枚举

## 题解分析

### 关键思路
将原式变形为 $A_i = A_j \times A_k$，通过桶计数统计每个数值出现次数。枚举所有可能的 $A_j$ 和 $A_k$ 的组合，若其乘积存在于桶中，则累加对应出现次数的乘积。

### 解决难点
- **数值范围优化**：通过限制 $A_j \times A_k \leq 2 \times 10^5$ 避免无效计算
- **桶计数加速**：用数组替代哈希表实现 $O(1)$ 查询
- **复杂度控制**：双重循环的枚举次数为调和级数级别 $O(M \log M)$，其中 $M = 2 \times 10^5$

### 精选题解

#### Tsawke（⭐⭐⭐⭐⭐）
**核心亮点**  
- 清晰的埃式筛法复杂度分析
- 完整的代码框架与输入处理
- 强调 `long long` 类型防溢出

**关键代码**
```cpp
for(int i = 1; i <= MAX; ++i)
    for(int j = 1; i * j <= MAX; ++j)
        ans += (ll)buc[i] * buc[j] * buc[i * j];
```

#### 作者：_qingshu_（⭐⭐⭐⭐）
**核心亮点**  
- 直观的桶计数实现
- 剪枝优化思路明确
- 代码极简无冗余

**关键代码**
```cpp
for(int i=1;i<=200000;i++)
    for(int j=1;i*j<=200000;j++)
        ans += ton[i] * ton[j] * ton[i*j];
```

#### TLEWA（⭐⭐⭐⭐）
**核心亮点**  
- 循环步长优化（j += i）
- 简洁的条件判断处理
- 强调数值范围限制

**关键代码**
```cpp
for(int i=1;i<=maxn;++i)
    for(int j=i;j<=maxn;j+=i)
        ans += t[i] * t[j] * t[j/i];
```

## 拓展练习
1. [CF1398C - Good Subarrays](https://codeforces.com/problemset/problem/1398/C)（前缀和+哈希）
2. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)（桶计数变形）
3. [ABC179D - Leaping Tak](https://atcoder.jp/contests/abc179/tasks/abc179_d)（动态规划+前缀和优化）

---
处理用时：64.65秒