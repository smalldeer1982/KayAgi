---
title: "Convex Countour"
layout: "post"
diff: 提高+/省选-
pid: CF838E
tag: []
---

# Convex Countour

## 题目描述

You are given an strictly convex polygon with $ n $ vertices. It is guaranteed that no three points are collinear. You would like to take a maximum non intersecting path on the polygon vertices that visits each point at most once.

More specifically your path can be represented as some sequence of distinct polygon vertices. Your path is the straight line segments between adjacent vertices in order. These segments are not allowed to touch or intersect each other except at the vertices in your sequence.

Given the polygon, print the maximum length non-intersecting path that visits each point at most once.

## 输入格式

The first line of input will contain a single integer $ n $ ( $ 2<=n<=2500 $ ), the number of points.

The next $ n $ lines will contain two integers $ x_{i},y_{i} $ ( $ |x_{i}|,|y_{i}|<=10^{9} $ ), denoting the coordinates of the $ i $ -th vertex.

It is guaranteed that these points are listed in clockwise order.

## 输出格式

Print a single floating point number, representing the longest non-intersecting path that visits the vertices at most once.

Your answer will be accepted if it has absolute or relative error at most $ 10^{-9} $ . More specifically, if your answer is $ a $ and the jury answer is $ b $ , your answer will be accepted if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF838E/d8d110e69d298146d951837cc2710d1c4cc74a7d.png).

## 说明/提示

One optimal path is to visit points 0,1,3,2 in order.

## 样例 #1

### 输入

```
4
0 0
0 1
1 1
1 0

```

### 输出

```
3.4142135624

```

