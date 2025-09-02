---
title: "Clique in the Divisibility Graph"
layout: "post"
diff: 普及+/提高
pid: CF566F
tag: ['动态规划 DP']
---

# Clique in the Divisibility Graph

## 题目描述

As you must know, the maximum clique problem in an arbitrary graph is $ NP $ -hard. Nevertheless, for some graphs of specific kinds it can be solved effectively.

Just in case, let us remind you that a clique in a non-directed graph is a subset of the vertices of a graph, such that any two vertices of this subset are connected by an edge. In particular, an empty set of vertexes and a set consisting of a single vertex, are cliques.

Let's define a divisibility graph for a set of positive integers $ A={a_{1},a_{2},...,a_{n}} $ as follows. The vertices of the given graph are numbers from set $ A $ , and two numbers $ a_{i} $ and $ a_{j} $ ( $ i≠j $ ) are connected by an edge if and only if either $ a_{i} $ is divisible by $ a_{j} $ , or $ a_{j} $ is divisible by $ a_{i} $ .

You are given a set of non-negative integers $ A $ . Determine the size of a maximum clique in a divisibility graph for set $ A $ .

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{6} $ ), that sets the size of set $ A $ .

The second line contains $ n $ distinct positive integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{6} $ ) — elements of subset $ A $ . The numbers in the line follow in the ascending order.

## 输出格式

Print a single number — the maximum size of a clique in a divisibility graph for set $ A $ .

## 说明/提示

In the first sample test a clique of size 3 is, for example, a subset of vertexes $ {3,6,18} $ . A clique of a larger size doesn't exist in this graph.

## 样例 #1

### 输入

```
8
3 4 6 8 10 18 21 24

```

### 输出

```
3

```

