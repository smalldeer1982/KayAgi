---
title: "Wilbur and Swimming Pool"
layout: "post"
diff: 普及-
pid: CF596A
tag: []
---

# Wilbur and Swimming Pool

## 题目描述

After making bad dives into swimming pools, Wilbur wants to build a swimming pool in the shape of a rectangle in his backyard. He has set up coordinate axes, and he wants the sides of the rectangle to be parallel to them. Of course, the area of the rectangle must be positive. Wilbur had all four vertices of the planned pool written on a paper, until his friend came along and erased some of the vertices.

Now Wilbur is wondering, if the remaining $ n $ vertices of the initial rectangle give enough information to restore the area of the planned swimming pool.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=4 $ ) — the number of vertices that were not erased by Wilbur's friend.

Each of the following $ n $ lines contains two integers $ x_{i} $ and $ y_{i} $ ( $ -1000<=x_{i},y_{i}<=1000 $ ) —the coordinates of the $ i $ -th vertex that remains. Vertices are given in an arbitrary order.

It's guaranteed that these points are distinct vertices of some rectangle, that has positive area and which sides are parallel to the coordinate axes.

## 输出格式

Print the area of the initial rectangle if it could be uniquely determined by the points remaining. Otherwise, print $ -1 $ .

## 说明/提示

In the first sample, two opposite corners of the initial rectangle are given, and that gives enough information to say that the rectangle is actually a unit square.

In the second sample there is only one vertex left and this is definitely not enough to uniquely define the area.

## 样例 #1

### 输入

```
2
0 0
1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
1
1 1

```

### 输出

```
-1

```

