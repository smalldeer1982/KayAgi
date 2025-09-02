---
title: "Mahmoud and Ehab and the bipartiteness"
layout: "post"
diff: 普及+/提高
pid: CF862B
tag: ['二分图']
---

# Mahmoud and Ehab and the bipartiteness

## 题目描述

Mahmoud and Ehab continue their adventures! As everybody in the evil land knows, Dr. Evil likes bipartite graphs, especially trees.

A tree is a connected acyclic graph. A bipartite graph is a graph, whose vertices can be partitioned into $ 2 $ sets in such a way, that for each edge $ (u,v) $ that belongs to the graph, $ u $ and $ v $ belong to different sets. You can find more formal definitions of a tree and a bipartite graph in the notes section below.

Dr. Evil gave Mahmoud and Ehab a tree consisting of $ n $ nodes and asked them to add edges to it in such a way, that the graph is still bipartite. Besides, after adding these edges the graph should be simple (doesn't contain loops or multiple edges). What is the maximum number of edges they can add?

A loop is an edge, which connects a node with itself. Graph doesn't contain multiple edges when for each pair of nodes there is no more than one edge between them. A cycle and a loop aren't the same .

## 输入格式

The first line of input contains an integer $ n $ — the number of nodes in the tree ( $ 1<=n<=10^{5} $ ).

The next $ n-1 $ lines contain integers $ u $ and $ v $ ( $ 1<=u,v<=n $ , $ u≠v $ ) — the description of the edges of the tree.

It's guaranteed that the given graph is a tree.

## 输出格式

Output one integer — the maximum number of edges that Mahmoud and Ehab can add to the tree while fulfilling the conditions.

## 说明/提示

Tree definition: <a>https://en.wikipedia.org/wiki/Tree\_(graph\_theory)</a>

Bipartite graph definition: [https://en.wikipedia.org/wiki/Bipartite\_graph](https://en.wikipedia.org/wiki/Bipartite_graph)

In the first test case the only edge that can be added in such a way, that graph won't contain loops or multiple edges is $ (2,3) $ , but adding this edge will make the graph non-bipartite so the answer is 0.

In the second test case Mahmoud and Ehab can add edges $ (1,4) $ and $ (2,5) $ .

## 样例 #1

### 输入

```
3
1 2
1 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
4 5

```

### 输出

```
2

```

