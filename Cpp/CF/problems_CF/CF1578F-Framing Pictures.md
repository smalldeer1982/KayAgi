---
title: "Framing Pictures"
layout: "post"
diff: 省选/NOI-
pid: CF1578F
tag: []
---

# Framing Pictures

## 题目描述

Life has been discovered on Venus! What is more, the life forms appear to be convex polygons. An international consortium is designing a probe to send to Venus to take pictures, but they need to estimate the bandwidth needed to send back pictures.

When the probe takes a picture of a life form and wishes to send it back to Earth, the bandwidth required is proportional to the area of the bounding box (in other words, the smallest axis-aligned rectangle that contains the life-form). The shape and size of the life forms are known, but the orientation relative to the camera is random. You must thus determine the expected (average) area of the bounding box across all orientations.

## 输入格式

The input describes the shape of a life form as a convex polygon in two dimensions.

The first line of input contains an integer $ n $ ( $ 3 \le n \le 200\,000 $ ) — the number of vertices. The remaining $ n $ lines each contain two integers $ x $ and $ y $ ( $ -10^9 \le x, y \le 10^9 $ ) — the coordinates of a vertex. The vertices are given in counterclockwise order, and no three vertices lie on a straight line.

## 输出格式

Output a single line containing the expected area of the bounding box of the polygon. Your answer should have an absolute or relative error of at most $ 10^{-6} $ .

## 说明/提示

The pictures show example life forms and various camera orientations.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1578F/7bf5484b8f790ebf466874683ff7667e104e8a6b.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1578F/7e42566134414108c937e1e5ff26ff9d1b86c9db.png)

## 样例 #1

### 输入

```
4
0 0
10 0
10 10
0 10
```

### 输出

```
163.661977237
```

## 样例 #2

### 输入

```
5
0 0
10 0
15 8
5 20
-5 7
```

### 输出

```
365.666028588
```

