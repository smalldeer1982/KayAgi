---
title: "Volcanoes"
layout: "post"
diff: 提高+/省选-
pid: CF383B
tag: []
---

# Volcanoes

## 题目描述

Iahub got lost in a very big desert. The desert can be represented as a $ n×n $ square matrix, where each cell is a zone of the desert. The cell $ (i,j) $ represents the cell at row $ i $ and column $ j $ $ (1<=i,j<=n) $ . Iahub can go from one cell $ (i,j) $ only down or right, that is to cells $ (i+1,j) $ or $ (i,j+1) $ .

Also, there are $ m $ cells that are occupied by volcanoes, which Iahub cannot enter.

Iahub is initially at cell $ (1,1) $ and he needs to travel to cell $ (n,n) $ . Knowing that Iahub needs $ 1 $ second to travel from one cell to another, find the minimum time in which he can arrive in cell $ (n,n) $ .

## 输入格式

The first line contains two integers $ n $ $ (1<=n<=10^{9}) $ and $ m $ $ (1<=m<=10^{5}) $ . Each of the next $ m $ lines contains a pair of integers, $ x $ and $ y $ $ (1<=x,y<=n) $ , representing the coordinates of the volcanoes.

Consider matrix rows are numbered from 1 to $ n $ from top to bottom, and matrix columns are numbered from 1 to $ n $ from left to right. There is no volcano in cell $ (1,1) $ . No two volcanoes occupy the same location.

## 输出格式

Print one integer, the minimum time in which Iahub can arrive at cell $ (n,n) $ . If no solution exists (there is no path to the final cell), print -1.

## 说明/提示

Consider the first sample. A possible road is: $ (1,1) $ $ → $ $ (1,2) $ $ → $ $ (2,2) $ $ → $ $ (2,3) $ $ → $ $ (3,3) $ $ → $ $ (3,4) $ $ → $ $ (4,4) $ .

## 样例 #1

### 输入

```
4 2
1 3
1 4

```

### 输出

```
6

```

## 样例 #2

### 输入

```
7 8
1 6
2 6
3 5
3 6
4 3
5 1
5 2
5 3

```

### 输出

```
12

```

## 样例 #3

### 输入

```
2 2
1 2
2 1

```

### 输出

```
-1

```

