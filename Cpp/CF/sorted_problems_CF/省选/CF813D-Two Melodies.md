---
title: "Two Melodies"
layout: "post"
diff: 省选/NOI-
pid: CF813D
tag: []
---

# Two Melodies

## 题目描述

Alice is a beginner composer and now she is ready to create another masterpiece. And not even the single one but two at the same time!

Alice has a sheet with $ n $ notes written on it. She wants to take two such non-empty non-intersecting subsequences that both of them form a melody and sum of their lengths is maximal.

Subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

Subsequence forms a melody when each two adjacent notes either differs by 1 or are congruent modulo 7.

You should write a program which will calculate maximum sum of lengths of such two non-empty non-intersecting subsequences that both of them form a melody.

## 输入格式

The first line contains one integer number $ n $ ( $ 2<=n<=5000 $ ).

The second line contains $ n $ integer numbers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{5} $ ) — notes written on a sheet.

## 输出格式

Print maximum sum of lengths of such two non-empty non-intersecting subsequences that both of them form a melody.

## 说明/提示

In the first example subsequences $ [1,2] $ and $ [4,5] $ give length 4 in total.

In the second example subsequences $ [62,48,49] $ and $ [60,61] $ give length 5 in total. If you choose subsequence $ [62,61] $ in the first place then the second melody will have maximum length 2, that gives the result of 4, which is not maximal.

## 样例 #1

### 输入

```
4
1 2 4 5

```

### 输出

```
4

```

## 样例 #2

### 输入

```
6
62 22 60 61 48 49

```

### 输出

```
5

```

