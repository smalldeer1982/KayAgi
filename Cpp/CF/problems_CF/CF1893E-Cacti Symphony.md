---
title: "Cacti Symphony"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1893E
tag: []
---

# Cacti Symphony

## 题目描述

You are given an undirected connected graph in which any two distinct simple cycles do not have common vertices. Since the graph can be very large, it is given to you in a compressed form: for each edge, you are also given a number $ d $ , which indicates that there are $ d $ additional vertices on this edge.

You need to assign a weight to each vertex and each edge of the graph — an integer from $ 1 $ to $ 3 $ .

An edge of the graph is called good if the [bitwise XOR](https://en.wikipedia.org/wiki/Exclusive_or) of the weights of its adjacent vertices is not equal to $ 0 $ and not equal to the weight of that edge.

Similarly, a vertex of the graph is called good if the [bitwise XOR](https://en.wikipedia.org/wiki/Exclusive_or) of the weights of its adjacent edges is not equal to $ 0 $ and not equal to the weight of that vertex.

You need to determine how many ways there are to assign weights to the vertices and edges of the graph so that all vertices and edges are good. Since the answer can be quite large, you need to calculate the remainder of the answer divided by $ 998\,244\,353 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ — the number of vertices and the number of edges in the graph ( $ 2 \le n \le 5 \cdot 10^5 $ , $ n - 1 \le m \le 10^6 $ ).

Each of the next $ m $ lines contains three integers $ a_i, b_i $ , and $ d_i $ ( $ 1 \le a_i, b_i \le n $ , $ a_i \ne b_i $ , $ 0 \le d_i \le 10^9 $ ), indicating that there is an edge in the graph connecting vertices $ a_i $ and $ b_i $ . Additionally, on this edge, there are $ d_i $ additional vertices. It is guaranteed that the given graph is connected, there are no multiple edges, loops, and any two distinct simple cycles of the graph do not have common vertices.

## 输出格式

Output a single integer — the answer to the problem modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test, the graph is a simple cycle of $ 3 $ vertices. It can be shown, that there are exactly $ 12 $ ways to assign weights, to make all vertexes and edges good.

In the second test, the graph has the form of two simple cycles of $ 3 $ vertices connected by an edge. It can be shown that for such a graph there are no ways to arrange weights so that all vertices and edges are good.

## 样例 #1

### 输入

```
3 3
1 2 0
2 3 0
3 1 0
```

### 输出

```
12
```

## 样例 #2

### 输入

```
6 7
1 2 0
2 3 0
3 1 0
4 5 0
5 6 0
6 4 0
4 3 0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 1
2 1 777
```

### 输出

```
0
```

## 样例 #4

### 输入

```
3 3
1 2 0
2 3 110850709
3 1 1000000000
```

### 输出

```
179179178
```

