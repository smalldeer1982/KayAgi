---
title: "Leaf Sets"
layout: "post"
diff: 提高+/省选-
pid: CF1042F
tag: []
---

# Leaf Sets

## 题目描述

You are given an undirected tree, consisting of $ n $ vertices.

The vertex is called a leaf if it has exactly one vertex adjacent to it.

The distance between some pair of vertices is the number of edges in the shortest path between them.

Let's call some set of leaves beautiful if the maximum distance between any pair of leaves in it is less or equal to $ k $ .

You want to split all leaves into non-intersecting beautiful sets. What is the minimal number of sets in such a split?

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 3 \le n \le 10^6 $ , $ 1 \le k \le 10^6 $ ) — the number of vertices in the tree and the maximum distance between any pair of leaves in each beautiful set.

Each of the next $ n - 1 $ lines contains two integers $ v_i $ and $ u_i $ ( $ 1 \le v_i, u_i \le n $ ) — the description of the $ i $ -th edge.

It is guaranteed that the given edges form a tree.

## 输出格式

Print a single integer — the minimal number of beautiful sets the split can have.

## 说明/提示

Here is the graph for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1042F/5a707ac956bf7a0b2ca96d67d4d3ef782292e2c3.png)

## 样例 #1

### 输入

```
9 3
1 2
1 3
2 4
2 5
3 6
6 7
6 8
3 9

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 3
1 2
2 3
3 4
4 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
6 1
1 2
1 3
1 4
1 5
1 6

```

### 输出

```
5

```

