---
title: "Rectangular Game"
layout: "post"
diff: 普及-
pid: CF177B1
tag: []
---

# Rectangular Game

## 题目描述

The Smart Beaver from ABBYY decided to have a day off. But doing nothing the whole day turned out to be too boring, and he decided to play a game with pebbles. Initially, the Beaver has $ n $ pebbles. He arranges them in $ a $ equal rows, each row has $ b $ pebbles ( $ a>1 $ ). Note that the Beaver must use all the pebbles he has, i. e. $ n=a·b $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF177B1/72b3400d0a6aa691e5c49fe273a750815ff16b58.png) 10 pebbles are arranged in two rows, each row has 5 pebbles Once the Smart Beaver has arranged the pebbles, he takes back any of the resulting rows (that is, $ b $ pebbles) and discards all other pebbles. Then he arranges all his pebbles again (possibly choosing other values of $ a $ and $ b $ ) and takes back one row, and so on. The game continues until at some point the Beaver ends up with exactly one pebble.

The game process can be represented as a finite sequence of integers $ c_{1},...,c_{k} $ , where:

- $ c_{1}=n $
- $ c_{i+1} $ is the number of pebbles that the Beaver ends up with after the $ i $ -th move, that is, the number of pebbles in a row after some arrangement of $ c_{i} $ pebbles ( $ 1<=i<k $ ). Note that $ c_{i}>c_{i+1} $ .
- $ c_{k}=1 $

The result of the game is the sum of numbers $ c_{i} $ . You are given $ n $ . Find the maximum possible result of the game.

## 输入格式

The single line of the input contains a single integer $ n $ — the initial number of pebbles the Smart Beaver has.

The input limitations for getting 30 points are:

- $ 2<=n<=50 $

The input limitations for getting 100 points are:

- $ 2<=n<=10^{9} $

## 输出格式

Print a single number — the maximum possible result of the game.

## 说明/提示

Consider the first example ( $ c_{1}=10 $ ). The possible options for the game development are:

- Arrange the pebbles in 10 rows, one pebble per row. Then $ c_{2}=1 $ , and the game ends after the first move with the result of 11.
- Arrange the pebbles in 5 rows, two pebbles per row. Then $ c_{2}=2 $ , and the game continues. During the second move we have two pebbles which can be arranged in a unique way (remember that you are not allowed to put all the pebbles in the same row!) — 2 rows, one pebble per row. $ c_{3}=1 $ , and the game ends with the result of 13.
- Finally, arrange the pebbles in two rows, five pebbles per row. The same logic leads us to $ c_{2}=5,c_{3}=1 $ , and the game ends with the result of 16 — the maximum possible result.

## 样例 #1

### 输入

```
10

```

### 输出

```
16

```

## 样例 #2

### 输入

```
8

```

### 输出

```
15

```

