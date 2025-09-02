---
title: "Tree and Queries"
layout: "post"
diff: 省选/NOI-
pid: CF375D
tag: ['莫队', '树上启发式合并']
---

# Tree and Queries

## 题目描述

You have a rooted tree consisting of $ n $ vertices. Each vertex of the tree has some color. We will assume that the tree vertices are numbered by integers from 1 to $ n $ . Then we represent the color of vertex $ v $ as $ c_{v} $ . The tree root is a vertex with number 1.

In this problem you need to answer to $ m $ queries. Each query is described by two integers $ v_{j},k_{j} $ . The answer to query $ v_{j},k_{j} $ is the number of such colors of vertices $ x $ , that the subtree of vertex $ v_{j} $ contains at least $ k_{j} $ vertices of color $ x $ .

You can find the definition of a rooted tree by the following link: http://en.wikipedia.org/wiki/Tree\_(graph\_theory).

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (2<=n<=10^{5}; 1<=m<=10^{5}) $ . The next line contains a sequence of integers $ c_{1},c_{2},...,c_{n} $ $ (1<=c_{i}<=10^{5}) $ . The next $ n-1 $ lines contain the edges of the tree. The $ i $ -th line contains the numbers $ a_{i},b_{i} $ $ (1<=a_{i},b_{i}<=n; a_{i}≠b_{i}) $ — the vertices connected by an edge of the tree.

Next $ m $ lines contain the queries. The $ j $ -th line contains two integers $ v_{j},k_{j} $ $ (1<=v_{j}<=n; 1<=k_{j}<=10^{5}) $ .

## 输出格式

Print $ m $ integers — the answers to the queries in the order the queries appear in the input.

## 说明/提示

A subtree of vertex $ v $ in a rooted tree with root $ r $ is a set of vertices $ {u :dist(r,v)+dist(v,u)=dist(r,u)} $ . Where $ dist(x,y) $ is the length (in edges) of the shortest path between vertices $ x $ and $ y $ .

## 样例 #1

### 输入

```
8 5
1 2 2 3 3 2 3 3
1 2
1 5
2 3
2 4
5 6
5 7
5 8
1 2
1 3
1 4
2 3
5 3

```

### 输出

```
2
2
1
0
1

```

## 样例 #2

### 输入

```
4 1
1 2 3 4
1 2
2 3
3 4
1 1

```

### 输出

```
4

```

