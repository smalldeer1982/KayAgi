---
title: "ALICE - Alice and Bob"
layout: "post"
diff: 省选/NOI-
pid: SP9934
tag: []
---

# ALICE - Alice and Bob

## 题目描述

Alice and Bob are very smart guys and they like to play all kinds of games in their spare time. The most amazing thing is that they always find the best strategy, and that's why they feel bored again and again. They just invented a new game, as they usually did.

The rule of the new game is quite simple. At the beginning of the game, they write down **N** random positive integers, then they take turns (Alice first) to either:

1. Decrease a number by one.
2. Erase any two numbers and write down their sum.

Whenever a number is decreased to 0, it will be erased automatically. The game ends when all numbers are finally erased, and the one who cannot play in his(her) turn loses the game.

Here's the problem: Who will win the game if both use the best strategy? Find it out quickly, before they get bored of the game again!

## 输入格式

The first line contains an integer **T** (1 ≤ **T** ≤ 4000), indicating the number of test cases. Each test case contains several lines. The first line contains an integer **N** (1 ≤ **N** ≤ 50). The next line contains **N** positive integers **A $ _{1} $** ... **A $ _{N} $**  (1 ≤ **A $ _{i} $**  ≤ 1000), represents the numbers they write down at the beginning of the game.

## 输出格式

For each test case in the input, print one line: "Case #X: Y", where **X** is the test case number (starting with 1) and **Y** is either "Alice" or "Bob".

## 样例 #1

### 输入

```
3
3
1 1 2
2
3 4
3
2 3 5
```

### 输出

```
Case #1: Alice
Case #2: Bob
Case #3: Bob
```

