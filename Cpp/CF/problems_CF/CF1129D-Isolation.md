---
title: "Isolation"
layout: "post"
diff: 省选/NOI-
pid: CF1129D
tag: []
---

# Isolation

## 题目描述

Find the number of ways to divide an array $ a $ of $ n $ integers into any number of disjoint non-empty segments so that, in each segment, there exist at most $ k $ distinct integers that appear exactly once.

Since the answer can be large, find it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains two space-separated integers $ n $ and $ k $ ( $ 1 \leq k \leq n \leq 10^5 $ ) — the number of elements in the array $ a $ and the restriction from the statement.

The following line contains $ n $ space-separated integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq n $ ) — elements of the array $ a $ .

## 输出格式

The first and only line contains the number of ways to divide an array $ a $ modulo $ 998\,244\,353 $ .

## 说明/提示

In the first sample, the three possible divisions are as follows.

- $ [[1], [1], [2]] $
- $ [[1, 1], [2]] $
- $ [[1, 1, 2]] $

Division $ [[1], [1, 2]] $ is not possible because two distinct integers appear exactly once in the second segment $ [1, 2] $ .

## 样例 #1

### 输入

```
3 1
1 1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 2
1 1 2 1 3

```

### 输出

```
14

```

## 样例 #3

### 输入

```
5 5
1 2 3 4 5

```

### 输出

```
16

```

