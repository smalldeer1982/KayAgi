---
title: "Maximum Sum of Digits"
layout: "post"
diff: 普及-
pid: CF1060B
tag: []
---

# Maximum Sum of Digits

## 题目描述

You are given a positive integer $ n $ .

Let $ S(x) $ be sum of digits in base 10 representation of $ x $ , for example, $ S(123) = 1 + 2 + 3 = 6 $ , $ S(0) = 0 $ .

Your task is to find two integers $ a, b $ , such that $ 0 \leq a, b \leq n $ , $ a + b = n $ and $ S(a) + S(b) $ is the largest possible among all such pairs.

## 输入格式

The only line of input contains an integer $ n $ $ (1 \leq n \leq 10^{12}) $ .

## 输出格式

Print largest $ S(a) + S(b) $ among all pairs of integers $ a, b $ , such that $ 0 \leq a, b \leq n $ and $ a + b = n $ .

## 说明/提示

In the first example, you can choose, for example, $ a = 17 $ and $ b = 18 $ , so that $ S(17) + S(18) = 1 + 7 + 1 + 8 = 17 $ . It can be shown that it is impossible to get a larger answer.

In the second test example, you can choose, for example, $ a = 5000000001 $ and $ b = 4999999999 $ , with $ S(5000000001) + S(4999999999) = 91 $ . It can be shown that it is impossible to get a larger answer.

## 样例 #1

### 输入

```
35

```

### 输出

```
17

```

## 样例 #2

### 输入

```
10000000000

```

### 输出

```
91

```

