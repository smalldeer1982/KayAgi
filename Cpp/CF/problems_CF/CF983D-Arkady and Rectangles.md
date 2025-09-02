---
title: "Arkady and Rectangles"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF983D
tag: []
---

# Arkady and Rectangles

## 题目描述

Arkady has got an infinite plane painted in color $ 0 $ . Then he draws $ n $ rectangles filled with paint with sides parallel to the Cartesian coordinate axes, one after another. The color of the $ i $ -th rectangle is $ i $ (rectangles are enumerated from $ 1 $ to $ n $ in the order he draws them). It is possible that new rectangles cover some of the previous ones completely or partially.

Count the number of different colors on the plane after Arkady draws all the rectangles.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 100\,000 $ ) — the number of rectangles.

The $ i $ -th of the next $ n $ lines contains $ 4 $ integers $ x_1 $ , $ y_1 $ , $ x_2 $ and $ y_2 $ ( $ -10^9 \le x_1 < x_2 \le 10^9 $ , $ -10^9 \le y_1 < y_2 \le 10^9 $ ) — the coordinates of corners of the $ i $ -th rectangle.

## 输出格式

In the single line print the number of different colors in the plane, including color $ 0 $ .

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF983D/e648fc5d318d6ae14ac43cb4aec90db39b1df7c2.png) That's how the plane looks in the first sample![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF983D/a83940168cd3126926164152304295d595ea5d06.png) That's how the plane looks in the second sample

 $ 0 $ = white, $ 1 $ = cyan, $ 2 $ = blue, $ 3 $ = purple, $ 4 $ = yellow, $ 5 $ = red.

## 样例 #1

### 输入

```
5
-1 -1 1 1
-4 0 0 4
0 0 4 4
-4 -4 0 0
0 -4 4 0

```

### 输出

```
5
```

## 样例 #2

### 输入

```
4
0 0 4 4
-4 -4 0 0
0 -4 4 0
-2 -4 2 4

```

### 输出

```
5
```

