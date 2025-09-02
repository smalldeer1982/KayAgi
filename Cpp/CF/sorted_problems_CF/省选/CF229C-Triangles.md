---
title: "Triangles"
layout: "post"
diff: 省选/NOI-
pid: CF229C
tag: []
---

# Triangles

## 题目描述

Alice and Bob don't play games anymore. Now they study properties of all sorts of graphs together. Alice invented the following task: she takes a complete undirected graph with $ n $ vertices, chooses some $ m $ edges and keeps them. Bob gets the ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF229C/4408e88d41b3075c330afb5b8cbb30c34ea57359.png) remaining edges.

Alice and Bob are fond of "triangles" in graphs, that is, cycles of length 3. That's why they wonder: what total number of triangles is there in the two graphs formed by Alice and Bob's edges, correspondingly?

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ ( $ 1<=n<=10^{6},0<=m<=10^{6} $ ) — the number of vertices in the initial complete graph and the number of edges in Alice's graph, correspondingly. Then $ m $ lines follow: the $ i $ -th line contains two space-separated integers $ a_{i} $ , $ b_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ a_{i}≠b_{i} $ ), — the numbers of the two vertices connected by the $ i $ -th edge in Alice's graph. It is guaranteed that Alice's graph contains no multiple edges and self-loops. It is guaranteed that the initial complete graph also contains no multiple edges and self-loops.

Consider the graph vertices to be indexed in some way from 1 to $ n $ .

## 输出格式

Print a single number — the total number of cycles of length 3 in Alice and Bob's graphs together.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is advised to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first sample Alice has 2 triangles: (1, 2, 3) and (2, 3, 4). Bob's graph has only 1 triangle : (1, 4, 5). That's why the two graphs in total contain 3 triangles.

In the second sample Alice's graph has only one triangle: (1, 2, 3). Bob's graph has three triangles: (1, 4, 5), (2, 4, 5) and (3, 4, 5). In this case the answer to the problem is 4.

## 样例 #1

### 输入

```
5 5
1 2
1 3
2 3
2 4
3 4

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 3
1 2
2 3
1 3

```

### 输出

```
4

```

