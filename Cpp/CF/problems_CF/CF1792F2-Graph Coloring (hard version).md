---
title: "Graph Coloring (hard version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1792F2
tag: ['动态规划 DP', '图论', '组合数学', '快速数论变换 NTT']
---

# Graph Coloring (hard version)

## 题目描述

The only difference between the easy and the hard version is the constraint on $ n $ .

You are given an undirected complete graph on $ n $ vertices. A complete graph is a graph where each pair of vertices is connected by an edge. You have to paint the edges of the graph into two colors, red and blue (each edge will have one color).

A set of vertices $ S $ is red-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through red edges and vertices from $ S $ . Similarly, a set of vertices $ S $ is blue-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through blue edges and vertices from $ S $ .

You have to paint the graph in such a way that:

- there is at least one red edge;
- there is at least one blue edge;
- for each set of vertices $ S $ such that $ |S| \ge 2 $ , $ S $ is either red-connected or blue-connected, but not both.

Calculate the number of ways to paint the graph, and print it modulo $ 998244353 $ .

## 输入格式

The first (and only) line contains one integer $ n $ ( $ 3 \le n \le 5 \cdot 10^4 $ ).

## 输出格式

Print one integer — the number of ways to paint the graph, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
```

### 输出

```
50
```

## 样例 #3

### 输入

```
100
```

### 输出

```
878752271
```

## 样例 #4

### 输入

```
1337
```

### 输出

```
520628749
```

## 样例 #5

### 输入

```
42013
```

### 输出

```
906821221
```

