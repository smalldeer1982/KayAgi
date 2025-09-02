---
title: "Mice problem"
layout: "post"
diff: 普及+/提高
pid: CF793C
tag: []
---

# Mice problem

## 题目描述

Igor the analyst fell asleep on the work and had a strange dream. In the dream his desk was crowded with computer mice, so he bought a mousetrap to catch them.

The desk can be considered as an infinite plane, then the mousetrap is a rectangle which sides are parallel to the axes, and which opposite sides are located in points $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ .

Igor wants to catch all mice. Igor has analysed their behavior and discovered that each mouse is moving along a straight line with constant speed, the speed of the $ i $ -th mouse is equal to $ (v_{i}^{x},v_{i}^{y}) $ , that means that the $ x $ coordinate of the mouse increases by $ v_{i}^{x} $ units per second, while the $ y $ coordinates increases by $ v_{i}^{y} $ units. The mousetrap is open initially so that the mice are able to move freely on the desk. Igor can close the mousetrap at any moment catching all the mice that are strictly inside the mousetrap.

Igor works a lot, so he is busy in the dream as well, and he asks you to write a program that by given mousetrap's coordinates, the initial coordinates of the mice and their speeds determines the earliest time moment in which he is able to catch all the mice. Please note that Igor can close the mousetrap only once.

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=100000 $ ) — the number of computer mice on the desk.

The second line contains four integers $ x_{1} $ , $ y_{1} $ , $ x_{2} $ and $ y_{2} $ ( $ 0<=x_{1}<=x_{2}<=100000 $ ), ( $ 0<=y_{1}<=y_{2}<=100000 $ ) — the coordinates of the opposite corners of the mousetrap.

The next $ n $ lines contain the information about mice.

The $ i $ -th of these lines contains four integers $ r_{i}^{x} $ , $ r_{i}^{y} $ , $ v_{i}^{x} $ and $ v_{i}^{y} $ , ( $ 0<=r_{i}^{x},r_{i}^{y}<=100000 $ , $ -100000<=v_{i}^{x},v_{i}^{y}<=100000 $ ), where $ (r_{i}^{x},r_{i}^{y}) $ is the initial position of the mouse, and $ (v_{i}^{x},v_{i}^{y}) $ is its speed.

## 输出格式

In the only line print minimum possible non-negative number $ t $ such that if Igor closes the mousetrap at $ t $ seconds from the beginning, then all the mice are strictly inside the mousetrap. If there is no such $ t $ , print -1.

Your answer is considered correct if its absolute or relative error doesn't exceed $ 10^{-6} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer is considered correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793C/313939207300df9d9a3c0d148fdf8efe71d5f7e3.png).

## 说明/提示

Here is a picture of the first sample

Points A, B, C, D - start mice positions, segments are their paths.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793C/0c2fcb8709057e532ca0131544d2596c5ce57683.png)

Then, at first time when all mice will be in rectangle it will be looks like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793C/243afe4c229018b391d2ff30ae0186ebf1cbce8c.png)

Here is a picture of the second sample

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793C/c8ca503e68f8ea8d507deb9be3b10b823dad4205.png)

Points A, D, B will never enter rectangle.

## 样例 #1

### 输入

```
4
7 7 9 8
3 5 7 5
7 5 2 4
3 3 7 8
6 6 3 2

```

### 输出

```
0.57142857142857139685

```

## 样例 #2

### 输入

```
4
7 7 9 8
0 3 -5 4
5 0 5 4
9 9 -1 -6
10 5 -7 -10

```

### 输出

```
-1

```

