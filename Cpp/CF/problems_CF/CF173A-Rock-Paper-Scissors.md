---
title: "Rock-Paper-Scissors"
layout: "post"
diff: 普及-
pid: CF173A
tag: []
---

# Rock-Paper-Scissors

## 题目描述

Nikephoros and Polycarpus play rock-paper-scissors. The loser gets pinched (not too severely!).

Let us remind you the rules of this game. Rock-paper-scissors is played by two players. In each round the players choose one of three items independently from each other. They show the items with their hands: a rock, scissors or paper. The winner is determined by the following rules: the rock beats the scissors, the scissors beat the paper and the paper beats the rock. If the players choose the same item, the round finishes with a draw.

Nikephoros and Polycarpus have played $ n $ rounds. In each round the winner gave the loser a friendly pinch and the loser ended up with a fresh and new red spot on his body. If the round finished in a draw, the players did nothing and just played on.

Nikephoros turned out to have worked out the following strategy: before the game began, he chose some sequence of items $ A=(a_{1},a_{2},...,a_{m}) $ , and then he cyclically showed the items from this sequence, starting from the first one. Cyclically means that Nikephoros shows signs in the following order: $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{m} $ , $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{m} $ , $ a_{1} $ , $ ... $ and so on. Polycarpus had a similar strategy, only he had his own sequence of items $ B=(b_{1},b_{2},...,b_{k}) $ .

Determine the number of red spots on both players after they've played $ n $ rounds of the game. You can consider that when the game began, the boys had no red spots on them.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=2·10^{9} $ ) — the number of the game's rounds.

The second line contains sequence $ A $ as a string of $ m $ characters and the third line contains sequence $ B $ as a string of $ k $ characters ( $ 1<=m,k<=1000 $ ). The given lines only contain characters "R", "S" and "P". Character "R" stands for the rock, character "S" represents the scissors and "P" represents the paper.

## 输出格式

Print two space-separated integers: the numbers of red spots Nikephoros and Polycarpus have.

## 说明/提示

In the first sample the game went like this:

- R - R. Draw.
- P - S. Nikephoros loses.
- S - P. Polycarpus loses.
- R - P. Nikephoros loses.
- P - R. Polycarpus loses.
- S - S. Draw.
- R - P. Nikephoros loses.

Thus, in total Nikephoros has $ 3 $ losses (and $ 3 $ red spots), and Polycarpus only has $ 2 $ .

## 样例 #1

### 输入

```
7
RPS
RSPP

```

### 输出

```
3 2
```

## 样例 #2

### 输入

```
5
RRRRRRRR
R

```

### 输出

```
0 0
```

