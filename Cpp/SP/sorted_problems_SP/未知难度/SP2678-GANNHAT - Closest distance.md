---
title: "GANNHAT - Closest distance"
layout: "post"
diff: 难度0
pid: SP2678
tag: []
---

# GANNHAT - Closest distance

## 题目描述

### 题意翻译

对于平面直角坐标系上的两个点 $A(x_1,y_1)$ 和 $B(x_2,y_2)$，它们的曼哈顿距离 $D(A,B)= | x_1-x_2 | + |y_1-y_2|$。

给你 $N$ 个点的横纵坐标，对于每个点求离它曼哈顿距离最小的点。

## 输入格式

第一行一个正整数 $N$，表示点的数量。

接下来 $N$ 行，对于第 $i+1$ 行，输入两个非负整数 $x,y$ 表示第 $i$ 个点的横坐标和纵坐标。

## 输出格式

输出 $N$ 行，第 $i$ 行表示离第 $i$ 个点最小的曼哈顿距离 $D(i,j)$（$j\neq i$）。

## 说明/提示

$1\le N \le 2\times 10^5$，$0\le x,y\le 10^7$。

***

翻译：[Zskioaert1106](https://www.luogu.com.cn/user/1072502)。

## 样例 #1

### 输入

```
4
0 0
0 1
1 0
1 1
```

### 输出

```
1
1
1
1
```

