---
title: "Equalizing Two Strings"
layout: "post"
diff: 普及+/提高
pid: CF1256F
tag: []
---

# Equalizing Two Strings

## 题目描述

### 题意

给你两长度都为 $n$ 的小写字符串 $S, T$。

每次操作中你可以任选一个 $L (1\le L\le n)$，同时翻转 $S$ 中的任意一个长度为 $L$ 的子串和 $T$ 中任意一个长度为 $L$ 的子串。

请回答你是否能在若干次操作后使两字符串一样？

## 输入格式

第一行一个正整数 $q(1\le q\le 10^4)$ 表示询问次数

接下来 $q$ 组数据，每组数据三行，第一行一个正整数 $n(1\le n\le 2\times 10^5)$，第二行一个字符串 $S$，第三行一个字符串 $T$。

保证 $\sum n\le 2\times 10^5$

## 输出格式

$q$ 行，每行一个字符串 ``YES`` 或 ``NO``。

## 样例 #1

### 输入

```
4
4
abcd
abdc
5
ababa
baaba
4
asdf
asdg
4
abcd
badc

```

### 输出

```
NO
YES
NO
YES

```

