---
title: "Special Numbers"
layout: "post"
diff: 普及/提高-
pid: CF1594B
tag: []
---

# Special Numbers

## 题目描述

Theofanis really likes sequences of positive integers, thus his teacher (Yeltsa Kcir) gave him a problem about a sequence that consists of only special numbers.

Let's call a positive number special if it can be written as a sum of different non-negative powers of $ n $ . For example, for $ n = 4 $ number $ 17 $ is special, because it can be written as $ 4^0 + 4^2 = 1 + 16 = 17 $ , but $ 9 $ is not.

Theofanis asks you to help him find the $ k $ -th special number if they are sorted in increasing order. Since this number may be too large, output it modulo $ 10^9+7 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first and only line of each test case contains two integers $ n $ and $ k $ ( $ 2 \le n \le 10^9 $ ; $ 1 \le k \le 10^9 $ ).

## 输出格式

For each test case, print one integer — the $ k $ -th special number in increasing order modulo $ 10^9+7 $ .

## 说明/提示

For $ n = 3 $ the sequence is $ [1,3,4,9...] $

## 样例 #1

### 输入

```
3
3 4
2 12
105 564
```

### 输出

```
9
12
3595374
```

