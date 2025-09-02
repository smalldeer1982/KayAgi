---
title: "Vulnerable Kerbals"
layout: "post"
diff: 提高+/省选-
pid: CF772C
tag: []
---

# Vulnerable Kerbals

## 题目描述

给出两个整数 $n, m$，在给出一个大小为 $n$ 的集合 $B$，且 $\forall y \in B$ 有 $0 \leq y < m$。现要求构造一个序列 $A$，满足以下条件：

- $\forall x \in A$ 有 $0 \leq x < m$。
- $\forall i, j, 1 \leq i, j \leq |A|$， 有 $\prod \limits _{k = 1}^{i}A_k \not\equiv \prod \limits _{k = 1}^{j}A_k \pmod m$
- $\forall i, y, 1 \leq i \leq |A|, y \in B$， 有 $\prod \limits _{k = 1}^{i}A_k \not\equiv y \pmod m$

在序列 $A$ 合法的条件下满足长度最大化，并给出一种构造方案。

## 输入格式

第一行两个整数 $n, m$。

第二行（若 $n = 0$ 则没有）输入 $n$ 个整数，表示集合 $B$。

## 输出格式

第一行一个整数，表示序列 $A$ 的最大长度 $|A|$。

第二行 $|A|$ 个整数，表示序列 $A$。

## 说明/提示

$0 \leq n, m \leq 2 \times 10^5$。

## 样例 #1

### 输入

```
0 5

```

### 输出

```
5
1 2 4 3 0

```

## 样例 #2

### 输入

```
3 10
2 9 1

```

### 输出

```
6
3 9 2 9 8 0

```

