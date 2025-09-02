---
title: "Interesting Problem (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1987F2
tag: ['区间 DP']
---

# Interesting Problem (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is the constraint on $ n $ . You can make hacks only if both versions of the problem are solved.

You are given an array of integers $ a $ of length $ n $ .

In one operation, you will perform the following two-step process:

1. Choose an index $ i $ such that $ 1 \le i < |a| $ and $ a_i = i $ .
2. Remove $ a_i $ and $ a_{i+1} $ from the array and concatenate the remaining parts.

Find the maximum number of times that you can perform the operation above.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 800 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 800 $ .

## 输出格式

For each test case, output a single integer — the maximum number of times that you can perform the operation.

## 说明/提示

In the first test case, one possible optimal sequence of operations is $ [ 1, 5, \color{red}{3}, \color{red}{2}, 4 ] \rightarrow [\color{red}{1}, \color{red}{5}, 4] \rightarrow [4] $ .

In the third test case, one possible optimal sequence of operations is $ [1, \color{red}{2}, \color{red}{3}] \rightarrow [1] $ .

## 样例 #1

### 输入

```
6
5
1 5 3 2 4
8
2 1 3 4 5 6 7 8
3
1 2 3
4
1 2 4 4
5
4 4 1 3 5
1
1
```

### 输出

```
2
3
1
2
0
0
```

