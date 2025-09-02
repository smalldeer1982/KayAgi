---
title: "The Lakes"
layout: "post"
diff: 普及-
pid: CF1829E
tag: []
---

# The Lakes

## 题目描述

You are given an $ n \times m $ grid $ a $ of non-negative integers. The value $ a_{i,j} $ represents the depth of water at the $ i $ -th row and $ j $ -th column.

A lake is a set of cells such that:

- each cell in the set has $ a_{i,j} > 0 $ , and
- there exists a path between any pair of cells in the lake by going up, down, left, or right a number of times and without stepping on a cell with $ a_{i,j} = 0 $ .

The volume of a lake is the sum of depths of all the cells in the lake.

Find the largest volume of a lake in the grid.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n, m $ ( $ 1 \leq n, m \leq 1000 $ ) — the number of rows and columns of the grid, respectively.

Then $ n $ lines follow each with $ m $ integers $ a_{i,j} $ ( $ 0 \leq a_{i,j} \leq 1000 $ ) — the depth of the water at each cell.

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output a single integer — the largest volume of a lake in the grid.

## 样例 #1

### 输入

```
5
3 3
1 2 0
3 4 0
0 0 5
1 1
0
3 3
0 1 1
1 0 1
1 1 1
5 5
1 1 1 1 1
1 0 0 0 1
1 0 5 0 1
1 0 0 0 1
1 1 1 1 1
5 5
1 1 1 1 1
1 0 0 0 1
1 1 4 0 1
1 0 0 0 1
1 1 1 1 1
```

### 输出

```
10
0
7
16
21
```

