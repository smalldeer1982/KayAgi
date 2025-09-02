---
title: "XOR = Average"
layout: "post"
diff: 普及-
pid: CF1758B
tag: []
---

# XOR = Average

## 题目描述

You are given an integer $ n $ . Find a sequence of $ n $ integers $ a_1, a_2, \dots, a_n $ such that $ 1 \leq a_i \leq 10^9 $ for all $ i $ and $ $$$a_1 \oplus a_2 \oplus \dots \oplus a_n = \frac{a_1 + a_2 + \dots + a_n}{n}, $ $  where  $ \\oplus$$$ represents the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

It can be proven that there exists a sequence of integers that satisfies all the conditions above.

## 输入格式

The first line of input contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first and only line of each test case contains one integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the length of the sequence you have to find.

The sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output $ n $ space-separated integers $ a_1, a_2, \dots, a_n $ satisfying the conditions in the statement.

If there are several possible answers, you can output any of them.

## 说明/提示

In the first test case, $ 69 = \frac{69}{1} = 69 $ .

In the second test case, $ 13 \oplus 2 \oplus 8 \oplus 1 = \frac{13 + 2 + 8 + 1}{4} = 6 $ .

## 样例 #1

### 输入

```
3
1
4
3
```

### 输出

```
69
13 2 8 1
7 7 7
```

