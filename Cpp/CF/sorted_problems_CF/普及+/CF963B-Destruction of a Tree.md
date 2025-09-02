---
title: "Destruction of a Tree"
layout: "post"
diff: 普及+/提高
pid: CF963B
tag: ['搜索']
---

# Destruction of a Tree

## 题目描述

You are given a tree (a graph with $ n $ vertices and $ n-1 $ edges in which it's possible to reach any vertex from any other vertex using only its edges).

A vertex can be destroyed if this vertex has even degree. If you destroy a vertex, all edges connected to it are also deleted.

Destroy all vertices in the given tree or determine that it is impossible.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=2·10^{5} $ ) — number of vertices in a tree.

The second line contains $ n $ integers $ p_{1},p_{2},...,p_{n} $ ( $ 0<=p_{i}<=n $ ). If $ p_{i}≠0 $ there is an edge between vertices $ i $ and $ p_{i} $ . It is guaranteed that the given graph is a tree.

## 输出格式

If it's possible to destroy all vertices, print "YES" (without quotes), otherwise print "NO" (without quotes).

If it's possible to destroy all vertices, in the next $ n $ lines print the indices of the vertices in order you destroy them. If there are multiple correct answers, print any.

## 说明/提示

In the first example at first you have to remove the vertex with index 1 (after that, the edges (1, 2) and (1, 4) are removed), then the vertex with index 2 (and edges (2, 3) and (2, 5) are removed). After that there are no edges in the tree, so you can remove remaining vertices in any order.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF963B/9b84e98fe96447b82c6a8ccba7a9e4a5189ce14b.png)

## 样例 #1

### 输入

```
5
0 1 2 1 2

```

### 输出

```
YES
1
2
3
5
4

```

## 样例 #2

### 输入

```
4
0 1 2 3

```

### 输出

```
NO

```

