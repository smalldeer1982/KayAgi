---
title: "Slalom"
layout: "post"
diff: 省选/NOI-
pid: CF720D
tag: []
---

# Slalom

## 题目描述

Little girl Masha likes winter sports, today she's planning to take part in slalom skiing.

The track is represented as a grid composed of $ n×m $ squares. There are rectangular obstacles at the track, composed of grid squares. Masha must get from the square $ (1,1) $ to the square $ (n,m) $ . She can move from a square to adjacent square: either to the right, or upwards. If the square is occupied by an obstacle, it is not allowed to move to that square.

One can see that each obstacle can actually be passed in two ways: either it is to the right of Masha's path, or to the left. Masha likes to try all ways to do things, so she would like to know how many ways are there to pass the track. Two ways are considered different if there is an obstacle such that it is to the right of the path in one way, and to the left of the path in the other way.

Help Masha to find the number of ways to pass the track. The number of ways can be quite big, so Masha would like to know it modulo $ 10^{9}+7 $ .

The pictures below show different ways to pass the track in sample tests. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF720D/2ddedad82f8f5e28a322fd1fe426b1600d8a03dd.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF720D/c0dbe07c720846d8b66f7c06424a8cfd200c6af3.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF720D/f511984d971426f2757dbb61173a665800b3ee08.png)

## 输入格式

The first line of input data contains three positive integers: $ n $ , $ m $ and $ k $ ( $ 3<=n,m<=10^{6} $ , $ 0<=k<=10^{5} $ ) — the size of the track and the number of obstacles.

The following $ k $ lines contain four positive integers each: $ x_{1} $ , $ y_{1} $ , $ x_{2} $ , $ y_{2} $ ( $ 1<=x_{1}<=x_{2}<=n $ , $ 1<=y_{1}<=y_{2}<=m $ ) — coordinates of bottom left, and top right squares of the obstacle.

It is guaranteed that there are no obstacles at squares $ (1,1) $ and $ (n,m) $ , and no obstacles overlap (but some of them may touch).

## 输出格式

Output one integer — the number of ways to pass the track modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
3 3 0

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4 5 1
2 2 3 4

```

### 输出

```
2

```

## 样例 #3

### 输入

```
5 5 3
2 2 2 3
4 2 5 2
4 4 4 4

```

### 输出

```
3

```

