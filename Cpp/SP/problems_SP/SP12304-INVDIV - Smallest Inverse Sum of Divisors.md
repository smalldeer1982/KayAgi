---
title: "INVDIV - Smallest Inverse Sum of Divisors"
layout: "post"
diff: 普及/提高-
pid: SP12304
tag: []
---

# INVDIV - Smallest Inverse Sum of Divisors

## 题目描述

定义一个函数： $\sigma(x)$ 为正整数  $x$ 的所有约数的和，举个例子： $\sigma(60)=1+2+3+4+5+6+10+12+15+20+30+60=168$

现在给定一个正整数  $n$ ，求最小的正整数  $i$ ，使得  $\sigma(i)=n$ 。 （若无解，请输出`-1`）

## 输入格式

本题有多组数据，数据组数共  $T$ 组。

对于每组数据，一组数据占一行，仅输入一行一个正整数  $n$ 。

## 输出格式

输出的第  $j$ 行表示第  $j$ 组数据的答案，一个正整数。

## 说明/提示

$1\leq T\leq 10^5, 1\leq n\leq 10^8$

## 样例 #1

### 输入

```
5
1
16
40
60
168
```

### 输出

```
1
-1
27
24
60
```

