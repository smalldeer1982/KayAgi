---
title: "Three Trees"
layout: "post"
diff: 难度0
pid: CF391E1
tag: []
---

# Three Trees

## 题目描述

This problem consists of two subproblems: for solving subproblem E1 you will receive 11 points, and for solving subproblem E2 you will receive 13 points.

A tree is an undirected connected graph containing no cycles. The distance between two nodes in an unweighted tree is the minimum number of edges that have to be traversed to get from one node to another.

You are given 3 trees that have to be united into a single tree by adding two edges between these trees. Each of these edges can connect any pair of nodes from two trees. After the trees are connected, the distances between all unordered pairs of nodes in the united tree should be computed. What is the maximum possible value of the sum of these distances?

## 输入格式

The first line contains three space-separated integers $ n_{1} $ , $ n_{2} $ , $ n_{3} $ — the number of vertices in the first, second, and third trees, respectively. The following $ n_{1}-1 $ lines describe the first tree. Each of these lines describes an edge in the first tree and contains a pair of integers separated by a single space — the numeric labels of vertices connected by the edge. The following $ n_{2}-1 $ lines describe the second tree in the same fashion, and the $ n_{3}-1 $ lines after that similarly describe the third tree. The vertices in each tree are numbered with consecutive integers starting with $ 1 $ .

The problem consists of two subproblems. The subproblems have different constraints on the input. You will get some score for the correct submission of the subproblem. The description of the subproblems follows.

- In subproblem E1 (11 points), the number of vertices in each tree will be between $ 1 $ and $ 1000 $ , inclusive.
- In subproblem E2 (13 points), the number of vertices in each tree will be between $ 1 $ and $ 100000 $ , inclusive.

## 输出格式

Print a single integer number — the maximum possible sum of distances between all pairs of nodes in the united tree.

## 说明/提示

Consider the first test case. There are two trees composed of two nodes, and one tree with three nodes. The maximum possible answer is obtained if the trees are connected in a single chain of 7 vertices.

In the second test case, a possible choice of new edges to obtain the maximum answer is the following:

- Connect node 3 from the first tree to node 1 from the second tree;
- Connect node 2 from the third tree to node 1 from the second tree.

## 样例 #1

### 输入

```
2 2 3
1 2
1 2
1 2
2 3

```

### 输出

```
56

```

## 样例 #2

### 输入

```
5 1 4
1 2
2 5
3 4
4 2
1 2
1 3
1 4

```

### 输出

```
151

```

