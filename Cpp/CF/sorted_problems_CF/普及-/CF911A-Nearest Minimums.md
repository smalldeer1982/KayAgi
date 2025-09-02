---
title: "Nearest Minimums"
layout: "post"
diff: 普及-
pid: CF911A
tag: ['枚举', '排序', '位运算']
---

# Nearest Minimums

## 题目描述

You are given an array of $ n $ integer numbers $ a_{0},a_{1},...,a_{n-1} $ . Find the distance between two closest (nearest) minimums in it. It is guaranteed that in the array a minimum occurs at least two times.
找到一个长度为n的序列中，距离最短的最小值的距离。

## 输入格式

The first line contains positive integer $ n $ ( $ 2<=n<=10^{5} $ ) — size of the given array. The second line contains $ n $ integers $ a_{0},a_{1},...,a_{n-1} $ ( $ 1<=a_{i}<=10^{9} $ ) — elements of the array. It is guaranteed that in the array a minimum occurs at least two times.

## 输出格式

Print the only number — distance between two nearest minimums in the array.

## 样例 #1

### 输入

```
2
3 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
5 6 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
9
2 1 3 5 4 1 2 3 1

```

### 输出

```
3

```

