---
title: "GAME2 - Looks like Nim - but it is not"
layout: "post"
diff: 难度0
pid: SP8720
tag: []
---

# GAME2 - Looks like Nim - but it is not

## 题目描述

Goran and Stjepan play an interesting game. On the table between them, there is a sequence of N skyscrapers made of Lego bricks. All of them are made of equal bricks and each of them has a height, which equals the number of bricks in it.

Goran plays first; then Stjepan, then Goran, then Stjepan and so on. In each move, a player has to find the **highest** skyscraper in the sequence (if there's more than one, he chooses any of them) and reduces its height - that is, takes away an arbitrary (positive) number of bricks from it.

The winner of the game is the one who takes away the last brick. Equivalently, the loser of the game is the one who is not able to make a move.

Help Goran and tell him in how many ways he can play his first move, so that he can certainly win (no matter how Stjepan played). If Goran doesn't have a winning strategy at all, the number of ways is zero.

## 输入格式

In the first line of input, there is an integer T

Then follow T blocks, each of them in two lines:

\- N

\- a sequence of N integers in the range \[0, 10 $ ^{6} $ \]

## 输出格式

For each of the T games, print the required number of ways.

## 样例 #1

### 输入

```
350 1 0 1 030 7 051 0 1 0 1
```

### 输出

```
0
```

