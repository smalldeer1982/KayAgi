---
title: "Captain Flint and a Long Voyage"
layout: "post"
diff: 普及-
pid: CF1388B
tag: []
---

# Captain Flint and a Long Voyage

## 题目描述

若有一个 $n$ 位正整数 $x$，定义 $k$ 的值为将 $x$ 的每一位上的数字转换为二进制（不含前导 $0$）。比如 $x=729$ 时，$k=111101001$。将 $k$ 的后 $n$ 位截去得到 $r$。比如 $x=729$ 时，$r=111101$。

现在给定 $n$，你需要找到 $r$ 最大时 $x$ 的最小值。

## 输入格式

第一行一个整数 $T(1\le t\le1000)$，表示数据组数。

接下来 $T$ 行，每行一个正整数 $n(1\le n\le 10^5)$。

## 输出格式

对于每组数据，输出一行一个正整数，表示 $r$ 最大时 $x$ 的最小值。

## 说明/提示

$1\le t\le1000$，$1\le n\le 10^5$。

数据保证所有数据中的 $n$ 之和不超过 $2\times10^5$。

Translated by [cmll02](https://www.luogu.com.cn/user/171487).

## 样例 #1

### 输入

```
2
1
3
```

### 输出

```
8
998
```

