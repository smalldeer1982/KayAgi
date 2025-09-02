---
title: "Unique Palindromes"
layout: "post"
diff: 提高+/省选-
pid: CF1823D
tag: []
---

# Unique Palindromes

## 题目描述

令 $p(t)$ 表示字符串 $t$ 的不同回文子串数（不同即多次出现只算一次）。

令 $p(s,m)$ 表示字符串 $s$ 的 $m$ 前缀的不同回文子串数，即 $p(s,m)=p(t)$，其中 $t=s[1..m]$。

如：$t=\texttt{abcbbcabcb}$，则 $p(t)=6$（$\texttt{a},\texttt{b},\texttt{c},\texttt{bb},\texttt{bcb},\texttt{cbbc}$），$p(t,5)=p(\texttt{abcbb})=5$（$\texttt{a},\texttt{b},\texttt{c},\texttt{bb},\texttt{bcb}$）。

给定整数 $n$ 和 $k$ 个条件，第 $i$ 个条件用 $(x_i,c_i)$ 表示，意思是对于字符串 $s$，满足 $p(s,x_i)=c_i$。

请你构造一个由小写拉丁字母组成的长度为 $n$ 的字符串 $s$，使其满足所有的 $k$ 个条件。

## 输入格式

本题有**多组数据**。第一行输入数据组数 $t$。

对于每组数据，第一行输入两个整数 $n$ 和 $k$，第二行输入 $k$ 个整数 $x_1,x_2,\dots,x_k$，第三行输入 $k$ 个整数 $c_1,c_2,\dots,c_k$。

## 输出格式

对于每组数据：

如果不能构造满足所有 $k$ 个条件且长度为 $n$ 的字符串 $s$，输出一行 `NO`；否则，输出 `YES`，然后输出任意一种满足所有条件的 $s$。

## 说明/提示

$1\le t\le10^4$，$3\le n\le2\times10^5$，$1\le k\le20$。

$3\le x_1<x_2<\dots<x_k=n$，$3\le c_1\le c_2\le\dots\le c_k\le\min\left(10^9,\frac{(n+1)n}2\right)$。

每组数据的 $n$ 的总和 $\sum n\le2\times10^5$。

## 样例 #1

### 输入

```
7
10 2
5 10
5 6
3 1
3
3
4 2
3 4
3 3
4 2
3 4
3 4
4 1
4
5
10 3
4 6 10
4 5 8
10 4
4 6 7 10
4 5 7 8
```

### 输出

```
YES
abcbbcabcb
YES
foo
YES
ayda
YES
wada
NO
YES
abcbcacbab
NO
```

