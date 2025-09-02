---
title: "Fiber Shape"
layout: "post"
diff: 省选/NOI-
pid: CF1510F
tag: []
---

# Fiber Shape

## 题目描述

Imagine a board with $ n $ pins put into it, the $ i $ -th pin is located at $ (x_i, y_i) $ . For simplicity, we will restrict the problem to the case where the pins are placed in vertices of a convex polygon.

Then, take a non-stretchable string of length $ l $ , and put it around all the pins. Place a pencil inside the string and draw a curve around the pins, trying to pull the string in every possible direction. The picture below shows an example of a string tied around the pins and pulled by a pencil (a point $ P $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510F/3b434456ce86779edbd75c1c31032e6011c62ac7.png)Your task is to find an area inside this curve. Formally, for a given convex polygon $ S $ and a length $ l $ let's define a fiber shape $ F(S, l) $ as a set of points $ t $ such that the perimeter of the convex hull of $ S \cup \{t\} $ does not exceed $ l $ . Find an area of $ F(S, l) $ .

## 输入格式

The first line contains two integers $ n $ and $ l $ ( $ 3 \le n \le 10^4 $ ; $ 1 \le l \le 8 \cdot 10^5 $ ) — the number of vertices of the polygon $ S $ and the length of the string. Next $ n $ lines contain integers $ x_i $ and $ y_i $ ( $ -10^5 \le x_i, y_i \le 10^5 $ ) — coordinates of polygon's vertices in counterclockwise order. All internal angles of the polygon are strictly less than $ \pi $ . The length $ l $ exceeds the perimeter of the polygon by at least $ 10^{-3} $ .

## 输出格式

Output a single floating-point number — the area of the fiber shape $ F(S, l) $ . Your answer will be considered correct if its absolute or relative error doesn't exceed $ 10^{-6} $ .

## 说明/提示

The following pictures illustrate the example tests.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510F/73efb05d151b205642c75f0c21efa36e2790cfd3.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510F/3d7b56874f36b0db8d6135c9d751060f7ad68412.png)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510F/e25400dd84baf171efc8e3b94be6a87e03a7df61.png)

## 样例 #1

### 输入

```
3 4
0 0
1 0
0 1
```

### 输出

```
3.012712585980357
```

## 样例 #2

### 输入

```
4 5
0 0
1 0
1 1
0 1
```

### 输出

```
5.682061989789656
```

## 样例 #3

### 输入

```
5 17
0 0
2 -1
3 0
4 3
-1 4
```

### 输出

```
37.719371276930820
```

