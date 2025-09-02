---
title: "Vanya and Table"
layout: "post"
diff: 普及-
pid: CF552A
tag: []
---

# Vanya and Table

## 题目描述

Vanya has a table consisting of $ 100 $ rows, each row contains $ 100 $ cells. The rows are numbered by integers from $ 1 $ to $ 100 $ from bottom to top, the columns are numbered from $ 1 $ to $ 100 $ from left to right.

In this table, Vanya chose $ n $ rectangles with sides that go along borders of squares (some rectangles probably occur multiple times). After that for each cell of the table he counted the number of rectangles it belongs to and wrote this number into it. Now he wants to find the sum of values in all cells of the table and as the table is too large, he asks you to help him find the result.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=100 $ ) — the number of rectangles.

Each of the following $ n $ lines contains four integers $ x_{1},y_{1},x_{2},y_{2} $ ( $ 1<=x_{1}<=x_{2}<=100 $ , $ 1<=y_{1}<=y_{2}<=100) $ , where $ x_{1} $ and $ y_{1} $ are the number of the column and row of the lower left cell and $ x_{2} $ and $ y_{2} $ are the number of the column and row of the upper right cell of a rectangle.

## 输出格式

In a single line print the sum of all values in the cells of the table.

## 说明/提示

Note to the first sample test:

Values of the table in the first three rows and columns will be as follows:

 $ 121 $

 $ 121 $

 $ 110 $

So, the sum of values will be equal to $ 10 $ .

Note to the second sample test:

Values of the table in the first three rows and columns will be as follows:

 $ 222 $

 $ 222 $

 $ 222 $

So, the sum of values will be equal to $ 18 $ .

## 样例 #1

### 输入

```
2
1 1 2 3
2 2 3 3

```

### 输出

```
10

```

## 样例 #2

### 输入

```
2
1 1 3 3
1 1 3 3

```

### 输出

```
18

```

