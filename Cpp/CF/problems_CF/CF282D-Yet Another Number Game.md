---
title: "Yet Another Number Game"
layout: "post"
diff: 提高+/省选-
pid: CF282D
tag: []
---

# Yet Another Number Game

## 题目描述

Since most contestants do not read this part, I have to repeat that Bitlandians are quite weird. They have their own jobs, their own working method, their own lives, their own sausages and their own games!

Since you are so curious about Bitland, I'll give you the chance of peeking at one of these games.

BitLGM and BitAryo are playing yet another of their crazy-looking genius-needed Bitlandish games. They've got a sequence of $ n $ non-negative integers $ a_{1},a_{2},...,a_{n} $ . The players make moves in turns. BitLGM moves first. Each player can and must do one of the two following actions in his turn:

- Take one of the integers (we'll denote it as $ a_{i} $ ). Choose integer $ x $ $ (1\le x\le a_{i}) $ . And then decrease $ a_{i} $ by $ x $ , that is, apply assignment: $ a_{i}=a_{i}-x $ .
- Choose integer $ x $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF282D/cfd12ee35f4fd2cdcce2f524b91ce3785f31af4d.png). And then decrease all $ a_{i} $ by $ x $ , that is, apply assignment: $ a_{i}=a_{i}-x $ , for all $ i $ .

The player who cannot make a move loses.

You're given the initial sequence $ a_{1},a_{2},...,a_{n} $ . Determine who wins, if both players plays optimally well and if BitLGM and BitAryo start playing the described game in this sequence.

## 输入格式

The first line contains an integer $ n $ ( $ 1\le n\le 3 $ ).

The next line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (0<=a_{i}<300) $ .

## 输出格式

Write the name of the winner (provided that both players play optimally well). Either "BitLGM" or "BitAryo" (without the quotes).

## 样例 #1

### 输入

```
2
1 1

```

### 输出

```
BitLGM

```

## 样例 #2

### 输入

```
2
1 2

```

### 输出

```
BitAryo

```

## 样例 #3

### 输入

```
3
1 2 1

```

### 输出

```
BitLGM

```

