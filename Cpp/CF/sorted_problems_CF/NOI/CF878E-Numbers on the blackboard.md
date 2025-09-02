---
title: "Numbers on the blackboard"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF878E
tag: []
---

# Numbers on the blackboard

## 题目描述

A sequence of $ n $ integers is written on a blackboard. Soon Sasha will come to the blackboard and start the following actions: let $ x $ and $ y $ be two adjacent numbers ( $ x $ before $ y $ ), then he can remove them and write $ x+2y $ instead of them. He will perform these operations until one number is left. Sasha likes big numbers and will get the biggest possible number.

Nikita wants to get to the blackboard before Sasha and erase some of the numbers. He has $ q $ options, in the option $ i $ he erases all numbers to the left of the $ l_{i} $ -th number and all numbers to the right of $ r_{i} $ -th number, i. e. all numbers between the $ l_{i} $ -th and the $ r_{i} $ -th, inclusive, remain on the blackboard. For each of the options he wants to know how big Sasha's final number is going to be. This number can be very big, so output it modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1<=n,q<=10^{5} $ ) — the number of integers on the blackboard and the number of Nikita's options.

The next line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ -10^{9}<=a_{i}<=10^{9} $ ) — the sequence on the blackboard.

Each of the next $ q $ lines contains two integers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ), describing Nikita's options.

## 输出格式

For each option output Sasha's result modulo $ 10^{9}+7 $ .

## 说明/提示

In the second sample Nikita doesn't erase anything. Sasha first erases the numbers $ 1 $ and $ 2 $ and writes $ 5 $ . Then he erases $ 5 $ and -3 and gets -1. -1 modulo $ 10^{9}+7 $ is $ 10^{9}+6 $ .

## 样例 #1

### 输入

```
3 3
1 2 3
1 3
1 2
2 3

```

### 输出

```
17
5
8

```

## 样例 #2

### 输入

```
3 1
1 2 -3
1 3

```

### 输出

```
1000000006

```

## 样例 #3

### 输入

```
4 2
1 1 1 -1
1 4
3 4

```

### 输出

```
5
1000000006

```

