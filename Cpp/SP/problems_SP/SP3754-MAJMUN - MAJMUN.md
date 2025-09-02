---
title: "MAJMUN - MAJMUN"
layout: "post"
diff: 难度0
pid: SP3754
tag: []
---

# MAJMUN - MAJMUN

## 题目描述

 [English](/problems/MAJMUN/en/) [Vietnamese](/problems/MAJMUN/vn/)Coming home after a hard day at school, Ivica is ready to relax playing the computer game "Monkey &banana". In the game, the monkey is located in a jungle, modeled as a coordinate plane.Every point with integer coordinates represents a tree. The monkey is initially located at tree (XM ,YM ) facing up i.e.towards the tree (XM ,YM +1).The monkey is controlled with the keys 0 to 7.When the key K is pressed,the monkey turns 45 degrees left K times and then jumps to the first tree he sees in his new direction.

The game lasts until the monkey jumps exactly N times.After that,the score is calculated from the distance between the monkey and the banana tree,which is located at coordinates (XB ,YB ).The lower the distance,the bigger the score. Ivica played one game and is now interested if he could have done better changing at most one key press. Write a program that determines the smallest possible ending (Euclidean) distance between the monkey and the banana tree (it is possible that the current score cannot be improved).

## 输入格式

The first line of input contains our integers XM ,YM ,XB and YB (0 XM ,YM ,XB ,YB 1 000 000),the initial coordinates of the monkey and the coordinates o the banana tree. The next line contains the integer N (1

The last line contains a string o N digits between 0 and 7,the keys that Ivica pressed.

## 输出格式

Output a single decimal number,the smallest achievable distance.Your output must be accurate to ±0.01.

## 样例 #1

### 输入

```
0 0 2 3
5
15102
```

### 输出

```
0.000000
```

