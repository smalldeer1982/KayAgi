---
title: "Volatile Kite"
layout: "post"
diff: 普及+/提高
pid: CF772B
tag: []
---

# Volatile Kite

## 题目描述

You are given a convex polygon $ P $ with $ n $ distinct vertices $ p_{1},p_{2},...,p_{n} $ . Vertex $ p_{i} $ has coordinates $ (x_{i},y_{i}) $ in the 2D plane. These vertices are listed in clockwise order.

You can choose a real number $ D $ and move each vertex of the polygon a distance of at most $ D $ from their original positions.

Find the maximum value of $ D $ such that no matter how you move the vertices, the polygon does not intersect itself and stays convex.

## 输入格式

The first line has one integer $ n $ ( $ 4<=n<=1000 $ ) — the number of vertices.

The next $ n $ lines contain the coordinates of the vertices. Line $ i $ contains two integers $ x_{i} $ and $ y_{i} $ ( $ -10^{9}<=x_{i},y_{i}<=10^{9} $ ) — the coordinates of the $ i $ -th vertex. These points are guaranteed to be given in clockwise order, and will form a strictly convex polygon (in particular, no three consecutive points lie on the same straight line).

## 输出格式

Print one real number $ D $ , which is the maximum real number such that no matter how you move the vertices, the polygon stays convex.

Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Namely, let's assume that your answer is $ a $ and the answer of the jury is $ b $ . The checker program will consider your answer correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772B/259203790d90e969d73ec841bd0673c1e8e7d69a.png).

## 说明/提示

Here is a picture of the first sample

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772B/dde3b583b8130c23fcfe1a3be5859cfee6d3318c.png)

Here is an example of making the polygon non-convex.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772B/6cf9c89dbdf099a68520895969908ade3679a607.png)

This is not an optimal solution, since the maximum distance we moved one point is $ ≈0.4242640687 $ , whereas we can make it non-convex by only moving each point a distance of at most $ ≈0.3535533906 $ .

## 样例 #1

### 输入

```
4
0 0
0 1
1 1
1 0

```

### 输出

```
0.3535533906

```

## 样例 #2

### 输入

```
6
5 0
10 0
12 -4
10 -8
5 -8
3 -4

```

### 输出

```
1.0000000000

```

