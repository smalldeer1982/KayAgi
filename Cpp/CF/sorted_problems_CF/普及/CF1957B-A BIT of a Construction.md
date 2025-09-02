---
title: "A BIT of a Construction"
layout: "post"
diff: 普及/提高-
pid: CF1957B
tag: ['贪心', '位运算']
---

# A BIT of a Construction

## 题目描述

给定 $n,k$，请构造序列 $a_n$，你需要保证 $a_i$ 为自然数，同时满足以下条件：

* $\sum\limits_{i=1}^{n} a_i=k$。

* $a_1|a_2|\dots|a_n$ 二进制下拆位后 $1$ 的数量最大，其中 $|$ 表示[按位或](https://baike.baidu.com/item/%E6%8C%89%E4%BD%8D%E6%88%96/548283?fr=ge_ala)。

## 输入格式

第一行一个整数 $t$，表示数据组数。

接下来对于每组数据，共一行两个整数 $n,k$。

## 输出格式

共 $t$ 行，每行 $n$ 个整数，表示构造的 $a_n$。

如果有多个解，输出任意解即可。

## 说明/提示

对于全部数据，满足 $1\le t\le10^4$，$1\le n\le2\times10^5$，$1\le k\le10^9$，$\sum n\le2\times10^5$。

## 样例 #1

### 输入

```
4
1 5
2 3
2 5
6 51
```

### 输出

```
5
1 2
5 0
3 1 1 32 2 12
```

