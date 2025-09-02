---
title: "Combinatorics Problem"
layout: "post"
diff: 提高+/省选-
pid: CF1832E
tag: []
---

# Combinatorics Problem

## 题目描述

# 组合数学问题


回顾一下二项式系数 $ \binom{x}{y} $ 的计算方法（其中 $ x $ 和 $ y $ 是非负整数）：

- 如果 $ x < y $ ，则 $ \binom{x}{y} = 0 $ ；
- 否则，$ \binom{x}{y} = \frac{x!}{y! \cdot (x-y)!} $ 。

给定一个数组 $ a_1, a_2, \dots, a_n $ 和一个整数 $ k $ ，你需要计算一个新数组 $ b_1, b_2, \dots, b_n $ ，其中

- $ b_1 = (\binom{1}{k} \cdot a_1) \bmod 998244353 $ ；
- $ b_2 = (\binom{2}{k} \cdot a_1 + \binom{1}{k} \cdot a_2) \bmod 998244353 $ ；
- $ b_3 = (\binom{3}{k} \cdot a_1 + \binom{2}{k} \cdot a_2 + \binom{1}{k} \cdot a_3) \bmod 998244353 $ ，依此类推。

具体而言，$ b_i = (\sum\limits_{j=1}^{i} \binom{i - j + 1}{k} \cdot a_j) \bmod 998244353 $ 。

注意，数组以一种修改的方式给出，你也需要以一种修改的方式输出。

## 输入格式

输入的第一行包含六个整数 $ n $ ， $ a_1 $ ， $ x $ ， $ y $ ， $ m $ 和 $ k $ （ $ 1 \le n \le 10^7 $ ； $ 0 \le a_1, x, y < m $ ； $ 2 \le m \le 998244353 $ ； $ 1 \le k \le 5 $ ）。

数组 $ [a_1, a_2, \dots, a_n] $ 的生成方式如下：

- 输入给定了 $ a_1 $ ；
- 对于 $ 2 \le i \le n $ ， $ a_i = (a_{i-1} \cdot x + y) \bmod m $ 。

## 输出格式

由于输出最多可能有 $ 10^7 $ 个整数，可能会导致速度过慢，因此你需要进行以下处理：

设 $ c_i = b_i \cdot i $ （不在乘法后取模 $ 998244353 $ ）。输出整数 $ c_1 \oplus c_2 \oplus \dots \oplus c_n $ ，其中 $ \oplus $ 表示按位异或运算。

## 样例 #1

### 输入样例 #1

```
5 8 2 3 100 2
```

### 输出样例 #1

```
1283
```

## 样例 #1

### 输入

```
5 8 2 3 100 2
```

### 输出

```
1283
```

