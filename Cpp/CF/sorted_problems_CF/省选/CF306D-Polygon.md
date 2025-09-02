---
title: "Polygon"
layout: "post"
diff: 省选/NOI-
pid: CF306D
tag: []
---

# Polygon

## 题目描述

Polycarpus loves convex polygons, especially if all their angles are the same and all their sides are different. Draw for him any such polygon with the given number of vertexes.

## 输入格式

The input contains a single integer $ n $ ( $ 3<=n<=100 $ ) — the number of the polygon vertexes.

## 输出格式

Print $ n $ lines, containing the coordinates of the vertexes of the $ n $ -gon " $ x_{i} $ $ y_{i} $ " in the counter clockwise order. The coordinates of the vertexes shouldn't exceed $ 10^{6} $ in their absolute value. The side lengths should fit within limits $ [1,1000] $ (not necessarily integer). Mutual comparing sides and angles of your polygon during the test will go with precision of $ 10^{-3} $ .

If there is no solution, print "No solution" (without the quotes).

## 样例 #1

### 输入

```
8

```

### 输出

```
1.000 0.000
7.000 0.000
9.000 2.000
9.000 3.000
5.000 7.000
3.000 7.000
0.000 4.000
0.000 1.000

```

