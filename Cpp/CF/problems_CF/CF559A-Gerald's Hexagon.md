---
title: "Gerald's Hexagon"
layout: "post"
diff: 普及-
pid: CF559A
tag: []
---

# Gerald's Hexagon

## 题目描述

Gerald got a very curious hexagon for his birthday. The boy found out that all the angles of the hexagon are equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF559A/51081de61718bdab7ac2fc919b0406c7c9b3db07.png). Then he measured the length of its sides, and found that each of them is equal to an integer number of centimeters. There the properties of the hexagon ended and Gerald decided to draw on it.

He painted a few lines, parallel to the sides of the hexagon. The lines split the hexagon into regular triangles with sides of 1 centimeter. Now Gerald wonders how many triangles he has got. But there were so many of them that Gerald lost the track of his counting. Help the boy count the triangles.

## 输入格式

The first and the single line of the input contains 6 space-separated integers $ a_{1},a_{2},a_{3},a_{4},a_{5} $ and $ a_{6} $ ( $ 1<=a_{i}<=1000 $ ) — the lengths of the sides of the hexagons in centimeters in the clockwise order. It is guaranteed that the hexagon with the indicated properties and the exactly such sides exists.

## 输出格式

Print a single integer — the number of triangles with the sides of one 1 centimeter, into which the hexagon is split.

## 说明/提示

This is what Gerald's hexagon looks like in the first sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF559A/4ab048b05b556943a01545b02118caaeb324465f.png)

And that's what it looks like in the second sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF559A/5870b6c24fc4fc3203a53b2587509290d8665c96.png)

## 样例 #1

### 输入

```
1 1 1 1 1 1

```

### 输出

```
6

```

## 样例 #2

### 输入

```
1 2 1 2 1 2

```

### 输出

```
13

```

