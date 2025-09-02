---
title: "Alice, Bob and Chocolate"
layout: "post"
diff: 普及-
pid: CF6C
tag: ['模拟']
---

# Alice, Bob and Chocolate

## 题目描述

Alice and Bob like games. And now they are ready to start a new game. They have placed $ n $ chocolate bars in a line. Alice starts to eat chocolate bars one by one from left to right, and Bob — from right to left. For each chocololate bar the time, needed for the player to consume it, is known (Alice and Bob eat them with equal speed). When the player consumes a chocolate bar, he immediately starts with another. It is not allowed to eat two chocolate bars at the same time, to leave the bar unfinished and to make pauses. If both players start to eat the same bar simultaneously, Bob leaves it to Alice as a true gentleman.

How many bars each of the players will consume?

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=10^{5} $ ) — the amount of bars on the table. The second line contains a sequence $ t_{1},t_{2},...,t_{n} $ ( $ 1<=t_{i}<=1000 $ ), where $ t_{i} $ is the time (in seconds) needed to consume the $ i $ -th bar (in the order from left to right).

## 输出格式

Print two numbers $ a $ and $ b $ , where $ a $ is the amount of bars consumed by Alice, and $ b $ is the amount of bars consumed by Bob.

## 样例 #1

### 输入

```
5
2 9 8 2 7

```

### 输出

```
2 3

```

