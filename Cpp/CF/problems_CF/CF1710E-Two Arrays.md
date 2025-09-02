---
title: "Two Arrays"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1710E
tag: ['博弈论', '二分图']
---

# Two Arrays

## 题目描述

You are given two arrays of integers $ a_1,a_2,\dots,a_n $ and $ b_1,b_2,\dots,b_m $ .

Alice and Bob are going to play a game. Alice moves first and they take turns making a move.

They play on a grid of size $ n \times m $ (a grid with $ n $ rows and $ m $ columns). Initially, there is a rook positioned on the first row and first column of the grid.

During her/his move, a player can do one of the following two operations:

1. Move the rook to a different cell on the same row or the same column of the current cell. A player cannot move the rook to a cell that has been visited $ 1000 $ times before (i.e., the rook can stay in a certain cell at most $ 1000 $ times during the entire game). Note that the starting cell is considered to be visited once at the beginning of the game.
2. End the game immediately with a score of $ a_r+b_c $ , where $ (r, c) $ is the current cell (i.e., the rook is on the $ r $ -th row and $ c $ -th column).

Bob wants to maximize the score while Alice wants to minimize it. If they both play this game optimally, what is the final score of the game?

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \leq n,m \leq 2 \cdot 10^5 $ ) — the length of the arrays $ a $ and $ b $ (which coincide with the number of rows and columns of the grid).

The second line contains the $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq 5 \cdot 10^8 $ ).

The third line contains the $ m $ integers $ b_1, b_2,\dots, b_n $ ( $ 1 \leq b_i \leq 5 \cdot 10^8 $ ).

## 输出格式

Print a single line containing the final score of the game.

## 说明/提示

In the first test case, Alice moves the rook to $ (2, 1) $ and Bob moves the rook to $ (1, 1) $ . This process will repeat for $ 999 $ times until finally, after Alice moves the rook, Bob cannot move it back to $ (1, 1) $ because it has been visited $ 1000 $ times before. So the final score of the game is $ a_2+b_1=4 $ .

In the second test case, the final score of the game is $ a_3+b_5 $ .

## 样例 #1

### 输入

```
2 1
3 2
2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 5
235499701 451218171 355604420 132973458
365049318 264083156 491406845 62875547 175951751
```

### 输出

```
531556171
```

