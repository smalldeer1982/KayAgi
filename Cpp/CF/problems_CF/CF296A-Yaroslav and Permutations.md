---
title: "Yaroslav and Permutations"
layout: "post"
diff: 普及-
pid: CF296A
tag: []
---

# Yaroslav and Permutations

## 题目描述

Yaroslav has an array that consists of $ n $ integers. In one second Yaroslav can swap two neighboring array elements. Now Yaroslav is wondering if he can obtain an array where any two neighboring elements would be distinct in a finite time.

Help Yaroslav.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=100) $ — the number of elements in the array. The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=1000) $ — the array elements.

## 输出格式

In the single line print "YES" (without the quotes) if Yaroslav can obtain the array he needs, and "NO" (without the quotes) otherwise.

## 说明/提示

In the first sample the initial array fits well.

In the second sample Yaroslav can get array: $ 1 $ , $ 2 $ , $ 1 $ . He can swap the last and the second last elements to obtain it.

In the third sample Yarosav can't get the array he needs.

## 样例 #1

### 输入

```
1
1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
3
1 1 2

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
4
7 7 7 7

```

### 输出

```
NO

```

