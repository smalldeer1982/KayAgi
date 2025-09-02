---
title: "Set of Strangers"
layout: "post"
diff: 难度0
pid: CF2069B
tag: []
---

# Set of Strangers

## 题目描述

You are given a table of $ n $ rows and $ m $ columns. Initially, the cell at the $ i $ -th row and the $ j $ -th column has color $ a_{i, j} $ .

Let's say that two cells are strangers if they don't share a side. Strangers are allowed to touch with corners.

Let's say that the set of cells is a set of strangers if all pairs of cells in the set are strangers. Sets with no more than one cell are sets of strangers by definition.

In one step, you can choose any set of strangers such that all cells in it have the same color and paint all of them in some other color. You can choose the resulting color.

What is the minimum number of steps you need to make the whole table the same color?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Next, $ t $ cases follow.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n \le m \le 700 $ ) — the number of rows and columns in the table.

The next $ n $ lines contain the colors of cells in the corresponding row $ a_{i, 1}, \dots, a_{i, m} $ ( $ 1 \le a_{i, j} \le nm $ ).

It's guaranteed that the total sum of $ nm $ doesn't exceed $ 5 \cdot 10^5 $ over all test cases.

## 输出格式

For each test case, print one integer — the minimum number of steps to paint all cells of the table the same color.

## 说明/提示

In the first test case, the table is painted in one color from the start.

In the second test case, you can, for example, choose all cells with color $ 1 $ and paint them in $ 3 $ . Then choose all cells with color $ 2 $ and also paint them in $ 3 $ .

In the third test case, you can choose all cells with color $ 5 $ and paint them in color $ 4 $ .

## 样例 #1

### 输入

```
4
1 1
1
3 3
1 2 1
2 3 2
1 3 1
1 6
5 4 5 4 4 5
3 4
1 4 2 2
1 4 3 5
6 6 3 5
```

### 输出

```
0
2
1
10
```

