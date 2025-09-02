---
title: "Vasily the Bear and Triangle"
layout: "post"
diff: 入门
pid: CF336A
tag: []
---

# Vasily the Bear and Triangle

## 题目描述

Vasily the bear has a favorite rectangle, it has one vertex at point $ (0,0) $ , and the opposite vertex at point $ (x,y) $ . Of course, the sides of Vasya's favorite rectangle are parallel to the coordinate axes.

Vasya also loves triangles, if the triangles have one vertex at point $ B=(0,0) $ . That's why today he asks you to find two points $ A=(x_{1},y_{1}) $ and $ C=(x_{2},y_{2}) $ , such that the following conditions hold:

- the coordinates of points: $ x_{1} $ , $ x_{2} $ , $ y_{1} $ , $ y_{2} $ are integers. Besides, the following inequation holds: $ x_{1}&lt;x_{2} $ ;
- the triangle formed by point $ A $ , $ B $ and $ C $ is rectangular and isosceles (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336A/722fcc24f0ddfe8fedfe378a89e62bfed7c996ca.png) is right);
- all points of the favorite rectangle are located inside or on the border of triangle $ ABC $ ;
- the area of triangle $ ABC $ is as small as possible.

Help the bear, find the required points. It is not so hard to proof that these points are unique.

## 输入格式

The first line contains two integers $ x,y $ $ (-10^{9}<=x,y<=10^{9},x≠0,y≠0) $ .

## 输出格式

Print in the single line four integers $ x_{1},y_{1},x_{2},y_{2} $ — the coordinates of the required points.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336A/896cbfe600ef69dca7f4621525643522b7e1ceb2.png)

Figure to the first sample

## 样例 #1

### 输入

```
10 5

```

### 输出

```
0 15 15 0

```

## 样例 #2

### 输入

```
-10 5

```

### 输出

```
-15 0 0 15

```

