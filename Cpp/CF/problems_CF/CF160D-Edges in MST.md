---
title: "Edges in MST"
layout: "post"
diff: 省选/NOI-
pid: CF160D
tag: ['线段树', '并查集', '生成树', '连通块']
---

# Edges in MST

## 题目描述

You are given a connected weighted undirected graph without any loops and multiple edges.

Let us remind you that a graph's spanning tree is defined as an acyclic connected subgraph of the given graph that includes all of the graph's vertexes. The weight of a tree is defined as the sum of weights of the edges that the given tree contains. The minimum spanning tree (MST) of a graph is defined as the graph's spanning tree having the minimum possible weight. For any connected graph obviously exists the minimum spanning tree, but in the general case, a graph's minimum spanning tree is not unique.

Your task is to determine the following for each edge of the given graph: whether it is either included in any MST, or included at least in one MST, or not included in any MST.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=10^{5} $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF160D/1841eb9adb257200301ec3daad18abd00c456982.png)) — the number of the graph's vertexes and edges, correspondingly. Then follow $ m $ lines, each of them contains three integers — the description of the graph's edges as " $ a_{i} $ $ b_{i} $ $ w_{i} $ " ( $ 1<=a_{i},b_{i}<=n,1<=w_{i}<=10^{6},a_{i}≠b_{i} $ ), where $ a_{i} $ and $ b_{i} $ are the numbers of vertexes connected by the $ i $ -th edge, $ w_{i} $ is the edge's weight. It is guaranteed that the graph is connected and doesn't contain loops or multiple edges.

## 输出格式

Print $ m $ lines — the answers for all edges. If the $ i $ -th edge is included in any MST, print "any"; if the $ i $ -th edge is included at least in one MST, print "at least one"; if the $ i $ -th edge isn't included in any MST, print "none". Print the answers for the edges in the order in which the edges are specified in the input.

## 说明/提示

In the second sample the MST is unique for the given graph: it contains two first edges.

In the third sample any two edges form the MST for the given graph. That means that each edge is included at least in one MST.

## 样例 #1

### 输入

```
4 5
1 2 101
1 3 100
2 3 2
2 4 2
3 4 1

```

### 输出

```
none
any
at least one
at least one
any

```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 1
1 3 2

```

### 输出

```
any
any
none

```

## 样例 #3

### 输入

```
3 3
1 2 1
2 3 1
1 3 1

```

### 输出

```
at least one
at least one
at least one

```

