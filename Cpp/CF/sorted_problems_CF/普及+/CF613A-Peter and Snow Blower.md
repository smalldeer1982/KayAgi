---
title: "Peter and Snow Blower"
layout: "post"
diff: 普及+/提高
pid: CF613A
tag: ['模拟', '数学', '构造']
---

# Peter and Snow Blower

## 题目描述

Peter got a new snow blower as a New Year present. Of course, Peter decided to try it immediately. After reading the instructions he realized that it does not work like regular snow blowing machines. In order to make it work, you need to tie it to some point that it does not cover, and then switch it on. As a result it will go along a circle around this point and will remove all the snow from its path.

Formally, we assume that Peter's machine is a polygon on a plane. Then, after the machine is switched on, it will make a circle around the point to which Peter tied it (this point lies strictly outside the polygon). That is, each of the points lying within or on the border of the polygon will move along the circular trajectory, with the center of the circle at the point to which Peter tied his machine.

Peter decided to tie his car to point $ P $ and now he is wondering what is the area of ​​the region that will be cleared from snow. Help him.

## 输入格式

The first line of the input contains three integers — the number of vertices of the polygon $ n $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/e07eddcf01ea19e02be99447a5d31677c12c0459.png)), and coordinates of point $ P $ .

Each of the next $ n $ lines contains two integers — coordinates of the vertices of the polygon in the clockwise or counterclockwise order. It is guaranteed that no three consecutive vertices lie on a common straight line.

All the numbers in the input are integers that do not exceed $ 1000000 $ in their absolute value.

## 输出格式

Print a single real value number — the area of the region that will be cleared. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/259203790d90e969d73ec841bd0673c1e8e7d69a.png).

## 说明/提示

In the first sample snow will be removed from that area:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/d58837ea7895097f43b3c725628f9a11757bb6b3.png)

## 样例 #1

### 输入

```
3 0 0
0 1
-1 2
1 2

```

### 输出

```
12.566370614359172464

```

## 样例 #2

### 输入

```
4 1 -1
0 0
1 2
2 0
1 1

```

### 输出

```
21.991148575128551812

```

