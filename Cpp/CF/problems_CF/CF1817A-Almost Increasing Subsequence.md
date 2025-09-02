---
title: "Almost Increasing Subsequence"
layout: "post"
diff: 普及/提高-
pid: CF1817A
tag: []
---

# Almost Increasing Subsequence

## 题目描述

A sequence is almost-increasing if it does not contain three consecutive elements $ x, y, z $ such that $ x\ge y\ge z $ .

You are given an array $ a_1, a_2, \dots, a_n $ and $ q $ queries.

Each query consists of two integers $ 1\le l\le r\le n $ . For each query, find the length of the longest almost-increasing subsequence of the subarray $ a_l, a_{l+1}, \dots, a_r $ .

A subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without changing the order of the remaining elements.

## 输入格式

The first line of input contains two integers, $ n $ and $ q $ ( $ 1 \leq n, q \leq 200\,000 $ ) — the length of the array $ a $ and the number of queries.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the values of the array $ a $ .

Each of the next $ q $ lines contains the description of a query. Each line contains two integers $ l $ and $ r $ ( $ 1 \leq l \leq r \leq n $ ) — the query is about the subarray $ a_l, a_{l+1}, \dots, a_r $ .

## 输出格式

For each of the $ q $ queries, print a line containing the length of the longest almost-increasing subsequence of the subarray $ a_l, a_{l+1}, \dots, a_r $ .

## 说明/提示

In the first query, the subarray is $ a_1, a_2, a_3 = [1,2,4] $ . The whole subarray is almost-increasing, so the answer is $ 3 $ .

In the second query, the subarray is $ a_1, a_2, a_3,a_4 = [1,2,4,3] $ . The whole subarray is a almost-increasing, because there are no three consecutive elements such that $ x \geq y \geq z $ . So the answer is $ 4 $ .

In the third query, the subarray is $ a_2, a_3, a_4, a_5 = [2, 4, 3, 3] $ . The whole subarray is not almost-increasing, because the last three elements satisfy $ 4 \geq 3 \geq 3 $ . An almost-increasing subsequence of length $ 3 $ can be found (for example taking $ a_2,a_3,a_5 = [2,4,3] $ ). So the answer is $ 3 $ .

## 样例 #1

### 输入

```
9 8
1 2 4 3 3 5 6 2 1
1 3
1 4
2 5
6 6
3 7
7 8
1 8
8 8
```

### 输出

```
3
4
3
1
4
2
7
1
```

