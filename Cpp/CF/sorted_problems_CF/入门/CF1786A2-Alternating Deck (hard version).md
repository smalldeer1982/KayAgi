---
title: "Alternating Deck (hard version)"
layout: "post"
diff: 入门
pid: CF1786A2
tag: []
---

# Alternating Deck (hard version)

## 题目描述

This is a hard version of the problem. In this version, there are two colors of the cards.

Alice has $ n $ cards, each card is either black or white. The cards are stacked in a deck in such a way that the card colors alternate, starting from a white card. Alice deals the cards to herself and to Bob, dealing at once several cards from the top of the deck in the following order: one card to herself, two cards to Bob, three cards to Bob, four cards to herself, five cards to herself, six cards to Bob, seven cards to Bob, eight cards to herself, and so on. In other words, on the $ i $ -th step, Alice deals $ i $ top cards from the deck to one of the players; on the first step, she deals the cards to herself and then alternates the players every two steps. When there aren't enough cards at some step, Alice deals all the remaining cards to the current player, and the process stops.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1786A2/0207dd60d582562fa5c47d04eb7edab3058bc16d.png) First Alice's steps in a deck of many cards.How many cards of each color will Alice and Bob have at the end?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 200 $ ). The description of the test cases follows

The only line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the number of cards.

## 输出格式

For each test case print four integers — the number of cards in the end for each player — in this order: white cards Alice has, black cards Alice has, white cards Bob has, black cards Bob has.

## 样例 #1

### 输入

```
5
10
6
17
8
1000000
```

### 输出

```
3 2 2 3
1 0 2 3
6 4 3 4
2 1 2 3
250278 249924 249722 250076
```

