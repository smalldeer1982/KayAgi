---
title: "Supercentral Point"
layout: "post"
diff: 普及-
pid: CF165A
tag: []
---

# Supercentral Point

## 题目描述

One day Vasya painted a Cartesian coordinate system on a piece of paper and marked some set of points $ (x_{1},y_{1}),(x_{2},y_{2}),...,(x_{n},y_{n}) $ . Let's define neighbors for some fixed point from the given set $ (x,y) $ :

- point $ (x',y') $ is $ (x,y) $ 's right neighbor, if $ x'&gt;x $ and $ y'=y $
- point $ (x',y') $ is $ (x,y) $ 's left neighbor, if $ x'&lt;x $ and $ y'=y $
- point $ (x',y') $ is $ (x,y) $ 's lower neighbor, if $ x'=x $ and $ y'&lt;y $
- point $ (x',y') $ is $ (x,y) $ 's upper neighbor, if $ x'=x $ and $ y'&gt;y $

We'll consider point $ (x,y) $ from the given set supercentral, if it has at least one upper, at least one lower, at least one left and at least one right neighbor among this set's points.

Vasya marked quite many points on the paper. Analyzing the picture manually is rather a challenge, so Vasya asked you to help him. Your task is to find the number of supercentral points in the given set.

## 输入格式

The first input line contains the only integer $ n $ ( $ 1<=n<=200 $ ) — the number of points in the given set. Next $ n $ lines contain the coordinates of the points written as " $ x $ $ y $ " (without the quotes) ( $ |x|,|y|<=1000 $ ), all coordinates are integers. The numbers in the line are separated by exactly one space. It is guaranteed that all points are different.

## 输出格式

Print the only number — the number of supercentral points of the given set.

## 说明/提示

In the first sample the supercentral points are only points $ (1,1) $ and $ (1,2) $ .

In the second sample there is one supercental point — point $ (0,0) $ .

## 样例 #1

### 输入

```
8
1 1
4 2
3 1
1 2
0 2
0 1
1 0
1 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
0 0
0 1
1 0
0 -1
-1 0

```

### 输出

```
1

```

