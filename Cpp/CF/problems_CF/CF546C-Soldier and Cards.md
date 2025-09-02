---
title: "Soldier and Cards"
layout: "post"
diff: 普及/提高-
pid: CF546C
tag: []
---

# Soldier and Cards

## 题目描述

Two bored soldiers are playing card war. Their card deck consists of exactly $ n $ cards, numbered from $ 1 $ to $ n $ , all values are different. They divide cards between them in some manner, it's possible that they have different number of cards. Then they play a "war"-like card game.

The rules are following. On each turn a fight happens. Each of them picks card from the top of his stack and puts on the table. The one whose card value is bigger wins this fight and takes both cards from the table to the bottom of his stack. More precisely, he first takes his opponent's card and puts to the bottom of his stack, and then he puts his card to the bottom of his stack. If after some turn one of the player's stack becomes empty, he loses and the other one wins.

You have to calculate how many fights will happen and who will win the game, or state that game won't end.

## 输入格式

First line contains a single integer $ n $ ( $ 2<=n<=10 $ ), the number of cards.

Second line contains integer $ k_{1} $ ( $ 1<=k_{1}<=n-1 $ ), the number of the first soldier's cards. Then follow $ k_{1} $ integers that are the values on the first soldier's cards, from top to bottom of his stack.

Third line contains integer $ k_{2} $ ( $ k_{1}+k_{2}=n $ ), the number of the second soldier's cards. Then follow $ k_{2} $ integers that are the values on the second soldier's cards, from top to bottom of his stack.

All card values are different.

## 输出格式

If somebody wins in this game, print $ 2 $ integers where the first one stands for the number of fights before end of game and the second one is $ 1 $ or $ 2 $ showing which player has won.

If the game won't end and will continue forever output $ -1 $ .

## 说明/提示

First sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF546C/13fabc002be9b868c475a6223b80932fbf64aac8.png)Second sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF546C/baf8f9cbd8baa7b7a7d1f276ff7ae6d3445560b3.png)

## 样例 #1

### 输入

```
4
2 1 3
2 4 2

```

### 输出

```
6 2
```

## 样例 #2

### 输入

```
3
1 2
2 1 3

```

### 输出

```
-1
```

