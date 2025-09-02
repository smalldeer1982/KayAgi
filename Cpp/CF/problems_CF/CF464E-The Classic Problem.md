---
title: "The Classic Problem"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF464E
tag: ['最短路', '可持久化线段树', '哈希 hashing']
---

# The Classic Problem

## 题目描述

You are given a weighted undirected graph on $ n $ vertices and $ m $ edges. Find the shortest path from vertex $ s $ to vertex $ t $ or else state that such path doesn't exist.

## 输入格式

The first line of the input contains two space-separated integers — $ n $ and $ m $ ( $ 1<=n<=10^{5} $ ; $ 0<=m<=10^{5} $ ).

Next $ m $ lines contain the description of the graph edges. The $ i $ -th line contains three space-separated integers — $ u_{i} $ , $ v_{i} $ , $ x_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ; $ 0<=x_{i}<=10^{5} $ ). That means that vertices with numbers $ u_{i} $ and $ v_{i} $ are connected by edge of length $ 2^{x_{i}} $ (2 to the power of $ x_{i} $ ).

The last line contains two space-separated integers — the numbers of vertices $ s $ and $ t $ .

The vertices are numbered from $ 1 $ to $ n $ . The graph contains no multiple edges and self-loops.

## 输出格式

In the first line print the remainder after dividing the length of the shortest path by $ 1000000007 (10^{9}+7) $ if the path exists, and -1 if the path doesn't exist.

If the path exists print in the second line integer $ k $ — the number of vertices in the shortest path from vertex $ s $ to vertex $ t $ ; in the third line print $ k $ space-separated integers — the vertices of the shortest path in the visiting order. The first vertex should be vertex $ s $ , the last vertex should be vertex $ t $ . If there are multiple shortest paths, print any of them.

## 说明/提示

A path from vertex $ s $ to vertex $ t $ is a sequence $ v_{0} $ , ..., $ v_{k} $ , such that $ v_{0}=s $ , $ v_{k}=t $ , and for any $ i $ from 0 to $ k-1 $ vertices $ v_{i} $ and $ v_{i+1} $ are connected by an edge.

The length of the path is the sum of weights of edges between $ v_{i} $ and $ v_{i+1} $ for all $ i $ from 0 to $ k-1 $ .

The shortest path from $ s $ to $ t $ is the path which length is minimum among all possible paths from $ s $ to $ t $ .

## 样例 #1

### 输入

```
4 4
1 4 2
1 2 0
2 3 0
3 4 0
1 4

```

### 输出

```
3
4
1 2 3 4 

```

## 样例 #2

### 输入

```
4 3
1 2 4
2 3 5
3 4 6
1 4

```

### 输出

```
112
4
1 2 3 4 

```

## 样例 #3

### 输入

```
4 2
1 2 0
3 4 1
1 4

```

### 输出

```
-1

```

