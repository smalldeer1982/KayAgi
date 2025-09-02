---
title: "Arithmetic Progression"
layout: "post"
diff: 普及+/提高
pid: CF382C
tag: []
---

# Arithmetic Progression

## 题目描述

Everybody knows what an arithmetic progression is. Let us remind you just in case that an arithmetic progression is such sequence of numbers $ a_{1},a_{2},...,a_{n} $ of length $ n $ , that the following condition fulfills:

 $ a_{2}-a_{1}=a_{3}-a_{2}=a_{4}-a_{3}=...=a_{i+1}-a_{i}=...=a_{n}-a_{n-1}. $ For example, sequences \[1, 5\], \[10\], \[5, 4, 3\] are arithmetic progressions and sequences \[1, 3, 2\], \[1, 2, 4\] are not.

Alexander has $ n $ cards containing integers. Arthur wants to give Alexander exactly one more card with a number so that he could use the resulting $ n+1 $ cards to make an arithmetic progression (Alexander has to use all of his cards).

Arthur has already bought a card but he hasn't written a number on it. Help him, print all integers that you can write on a card so that the described condition fulfilled.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{5}) $ — the number of cards. The next line contains the sequence of integers — the numbers on Alexander's cards. The numbers are positive integers, each of them doesn't exceed $ 10^{8} $ .

## 输出格式

If Arthur can write infinitely many distinct integers on the card, print on a single line -1.

Otherwise, print on the first line the number of integers that suit you. In the second line, print the numbers in the increasing order. Note that the numbers in the answer can exceed $ 10^{8} $ or even be negative (see test samples).

## 样例 #1

### 输入

```
3
4 1 7

```

### 输出

```
2
-2 10

```

## 样例 #2

### 输入

```
1
10

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
4
1 3 5 9

```

### 输出

```
1
7

```

## 样例 #4

### 输入

```
4
4 3 4 5

```

### 输出

```
0

```

## 样例 #5

### 输入

```
2
2 4

```

### 输出

```
3
0 3 6

```

