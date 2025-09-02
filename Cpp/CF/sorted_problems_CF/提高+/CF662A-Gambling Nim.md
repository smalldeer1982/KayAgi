---
title: "Gambling Nim"
layout: "post"
diff: 提高+/省选-
pid: CF662A
tag: []
---

# Gambling Nim

## 题目描述

As you know, the game of "Nim" is played with $ n $ piles of stones, where the $ i $ -th pile initially contains $ a_{i} $ stones. Two players alternate the turns. During a turn a player picks any non-empty pile and removes any positive number of stones from it. The one who is not able to make a move loses the game.

Petya and Vasya are tired of playing Nim, so they invented their own version of the game and named it the "Gambling Nim". They have $ n $ two-sided cards, one side of the $ i $ -th card has number $ a_{i} $ written on it, while the other side has number $ b_{i} $ . At the beginning of the game the players put all the cards on the table, each card only one of its sides up, and this side is chosen independently and uniformly. Thus they obtain a sequence $ c_{1},c_{2},...,c_{n} $ , where $ c_{i} $ is equal to $ a_{i} $ or $ b_{i} $ . Then they take $ n $ piles of stones, with $ i $ -th pile containing exactly $ c_{i} $ stones and play Nim. Petya takes the first turn.

Given that both players play optimally, find the probability of Petya's victory. Output the answer as an irreducible fraction.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=500000 $ ) — the number of cards in the deck.

Each of the following $ n $ lines contains the description of one card, consisting of two integers $ a_{i} $ and $ b_{i} $ ( $ 0<=a_{i},b_{i}<=10^{18} $ ).

## 输出格式

Output the answer as an irreducible fraction $ p/q $ . If the probability of Petya's victory is $ 0 $ , print 0/1.

## 样例 #1

### 输入

```
2
1 1
1 1

```

### 输出

```
0/1

```

## 样例 #2

### 输入

```
2
1 2
1 2

```

### 输出

```
1/2

```

## 样例 #3

### 输入

```
3
0 4
1 5
2 3

```

### 输出

```
1/1

```

