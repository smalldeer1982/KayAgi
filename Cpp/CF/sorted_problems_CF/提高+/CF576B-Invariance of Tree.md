---
title: "Invariance of Tree"
layout: "post"
diff: 提高+/省选-
pid: CF576B
tag: []
---

# Invariance of Tree

## 题目描述

A tree of size $ n $ is an undirected connected graph consisting of $ n $ vertices without cycles.

Consider some tree with $ n $ vertices. We call a tree invariant relative to permutation $ p=p_{1}p_{2}...\ p_{n} $ , if for any two vertices of the tree $ u $ and $ v $ the condition holds: "vertices $ u $ and $ v $ are connected by an edge if and only if vertices $ p_{u} $ and $ p_{v} $ are connected by an edge".

You are given permutation $ p $ of size $ n $ . Find some tree size $ n $ , invariant relative to the given permutation.

## 输入格式

The first line contains number $ n $ ( $ 1<=n<=10^{5} $ ) — the size of the permutation (also equal to the size of the sought tree).

The second line contains permutation $ p_{i} $ ( $ 1<=p_{i}<=n $ ).

## 输出格式

If the sought tree does not exist, print "NO" (without the quotes).

Otherwise, print "YES", and then print $ n-1 $ lines, each of which contains two integers — the numbers of vertices connected by an edge of the tree you found. The vertices are numbered from 1, the order of the edges and the order of the vertices within the edges does not matter.

If there are multiple solutions, output any of them.

## 说明/提示

In the first sample test a permutation transforms edge (4, 1) into edge (1, 4), edge (4, 2) into edge (1, 3) and edge (1, 3) into edge (4, 2). These edges all appear in the resulting tree.

It can be shown that in the second sample test no tree satisfies the given condition.

## 样例 #1

### 输入

```
4
4 3 2 1

```

### 输出

```
YES
4 1
4 2
1 3

```

## 样例 #2

### 输入

```
3
3 1 2

```

### 输出

```
NO

```

