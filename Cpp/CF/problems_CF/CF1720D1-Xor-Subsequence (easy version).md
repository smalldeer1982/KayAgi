---
title: "Xor-Subsequence (easy version)"
layout: "post"
diff: 普及+/提高
pid: CF1720D1
tag: []
---

# Xor-Subsequence (easy version)

## 题目描述

这是此问题的简单版本。简单版本与困难版本的唯一区别在于：在简单版本中，$a_i\leq 200$。

给你一个长为 $n$ 的整数数组 $a$，从 $0$ 开始编号。

一个长为 $m$ ，从 $0$ 开始编号的整数数组 $b$ 是数组 $a$ 的 subsequence，当且仅当 $0\leq b_0<b_1<\dots<b_{m-1}<n$。

若 $b$ 是 $a$ 的 beautiful subsequence，当且仅当满足以下条件：

+ $b$ 是 $a$ 的 subsequence；
+ $\forall p\in[0,m)\cap\textbf{N},a_{b_p}\oplus b_{p+1}<a_{b_{p+1}}\oplus b_p$。

其中 $\oplus$ 表示位运算中的异或运算。

现在，你需要求出最长的 beautiful subsequence 有多长。

## 输入格式

第一行一个整数 $T$，表示数据组数。

对于每组数据，第一行一个整数 $n$，表示数组 $a$ 的长度。

第二行有 $n$ 个整数，表示数组 $a$。

## 输出格式

对于每组数据，输出一行一个数，表示最长的 beautiful subsequence 的长度。

## 说明/提示

$1\leq T\leq 10^5,2\leq n\leq 3\times 10^5,0\leq a_i\leq 200,\sum n\leq 3\times 10^5$。

## 样例 #1

### 输入

```
3
2
1 2
5
5 2 4 3 1
10
3 8 8 2 9 1 6 2 8 3
```

### 输出

```
2
3
6
```

