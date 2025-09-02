---
title: "Replace With the Previous, Minimize"
layout: "post"
diff: 普及/提高-
pid: CF1675E
tag: ['贪心']
---

# Replace With the Previous, Minimize

## 题目描述

### 题意简述

有一个长度为 $n$ 的，只含小写字母的字符串 $s$，每次操作可以选择 $26$ 个字母之一，将字符串中所有该字母替换为上一个字母（如 $\texttt{c}\to\texttt{b},\texttt{b}\to\texttt{a}$，特殊地，$\texttt{a}\to\texttt{z}$）。在 $k$ 次操作**之内**，使得到的字符串的字典序最小。

## 输入格式

第一行一个正整数 $t$ 表示数据组数。

对于每组数据，第一行两个正整数 $n,k$，第二行一个字符串 $s$。

## 输出格式

对于每组数据，输出一行一个字符串表示答案。

### 数据规模

$n\le 2\times 10^5,k\le 10^9,\sum n\le 2\times 10^5$

## 样例 #1

### 输入

```
4
3 2
cba
4 5
fgde
7 5
gndcafb
4 19
ekyv
```

### 输出

```
aaa
agaa
bnbbabb
aapp
```

