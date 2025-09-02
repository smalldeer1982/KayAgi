---
title: "2-Coloring"
layout: "post"
diff: 省选/NOI-
pid: CF1503E
tag: []
---

# 2-Coloring

## 题目描述

There is a grid with $ n $ rows and $ m $ columns. Every cell of the grid should be colored either blue or yellow.

A coloring of the grid is called stupid if every row has exactly one segment of blue cells and every column has exactly one segment of yellow cells.

In other words, every row must have at least one blue cell, and all blue cells in a row must be consecutive. Similarly, every column must have at least one yellow cell, and all yellow cells in a column must be consecutive.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1503E/f3562aaf6fab4721f0bb458f1d8dd50d6d917a2d.png) An example of a stupid coloring.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1503E/de3679de796822ab7c00a24a2e2a1dd2e13093bc.png) Examples of clever colorings. The first coloring is missing a blue cell in the second row, and the second coloring has two yellow segments in the second column. How many stupid colorings of the grid are there? Two colorings are considered different if there is some cell that is colored differently.

## 输入格式

The only line contains two integers $ n $ , $ m $ ( $ 1\le n, m\le 2021 $ ).

## 输出格式

Output a single integer — the number of stupid colorings modulo $ 998244353 $ .

## 说明/提示

In the first test case, these are the only two stupid $ 2\times 2 $ colorings.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1503E/f66a34ec71497a45956a4e5d1e13d8d8d13ba2bf.png)

## 样例 #1

### 输入

```
2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 3
```

### 输出

```
294
```

## 样例 #3

### 输入

```
2020 2021
```

### 输出

```
50657649
```

