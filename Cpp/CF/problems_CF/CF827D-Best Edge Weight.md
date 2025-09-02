---
title: "Best Edge Weight"
layout: "post"
diff: 省选/NOI-
pid: CF827D
tag: ['深度优先搜索 DFS', '生成树', '动态树 LCT']
---

# Best Edge Weight

## 题目描述

You are given a connected weighted graph with $ n $ vertices and $ m $ edges. The graph doesn't contain loops nor multiple edges. Consider some edge with id $ i $ . Let's determine for this edge the maximum integer weight we can give to it so that it is contained in all minimum spanning trees of the graph if we don't change the other weights.

You are to determine this maximum weight described above for each edge. You should calculate the answer for each edge independently, it means there can't be two edges with changed weights at the same time.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=2·10^{5} $ , $ n-1<=m<=2·10^{5} $ ), where $ n $ and $ m $ are the number of vertices and the number of edges in the graph, respectively.

Each of the next $ m $ lines contains three integers $ u $ , $ v $ and $ c $ ( $ 1<=v,u<=n $ , $ v≠u $ , $ 1<=c<=10^{9} $ ) meaning that there is an edge between vertices $ u $ and $ v $ with weight $ c $ .

## 输出格式

Print the answer for each edge in the order the edges are given in the input. If an edge is contained in every minimum spanning tree with any weight, print -1 as the answer.

## 样例 #1

### 输入

```
4 4
1 2 2
2 3 2
3 4 2
4 1 3

```

### 输出

```
2 2 2 1 
```

## 样例 #2

### 输入

```
4 3
1 2 2
2 3 2
3 4 2

```

### 输出

```
-1 -1 -1 
```

