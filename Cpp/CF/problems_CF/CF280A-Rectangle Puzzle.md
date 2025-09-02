---
title: "Rectangle Puzzle"
layout: "post"
diff: 普及+/提高
pid: CF280A
tag: []
---

# Rectangle Puzzle

## 题目描述

You are given two rectangles on a plane. The centers of both rectangles are located in the origin of coordinates (meaning the center of the rectangle's symmetry). The first rectangle's sides are parallel to the coordinate axes: the length of the side that is parallel to the $ Ox $ axis, equals $ w $ , the length of the side that is parallel to the $ Oy $ axis, equals $ h $ . The second rectangle can be obtained by rotating the first rectangle relative to the origin of coordinates by angle $ α $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF280A/052b43ecd665cd6e4ffd3e118c46f92dcd4eb612.png)Your task is to find the area of the region which belongs to both given rectangles. This region is shaded in the picture.

## 输入格式

The first line contains three integers $ w,h,α $ $ (1<=w,h<=10^{6}; 0<=α<=180) $ . Angle $ α $ is given in degrees.

## 输出格式

In a single line print a real number — the area of the region which belongs to both given rectangles.

The answer will be considered correct if its relative or absolute error doesn't exceed $ 10^{-6} $ .

## 说明/提示

The second sample has been drawn on the picture above.

## 样例 #1

### 输入

```
1 1 45

```

### 输出

```
0.828427125

```

## 样例 #2

### 输入

```
6 4 30

```

### 输出

```
19.668384925

```

