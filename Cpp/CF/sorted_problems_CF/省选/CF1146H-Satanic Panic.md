---
title: "Satanic Panic"
layout: "post"
diff: 省选/NOI-
pid: CF1146H
tag: ['动态规划 DP', '计算几何', '区间 DP']
---

# Satanic Panic

## 题目描述

You are given a set of $ n $ points in a 2D plane. No three points are collinear.

A pentagram is a set of $ 5 $ points $ A,B,C,D,E $ that can be arranged as follows. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/f942ae06c7e29cb9bc6462315be09bb7d5b4c362.png) Note the length of the line segments don't matter, only that those particular intersections exist.

Count the number of ways to choose $ 5 $ points from the given set that form a pentagram.

## 输入格式

The first line contains an integer $ n $ ( $ 5 \leq n \leq 300 $ ) — the number of points.

Each of the next $ n $ lines contains two integers $ x_i, y_i $ ( $ -10^6 \leq x_i,y_i \leq 10^6 $ ) — the coordinates of the $ i $ -th point. It is guaranteed that no three points are collinear.

## 输出格式

Print a single integer, the number of sets of $ 5 $ points that form a pentagram.

## 说明/提示

A picture of the first sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/ecb5db206846ce3b41c177fcaeaebe0ee2b1bb2a.png) A picture of the second sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/4f7f38f01a0904403461b302f8dc7d443ccc0e93.png) A picture of the third sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/d922b8e812b7b67b3a0bbbb474a47be87ee53781.png)

## 样例 #1

### 输入

```
5
0 0
0 2
2 0
2 2
1 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
0 0
4 0
0 4
4 4
2 3

```

### 输出

```
0

```

## 样例 #3

### 输入

```
10
841746 527518
595261 331297
-946901 129987
670374 -140388
-684770 309555
-302589 415564
-387435 613331
-624940 -95922
945847 -199224
24636 -565799

```

### 输出

```
85

```

