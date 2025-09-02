---
title: "Maximum Subarray"
layout: "post"
diff: 普及+/提高
pid: CF1796D
tag: []
---

# Maximum Subarray

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , consisting of $ n $ integers. You are also given two integers $ k $ and $ x $ .

You have to perform the following operation exactly once: add $ x $ to the elements on exactly $ k $ distinct positions, and subtract $ x $ from all the others.

For example, if $ a = [2, -1, 2, 3] $ , $ k = 1 $ , $ x = 2 $ , and we have picked the first element, then after the operation the array $ a = [4, -3, 0, 1] $ .

Let $ f(a) $ be the maximum possible sum of a subarray of $ a $ . The subarray of $ a $ is a contiguous part of the array $ a $ , i. e. the array $ a_i, a_{i + 1}, \dots, a_j $ for some $ 1 \le i \le j \le n $ . An empty subarray should also be considered, it has sum $ 0 $ .

Let the array $ a' $ be the array $ a $ after applying the aforementioned operation. Apply the operation in such a way that $ f(a') $ is the maximum possible, and print the maximum possible value of $ f(a') $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains three integers $ n $ , $ k $ and $ x $ ( $ 1 \le n \le 2 \cdot 10^5 $ ; $ 0 \le k \le \min(20, n) $ ; $ -10^9 \le x \le 10^9 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ).

The sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print one integer — the maximum possible value of $ f(a') $ .

## 样例 #1

### 输入

```
4
4 1 2
2 -1 2 3
2 2 3
-1 2
3 0 5
3 2 4
6 2 -8
4 -1 9 -3 7 -8
```

### 输出

```
5
7
0
44
```

