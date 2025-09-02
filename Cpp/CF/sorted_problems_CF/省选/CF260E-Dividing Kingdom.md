---
title: "Dividing Kingdom"
layout: "post"
diff: 省选/NOI-
pid: CF260E
tag: []
---

# Dividing Kingdom

## 题目描述

A country called Flatland is an infinite two-dimensional plane. Flatland has $ n $ cities, each of them is a point on the plane.

Flatland is ruled by king Circle IV. Circle IV has 9 sons. He wants to give each of his sons part of Flatland to rule. For that, he wants to draw four distinct straight lines, such that two of them are parallel to the $ Ox $ axis, and two others are parallel to the $ Oy $ axis. At that, no straight line can go through any city. Thus, Flatland will be divided into 9 parts, and each son will be given exactly one of these parts. Circle IV thought a little, evaluated his sons' obedience and decided that the $ i $ -th son should get the part of Flatland that has exactly $ a_{i} $ cities.

Help Circle find such four straight lines that if we divide Flatland into 9 parts by these lines, the resulting parts can be given to the sons so that son number $ i $ got the part of Flatland which contains $ a_{i} $ cities.

## 输入格式

The first line contains integer $ n\ (9<=n<=10^{5}) $ — the number of cities in Flatland. Next $ n $ lines each contain two space-separated integers: $ x_{i},y_{i}\ (-10^{9}<=x_{i},y_{i}<=10^{9}) $ — the coordinates of the $ i $ -th city. No two cities are located at the same point. The last line contains nine space-separated integers: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF260E/8e882aa22699e3ae56d95dbb5dcc548b415f27bc.png).

## 输出格式

If there is no solution, print a single integer -1.

Otherwise, print in the first line two distinct real space-separated numbers: $ x_{1},x_{2} $ — the abscissas of the straight lines that are parallel to the $ Oy $ axis. And in the second line print two distinct real space-separated numbers: $ y_{1},y_{2} $ — the ordinates of the straight lines, parallel to the $ Ox $ . If there are multiple solutions, print any of them.

When the answer is being checked, a city is considered to lie on a straight line, if the distance between the city and the line doesn't exceed $ 10^{-6} $ . Two straight lines are considered the same if the distance between them doesn't exceed $ 10^{-6} $ .

## 说明/提示

The solution for the first sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF260E/f25dd1f6e7f7e19d7007bdb9da678c4a92207eda.png)The solution for the second sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF260E/cfb5bf22cb67c702c1b27adab1d86b1bf50d84b5.png)There is no solution for the third sample test.

## 样例 #1

### 输入

```
9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
1 1 1 1 1 1 1 1 1

```

### 输出

```
1.5000000000 2.5000000000
1.5000000000 2.5000000000

```

## 样例 #2

### 输入

```
15
4 4
-1 -3
1 5
3 -4
-4 4
-1 1
3 -3
-4 -5
-3 3
3 2
4 1
-4 2
-2 -5
-3 4
-1 4
2 1 2 1 2 1 3 2 1

```

### 输出

```
-3.5000000000 2.0000000000
3.5000000000 -1.0000000000

```

## 样例 #3

### 输入

```
10
-2 10
6 0
-16 -6
-4 13
-4 -2
-17 -10
9 15
18 16
-5 2
10 -5
2 1 1 1 1 1 1 1 1

```

### 输出

```
-1

```

