---
title: "Amr and Pins"
layout: "post"
diff: 普及/提高-
pid: CF507B
tag: []
---

# Amr and Pins

## 题目描述

Amr loves Geometry. One day he came up with a very interesting problem.

Amr has a circle of radius $ r $ and center in point $ (x,y) $ . He wants the circle center to be in new position $ (x',y') $ .

In one step Amr can put a pin to the border of the circle in a certain point, then rotate the circle around that pin by any angle and finally remove the pin.

Help Amr to achieve his goal in minimum number of steps.

## 输入格式

Input consists of 5 space-separated integers $ r $ , $ x $ , $ y $ , $ x' $ $ y' $ ( $ 1<=r<=10^{5} $ , $ -10^{5}<=x,y,x',y'<=10^{5} $ ), circle radius, coordinates of original center of the circle and coordinates of destination center of the circle respectively.

## 输出格式

Output a single integer — minimum number of steps required to move the center of the circle to the destination point.

## 说明/提示

In the first sample test the optimal way is to put a pin at point $ (0,2) $ and rotate the circle by $ 180 $ degrees counter-clockwise (or clockwise, no matter).

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF507B/a26ac87b2d0412fb38dc1bc7b7b71315dcd60080.png)

## 样例 #1

### 输入

```
2 0 0 0 4

```

### 输出

```
1

```

## 样例 #2

### 输入

```
1 1 1 4 4

```

### 输出

```
3

```

## 样例 #3

### 输入

```
4 5 6 5 6

```

### 输出

```
0

```

