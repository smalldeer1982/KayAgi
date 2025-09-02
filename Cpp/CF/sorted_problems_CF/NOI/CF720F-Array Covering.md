---
title: "Array Covering"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF720F
tag: []
---

# Array Covering

## 题目描述

Misha has an array of integers of length $ n $ . He wants to choose $ k $ different continuous subarrays, so that each element of the array belongs to at least one of the chosen subarrays.

Misha wants to choose the subarrays in such a way that if he calculated the sum of elements for each subarray, and then add up all these sums, the resulting value was maximum possible.

## 输入格式

The first line of input contains two integers: $ n $ , $ k $ ( $ 1<=n<=100000 $ , $ 1<=k<=n·(n+1)/2 $ ) — the number of elements in the array and the number of different subarrays that must be chosen.

The second line contains $ n $ integers $ a_{i} $ ( $ -50000<=a_{i}<=50000 $ ) — the elements of the array.

## 输出格式

Output one integer — the maximum possible value Misha can get by choosing $ k $ different subarrays.

## 样例 #1

### 输入

```
5 4
6 -4 -10 -4 7

```

### 输出

```
11

```

