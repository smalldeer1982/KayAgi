---
title: "Complete The Graph"
layout: "post"
diff: 提高+/省选-
pid: CF715B
tag: ['枚举', '最短路']
---

# Complete The Graph

## 题目描述

ZS the Coder has drawn an undirected graph of $ n $ vertices numbered from $ 0 $ to $ n-1 $ and $ m $ edges between them. Each edge of the graph is weighted, each weight is a positive integer.

The next day, ZS the Coder realized that some of the weights were erased! So he wants to reassign positive integer weight to each of the edges which weights were erased, so that the length of the shortest path between vertices $ s $ and $ t $ in the resulting graph is exactly $ L $ . Can you help him?

## 输入格式

The first line contains five integers $ n,m,L,s,t $ ( $ 2<=n<=1000,1<=m<=10000,1<=L<=10^{9},0<=s,t<=n-1,s≠t $ ) — the number of vertices, number of edges, the desired length of shortest path, starting vertex and ending vertex respectively.

Then, $ m $ lines describing the edges of the graph follow. $ i $ -th of them contains three integers, $ u_{i},v_{i},w_{i} $ ( $ 0<=u_{i},v_{i}<=n-1,u_{i}≠v_{i},0<=w_{i}<=10^{9} $ ). $ u_{i} $ and $ v_{i} $ denote the endpoints of the edge and $ w_{i} $ denotes its weight. If $ w_{i} $ is equal to $ 0 $ then the weight of the corresponding edge was erased.

It is guaranteed that there is at most one edge between any pair of vertices.

## 输出格式

Print "NO" (without quotes) in the only line if it's not possible to assign the weights in a required way.

Otherwise, print "YES" in the first line. Next $ m $ lines should contain the edges of the resulting graph, with weights assigned to edges which weights were erased. $ i $ -th of them should contain three integers $ u_{i} $ , $ v_{i} $ and $ w_{i} $ , denoting an edge between vertices $ u_{i} $ and $ v_{i} $ of weight $ w_{i} $ . The edges of the new graph must coincide with the ones in the graph from the input. The weights that were not erased must remain unchanged whereas the new weights can be any positive integer not exceeding $ 10^{18} $ .

The order of the edges in the output doesn't matter. The length of the shortest path between $ s $ and $ t $ must be equal to $ L $ .

If there are multiple solutions, print any of them.

## 说明/提示

Here's how the graph in the first sample case looks like :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715B/c442fd279761bfa74ef367b518cede1e1fa97983.png)In the first sample case, there is only one missing edge weight. Placing the weight of $ 8 $ gives a shortest path from $ 0 $ to $ 4 $ of length $ 13 $ .

In the second sample case, there is only a single edge. Clearly, the only way is to replace the missing weight with $ 123456789 $ .

In the last sample case, there is no weights to assign but the length of the shortest path doesn't match the required value, so the answer is "NO".

## 样例 #1

### 输入

```
5 5 13 0 4
0 1 5
2 1 2
3 2 3
1 4 0
4 3 4

```

### 输出

```
YES
0 1 5
2 1 2
3 2 3
1 4 8
4 3 4

```

## 样例 #2

### 输入

```
2 1 123456789 0 1
0 1 0

```

### 输出

```
YES
0 1 123456789

```

## 样例 #3

### 输入

```
2 1 999999999 1 0
0 1 1000000000

```

### 输出

```
NO

```

