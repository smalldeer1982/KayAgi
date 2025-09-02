---
title: "Points, Lines and Ready-made Titles"
layout: "post"
diff: 提高+/省选-
pid: CF870E
tag: []
---

# Points, Lines and Ready-made Titles

## 题目描述

You are given $ n $ distinct points on a plane with integral coordinates. For each point you can either draw a vertical line through it, draw a horizontal line through it, or do nothing.

You consider several coinciding straight lines as a single one. How many distinct pictures you can get? Print the answer modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of points.

 $ n $ lines follow. The ( $ i+1 $ )-th of these lines contains two integers $ x_{i} $ , $ y_{i} $ ( $ -10^{9}<=x_{i},y_{i}<=10^{9} $ ) — coordinates of the $ i $ -th point.

It is guaranteed that all points are distinct.

## 输出格式

Print the number of possible distinct pictures modulo $ 10^{9}+7 $ .

## 说明/提示

In the first example there are two vertical and two horizontal lines passing through the points. You can get pictures with any subset of these lines. For example, you can get the picture containing all four lines in two ways (each segment represents a line containing it).

 The first way: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870E/16d9107c00bae4cf5f33754cdc1989ed71bbf8ba.png) The second way: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870E/cc0bfe7f0aace68a3f05623608cb42281913494e.png)In the second example you can work with two points independently. The number of pictures is $ 3^{2}=9 $ .

## 样例 #1

### 输入

```
4
1 1
1 2
2 1
2 2

```

### 输出

```
16

```

## 样例 #2

### 输入

```
2
-1 -1
0 1

```

### 输出

```
9

```

