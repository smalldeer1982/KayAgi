---
title: "Earn or Unlock"
layout: "post"
diff: 提高+/省选-
pid: CF1854B
tag: []
---

# Earn or Unlock

## 题目描述

Andrea is playing the game Tanto Cuore.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1854B/1661c88808ceec929a74ca91720280905e810592.png)He has a deck of $ n $ cards with values $ a_1, \ldots, a_n $ from top to bottom. Each card can be either locked or unlocked. Initially, only the topmost card is unlocked.

The game proceeds in turns. In each turn, Andrea chooses an unlocked card in the deck — the value written on the card is $ v $ — and performs exactly one of the following two operations:

1. Unlock the first $ v $ locked cards in the deck from the top. If there are less than $ v $ locked cards in the deck, then unlock all the locked cards.
2. Earn $ v $ victory points.

 In both cases, after performing the operation, he removes the card from the deck.The game ends when all the cards remaining in the deck are locked, or there are no more cards in the deck.

What is the maximum number of victory points Andrea can earn?

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the number of cards in the deck.

The second line contains $ n $ integers $ a_1, \ldots, a_n $ ( $ 0 \leq a_1, \ldots, a_n \leq n $ ) — the values of the cards in the deck.

## 输出格式

Output a single integer — the maximum number of victory points Andrea can earn.

## 说明/提示

In the first sample test, the deck starts as \[unlocked, locked\]. Then, Andrea uses the first card to unlock the second card. Then he uses the second card to earn $ 2 $ victory points.

In the second sample test, Andrea can use the first card to unlock the second and the third card. Then he uses the second and the third card to earn $ 4+5=9 $ victory points.

In the third sample test, Andrea can't unlock any cards or gain any victory points with the first card.

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
2 4 5 0 1
```

### 输出

```
9
```

## 样例 #3

### 输入

```
4
0 4 4 4
```

### 输出

```
0
```

