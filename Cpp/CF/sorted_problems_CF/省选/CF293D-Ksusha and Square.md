---
title: "Ksusha and Square"
layout: "post"
diff: 省选/NOI-
pid: CF293D
tag: []
---

# Ksusha and Square

## 题目描述

Ksusha is a vigorous mathematician. She is keen on absolutely incredible mathematical riddles.

Today Ksusha came across a convex polygon of non-zero area. She is now wondering: if she chooses a pair of distinct points uniformly among all integer points (points with integer coordinates) inside or on the border of the polygon and then draws a square with two opposite vertices lying in the chosen points, what will the expectation of this square's area be?

A pair of distinct points is chosen uniformly among all pairs of distinct points, located inside or on the border of the polygon. Pairs of points $ p,q $ $ (p≠q) $ and $ q,p $ are considered the same.

Help Ksusha! Count the required expectation.

## 输入格式

The first line contains integer $ n $ $ (3<=n<=10^{5}) $ — the number of vertices of Ksusha's convex polygon. Next $ n $ lines contain the coordinates of the polygon vertices in clockwise or counterclockwise order. The $ i $ -th line contains integers $ x_{i},y_{i} $ $ (|x_{i}|,|y_{i}|<=10^{6}) $ — the coordinates of the vertex that goes $ i $ -th in that order.

## 输出格式

Print a single real number — the required expected area.

The answer will be considered correct if its absolute and relative error doesn't exceed $ 10^{-6} $ .

## 样例 #1

### 输入

```
3
0 0
5 5
5 0

```

### 输出

```
4.6666666667

```

## 样例 #2

### 输入

```
4
-1 3
4 5
6 2
3 -5

```

### 输出

```
8.1583333333

```

## 样例 #3

### 输入

```
3
17 136
859 937
16 641

```

### 输出

```
66811.3704155169

```

