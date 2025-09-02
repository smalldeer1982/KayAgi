---
title: "POLY1 - Polygon"
layout: "post"
diff: 难度0
pid: SP175
tag: []
---

# POLY1 - Polygon

## 题目描述

如果两个三角形的内部至少有一个公共点，我们便称这两个三角形相交。一个多边形是凸多边形，当且仅当任意两点之间的线段都完全在多边形内。如果一个三角形的顶点也是凸多边形的顶点，那么这个三角形就被称为该多边形的基本三角形。将一个凸多边形进行三角剖分，指的是将其划分为若干个基本三角形，并要求这些三角形互不相交，且它们的组合要完全覆盖整个多边形。现给定一个凸多边形及其三角剖分，请问该多边形的一个基本三角形最多可以与剖分中的多少个三角形相交。

## 输入格式

第一行输入一个整数 $t$，表示测试用例的数量。接下来是 $t$ 个测试用例，每个测试用例之间用空行分隔。

每个测试用例的第一行包含一个整数 $n$（$3 \leq n \leq 1000$），表示多边形的顶点数。顶点按顺时针方向编号为 $0$ 到 $n-1$。接下来的 $n-2$ 行描述了三角剖分中的每个三角形，每行有三个整数，表示第 $i$ 个三角形的顶点编号，这里 $1 \leq i \leq n-2$。

## 输出格式

对于每个测试用例，输出一个整数，表示对于给定的三角剖分，该多边形的一个基本三角形能够相交的最大三角形数量。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
The number of test cases t is in the first line of input, then t test cases follow separated by an empty line
In the first line of a test case there is a number n, 3 &lt;= n &lt;= 1000, which equals the number of vertices of the polygon. The vertices of the polygon are numbered from 0 to n-1 clockwise. The following n-2 lines describe the triangles in the triangulation. There are three integers separated by single spaces in the (i+1)-st line, where 1 &lt;= i &lt;= n-2. These are the numbers of the vertices of the i-th triangle in the triangulation.
```

### 输出

```
For each test case your program should produce one line with exactly one integer - the maximal number of triangles in the triangulation, that can be intersected by a single elementary triangle of the input polygon. 

Example
Sample input:
1
6
0 1 2
2 4 3
0 5 4
2 4 0

Sample output:
4
```

## 样例 #2

### 输入

```
1
6
0 1 2
2 4 3
0 5 4
2 4 0
```

### 输出

```
None
```

