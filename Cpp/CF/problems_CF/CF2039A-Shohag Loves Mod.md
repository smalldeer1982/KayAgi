---
title: "Shohag Loves Mod"
layout: "post"
diff: 普及-
pid: CF2039A
tag: ['数论', '构造']
---

# Shohag Loves Mod

## 题目描述

Shohag 有一个整数 $n$，请帮助他找到一个升序序列 $1\le a_1< a_2<\cdots<a_n\le100$，使得对于所有满足 $1\le i < j \le n$ 的数对 $(i,j)$，都满足 $a_i \bmod i\neq a_j \bmod j$。

可以证明，在给定限制下，一定存在合法的序列。

$a\bmod b$ 表示 $a$ 除以 $b$ 的余数。比如，$7\bmod 3=1, 8\bmod 4=0, 69\bmod 10=9$。

## 输入格式

第一行，一个整数 $t$（$1\le t\le 50$） 表示数据组数。

对于每组数据，输入一行，一个整数 $n$（$2\le n\le 50$）。

## 输出格式

对于每组数据，输出 $n$ 个整数，表示符合题目条件的一个序列。如果有多个符合条件的序列，输出任意一个即可。

翻译：[HYdroKomide](https://www.luogu.com.cn/user/299883)

## 样例 #1

### 输入

```
2
3
6
```

### 输出

```
2 7 8
2 3 32 35 69 95
```

