---
title: "Ice Baby"
layout: "post"
diff: 提高+/省选-
pid: CF2121H
tag: ['动态规划 DP', '线段树', '动态规划优化', '标签504']
---

# Ice Baby

## 题目描述

The longest non-decreasing subsequence of an array of integers $ a_1, a_2, \ldots, a_n $ is the longest sequence of indices $ 1 \leq i_1 < i_2 < \ldots < i_k \leq n $ such that $ a_{i_1} \leq a_{i_2} \leq \ldots \leq a_{i_k} $ . The length of the sequence is defined as the number of elements in the sequence. For example, the length of the longest non-decreasing subsequence of the array $ a = [3, 1, 4, 1, 2] $ is $ 3 $ .

You are given two arrays of integers $ l_1, l_2, \ldots, l_n $ and $ r_1, r_2, \ldots, r_n $ . For each $ 1 \le k \le n $ , solve the following problem:

- Consider all arrays of integers $ a $ of length $ k $ , such that for each $ 1 \leq i \leq k $ , it holds that $ l_i \leq a_i \leq r_i $ . Find the maximum length of the longest non-decreasing subsequence among all such arrays.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the arrays $ l $ and $ r $ .

The next $ n $ lines of each test case contain two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i \leq r_i \leq 10^9 $ ).

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers: for each $ k $ from $ 1 $ to $ n $ , output the maximum length of the longest non-decreasing subsequence among all suitable arrays.

## 说明/提示

In the first test case, the only possible array is $ a = [1] $ . The length of the longest non-decreasing subsequence of this array is $ 1 $ .

In the second test case, for $ k = 2 $ , no matter how we choose the values of $ a_1 $ and $ a_2 $ , the condition $ a_1 > a_2 $ will always hold. Therefore, the answer for $ k = 2 $ will be $ 1 $ .

In the third test case, for $ k = 4 $ , we can choose the array $ a = [5, 3, 3, 3] $ . The length of the longest non-decreasing subsequence of this array is $ 3 $ .

In the fourth test case, for $ k = 8 $ , we can choose the array $ a = [7, 5, 3, 5, 3, 3, 3, 3] $ . The length of the longest non-decreasing subsequence of this array is $ 5 $ .

In the fifth test case, for $ k = 5 $ , we can choose the array $ a = [2, 8, 5, 3, 3] $ . The length of the longest non-decreasing subsequence of this array is $ 3 $ .

## 样例 #1

### 输入

```
6
1
1 1
2
3 4
1 2
4
4 5
3 4
1 3
3 3
8
6 8
4 6
3 5
5 5
3 4
1 3
2 4
3 3
5
1 2
6 8
4 5
2 3
3 3
11
35 120
66 229
41 266
98 164
55 153
125 174
139 237
30 72
138 212
109 123
174 196
```

### 输出

```
1 
1 1 
1 2 2 3 
1 2 2 3 3 3 4 5 
1 2 2 2 3 
1 2 3 4 5 6 7 7 8 8 9
```

