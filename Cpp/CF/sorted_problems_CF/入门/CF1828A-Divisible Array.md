---
title: "Divisible Array"
layout: "post"
diff: 入门
pid: CF1828A
tag: []
---

# Divisible Array

## 题目描述

You are given a positive integer $ n $ . Please find an array $ a_1, a_2, \ldots, a_n $ that is perfect.

A perfect array $ a_1, a_2, \ldots, a_n $ satisfies the following criteria:

- $ 1 \le a_i \le 1000 $ for all $ 1 \le i \le n $ .
- $ a_i $ is divisible by $ i $ for all $ 1 \le i \le n $ .
- $ a_1 + a_2 + \ldots + a_n $ is divisible by $ n $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 200 $ ). The description of the test cases follows.

The only line of each test case contains a single positive integer $ n $ ( $ 1 \le n \le 200 $ ) — the length of the array $ a $ .

## 输出格式

For each test case, output an array $ a_1, a_2, \ldots, a_n $ that is perfect.

We can show that an answer always exists. If there are multiple solutions, print any.

## 说明/提示

In the third test case:

- $ a_1 = 1 $ is divisible by $ 1 $ .
- $ a_2 = 2 $ is divisible by $ 2 $ .
- $ a_3 = 3 $ is divisible by $ 3 $ .
- $ a_1 + a_2 + a_3 = 1 + 2 + 3 = 6 $ is divisible by $ 3 $ .

In the fifth test case:

- $ a_1 = 3 $ is divisible by $ 1 $ .
- $ a_2 = 4 $ is divisible by $ 2 $ .
- $ a_3 = 9 $ is divisible by $ 3 $ .
- $ a_4 = 4 $ is divisible by $ 4 $ .
- $ a_5 = 5 $ is divisible by $ 5 $ .
- $ a_1 + a_2 + a_3 + a_4 + a_5 = 3 + 4 + 9 + 4 + 5 = 25 $ is divisible by $ 5 $ .

## 样例 #1

### 输入

```
7
1
2
3
4
5
6
7
```

### 输出

```
1
2 4
1 2 3
2 8 6 4
3 4 9 4 5
1 10 18 8 5 36
3 6 21 24 10 6 14
```

