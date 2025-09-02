---
title: "Kosuke's Sloth"
layout: "post"
diff: 普及+/提高
pid: CF2033F
tag: ['数学']
---

# Kosuke's Sloth

## 题目描述

Kosuke is too lazy. He will not give you any legend, just the task:

Fibonacci numbers are defined as follows:

- $ f(1)=f(2)=1 $ .
- $ f(n)=f(n-1)+f(n-2) $ $ (3\le n) $

 We denote $ G(n,k) $ as an index of the $ n $ -th Fibonacci number that is divisible by $ k $ . For given $ n $ and $ k $ , compute $ G(n,k) $ .As this number can be too big, output it by modulo $ 10^9+7 $ .

For example: $ G(3,2)=9 $ because the $ 3 $ -rd Fibonacci number that is divisible by $ 2 $ is $ 34 $ . $ [1,1,\textbf{2},3,5,\textbf{8},13,21,\textbf{34}] $ .

## 输入格式

The first line of the input data contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first and only line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 10^{18} $ , $ 1 \le k \le 10^5 $ ).

It is guaranteed that the sum of $ k $ across all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output the only number: the value $ G(n,k) $ taken by modulo $ 10^9+7 $ .

## 样例 #1

### 输入

```
3
3 2
100 1
1000000000000 1377
```

### 输出

```
9
100
999244007
```

