---
title: "Set of Points"
layout: "post"
diff: 提高+/省选-
pid: CF277B
tag: []
---

# Set of Points

## 题目描述

Convexity of a set of points on the plane is the size of the largest subset of points that form a convex polygon. Your task is to build a set of $ n $ points with the convexity of exactly $ m $ . Your set of points should not contain three points that lie on a straight line.

## 输入格式

The single line contains two integers $ n $ and $ m $ ( $ 3<=m<=100,m<=n<=2m $ ).

## 输出格式

If there is no solution, print "-1". Otherwise, print $ n $ pairs of integers — the coordinates of points of any set with the convexity of $ m $ . The coordinates shouldn't exceed $ 10^{8} $ in their absolute value.

## 样例 #1

### 输入

```
4 3

```

### 输出

```
0 0
3 0
0 3
1 1

```

## 样例 #2

### 输入

```
6 3

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
6 6

```

### 输出

```
10 0
-10 0
10 1
9 1
9 -1
0 -2

```

## 样例 #4

### 输入

```
7 4

```

### 输出

```
176166 6377
709276 539564
654734 174109
910147 434207
790497 366519
606663 21061
859328 886001

```

