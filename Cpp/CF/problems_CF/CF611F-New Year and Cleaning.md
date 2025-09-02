---
title: "New Year and Cleaning"
layout: "post"
diff: 提高+/省选-
pid: CF611F
tag: []
---

# New Year and Cleaning

## 题目描述

Limak is a little polar bear. His parents told him to clean a house before the New Year's Eve. Their house is a rectangular grid with $ h $ rows and $ w $ columns. Each cell is an empty square.

He is a little bear and thus he can't clean a house by himself. Instead, he is going to use a cleaning robot.

A cleaning robot has a built-in pattern of $ n $ moves, defined by a string of the length $ n $ . A single move (character) moves a robot to one of four adjacent cells. Each character is one of the following four: 'U' (up), 'D' (down), 'L' (left), 'R' (right). One move takes one minute.

A cleaning robot must be placed and started in some cell. Then it repeats its pattern of moves till it hits a wall (one of four borders of a house). After hitting a wall it can be placed and used again.

Limak isn't sure if placing a cleaning robot in one cell will be enough. Thus, he is going to start it $ w·h $ times, one time in each cell. Maybe some cells will be cleaned more than once but who cares?

Limak asks you one question. How much time will it take to clean a house? Find and print the number of minutes modulo $ 10^{9}+7 $ . It's also possible that a cleaning robot will never stop — then print "-1" (without the quotes) instead.

Placing and starting a robot takes no time, however, you must count a move when robot hits a wall. Take a look into samples for further clarification.

## 输入格式

The first line contains three integers $ n $ , $ h $ and $ w $ ( $ 1<=n,h,w<=500000 $ ) — the length of the pattern, the number of rows and the number of columns, respectively.

The second line contains a string of length $ n $ — the pattern of $ n $ moves. Each character is one of uppercase letters 'U', 'D', 'L' or 'R'.

## 输出格式

Print one line with the answer.

If a cleaning robot will never stop, print "-1" (without the quotes). Otherwise, print the number of minutes it will take to clean a house modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample house is a grid with $ 10 $ rows and $ 2 $ columns. Starting a robot anywhere in the second column will result in only one move (thus, one minute of cleaning) in which robot will hit a wall — he tried to go right but there is no third column. Starting a robot anywhere in the first column will result in two moves. The total number of minutes is $ 10·1+10·2=30 $ .

In the second sample a started robot will try to move "RULRULRULR..." For example, for the leftmost cell in the second row robot will make $ 5 $ moves before it stops because of hitting an upper wall.

## 样例 #1

### 输入

```
1 10 2
R

```

### 输出

```
30

```

## 样例 #2

### 输入

```
3 4 6
RUL

```

### 输出

```
134

```

## 样例 #3

### 输入

```
4 1 500000
RLRL

```

### 输出

```
-1

```

