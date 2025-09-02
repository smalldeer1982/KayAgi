---
title: "Dasha and Puzzle"
layout: "post"
diff: 普及+/提高
pid: CF761E
tag: []
---

# Dasha and Puzzle

## 题目描述

Dasha decided to have a rest after solving the problem. She had been ready to start her favourite activity — origami, but remembered the puzzle that she could not solve.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF761E/f94317c6a4e9720232d894633f6f0c7ec38b7c88.png)The tree is a non-oriented connected graph without cycles. In particular, there always are $ n-1 $ edges in a tree with $ n $ vertices.

The puzzle is to position the vertices at the points of the Cartesian plane with integral coordinates, so that the segments between the vertices connected by edges are parallel to the coordinate axes. Also, the intersection of segments is allowed only at their ends. Distinct vertices should be placed at different points.

Help Dasha to find any suitable way to position the tree vertices on the plane.

It is guaranteed that if it is possible to position the tree vertices on the plane without violating the condition which is given above, then you can do it by using points with integral coordinates which don't exceed $ 10^{18} $ in absolute value.

## 输入格式

The first line contains single integer $ n $ $ (1<=n<=30) $ — the number of vertices in the tree.

Each of next $ n-1 $ lines contains two integers $ u_{i} $ , $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) that mean that the $ i $ -th edge of the tree connects vertices $ u_{i} $ and $ v_{i} $ .

It is guaranteed that the described graph is a tree.

## 输出格式

If the puzzle doesn't have a solution then in the only line print "NO".

Otherwise, the first line should contain "YES". The next $ n $ lines should contain the pair of integers $ x_{i} $ , $ y_{i} $ $ (|x_{i}|,|y_{i}|<=10^{18}) $ — the coordinates of the point which corresponds to the $ i $ -th vertex of the tree.

If there are several solutions, print any of them.

## 说明/提示

In the first sample one of the possible positions of tree is: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF761E/9f7bd78ab90b0ce22425fab0baf00155435088d1.png)

## 样例 #1

### 输入

```
7
1 2
1 3
2 4
2 5
3 6
3 7
```

### 输出

```
YES
0 0
1 0
0 1
2 0
1 -1
-1 1
0 2
```

## 样例 #2

### 输入

```
6
1 2
2 3
2 4
2 5
2 6

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
4
1 2
2 3
3 4
```

### 输出

```
YES
3 3
4 3
5 3
6 3
```

