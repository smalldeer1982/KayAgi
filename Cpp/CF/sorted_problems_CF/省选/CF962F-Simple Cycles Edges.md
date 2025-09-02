---
title: "Simple Cycles Edges"
layout: "post"
diff: 省选/NOI-
pid: CF962F
tag: ['搜索', '枚举', '差分']
---

# Simple Cycles Edges

## 题目描述

You are given an undirected graph, consisting of $ n $ vertices and $ m $ edges. The graph does not necessarily connected. Guaranteed, that the graph does not contain multiple edges (more than one edges between a pair of vertices) or loops (edges from a vertex to itself).

A cycle in a graph is called a simple, if it contains each own vertex exactly once. So simple cycle doesn't allow to visit a vertex more than once in a cycle.

Determine the edges, which belong to exactly on one simple cycle.

## 输入格式

The first line contain two integers $ n $ and $ m $ $ (1 \le n \le 100\,000 $ , $ 0 \le m \le \min(n \cdot (n - 1) / 2, 100\,000)) $ — the number of vertices and the number of edges.

Each of the following $ m $ lines contain two integers $ u $ and $ v $ ( $ 1 \le u, v \le n $ , $ u \neq v $ ) — the description of the edges.

## 输出格式

In the first line print the number of edges, which belong to exactly one simple cycle.

In the second line print the indices of edges, which belong to exactly one simple cycle, in increasing order. The edges are numbered from one in the same order as they are given in the input.

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1

```

### 输出

```
3
1 2 3 

```

## 样例 #2

### 输入

```
6 7
2 3
3 4
4 2
1 2
1 5
5 6
6 1

```

### 输出

```
6
1 2 3 5 6 7 

```

## 样例 #3

### 输入

```
5 6
1 2
2 3
2 4
4 3
2 5
5 3

```

### 输出

```
0


```

