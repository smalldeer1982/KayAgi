---
title: "Approximating a Constant Range"
layout: "post"
diff: 普及/提高-
pid: CF602B
tag: []
---

# Approximating a Constant Range

## 题目描述

When Xellos was doing a practice course in university, he once had to measure the intensity of an effect that slowly approached equilibrium. A good way to determine the equilibrium intensity would be choosing a sufficiently large number of consecutive data points that seems as constant as possible and taking their average. Of course, with the usual sizes of data, it's nothing challenging — but why not make a similar programming contest problem while we're at it?

You're given a sequence of $ n $ data points $ a_{1},...,a_{n} $ . There aren't any big jumps between consecutive data points — for each $ 1<=i&lt;n $ , it's guaranteed that $ |a_{i+1}-a_{i}|<=1 $ .

A range $ [l,r] $ of data points is said to be almost constant if the difference between the largest and the smallest value in that range is at most $ 1 $ . Formally, let $ M $ be the maximum and $ m $ the minimum value of $ a_{i} $ for $ l<=i<=r $ ; the range $ [l,r] $ is almost constant if $ M-m<=1 $ .

Find the length of the longest almost constant range.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=100000 $ ) — the number of data points.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=100000 $ ).

## 输出格式

Print a single number — the maximum length of an almost constant range of the given sequence.

## 说明/提示

In the first sample, the longest almost constant range is $ [2,5] $ ; its length (the number of data points in it) is 4.

In the second sample, there are three almost constant ranges of length $ 4 $ : $ [1,4] $ , $ [6,9] $ and $ [7,10] $ ; the only almost constant range of the maximum length $ 5 $ is $ [6,10] $ .

## 样例 #1

### 输入

```
5
1 2 3 3 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
11
5 4 5 5 6 7 8 8 8 7 6

```

### 输出

```
5

```

