---
title: "Perfect Squares"
layout: "post"
diff: 入门
pid: CF914A
tag: ['模拟', '枚举', '排序']
---

# Perfect Squares

## 题目描述

Given an array $ a_{1},a_{2},...,a_{n} $ of $ n $ integers, find the largest number in the array that is not a perfect square.

A number $ x $ is said to be a perfect square if there exists an integer $ y $ such that $ x=y^{2} $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=1000 $ ) — the number of elements in the array.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ -10^{6}<=a_{i}<=10^{6} $ ) — the elements of the array.

It is guaranteed that at least one element of the array is not a perfect square.

## 输出格式

Print the largest number in the array which is not a perfect square. It is guaranteed that an answer always exists.

## 说明/提示

In the first sample case, $ 4 $ is a perfect square, so the largest number in the array that is not a perfect square is $ 2 $ .

## 样例 #1

### 输入

```
2
4 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
8
1 2 4 8 16 32 64 576

```

### 输出

```
32

```

