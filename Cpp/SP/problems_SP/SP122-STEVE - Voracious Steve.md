---
title: "STEVE - Voracious Steve"
layout: "post"
diff: 普及+/提高
pid: SP122
tag: []
---

# STEVE - Voracious Steve

## 题目描述

 Steve and Digit bought a box containing a number of donuts. In order to divide them between themselves they play a special game that they created. The players alternately take a certain, positive number of donuts from the box, but no more than some fixed integer. Each player's donuts are gathered on the player's side. The player that empties the box eats his donuts while the other one puts his donuts back into the box and the game continues with the "loser" player starting. The game goes on until all the donuts are eaten. The goal of the game is to eat the most donuts. How many donuts can Steve, who starts the game, count on, assuming the best strategy for both players?

   
### Task

Write a program that:

- reads the parameters of the game from the standard input,
- computes the number of donuts Steve can count on,
- writes the result to the standard output.

## 输入格式

 The input begins with the integer t, the number of test cases. Then t test cases follow.

 For each test case the first and only line of the input contains exactly two integers n and m separated by a single space, 1 <= m <= n <= 100 - the parameters of the game, where n is the number of donuts in the box at the beginning of the game and m is the upper limit on the number of donuts to be taken by one player in one move.

## 输出格式

 For each test case the output contains exactly one integer equal to the number of donuts Steve can count on.

## 样例 #1

### 输入

```
1
5 2
```

### 输出

```
3
```

