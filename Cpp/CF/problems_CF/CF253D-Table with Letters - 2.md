---
title: "Table with Letters - 2"
layout: "post"
diff: 普及+/提高
pid: CF253D
tag: []
---

# Table with Letters - 2

## 题目描述

Vasya has recently started to learn English. Now he needs to remember how to write English letters. He isn't sure about some of them, so he decided to train a little.

He found a sheet of squared paper and began writing arbitrary English letters there. In the end Vasya wrote $ n $ lines containing $ m $ characters each. Thus, he got a rectangular $ n×m $ table, each cell of the table contained some English letter. Let's number the table rows from top to bottom with integers from 1 to $ n $ , and columns — from left to right with integers from 1 to $ m $ .

After that Vasya looked at the resulting rectangular table and wondered, how many subtables are there, that matches both following conditions:

- the subtable contains at most $ k $ cells with "a" letter;
- all letters, located in all four corner cells of the subtable, are equal.

Formally, a subtable's definition is as follows. It is defined by four integers $ x_{1},y_{1},x_{2},y_{2} $ such that $ 1<=x_{1}&lt;x_{2}<=n $ , $ 1<=y_{1}&lt;y_{2}<=m $ . Then the subtable contains all such cells $ (x,y) $ ( $ x $ is the row number, $ y $ is the column number), for which the following inequality holds $ x_{1}<=x<=x_{2},y_{1}<=y<=y_{2} $ . The corner cells of the table are cells $ (x_{1},y_{1}) $ , $ (x_{1},y_{2}) $ , $ (x_{2},y_{1}) $ , $ (x_{2},y_{2}) $ .

Vasya is already too tired after he's been writing letters to a piece of paper. That's why he asks you to count the value he is interested in.

## 输入格式

The first line contains three integers $ n,m,k $ $ (2<=n,m<=400; 0<=k<=n·m) $ .

Next $ n $ lines contain $ m $ characters each — the given table. Each character of the table is a lowercase English letter.

## 输出格式

Print a single integer — the number of required subtables.

## 说明/提示

There are two suitable subtables in the first sample: the first one's upper left corner is cell $ (2,2) $ and lower right corner is cell $ (3,3) $ , the second one's upper left corner is cell $ (2,1) $ and lower right corner is cell $ (3,4) $ .

## 样例 #1

### 输入

```
3 4 4
aabb
baab
baab

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 5 1
ababa
ccaca
ccacb
cbabc

```

### 输出

```
1

```

