---
title: "Square Tiling"
layout: "post"
diff: 提高+/省选-
pid: CF432E
tag: []
---

# Square Tiling

## 题目描述

You have an $ n×m $ rectangle table, its cells are not initially painted. Your task is to paint all cells of the table. The resulting picture should be a tiling of the table with squares. More formally:

- each cell must be painted some color (the colors are marked by uppercase Latin letters);
- we will assume that two cells of the table are connected if they are of the same color and share a side; each connected region of the table must form a square.

Given $ n $ and $ m $ , find lexicographically minimum coloring of the table that meets the described properties.

## 输入格式

The first line contains two integers, $ n $ and $ m $ $ (1<=n,m<=100) $ .

## 输出格式

Print lexicographically minimum coloring of the table that meets the described conditions.

One coloring (let's call it X) is considered lexicographically less than the other one (let's call it Y), if:

- consider all the table cells from left to right and from top to bottom (first, the first cell in the first row, then the second cell in the first row and so on);
- let's find in this order the first cell that has distinct colors in two colorings;
- the letter that marks the color of the cell in X, goes alphabetically before the letter that marks the color of the cell in Y.

## 样例 #1

### 输入

```
1 3

```

### 输出

```
ABA

```

## 样例 #2

### 输入

```
2 2

```

### 输出

```
AA
AA

```

## 样例 #3

### 输入

```
3 4

```

### 输出

```
AAAB
AAAC
AAAB

```

