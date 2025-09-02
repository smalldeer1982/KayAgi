---
title: "Mr. Bender and Square"
layout: "post"
diff: 普及+/提高
pid: CF255D
tag: []
---

# Mr. Bender and Square

## 题目描述

Mr. Bender has a digital table of size $ n×n $ , each cell can be switched on or off. He wants the field to have at least $ c $ switched on squares. When this condition is fulfilled, Mr Bender will be happy.

We'll consider the table rows numbered from top to bottom from 1 to $ n $ , and the columns — numbered from left to right from 1 to $ n $ . Initially there is exactly one switched on cell with coordinates $ (x,y) $ ( $ x $ is the row number, $ y $ is the column number), and all other cells are switched off. Then each second we switch on the cells that are off but have the side-adjacent cells that are on.

For a cell with coordinates $ (x,y) $ the side-adjacent cells are cells with coordinates $ (x-1,y) $ , $ (x+1,y) $ , $ (x,y-1) $ , $ (x,y+1) $ .

In how many seconds will Mr. Bender get happy?

## 输入格式

The first line contains four space-separated integers $ n,x,y,c $ $ (1<=n,c<=10^{9}; 1<=x,y<=n; c<=n^{2}) $ .

## 输出格式

In a single line print a single integer — the answer to the problem.

## 说明/提示

Initially the first test has one painted cell, so the answer is 0. In the second test all events will go as is shown on the figure. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF255D/b709c1aa5b91b7af907cf3f3ca10b895a1b76650.png).

## 样例 #1

### 输入

```
6 4 3 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
9 3 8 10

```

### 输出

```
2

```

