---
title: "The Collatz Sequence"
layout: "post"
diff: 难度0
pid: UVA694
tag: []
---

# The Collatz Sequence

## 题目描述

### 题目
Collatz序列

### 题意
Lothar Collatz 发明了一种算法，它以以下的规则生成序列：

1. 任选一个正整数 $A$ 作为序列的第一项；
2. 如果 $A = 1$ ，停止计算；
3. 如果 $A$ 是偶数，那么 $A$ 的值变为 $\Large{\frac{A}{2}}$ ，并跳转到第二步；
4. 如果 $A$ 是奇数，那么 $A$ 的值变为 $3 \times A + 1$ ，并跳转到第二步；

现在，我们再给这一算法加上一个限制：如果任意一次计算中 $A$ 的值大于一个给定的数 $L$ ，那么停止计算。

## 输入格式

输入有多组数据，其中每一组一行，为两个正整数 $A$ 和 $L$ ，输入以 $-1\ -1$ 结束。

## 输出格式

对于每一组数据，输出 `Case x: A = a, limit = l, number of terms = n` 格式的一行，其中 `x` 为数据组编号， `a` 为输入的 $A$ ， `l` 为输入的 $L$ ， `n` 为计算结束时序列的长度（计算的次数）。

## 说明/提示

$0 < A, L \le 2147483647$

## 样例 #1

### 输入

```
3 100
34 100
75 250
27 2147483647
101 304
101 303
-1 -1
```

### 输出

```
Case 1: A = 3, limit = 100, number of terms = 8
Case 2: A = 34, limit = 100, number of terms = 14
Case 3: A = 75, limit = 250, number of terms = 3
Case 4: A = 27, limit = 2147483647, number of terms = 112
Case 5: A = 101, limit = 304, number of terms = 26
Case 6: A = 101, limit = 303, number of terms = 1
```

