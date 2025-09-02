---
title: "K-Sort"
layout: "post"
diff: 普及-
pid: CF1987B
tag: ['贪心']
---

# K-Sort

## 题目描述

You are given an array of integers $ a $ of length $ n $ .

You can apply the following operation any number of times (maybe, zero):

- First, choose an integer $ k $ such that $ 1 \le k \le n $ and pay $ k + 1 $ coins.
- Then, choose exactly $ k $ indices such that $ 1 \le i_1 < i_2 < \ldots < i_k \le n $ .
- Then, for each $ x $ from $ 1 $ to $ k $ , increase $ a_{i_x} $ by $ 1 $ .

Find the minimum number of coins needed to make $ a $ non-decreasing. That is, $ a_1 \le a_2 \le \ldots \le a_n $ .

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer — the minimum number of coins needed to make $ a $ non-decreasing.

## 说明/提示

In the first test case, $ a $ is already sorted, so you don't have to spend any coins.

In the second test case, the optimal sequence of operations is:

- Choose $ k = 2 $ and the indices $ 2 $ and $ 5 $ : $ [ 2, \color{red}{1}, 4, 7, \color{red}{6} ] \rightarrow [2, 2, 4, 7, 7] $ . This costs $ 3 $ coins.

 It can be proven that it is not possible to make $ a $ non-decreasing by spending less than $ 3 $ coins.

## 样例 #1

### 输入

```
5
3
1 7 9
5
2 1 4 7 6
4
1 3 2 4
1
179
9
344 12 37 60 311 613 365 328 675
```

### 输出

```
0
3
2
0
1821
```

