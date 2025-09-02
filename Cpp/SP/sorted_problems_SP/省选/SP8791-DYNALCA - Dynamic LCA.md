---
title: "DYNALCA - Dynamic LCA"
layout: "post"
diff: 省选/NOI-
pid: SP8791
tag: []
---

# DYNALCA - Dynamic LCA

## 题目描述

A forest of rooted trees initially consists of N (1

You must process the following queries, where (1

- **link** A B : add an edge from vertex A to B, making A a child of B, where initially A is a root vertex, A and B are in different trees.
- **cut** A : remove edge from A to its parent, where initially A is a non-root vertex.
- **lca** A B : print the lowest common ancestor of A and B, where A and B are in the same tree.

## 输入格式

The first line of input contains the number of initial single-vertex trees N and the number of queries M (1

## 输出格式

For each **lca** query output the lowest common ancestor (vertex number between 1 and N).

## 样例 #1

### 输入

```
5 9
lca 1 1
link 1 2
link 3 2
link 4 3
lca 1 4
lca 3 4
cut 4
link 5 3
lca 1 5
```

### 输出

```
1
2
3
2
```

