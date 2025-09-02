---
title: "st-Spanning Tree"
layout: "post"
diff: 提高+/省选-
pid: CF723F
tag: []
---

# st-Spanning Tree

## 题目描述

You are given an undirected connected graph consisting of $ n $ vertices and $ m $ edges. There are no loops and no multiple edges in the graph.

You are also given two distinct vertices $ s $ and $ t $ , and two values $ d_{s} $ and $ d_{t} $ . Your task is to build any spanning tree of the given graph (note that the graph is not weighted), such that the degree of the vertex $ s $ doesn't exceed $ d_{s} $ , and the degree of the vertex $ t $ doesn't exceed $ d_{t} $ , or determine, that there is no such spanning tree.

The spanning tree of the graph $ G $ is a subgraph which is a tree and contains all vertices of the graph $ G $ . In other words, it is a connected graph which contains $ n-1 $ edges and can be obtained by removing some of the edges from $ G $ .

The degree of a vertex is the number of edges incident to this vertex.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 2<=n<=200000 $ , $ 1<=m<=min(400000,n·(n-1)/2) $ ) — the number of vertices and the number of edges in the graph.

The next $ m $ lines contain the descriptions of the graph's edges. Each of the lines contains two integers $ u $ and $ v $ ( $ 1<=u,v<=n $ , $ u≠v $ ) — the ends of the corresponding edge. It is guaranteed that the graph contains no loops and no multiple edges and that it is connected.

The last line contains four integers $ s $ , $ t $ , $ d_{s} $ , $ d_{t} $ ( $ 1<=s,t<=n $ , $ s≠t $ , $ 1<=d_{s},d_{t}<=n-1 $ ).

## 输出格式

If the answer doesn't exist print "No" (without quotes) in the only line of the output.

Otherwise, in the first line print "Yes" (without quotes). In the each of the next $ (n-1) $ lines print two integers — the description of the edges of the spanning tree. Each of the edges of the spanning tree must be printed exactly once.

You can output edges in any order. You can output the ends of each edge in any order.

If there are several solutions, print any of them.

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1
1 2 1 1

```

### 输出

```
Yes
3 2
1 3

```

## 样例 #2

### 输入

```
7 8
7 4
1 3
5 4
5 7
3 2
2 4
6 1
1 2
6 4 1 4

```

### 输出

```
Yes
1 3
5 7
3 2
7 4
2 4
6 1

```

