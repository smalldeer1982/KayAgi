---
title: "找座位 Finding Seats Again"
layout: "post"
diff: 省选/NOI-
pid: UVA11846
tag: []
---

# 找座位 Finding Seats Again

## 题目描述

有一个$n^2(n<20)$的座位矩阵里坐着$k(k\leq26)$个研究小组。每个小组的座位都是矩形形状。输入每个小组组长的位置和改组的成员个数，找到一种可能的座位方案。

## 输入格式

输入包含多组数据。
每组数据第一个是两个整数$n,k$。

接下来$n$行是一个$n^2$的矩阵。

## 输出格式

对于每组数据，输出$n$行一个$n^2$的矩阵，表示答案。

## 样例 #1

### 输入

```
3 3
3.4
...
.2.
7 18
...4.2.
...45..
222..3.
...2..3
.24...2
...2.3.
22..3..
0 0
```

### 输出

```
ABB
ABB
ACC
AAAABCC
DDDDBEF
GHIIBEF
GHJKBEF
LLJKBMM
NOJPQQQ
NOJPRRR
```

