---
title: "Magic Trick"
layout: "post"
diff: 提高+/省选-
pid: CF452C
tag: []
---

# Magic Trick

## 题目描述

Alex enjoys performing magic tricks. He has a trick that requires a deck of $ n $ cards. He has $ m $ identical decks of $ n $ different cards each, which have been mixed together. When Alex wishes to perform the trick, he grabs $ n $ cards at random and performs the trick with those. The resulting deck looks like a normal deck, but may have duplicates of some cards.

The trick itself is performed as follows: first Alex allows you to choose a random card from the deck. You memorize the card and put it back in the deck. Then Alex shuffles the deck, and pulls out a card. If the card matches the one you memorized, the trick is successful.

You don't think Alex is a very good magician, and that he just pulls a card randomly from the deck. Determine the probability of the trick being successful if this is the case.

## 输入格式

First line of the input consists of two integers $ n $ and $ m $ ( $ 1<=n,m<=1000 $ ), separated by space — number of cards in each deck, and number of decks.

## 输出格式

On the only line of the output print one floating point number – probability of Alex successfully performing the trick. Relative or absolute error of your answer should not be higher than $ 10^{-6} $ .

## 说明/提示

In the first sample, with probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF452C/11122857c8fbc4142ef5e22b839ee7f4cb432c56.png) Alex will perform the trick with two cards with the same value from two different decks. In this case the trick is guaranteed to succeed.

With the remaining ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF452C/c171d3ec3c02b9089b571e24a262c7ab1c15c85e.png) probability he took two different cards, and the probability of pulling off the trick is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF452C/fda96725ccc697b767e5edbf0d5cfb5ba17d9aa2.png).

The resulting probability is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF452C/a205e249fe823af48892b89b115b150661d33162.png)

## 样例 #1

### 输入

```
2 2

```

### 输出

```
0.6666666666666666

```

## 样例 #2

### 输入

```
4 4

```

### 输出

```
0.4000000000000000

```

## 样例 #3

### 输入

```
1 2

```

### 输出

```
1.0000000000000000

```

