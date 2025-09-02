---
title: "FASTFLOW - Fast Maximum Flow"
layout: "post"
diff: 省选/NOI-
pid: SP4110
tag: []
---

# FASTFLOW - Fast Maximum Flow

## 题目描述

Given a graph with N (2 ≤ N ≤ 5,000) vertices numbered 1 to N and M (1 ≤ M ≤ 30,000) undirected, weighted edges, compute the [maximum flow / minimum cut](http://en.wikipedia.org/wiki/Maximum_flow_problem) from vertex 1 to vertex N.

## 输入格式

The first line contains the two integers N and M. The next M lines each contain three integers A, B, and C, denoting that there is an edge of capacity C (1 ≤ C ≤ 10 $ ^{9} $ ) between nodes A and B (1 ≤ A, B ≤ N). Note that it is possible for there to be duplicate edges, as well as an edge from a node to itself.

## 输出格式

Print a single integer (which may not fit into a 32-bit integer) denoting the maximum flow / minimum cut between 1 and N.

## 样例 #1

### 输入

```
4 6
1 2 3
2 3 4
3 1 2
2 2 5
3 4 3
4 3 3
```

### 输出

```
5
```

