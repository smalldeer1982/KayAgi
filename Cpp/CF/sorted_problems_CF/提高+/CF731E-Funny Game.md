---
title: "Funny Game"
layout: "post"
diff: 提高+/省选-
pid: CF731E
tag: ['动态规划 DP', '博弈论']
---

# Funny Game

## 题目描述

Once upon a time Petya and Gena gathered after another programming competition and decided to play some game. As they consider most modern games to be boring, they always try to invent their own games. They have only stickers and markers, but that won't stop them.

The game they came up with has the following rules. Initially, there are $ n $ stickers on the wall arranged in a row. Each sticker has some number written on it. Now they alternate turn, Petya moves first.

One move happens as follows. Lets say there are $ m>=2 $ stickers on the wall. The player, who makes the current move, picks some integer $ k $ from $ 2 $ to $ m $ and takes $ k $ leftmost stickers (removes them from the wall). After that he makes the new sticker, puts it to the left end of the row, and writes on it the new integer, equal to the sum of all stickers he took on this move.

Game ends when there is only one sticker left on the wall. The score of the player is equal to the sum of integers written on all stickers he took during all his moves. The goal of each player is to maximize the difference between his score and the score of his opponent.

Given the integer $ n $ and the initial sequence of stickers on the wall, define the result of the game, i.e. the difference between the Petya's and Gena's score if both players play optimally.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 2<=n<=200000 $ ) — the number of stickers, initially located on the wall.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ -10000<=a_{i}<=10000 $ ) — the numbers on stickers in order from left to right.

## 输出格式

Print one integer — the difference between the Petya's score and Gena's score at the end of the game if both players play optimally.

## 说明/提示

In the first sample, the optimal move for Petya is to take all the stickers. As a result, his score will be equal to $ 14 $ and Gena's score will be equal to $ 0 $ .

In the second sample, the optimal sequence of moves is the following. On the first move Petya will take first three sticker and will put the new sticker with value $ -8 $ . On the second move Gena will take the remaining two stickers. The Petya's score is $ 1+(-7)+(-2)=-8 $ , Gena's score is $ (-8)+3=-5 $ , i.e. the score difference will be $ -3 $ .

## 样例 #1

### 输入

```
3
2 4 8

```

### 输出

```
14

```

## 样例 #2

### 输入

```
4
1 -7 -2 3

```

### 输出

```
-3

```

