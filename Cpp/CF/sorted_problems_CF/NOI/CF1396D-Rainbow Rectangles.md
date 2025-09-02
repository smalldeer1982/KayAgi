---
title: "Rainbow Rectangles"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1396D
tag: []
---

# Rainbow Rectangles

## 题目描述

Shrimpy Duc is a fat and greedy boy who is always hungry. After a while of searching for food to satisfy his never-ending hunger, Shrimpy Duc finds M&amp;M candies lying unguarded on a $ L \times       L $ grid. There are $ n $ M&amp;M candies on the grid, the $ i $ -th M&amp;M is currently located at $ (x_i + 0.5, y_i +       0.5), $ and has color $ c_i $ out of a total of $ k $ colors (the size of M&amp;Ms are insignificant).

Shrimpy Duc wants to steal a rectangle of M&amp;Ms, specifically, he wants to select a rectangle with integer coordinates within the grid and steal all candies within the rectangle. Shrimpy Duc doesn't need to steal every single candy, however, he would like to steal at least one candy for each color.

In other words, he wants to select a rectangle whose sides are parallel to the coordinate axes and whose left-bottom vertex $ (X_1, Y_1) $ and right-top vertex $ (X_2, Y_2) $ are points with integer coordinates satisfying $ 0 \le X_1 < X_2 \le L $ and $ 0 \le Y_1 < Y_2 \le L $ , so that for every color $ 1       \le c \le k $ there is at least one M&amp;M with color $ c $ that lies within that rectangle.

How many such rectangles are there? This number may be large, so you only need to find it modulo $ 10^9 + 7 $ .

## 输入格式

The first line contains three positive integers $ n, k, L $ $ (1 \leq k \leq n \leq 2 \cdot 10^3, 1 \leq L \leq 10^9 ) $ — the number of M&amp;Ms, the number of colors and the length of the grid respectively.

The following $ n $ points describe the M&amp;Ms. Each line contains three integers $ x_i, y_i, c_i $ $ (0 \leq x_i, y_i       < L, 1 \le c_i \le k) $ — the coordinates and color of the $ i $ -th M&amp;M respectively.

Different M&amp;Ms have different coordinates ( $ x_i \ne x_j $ or $ y_i \ne y_j $ for every $ i \ne j $ ), and for every $ 1       \le c \le k $ there is at least one M&amp;M with color $ c $ .

## 输出格式

Output a single integer — the number of rectangles satisfying Shrimpy Duc's conditions, modulo $ 10^9 + 7 $ .

## 说明/提示

Grid for the first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1396D/87d4986f66d2e50903924ec6780f2b0776d8fbb4.png)

## 样例 #1

### 输入

```
4 2 4
3 2 2
3 1 1
1 1 1
1 2 1
```

### 输出

```
20
```

## 样例 #2

### 输入

```
5 3 10
6 5 3
5 3 1
7 9 1
2 3 2
5 0 2
```

### 输出

```
300
```

## 样例 #3

### 输入

```
10 4 10
5 4 4
0 0 3
6 0 1
3 9 2
8 7 1
8 1 3
2 1 3
6 3 2
3 5 3
4 3 4
```

### 输出

```
226
```

