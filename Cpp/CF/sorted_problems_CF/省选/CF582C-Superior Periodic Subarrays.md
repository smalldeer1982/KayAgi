---
title: "Superior Periodic Subarrays"
layout: "post"
diff: 省选/NOI-
pid: CF582C
tag: []
---

# Superior Periodic Subarrays

## 题目描述

You are given an infinite periodic array $ a_{0},a_{1},...,a_{n-1},... $ with the period of length $ n $ . Formally, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF582C/aa44e9dfb7106bc0c4afdc0035ceead70e7d91ec.png). A periodic subarray $ (l,s) $ ( $ 0<=l&lt;n $ , $ 1<=s&lt;n $ ) of array $ a $ is an infinite periodic array with a period of length $ s $ that is a subsegment of array $ a $ , starting with position $ l $ .

A periodic subarray $ (l,s) $ is superior, if when attaching it to the array $ a $ , starting from index $ l $ , any element of the subarray is larger than or equal to the corresponding element of array $ a $ . An example of attaching is given on the figure (top — infinite array $ a $ , bottom — its periodic subarray $ (l,s) $ ):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF582C/3459142ae634f6d125367238083d1b99f717b1ba.png)Find the number of distinct pairs $ (l,s) $ , corresponding to the superior periodic arrays.

## 输入格式

The first line contains number $ n $ ( $ 1<=n<=2·10^{5} $ ). The second line contains $ n $ numbers $ a_{0},a_{1},...,a_{n-1} $ ( $ 1<=a_{i}<=10^{6} $ ), separated by a space.

## 输出格式

Print a single integer — the sought number of pairs.

## 说明/提示

In the first sample the superior subarrays are (0, 1) and (3, 2).

Subarray (0, 1) is superior, as $ a_{0}>=a_{0},a_{0}>=a_{1},a_{0}>=a_{2},a_{0}>=a_{3},a_{0}>=a_{0},... $

Subarray (3, 2) is superior $ a_{3}>=a_{3},a_{0}>=a_{0},a_{3}>=a_{1},a_{0}>=a_{2},a_{3}>=a_{3},... $

In the third sample any pair of $ (l,s) $ corresponds to a superior subarray as all the elements of an array are distinct.

## 样例 #1

### 输入

```
4
7 1 2 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2
2 1

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3
1 1 1

```

### 输出

```
6

```

