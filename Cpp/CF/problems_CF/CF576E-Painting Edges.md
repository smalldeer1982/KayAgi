---
title: "Painting Edges"
layout: "post"
diff: 省选/NOI-
pid: CF576E
tag: ['线段树', '分治', '栈']
---

# Painting Edges

## 题目描述

Note the unusual memory limit for this problem.

You are given an undirected graph consisting of $ n $ vertices and $ m $ edges. The vertices are numbered with integers from $ 1 $ to $ n $ , the edges are numbered with integers from $ 1 $ to $ m $ . Each edge can be unpainted or be painted in one of the $ k $ colors, which are numbered with integers from $ 1 $ to $ k $ . Initially, none of the edges is painted in any of the colors.

You get queries of the form "Repaint edge $ e_{i} $ to color $ c_{i} $ ". At any time the graph formed by the edges of the same color must be bipartite. If after the repaint this condition is violated, then the query is considered to be invalid and edge $ e_{i} $ keeps its color. Otherwise, edge $ e_{i} $ is repainted in color $ c_{i} $ , and the query is considered to valid.

Recall that the graph is called bipartite if the set of its vertices can be divided into two parts so that no edge connected vertices of the same parts.

For example, suppose you are given a triangle graph, that is a graph with three vertices and edges $ (1,2) $ , $ (2,3) $ and $ (3,1) $ . Suppose that the first two edges are painted color $ 1 $ , and the third one is painted color $ 2 $ . Then the query of "repaint the third edge in color $ 1 $ " will be incorrect because after its execution the graph formed by the edges of color $ 1 $ will not be bipartite. On the other hand, it is possible to repaint the second edge in color $ 2 $ .

You receive $ q $ queries. For each query, you should either apply it, and report that the query is valid, or report that the query is invalid.

## 输入格式

The first line contains integers $ n $ , $ m $ , $ k $ , $ q $ ( $ 2<=n<=5·10^{5} $ , $ 1<=m,q<=5·10^{5} $ , $ 1<=k<=50 $ ) — the number of vertices, the number of edges, the number of colors and the number of queries.

Then follow $ m $ edges of the graph in the form $ a_{i} $ , $ b_{i} $ ( $ 1<=a_{i},b_{i}<=n $ ).

Then follow $ q $ queries of the form $ e_{i} $ , $ c_{i} $ ( $ 1<=e_{i}<=m $ , $ 1<=c_{i}<=k $ ).

It is guaranteed that the graph doesn't contain multiple edges and loops.

## 输出格式

For each query print "YES" (without the quotes), if it is valid, or "NO" (without the quotes), if this query destroys the bipartivity of the graph formed by the edges of some color.

## 样例 #1

### 输入

```
3 3 2 5
1 2
2 3
1 3
1 1
2 1
3 2
3 1
2 2

```

### 输出

```
YES
YES
YES
NO
YES

```

