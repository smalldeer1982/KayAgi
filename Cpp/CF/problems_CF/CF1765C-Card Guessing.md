---
title: "Card Guessing"
layout: "post"
diff: 省选/NOI-
pid: CF1765C
tag: []
---

# Card Guessing

## 题目描述

Consider a deck of cards. Each card has one of $ 4 $ suits, and there are exactly $ n $ cards for each suit — so, the total number of cards in the deck is $ 4n $ . The deck is shuffled randomly so that each of $ (4n)! $ possible orders of cards in the deck has the same probability of being the result of shuffling. Let $ c_i $ be the $ i $ -th card of the deck (from top to bottom).

Monocarp starts drawing the cards from the deck one by one. Before drawing a card, he tries to guess its suit. Monocarp remembers the suits of the $ k $ last cards, and his guess is the suit that appeared the least often among the last $ k $ cards he has drawn. So, while drawing the $ i $ -th card, Monocarp guesses that its suit is the suit that appears the minimum number of times among the cards $ c_{i-k}, c_{i-k+1}, \dots, c_{i-1} $ (if $ i \le k $ , Monocarp considers all previously drawn cards, that is, the cards $ c_1, c_2, \dots, c_{i-1} $ ). If there are multiple suits that appeared the minimum number of times among the previous cards Monocarp remembers, he chooses a random suit out of those for his guess (all suits that appeared the minimum number of times have the same probability of being chosen).

After making a guess, Monocarp draws a card and compares its suit to his guess. If they match, then his guess was correct; otherwise it was incorrect.

Your task is to calculate the expected number of correct guesses Monocarp makes after drawing all $ 4n $ cards from the deck.

## 输入格式

The first (and only) line contains two integers $ n $ ( $ 1 \le n \le 500 $ ) and $ k $ ( $ 1 \le k \le 4 \cdot n $ ).

## 输出格式

Let the expected value you have to calculate be an irreducible fraction $ \dfrac{x}{y} $ . Print one integer — the value of $ x \cdot y^{-1} \bmod 998244353 $ , where $ y^{-1} $ is the inverse to $ y $ (i. e. an integer such that $ y \cdot y^{-1} \bmod 998244353 = 1 $ ).

## 样例 #1

### 输入

```
1 1
```

### 输出

```
748683266
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
567184295
```

## 样例 #3

### 输入

```
2 7
```

### 输出

```
373153250
```

## 样例 #4

### 输入

```
2 8
```

### 输出

```
373153250
```

