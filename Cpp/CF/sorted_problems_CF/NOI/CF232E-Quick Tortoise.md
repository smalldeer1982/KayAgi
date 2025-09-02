---
title: "Quick Tortoise"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF232E
tag: []
---

# Quick Tortoise

## 题目描述

John Doe has a field, which is a rectangular table of size $ n×m $ . We assume that the field rows are numbered from 1 to $ n $ from top to bottom, and the field columns are numbered from 1 to $ m $ from left to right. Then the cell of the field at the intersection of the $ x $ -th row and the $ y $ -th column has coordinates ( $ x $ ; $ y $ ).

We know that some cells of John's field are painted white, and some are painted black. Also, John has a tortoise, which can move along the white cells of the field. The tortoise can get from a white cell with coordinates ( $ x $ ; $ y $ ) into cell ( $ x+1 $ ; $ y $ ) or ( $ x $ ; $ y+1 $ ), if the corresponding cell is painted white. In other words, the turtle can move only along the white cells of the field to the right or down. The turtle can not go out of the bounds of the field.

In addition, John has $ q $ queries, each of them is characterized by four numbers $ x_{1},y_{1},x_{2},y_{2} $ ( $ x_{1}<=x_{2} $ , $ y_{1}<=y_{2} $ ). For each query John wants to know whether the tortoise can start from the point with coordinates ( $ x_{1} $ ; $ y_{1} $ ), and reach the point with coordinates ( $ x_{2} $ ; $ y_{2} $ ), moving only along the white squares of the field.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ ( $ 1<=n,m<=500 $ ) — the field sizes.

Each of the next $ n $ lines contains $ m $ characters "\#" and ".": the $ j $ -th character of the $ i $ -th line equals "\#", if the cell ( $ i $ ; $ j $ ) is painted black and ".", if it is painted white.

The next line contains integer $ q $ ( $ 1<=q<=6·10^{5}) $ — the number of queries. Next $ q $ lines contain four space-separated integers $ x_{1} $ , $ y_{1} $ , $ x_{2} $ and $ y_{2} $ ( $ 1<=x_{1}<=x_{2}<=n $ , $ 1<=y_{1}<=y_{2}<=m $ ) — the coordinates of the starting and the finishing cells. It is guaranteed that cells ( $ x_{1} $ ; $ y_{1} $ ) and ( $ x_{2} $ ; $ y_{2} $ ) are white.

## 输出格式

For each of $ q $ queries print on a single line "Yes", if there is a way from cell ( $ x_{1} $ ; $ y_{1} $ ) to cell ( $ x_{2} $ ; $ y_{2} $ ), that meets the requirements, and "No" otherwise. Print the answers to the queries in the order, in which the queries are given in the input.

## 样例 #1

### 输入

```
3 3
...
.##
.#.
5
1 1 3 3
1 1 1 3
1 1 3 1
1 1 1 2
1 1 2 1

```

### 输出

```
No
Yes
Yes
Yes
Yes

```

## 样例 #2

### 输入

```
5 5
.....
.###.
.....
.###.
.....
5
1 1 5 5
1 1 1 5
1 1 3 4
2 1 2 5
1 1 2 5

```

### 输出

```
Yes
Yes
Yes
No
Yes

```

