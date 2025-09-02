---
title: "Beautiful numbers"
layout: "post"
diff: 省选/NOI-
pid: CF55D
tag: ['动态规划 DP', '数位 DP', '状态合并']
---

# Beautiful numbers

## 题目描述

Volodya is an odd boy and his taste is strange as well. It seems to him that a positive integer number is beautiful if and only if it is divisible by each of its nonzero digits. We will not argue with this and just count the quantity of beautiful numbers in given ranges.

## 输入格式

The first line of the input contains the number of cases $ t $ ( $ 1<=t<=10 $ ). Each of the next $ t $ lines contains two natural numbers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=9·10^{18} $ ).

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cin (also you may use %I64d).

## 输出格式

Output should contain $ t $ numbers — answers to the queries, one number per line — quantities of beautiful numbers in given intervals (from $ l_{i} $ to $ r_{i} $ , inclusively).

## 样例 #1

### 输入

```
1
1 9

```

### 输出

```
9

```

## 样例 #2

### 输入

```
1
12 15

```

### 输出

```
2

```

