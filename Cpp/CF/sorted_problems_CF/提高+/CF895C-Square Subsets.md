---
title: "Square Subsets"
layout: "post"
diff: 提高+/省选-
pid: CF895C
tag: ['数学', '状态合并', '线性基', '位运算']
---

# Square Subsets

## 题目描述

Petya was late for the lesson too. The teacher gave him an additional task. For some array $ a $ Petya should find the number of different ways to select non-empty subset of elements from it in such a way that their product is equal to a square of some integer.

Two ways are considered different if sets of indexes of elements chosen by these ways are different.

Since the answer can be very large, you should find the answer modulo $ 10^{9}+7 $ .

## 输入格式

First line contains one integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of elements in the array.

Second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=70 $ ) — the elements of the array.

## 输出格式

Print one integer — the number of different ways to choose some elements so that their product is a square of a certain integer modulo $ 10^{9}+7 $ .

## 说明/提示

In first sample product of elements chosen by any way is $ 1 $ and $ 1=1^{2} $ . So the answer is $ 2^{4}-1=15 $ .

In second sample there are six different ways to choose elements so that their product is $ 4 $ , and only one way so that their product is $ 16 $ . So the answer is $ 6+1=7 $ .

## 样例 #1

### 输入

```
4
1 1 1 1

```

### 输出

```
15

```

## 样例 #2

### 输入

```
4
2 2 2 2

```

### 输出

```
7

```

## 样例 #3

### 输入

```
5
1 2 4 5 8

```

### 输出

```
7

```

