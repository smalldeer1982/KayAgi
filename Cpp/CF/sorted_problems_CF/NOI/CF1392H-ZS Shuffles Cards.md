---
title: "ZS Shuffles Cards"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1392H
tag: []
---

# ZS Shuffles Cards

## 题目描述

zscoder has a deck of $ n+m $ custom-made cards, which consists of $ n $ cards labelled from $ 1 $ to $ n $ and $ m $ jokers. Since zscoder is lonely, he wants to play a game with himself using those cards.

Initially, the deck is shuffled uniformly randomly and placed on the table. zscoder has a set $ S $ which is initially empty.

Every second, zscoder draws the top card from the deck.

- If the card has a number $ x $ written on it, zscoder removes the card and adds $ x $ to the set $ S $ .
- If the card drawn is a joker, zscoder places all the cards back into the deck and reshuffles (uniformly randomly) the $ n+m $ cards to form a new deck (hence the new deck now contains all cards from $ 1 $ to $ n $ and the $ m $ jokers). Then, if $ S $ currently contains all the elements from $ 1 $ to $ n $ , the game ends. Shuffling the deck doesn't take time at all.

What is the expected number of seconds before the game ends? We can show that the answer can be written in the form $ \frac{P}{Q} $ where $ P, Q $ are relatively prime integers and $ Q \neq 0 \bmod 998244353 $ . Output the value of $ (P       \cdot Q^{-1}) $ modulo $ 998244353 $ .

## 输入格式

The only line of the input contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 2 \cdot 10^{6} $ ).

## 输出格式

Output a single integer, the value of $ (P \cdot Q^{-1}) $ modulo $ 998244353 $ .

## 说明/提示

For the first sample, it can be proven that the expected time before the game ends is $ 5 $ seconds.

For the second sample, it can be proven that the expected time before the game ends is $ \frac{28}{3} $ seconds.

## 样例 #1

### 输入

```
2 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
332748127
```

## 样例 #3

### 输入

```
14 9
```

### 输出

```
969862773
```

