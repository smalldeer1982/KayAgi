---
title: "Centroids"
layout: "post"
diff: 提高+/省选-
pid: CF708C
tag: []
---

# Centroids

## 题目描述

Tree is a connected acyclic graph. Suppose you are given a tree consisting of $ n $ vertices. The vertex of this tree is called centroid if the size of each connected component that appears if this vertex is removed from the tree doesn't exceed ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708C/666f6519688863e0a36337875170dd12050e1c31.png).

You are given a tree of size $ n $ and can perform no more than one edge replacement. Edge replacement is the operation of removing one edge from the tree (without deleting incident vertices) and inserting one new edge (without adding new vertices) in such a way that the graph remains a tree. For each vertex you have to determine if it's possible to make it centroid by performing no more than one edge replacement.

## 输入格式

The first line of the input contains an integer $ n $ ( $ 2<=n<=400000 $ ) — the number of vertices in the tree. Each of the next $ n-1 $ lines contains a pair of vertex indices $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) — endpoints of the corresponding edge.

## 输出格式

Print $ n $ integers. The $ i $ -th of them should be equal to $ 1 $ if the $ i $ -th vertex can be made centroid by replacing no more than one edge, and should be equal to $ 0 $ otherwise.

## 说明/提示

In the first sample each vertex can be made a centroid. For example, in order to turn vertex $ 1 $ to centroid one have to replace the edge $ (2,3) $ with the edge $ (1,3) $ .

## 样例 #1

### 输入

```
3
1 2
2 3

```

### 输出

```
1 1 1 

```

## 样例 #2

### 输入

```
5
1 2
1 3
1 4
1 5

```

### 输出

```
1 0 0 0 0 

```

