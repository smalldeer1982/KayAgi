---
title: "Restaurant Game"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1599B
tag: []
---

# Restaurant Game

## 题目描述

Alice and Bob always had hard time choosing restaurant for the dinner. Previously they performed Eenie Meenie Miney Mo game, but eventually as their restaurant list grew, they had to create a new game. This new game starts as they write restaurant names on $ N $ cards and align the cards in one line. Before the game begins, they both choose starting card and starting direction they are going to. They take turns in order one after another. After each turn, they move one card in their current direction. If they reach the end or beginning of the line of cards they change direction. Once they meet in a card, the card is marked for removal and is removed the first moment they both leave the card.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1599B/6c640cc608bf157b205c020e47ff44f6f8443491.png)Example of how card is removedThey repeat this process until there is only one restaurant card left. Since there are a lot of restaurant cards, they are bored to simulate this process over and over and need your help to determine the last card that remains. Can you help them?

## 输入格式

The first line of the input is one integer $ T $ ( $ 1 $ $ \leq $ $ T $ $ \leq $ $ 10^{4} $ ) representing number of test cases. Each test case contains 3 lines: The first line contains an integer $ N $ representing initial number of cards. Next line contains two integer values $ A,B $ ( $ 0 $ $ \leq $ $ A, B $ &lt; $ N $ , $ 2 $ $ \leq $ $ N $ $ \leq $ $ 10^{18} $ ) representing starting 0-based index of the card in the array. Last line contains two strings $ D_A, D_B $ $ \in $ {"left", "right"} representing starting direction of their movement.

## 输出格式

The output contains $ T $ integer number – the 0-based index of the last card that remains for every test case in order.

## 说明/提示

Note that since Alice is starting at the beginning of the line even though her initial direction is left, on her next move she will go right.

## 样例 #1

### 输入

```
1
4
0 1
left right
```

### 输出

```
0
```

