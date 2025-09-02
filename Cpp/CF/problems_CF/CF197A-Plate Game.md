---
title: "Plate Game"
layout: "post"
diff: 普及/提高-
pid: CF197A
tag: []
---

# Plate Game

## 题目描述

You've got a rectangular table with length $ a $ and width $ b $ and the infinite number of plates of radius $ r $ . Two players play the following game: they take turns to put the plates on the table so that the plates don't lie on each other (but they can touch each other), and so that any point on any plate is located within the table's border. During the game one cannot move the plates that already lie on the table. The player who cannot make another move loses. Determine which player wins, the one who moves first or the one who moves second, provided that both players play optimally well.

## 输入格式

A single line contains three space-separated integers $ a $ , $ b $ , $ r $ $ (1<=a,b,r<=100) $ — the table sides and the plates' radius, correspondingly.

## 输出格式

If wins the player who moves first, print "First" (without the quotes). Otherwise print "Second" (without the quotes).

## 说明/提示

In the first sample the table has place for only one plate. The first player puts a plate on the table, the second player can't do that and loses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197A/616ddb445b80df1d3e6e847cff2f0e32d4fd3dd4.png)In the second sample the table is so small that it doesn't have enough place even for one plate. So the first player loses without making a single move.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197A/c6393d7d89b7426c75efde7ce23de7dae72901f3.png)

## 样例 #1

### 输入

```
5 5 2

```

### 输出

```
First

```

## 样例 #2

### 输入

```
6 7 4

```

### 输出

```
Second

```

