# 题目信息

# [ARC158B] Sum-Product Ratio

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc158/tasks/arc158_b

$ 0 $ でない整数 $ x_1,\ \ldots,\ x_N $ が与えられます．$ i,j,k $ を $ 1\leq\ i\ <\ j\ <\ k\leq\ N $ を満たす整数とするとき，$ \dfrac{x_i+x_j+x_k}{x_ix_jx_k} $ としてありうる最小値と最大値を求めてください．

## 说明/提示

### 制約

- $ 3\leq\ N\leq\ 2\times\ 10^5 $
- $ -10^6\leq\ x_i\ \leq\ 10^6 $
- $ x_i\neq\ 0 $
 
### Sample Explanation 1

$ \dfrac{x_i+x_j+x_k}{x_ix_jx_k} $ としてありうる値は次の $ 4 $ 通りです． - $ (i,j,k)\ =\ (1,2,3) $：$ \dfrac{(-2)\ +\ (-4)\ +\ 4}{(-2)\cdot\ (-4)\cdot\ 4}\ =\ -\dfrac{1}{16} $． - $ (i,j,k)\ =\ (1,2,4) $：$ \dfrac{(-2)\ +\ (-4)\ +\ 5}{(-2)\cdot\ (-4)\cdot\ 5}\ =\ -\dfrac{1}{40} $． - $ (i,j,k)\ =\ (1,3,4) $：$ \dfrac{(-2)\ +\ 4\ +\ 5}{(-2)\cdot\ 4\cdot\ 5}\ =\ -\dfrac{7}{40} $． - $ (i,j,k)\ =\ (2,3,4) $：$ \dfrac{(-4)\ +\ 4\ +\ 5}{(-4)\cdot\ 4\cdot\ 5}\ =\ -\dfrac{1}{16} $． これらの最小値は $ -\dfrac{7}{40} $，最大値は $ -\dfrac{1}{40} $ です．

## 样例 #1

### 输入

```
4

-2 -4 4 5```

### 输出

```
-0.175000000000000

-0.025000000000000```

## 样例 #2

### 输入

```
4

1 1 1 1```

### 输出

```
3.000000000000000

3.000000000000000```

## 样例 #3

### 输入

```
5

1 2 3 4 5```

### 输出

```
0.200000000000000

1.000000000000000```

# AI分析结果

### 题目内容重写

#### [ARC158B] Sum-Product Ratio

**题目描述**

给定 $N$ 个非零整数 $x_1, x_2, \ldots, x_N$。选择满足 $1 \leq i < j < k \leq N$ 的三个整数 $i, j, k$，求 $\dfrac{x_i + x_j + x_k}{x_i x_j x_k}$ 的最小值和最大值。

**说明/提示**

**约束条件**

- $3 \leq N \leq 2 \times 10^5$
- $-10^6 \leq x_i \leq 10^6$
- $x_i \neq 0$

**样例解释**

样例 1 中，$x_i + x_j + x_k$ 与 $x_i x_j x_k$ 的比值有四种可能，最小值为 $-\dfrac{7}{40}$，最大值为 $-\dfrac{1}{40}$。

**样例输入输出**

样例 1 输入：
```
4
-2 -4 4 5
```
输出：
```
-0.175000000000000
-0.025000000000000
```

样例 2 输入：
```
4
1 1 1 1
```
输出：
```
3.000000000000000
3.000000000000000
```

样例 3 输入：
```
5
1 2 3 4 5
```
输出：
```
0.200000000000000
1.000000000000000
```

### 题解分析与结论

#### 综合分析

本题的核心在于如何高效地找到 $\dfrac{x_i + x_j + x_k}{x_i x_j x_k}$ 的最小值和最大值。由于 $N$ 的范围较大（$2 \times 10^5$），直接枚举所有三元组显然不可行。因此，大多数题解都采用了“极值法”，即通过排序后选取极值来缩小搜索范围。

#### 关键思路与技巧

1. **极值法**：通过排序后选取正数、负数的极值（最大、最小等），从而将问题规模缩小到可接受的范围。
2. **数学变形**：部分题解通过数学变形，将原式转化为更易处理的形式，如 $\frac{1}{x_i x_j} + \frac{1}{x_i x_k} + \frac{1}{x_j x_k}$，从而简化计算。
3. **前缀和后缀优化**：通过预处理前缀和后缀的最大最小值，进一步优化计算过程。

#### 最优题解推荐

1. **作者：_•́へ•́╬_**  
   **星级：5**  
   **关键亮点**：通过排序后选取极值，将问题规模缩小到 12 个数，极大减少了计算量。代码简洁高效，适合大规模数据处理。  
   **代码核心**：
   ```cpp
   sort(x, x+n);
   int i = lower_bound(x, x+n, 0) - x;
   if (i <= 6) for (int j = 0; j < i; a.emplace_back(x[j++]));
   else a.emplace_back(x[0]), a.emplace_back(x[1]), a.emplace_back(x[2]),
        a.emplace_back(x[i-3]), a.emplace_back(x[i-2]), a.emplace_back(x[i-1]);
   if (n-i <= 6) for (int j = i; j < n; a.emplace_back(x[j++]));
   else a.emplace_back(x[i]), a.emplace_back(x[i+1]), a.emplace_back(x[i+2]),
        a.emplace_back(x[n-3]), a.emplace_back(x[n-2]), a.emplace_back(x[n-1]);
   ```

2. **作者：sanaka87**  
   **星级：4**  
   **关键亮点**：通过数学变形和前缀后缀优化，将时间复杂度降低到 $O(n)$，适合大规模数据处理。  
   **代码核心**：
   ```cpp
   for (int i = 1; i <= n; i++) {
       pmi[i] = fmin(pmi[i-1], 1./a[i]);
       pma[i] = fmax(pma[i-1], 1./a[i]);
   }
   for (int i = n; i; i--) {
       smi[i] = fmin(smi[i+1], 1./a[i]);
       sma[i] = fmax(sma[i+1], 1./a[i]);
   }
   ```

3. **作者：iiiiiyang**  
   **星级：4**  
   **关键亮点**：通过数学变形和排序，将问题转化为极值问题，代码简洁且思路清晰。  
   **代码核心**：
   ```cpp
   sort(num + 1, num + 1 + n, [](double x, double y) {
       return 1/x < 1/y;
   });
   minx = inf, maxx = -inf;
   cmin(minx, func(num[1], num[2], num[3])), cmin(minx, func(num[1], num[2], num[n])),
   cmin(minx, func(num[1], num[n-1], num[n])), cmin(minx, func(num[n-2], num[n-1], num[n]));
   cmax(maxx, func(num[1], num[2], num[3])), cmax(maxx, func(num[1], num[2], num[n])),
   cmax(maxx, func(num[1], num[n-1], num[n])), cmax(maxx, func(num[n-2], num[n-1], num[n]));
   ```

### 推荐题目

1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

这些题目都涉及到极值处理和优化策略，适合进一步巩固相关算法技巧。

---
处理用时：44.26秒