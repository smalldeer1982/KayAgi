---
title: "Star MST"
layout: "post"
diff: 提高+/省选-
pid: CF1657E
tag: ['组合数学']
---

# Star MST

## 题目描述

In this problem, we will consider complete undirected graphs consisting of $ n $ vertices with weighted edges. The weight of each edge is an integer from $ 1 $ to $ k $ .

An undirected graph is considered beautiful if the sum of weights of all edges incident to vertex $ 1 $ is equal to the weight of MST in the graph. MST is the minimum spanning tree — a tree consisting of $ n-1 $ edges of the graph, which connects all $ n $ vertices and has the minimum sum of weights among all such trees; the weight of MST is the sum of weights of all edges in it.

Calculate the number of complete beautiful graphs having exactly $ n $ vertices and the weights of edges from $ 1 $ to $ k $ . Since the answer might be large, print it modulo $ 998244353 $ .

## 输入格式

The only line contains two integers $ n $ and $ k $ ( $ 2 \le n \le 250 $ ; $ 1 \le k \le 250 $ ).

## 输出格式

Print one integer — the number of complete beautiful graphs having exactly $ n $ vertices and the weights of edges from $ 1 $ to $ k $ . Since the answer might be large, print it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3 2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4 4
```

### 输出

```
571
```

## 样例 #3

### 输入

```
6 9
```

### 输出

```
310640163
```

## 样例 #4

### 输入

```
42 13
```

### 输出

```
136246935
```

