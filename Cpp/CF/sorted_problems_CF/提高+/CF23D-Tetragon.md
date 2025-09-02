---
title: "Tetragon"
layout: "post"
diff: 提高+/省选-
pid: CF23D
tag: []
---

# Tetragon

## 题目描述

You're given the centers of three equal sides of a strictly convex tetragon. Your task is to restore the initial tetragon.

## 输入格式

The first input line contains one number $ T $ — amount of tests ( $ 1<=T<=5·10^{4} $ ). Each of the following $ T $ lines contains numbers $ x_{1} $ , $ y_{1} $ , $ x_{2} $ , $ y_{2} $ , $ x_{3} $ , $ y_{3} $ — coordinates of different points that are the centers of three equal sides (non-negative integer numbers, not exceeding 10).

## 输出格式

For each test output two lines. If the required tetragon exists, output in the first line YES, in the second line — four pairs of numbers — coordinates of the polygon's vertices in clockwise or counter-clockwise order. Don't forget, please, that the tetragon should be strictly convex, i.e. no 3 of its points lie on one line. Output numbers with 9 characters after a decimal point.

If the required tetragon doen't exist, output NO in the first line, and leave the second line empty.

## 样例 #1

### 输入

```
3
1 1 2 2 3 3
0 1 1 0 2 2
9 3 7 9 9 8

```

### 输出

```
NO

YES
3.5 1.5 0.5 2.5 -0.5 -0.5 2.5 0.5
NO


```

