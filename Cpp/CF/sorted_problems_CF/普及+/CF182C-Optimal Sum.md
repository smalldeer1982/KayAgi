---
title: "Optimal Sum"
layout: "post"
diff: 普及+/提高
pid: CF182C
tag: []
---

# Optimal Sum

## 题目描述

And here goes another problem on arrays. You are given positive integer $ len $ and array $ a $ which consists of $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ . Let's introduce two characteristics for the given array.

- Let's consider an arbitrary interval of the array with length $ len $ , starting in position $ i $ . Value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF182C/a67922122e1d38581ab8c091ae9897d972811ca1.png), is the modular sum on the chosen interval. In other words, the modular sum is the sum of integers on the chosen interval with length $ len $ , taken in its absolute value.
- Value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF182C/93dd358f9082d67d4f803ced64f412bb80cdf4c2.png) is the optimal sum of the array. In other words, the optimal sum of an array is the maximum of all modular sums on various intervals of array with length $ len $ .

Your task is to calculate the optimal sum of the given array $ a $ . However, before you do the calculations, you are allowed to produce no more than $ k $ consecutive operations of the following form with this array: one operation means taking an arbitrary number from array $ a_{i} $ and multiply it by -1. In other words, no more than $ k $ times you are allowed to take an arbitrary number $ a_{i} $ from the array and replace it with $ -a_{i} $ . Each number of the array is allowed to choose an arbitrary number of times.

Your task is to calculate the maximum possible optimal sum of the array after at most $ k $ operations described above are completed.

## 输入格式

The first line contains two integers $ n $ , $ len $ ( $ 1<=len<=n<=10^{5} $ ) — the number of elements in the array and the length of the chosen subinterval of the array, correspondingly.

The second line contains a sequence consisting of $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ $ (|a_{i}|<=10^{9}) $ — the original array.

The third line contains a single integer $ k $ ( $ 0<=k<=n $ ) — the maximum allowed number of operations.

All numbers in lines are separated by a single space.

## 输出格式

In a single line print the maximum possible optimal sum after no more than $ k $ acceptable operations are fulfilled.

Please do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
5 3
0 -2 3 -5 1
2

```

### 输出

```
10

```

## 样例 #2

### 输入

```
5 2
1 -3 -10 4 1
3

```

### 输出

```
14

```

## 样例 #3

### 输入

```
3 3
-2 -5 4
1

```

### 输出

```
11

```

