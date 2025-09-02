---
title: "Immobile Knight"
layout: "post"
diff: 普及-
pid: CF1739A
tag: ['构造']
---

# Immobile Knight

## 题目描述

There is a chess board of size $ n \times m $ . The rows are numbered from $ 1 $ to $ n $ , the columns are numbered from $ 1 $ to $ m $ .

Let's call a cell isolated if a knight placed in that cell can't move to any other cell on the board. Recall that a chess knight moves two cells in one direction and one cell in a perpendicular direction:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1739A/a0d7d8c62ba0d8d73d58490b8d2222f35ced96b2.png)Find any isolated cell on the board. If there are no such cells, print any cell on the board.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 64 $ ) — the number of testcases.

The only line of each testcase contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 8 $ ) — the number of rows and columns of the board.

## 输出格式

For each testcase, print two integers — the row and the column of any isolated cell on the board. If there are no such cells, print any cell on the board.

## 说明/提示

In the first testcase, all cells are isolated. A knight can't move from any cell of the board to any other one. Thus, any cell on board is a correct answer.

In the second testcase, there are no isolated cells. On a normal chess board, a knight has at least two moves from any cell. Thus, again, any cell is a correct answer.

In the third testcase, only the middle cell of the board is isolated. The knight can move freely around the border of the board, but can't escape the middle.

## 样例 #1

### 输入

```
3
1 7
8 8
3 3
```

### 输出

```
1 7
7 2
2 2
```

