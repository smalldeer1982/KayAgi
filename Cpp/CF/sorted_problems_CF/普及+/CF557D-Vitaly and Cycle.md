---
title: "Vitaly and Cycle"
layout: "post"
diff: 普及+/提高
pid: CF557D
tag: []
---

# Vitaly and Cycle

## 题目描述

After Vitaly was expelled from the university, he became interested in the graph theory.

Vitaly especially liked the cycles of an odd length in which each vertex occurs at most once.

Vitaly was wondering how to solve the following problem. You are given an undirected graph consisting of $ n $ vertices and $ m $ edges, not necessarily connected, without parallel edges and loops. You need to find $ t $ — the minimum number of edges that must be added to the given graph in order to form a simple cycle of an odd length, consisting of more than one vertex. Moreover, he must find $ w $ — the number of ways to add $ t $ edges in order to form a cycle of an odd length (consisting of more than one vertex). It is prohibited to add loops or parallel edges.

Two ways to add edges to the graph are considered equal if they have the same sets of added edges.

Since Vitaly does not study at the university, he asked you to help him with this task.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF557D/8231a822605c1073127681be1ea7f20d9b0e33dd.png) — the number of vertices in the graph and the number of edges in the graph.

Next $ m $ lines contain the descriptions of the edges of the graph, one edge per line. Each edge is given by a pair of integers $ a_{i} $ , $ b_{i} $ ( $ 1<=a_{i},b_{i}<=n $ ) — the vertices that are connected by the $ i $ -th edge. All numbers in the lines are separated by a single space.

It is guaranteed that the given graph doesn't contain any loops and parallel edges. The graph isn't necessarily connected.

## 输出格式

Print in the first line of the output two space-separated integers $ t $ and $ w $ — the minimum number of edges that should be added to the graph to form a simple cycle of an odd length consisting of more than one vertex where each vertex occurs at most once, and the number of ways to do this.

## 说明/提示

The simple cycle is a cycle that doesn't contain any vertex twice.

## 样例 #1

### 输入

```
4 4
1 2
1 3
4 2
4 3

```

### 输出

```
1 2

```

## 样例 #2

### 输入

```
3 3
1 2
2 3
3 1

```

### 输出

```
0 1

```

## 样例 #3

### 输入

```
3 0

```

### 输出

```
3 1

```

