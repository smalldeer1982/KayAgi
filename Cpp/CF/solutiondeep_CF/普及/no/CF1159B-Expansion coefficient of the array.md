# 题目信息

# Expansion coefficient of the array

## 题目描述

Let's call an array of non-negative integers $ a_1, a_2, \ldots, a_n $ a $ k $ -extension for some non-negative integer $ k $ if for all possible pairs of indices $ 1 \leq i, j \leq n $ the inequality $ k \cdot |i - j| \leq min(a_i, a_j) $ is satisfied. The expansion coefficient of the array $ a $ is the maximal integer $ k $ such that the array $ a $ is a $ k $ -extension. Any array is a 0-expansion, so the expansion coefficient always exists.

You are given an array of non-negative integers $ a_1, a_2, \ldots, a_n $ . Find its expansion coefficient.

## 说明/提示

In the first test, the expansion coefficient of the array $ [6, 4, 5, 5] $ is equal to $ 1 $ because $ |i-j| \leq min(a_i, a_j) $ , because all elements of the array satisfy $ a_i \geq 3 $ . On the other hand, this array isn't a $ 2 $ -extension, because $ 6 = 2 \cdot |1 - 4| \leq min(a_1, a_4) = 5 $ is false.

In the second test, the expansion coefficient of the array $ [0, 1, 2] $ is equal to $ 0 $ because this array is not a $ 1 $ -extension, but it is $ 0 $ -extension.

## 样例 #1

### 输入

```
4
6 4 5 5
```

### 输出

```
1```

## 样例 #2

### 输入

```
3
0 1 2
```

### 输出

```
0```

## 样例 #3

### 输入

```
4
821 500 479 717
```

### 输出

```
239```

# AI分析结果

【题目内容】
# 数组的扩展系数

## 题目描述

我们称一个非负整数数组 $a_1, a_2, \ldots, a_n$ 为 $k$ -扩展，如果对于所有可能的索引对 $1 \leq i, j \leq n$，不等式 $k \cdot |i - j| \leq \min(a_i, a_j)$ 成立。数组 $a$ 的扩展系数是使得数组 $a$ 是 $k$ -扩展的最大整数 $k$。任何数组都是 0-扩展，因此扩展系数总是存在。

给定一个非负整数数组 $a_1, a_2, \ldots, a_n$，求其扩展系数。

## 说明/提示

在第一个测试中，数组 $[6, 4, 5, 5]$ 的扩展系数为 $1$，因为 $|i-j| \leq \min(a_i, a_j)$，因为数组中的所有元素都满足 $a_i \geq 3$。另一方面，这个数组不是 $2$ -扩展，因为 $6 = 2 \cdot |1 - 4| \leq \min(a_1, a_4) = 5$ 不成立。

在第二个测试中，数组 $[0, 1, 2]$ 的扩展系数为 $0$，因为该数组不是 $1$ -扩展，但它是 $0$ -扩展。

## 样例 #1

### 输入

```
4
6 4 5 5
```

### 输出

```
1```

## 样例 #2

### 输入

```
3
0 1 2
```

### 输出

```
0```

## 样例 #3

### 输入

```
4
821 500 479 717
```

### 输出

```
239```

【算法分类】贪心

【题解分析与结论】
题目要求找到最大的 $k$，使得对于数组中的任意两个元素 $a_i$ 和 $a_j$，满足 $k \cdot |i - j| \leq \min(a_i, a_j)$。通过将不等式变形，可以得到 $k \leq \frac{\min(a_i, a_j)}{|i - j|}$。因此，问题转化为求所有 $\frac{\min(a_i, a_j)}{|i - j|}$ 的最小值。

大多数题解都采用了贪心策略，通过枚举每个元素 $a_i$，并计算其与最远点（即 $j=1$ 或 $j=n$）的 $\frac{\min(a_i, a_j)}{|i - j|}$，最终取所有结果的最小值作为答案。这种方法将时间复杂度从 $O(n^2)$ 优化到 $O(n)$，大大提高了效率。

【高星题解】

1. **作者：xu222ux (5星)**
   - **关键亮点**：通过预处理所有 $(i,j)$ 并优化到 $O(n)$，代码简洁明了，思路清晰。
   - **代码核心**：
     ```cpp
     int ans = min(a[1], a[n]) / (n - 1);
     for (int i = 2; i < n; i++) 
         ans = min(ans, min(min(a[n], a[i]) / (n - i), min(a[1], a[i]) / (i - 1)));
     ```

2. **作者：QianianXY (5星)**
   - **关键亮点**：通过贪心策略，将问题转化为求 $\frac{a_i}{|i-j|}$ 的最小值，思路清晰，代码简洁。
   - **代码核心**：
     ```cpp
     for (rei i = 1; i <= n; i++) 
         ans = min(a[i] / max(i - 1, n - i), ans);
     ```

3. **作者：szr666 (4星)**
   - **关键亮点**：通过贪心策略，找到距离当前点最远的点，简化了问题，代码实现简洁。
   - **代码核心**：
     ```cpp
     for (i = 1; i <= n; i++) 
         k = min(k, a[i] / max(i - 1, n - i));
     ```

【最优关键思路或技巧】
- **贪心策略**：通过枚举每个元素，并计算其与最远点的 $\frac{\min(a_i, a_j)}{|i - j|}$，最终取所有结果的最小值作为答案。这种方法将时间复杂度从 $O(n^2)$ 优化到 $O(n)$。
- **代码实现技巧**：使用 `min` 和 `max` 函数简化计算，避免复杂的条件判断。

【可拓展之处】
- 类似的问题可以通过贪心策略进行优化，尤其是在需要枚举所有可能对的情况下，通过寻找某些特定点来减少计算量。
- 可以考虑在更复杂的数据结构（如树状数组）中应用类似的贪心策略，以解决更复杂的问题。

【推荐题目】
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：36.70秒