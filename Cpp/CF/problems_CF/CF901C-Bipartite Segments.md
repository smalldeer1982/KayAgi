---
title: "Bipartite Segments"
layout: "post"
diff: 省选/NOI-
pid: CF901C
tag: []
---

# Bipartite Segments

## 题目描述

You are given an undirected graph with $ n $ vertices. There are no edge-simple cycles with the even length in it. In other words, there are no cycles of even length that pass each edge at most once. Let's enumerate vertices from $ 1 $ to $ n $ .

You have to answer $ q $ queries. Each query is described by a segment of vertices $ [l;r] $ , and you have to count the number of its subsegments $ [x;y] $ ( $ l<=x<=y<=r $ ), such that if we delete all vertices except the segment of vertices $ [x;y] $ (including $ x $ and $ y $ ) and edges between them, the resulting graph is bipartite.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=3·10^{5} $ , $ 1<=m<=3·10^{5} $ ) — the number of vertices and the number of edges in the graph.

The next $ m $ lines describe edges in the graph. The $ i $ -th of these lines contains two integers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i},b_{i}<=n $ ; $ a_{i}≠b_{i} $ ), denoting an edge between vertices $ a_{i} $ and $ b_{i} $ . It is guaranteed that this graph does not contain edge-simple cycles of even length.

The next line contains a single integer $ q $ ( $ 1<=q<=3·10^{5} $ ) — the number of queries.

The next $ q $ lines contain queries. The $ i $ -th of these lines contains two integers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) — the query parameters.

## 输出格式

Print $ q $ numbers, each in new line: the $ i $ -th of them should be the number of subsegments $ [x;y] $ ( $ l_{i}<=x<=y<=r_{i} $ ), such that the graph that only includes vertices from segment $ [x;y] $ and edges between them is bipartite.

## 说明/提示

The first example is shown on the picture below:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901C/9b1dc17b2719bb085fa0c10624f2d9373bdbe5c5.png)

For the first query, all subsegments of $ [1;3] $ , except this segment itself, are suitable.

For the first query, all subsegments of $ [4;6] $ , except this segment itself, are suitable.

For the third query, all subsegments of $ [1;6] $ are suitable, except $ [1;3] $ , $ [1;4] $ , $ [1;5] $ , $ [1;6] $ , $ [2;6] $ , $ [3;6] $ , $ [4;6] $ .

The second example is shown on the picture below:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901C/d6699797f2ea521389d1d5d2e2e1a5397ed46123.png)

## 样例 #1

### 输入

```
6 6
1 2
2 3
3 1
4 5
5 6
6 4
3
1 3
4 6
1 6

```

### 输出

```
5
5
14

```

## 样例 #2

### 输入

```
8 9
1 2
2 3
3 1
4 5
5 6
6 7
7 8
8 4
7 2
3
1 8
1 4
3 8

```

### 输出

```
27
8
19

```

