---
title: "Geometric Progressions"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF571E
tag: []
---

# Geometric Progressions

## 题目描述

Geometric progression with the first element $ a $ and common ratio $ b $ is a sequence of numbers $ a,ab,ab^{2},ab^{3},... $ .

You are given $ n $ integer geometric progressions. Your task is to find the smallest integer $ x $ , that is the element of all the given progressions, or else state that such integer does not exist.

## 输入格式

The first line contains integer ( $ 1<=n<=100 $ ) — the number of geometric progressions.

Next $ n $ lines contain pairs of integers $ a,b $ ( $ 1<=a,b<=10^{9} $ ), that are the first element and the common ratio of the corresponding geometric progression.

## 输出格式

If the intersection of all progressions is empty, then print $ -1 $ , otherwise print the remainder of the minimal positive integer number belonging to all progressions modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

In the second sample test one of the progressions contains only powers of two, the other one contains only powers of three.

## 样例 #1

### 输入

```
2
2 2
4 1

```

### 输出

```
4

```

## 样例 #2

### 输入

```
2
2 2
3 3

```

### 输出

```
-1

```

