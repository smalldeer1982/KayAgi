---
title: "Blackboard Game"
layout: "post"
diff: 难度0
pid: CF2123A
tag: []
---

# Blackboard Game

## 题目描述

Initially, the integers from $ 0 $ to $ n-1 $ are written on a blackboard.

In one round,

- Alice chooses an integer $ a $ on the blackboard and erases it;
- then Bob chooses an integer $ b $ on the blackboard such that $ a+b \equiv 3 \pmod 4 $ $ ^{\text{∗}} $ and erases it.

Rounds take place in succession until a player is unable to make a move — the first player who is unable to make a move loses. Determine who wins with optimal play.

 $ ^{\text{∗}} $ We define that $ x\equiv y\pmod m $ whenever $ x-y $ is an integer multiple of $ m $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

The only line of each test case contains an integer $ n $ ( $ 1\leq n \leq 100 $ ) — the number of integers written on the blackboard.

## 输出格式

For each test case, output on a single line "Alice" if Alice wins with optimal play, and "Bob" if Bob wins with optimal play.

You can output the answer in any case (upper or lower). For example, the strings "aLiCe", "alice", "ALICE", and "alICE" will be recognized as "Alice".

## 说明/提示

In the first sample, suppose Alice chooses $ 0 $ , then Bob cannot choose any number so Alice wins immediately.

In the second sample, suppose Alice chooses $ 0 $ , then Bob can choose $ 3 $ . Then suppose Alice chooses $ 2 $ , then Bob can choose $ 1 $ . Then Alice has no numbers remaining, so Bob wins.

## 样例 #1

### 输入

```
5
2
4
5
7
100
```

### 输出

```
Alice
Bob
Alice
Alice
Bob
```

