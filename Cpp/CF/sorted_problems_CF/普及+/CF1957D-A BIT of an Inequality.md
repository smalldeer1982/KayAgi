---
title: "A BIT of an Inequality"
layout: "post"
diff: 普及+/提高
pid: CF1957D
tag: ['前缀和', '位运算']
---

# A BIT of an Inequality

## 题目描述

给定序列 $a_n$，求满足以下条件的三元组 $(x,y,z)$ 的数量：

* $1\le x\le y\le z\le n$.

* $f(x,y)\oplus f(y,z)>f(x,z)$.

我们规定 $f(l,r)$ 表示 $a_l\oplus a_{l+1}\oplus\dots\oplus a_{r-1}\oplus a_{r}$，$\oplus$ 表示[异或和](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fr=ge_ala)。

## 输入格式

第一行一个整数 $t$，表示数据组数。

接下来对于每组数据，第一行一个整数 $n$。

接下来 $n$ 个整数，表示 $a_i$。

## 输出格式

共 $t$ 行，每行一个整数，表示答案。

## 说明/提示

对于全部数据，满足 $1\le t\le10^4$，$1\le n\le10^5$，$1\le a_i\le10^9$，$\sum n\le10^5$。

## 样例 #1

### 输入

```
3
3
6 2 4
1
3
5
7 3 7 2 1
```

### 输出

```
4
0
16
```

