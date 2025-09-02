---
title: "Arrow"
layout: "post"
diff: 普及+/提高
pid: CF630O
tag: []
---

# Arrow

## 题目描述

Petya has recently started working as a programmer in the IT city company that develops computer games.

Besides game mechanics implementation to create a game it is necessary to create tool programs that can be used by game designers to create game levels. Petya's first assignment is to create a tool that allows to paint different arrows on the screen.

A user of this tool will choose a point on the screen, specify a vector (the arrow direction) and vary several parameters to get the required graphical effect. In the first version of the program Petya decided to limit parameters of the arrow by the following: a point with coordinates $ (px,py) $ , a nonzero vector with coordinates $ (vx,vy) $ , positive scalars $ a,b,c,d,a&gt;c $ .

The produced arrow should have the following properties. The arrow consists of a triangle and a rectangle. The triangle is isosceles with base of length $ a $ and altitude of length $ b $ perpendicular to the base. The rectangle sides lengths are $ c $ and $ d $ . Point $ (px,py) $ is situated in the middle of the triangle base and in the middle of side of rectangle that has length $ c $ . Area of intersection of the triangle and the rectangle is zero. The direction from $ (px,py) $ point to the triangle vertex opposite to base containing the point coincides with direction of $ (vx,vy) $ vector.

Enumerate the arrow points coordinates in counter-clockwise order starting from the tip.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630O/b1373ea5c55d47b5adf32698b1a37967e1fa1cc0.png)

## 输入格式

The only line of the input contains eight integers $ px,py,vx,vy $ ( $ -1000<=px,py,vx,vy<=1000,vx^{2}+vy^{2}&gt;0 $ ), $ a,b,c,d $ ( $ 1<=a,b,c,d<=1000,a&gt;c $ ).

## 输出格式

Output coordinates of the arrow points in counter-clockwise order. Each line should contain two coordinates, first $ x $ , then $ y $ . Relative or absolute error should not be greater than $ 10^{-9} $ .

## 样例 #1

### 输入

```
8 8 0 2 8 3 4 5

```

### 输出

```
8.000000000000 11.000000000000
4.000000000000 8.000000000000
6.000000000000 8.000000000000
6.000000000000 3.000000000000
10.000000000000 3.000000000000
10.000000000000 8.000000000000
12.000000000000 8.000000000000

```

