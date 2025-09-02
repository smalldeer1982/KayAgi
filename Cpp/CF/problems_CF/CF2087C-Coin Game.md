---
title: "Coin Game"
layout: "post"
diff: 难度0
pid: CF2087C
tag: []
---

# Coin Game

## 题目描述

There are some coins arranged in a line, numbered from $ 1 $ from left to right. There are three types of coins: gold, silver, and bronze.

Two players play a game; players take turns, and the first player makes the first turn. In one turn, the player chooses one of the three types of coins, and then collects all coins of that type which are still not taken by the other player. The game continues until all the coins are collected. Both players play optimally, and each player wants to maximize the number of coins he/she gets.

Your task is to answer $ q $ independent queries of the following form: how many coins can the first player collect if the game is played using only coins with indices from $ l $ to $ r $ inclusive.

## 输入格式

The first line contains a string $ s $ ( $ 1 \le |s| \le 10^5 $ ), consisting of the characters G, S, and/or B. G means that the coin is gold. S means that the coin is silver. B means that the coin is bronze.

The second line contains a single integer $ q $ ( $ 1 \le q \le 10^5 $ ) — the number of queries.

Then $ q $ lines follow; each of them contains two integers $ l $ and $ r $ ( $ 1 \le l \le r \le |s| $ ).

## 输出格式

For each query, print a single integer — the number of coins the first player can collect if the game is played using only coins with indices from $ l $ to $ r $ inclusive.

## 说明/提示

Let's consider the queries from the example:

- In the first query, all coins are in the game. The optimal play can proceed as follows: the first player takes all the bronze coins, the second takes all the gold coins, and finally, the first player takes all the silver coins. Then the first player will collect $ 5 $ coins;
- In the second query, the coins from the $ 2 $ -nd to the $ 6 $ -th are in the game. The optimal play can proceed as follows: the first player takes all the silver coins, the second takes all the gold coins, and finally, the first player takes all the bronze coins. Then the first player will collect $ 3 $ coins;
- In the third query, the coins from the $ 1 $ -st to the $ 5 $ -th are in the game. The optimal play can proceed as follows: the first player takes all the silver coins, the second takes all the bronze coins, and finally, the first player takes all the gold coins. Then the first player will collect $ 3 $ coins;
- In the fourth query, only the $ 3 $ -rd coin is in the game. The first player can take it immediately and end the game.

## 样例 #1

### 输入

```
BGSSBGB
5
1 7
2 6
1 5
3 3
4 7
```

### 输出

```
5
3
3
1
3
```

