---
title: "Temporarily unavailable"
layout: "post"
diff: 普及-
pid: CF1282A
tag: []
---

# Temporarily unavailable

## 题目描述

Polycarp lives on the coordinate axis $ Ox $ and travels from the point $ x=a $ to $ x=b $ . It moves uniformly rectilinearly at a speed of one unit of distance per minute.

On the axis $ Ox $ at the point $ x=c $ the base station of the mobile operator is placed. It is known that the radius of its coverage is $ r $ . Thus, if Polycarp is at a distance less than or equal to $ r $ from the point $ x=c $ , then he is in the network coverage area, otherwise — no. The base station can be located both on the route of Polycarp and outside it.

Print the time in minutes during which Polycarp will not be in the coverage area of the network, with a rectilinear uniform movement from $ x=a $ to $ x=b $ . His speed — one unit of distance per minute.

## 输入格式

The first line contains a positive integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. In the following lines are written $ t $ test cases.

The description of each test case is one line, which contains four integers $ a $ , $ b $ , $ c $ and $ r $ ( $ -10^8 \le a,b,c \le 10^8 $ , $ 0 \le r \le 10^8 $ ) — the coordinates of the starting and ending points of the path, the base station, and its coverage radius, respectively.

Any of the numbers $ a $ , $ b $ and $ c $ can be equal (either any pair or all three numbers). The base station can be located both on the route of Polycarp and outside it.

## 输出格式

Print $ t $ numbers — answers to given test cases in the order they are written in the test. Each answer is an integer — the number of minutes during which Polycarp will be unavailable during his movement.

## 说明/提示

The following picture illustrates the first test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1282A/307b325125eb4f2400d0fb03b9026999f9da2b19.png)Polycarp goes from $ 1 $ to $ 10 $ . The yellow area shows the coverage area of the station with a radius of coverage of $ 1 $ , which is located at the point of $ 7 $ . The green area shows a part of the path when Polycarp is out of coverage area.

## 样例 #1

### 输入

```
9
1 10 7 1
3 3 3 0
8 2 10 4
8 2 10 100
-10 20 -17 2
-3 2 2 0
-3 1 2 0
2 3 2 3
-1 3 -2 2

```

### 输出

```
7
0
4
0
30
5
4
0
3

```

