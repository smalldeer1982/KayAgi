---
title: "感觉不错 Feel Good"
layout: "post"
diff: 提高+/省选-
pid: UVA1619
tag: ['枚举', '栈']
---

# 感觉不错 Feel Good

## 题目背景

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4494

[PDF](https://uva.onlinejudge.org/external/16/p1619.pdf)

## 题目描述

给出正整数 $n$ 和一个长度为 $n$ 的数列 $a$，要求找出一个子区间 $[l,r]$，使这个子区间的数字和乘上子区间中的最小值最大。

形式化的，要求找出 $[l,r]$ 使得：
$$
\left(\sum \limits_{i=l}^{r}a_i\right)\times\min\limits_{i=l}^{r}a_i
$$
最大。输出这个最大值与区间的两个端点。

在答案相等的情况下最小化区间长度，最小化长度的情况下最小化左端点序号。


## 输入格式

本题有多组数据。

每组数据的第一行是一个整数 $n$；
第二行是 $n$ 个非负整数 $a_i$。

两组数据之间用一个空行隔开。

## 输出格式

对于每组数据，第一行输出最大值，第二行输出区间左、右端点。

两组数据间用 **一个空行** 隔开。

**本题不忽略文末回车。**

## 说明/提示

$1 \leq n \leq 10^5, 0 \leq a_i \leq 10^6$。

## 样例 #1

### 输入

```
6
3 1 6 4 5 2
```

### 输出

```
60
3 5
```



---

