---
title: "Good Subarrays (Easy Version)"
layout: "post"
diff: 普及/提高-
pid: CF1736C1
tag: []
---

# Good Subarrays (Easy Version)

## 题目描述

This is the easy version of this problem. In this version, we do not have queries. Note that we have multiple test cases in this version. You can make hacks only if both versions of the problem are solved.

An array $ b $ of length $ m $ is good if for all $ i $ the $ i $ -th element is greater than or equal to $ i $ . In other words, $ b $ is good if and only if $ b_i \geq i $ for all $ i $ ( $ 1 \leq i \leq m $ ).

You are given an array $ a $ consisting of $ n $ positive integers. Find the number of pairs of indices $ (l, r) $ , where $ 1 \le l \le r \le n $ , such that the array $ [a_l, a_{l+1}, \ldots, a_r] $ is good.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 2 \cdot 10^5 $ ). Description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ), the length of the array $ a $ .

The second line of each test case contains $ n $ space-separated integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \leq a_i \leq n $ ), representing the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the number of suitable pairs of indices.

## 说明/提示

In the first test case, all subarrays of $ a $ are good, so all pairs are suitable.

In the second test case, the pairs $ (1, 1) $ , $ (2, 2) $ , and $ (3, 3) $ are suitable. For example, when $ (l, r) = (1, 2) $ , the array $ b=[1,1] $ is not good because $ b_2 < 2 $ .

## 样例 #1

### 输入

```
3
3
1 2 3
3
1 1 1
4
2 1 4 3
```

### 输出

```
6
3
7
```

