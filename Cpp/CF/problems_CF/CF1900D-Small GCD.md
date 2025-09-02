---
title: "Small GCD"
layout: "post"
diff: 普及+/提高
pid: CF1900D
tag: []
---

# Small GCD

## 题目描述

$ a, b, c $ 为整数，定义 $ f(a, b, c) $ 如下:

将三个数排序，使得 $ a \le b \le c $。则函数返回 $ \gcd(a, b) $ , 这里 $ \gcd(a, b) $ 表示 [最大公约数 (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) 。简而言之，函数返回较小的两个数的最大公约数。

你会得到数组 $ a $，包含 $ n $ 个元素。求 $ f(a_i, a_j, a_k) $ 之和，其中 $ 1 \le i< j < k \le n $。

形式化的讲，求 $ \sum_{i = 1}^n \sum_{j = i+1}^n \sum_{k =j +1}^n f(a_i, a_j, a_k)$。

## 输入格式

第一行一个整数 $ t \ ( 1 \le t \le 10 )$ 为数据组数。

每组数据第一行为 $ n \ (3 \le n \le 8 \cdot 10^4) $，第二行为 $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^5 $ )  。

所有数据中 $ n $ 的和不超过 $ 8 \cdot 10^4 $。

## 输出格式

对每组数据，输出题中要求计算的求和。

## 样例 #1

### 输入

```
2
5
2 3 6 12 17
8
6 12 8 10 15 12 18 16
```

### 输出

```
24
203
```

