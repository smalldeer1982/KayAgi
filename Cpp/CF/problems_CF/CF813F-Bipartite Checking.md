---
title: "Bipartite Checking"
layout: "post"
diff: 省选/NOI-
pid: CF813F
tag: []
---

# Bipartite Checking

## 题目描述

You are given an undirected graph consisting of $ n $ vertices. Initially there are no edges in the graph. Also you are given $ q $ queries, each query either adds one undirected edge to the graph or removes it. After each query you have to check if the resulting graph is bipartite (that is, you can paint all vertices of the graph into two colors so that there is no edge connecting two vertices of the same color).

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2<=n,q<=100000 $ ).

Then $ q $ lines follow. $ i $ th line contains two numbers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i}<y_{i}<=n $ ). These numbers describe $ i $ th query: if there is an edge between vertices $ x_{i} $ and $ y_{i} $ , then remove it, otherwise add it.

## 输出格式

Print $ q $ lines. $ i $ th line must contain YES if the graph is bipartite after $ i $ th query, and NO otherwise.

## 样例 #1

### 输入

```
3 5
2 3
1 3
1 2
1 2
1 2

```

### 输出

```
YES
YES
NO
YES
NO

```

