---
title: "Square and Rectangles"
layout: "post"
diff: 普及/提高-
pid: CF325A
tag: []
---

# Square and Rectangles

## 题目描述

You are given $ n $ rectangles. The corners of rectangles have integer coordinates and their edges are parallel to the $ Ox $ and $ Oy $ axes. The rectangles may touch each other, but they do not overlap (that is, there are no points that belong to the interior of more than one rectangle).

Your task is to determine if the rectangles form a square. In other words, determine if the set of points inside or on the border of at least one rectangle is precisely equal to the set of points inside or on the border of some square.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=5 $ ). Next $ n $ lines contain four integers each, describing a single rectangle: $ x_{1} $ , $ y_{1} $ , $ x_{2} $ , $ y_{2} $ ( $ 0<=x_{1}&lt;x_{2}<=31400,0<=y_{1}&lt;y_{2}<=31400 $ ) — $ x_{1} $ and $ x_{2} $ are $ x $ -coordinates of the left and right edges of the rectangle, and $ y_{1} $ and $ y_{2} $ are $ y $ -coordinates of the bottom and top edges of the rectangle.

No two rectangles overlap (that is, there are no points that belong to the interior of more than one rectangle).

## 输出格式

In a single line print "YES", if the given rectangles form a square, or "NO" otherwise.

## 样例 #1

### 输入

```
5
0 0 2 3
0 3 3 5
2 0 5 2
3 2 5 5
2 2 3 3

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
4
0 0 2 3
0 3 3 5
2 0 5 2
3 2 5 5

```

### 输出

```
NO

```

