---
title: "Replace Character"
layout: "post"
diff: 普及-
pid: CF2047B
tag: ['贪心', '排列组合']
---

# Replace Character

## 题目描述

给定一个长度为 $n$ 的字符串 $s$，只包含小写英文字母。

你只能进行一次如下操作：

- 选择任意两个下标 $i$ 和 $j$ ($1\le i,j\le n$)，允许选择 $i=j$。
- 将 $s_i$ 赋值为 $s_j$。

你需要最小化 $s$ 不同排列的个数。输出在一次操作后满足条件的任何一个字符串 $s$。

字符串的一个排列是打乱其字符顺序后形成的新字符串。比如 `bac` 是 `abc` 的一个排列，而 `bcc` 不是。

## 输入格式

本题有多组数据。第一行，一个整数 $t$ ($1\le t\le 500$)，表示数据组数。

对于每组数据：

第一行，一个整数 $n$ ($1\le n\le 10$)，表示 $s$ 的长度。

第二行，一个长度为 $n$ 的字符串 $s$，只包含小写英文字母。

## 输出格式

对于每组数据，输出一次操作后满足要求的 $s$。如果有多个答案，输出任意一个即可。

翻译：[HYdroKomide](https://www.luogu.com.cn/user/299883)

## 样例 #1

### 输入

```
6
3
abc
4
xyyx
8
alphabet
1
k
10
aabbccddee
6
ttbddq
```

### 输出

```
cbc
yyyx
alphaaet
k
eabbccddee
tttddq
```

