---
title: "Gargari and Bishops"
layout: "post"
diff: 普及+/提高
pid: CF463C
tag: []
---

# Gargari and Bishops

## 题目描述

Gargari is jealous that his friend Caisa won the game from the previous problem. He wants to prove that he is a genius.

He has a $ n×n $ chessboard. Each cell of the chessboard has a number written on it. Gargari wants to place two bishops on the chessboard in such a way that there is no cell that is attacked by both of them. Consider a cell with number $ x $ written on it, if this cell is attacked by one of the bishops Gargari will get $ x $ dollars for it. Tell Gargari, how to place bishops on the chessboard to get maximum amount of money.

We assume a cell is attacked by a bishop, if the cell is located on the same diagonal with the bishop (the cell, where the bishop is, also considered attacked by it).

## 输入格式

The first line contains a single integer $ n $ $ (2<=n<=2000) $ . Each of the next $ n $ lines contains $ n $ integers $ a_{ij} $ $ (0<=a_{ij}<=10^{9}) $ — description of the chessboard.

## 输出格式

On the first line print the maximal number of dollars Gargari will get. On the next line print four integers: $ x_{1},y_{1},x_{2},y_{2} $ $ (1<=x_{1},y_{1},x_{2},y_{2}<=n) $ , where $ x_{i} $ is the number of the row where the $ i $ -th bishop should be placed, $ y_{i} $ is the number of the column where the $ i $ -th bishop should be placed. Consider rows are numbered from 1 to $ n $ from top to bottom, and columns are numbered from 1 to $ n $ from left to right.

If there are several optimal solutions, you can print any of them.

## 样例 #1

### 输入

```
4
1 1 1 1
2 1 1 0
1 1 1 0
1 0 0 1

```

### 输出

```
12
2 2 3 2

```

