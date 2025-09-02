---
title: "Omkar and Akmar"
layout: "post"
diff: 省选/NOI-
pid: CF1536F
tag: []
---

# Omkar and Akmar

## 题目描述

Omkar and Akmar are playing a game on a circular board with $ n $ ( $ 2 \leq n \leq 10^6 $ ) cells. The cells are numbered from $ 1 $ to $ n $ so that for each $ i $ ( $ 1 \leq i \leq n-1 $ ) cell $ i $ is adjacent to cell $ i+1 $ and cell $ 1 $ is adjacent to cell $ n $ . Initially, each cell is empty.

Omkar and Akmar take turns placing either an A or a B on the board, with Akmar going first. The letter must be placed on an empty cell. In addition, the letter cannot be placed adjacent to a cell containing the same letter.

A player loses when it is their turn and there are no more valid moves.

Output the number of possible distinct games where both players play optimally modulo $ 10^9+7 $ . Note that we only consider games where some player has lost and there are no more valid moves.

Two games are considered distinct if the number of turns is different or for some turn, the letter or cell number that the letter is placed on were different.

A move is considered optimal if the move maximizes the player's chance of winning, assuming the other player plays optimally as well. More formally, if the player who has to move has a winning strategy, they have to make a move after which they will still have a winning strategy. If they do not, they can make any move.

## 输入格式

The only line will contain an integer $ n $ ( $ 2 \leq n \leq 10^6 $ ) — the number of cells on the board.

## 输出格式

Output a single integer — the number of possible distinct games where both players play optimally modulo $ 10^9+7 $ .

## 说明/提示

For the first sample case, the first player has $ 4 $ possible moves. No matter what the first player plays, the second player only has $ 1 $ possible move, so there are $ 4 $ possible games.

## 样例 #1

### 输入

```
2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
69420
```

### 输出

```
629909355
```

## 样例 #3

### 输入

```
42069
```

### 输出

```
675837193
```

