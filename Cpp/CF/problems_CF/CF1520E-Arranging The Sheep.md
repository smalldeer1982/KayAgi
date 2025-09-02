---
title: "Arranging The Sheep"
layout: "post"
diff: 普及-
pid: CF1520E
tag: []
---

# Arranging The Sheep

## 题目描述

You are playing the game "Arranging The Sheep". The goal of this game is to make the sheep line up. The level in the game is described by a string of length $ n $ , consisting of the characters '.' (empty space) and '\*' (sheep). In one move, you can move any sheep one square to the left or one square to the right, if the corresponding square exists and is empty. The game ends as soon as the sheep are lined up, that is, there should be no empty cells between any sheep.

For example, if $ n=6 $ and the level is described by the string "\*\*.\*..", then the following game scenario is possible:

- the sheep at the $ 4 $ position moves to the right, the state of the level: "\*\*..\*.";
- the sheep at the $ 2 $ position moves to the right, the state of the level: "\*.\*.\*.";
- the sheep at the $ 1 $ position moves to the right, the state of the level: ".\*\*.\*.";
- the sheep at the $ 3 $ position moves to the right, the state of the level: ".\*.\*\*.";
- the sheep at the $ 2 $ position moves to the right, the state of the level: "..\*\*\*.";
- the sheep are lined up and the game ends.

For a given level, determine the minimum number of moves you need to make to complete the level.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ). Then $ t $ test cases follow.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 10^6 $ ).

The second line of each test case contains a string of length $ n $ , consisting of the characters '.' (empty space) and '\*' (sheep) — the description of the level.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case output the minimum number of moves you need to make to complete the level.

## 样例 #1

### 输入

```
5
6
**.*..
5
*****
3
.*.
3
...
10
*.*...*.**
```

### 输出

```
1
0
0
0
9
```

