---
title: "Increasing Subsequences"
layout: "post"
diff: 普及+/提高
pid: CF1922E
tag: ['构造']
---

# Increasing Subsequences

## 题目描述

Let's recall that an increasing subsequence of the array $ a $ is a sequence that can be obtained from it by removing some elements without changing the order of the remaining elements, and the remaining elements are strictly increasing (i. e $ a_{b_1} < a_{b_2} < \dots < a_{b_k} $ and $ b_1 < b_2 < \dots < b_k $ ). Note that an empty subsequence is also increasing.

You are given a positive integer $ X $ . Your task is to find an array of integers of length at most $ 200 $ , such that it has exactly $ X $ increasing subsequences, or report that there is no such array. If there are several answers, you can print any of them.

If two subsequences consist of the same elements, but correspond to different positions in the array, they are considered different (for example, the array $ [2, 2] $ has two different subsequences equal to $ [2] $ ).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The only line of each test case contains a single integer $ X $ ( $ 2 \le X \le 10^{18} $ ).

## 输出格式

For each query, print the answer to it. If it is impossible to find the required array, print -1 on the first line. Otherwise, print a positive integer $ n $ on the first line — the length of the array. On the second line, print $ n $ integers — the required array itself. If there are several answers, you can print any of them. All elements of the array should be in the range $ [-10^9; 10^9] $ .

## 样例 #1

### 输入

```
4
2
5
13
37
```

### 输出

```
1
0
3
0 1 0
5
2 2 3 4 2
7
-1 -1 0 0 2 3 -1
```

