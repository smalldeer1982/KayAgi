---
title: "Counting Graphs"
layout: "post"
diff: 普及+/提高
pid: CF1857G
tag: []
---

# Counting Graphs

## 题目描述

Given a tree consisting of $ n $ vertices. A tree is a connected undirected graph without cycles. Each edge of the tree has its weight, $ w_i $ .

Your task is to count the number of different graphs that satisfy all four conditions:

1. The graph does not have self-loops and multiple edges.
2. The weights on the edges of the graph are integers and do not exceed $ S $ .
3. The graph has exactly one [minimum spanning tree](http://tiny.cc/30g9vz).
4. The minimum spanning tree of the graph is the given tree.

Two graphs are considered different if their sets of edges are different, taking into account the weights of the edges.

The answer can be large, output it modulo $ 998244353 $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ S $ ( $ 2 \le n \le 2 \cdot 10^5, 1\le S\le 10^9 $ ) — the number of vertices and the upper bound of the weights.

Then follow $ n-1 $ lines describing the tree, the $ i $ -th line contains three integers $ u_i $ , $ v_i $ , and $ w_i $ ( $ 1\le u_i,v_i\le n, u_i \ne v_i, 1\le w_i\le S $ ) — an edge in the tree with weight $ w_i $ .

It is guaranteed that the sum of $ n $ for all tests does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test, output the number of different graphs that satisfy the conditions, modulo $ 998244353 $ .

## 说明/提示

In the first sample, there is only one graph, which is the given tree.

In the second samle, the given tree looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1857G/ab436917e6d0d4d72cf47ac14814448742495cf6.png)  All possible graphs for the second sample are shown below, the minimum spanning tree is highlighted in red: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1857G/9737432c0bacf448b6d65d0d9cf4c5fd9e2081b3.png)

## 样例 #1

### 输入

```
4
2 5
1 2 4
4 5
1 2 2
2 3 4
3 4 3
5 6
1 2 3
1 3 2
3 4 6
3 5 1
10 200
1 2 3
2 3 33
3 4 200
1 5 132
5 6 1
5 7 29
7 8 187
7 9 20
7 10 4
```

### 输出

```
1
8
80
650867886
```

