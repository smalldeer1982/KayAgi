---
title: "Pyramid of Glasses"
layout: "post"
diff: 普及+/提高
pid: CF676B
tag: []
---

# Pyramid of Glasses

## 题目描述

Mary has just graduated from one well-known University and is now attending celebration party. Students like to dream of a beautiful life, so they used champagne glasses to construct a small pyramid. The height of the pyramid is $ n $ . The top level consists of only $ 1 $ glass, that stands on $ 2 $ glasses on the second level (counting from the top), then $ 3 $ glasses on the third level and so on.The bottom level consists of $ n $ glasses.

Vlad has seen in the movies many times how the champagne beautifully flows from top levels to bottom ones, filling all the glasses simultaneously. So he took a bottle and started to pour it in the glass located at the top of the pyramid.

Each second, Vlad pours to the top glass the amount of champagne equal to the size of exactly one glass. If the glass is already full, but there is some champagne flowing in it, then it pours over the edge of the glass and is equally distributed over two glasses standing under. If the overflowed glass is at the bottom level, then the champagne pours on the table. For the purpose of this problem we consider that champagne is distributed among pyramid glasses immediately. Vlad is interested in the number of completely full glasses if he stops pouring champagne in $ t $ seconds.

Pictures below illustrate the pyramid consisting of three levels.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF676B/ed339075e4609507dba05c150b7d4a59f8205147.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF676B/26451ba18b38a1279a26b3d7ab7f9bf63116bb12.png)

## 输入格式

The only line of the input contains two integers $ n $ and $ t $ ( $ 1<=n<=10,0<=t<=10000 $ ) — the height of the pyramid and the number of seconds Vlad will be pouring champagne from the bottle.

## 输出格式

Print the single integer — the number of completely full glasses after $ t $ seconds.

## 说明/提示

In the first sample, the glasses full after $ 5 $ seconds are: the top glass, both glasses on the second level and the middle glass at the bottom level. Left and right glasses of the bottom level will be half-empty.

## 样例 #1

### 输入

```
3 5

```

### 输出

```
4

```

## 样例 #2

### 输入

```
4 8

```

### 输出

```
6

```

