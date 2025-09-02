---
title: "MAXOR - MAXOR"
layout: "post"
diff: 省选/NOI-
pid: SP11444
tag: []
---

# MAXOR - MAXOR

## 题目描述

### 题目大意

给出一个序列 $a_1,a_2,...a_n$ 。

对于一个询问的区间 $(l,r)$ ，需要求出 $\max(a_i  \oplus a_{i+1} \oplus a_{i+2} \oplus ... \oplus a_j)$ 其中 $l \le i \le j \le r$ 。（这里的 $\oplus$ 代表异或）。

现在给出若干个 $(x,y)$ ，则定义查询区间 $(l,r)$ 为

$l=\min((x+lastans) \mod n+1,(y+lastans) \mod n+1 )$

$r=\max((x+lastans) \mod n+1,(y+lastans) \mod n+1 )$

其中 $lastans$ 表示上一次查询的答案。而对于第一次查询， $lastans$ 为 $0$ 。

## 输入格式

第一行，两个数 $n,m$ 。表示有 $n$ 个数和 $m$ 个查询。

第二行有 $n$ 个数，表示序列。

第三行开始有 $m$ 行，每行两个数表示 $(x,y)$ 。

## 输出格式

$m$ 行。一行一个数表示查询的最大值。

## 说明/提示

- $n\le1.2\times10^4$。
- $0\le a_i<2^{31}$。
- $m\le 6\times10^3$。

## 样例 #1

### 输入

```
3 3
1 4 3
0 1
0 1
4 3
```

### 输出

```
5
7
7
```

