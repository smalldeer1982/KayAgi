---
title: "Definite Game"
layout: "post"
diff: 入门
pid: CF1081A
tag: []
---

# Definite Game

## 题目描述

Chouti was doing a competitive programming competition. However, after having all the problems accepted, he got bored and decided to invent some small games.

He came up with the following game. The player has a positive integer $ n $ . Initially the value of $ n $ equals to $ v $ and the player is able to do the following operation as many times as the player want (possibly zero): choose a positive integer $ x $ that $ x<n $ and $ x $ is not a divisor of $ n $ , then subtract $ x $ from $ n $ . The goal of the player is to minimize the value of $ n $ in the end.

Soon, Chouti found the game trivial. Can you also beat the game?

## 输入格式

The input contains only one integer in the first line: $ v $ ( $ 1 \le v \le 10^9 $ ), the initial value of $ n $ .

## 输出格式

Output a single integer, the minimum value of $ n $ the player can get.

## 说明/提示

In the first example, the player can choose $ x=3 $ in the first turn, then $ n $ becomes $ 5 $ . He can then choose $ x=4 $ in the second turn to get $ n=1 $ as the result. There are other ways to get this minimum. However, for example, he cannot choose $ x=2 $ in the first turn because $ 2 $ is a divisor of $ 8 $ .

In the second example, since $ n=1 $ initially, the player can do nothing.

## 样例 #1

### 输入

```
8

```

### 输出

```
1

```

## 样例 #2

### 输入

```
1

```

### 输出

```
1

```

