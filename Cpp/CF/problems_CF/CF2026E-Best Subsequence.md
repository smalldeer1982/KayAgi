---
title: "Best Subsequence"
layout: "post"
diff: 提高+/省选-
pid: CF2026E
tag: ['网络流', '二分图']
---

# Best Subsequence

## 题目描述

Given an integer array $ a $ of size $ n $ .

Let's define the value of the array as its size minus the number of set bits in the bitwise OR of all elements of the array.

For example, for the array $ [1, 0, 1, 2] $ , the bitwise OR is $ 3 $ (which contains $ 2 $ set bits), and the value of the array is $ 4-2=2 $ .

Your task is to calculate the maximum possible value of some subsequence of the given array.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 100 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i < 2^{60} $ ).

## 输出格式

For each test case, print the maximum possible value of some subsequence of the given array.

## 样例 #1

### 输入

```
4
3
0 0 0
4
1 0 1 2
1
5
8
7 1 48 14 13 8 7 6
```

### 输出

```
3
2
0
3
```

