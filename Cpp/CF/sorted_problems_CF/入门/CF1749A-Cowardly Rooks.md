---
title: "Cowardly Rooks"
layout: "post"
diff: 入门
pid: CF1749A
tag: []
---

# Cowardly Rooks

## 题目描述

There's a chessboard of size $ n \times n $ . $ m $ rooks are placed on it in such a way that:

- no two rooks occupy the same cell;
- no two rooks attack each other.

A rook attacks all cells that are in its row or column.

Is it possible to move exactly one rook (you can choose which one to move) into a different cell so that no two rooks still attack each other? A rook can move into any cell in its row or column if no other rook stands on its path.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 2000 $ ) — the number of testcases.

The first line of each testcase contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 8 $ ) — the size of the chessboard and the number of the rooks.

The $ i $ -th of the next $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le n $ ) — the position of the $ i $ -th rook: $ x_i $ is the row and $ y_i $ is the column.

No two rooks occupy the same cell. No two rooks attack each other.

## 输出格式

For each testcase, print "YES" if it's possible to move exactly one rook into a different cell so that no two rooks still attack each other. Otherwise, print "NO".

## 说明/提示

In the first testcase, the rooks are in the opposite corners of a $ 2 \times 2 $ board. Each of them has a move into a neighbouring corner, but moving there means getting attacked by another rook.

In the second testcase, there's a single rook in a middle of a $ 3 \times 3 $ board. It has $ 4 $ valid moves, and every move is fine because there's no other rook to attack it.

## 样例 #1

### 输入

```
2
2 2
1 2
2 1
3 1
2 2
```

### 输出

```
NO
YES
```

