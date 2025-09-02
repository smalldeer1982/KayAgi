---
title: "Polo the Penguin and Lucky Numbers"
layout: "post"
diff: 省选/NOI-
pid: CF288E
tag: []
---

# Polo the Penguin and Lucky Numbers

## 题目描述

Everybody knows that lucky numbers are positive integers that contain only lucky digits 4 and 7 in their decimal representation. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Polo the Penguin have two positive integers $ l $ and $ r $ $ (l&lt;r) $ , both of them are lucky numbers. Moreover, their lengths (that is, the number of digits in the decimal representation without the leading zeroes) are equal to each other.

Let's assume that $ n $ is the number of distinct lucky numbers, each of them cannot be greater than $ r $ or less than $ l $ , and $ a_{i} $ is the $ i $ -th (in increasing order) number of them. Find $ a_{1}·a_{2}+a_{2}·a_{3}+...+a_{n-1}·a_{n} $ . As the answer can be rather large, print the remainder after dividing it by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line contains a positive integer $ l $ , and the second line contains a positive integer $ r $ ( $ 1<=l&lt;r<=10^{100000} $ ). The numbers are given without any leading zeroes.

It is guaranteed that the lengths of the given numbers are equal to each other and that both of them are lucky numbers.

## 输出格式

In the single line print a single integer — the answer to the problem modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
4
7

```

### 输出

```
28

```

## 样例 #2

### 输入

```
474
777

```

### 输出

```
2316330

```

