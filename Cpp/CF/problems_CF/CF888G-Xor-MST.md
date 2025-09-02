---
title: "Xor-MST"
layout: "post"
diff: 省选/NOI-
pid: CF888G
tag: ['深度优先搜索 DFS', '生成树', '进制']
---

# Xor-MST

## 题目描述

You are given a complete undirected graph with $ n $ vertices. A number $ a_{i} $ is assigned to each vertex, and the weight of an edge between vertices $ i $ and $ j $ is equal to $ a_{i}xora_{j} $ .

Calculate the weight of the minimum spanning tree in this graph.

## 输入格式

The first line contains $ n $ ( $ 1<=n<=200000 $ ) — the number of vertices in the graph.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 0<=a_{i}<2^{30} $ ) — the numbers assigned to the vertices.

## 输出格式

Print one number — the weight of the minimum spanning tree in the graph.

## 样例 #1

### 输入

```
5
1 2 3 4 5

```

### 输出

```
8

```

## 样例 #2

### 输入

```
4
1 2 3 4

```

### 输出

```
8

```

