---
title: "KPGRAPHS - Counting Graphs"
layout: "post"
diff: 省选/NOI-
pid: SP4420
tag: []
---

# KPGRAPHS - Counting Graphs

## 题目描述

In this problem your task is to count the amount of graphs of different types. We only consider undirected graphs without self-loops. Every pair of vectices can be connected with at most one edge. Graphs are labeled, i.e. if a graph has N vertices, then each of them has a unique label from 1 to N.

We will be interested in three types of graphs - connected, eulerian and bipartite. A graph is connected, if and only if there is at least one path between any pair of vertices. A graph is eulerian, if and only if it's connected and there is a cycle that goes through every edge exactly once. A graph is bipartite, if and only if we can split all of its vertices into two subsets A and B, such that every edge has one endpoint in A and another in B.

## 输入格式

The first line of the input contains one integer number T (1 <= T <= 1000) - the number of test cases.

Next T lines contain different test cases. Each test case contains one integer number N (1 <= N <= 1000) - the number of vertices in a graph.

## 输出格式

For each test case, output the number of connected graphs, the number of euleran graphs and the number of bipartite graphs - all modulo 1000000007. See examples for the required format. Output one additional empty line after each test case.

## 样例 #1

### 输入

```
2
1
2

```

### 输出

```
Connected: 1
Eulerian: 1
Bipartite: 1

Connected: 1
Eulerian: 0
Bipartite: 2


```

