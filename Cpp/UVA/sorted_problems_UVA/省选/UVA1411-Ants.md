---
title: "Ants"
layout: "post"
diff: 省选/NOI-
pid: UVA1411
tag: ['网络流', '图论建模', '二分图', '费用流']
---

# Ants

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4157

[PDF](https://uva.onlinejudge.org/external/14/p1411.pdf)

给定平面上的 $N$ 个黑点和 $N$ 个白点（共 $2N$ 个点），请找到一种方案，对于每一个黑点，找到一个白点，用线段把黑点和白点连接，保证最后**任意两条线段无公共点（不相交）**。

## 输入格式

**可能有多组数据。**

对于每组输入数据，第一行一个整数 $N$，描述黑点和白点的数量；

接下来 $N$ 行，每行两个整数 $x,y$，描述**黑点**的坐标；

再接下来 $N$ 行，每行两个整数 $x,y$，描述**白点**的坐标；

## 输出格式

对于每组数据，输出 $N$ 行，每行一个整数，第 $i$ 行的整数 $j$ 表示第 $i$ 个黑点与第 $j$ （$1\leq j \leq N$）个白点相连。

**请在每组数据之间输出一个空行。**

若有多解，任意输出一个均可。

## 说明/提示

## 数据范围与提示

$1\leq N\leq 100, |x|, |y|\leq 10^4$。

保证无三点共线。数据保证有解。

$\small{\text{Statement fixed by @Starrykiller.}}$

## 样例 #1

### 输入

```
5
-42 58
44 86
7 28
99 34
-13 -59
-47 -44
86 74
68 -75
-68 60
99 -6
```

### 输出

```
4
2
1
5
3
```

