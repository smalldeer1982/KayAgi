---
title: "Vupsen, Pupsen and 0"
layout: "post"
diff: 普及+/提高
pid: CF1582D
tag: []
---

# Vupsen, Pupsen and 0

## 题目描述

给一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$ ，寻找一个长度为 $n$ 序列 $b_1,b_2,\dots,b_n$ ，满足 $\forall i\in\left[1,n\right]b_i\not=0,\ \ \sum\limits_{i=1}^n |b_i|\le10^9,\ \ \sum\limits_{i=1}^n a_i\times b_i=0$ ，可以证明答案一定存在。

## 输入格式

第一行输入一个正整数 $t$ 表示数据组数。

对于每一组数据，第一行输入一个正整数 $n$ 表示序列长度，第二行 $n$ 个整数表示序列 $a$ 。

## 输出格式

对于每一组数据，输出一行 $n$ 个整数表示序列 $b$ 。如果有多种答案，输出任意一种。

## 说明/提示

$1\le t\le100,2\le n\le10^5,2\le\sum n\le2\times10^5,-10^4\le a_i\le10^4,a_i\not=0$ 。

## 样例 #1

### 输入

```
3
2
5 5
5
5 -2 10 -9 4
7
1 2 3 4 5 6 7
```

### 输出

```
1 -1
-1 5 1 -1 -1
-10 2 2 -3 5 -1 -1
```

