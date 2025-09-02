---
title: "DZY Loves Physics"
layout: "post"
diff: 普及+/提高
pid: CF444A
tag: []
---

# DZY Loves Physics

## 题目描述

DZY loves Physics, and he enjoys calculating density.

Almost everything has density, even a graph. We define the density of a non-directed graph (nodes and edges of the graph have some values) as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/a425e0bd8ecdace80b53301f0ed617a22d06cb47.png) where $ v $ is the sum of the values of the nodes, $ e $ is the sum of the values of the edges.Once DZY got a graph $ G $ , now he wants to find a connected induced subgraph $ G' $ of the graph, such that the density of $ G' $ is as large as possible.

An induced subgraph $ G'(V',E') $ of a graph $ G(V,E) $ is a graph that satisfies:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/205d30887fed54bfaabe37b0daf749cd5804bf34.png);
- edge ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/7ea118e128a0519e2d5be64db2d60ebfb7343781.png) if and only if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/ea6ddeec58cbe4a1da10914bab9d3a37e180ee3e.png), and edge ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/a10ab0808c4b5f03a82ae1ae0a40b33ad030284e.png);
- the value of an edge in $ G' $ is the same as the value of the corresponding edge in $ G $ , so as the value of a node.

Help DZY to find the induced subgraph with maximum density. Note that the induced subgraph you choose must be connected.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/3a3e9eb2a63d273e409ca45b73267a13b68b4d42.png)

## 输入格式

The first line contains two space-separated integers $ n (1<=n<=500) $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/623e0a0f7617bb5ac295de245fd8a61995ab4225.png). Integer $ n $ represents the number of nodes of the graph $ G $ , $ m $ represents the number of edges.

The second line contains $ n $ space-separated integers $ x_{i} (1<=x_{i}<=10^{6}) $ , where $ x_{i} $ represents the value of the $ i $ -th node. Consider the graph nodes are numbered from $ 1 $ to $ n $ .

Each of the next $ m $ lines contains three space-separated integers $ a_{i},b_{i},c_{i} (1<=a_{i}&lt;b_{i}<=n; 1<=c_{i}<=10^{3}) $ , denoting an edge between node $ a_{i} $ and $ b_{i} $ with value $ c_{i} $ . The graph won't contain multiple edges.

## 输出格式

Output a real number denoting the answer, with an absolute or relative error of at most $ 10^{-9} $ .

## 说明/提示

In the first sample, you can only choose an empty subgraph, or the subgraph containing only node $ 1 $ .

In the second sample, choosing the whole graph is optimal.

## 样例 #1

### 输入

```
1 0
1

```

### 输出

```
0.000000000000000

```

## 样例 #2

### 输入

```
2 1
1 2
1 2 1

```

### 输出

```
3.000000000000000

```

## 样例 #3

### 输入

```
5 6
13 56 73 98 17
1 2 56
1 3 29
1 4 42
2 3 95
2 4 88
3 4 63

```

### 输出

```
2.965517241379311

```

