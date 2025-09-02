---
title: "Optimal Polygon Perimeter"
layout: "post"
diff: 普及+/提高
pid: CF1044C
tag: []
---

# Optimal Polygon Perimeter

## 题目描述

You are given $ n $ points on the plane. The polygon formed from all the $ n $ points is strictly convex, that is, the polygon is convex, and there are no three collinear points (i.e. lying in the same straight line). The points are numbered from $ 1 $ to $ n $ , in clockwise order.

We define the distance between two points $ p_1 = (x_1, y_1) $ and $ p_2 = (x_2, y_2) $ as their Manhattan distance: $ $$$d(p_1, p_2) = |x_1 - x_2| + |y_1 - y_2|. $ $ </p><p>Furthermore, we define the perimeter of a polygon, as the sum of Manhattan distances between all adjacent pairs of points on it; if the points on the polygon are ordered as  $ p\_1, p\_2, \\ldots, p\_k $   $ (k \\geq 3) $ , then the perimeter of the polygon is  $ d(p\_1, p\_2) + d(p\_2, p\_3) + \\ldots + d(p\_k, p\_1) $ .</p><p>For some parameter  $ k $ , let's consider all the polygons that can be formed from the given set of points, having <span class="tex-font-style-bf">any</span>  $ k $  vertices, such that the polygon is <span class="tex-font-style-bf">not</span> self-intersecting. For each such polygon, let's consider its perimeter. Over all such perimeters, we define  $ f(k) $  to be the maximal perimeter.</p><p>Please note, when checking whether a polygon is self-intersecting, that the edges of a polygon are still drawn as straight lines. For instance, in the following pictures:</p><center> <img class="tex-graphics" src="/predownloaded/4e/c2/4ec25e6ecb8feac3ac0b9b7fa51a118c2b777e87.png" style="max-width: 100.0%;max-height: 100.0%;" /> </center><p>In the middle polygon, the order of points ( $ p\_1, p\_3, p\_2, p\_4 $ ) is not valid, since it is a self-intersecting polygon. The right polygon (whose edges resemble the Manhattan distance) has the same order and is not self-intersecting, but we consider edges as straight lines. The correct way to draw this polygon is ( $ p\_1, p\_2, p\_3, p\_4 $ ), which is the left polygon.</p><p>Your task is to compute  $ f(3), f(4), \\ldots, f(n) $ . In other words, find the maximum possible perimeter for each possible number of points (i.e.  $ 3 $  to  $ n$$$).

## 输入格式

The first line contains a single integer $ n $ ( $ 3 \leq n \leq 3\cdot 10^5 $ ) — the number of points.

Each of the next $ n $ lines contains two integers $ x_i $ and $ y_i $ ( $ -10^8 \leq x_i, y_i \leq 10^8 $ ) — the coordinates of point $ p_i $ .

The set of points is guaranteed to be convex, all points are distinct, the points are ordered in clockwise order, and there will be no three collinear points.

## 输出格式

For each $ i $ ( $ 3\leq i\leq n $ ), output $ f(i) $ .

## 说明/提示

In the first example, for $ f(3) $ , we consider four possible polygons:

- ( $ p_1, p_2, p_3 $ ), with perimeter $ 12 $ .
- ( $ p_1, p_2, p_4 $ ), with perimeter $ 8 $ .
- ( $ p_1, p_3, p_4 $ ), with perimeter $ 12 $ .
- ( $ p_2, p_3, p_4 $ ), with perimeter $ 12 $ .

For $ f(4) $ , there is only one option, taking all the given points. Its perimeter $ 14 $ .

In the second example, there is only one possible polygon. Its perimeter is $ 8 $ .

## 样例 #1

### 输入

```
4
2 4
4 3
3 0
1 3

```

### 输出

```
12 14 
```

## 样例 #2

### 输入

```
3
0 0
0 2
2 0

```

### 输出

```
8 
```

