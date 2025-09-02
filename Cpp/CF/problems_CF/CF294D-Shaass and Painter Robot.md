---
title: "Shaass and Painter Robot"
layout: "post"
diff: 提高+/省选-
pid: CF294D
tag: []
---

# Shaass and Painter Robot

## 题目描述

Shaass thinks a kitchen with all white floor tiles is so boring. His kitchen floor is made of $ n·m $ square tiles forming a $ n×m $ rectangle. Therefore he's decided to color some of the tiles in black so that the floor looks like a checkerboard, which is no two side-adjacent tiles should have the same color.

Shaass wants to use a painter robot to color the tiles. In the beginning the robot is standing in a border tile $ (x_{s},y_{s}) $ facing a diagonal direction (i.e. upper-left, upper-right, down-left or down-right). As the robot walks in the kitchen he paints every tile he passes even if it's painted before. Painting each tile consumes one unit of black paint. If at any moment the robot hits a wall of the kitchen he changes his direction according the reflection rules. Note that a tile gets painted when the robot enters the tile from another tile, in other words changing direction in the same tile doesn't lead to any painting. The first tile the robot is standing on, is also painted.

The robot stops painting the first moment the floor is checkered. Given the dimensions of the kitchen and the position of the robot, find out the amount of paint the robot consumes before it stops painting the floor.

Let's consider an examples depicted below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF294D/9a76f461f123d79b09ad121ee5e2505584689476.png)If the robot starts at tile number 1 (the tile $ (1,1) $ ) of the left grid heading to down-right it'll pass tiles 1354236 and consumes 7 units of black paint on his way until he stops at tile number 6. But if it starts at tile number 1 in the right grid heading to down-right it will get stuck in a loop painting tiles 1, 2, and 3.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ , $ (2<=n,m<=10^{5}) $ . The second line contains two integers $ x_{s} $ and $ y_{s} $ $ (1<=x_{s}<=n,1<=y_{s}<=m) $ and the direction robot is facing initially. Direction is one of the strings: "UL" (upper-left direction), "UR" (upper-right), "DL" (down-left) or "DR" (down-right).

Note, that record $ (x_{s},y_{s}) $ denotes the tile that is located at the $ x_{s} $ -th row from the top and at the $ y_{s} $ -th column from the left of the kitchen.

It's guaranteed that the starting position will be a border tile (a tile with less than four side-adjacent tiles).

## 输出格式

Print the amount of paint the robot consumes to obtain a checkered kitchen floor. Or print -1 if it never happens.

Please do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specificator.

## 样例 #1

### 输入

```
3 4
1 1 DR

```

### 输出

```
7

```

## 样例 #2

### 输入

```
3 4
3 3 DR

```

### 输出

```
11

```

## 样例 #3

### 输入

```
3 3
1 1 DR

```

### 输出

```
-1

```

## 样例 #4

### 输入

```
3 3
1 2 DL

```

### 输出

```
4

```

