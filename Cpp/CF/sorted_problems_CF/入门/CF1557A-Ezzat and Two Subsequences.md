---
title: "Ezzat and Two Subsequences"
layout: "post"
diff: 入门
pid: CF1557A
tag: []
---

# Ezzat and Two Subsequences

## 题目描述

Ezzat 有一个长度为 $n$ 的数组，他想将这个数组分成非空的数组 $a$ 和 $b$，使得 $f(a)+f(b)$ 最大，其中 $f(x)$ 表示 数组 $x$ 的平均值。

比如 $f([1,5,6])=\dfrac{1+5+6}{3}=4$。

## 输入格式

第一行一个正整数 $t$，表示有 $t$ 组数据。

对于每组数据，第一行一个正整数 $n$，第二行有 $n$ 个正整数 $a_1,a_2\ldots,a_n$。

## 输出格式

对于每组数据，每一行输出满足 Ezzat 的数组 $a$ 和 $b$ 的平均数之和。

记你的答案为 $a$，标准答案为 $b$ ，如果 $\dfrac{|a-b|}{\max(1,|b|)}\le10^{-6}$，那你的的答案就是正确的。

## 说明/提示

$1\le t\le10^3$，$2\le n\le10^5$，$-10^9\le a_i\le10^9$，$\sum n\le3\times10^5$。

translated by  @[lfxxx](https://www.luogu.com.cn/user/478461)

## 样例 #1

### 输入

```
4
3
3 1 2
3
-7 -6 -6
3
2 2 2
4
17 3 5 -3
```

### 输出

```
4.500000000
-12.500000000
4.000000000
18.666666667
```

