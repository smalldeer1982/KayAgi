---
title: "Royal Flush"
layout: "post"
diff: 省选/NOI-
pid: CF2038M
tag: ['动态规划 DP', '标签464']
---

# Royal Flush

## 题目描述

Consider the following game. There is a deck, which consists of cards of $ n $ different suits. For each suit, there are $ 13 $ cards in the deck, all with different ranks (the ranks are $ 2 $ , $ 3 $ , $ 4 $ , ..., $ 10 $ , Jack, Queen, King and Ace).

Initially, the deck is shuffled randomly (all $ (13n)! $ possible orders of cards have the same probability). You draw $ 5 $ topmost cards from the deck. Then, every turn of the game, the following events happen, in the given order:

1. if the cards in your hand form a Royal Flush (a $ 10 $ , a Jack, a Queen, a King, and an Ace, all of the same suit), you win, and the game ends;
2. if you haven't won yet, and the deck is empty, you lose, and the game ends;
3. if the game hasn't ended yet, you may choose any cards from your hand (possibly, all of them) and discard them. When a card is discarded, it is removed from the game;
4. finally, you draw cards from the deck, until you have $ 5 $ cards or the deck becomes empty.

Your goal is to find a strategy that allows you to win in the minimum expected number of turns. Note that the turn when the game ends is not counted (for example, if the $ 5 $ cards you draw initially already form a Royal Flush, you win in $ 0 $ turns).

Calculate the minimum possible expected number of turns required to win the game.

## 输入格式

The only line contains one integer $ n $ ( $ 1 \le n \le 4 $ ) — the number of suits used in the game.

## 输出格式

Print the minimum expected number of turns.

Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ . Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer will be accepted if and only if $ \frac{|a - b|}{\max{(1, |b|)}} \le 10^{-6} $ .

## 样例 #1

### 输入

```
1
```

### 输出

```
3.598290598
```

## 样例 #2

### 输入

```
2
```

### 输出

```
8.067171309
```

