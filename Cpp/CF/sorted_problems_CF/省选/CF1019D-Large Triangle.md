---
title: "Large Triangle"
layout: "post"
diff: 省选/NOI-
pid: CF1019D
tag: []
---

# Large Triangle

## 题目描述

There is a strange peculiarity: if you connect the cities of Rostov, Taganrog and Shakhty, peculiarly, you get a triangle

«Unbelievable But True»



Students from many different parts of Russia and abroad come to Summer Informatics School. You marked the hometowns of the SIS participants on a map.

Now you decided to prepare an interesting infographic based on this map. The first thing you chose to do is to find three cities on this map, such that they form a triangle with area $ S $ .

## 输入格式

The first line of input contains two integers $ n $ and $ S $ ( $ 3 \le n \le 2000 $ , $ 1 \le S \le 2 \cdot 10^{18} $ ) — the number of cities on the map and the area of the triangle to be found.

The next $ n $ lines contain descriptions of the cities, one per line. Each city is described by its integer coordinates $ x_i $ , $ y_i $ ( $ -10^9 \le x_i, y_i \le 10^9 $ ).

It is guaranteed that all cities are located at distinct points. It is also guaranteed that no three cities lie on the same line.

## 输出格式

If the solution doesn't exist — print «No».

Otherwise, print «Yes», followed by three pairs of coordinates $ (x, y) $ — the locations of the three cities, which form the triangle of area $ S $ .

## 样例 #1

### 输入

```
3 7
0 0
3 0
0 4

```

### 输出

```
No

```

## 样例 #2

### 输入

```
4 3
0 0
2 0
1 2
1 3

```

### 输出

```
Yes
0 0
1 3
2 0

```

