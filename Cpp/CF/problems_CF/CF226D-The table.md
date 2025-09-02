---
title: "The table"
layout: "post"
diff: 省选/NOI-
pid: CF226D
tag: []
---

# The table

## 题目描述

Harry Potter has a difficult homework. Given a rectangular table, consisting of $ n×m $ cells. Each cell of the table contains the integer. Harry knows how to use two spells: the first spell change the sign of the integers in the selected row, the second — in the selected column. Harry's task is to make non-negative the sum of the numbers in each row and each column using these spells.

Alone, the boy can not cope. Help the young magician!

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n, m<=100) $ — the number of rows and the number of columns.

Next $ n $ lines follow, each contains $ m $ integers: $ j $ -th integer in the $ i $ -th line is $ a_{i,j} $ $ (|a_{i,j}|<=100) $ , the number in the $ i $ -th row and $ j $ -th column of the table.

The rows of the table numbered from 1 to $ n $ . The columns of the table numbered from 1 to $ m $ .

## 输出格式

In the first line print the number $ a $ — the number of required applications of the first spell. Next print $ a $ space-separated integers — the row numbers, you want to apply a spell. These row numbers must be distinct!

In the second line print the number $ b $ — the number of required applications of the second spell. Next print $ b $ space-separated integers — the column numbers, you want to apply a spell. These column numbers must be distinct!

If there are several solutions are allowed to print any of them.

## 样例 #1

### 输入

```
4 1
-1
-1
-1
-1

```

### 输出

```
4 1 2 3 4 
0 

```

## 样例 #2

### 输入

```
2 4
-1 -1 -1 2
1 1 1 1

```

### 输出

```
1 1 
1 4 

```

