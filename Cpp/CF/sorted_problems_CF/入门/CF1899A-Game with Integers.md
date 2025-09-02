---
title: "Game with Integers"
layout: "post"
diff: 入门
pid: CF1899A
tag: []
---

# Game with Integers

## 题目描述

Vanya and Vova are playing a game. Players are given an integer $ n $ . On their turn, the player can add $ 1 $ to the current integer or subtract $ 1 $ . The players take turns; Vanya starts. If after Vanya's move the integer is divisible by $ 3 $ , then he wins. If $ 10 $ moves have passed and Vanya has not won, then Vova wins.

Write a program that, based on the integer $ n $ , determines who will win if both players play optimally.

## 输入格式

The first line contains the integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

The single line of each test case contains the integer $ n $ ( $ 1 \leq n \leq 1000 $ ).

## 输出格式

For each test case, print "First" without quotes if Vanya wins, and "Second" without quotes if Vova wins.

## 样例 #1

### 输入

```
6
1
3
5
100
999
1000
```

### 输出

```
First
Second
First
First
Second
First
```

