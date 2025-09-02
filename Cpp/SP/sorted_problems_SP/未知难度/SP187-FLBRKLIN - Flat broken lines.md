---
title: "FLBRKLIN - Flat broken lines"
layout: "post"
diff: 难度0
pid: SP187
tag: []
---

# FLBRKLIN - Flat broken lines

## 题目描述

我们在一张纸上绘制了一个笛卡尔坐标系。假设我们可以从纸的左边到右边用一笔画出折线，同时要求每段折线与 $OX$ 轴的夹角在 \[-45°, 45°\] 范围内。这样的折线我们称之为「平直折线」。现在给定 $n$ 个不同的整数坐标点，请找出需要画多少条这样的平直折线，才能覆盖所有这些点（一个点被折线覆盖当且仅当它位于这条折线上）。

## 输入格式

第一行输入一个整数 $t$，表示测试用例的数量。接下来是 $t$ 个测试用例，测试用例之间用一个空行隔开。

每个测试用例的第一行是一个正整数 $n$，表示点的数量（$n$ 不超过 30000）。接下来的 $n$ 行中，每行有两个整数 $x$ 和 $y$，用空格隔开，表示一个点的坐标，满足 $0 \leq x \leq 30000$，$0 \leq y \leq 30000$。

## 输出格式

对于每个测试用例，输出一行，表示覆盖所有点所需的最少平直折线的条数。

## 说明/提示

- $1 \leq t \leq 10$
- $1 \leq n \leq 30000$
- $0 \leq x, y \leq 30000$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
The number of test cases t is in the first line of input, then t test cases follow separated by an empty line.
In the first line of a test case there is one positive integer n, not greater than 30000, which denotes the number of points. In the following n lines there are coordinates of points. Each line contains two integers x, y separated by a single space, 0  &lt;=  x  &lt;=  30000, 0  &lt;=  y  &lt;=  30000. The numbers in the i-th line are the coordinates of the i-th point.
```

### 输出

```
s the result.
```

## 样例 #2

### 输入

```
1
6
1 6
10 8
1 5
2 20
4 4
6 2
```

### 输出

```
3
```

