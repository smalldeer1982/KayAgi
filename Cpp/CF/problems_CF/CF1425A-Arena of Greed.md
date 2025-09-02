---
title: "Arena of Greed"
layout: "post"
diff: 普及/提高-
pid: CF1425A
tag: ['贪心', '博弈论']
---

# Arena of Greed

## 题目描述

Lately, Mr. Chanek frequently plays the game Arena of Greed. As the name implies, the game's goal is to find the greediest of them all, who will then be crowned king of Compfestnesia.

The game is played by two people taking turns, where Mr. Chanek takes the first turn. Initially, there is a treasure chest containing $ N $ gold coins. The game ends if there are no more gold coins in the chest. In each turn, the players can make one of the following moves:

- Take one gold coin from the chest.
- Take half of the gold coins on the chest. This move is only available if the number of coins in the chest is even.

Both players will try to maximize the number of coins they have. Mr. Chanek asks your help to find the maximum number of coins he can get at the end of the game if both he and the opponent plays optimally.

## 输入格式

The first line contains a single integer $ T $ $ (1 \le T \le 10^5) $ denotes the number of test cases.

The next $ T $ lines each contain a single integer $ N $ $ (1 \le N \le 10^{18}) $ .

## 输出格式

$ T $ lines, each line is the answer requested by Mr. Chanek.

## 说明/提示

For the first case, the game is as follows:

1. Mr. Chanek takes one coin.
2. The opponent takes two coins.
3. Mr. Chanek takes one coin.
4. The opponent takes one coin.

For the second case, the game is as follows:

1. Mr. Chanek takes three coins.
2. The opponent takes one coin.
3. Mr. Chanek takes one coin.
4. The opponent takes one coin.

## 样例 #1

### 输入

```
2
5
6
```

### 输出

```
2
4
```

