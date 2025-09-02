---
title: "Unique Array"
layout: "post"
diff: 提高+/省选-
pid: CF1969E
tag: ['贪心', '线段树']
---

# Unique Array

## 题目描述

You are given an integer array $ a $ of length $ n $ . A subarray of $ a $ is one of its contiguous subsequences (i. e. an array $ [a_l, a_{l+1}, \dots, a_r] $ for some integers $ l $ and $ r $ such that $ 1 \le l < r \le n $ ). Let's call a subarray unique if there is an integer that occurs exactly once in the subarray.

You can perform the following operation any number of times (possibly zero): choose an element of the array and replace it with any integer.

Your task is to calculate the minimum number of aforementioned operation in order for all the subarrays of the array $ a $ to be unique.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ).

Additional constraint on the input: the sum of $ n $ over all test cases doesn't exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the minimum number of aforementioned operation in order for all the subarrays of the array $ a $ to be unique.

## 说明/提示

In the second test case, you can replace the $ 1 $ -st and the $ 3 $ -rd element, for example, like this: $ [3, 4, 1, 4] $ .

In the third test case, you can replace the $ 4 $ -th element, for example, like this: $ [3, 1, 2, 3, 2] $ .

## 样例 #1

### 输入

```
4
3
2 1 2
4
4 4 4 4
5
3 1 2 1 2
5
1 3 2 1 2
```

### 输出

```
0
2
1
0
```

