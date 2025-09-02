---
title: "New Year and Buggy Bot"
layout: "post"
diff: 普及/提高-
pid: CF908B
tag: []
---

# New Year and Buggy Bot

## 题目描述

Bob programmed a robot to navigate through a 2d maze.

The maze has some obstacles. Empty cells are denoted by the character '.', where obstacles are denoted by '\#'.

There is a single robot in the maze. Its start position is denoted with the character 'S'. This position has no obstacle in it. There is also a single exit in the maze. Its position is denoted with the character 'E'. This position has no obstacle in it.

The robot can only move up, left, right, or down.

When Bob programmed the robot, he wrote down a string of digits consisting of the digits 0 to 3, inclusive. He intended for each digit to correspond to a distinct direction, and the robot would follow the directions in order to reach the exit. Unfortunately, he forgot to actually assign the directions to digits.

The robot will choose some random mapping of digits to distinct directions. The robot will map distinct digits to distinct directions. The robot will then follow the instructions according to the given string in order and chosen mapping. If an instruction would lead the robot to go off the edge of the maze or hit an obstacle, the robot will crash and break down. If the robot reaches the exit at any point, then the robot will stop following any further instructions.

Bob is having trouble debugging his robot, so he would like to determine the number of mappings of digits to directions that would lead the robot to the exit.

## 输入格式

The first line of input will contain two integers $ n $ and $ m $ ( $ 2<=n,m<=50 $ ), denoting the dimensions of the maze.

The next $ n $ lines will contain exactly $ m $ characters each, denoting the maze.

Each character of the maze will be '.', '\#', 'S', or 'E'.

There will be exactly one 'S' and exactly one 'E' in the maze.

The last line will contain a single string $ s $ ( $ 1<=|s|<=100 $ ) — the instructions given to the robot. Each character of $ s $ is a digit from 0 to 3.

## 输出格式

Print a single integer, the number of mappings of digits to directions that will lead the robot to the exit.

## 说明/提示

For the first sample, the only valid mapping is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908B/4c40549367cb1d718a2322ebe6b5a9600149483b.png), where $ D $ is down, $ L $ is left, $ U $ is up, $ R $ is right.

## 样例 #1

### 输入

```
5 6
.....#
S....#
.#....
.#....
...E..
333300012

```

### 输出

```
1

```

## 样例 #2

### 输入

```
6 6
......
......
..SE..
......
......
......
01232123212302123021

```

### 输出

```
14

```

## 样例 #3

### 输入

```
5 3
...
.S.
###
.E.
...
3

```

### 输出

```
0

```

