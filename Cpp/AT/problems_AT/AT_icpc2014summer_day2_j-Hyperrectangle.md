---
title: "Hyperrectangle"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_icpc2014summer_day2_j
tag: []
---

# Hyperrectangle

## 题目描述

## 题意简述

* 你有一个 $n$ 维超矩形，第 $i$ 维坐标在 $[0,l_i]$ 之间。
* 给定 $s$，求这个矩形中满足 $\sum\limits_{i=1}^{n}x_i\le s$ 的部分所占超体积。
* $2\le n\le 300$，$1\le l_i\le300$，$0\le s\le \sum\limits_{i=1}^{n}l_i$。

## 输入格式

第一行，输入一个数 $n$。

接下来 $n$ 行，每行一个数表示 $l_i$。

第 $n+2$ 行，输入一个数 $s$。

## 输出格式

设答案为 $ans$，输出 $ans\times n!$ 对 $10^9+7$ 取模的结果。

## 样例 #1

### 输入

```
2
6
3
4

```

### 输出

```
15

```

## 样例 #2

### 输入

```
5
12
34
56
78
90
123

```

### 输出

```
433127538

```

