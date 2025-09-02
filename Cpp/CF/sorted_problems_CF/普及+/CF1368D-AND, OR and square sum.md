---
title: "AND, OR and square sum"
layout: "post"
diff: 普及+/提高
pid: CF1368D
tag: []
---

# AND, OR and square sum

## 题目描述

### 题面描述

给定 $n$ 个非负整数 $a_1,\cdots,a_n$。

你可以进行如下操作：选择两个不同的下标 $i,j$ 满足 $1\leq i,j\leq n$，并将 $a_i\gets a_i\ \mathsf{AND}\ a_j,\ a_j\gets a_i\ \mathsf{OR}\ a_j$，**两个赋值同时进行**。AND 是按位与，OR 是按位或。

你可以进行任意次操作。求操作后所有数的平方和的最大值，即 $\max \sum a_i^2$。

## 输入格式

第一行一个整数 $n\ (1\leq n\leq 2\times 10^5)$。

第二行 $n$ 个整数 $a_1,\cdots,a_n\ (0\leq a_i<2^{20})$。

## 输出格式

输出一行一个整数表示答案，即操作后所有数的平方和的最大值。

Translated by Alex_Wei.

## 样例 #1

### 输入

```
1
123
```

### 输出

```
15129
```

## 样例 #2

### 输入

```
3
1 3 5
```

### 输出

```
51
```

## 样例 #3

### 输入

```
2
349525 699050
```

### 输出

```
1099509530625
```

