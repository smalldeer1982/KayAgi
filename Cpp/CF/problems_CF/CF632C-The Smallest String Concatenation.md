---
title: "The Smallest String Concatenation"
layout: "post"
diff: 普及+/提高
pid: CF632C
tag: []
---

# The Smallest String Concatenation

## 题目描述

给定 $n$ 个字符串，第 $i$ 个字符串为 $a_i$。求出一种依次连接这 $n$ 个字符串的顺序，使连接而成的字符串满足字典序最小。

## 输入格式

第一行输入一个数 $n(1\leq n\leq 5\times 10^4)$，表示字符串数量。

接下来 $n$ 行中，每行输入一个小写英文字母串 $a_i(1\leq |a_i|\leq 50)$，字符串长度总和不超过 $5 \times 10^4$。

## 输出格式

输出一行，包含一个字符串，为连接后字典序最小的字符串。

## 样例 #1

### 输入

```
4
abba
abacaba
bcd
er

```

### 输出

```
abacabaabbabcder

```

## 样例 #2

### 输入

```
5
x
xx
xxa
xxaa
xxaaa

```

### 输出

```
xxaaaxxaaxxaxxx

```

## 样例 #3

### 输入

```
3
c
cb
cba

```

### 输出

```
cbacbc

```

