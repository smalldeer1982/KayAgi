---
title: "Rudolph and Tic-Tac-Toe"
layout: "post"
diff: 入门
pid: CF1846B
tag: []
---

# Rudolph and Tic-Tac-Toe

## 题目描述

Rudolph invented the game of tic-tac-toe for three players. It has classic rules, except for the third player who plays with pluses. Rudolf has a $ 3 \times 3 $ field — the result of the completed game. Each field cell contains either a cross, or a nought, or a plus sign, or nothing. The game is won by the player who makes a horizontal, vertical or diagonal row of $ 3 $ 's of their symbols.

Rudolph wants to find the result of the game. Either exactly one of the three players won or it ended in a draw. It is guaranteed that multiple players cannot win at the same time.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of three lines, each of which consists of three characters. The symbol can be one of four: "X" means a cross, "O" means a nought, "+" means a plus, "." means an empty cell.

## 输出格式

For each test case, print the string "X" if the crosses won, "O" if the noughts won, "+" if the pluses won, "DRAW" if there was a draw.

## 样例 #1

### 输入

```
5
+X+
OXO
OX.
O+.
+OX
X+O
.XO
OX.
+++
O.+
X.O
+..
.++
X.O
+..
```

### 输出

```
X
O
+
DRAW
DRAW
```

