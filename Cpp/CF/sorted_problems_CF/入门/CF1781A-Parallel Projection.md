---
title: "Parallel Projection"
layout: "post"
diff: 入门
pid: CF1781A
tag: []
---

# Parallel Projection

## 题目描述

Vika's house has a room in a shape of a rectangular parallelepiped (also known as a rectangular cuboid). Its floor is a rectangle of size $ w \times d $ , and the ceiling is right above at the constant height of $ h $ . Let's introduce a coordinate system on the floor so that its corners are at points $ (0, 0) $ , $ (w, 0) $ , $ (w, d) $ , and $ (0, d) $ .

A laptop is standing on the floor at point $ (a, b) $ . A projector is hanging on the ceiling right above point $ (f, g) $ . Vika wants to connect the laptop and the projector with a cable in such a way that the cable always goes along the walls, ceiling, or floor (i. e. does not go inside the cuboid). Additionally, the cable should always run parallel to one of the cuboid's edges (i. e. it can not go diagonally).

What is the minimum length of a cable that can connect the laptop to the projector?

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1781A/d3b03cec2845dd798f781a8a559bfa32f913d5ba.png) Illustration for the first test case. One of the optimal ways to put the cable is shown in green.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains three integers $ w $ , $ d $ , and $ h $ ( $ 2 \le w, d, h \le 1000 $ ) — the size of the room.

The second line contains four integers $ a $ , $ b $ , $ f $ , $ g $ ( $ 0 < a, f < w $ ; $ 0 < b, g < d $ ): the laptop is located on the floor at point $ (a, b) $ , while the projector is hanging on the ceiling right above point $ (f, g) $ .

## 输出格式

For each test case, print a single integer — the minimum length of the cable connecting the laptop and the projector that runs only along the walls, floor, and ceiling parallel to cuboid's edges.

## 说明/提示

The picture in the statement illustrates the first test case.

## 样例 #1

### 输入

```
5
55 20 29
23 10 18 3
20 10 5
1 5 2 5
15 15 4
7 13 10 10
2 1000 2
1 1 1 999
10 4 10
7 1 2 1
```

### 输出

```
47
8
14
1002
17
```

