---
title: "Appleman and Complicated Task"
layout: "post"
diff: 省选/NOI-
pid: CF461D
tag: []
---

# Appleman and Complicated Task

## 题目描述

Toastman came up with a very complicated task. He gives it to Appleman, but Appleman doesn't know how to solve it. Can you help him?

Given a $ n×n $ checkerboard. Each cell of the board has either character 'x', or character 'o', or nothing. How many ways to fill all the empty cells with 'x' or 'o' (each cell must contain only one character in the end) are there, such that for each cell the number of adjacent cells with 'o' will be even? Find the number of ways modulo $ 1000000007 $ $ (10^{9}+7) $ . Two cells of the board are adjacent if they share a side.

## 输入格式

The first line contains two integers $ n $ , $ k $ ( $ 1<=n,k<=10^{5} $ ) — the size of the board, and the number of cells that has characters initially.

Then $ k $ lines follows. The $ i $ -th line contains two integers and a character: $ a_{i} $ , $ b_{i} $ , $ c_{i} $ ( $ 1<=a_{i},b_{i}<=n $ ; $ c_{i} $ is either 'o' or 'x'). This line means: there is a character $ c_{i} $ in the cell that is located on the intersection of the $ a_{i} $ -th row and $ b_{i} $ -th column. All the given cells are distinct.

Consider that the rows are numbered from $ 1 $ to $ n $ from top to bottom. Analogically, the columns are numbered from $ 1 $ to $ n $ from left to right.

## 输出格式

Print a single integer — the answer to the problem.

## 说明/提示

In the first example there are two ways:

`<br></br>    xxo          xoo<br></br>    xox          ooo<br></br>    oxx          oox<br></br>`

## 样例 #1

### 输入

```
3 2
1 1 x
2 2 o

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 3
2 4 x
3 4 x
3 2 x

```

### 输出

```
2

```

