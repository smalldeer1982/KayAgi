---
title: "Bear and Poker"
layout: "post"
diff: 普及/提高-
pid: CF573A
tag: []
---

# Bear and Poker

## 题目描述

Limak is an old brown bear. He often plays poker with his friends. Today they went to a casino. There are $ n $ players (including Limak himself) and right now all of them have bids on the table. $ i $ -th of them has bid with size $ a_{i} $ dollars.

Each player can double his bid any number of times and triple his bid any number of times. The casino has a great jackpot for making all bids equal. Is it possible that Limak and his friends will win a jackpot?

## 输入格式

First line of input contains an integer $ n $ ( $ 2<=n<=10^{5} $ ), the number of players.

The second line contains $ n $ integer numbers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the bids of players.

## 输出格式

Print "Yes" (without the quotes) if players can make their bids become equal, or "No" otherwise.

## 说明/提示

In the first sample test first and third players should double their bids twice, second player should double his bid once and fourth player should both double and triple his bid.

It can be shown that in the second sample test there is no way to make all bids equal.

## 样例 #1

### 输入

```
4
75 150 75 50

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
3
100 150 250

```

### 输出

```
No

```

