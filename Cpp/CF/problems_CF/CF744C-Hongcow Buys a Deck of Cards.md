---
title: "Hongcow Buys a Deck of Cards"
layout: "post"
diff: 省选/NOI-
pid: CF744C
tag: []
---

# Hongcow Buys a Deck of Cards

## 题目描述

One day, Hongcow goes to the store and sees a brand new deck of $ n $ special cards. Each individual card is either red or blue. He decides he wants to buy them immediately. To do this, he needs to play a game with the owner of the store.

This game takes some number of turns to complete. On a turn, Hongcow may do one of two things:

- Collect tokens. Hongcow collects $ 1 $ red token and $ 1 $ blue token by choosing this option (thus, $ 2 $ tokens in total per one operation).
- Buy a card. Hongcow chooses some card and spends tokens to purchase it as specified below.

The $ i $ -th card requires $ r_{i} $ red resources and $ b_{i} $ blue resources. Suppose Hongcow currently has $ A $ red cards and $ B $ blue cards. Then, the $ i $ -th card will require Hongcow to spend $ max(r_{i}-A,0) $ red tokens, and $ max(b_{i}-B,0) $ blue tokens. Note, only tokens disappear, but the cards stay with Hongcow forever. Each card can be bought only once.

Given a description of the cards and their costs determine the minimum number of turns Hongcow needs to purchase all cards.

## 输入格式

The first line of input will contain a single integer $ n $ ( $ 1<=n<=16 $ ).

The next $ n $ lines of input will contain three tokens $ c_{i} $ , $ r_{i} $ and $ b_{i} $ . $ c_{i} $ will be 'R' or 'B', denoting the color of the card as red or blue. $ r_{i} $ will be an integer denoting the amount of red resources required to obtain the card, and $ b_{i} $ will be an integer denoting the amount of blue resources required to obtain the card ( $ 0<=r_{i},b_{i}<=10^{7} $ ).

## 输出格式

Output a single integer, denoting the minimum number of turns needed to acquire all the cards.

## 说明/提示

For the first sample, Hongcow's four moves are as follows:

1. Collect tokens
2. Buy card $ 1 $
3. Buy card $ 2 $
4. Buy card $ 3 $

 Note, at the fourth step, Hongcow is able to buy card $ 3 $ because Hongcow already has one red and one blue card, so we don't need to collect tokens.For the second sample, one optimal strategy is as follows:

1. Collect tokens
2. Collect tokens
3. Buy card $ 2 $
4. Collect tokens
5. Buy card $ 3 $
6. Buy card $ 1 $

 At the fifth step, even though Hongcow has a red token, Hongcow doesn't actually need to spend it, since Hongcow has a red card already.

## 样例 #1

### 输入

```
3
R 0 1
B 1 0
R 1 1

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3
R 3 0
R 2 0
R 1 0

```

### 输出

```
6

```

