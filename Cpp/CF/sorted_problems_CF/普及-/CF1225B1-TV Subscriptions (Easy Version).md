---
title: "TV Subscriptions (Easy Version)"
layout: "post"
diff: 普及-
pid: CF1225B1
tag: []
---

# TV Subscriptions (Easy Version)

## 题目描述

### 题意简述

给定长度为 $n$ 的序列 $a$，对于 $a_i(1\leq i \leq n)$ 有 $a_i\leq k$。请你找出一段长度为 $d$ 的区间，使得这段区间所包含的不同元素的数量最小。

## 输入格式

第一行一个正整数 $t(1\leq t \leq 100)$ —— 数据组数。

对于每组数据，第一行有三个正整数 $n,k,d(1\leq n,k \leq 100,1\leq d \leq n)$。

接下来一行 $n$ 个正整数 $a_1,a_2,a_3,···a_n$。

## 输出格式

对于每组数据，输出长度为 $d$ 的区间中最小的不同元素的数量。

翻译贡献者：Meatherm (U108949)

## 样例 #1

### 输入

```
4
5 2 2
1 2 1 2 1
9 3 3
3 3 3 2 2 2 1 1 1
4 10 4
10 8 6 4
16 9 8
3 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3

```

### 输出

```
2
1
4
5

```

