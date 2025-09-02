---
title: "Insert a Progression"
layout: "post"
diff: 普及/提高-
pid: CF1671D
tag: []
---

# Insert a Progression

## 题目描述

给你一个 $n$ 个数的序列 $a_1,a_2,...,a_n$，同时给你 $x$ 个正整数 $1,2,...,x$。

你要将这 $x$ 个数插入到序列 $a$ 中，每个数可以插在序列首位，末位以及任意两个元素中间。

设最后得到的序列为 $a'$，定义它的分数为相邻两个元素之间的绝对值之和，也就是 $\sum\limits_{i=1}^{n+x-1}|a_i'-a_{i+1}'|$。

求最小分数。

## 输入格式

第一行输入一个整数 $t$（$1\le t\le 10^4$），表示 $t$ 组询问。

每组询问的第一行输入两个整数 $n,x$（$1\le n,x\le 2\times 10^5$），表示初始序列的长度以及你要插入的数的个数。

每组询问的第二行包含 $n$ 个整数 $a_1,a_2,...,a_n$（$1\le a_i\le 2\times 10^5$）。

保证 $\sum n\le2\times10^5$。

## 输出格式

对于每组询问，输出一个整数，表示将 $x$ 个数插入到 $a$ 后得到序列 $a'$ 的最小分数。

## 说明/提示

样例 $4$ 组询问（构造不一定唯一）：

- $ \underline{1}, \underline{2}, \underline{3}, \underline{4}, \underline{5}, 10 $
- $ \underline{7}, 7, \underline{6}, \underline{4}, 2, \underline{2}, \underline{1}, \underline{3}, \underline{5}, \underline{8}, 10 $
- $ 6, \underline{1}, 1, \underline{2}, 5, 7, 3, 3, 9, 10, 10, 1 $
- $ 1, 3, \underline{1}, 1, 2, \underline{2}, \underline{3}, \underline{4}, \underline{5}, \underline{6}, \underline{7}, \underline{8}, \underline{9}, \underline{10} $

## 样例 #1

### 输入

```
4
1 5
10
3 8
7 2 10
10 2
6 1 5 7 3 3 9 10 10 1
4 10
1 3 1 2
```

### 输出

```
9
15
31
13
```

