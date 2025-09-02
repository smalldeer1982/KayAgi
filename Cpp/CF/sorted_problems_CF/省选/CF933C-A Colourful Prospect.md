---
title: "A Colourful Prospect"
layout: "post"
diff: 省选/NOI-
pid: CF933C
tag: []
---

# A Colourful Prospect

## 题目描述

Firecrackers scare Nian the monster, but they're wayyyyy too noisy! Maybe fireworks make a nice complement.

Little Tommy is watching a firework show. As circular shapes spread across the sky, a splendid view unfolds on the night of Lunar New Year's eve.

A wonder strikes Tommy. How many regions are formed by the circles on the sky? We consider the sky as a flat plane. A region is a connected part of the plane with positive area, whose bound consists of parts of bounds of the circles and is a curve or several curves without self-intersections, and that does not contain any curve other than its boundaries. Note that exactly one of the regions extends infinitely.

## 输入格式

The first line of input contains one integer $ n $ ( $ 1<=n<=3 $ ), denoting the number of circles.

The following $ n $ lines each contains three space-separated integers $ x $ , $ y $ and $ r $ ( $ -10<=x,y<=10 $ , $ 1<=r<=10 $ ), describing a circle whose center is $ (x,y) $ and the radius is $ r $ . No two circles have the same $ x $ , $ y $ and $ r $ at the same time.

## 输出格式

Print a single integer — the number of regions on the plane.

## 说明/提示

For the first example,

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF933C/14c0de76a74c3258bd3ded40e0d00e7a0e02f324.png)For the second example,

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF933C/3893f9bc640d7c681b3a0c6aad769a8cc35a6b03.png)For the third example,

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF933C/6be8f427aaa2ce9d8da71a1bbf6003246592b3ca.png)

## 样例 #1

### 输入

```
3
0 0 1
2 0 1
4 0 1

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3
0 0 2
3 0 2
6 0 2

```

### 输出

```
6

```

## 样例 #3

### 输入

```
3
0 0 2
2 0 2
1 1 2

```

### 输出

```
8

```

