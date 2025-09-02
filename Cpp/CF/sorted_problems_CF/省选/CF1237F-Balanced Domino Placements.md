---
title: "Balanced Domino Placements"
layout: "post"
diff: 省选/NOI-
pid: CF1237F
tag: []
---

# Balanced Domino Placements

## 题目描述

Consider a square grid with $ h $ rows and $ w $ columns with some dominoes on it. Each domino covers exactly two cells of the grid that share a common side. Every cell is covered by at most one domino.

Let's call a placement of dominoes on the grid perfectly balanced if no row and no column contains a pair of cells covered by two different dominoes. In other words, every row and column may contain no covered cells, one covered cell, or two covered cells that belong to the same domino.

You are given a perfectly balanced placement of dominoes on a grid. Find the number of ways to place zero or more extra dominoes on this grid to keep the placement perfectly balanced. Output this number modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains three integers $ h $ , $ w $ , and $ n $ ( $ 1 \le h, w \le 3600 $ ; $ 0 \le n \le 2400 $ ), denoting the dimensions of the grid and the number of already placed dominoes. The rows are numbered from $ 1 $ to $ h $ , and the columns are numbered from $ 1 $ to $ w $ .

Each of the next $ n $ lines contains four integers $ r_{i, 1}, c_{i, 1}, r_{i, 2}, c_{i, 2} $ ( $ 1 \le r_{i, 1} \le r_{i, 2} \le h $ ; $ 1 \le c_{i, 1} \le c_{i, 2} \le w $ ), denoting the row id and the column id of the cells covered by the $ i $ -th domino. Cells $ (r_{i, 1}, c_{i, 1}) $ and $ (r_{i, 2}, c_{i, 2}) $ are distinct and share a common side.

The given domino placement is perfectly balanced.

## 输出格式

Output the number of ways to place zero or more extra dominoes on the grid to keep the placement perfectly balanced, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the initial grid looks like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237F/23d2c7832fa87b26433f4443e57f8a2c61335a78.png)

Here are $ 8 $ ways to place zero or more extra dominoes to keep the placement perfectly balanced:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237F/f39e74c5e6c5abc41daa487ad47333c83b2084c2.png)

In the second example, the initial grid looks like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237F/7739b264ee73fb643402600eb5d0f9454c11a61d.png)

No extra dominoes can be placed here.

## 样例 #1

### 输入

```
5 7 2
3 1 3 2
4 4 4 5

```

### 输出

```
8

```

## 样例 #2

### 输入

```
5 4 2
1 2 2 2
4 3 4 4

```

### 输出

```
1

```

## 样例 #3

### 输入

```
23 42 0

```

### 输出

```
102848351

```

