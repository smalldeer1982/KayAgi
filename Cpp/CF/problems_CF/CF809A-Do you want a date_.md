---
title: "Do you want a date?"
layout: "post"
diff: 普及+/提高
pid: CF809A
tag: []
---

# Do you want a date?

## 题目描述

给定含有 $n$ 个正整数的数字集合 $A$，求

$$ \sum_{a\subseteq A,a\ne\varnothing}F(a) $$

其中 $F(a)$ 表示集合 $a$ 中所有数字之间差值的最大值，即

$$ F(a)=\max_{(i,j)\in a}{|x_i-x_j|}. $$

## 输入格式

第一行一个整数 $n$。

接下来 $n$ 个数 $x_1,x_2,\cdots,x_n$

## 输出格式

一行一个整数表示答案，答案对 $10^9+7$ 取模。

## 说明/提示

$1 \le n \le 3\times 10^5$
$1 \le x_i \le 10^9$，保证 $x_i$ 互不相同。

## 样例 #1

### 输入

```
2
4 7

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
4 3 1

```

### 输出

```
9

```

