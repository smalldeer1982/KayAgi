---
title: "STRLCP - Longest Common Prefix"
layout: "post"
diff: 省选/NOI-
pid: SP3109
tag: []
---

# STRLCP - Longest Common Prefix

## 题目描述

定义两个字符串 $A[1 \dots la]$ 和 $B[1 \dots lb]$ 的 LCP（最长公共前缀）为LCP(A[1..la],B[1..lb]) = max{L | L<=la && L<=lb && A[1..L] == B[1..L]}

$LCP(A[1 \dots la], B[1 \dots lb]) = \mathrm{max}(L\ |\ L \leq la, L \leq lb, A[1 \dots L] = B[1 \dots L])$

给出一个原始字符串和几个操作，写出一个程序来处理它们。

## 输入格式

第一行为测试数据个数 $T$。

每个测试数据的第一行是一个长度为 $L$ 的字符串 $S \ (1 \leq L \leq 100000)$。

第二行包含一个整数 $Q \ (1 \leq Q \leq 150000)$，代表操作的数量。

接下来的 $Q$ 行，每行代表一个操作：

- $Q\ i\ j$：输出 $\mathrm{LCP}(S[i \dots l], S[j \dots l])$
- $R\ i\ char$：用 $char$ 替换 $S$ 的第 $i$ 个字符
- $I\ i\ char$： 在 $S$ 的第 $i$ 个字符后插入 $char$

## 输出格式

对于每个 $Q\ i\ j$ 操作，输出答案。

## 样例 #1

### 输入

```
1
madamimadam
7
Q 1 7
Q 4 8
Q 10 11
R 3 a
Q 1 7
I 10 a
Q 2 11
```

### 输出

```
5
1
0
2
1
```

