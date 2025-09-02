---
title: "Lucky Tickets"
layout: "post"
diff: 省选/NOI-
pid: CF1096G
tag: ['组合数学', '快速数论变换 NTT']
---

# Lucky Tickets

## 题目描述

All bus tickets in Berland have their numbers. A number consists of $ n $ digits ( $ n $ is even). Only $ k $ decimal digits $ d_1, d_2, \dots, d_k $ can be used to form ticket numbers. If $ 0 $ is among these digits, then numbers may have leading zeroes. For example, if $ n = 4 $ and only digits $ 0 $ and $ 4 $ can be used, then $ 0000 $ , $ 4004 $ , $ 4440 $ are valid ticket numbers, and $ 0002 $ , $ 00 $ , $ 44443 $ are not.

A ticket is lucky if the sum of first $ n / 2 $ digits is equal to the sum of remaining $ n / 2 $ digits.

Calculate the number of different lucky tickets in Berland. Since the answer may be big, print it modulo $ 998244353 $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ $ (2 \le n \le 2 \cdot 10^5, 1 \le k \le 10) $ — the number of digits in each ticket number, and the number of different decimal digits that may be used. $ n $ is even.

The second line contains a sequence of pairwise distinct integers $ d_1, d_2, \dots, d_k $ $ (0 \le d_i \le 9) $ — the digits that may be used in ticket numbers. The digits are given in arbitrary order.

## 输出格式

Print the number of lucky ticket numbers, taken modulo $ 998244353 $ .

## 说明/提示

In the first example there are $ 6 $ lucky ticket numbers: $ 1111 $ , $ 1818 $ , $ 1881 $ , $ 8118 $ , $ 8181 $ and $ 8888 $ .

There is only one ticket number in the second example, it consists of $ 20 $ digits $ 6 $ . This ticket number is lucky, so the answer is $ 1 $ .

## 样例 #1

### 输入

```
4 2
1 8

```

### 输出

```
6

```

## 样例 #2

### 输入

```
20 1
6

```

### 输出

```
1

```

## 样例 #3

### 输入

```
10 5
6 1 4 0 3

```

### 输出

```
569725

```

## 样例 #4

### 输入

```
1000 7
5 4 0 1 8 3 2

```

### 输出

```
460571165

```

