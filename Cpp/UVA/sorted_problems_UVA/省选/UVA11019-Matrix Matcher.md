---
title: "Matrix Matcher"
layout: "post"
diff: 省选/NOI-
pid: UVA11019
tag: []
---

# Matrix Matcher

## 题目描述

$T$ 组数据，每组数据给定一个 $N\times M$ 的 $A$ 矩阵，满足 $1\le N,M\le 1000$，再给定一个 $X\times Y$ 的 $B$ 矩阵，满足 $1\le X,Y\le 100$，求 $B$ 矩阵在 $A$ 矩阵中出现的次数。

## 输入格式

第一行输入 $T$，代表 $T$ 组数据;

接下来 $T$ 组数据，每组先输入 $N$ 和 $M$，代表 $A$ 矩阵有 $N$ 行 $M$ 列，输入 $A$ 矩阵；

最后输入 $X$ 和 $Y$，代表 $B$ 矩阵有 $X$ 行 $Y$ 列，输入 $B$ 矩阵。

## 输出格式

输出一个整数，即 $B$ 矩阵在 $A$ 矩阵中出现的次数。

## 样例 #1

### 输入

```
2
1 1
x
1 1
y
3 3
abc
bcd
cde
2 2
bc
cd
```

### 输出

```
0
2
```

