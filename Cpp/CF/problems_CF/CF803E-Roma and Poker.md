---
title: "Roma and Poker"
layout: "post"
diff: 提高+/省选-
pid: CF803E
tag: []
---

# Roma and Poker

## 题目描述

Each evening Roma plays online poker on his favourite website. The rules of poker on this website are a bit strange: there are always two players in a hand, there are no bets, and the winner takes $ 1 $ virtual bourle from the loser.

Last evening Roma started to play poker. He decided to spend no more than $ k $ virtual bourles — he will stop immediately if the number of his loses exceeds the number of his wins by $ k $ . Also Roma will leave the game if he wins enough money for the evening, i.e. if the number of wins exceeds the number of loses by $ k $ .

Next morning Roma found a piece of paper with a sequence on it representing his results. Roma doesn't remember the results exactly, and some characters in the sequence are written in a way such that it's impossible to recognize this character, so Roma can't recall whether he won $ k $ bourles or he lost.

The sequence written by Roma is a string $ s $ consisting of characters W (Roma won the corresponding hand), L (Roma lost), D (draw) and ? (unknown result). Roma wants to restore any valid sequence by changing all ? characters to W, L or D. The sequence is called valid if all these conditions are met:

- In the end the absolute difference between the number of wins and loses is equal to $ k $ ;
- There is no hand such that the absolute difference before this hand was equal to $ k $ .

Help Roma to restore any such sequence.

## 输入格式

The first line contains two numbers $ n $ (the length of Roma's sequence) and $ k $ ( $ 1<=n,k<=1000 $ ).

The second line contains the sequence $ s $ consisting of characters W, L, D and ?. There are exactly $ n $ characters in this sequence.

## 输出格式

If there is no valid sequence that can be obtained from $ s $ by replacing all ? characters by W, L or D, print NO.

Otherwise print this sequence. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3 2
L??

```

### 输出

```
LDL

```

## 样例 #2

### 输入

```
3 1
W??

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
20 5
?LLLLLWWWWW?????????

```

### 输出

```
WLLLLLWWWWWWWWLWLWDW

```

