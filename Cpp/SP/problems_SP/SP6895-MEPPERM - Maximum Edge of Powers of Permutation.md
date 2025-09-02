---
title: "MEPPERM - Maximum Edge of Powers of Permutation"
layout: "post"
diff: 难度0
pid: SP6895
tag: []
---

# MEPPERM - Maximum Edge of Powers of Permutation

## 题目描述

在一个有向图 $G$ 中，每个顶点 $v$ 具有两个权重值 $A_v$ 和 $B_v$。我们定义一条边 $(u, v)$ 的权重为 $A_u + B_v$。我们用 $MaxEdge(G)$ 表示图 $G$ 中所有边中的最大权重。

给定一个排列 $P$，它是在 $1$ 到 $n$ 上的一个排列，我们可以根据排列 $P$ 构造一个有向图 $G = (V, E)$，其中 $V = \{1, 2, \ldots, n\}$，且当且仅当 $P(u) = v$ 时，边 $(u, v)$ 包含在 $E$ 中。现在，你需要计算 $MaxEdge(P^k)$，其中 $k$ 从 $0$ 到 $q-1$。

## 输入格式

第一行是一个正整数 $n$，表示排列的大小。  
第二行包含 $n$ 个整数，表示排列 $P$。  
第三行包含 $n$ 个自然数，分别为 $A_1, A_2, \ldots, A_n$。  
第四行包含 $n$ 个自然数，分别为 $B_1, B_2, \ldots, B_n$。  
第五行是一个正整数 $q$，表示查询的次数。

## 输出格式

输出一行，包含 $q$ 个整数：分别表示从 $P^0$ 到 $P^{q-1}$ 的 $MaxEdge$ 值，用空格隔开。

## 说明/提示

- $1 \le n \le 10^5$
- $1 \le q \le 10^5$
- $1 \le P_i \le n$
- $1 \le A_i, B_i \le 10^9$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n3\n3 2 1\n0 1 2\n2 2 0\n5\n\n
```

### 输出

```
\n3 4 3 4 3\n
```

