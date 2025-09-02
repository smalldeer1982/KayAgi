---
title: "Lieges of Legendre"
layout: "post"
diff: 提高+/省选-
pid: CF603C
tag: []
---

# Lieges of Legendre

## 题目描述

Kevin and Nicky Sun have invented a new game called Lieges of Legendre. In this game, two players take turns modifying the game state with Kevin moving first. Initially, the game is set up so that there are $ n $ piles of cows, with the $ i $ -th pile containing $ a_{i} $ cows. During each player's turn, that player calls upon the power of Sunlight, and uses it to either:

1. Remove a single cow from a chosen non-empty pile.
2. Choose a pile of cows with even size $ 2·x $ ( $ x&gt;0 $ ), and replace it with $ k $ piles of $ x $ cows each.

The player who removes the last cow wins. Given $ n $ , $ k $ , and a sequence $ a_{1},a_{2},...,a_{n} $ , help Kevin and Nicky find the winner, given that both sides play in optimal way.

## 输入格式

The first line of the input contains two space-separated integers $ n $ and $ k $ ( $ 1<=n<=100000,1<=k<=10^{9} $ ).

The second line contains $ n $ integers, $ a_{1},a_{2},...\ a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) describing the initial state of the game.

## 输出格式

Output the name of the winning player, either "Kevin" or "Nicky" (without quotes).

## 说明/提示

In the second sample, Nicky can win in the following way: Kevin moves first and is forced to remove a cow, so the pile contains two cows after his move. Next, Nicky replaces this pile of size 2 with two piles of size 1. So the game state is now two piles of size 1. Kevin then removes one of the remaining cows and Nicky wins by removing the other.

## 样例 #1

### 输入

```
2 1
3 4

```

### 输出

```
Kevin

```

## 样例 #2

### 输入

```
1 2
3

```

### 输出

```
Nicky

```

