---
title: "Combination"
layout: "post"
diff: 普及-
pid: CF155B
tag: []
---

# Combination

## 题目描述

Ilya plays a card game by the following rules.

A player has several cards. Each card contains two non-negative integers inscribed, one at the top of the card and one at the bottom. At the beginning of the round the player chooses one of his cards to play it. If the top of the card contains number $ a_{i} $ , and the bottom contains number $ b_{i} $ , then when the player is playing the card, he gets $ a_{i} $ points and also gets the opportunity to play additional $ b_{i} $ cards. After the playing the card is discarded.

More formally: let's say that there is a counter of the cards that can be played. At the beginning of the round the counter equals one. When a card is played, the counter decreases by one for the played card and increases by the number $ b_{i} $ , which is written at the bottom of the card. Then the played card is discarded. If after that the counter is not equal to zero, the player gets the opportunity to play another card from the remaining cards. The round ends when the counter reaches zero or the player runs out of cards.

Of course, Ilya wants to get as many points as possible. Can you determine the maximum number of points he can score provided that you know his cards?

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=1000 $ ) — the number of cards Ilya has.

Each of the next $ n $ lines contains two non-negative space-separated integers — $ a_{i} $ and $ b_{i} $ ( $ 0<=a_{i},b_{i}<=10^{4} $ ) — the numbers, written at the top and the bottom of the $ i $ -th card correspondingly.

## 输出格式

Print the single number — the maximum number of points you can score in one round by the described rules.

## 说明/提示

In the first sample none of two cards brings extra moves, so you should play the one that will bring more points.

In the second sample you should first play the third card that doesn't bring any points but lets you play both remaining cards.

## 样例 #1

### 输入

```
2
1 0
2 0

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
1 0
2 0
0 2

```

### 输出

```
3

```

