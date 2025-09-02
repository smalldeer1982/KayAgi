---
title: "Comfortably Numb"
layout: "post"
diff: 省选/NOI-
pid: CF1777F
tag: []
---

# Comfortably Numb

## 题目描述

You are given an array $ a $ consisting of $ n $ non-negative integers.

The numbness of a subarray $ a_l, a_{l+1}, \ldots, a_r $ (for arbitrary $ l \leq r $ ) is defined as $\max(a_l, a_{l+1}, \ldots, a_r) \oplus (a_l \oplus a_{l+1} \oplus \ldots \oplus a_r)$, where  $\oplus$ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Find the maximum numbness over all subarrays.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print one integer — the maximum numbness over all subarrays of the given array.

## 说明/提示

For the first test case, for the subarray $ [3, 4, 5] $ , its maximum value is $ 5 $ . Hence, its numbness is $ 3 \oplus 4 \oplus 5 \oplus 5 $ = $ 7 $ . This is the maximum possible numbness in this array.

In the second test case the subarray $ [47, 52] $ provides the maximum numbness.

## 样例 #1

### 输入

```
2
5
1 2 3 4 5
3
10 47 52
```

### 输出

```
7
47
```

