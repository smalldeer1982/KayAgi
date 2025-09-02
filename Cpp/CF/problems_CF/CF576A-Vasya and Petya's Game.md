---
title: "Vasya and Petya's Game"
layout: "post"
diff: 普及/提高-
pid: CF576A
tag: []
---

# Vasya and Petya's Game

## 题目描述

Vasya and Petya are playing a simple game. Vasya thought of number $ x $ between $ 1 $ and $ n $ , and Petya tries to guess the number.

Petya can ask questions like: "Is the unknown number divisible by number $ y $ ?".

The game is played by the following rules: first Petya asks all the questions that interest him (also, he can ask no questions), and then Vasya responds to each question with a 'yes' or a 'no'. After receiving all the answers Petya should determine the number that Vasya thought of.

Unfortunately, Petya is not familiar with the number theory. Help him find the minimum number of questions he should ask to make a guaranteed guess of Vasya's number, and the numbers $ y_{i} $ , he should ask the questions about.

## 输入格式

A single line contains number $ n $ ( $ 1<=n<=10^{3} $ ).

## 输出格式

Print the length of the sequence of questions $ k $ ( $ 0<=k<=n $ ), followed by $ k $ numbers — the questions $ y_{i} $ ( $ 1<=y_{i}<=n $ ).

If there are several correct sequences of questions of the minimum length, you are allowed to print any of them.

## 说明/提示

The sequence from the answer to the first sample test is actually correct.

If the unknown number is not divisible by one of the sequence numbers, it is equal to $ 1 $ .

If the unknown number is divisible by $ 4 $ , it is $ 4 $ .

If the unknown number is divisible by $ 3 $ , then the unknown number is $ 3 $ .

Otherwise, it is equal to $ 2 $ . Therefore, the sequence of questions allows you to guess the unknown number. It can be shown that there is no correct sequence of questions of length 2 or shorter.

## 样例 #1

### 输入

```
4

```

### 输出

```
3
2 4 3 

```

## 样例 #2

### 输入

```
6

```

### 输出

```
4
2 4 3 5 

```

