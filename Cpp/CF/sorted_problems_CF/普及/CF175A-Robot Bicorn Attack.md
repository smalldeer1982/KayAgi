---
title: "Robot Bicorn Attack"
layout: "post"
diff: 普及/提高-
pid: CF175A
tag: []
---

# Robot Bicorn Attack

## 题目描述

Vasya plays Robot Bicorn Attack.

The game consists of three rounds. For each one a non-negative integer amount of points is given. The result of the game is the sum of obtained points. Vasya has already played three rounds and wrote obtained points one by one (without leading zeros) into the string $ s $ . Vasya decided to brag about his achievement to the friends. However, he has forgotten how many points he got for each round. The only thing he remembers is the string $ s $ .

Help Vasya to find out what is the maximum amount of points he could get. Take into account that Vasya played Robot Bicorn Attack for the first time, so he could not get more than 1000000 ( $ 10^{6} $ ) points for one round.

## 输入格式

The only line of input contains non-empty string $ s $ obtained by Vasya. The string consists of digits only. The string length does not exceed 30 characters.

## 输出格式

Print the only number — the maximum amount of points Vasya could get. If Vasya is wrong and the string could not be obtained according to the rules then output number -1.

## 说明/提示

In the first example the string must be split into numbers 1, 2 and 34.

In the second example the string must be split into numbers 90, 0 and 0.

In the third example the string is incorrect, because after splitting the string into 3 numbers number 00 or 09 will be obtained, but numbers cannot have leading zeroes.

## 样例 #1

### 输入

```
1234

```

### 输出

```
37

```

## 样例 #2

### 输入

```
9000

```

### 输出

```
90

```

## 样例 #3

### 输入

```
0009

```

### 输出

```
-1

```

