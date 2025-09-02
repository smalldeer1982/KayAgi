---
title: "Cactus"
layout: "post"
diff: 省选/NOI-
pid: CF231E
tag: []
---

# Cactus

## 题目描述

A connected undirected graph is called a vertex cactus, if each vertex of this graph belongs to at most one simple cycle.

A simple cycle in a undirected graph is a sequence of distinct vertices $ v_{1},v_{2},...,v_{t} $ $ (t&gt;2) $ , such that for any $ i $ $ (1<=i&lt;t) $ exists an edge between vertices $ v_{i} $ and $ v_{i+1} $ , and also exists an edge between vertices $ v_{1} $ and $ v_{t} $ .

A simple path in a undirected graph is a sequence of not necessarily distinct vertices $ v_{1},v_{2},...,v_{t} $ $ (t&gt;0) $ , such that for any $ i $ $ (1<=i&lt;t) $ exists an edge between vertices $ v_{i} $ and $ v_{i+1} $ and furthermore each edge occurs no more than once. We'll say that a simple path $ v_{1},v_{2},...,v_{t} $ starts at vertex $ v_{1} $ and ends at vertex $ v_{t} $ .

You've got a graph consisting of $ n $ vertices and $ m $ edges, that is a vertex cactus. Also, you've got a list of $ k $ pairs of interesting vertices $ x_{i},y_{i} $ , for which you want to know the following information — the number of distinct simple paths that start at vertex $ x_{i} $ and end at vertex $ y_{i} $ . We will consider two simple paths distinct if the sets of edges of the paths are distinct.

For each pair of interesting vertices count the number of distinct simple paths between them. As this number can be rather large, you should calculate it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line contains two space-separated integers $ n,m $ $ (2<=n<=10^{5}; 1<=m<=10^{5}) $ — the number of vertices and edges in the graph, correspondingly. Next $ m $ lines contain the description of the edges: the $ i $ -th line contains two space-separated integers $ a_{i},b_{i} $ $ (1<=a_{i},b_{i}<=n) $ — the indexes of the vertices connected by the $ i $ -th edge.

The next line contains a single integer $ k $ $ (1<=k<=10^{5}) $ — the number of pairs of interesting vertices. Next $ k $ lines contain the list of pairs of interesting vertices: the $ i $ -th line contains two space-separated numbers $ x_{i} $ , $ y_{i} $ $ (1<=x_{i},y_{i}<=n; x_{i}≠y_{i}) $ — the indexes of interesting vertices in the $ i $ -th pair.

It is guaranteed that the given graph is a vertex cactus. It is guaranteed that the graph contains no loops or multiple edges. Consider the graph vertices are numbered from 1 to $ n $ .

## 输出格式

Print $ k $ lines: in the $ i $ -th line print a single integer — the number of distinct simple ways, starting at $ x_{i} $ and ending at $ y_{i} $ , modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
10 11
1 2
2 3
3 4
1 4
3 5
5 6
8 6
8 7
7 6
7 9
9 10
6
1 2
3 5
6 9
9 2
9 3
9 10

```

### 输出

```
2
2
2
4
4
1

```

