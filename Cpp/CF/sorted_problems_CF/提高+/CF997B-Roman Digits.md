---
title: "Roman Digits"
layout: "post"
diff: 提高+/省选-
pid: CF997B
tag: ['枚举']
---

# Roman Digits

## 题目描述

Let's introduce a number system which is based on a roman digits. There are digits I, V, X, L which correspond to the numbers $ 1 $ , $ 5 $ , $ 10 $ and $ 50 $ respectively. The use of other roman digits is not allowed.

Numbers in this system are written as a sequence of one or more digits. We define the value of the sequence simply as the sum of digits in it.

For example, the number XXXV evaluates to $ 35 $ and the number IXI — to $ 12 $ .

Pay attention to the difference to the traditional roman system — in our system any sequence of digits is valid, moreover the order of digits doesn't matter, for example IX means $ 11 $ , not $ 9 $ .

One can notice that this system is ambiguous, and some numbers can be written in many different ways. Your goal is to determine how many distinct integers can be represented by exactly $ n $ roman digits I, V, X, L.

## 输入格式

The only line of the input file contains a single integer $ n $ ( $ 1 \le n \le 10^9 $ ) — the number of roman digits to use.

## 输出格式

Output a single integer — the number of distinct integers which can be represented using $ n $ roman digits exactly.

## 说明/提示

In the first sample there are exactly $ 4 $ integers which can be represented — I, V, X and L.

In the second sample it is possible to represent integers $ 2 $ (II), $ 6 $ (VI), $ 10 $ (VV), $ 11 $ (XI), $ 15 $ (XV), $ 20 $ (XX), $ 51 $ (IL), $ 55 $ (VL), $ 60 $ (XL) and $ 100 $ (LL).

## 样例 #1

### 输入

```
1

```

### 输出

```
4

```

## 样例 #2

### 输入

```
2

```

### 输出

```
10

```

## 样例 #3

### 输入

```
10

```

### 输出

```
244

```

