---
title: "Playing with String"
layout: "post"
diff: 提高+/省选-
pid: CF305E
tag: []
---

# Playing with String

## 题目描述

Two people play the following string game. Initially the players have got some string $ s $ . The players move in turns, the player who cannot make a move loses.

Before the game began, the string is written on a piece of paper, one letter per cell.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305E/e3dc20c8c09e1180ec4786b230762f8e7c79cfda.png)An example of the initial situation at $ s $ = "abacaba"A player's move is the sequence of actions:

1. The player chooses one of the available pieces of paper with some string written on it. Let's denote it is $ t $ . Note that initially, only one piece of paper is available.
2. The player chooses in the string $ t=t_{1}t_{2}...\ t_{|t|} $ character in position $ i $ $ (1<=i<=|t|) $ such that for some positive integer $ l $ $ (0&lt;i-l; i+l<=|t|) $ the following equations hold: $ t_{i-1}=t_{i+1} $ , $ t_{i-2}=t_{i+2} $ , ..., $ t_{i-l}=t_{i+l} $ .
3. Player cuts the cell with the chosen character. As a result of the operation, he gets three new pieces of paper, the first one will contain string $ t_{1}t_{2}...\ t_{i-1} $ , the second one will contain a string consisting of a single character $ t_{i} $ , the third one contains string $ t_{i+1}t_{i+2}...\ t_{|t|} $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305E/4da2b2c4651d8ec70c1d3e569c51588926a9324c.png)An example of making action $ (i=4) $ with string $ s $ = «abacaba»Your task is to determine the winner provided that both players play optimally well. If the first player wins, find the position of character that is optimal to cut in his first move. If there are multiple positions, print the minimal possible one.

## 输入格式

The first line contains string $ s $ ( $ 1<=|s|<=5000 $ ). It is guaranteed that string $ s $ only contains lowercase English letters.

## 输出格式

If the second player wins, print in the single line "Second" (without the quotes). Otherwise, print in the first line "First" (without the quotes), and in the second line print the minimal possible winning move — integer $ i $ $ (1<=i<=|s|) $ .

## 说明/提示

In the first sample the first player has multiple winning moves. But the minimum one is to cut the character in position $ 2 $ .

In the second sample the first player has no available moves.

## 样例 #1

### 输入

```
abacaba

```

### 输出

```
First
2

```

## 样例 #2

### 输入

```
abcde

```

### 输出

```
Second

```

