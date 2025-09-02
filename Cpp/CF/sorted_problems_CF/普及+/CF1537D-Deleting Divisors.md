---
title: "Deleting Divisors"
layout: "post"
diff: 普及+/提高
pid: CF1537D
tag: ['数学']
---

# Deleting Divisors

## 题目描述

Alice and Bob are playing a game.

They start with a positive integer $ n $ and take alternating turns doing operations on it. Each turn a player can subtract from $ n $ one of its divisors that isn't $ 1 $ or $ n $ . The player who cannot make a move on his/her turn loses. Alice always moves first.

Note that they subtract a divisor of the current number in each turn.

You are asked to find out who will win the game if both players play optimally.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Then $ t $ test cases follow.

Each test case contains a single integer $ n $ ( $ 1 \leq n \leq 10^9 $ ) — the initial number.

## 输出格式

For each test case output "Alice" if Alice will win the game or "Bob" if Bob will win, if both players play optimally.

## 说明/提示

In the first test case, the game ends immediately because Alice cannot make a move.

In the second test case, Alice can subtract $ 2 $ making $ n = 2 $ , then Bob cannot make a move so Alice wins.

In the third test case, Alice can subtract $ 3 $ so that $ n = 9 $ . Bob's only move is to subtract $ 3 $ and make $ n = 6 $ . Now, Alice can subtract $ 3 $ again and $ n = 3 $ . Then Bob cannot make a move, so Alice wins.

## 样例 #1

### 输入

```
4
1
4
12
69
```

### 输出

```
Bob
Alice
Alice
Bob
```

