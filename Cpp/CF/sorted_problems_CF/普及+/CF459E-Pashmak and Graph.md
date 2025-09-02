---
title: "Pashmak and Graph"
layout: "post"
diff: 普及+/提高
pid: CF459E
tag: ['动态规划 DP', '图论']
---

# Pashmak and Graph

## 题目描述

Pashmak's homework is a problem about graphs. Although he always tries to do his homework completely, he can't solve this problem. As you know, he's really weak at graph theory; so try to help him in solving the problem.

You are given a weighted directed graph with $ n $ vertices and $ m $ edges. You need to find a path (perhaps, non-simple) with maximum number of edges, such that the weights of the edges increase along the path. In other words, each edge of the path must have strictly greater weight than the previous edge in the path.

Help Pashmak, print the number of edges in the required path.

## 输入格式

The first line contains two integers $ n $ , $ m $ $ (2<=n<=3·10^{5}; 1<=m<=min(n·(n-1),3·10^{5})) $ . Then, $ m $ lines follows. The $ i $ -th line contains three space separated integers: $ u_{i} $ , $ v_{i} $ , $ w_{i} $ $ (1<=u_{i},v_{i}<=n; 1<=w_{i}<=10^{5}) $ which indicates that there's a directed edge with weight $ w_{i} $ from vertex $ u_{i} $ to vertex $ v_{i} $ .

It's guaranteed that the graph doesn't contain self-loops and multiple edges.

## 输出格式

Print a single integer — the answer to the problem.

## 说明/提示

In the first sample the maximum trail can be any of this trails: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/46950f7ebb1a8fb1042610e7d90ce693216dd148.png).

In the second sample the maximum trail is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/0a8ef1a8d44f73ed1581f13e754f7328cc98bdea.png).

In the third sample the maximum trail is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/077a752077571978dd842d2ca5ed7e4dcecd7b85.png).

## 样例 #1

### 输入

```
3 3
1 2 1
2 3 1
3 1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 2
3 1 3

```

### 输出

```
3

```

## 样例 #3

### 输入

```
6 7
1 2 1
3 2 5
2 4 2
2 5 2
2 6 9
5 4 3
4 3 4

```

### 输出

```
6

```

