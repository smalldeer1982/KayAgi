---
title: "Cards Sorting"
layout: "post"
diff: 普及+/提高
pid: CF830B
tag: []
---

# Cards Sorting

## 题目描述

Vasily has a deck of cards consisting of $ n $ cards. There is an integer on each of the cards, this integer is between $ 1 $ and $ 100000 $ , inclusive. It is possible that some cards have the same integers on them.

Vasily decided to sort the cards. To do this, he repeatedly takes the top card from the deck, and if the number on it equals the minimum number written on the cards in the deck, then he places the card away. Otherwise, he puts it under the deck and takes the next card from the top, and so on. The process ends as soon as there are no cards in the deck. You can assume that Vasily always knows the minimum number written on some card in the remaining deck, but doesn't know where this card (or these cards) is.

You are to determine the total number of times Vasily takes the top card from the deck.

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=100000 $ ) — the number of cards in the deck.

The second line contains a sequence of $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=100000 $ ), where $ a_{i} $ is the number written on the $ i $ -th from top card in the deck.

## 输出格式

Print the total number of times Vasily takes the top card from the deck.

## 说明/提示

In the first example Vasily at first looks at the card with number $ 6 $ on it, puts it under the deck, then on the card with number $ 3 $ , puts it under the deck, and then on the card with number $ 1 $ . He places away the card with $ 1 $ , because the number written on it is the minimum among the remaining cards. After that the cards from top to bottom are $ [2,6,3] $ . Then Vasily looks at the top card with number $ 2 $ and puts it away. After that the cards from top to bottom are $ [6,3] $ . Then Vasily looks at card $ 6 $ , puts it under the deck, then at card $ 3 $ and puts it away. Then there is only one card with number $ 6 $ on it, and Vasily looks at it and puts it away. Thus, in total Vasily looks at $ 7 $ cards.

## 样例 #1

### 输入

```
4
6 3 1 2

```

### 输出

```
7

```

## 样例 #2

### 输入

```
1
1000

```

### 输出

```
1

```

## 样例 #3

### 输入

```
7
3 3 3 3 3 3 3

```

### 输出

```
7

```

