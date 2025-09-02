---
title: "Number of Ways"
layout: "post"
diff: 普及/提高-
pid: CF466C
tag: ['枚举', '前缀和']
---

# Number of Ways

## 题目描述

You've got array $ a[1],a[2],...,a[n] $ , consisting of $ n $ integers. Count the number of ways to split all the elements of the array into three contiguous parts so that the sum of elements in each part is the same.

More formally, you need to find the number of such pairs of indices $ i,j $ $ (2<=i<=j<=n-1) $ , that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF466C/6d268bd0e5773093a8b59275245964aa2b1c55f9.png).

## 输入格式

The first line contains integer $ n $ $ (1<=n<=5·10^{5}) $ , showing how many numbers are in the array. The second line contains $ n $ integers $ a[1] $ , $ a[2] $ , ..., $ a[n] $ $ (|a[i]|<=10^{9}) $ — the elements of array $ a $ .

## 输出格式

Print a single integer — the number of ways to split the array into three parts with the same sum.

## 样例 #1

### 输入

```
5
1 2 3 0 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4
0 1 -1 0

```

### 输出

```
1

```

## 样例 #3

### 输入

```
2
4 1

```

### 输出

```
0

```

