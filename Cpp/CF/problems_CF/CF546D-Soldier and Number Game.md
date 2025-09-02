---
title: "Soldier and Number Game"
layout: "post"
diff: 普及+/提高
pid: CF546D
tag: []
---

# Soldier and Number Game

## 题目描述

Two soldiers are playing a game. At the beginning first of them chooses a positive integer $ n $ and gives it to the second soldier. Then the second one tries to make maximum possible number of rounds. Each round consists of choosing a positive integer $ x&gt;1 $ , such that $ n $ is divisible by $ x $ and replacing $ n $ with $ n/x $ . When $ n $ becomes equal to $ 1 $ and there is no more possible valid moves the game is over and the score of the second soldier is equal to the number of rounds he performed.

To make the game more interesting, first soldier chooses $ n $ of form $ a!/b! $ for some positive integer $ a $ and $ b $ ( $ a>=b $ ). Here by $ k! $ we denote the factorial of $ k $ that is defined as a product of all positive integers not large than $ k $ .

What is the maximum possible score of the second soldier?

## 输入格式

First line of input consists of single integer $ t $ ( $ 1<=t<=1000000 $ ) denoting number of games soldiers play.

Then follow $ t $ lines, each contains pair of integers $ a $ and $ b $ ( $ 1<=b<=a<=5000000 $ ) defining the value of $ n $ for a game.

## 输出格式

For each game output a maximum score that the second soldier can get.

## 样例 #1

### 输入

```
2
3 1
6 3

```

### 输出

```
2
5

```

