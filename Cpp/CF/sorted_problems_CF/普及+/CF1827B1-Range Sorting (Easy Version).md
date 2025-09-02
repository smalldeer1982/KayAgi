---
title: "Range Sorting (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF1827B1
tag: []
---

# Range Sorting (Easy Version)

## 题目描述

The only difference between this problem and the hard version is the constraints on $ t $ and $ n $ .

You are given an array $ a $ , consisting of $ n $ distinct integers $ a_1, a_2, \ldots, a_n $ .

Define the beauty of an array $ p_1, p_2, \ldots p_k $ as the minimum amount of time needed to sort this array using an arbitrary number of range-sort operations. In each range-sort operation, you will do the following:

- Choose two integers $ l $ and $ r $ ( $ 1 \le l < r \le k $ ).
- Sort the subarray $ p_l, p_{l + 1}, \ldots, p_r $ in $ r - l $ seconds.

Please calculate the sum of beauty over all subarrays of array $ a $ .

A subarray of an array is defined as a sequence of consecutive elements of the array.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 5 \cdot 10^3 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 5 \cdot 10^3 $ ) — the length of the array $ a $ .

The second line of each test case consists of $ n $ integers $ a_1,a_2,\ldots, a_n $ ( $ 1\le a_i\le 10^9 $ ). It is guaranteed that all elements of $ a $ are pairwise distinct.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^3 $ .

## 输出格式

For each test case, output the sum of beauty over all subarrays of array $ a $ .

## 说明/提示

In the first test case:

- The subarray $ [6] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [4] $ is already sorted, so its beauty is $ 0 $ .
- You can sort the subarray $ [6, 4] $ in one operation by choosing $ l = 1 $ and $ r = 2 $ . Its beauty is equal to $ 1 $ .

 The sum of beauty over all subarrays of the given array is equal to $ 0 + 0 + 1 = 1 $ .In the second test case:

- The subarray $ [3] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [10] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [6] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [3, 10] $ is already sorted, so its beauty is $ 0 $ .
- You can sort the subarray $ [10, 6] $ in one operation by choosing $ l = 1 $ and $ r = 2 $ . Its beauty is equal to $ 2 - 1 = 1 $ .
- You can sort the subarray $ [3, 10, 6] $ in one operation by choosing $ l = 2 $ and $ r = 3 $ . Its beauty is equal to $ 3 - 2 = 1 $ .

 The sum of beauty over all subarrays of the given array is equal to $ 0 + 0 + 0 + 0 + 1 + 1 = 2 $ .

## 样例 #1

### 输入

```
5
2
6 4
3
3 10 6
4
4 8 7 2
5
9 8 2 4 6
12
2 6 13 3 15 5 10 8 16 9 11 18
```

### 输出

```
1
2
8
16
232
```

