---
title: "Solitaire"
layout: "post"
diff: 提高+/省选-
pid: CF71D
tag: []
---

# Solitaire

## 题目描述

Vasya 手里有一副 54 张扑克牌。为了消遣，Vasya 开始玩纸牌游戏。

Vasya 将 $nm$ 张牌摆成一个 $n\times m$ 的矩形。如果其中有大小王，Vasya 会从剩下的 $54 - nm$ 张扑克牌中任意选牌将它们换下。Vasya 在换牌时会尽量使得纸牌游戏能被解决。

Vasya 认为：一轮纸牌游戏能被解决，当且仅当大小王被换下后，存在两个不重叠的 $3\times 3$ 正方形，每个正方形中的扑克牌**花色一致**或**点数互不相同**。

请你求出给定的纸牌游戏能否被解决。如果有解，给出任意一组解即可。

## 输入格式

第一行包含两个整数 $n,m\ (3\leq n,m\leq 17,n\times m\leq 52)$，表示矩形的大小。其中 $n$ 表示矩形的行数，$m$ 表示矩形的列数。

接下来 $n$ 行，每行 $m$ 个字符串。每个字符串包含两个字符。大小王表示为 `J1` 和 `J2`。剩下的扑克牌中，第一个字符表示点数，第二个字符表示花色。点数包含：`2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K` 和 `A`。花色包含：`C, D, H` 和 `S`。数据保证所有的牌互不相同。

## 输出格式

如果无解，输出 `No solution.`

否则输出共 $4$ 行。

第一行输出 `Solution exists.`

第二行输出大小王的替换情况，有三种可能：
- 如果没有大小王，输出 `There are no jokers.`
- 如果有一张王牌，输出 `Replace Jx with y.` $x$ 为王牌的标号，$y$ 为换上的扑克牌。
- 如果有两张王牌，输出 `Replace J1 with x and J2 with y.` $x$ 为换下 `J1` 的扑克牌，$y$ 为换下 `J2` 的扑克牌。

第三行输出第一个正方形的左上角 $(x_{1},y_{1})$，格式为：`Put the first square to (x1, y1).`

第四行输出第二个正方形的左上角 $(x_{2},y_{2})$，格式为：`Put the second square to (x2, y2).`

## 样例 #1

### 输入

```
4 6
2S 3S 4S 7S 8S AS
5H 6H 7H 5S TC AC
8H 9H TH 7C 8C 9C
2D 2C 3C 4C 5C 6C

```

### 输出

```
No solution.
```

## 样例 #2

### 输入

```
4 6
2S 3S 4S 7S 8S AS
5H 6H 7H J1 TC AC
8H 9H TH 7C 8C 9C
2D 2C 3C 4C 5C 6C

```

### 输出

```
Solution exists.
Replace J1 with 2H.
Put the first square to (1, 1).
Put the second square to (2, 4).

```

## 样例 #3

### 输入

```
4 6
2S 3S 4S 7S 8S AS
5H 6H 7H QC TC AC
8H 9H TH 7C 8C 9C
2D 2C 3C 4C 5C 6C

```

### 输出

```
Solution exists.
There are no jokers.
Put the first square to (1, 1).
Put the second square to (2, 4).

```

