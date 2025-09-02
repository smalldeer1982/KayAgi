---
title: "Ilya and Sticks"
layout: "post"
diff: 普及/提高-
pid: CF525C
tag: []
---

# Ilya and Sticks

## 题目描述

In the evening, after the contest Ilya was bored, and he really felt like maximizing. He remembered that he had a set of $ n $ sticks and an instrument. Each stick is characterized by its length $ l_{i} $ .

Ilya decided to make a rectangle from the sticks. And due to his whim, he decided to make rectangles in such a way that maximizes their total area. Each stick is used in making at most one rectangle, it is possible that some of sticks remain unused. Bending sticks is not allowed.

Sticks with lengths $ a_{1} $ , $ a_{2} $ , $ a_{3} $ and $ a_{4} $ can make a rectangle if the following properties are observed:

- $ a_{1}<=a_{2}<=a_{3}<=a_{4} $
- $ a_{1}=a_{2} $
- $ a_{3}=a_{4} $

A rectangle can be made of sticks with lengths of, for example, $ 3 3 3 3 $ or $ 2 2 4 4 $ . A rectangle cannot be made of, for example, sticks $ 5 5 5 7 $ .

Ilya also has an instrument which can reduce the length of the sticks. The sticks are made of a special material, so the length of each stick can be reduced by at most one. For example, a stick with length $ 5 $ can either stay at this length or be transformed into a stick of length $ 4 $ .

You have to answer the question — what maximum total area of the rectangles can Ilya get with a file if makes rectangles from the available sticks?

## 输入格式

The first line of the input contains a positive integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of the available sticks.

The second line of the input contains $ n $ positive integers $ l_{i} $ ( $ 2<=l_{i}<=10^{6} $ ) — the lengths of the sticks.

## 输出格式

The first line of the output must contain a single non-negative integer — the maximum total area of the rectangles that Ilya can make from the available sticks.

## 样例 #1

### 输入

```
4
2 4 4 2

```

### 输出

```
8

```

## 样例 #2

### 输入

```
4
2 2 3 5

```

### 输出

```
0

```

## 样例 #3

### 输入

```
4
100003 100004 100005 100006

```

### 输出

```
10000800015

```

