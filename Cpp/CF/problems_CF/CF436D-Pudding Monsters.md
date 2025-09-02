---
title: "Pudding Monsters"
layout: "post"
diff: 省选/NOI-
pid: CF436D
tag: []
---

# Pudding Monsters

## 题目描述

Have you ever played Pudding Monsters? In this task, a simplified one-dimensional model of this game is used.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF436D/cac747e35122b81f9dbf605774cf18b365c5306d.png)Imagine an infinite checkered stripe, the cells of which are numbered sequentially with integers. Some cells of the strip have monsters, other cells of the strip are empty. All monsters are made of pudding, so if there are two monsters in the neighboring cells, they stick to each other (literally). Similarly, if several monsters are on consecutive cells, they all stick together in one block of monsters. We will call the stuck together monsters a block of monsters. A detached monster, not stuck to anyone else, is also considered a block.

In one move, the player can take any block of monsters and with a movement of his hand throw it to the left or to the right. The selected monsters will slide on until they hit some other monster (or a block of monsters).

For example, if a strip has three monsters in cells $ 1 $ , $ 4 $ and $ 5 $ , then there are only four possible moves: to send a monster in cell $ 1 $ to minus infinity, send the block of monsters in cells $ 4 $ and $ 5 $ to plus infinity, throw monster $ 1 $ to the right (it will stop in cell $ 3 $ ), throw a block of monsters in cells $ 4 $ and $ 5 $ to the left (they will stop in cells $ 2 $ and $ 3 $ ).

Some cells on the strip are marked with stars. These are the special cells. The goal of the game is to make the largest possible number of special cells have monsters on them.

You are given the numbers of the special cells on a strip as well as the initial position of all monsters. What is the maximum number of special cells that will contain monsters in the optimal game?

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n<=10^{5}; 1<=m<=2000) $ — the number of monsters on the strip and the number of special cells.

The second line contains $ n $ distinct integers — the numbers of the cells with monsters, then the third line contains $ m $ distinct integers — the numbers of the special cells. It is guaranteed that all the numbers of the cells are positive integers not exceeding $ 2·10^{5} $ .

## 输出格式

Print a single integer — the maximum number of special cells that will contain monsters in the optimal game.

## 样例 #1

### 输入

```
3 2
1 3 5
2 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 2
1 3 4 6
2 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
4 2
1 8 4 5
7 2

```

### 输出

```
1

```

