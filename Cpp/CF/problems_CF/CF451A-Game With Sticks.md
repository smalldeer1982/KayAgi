---
title: "Game With Sticks"
layout: "post"
diff: 普及-
pid: CF451A
tag: []
---

# Game With Sticks

## 题目描述

After winning gold and silver in IOI 2014, Akshat and Malvika want to have some fun. Now they are playing a game on a grid made of $ n $ horizontal and $ m $ vertical sticks.

An intersection point is any point on the grid which is formed by the intersection of one horizontal stick and one vertical stick.

In the grid shown below, $ n=3 $ and $ m=3 $ . There are $ n+m=6 $ sticks in total (horizontal sticks are shown in red and vertical sticks are shown in green). There are $ n·m=9 $ intersection points, numbered from $ 1 $ to $ 9 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF451A/18b27511f71a42f9e0fd0b22af6d5248021325d7.png)The rules of the game are very simple. The players move in turns. Akshat won gold, so he makes the first move. During his/her move, a player must choose any remaining intersection point and remove from the grid all sticks which pass through this point. A player will lose the game if he/she cannot make a move (i.e. there are no intersection points remaining on the grid at his/her move).

Assume that both players play optimally. Who will win the game?

## 输入格式

The first line of input contains two space-separated integers, $ n $ and $ m $ ( $ 1<=n,m<=100 $ ).

## 输出格式

Print a single line containing "Akshat" or "Malvika" (without the quotes), depending on the winner of the game.

## 说明/提示

Explanation of the first sample:

The grid has four intersection points, numbered from $ 1 $ to $ 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF451A/e0d83475f64b355b0a9b5538e74aa373b38a9909.png)If Akshat chooses intersection point $ 1 $ , then he will remove two sticks ( $ 1-2 $ and $ 1-3 $ ). The resulting grid will look like this.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF451A/c9bd491d9b8dd9c48045e00c65ed3725174a35a0.png)Now there is only one remaining intersection point (i.e. $ 4 $ ). Malvika must choose it and remove both remaining sticks. After her move the grid will be empty.

In the empty grid, Akshat cannot make any move, hence he will lose.

Since all $ 4 $ intersection points of the grid are equivalent, Akshat will lose no matter which one he picks.

## 样例 #1

### 输入

```
2 2

```

### 输出

```
Malvika

```

## 样例 #2

### 输入

```
2 3

```

### 输出

```
Malvika

```

## 样例 #3

### 输入

```
3 3

```

### 输出

```
Akshat

```

