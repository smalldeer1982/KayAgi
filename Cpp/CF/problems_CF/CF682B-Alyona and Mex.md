---
title: "Alyona and Mex"
layout: "post"
diff: 普及-
pid: CF682B
tag: []
---

# Alyona and Mex

## 题目描述

Someone gave Alyona an array containing $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ . In one operation, Alyona can choose any element of the array and decrease it, i.e. replace with any positive integer that is smaller than the current one. Alyona can repeat this operation as many times as she wants. In particular, she may not apply any operation to the array at all.

Formally, after applying some operations Alyona will get an array of $ n $ positive integers $ b_{1},b_{2},...,b_{n} $ such that $ 1<=b_{i}<=a_{i} $ for every $ 1<=i<=n $ . Your task is to determine the maximum possible value of mex of this array.

Mex of an array in this problem is the minimum positive integer that doesn't appear in this array. For example, mex of the array containing $ 1 $ , $ 3 $ and $ 4 $ is equal to $ 2 $ , while mex of the array containing $ 2 $ , $ 3 $ and $ 2 $ is equal to $ 1 $ .

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the number of elements in the Alyona's array.

The second line of the input contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the elements of the array.

## 输出格式

Print one positive integer — the maximum possible value of mex of the array after Alyona applies some (possibly none) operations.

## 说明/提示

In the first sample case if one will decrease the second element value to $ 2 $ and the fifth element value to $ 4 $ then the mex value of resulting array $ 1 $ $ 2 $ $ 3 $ $ 3 $ $ 4 $ will be equal to $ 5 $ .

To reach the answer to the second sample case one must not decrease any of the array elements.

## 样例 #1

### 输入

```
5
1 3 3 3 6

```

### 输出

```
5

```

## 样例 #2

### 输入

```
2
2 1

```

### 输出

```
3

```

