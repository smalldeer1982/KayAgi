---
title: "Crossing Streets"
layout: "post"
diff: 提高+/省选-
pid: UVA1043
tag: ['搜索', '离散化']
---

# Crossing Streets

## 题目描述

Peter 要从家到学校，他想要规划穿过马路条数最少的路线。

给定 $n$ 条马路的起始点与终点坐标（马路一定与坐标轴平行），以及 Peter 家和大学所在位置坐标。求 Peter 从家到大学的任意路径下最少穿过多少条马路。特别地，Peter 不能穿过马路之间的交点。

## 输入格式

题目含有多组数据。

对于每组数据：

第一行，输入一个整数 $n$，代表马路条数。

接下来 $n$ 行，每行四个数 $x_1,y_1,x_2,y_2$，代表一条马路起点与终点坐标。

接下来一行四个数，$x_h,y_h,x_u,y_u$，代表 Peter 家的坐标与大学的坐标。

当输入的 $n$ 为 $0$ 时，结束程序。

## 输出格式

对于每组数据，输出 $2$ 行，格式如下：
```
City [i]
Peter has to cross [x] streets
```
其中 `i` 代表是第几组数据，`x` 代表答案（不包含 `[]`）。

## 说明/提示

$1\le n\le 500$，所有输入的坐标绝对值不大于 $2\times 10^9$。

Translated by HYdroKomide.

## 样例 #1

### 输入

```
8
6 0 24 0
24 0 24 4
24 4 6 4
6 4 6 0
12 1 26 1
26 1 26 6
26 6 12 6
12 6 12 1
0 1 17 3
1
10 10 20 10
1 1 30 30
0
```

### 输出

```
City 1
Peter has to cross 2 streets
City 2
Peter has to cross 0 streets
```

