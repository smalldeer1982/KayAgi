---
title: "Weird Game"
layout: "post"
diff: 普及+/提高
pid: CF293A
tag: []
---

# Weird Game

## 题目描述

Yaroslav, Andrey and Roman can play cubes for hours and hours. But the game is for three, so when Roman doesn't show up, Yaroslav and Andrey play another game.

Roman leaves a word for each of them. Each word consists of $ 2·n $ binary characters "0" or "1". After that the players start moving in turns. Yaroslav moves first. During a move, a player must choose an integer from 1 to $ 2·n $ , which hasn't been chosen by anybody up to that moment. Then the player takes a piece of paper and writes out the corresponding character from his string.

Let's represent Yaroslav's word as $ s=s_{1}s_{2}...\ s_{2n} $ . Similarly, let's represent Andrey's word as $ t=t_{1}t_{2}...\ t_{2n} $ . Then, if Yaroslav choose number $ k $ during his move, then he is going to write out character $ s_{k} $ on the piece of paper. Similarly, if Andrey choose number $ r $ during his move, then he is going to write out character $ t_{r} $ on the piece of paper.

The game finishes when no player can make a move. After the game is over, Yaroslav makes some integer from the characters written on his piece of paper (Yaroslav can arrange these characters as he wants). Andrey does the same. The resulting numbers can contain leading zeroes. The person with the largest number wins. If the numbers are equal, the game ends with a draw.

You are given two strings $ s $ and $ t $ . Determine the outcome of the game provided that Yaroslav and Andrey play optimally well.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{6} $ ). The second line contains string $ s $ — Yaroslav's word. The third line contains string $ t $ — Andrey's word.

It is guaranteed that both words consist of $ 2·n $ characters "0" and "1".

## 输出格式

Print "First", if both players play optimally well and Yaroslav wins. If Andrey wins, print "Second" and if the game ends with a draw, print "Draw". Print the words without the quotes.

## 样例 #1

### 输入

```
2
0111
0001

```

### 输出

```
First

```

## 样例 #2

### 输入

```
3
110110
001001

```

### 输出

```
First

```

## 样例 #3

### 输入

```
3
111000
000111

```

### 输出

```
Draw

```

## 样例 #4

### 输入

```
4
01010110
00101101

```

### 输出

```
First

```

## 样例 #5

### 输入

```
4
01100000
10010011

```

### 输出

```
Second

```

