---
title: "[ABC267G] Increasing K Times"
layout: "post"
diff: 省选/NOI-
pid: AT_abc267_g
tag: []
---

# [ABC267G] Increasing K Times

## 题目描述

给定一个正整数序列 $A=(a_1,a_2,\ldots,a_n)$，问有多少个 $1\sim n$ 的排列 $P=(p_1,p_2,\ldots,p_n)$ 满足：

- 存在恰好 $k$ 个整数 $i(1\leqslant i\leqslant n-1)$ 满足 $a_{p_i}<a_{p_{i+1}}$

对 $998244353$ 取模。

## 输入格式

第一行两个整数 $n,k$，含义如题意所示。

第二行 $n$ 个整数，第 $i$ 个整数表示 $a_i$。

## 输出格式

输出一个整数，表示满足条件的排列 $P$ 个数。

## 说明/提示

$2\leqslant n\leqslant 5000,0\leqslant k\leqslant n-1,1\leqslant a_i\leqslant n$

**样例解释**

只有四个排列 $P$ 满足条件，分别是 $(1,3,2,4),(1,4,2,3),(2,3,1,4),(2,4,1,3)$。

## 样例 #1

### 输入

```
4 2
1 1 2 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10 3
3 1 4 1 5 9 2 6 5 3
```

### 输出

```
697112
```

