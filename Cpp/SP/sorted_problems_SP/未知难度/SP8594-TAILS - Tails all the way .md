---
title: "TAILS - Tails all the way "
layout: "post"
diff: 难度0
pid: SP8594
tag: []
---

# TAILS - Tails all the way 

## 题目描述

John and James planned to play a game with coins. John has 20 coins and he places it on the table in a random manner(i.e either with heads(1) or tails(0) facing up). John asked james to convert all heads into tails in minimum number of flips with the condition that if a coin is flipped the coins present to the right and left of the chosen coin should also be flipped.

## 输入格式

A single line with 20 space-separated integers

## 输出格式

The minimum number of coin flips necessary to convert all heads into tails (i.e., to 0). For the inputs given, it will always be possible to find some combination of flips that will manipulate the coins to 20 tails.

## 样例 #1

### 输入

```
\n0 0 1 1 1 0 0 1 1 0 1 1 0 0 0 0 0 0 0 0\n\n
```

### 输出

```
3\n\nHint \nExplanation of the sample: \n&nbsp;\nFlip coins 4, 9, and 11 to make them all tails: \n0 0 1 1 1 0 0 1 1 0 1 1 0 0 0 0 0 0 0 0 [initial state] \n0 0 0 0 0 0 0 1 1 0 1 1 0 0 0 0 0 0 0 0 [after flipping coin 4] \n0 0 0 0 0 0 0 0 0 1 1 1 0 0 0 0 0 0 0 0 [after flipping coin 9] \n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 [after flipping coin 11]
```

