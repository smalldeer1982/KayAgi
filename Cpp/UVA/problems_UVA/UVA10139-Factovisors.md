---
title: "Factovisors"
layout: "post"
diff: 难度0
pid: UVA10139
tag: []
---

# Factovisors

## 题目描述

对于非负整数 $n$，$n! = \begin{cases} 1 & (n=0) \\ n \times (n - 1)! & (n>0) \end{cases}$

对于整数 $a,b$，如果存在整数 $k$ 使得 $k\times a=b$，则称 $a$ 整除 $b$，记作 $a \mid b$。

给你两个非负整数 $n,m$，判断 $n!$ 能否被 $m$ 整除。

## 输入格式

输入包含多组数据。每组数据有两个非负整数 $n,m$（$0\leq n,m < 2^{31}$）。

## 输出格式

判断 $n!$ 能否被 $m$ 整除。具体格式参见输入输出样例。

## 样例 #1

### 输入

```
6 9
6 27
20 10000
20 100000
1000 1009
```

### 输出

```
9 divides 6!
27 does not divide 6!
10000 divides 20!
100000 does not divide 20!
1009 does not divide 1000!
```

