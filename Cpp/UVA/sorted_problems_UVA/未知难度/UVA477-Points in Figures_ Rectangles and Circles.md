---
title: "Points in Figures: Rectangles and Circles"
layout: "post"
diff: 难度0
pid: UVA477
tag: []
---

# Points in Figures: Rectangles and Circles

## 题目描述

给你一些矩形，与圆形在平面上的位置，以及一些点的坐标。

求出每个点被包含在哪个图形里。

## 输入格式

初始每行会有小写字母 $c$ 或 $r$。

如果是 $r$ 代表此图形是矩形，有四个值：

左上角点的坐标 $(x_1,y_1)$ 与右下角的坐标 $(x_2,y_2)$。

如果是 $c$ 代表此图形是圆形，有三个值：

圆心的坐标 $(x,y)$ 与半径。

当一行第一个字符为 * 时停止输入图形。

接下来每一行有两个数，代表这个点的坐标 $(x,y)$。

如果坐标为$(9999.9,9999.9)$，则停止输入。

## 输出格式

依次每行输出每个点被包含在第几个图形里。

例如1号点被包含在3号图形。

输出`Point 1 is contained in figure 3`。

如果2号点没有被包含在任何点里。

输出`Point 2 is not contained in any figure`。

## 样例 #1

### 输入

```
r 8.5 17.0 25.5 -8.5
c 20.2 7.3 5.8
r 0.0 10.3 5.5 0.0
c -5.0 -5.0 3.7
r 2.5 12.5 12.5 2.5
c 5.0 15.0 7.2
*
2.0 2.0
4.7 5.3
6.9 11.2
20.0 20.0
17.6 3.2
-5.2 -7.8
9999.9 9999.9
```

### 输出

```
Point 1 is contained in figure 3
Point 2 is contained in figure 3
Point 2 is contained in figure 5
Point 3 is contained in figure 5
Point 3 is contained in figure 6
Point 4 is not contained in any figure
Point 5 is contained in figure 1
Point 5 is contained in figure 2
Point 6 is contained in figure 4
```

