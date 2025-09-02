---
title: "Sereja and Table "
layout: "post"
diff: 提高+/省选-
pid: CF425B
tag: []
---

# Sereja and Table 

## 题目描述

Sereja has an $ n×m $ rectangular table $ a $ , each cell of the table contains a zero or a number one. Sereja wants his table to meet the following requirement: each connected component of the same values forms a rectangle with sides parallel to the sides of the table. Rectangles should be filled with cells, that is, if a component form a rectangle of size $ h×w $ , then the component must contain exactly $ hw $ cells.

A connected component of the same values is a set of cells of the table that meet the following conditions:

- every two cells of the set have the same value;
- the cells of the set form a connected region on the table (two cells are connected if they are adjacent in some row or some column of the table);
- it is impossible to add any cell to the set unless we violate the two previous conditions.

Can Sereja change the values of at most $ k $ cells of the table so that the table met the described requirement? What minimum number of table cells should he change in this case?

## 输入格式

The first line contains integers $ n $ , $ m $ and $ k $ $ (1<=n,m<=100; 1<=k<=10) $ . Next $ n $ lines describe the table $ a $ : the $ i $ -th of them contains $ m $ integers $ a_{i1},a_{i2},...,a_{im} $ $ (0<=a_{i,j}<=1) $ — the values in the cells of the $ i $ -th row.

## 输出格式

Print -1, if it is impossible to meet the requirement. Otherwise, print the minimum number of cells which should be changed.

## 样例 #1

### 输入

```
5 5 2
1 1 1 1 1
1 1 1 1 1
1 1 0 1 1
1 1 1 1 1
1 1 1 1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 4 1
1 0 0 0
0 1 1 1
1 1 1 0

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
3 4 1
1 0 0 1
0 1 1 0
1 0 0 1

```

### 输出

```
0

```

