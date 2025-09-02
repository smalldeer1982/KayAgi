---
title: "Xenia and Tree"
layout: "post"
diff: 省选/NOI-
pid: CF342E
tag: []
---

# Xenia and Tree

## 题目描述

Xenia the programmer has a tree consisting of $ n $ nodes. We will consider the tree nodes indexed from 1 to $ n $ . We will also consider the first node to be initially painted red, and the other nodes — to be painted blue.

The distance between two tree nodes $ v $ and $ u $ is the number of edges in the shortest path between $ v $ and $ u $ .

Xenia needs to learn how to quickly execute queries of two types:

1. paint a specified blue node in red;
2. calculate which red node is the closest to the given one and print the shortest distance to the closest red node.

Your task is to write a program which will execute the described queries.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (2<=n<=10^{5},1<=m<=10^{5}) $ — the number of nodes in the tree and the number of queries. Next $ n-1 $ lines contain the tree edges, the $ i $ -th line contains a pair of integers $ a_{i},b_{i} $ $ (1<=a_{i},b_{i}<=n,a_{i}≠b_{i}) $ — an edge of the tree.

Next $ m $ lines contain queries. Each query is specified as a pair of integers $ t_{i},v_{i} $ $ (1<=t_{i}<=2,1<=v_{i}<=n) $ . If $ t_{i}=1 $ , then as a reply to the query we need to paint a blue node $ v_{i} $ in red. If $ t_{i}=2 $ , then we should reply to the query by printing the shortest distance from some red node to node $ v_{i} $ .

It is guaranteed that the given graph is a tree and that all queries are correct.

## 输出格式

For each second type query print the reply in a single line.

## 样例 #1

### 输入

```
5 4
1 2
2 3
2 4
4 5
2 1
2 5
1 2
2 5

```

### 输出

```
0
3
2

```

