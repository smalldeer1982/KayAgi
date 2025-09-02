---
title: "Binary Inversions"
layout: "post"
diff: 普及-
pid: CF1760E
tag: []
---

# Binary Inversions

## 题目描述

You are given a binary array $ ^{\dagger} $ of length $ n $ . You are allowed to perform one operation on it at most once. In an operation, you can choose any element and flip it: turn a $ 0 $ into a $ 1 $ or vice-versa.

What is the maximum number of inversions $ ^{\ddagger} $ the array can have after performing at most one operation?

 $ ^\dagger $ A binary array is an array that contains only zeroes and ones.

 $ ^\ddagger $ The number of inversions in an array is the number of pairs of indices $ i,j $ such that $ i<j $ and $ a_i > a_j $ .

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2\cdot10^5 $ ) — the length of the array.

The following line contains $ n $ space-separated positive integers $ a_1 $ , $ a_2 $ ,..., $ a_n $ ( $ 0 \leq a_i \leq 1 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum number of inversions the array can have after performing at most one operation.

## 说明/提示

For the first test case, the inversions are initially formed by the pairs of indices ( $ 1, 2 $ ), ( $ 1, 4 $ ), ( $ 3, 4 $ ), being a total of $ 3 $ , which already is the maximum possible.

For the second test case, the inversions are initially formed by the pairs of indices ( $ 2, 3 $ ), ( $ 2, 4 $ ), ( $ 2, 6 $ ), ( $ 5, 6 $ ), being a total of four. But, by flipping the first element, the array becomes $ {1, 1, 0, 0, 1, 0} $ , which has the inversions formed by the pairs of indices ( $ 1, 3 $ ), ( $ 1, 4 $ ), ( $ 1, 6 $ ), ( $ 2, 3 $ ), ( $ 2, 4 $ ), ( $ 2, 6 $ ), ( $ 5, 6 $ ) which total to $ 7 $ inversions which is the maximum possible.

## 样例 #1

### 输入

```
5
4
1 0 1 0
6
0 1 0 0 1 0
2
0 0
8
1 0 1 1 0 0 0 1
3
1 1 1
```

### 输出

```
3
7
1
13
2
```

