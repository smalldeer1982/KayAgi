---
title: "Excellent Arrays"
layout: "post"
diff: 提高+/省选-
pid: CF1550D
tag: []
---

# Excellent Arrays

## 题目描述

Let's call an integer array $ a_1, a_2, \dots, a_n $ good if $ a_i \neq i $ for each $ i $ .

Let $ F(a) $ be the number of pairs $ (i, j) $ ( $ 1 \le i < j \le n $ ) such that $ a_i + a_j = i + j $ .

Let's say that an array $ a_1, a_2, \dots, a_n $ is excellent if:

- $ a $ is good;
- $ l \le a_i \le r $ for each $ i $ ;
- $ F(a) $ is the maximum possible among all good arrays of size $ n $ .

Given $ n $ , $ l $ and $ r $ , calculate the number of excellent arrays modulo $ 10^9 + 7 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The first and only line of each test case contains three integers $ n $ , $ l $ , and $ r $ ( $ 2 \le n \le 2 \cdot 10^5 $ ; $ -10^9 \le l \le 1 $ ; $ n \le r \le 10^9 $ ).

It's guaranteed that the sum of $ n $ doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the number of excellent arrays modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case, it can be proven that the maximum $ F(a) $ among all good arrays $ a $ is equal to $ 2 $ . The excellent arrays are:

1. $ [2, 1, 2] $ ;
2. $ [0, 3, 2] $ ;
3. $ [2, 3, 2] $ ;
4. $ [3, 0, 1] $ .

## 样例 #1

### 输入

```
4
3 0 3
4 -3 5
42 -33 55
69 -42 146
```

### 输出

```
4
10
143922563
698570404
```

