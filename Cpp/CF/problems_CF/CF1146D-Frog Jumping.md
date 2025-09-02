---
title: "Frog Jumping"
layout: "post"
diff: 省选/NOI-
pid: CF1146D
tag: []
---

# Frog Jumping

## 题目描述

A frog is initially at position $ 0 $ on the number line. The frog has two positive integers $ a $ and $ b $ . From a position $ k $ , it can either jump to position $ k+a $ or $ k-b $ .

Let $ f(x) $ be the number of distinct integers the frog can reach if it never jumps on an integer outside the interval $ [0, x] $ . The frog doesn't need to visit all these integers in one trip, that is, an integer is counted if the frog can somehow reach it if it starts from $ 0 $ .

Given an integer $ m $ , find $ \sum_{i=0}^{m} f(i) $ . That is, find the sum of all $ f(i) $ for $ i $ from $ 0 $ to $ m $ .

## 输入格式

The first line contains three integers $ m, a, b $ ( $ 1 \leq m \leq 10^9, 1 \leq a,b \leq 10^5 $ ).

## 输出格式

Print a single integer, the desired sum.

## 说明/提示

In the first example, we must find $ f(0)+f(1)+\ldots+f(7) $ . We have $ f(0) = 1, f(1) = 1, f(2) = 1, f(3) = 1, f(4) = 1, f(5) = 3, f(6) = 3, f(7) = 8 $ . The sum of these values is $ 19 $ .

In the second example, we have $ f(i) = i+1 $ , so we want to find $ \sum_{i=0}^{10^9} i+1 $ .

In the third example, the frog can't make any jumps in any case.

## 样例 #1

### 输入

```
7 5 3

```

### 输出

```
19

```

## 样例 #2

### 输入

```
1000000000 1 2019

```

### 输出

```
500000001500000001

```

## 样例 #3

### 输入

```
100 100000 1

```

### 输出

```
101

```

## 样例 #4

### 输入

```
6 4 5

```

### 输出

```
10

```

