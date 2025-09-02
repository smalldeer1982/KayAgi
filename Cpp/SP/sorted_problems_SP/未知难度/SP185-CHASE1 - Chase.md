---
title: "CHASE1 - Chase"
layout: "post"
diff: 难度0
pid: SP185
tag: []
---

# CHASE1 - Chase

## 题目描述

追逐游戏是一个双人游戏，假设有玩家 A 和 B。一个棋盘包含由 1 到 n 编号的格子。对于一对编号不同的格子，会给定它们之间是否相连。每个玩家控制一个棋子。开始的时候，每个玩家的棋子会放在某个特定的不同的格子。在一回合中，玩家可以移开它的棋子，移到一个相邻的格子。

一个棋盘有下面属性：

- 不存在三角形连接的格子；

- 每个格子都可以被走到。

一次游戏由若干回合组成。在每个回合，每个玩家只能动一步。每回合 A 先开始动。

当两个棋子站在一起的时候，我们说 A 被 B 吃掉了。给定棋子的初始位置，假定 AB 都选用最佳决策，判断 B 是否必胜。如果是的话，需要多少回合。

## 输入格式

第一行包含四个整数 $n,m,a,b$，分别表示格子数量、相邻格子对数量，A 的初始位置，B 的初始位置。

接下来 $m$ 行，每行包含两个整数 $u,v$，表示格子 $u$ 和格子 $v$ 是相邻的。

## 输出格式

对于每个测试用例，您应该输出一行，其中包含：

一个 "No"（不含引号），如果玩家 B 无法抓住玩家 A，或者一个整数 ，表示 B 抓住 A 所需的回合数（如果 B 可以抓住 A）。

## 样例 #1

### 输入

```
The number of test cases t is in the first line of input, then t test cases follow separated by an empty line.
In the first line of a test case there are four integers n, m, a and b separated by single spaces, where 2
```

### 输出

```
s the result.
```

## 样例 #2

### 输入

```
1
9 11 9 4
1 2
3 2
1 4
4 7
7 5
5 1
6 9
8 5
9 8
5 3
4 8
```

### 输出

```
3
```

