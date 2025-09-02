---
title: "Special Olympics"
layout: "post"
diff: 普及+/提高
pid: CF199B
tag: []
---

# Special Olympics

## 题目描述

A renowned abstract artist Sasha, drawing inspiration from nowhere, decided to paint a picture entitled "Special Olympics". He justly thought that, if the regular Olympic games have five rings, then the Special ones will do with exactly two rings just fine.

Let us remind you that a ring is a region located between two concentric circles with radii $ r $ and $ R $ $ (r&lt;R) $ . These radii are called internal and external, respectively. Concentric circles are circles with centers located at the same point.

Soon a white canvas, which can be considered as an infinite Cartesian plane, had two perfect rings, painted with solid black paint. As Sasha is very impulsive, the rings could have different radii and sizes, they intersect and overlap with each other in any way. We know only one thing for sure: the centers of the pair of rings are not the same.

When Sasha got tired and fell into a deep sleep, a girl called Ilona came into the room and wanted to cut a circle for the sake of good memories. To make the circle beautiful, she decided to cut along the contour.

We'll consider a contour to be a continuous closed line through which there is transition from one color to another (see notes for clarification). If the contour takes the form of a circle, then the result will be cutting out a circle, which Iona wants.

But the girl's inquisitive mathematical mind does not rest: how many ways are there to cut a circle out of the canvas?

## 输入格式

The input contains two lines.

Each line has four space-separated integers $ x_{i} $ , $ y_{i} $ , $ r_{i} $ , $ R_{i} $ , that describe the $ i $ -th ring; $ x_{i} $ and $ y_{i} $ are coordinates of the ring's center, $ r_{i} $ and $ R_{i} $ are the internal and external radii of the ring correspondingly $ (-100<=x_{i},y_{i}<=100; 1<=r_{i}&lt;R_{i}<=100) $ .

It is guaranteed that the centers of the rings do not coinside.

## 输出格式

A single integer — the number of ways to cut out a circle from the canvas.

## 说明/提示

Figures for test samples are given below. The possible cuts are marked with red dotted line.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF199B/f6b80d43e3ef1e929ab8f5af0b211e93ea4d386a.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF199B/5e144d7158ec39b95e73e197fcc3c0319bf3cf78.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF199B/a3ad867f0752e7a06a2c050bd00ad9db2313f977.png)

## 样例 #1

### 输入

```
60 60 45 55
80 80 8 32

```

### 输出

```
1
```

## 样例 #2

### 输入

```
60 60 45 55
80 60 15 25

```

### 输出

```
4
```

## 样例 #3

### 输入

```
50 50 35 45
90 50 35 45

```

### 输出

```
0
```

