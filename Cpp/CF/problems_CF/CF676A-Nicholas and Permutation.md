---
title: "Nicholas and Permutation"
layout: "post"
diff: 普及-
pid: CF676A
tag: []
---

# Nicholas and Permutation

## 题目描述

Nicholas has an array $ a $ that contains $ n $ distinct integers from $ 1 $ to $ n $ . In other words, Nicholas has a permutation of size $ n $ .

Nicholas want the minimum element (integer $ 1 $ ) and the maximum element (integer $ n $ ) to be as far as possible from each other. He wants to perform exactly one swap in order to maximize the distance between the minimum and the maximum elements. The distance between two elements is considered to be equal to the absolute difference between their positions.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=100 $ ) — the size of the permutation.

The second line of the input contains $ n $ distinct integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=n $ ), where $ a_{i} $ is equal to the element at the $ i $ -th position.

## 输出格式

Print a single integer — the maximum possible distance between the minimum and the maximum elements Nicholas can achieve by performing exactly one swap.

## 说明/提示

In the first sample, one may obtain the optimal answer by swapping elements $ 1 $ and $ 2 $ .

In the second sample, the minimum and the maximum elements will be located in the opposite ends of the array if we swap $ 7 $ and $ 2 $ .

In the third sample, the distance between the minimum and the maximum elements is already maximum possible, so we just perform some unnecessary swap, for example, one can swap $ 5 $ and $ 2 $ .

## 样例 #1

### 输入

```
5
4 5 1 3 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
7
1 6 5 3 4 7 2

```

### 输出

```
6

```

## 样例 #3

### 输入

```
6
6 5 4 3 2 1

```

### 输出

```
5

```

