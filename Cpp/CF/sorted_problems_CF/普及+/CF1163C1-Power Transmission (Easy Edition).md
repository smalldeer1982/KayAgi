---
title: "Power Transmission (Easy Edition)"
layout: "post"
diff: 普及+/提高
pid: CF1163C1
tag: []
---

# Power Transmission (Easy Edition)

## 题目描述

This problem is same as the next one, but has smaller constraints.

It was a Sunday morning when the three friends Selena, Shiro and Katie decided to have a trip to the nearby power station (do not try this at home). After arriving at the power station, the cats got impressed with a large power transmission system consisting of many chimneys, electric poles, and wires. Since they are cats, they found those things gigantic.

At the entrance of the station, there is a map describing the complicated wiring system. Selena is the best at math among three friends. He decided to draw the map on the Cartesian plane. Each pole is now a point at some coordinates $ (x_i, y_i) $ . Since every pole is different, all of the points representing these poles are distinct. Also, every two poles are connected with each other by wires. A wire is a straight line on the plane infinite in both directions. If there are more than two poles lying on the same line, they are connected by a single common wire.

Selena thinks, that whenever two different electric wires intersect, they may interfere with each other and cause damage. So he wonders, how many pairs are intersecting? Could you help him with this problem?

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 50 $ ) — the number of electric poles.

Each of the following $ n $ lines contains two integers $ x_i $ , $ y_i $ ( $ -10^4 \le x_i, y_i \le 10^4 $ ) — the coordinates of the poles.

It is guaranteed that all of these $ n $ points are distinct.

## 输出格式

Print a single integer — the number of pairs of wires that are intersecting.

## 说明/提示

In the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/2317b27306c4c65175012212cdceb02039be0972.png)In the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/0792ee139dbdc603551bd0c872a1bea92551eac5.png)Note that the three poles $ (0, 0) $ , $ (0, 2) $ and $ (0, 4) $ are connected by a single wire.

In the third example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/9e20f52f47cf7b9d491a8675d81506c0f862a971.png)

## 样例 #1

### 输入

```
4
0 0
1 1
0 3
1 2

```

### 输出

```
14

```

## 样例 #2

### 输入

```
4
0 0
0 2
0 4
2 0

```

### 输出

```
6

```

## 样例 #3

### 输入

```
3
-1 -1
1 0
3 1

```

### 输出

```
0

```

