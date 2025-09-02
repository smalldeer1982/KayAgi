---
title: "Binary Cards"
layout: "post"
diff: 省选/NOI-
pid: CF949E
tag: []
---

# Binary Cards

## 题目描述

It is never too late to play the fancy "Binary Cards" game!

There is an infinite amount of cards of positive and negative ranks that are used in the game. The absolute value of any card rank is a power of two, i.e. each card has a rank of either $ 2^{k} $ or $ -2^{k} $ for some integer $ k>=0 $ . There is an infinite amount of cards of any valid rank.

At the beginning of the game player forms his deck that is some multiset (possibly empty) of cards. It is allowed to pick any number of cards of any rank but the small deck is considered to be a skill indicator. Game consists of $ n $ rounds. In the $ i $ -th round jury tells the player an integer $ a_{i} $ . After that the player is obligated to draw such a subset of his deck that the sum of ranks of the chosen cards is equal to $ a_{i} $ (it is allowed to not draw any cards, in which case the sum is considered to be equal to zero). If player fails to do so, he loses and the game is over. Otherwise, player takes back all of his cards into his deck and the game proceeds to the next round. Player is considered a winner if he is able to draw the suitable set of cards in each of the rounds.

Somebody told you which numbers $ a_{i} $ the jury is going to tell you in each round. Now you want to pick a deck consisting of the minimum number of cards that allows you to win the "Binary Cards" game.

## 输入格式

The first line of input contains an integer $ n $ ( $ 1<=n<=100000 $ ), the number of rounds in the game.

The second line of input contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ -100000<=a_{i}<=100000 $ ), the numbers that jury is going to tell in each round.

## 输出格式

In the first line print the integer $ k $ ( $ 0<=k<=100000 $ ), the minimum number of cards you have to pick in your deck in ordered to win the "Binary Cards".

In the second line print $ k $ integers $ b_{1},b_{2},...,b_{k} $ ( $ -2^{20}<=b_{i}<=2^{20} $ , $ |b_{i}| $ is a power of two), the ranks of the cards in your deck. You may output ranks in any order. If there are several optimum decks, you are allowed to print any of them.

It is guaranteed that there exists a deck of minimum size satisfying all the requirements above.

## 说明/提示

In the first sample there is the only round in the game, in which you may simply draw both your cards. Note that this sample test is the only one satisfying the first test group constraints.

In the second sample you may draw the only card $ -1 $ in the first round, cards $ 4 $ and $ -1 $ in the second round, nothing in the third round, the only card $ 4 $ in the fourth round and the whole deck in the fifth round.

## 样例 #1

### 输入

```
1
9

```

### 输出

```
2
1 8

```

## 样例 #2

### 输入

```
5
-1 3 0 4 7

```

### 输出

```
3
4 -1 4

```

## 样例 #3

### 输入

```
4
2 -2 14 18

```

### 输出

```
3
-2 2 16
```

