---
title: "Board Game"
layout: "post"
diff: 省选/NOI-
pid: CF605D
tag: []
---

# Board Game

## 题目描述

You are playing a board card game. In this game the player has two characteristics, $ x $ and $ y $ — the white magic skill and the black magic skill, respectively. There are $ n $ spell cards lying on the table, each of them has four characteristics, $ a_{i} $ , $ b_{i} $ , $ c_{i} $ and $ d_{i} $ . In one move a player can pick one of the cards and cast the spell written on it, but only if first two of it's characteristics meet the requirement $ a_{i}<=x $ and $ b_{i}<=y $ , i.e. if the player has enough magic skill to cast this spell. However, after casting the spell the characteristics of a player change and become equal to $ x=c_{i} $ and $ y=d_{i} $ .

At the beginning of the game both characteristics of a player are equal to zero. The goal of the game is to cast the $ n $ -th spell. Your task is to make it in as few moves as possible. You are allowed to use spell in any order and any number of times (for example, you may not use some spells at all).

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the number of cards on the table.

Each of the next $ n $ lines contains four integers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ , $ d_{i} $ ( $ 0<=a_{i},b_{i},c_{i},d_{i}<=10^{9} $ ) — the characteristics of the corresponding card.

## 输出格式

In the first line print a single integer $ k $ — the minimum number of moves needed to cast the $ n $ -th spell and in the second line print $ k $ numbers — the indices of the cards in the order in which you should cast them. In case there are multiple possible solutions, print any of them.

If it is impossible to cast the $ n $ -th spell, print $ -1 $ .

## 样例 #1

### 输入

```
4
0 0 3 4
2 2 5 3
4 1 1 7
5 3 8 8

```

### 输出

```
3
1 2 4

```

## 样例 #2

### 输入

```
2
0 0 4 6
5 1 1000000000 1000000000

```

### 输出

```
-1

```

