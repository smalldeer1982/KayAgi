---
title: "Flip the Cards"
layout: "post"
diff: 省选/NOI-
pid: CF1503D
tag: []
---

# Flip the Cards

## 题目描述

There is a deck of $ n $ cards. The $ i $ -th card has a number $ a_i $ on the front and a number $ b_i $ on the back. Every integer between $ 1 $ and $ 2n $ appears exactly once on the cards.

A deck is called sorted if the front values are in increasing order and the back values are in decreasing order. That is, if $ a_i< a_{i+1} $ and $ b_i> b_{i+1} $ for all $ 1\le i<n $ .

To flip a card $ i $ means swapping the values of $ a_i $ and $ b_i $ . You must flip some subset of cards (possibly, none), then put all the cards in any order you like. What is the minimum number of cards you must flip in order to sort the deck?

## 输入格式

The first line contains a single integer $ n $ ( $ 1\le n\le 2\cdot 10^5 $ ) — the number of cards.

The next $ n $ lines describe the cards. The $ i $ -th of these lines contains two integers $ a_i, b_i $ ( $ 1\le a_i, b_i\le 2n $ ). Every integer between $ 1 $ and $ 2n $ appears exactly once.

## 输出格式

If it is impossible to sort the deck, output "-1". Otherwise, output the minimum number of flips required to sort the deck.

## 说明/提示

In the first test case, we flip the cards $ (1, 9) $ and $ (2, 7) $ . The deck is then ordered $ (3,10), (5,8), (6,4), (7,2), (9,1) $ . It is sorted because $ 3<5<6<7<9 $ and $ 10>8>4>2>1 $ .

In the second test case, it is impossible to sort the deck.

## 样例 #1

### 输入

```
5
3 10
6 4
1 9
5 8
2 7
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
1 2
3 4
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3
1 2
3 6
4 5
```

### 输出

```
-1
```

