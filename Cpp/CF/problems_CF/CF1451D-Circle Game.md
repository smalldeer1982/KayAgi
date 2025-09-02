---
title: "Circle Game"
layout: "post"
diff: 普及+/提高
pid: CF1451D
tag: []
---

# Circle Game

## 题目描述

Utkarsh is forced to play yet another one of Ashish's games. The game progresses turn by turn and as usual, Ashish moves first.

Consider the 2D plane. There is a token which is initially at  $ (0,0) $ . In one move a player must increase either the $ x $ coordinate or the $ y $ coordinate of the token by exactly $ k $ . In doing so, the player must ensure that the token stays within a (Euclidean) distance $ d $ from $ (0,0) $ .

In other words, if after a move the coordinates of the token are $ (p,q) $ , then $ p^2 + q^2 \leq d^2 $ must hold.

The game ends when a player is unable to make a move. It can be shown that the game will end in a finite number of moves. If both players play optimally, determine who will win.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

The only line of each test case contains two space separated integers $ d $ ( $ 1 \leq d \leq 10^5 $ ) and $ k $ ( $ 1 \leq k \leq d $ ).

## 输出格式

For each test case, if Ashish wins the game, print "Ashish", otherwise print "Utkarsh" (without the quotes).

## 说明/提示

In the first test case, one possible sequence of moves can be

 $ (0, 0) \xrightarrow{\text{Ashish }} (0, 1) \xrightarrow{\text{Utkarsh }} (0, 2) $ .

Ashish has no moves left, so Utkarsh wins.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1451D/00adebe318fd60c39c1fde9564efcda9489c81f2.png)

## 样例 #1

### 输入

```
5
2 1
5 2
10 3
25 4
15441 33
```

### 输出

```
Utkarsh
Ashish
Utkarsh
Utkarsh
Ashish
```

