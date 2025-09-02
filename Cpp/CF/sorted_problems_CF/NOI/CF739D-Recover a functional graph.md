---
title: "Recover a functional graph"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF739D
tag: []
---

# Recover a functional graph

## 题目描述

Functional graph is a directed graph in which all vertices have outdegree equal to $ 1 $ . Loops are allowed.

Some vertices of a functional graph lay on a cycle. From the others we can come to a cycle by making a finite number of steps along the edges (we consider only finite functional graphs in this problem).

Let's compute two values for each vertex. $ precycle_{i} $ is the amount of edges we should pass to get to a vertex which is a part of some cycle (zero, if $ i $ itself lies on a cycle), $ cycle_{i} $ is the length of the cycle we get to.

You are given the information about these values for some functional graph. For each vertex you know the values $ precycle_{i} $ and $ cycle_{i} $ , however, instead of some values there can be the question mark. It means that these values are unknown.

Build any functional graph that suits the description or determine that there is no such graph.

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=300 $ ) — the number of vertices in the graph.

Each of the next $ n $ lines contain two integers — $ precycle_{i} $ ( $ 0<=precycle_{i}<=n-1 $ ) and $ cycle_{i} $ ( $ 1<=cycle_{i}<=n $ ). There could be question marks instead of some of these values.

## 输出格式

In case there is no solution, print -1.

Otherwise, print $ n $ integers. $ i $ -th of them is the number of vertex to which the edge form the $ i $ -th vertex go.

The vertices should be in the same order as they go in input data.

If there are multiple solutions, print any of them.

## 样例 #1

### 输入

```
3
0 3
0 3
? ?

```

### 输出

```
2 3 1 

```

## 样例 #2

### 输入

```
5
3 2
? ?
? ?
? ?
? ?

```

### 输出

```
5 3 2 2 4 

```

## 样例 #3

### 输入

```
8
? 3
? ?
0 2
0 2
0 3
0 3
0 3
3 3

```

### 输出

```
5 1 4 3 6 7 5 2 

```

## 样例 #4

### 输入

```
1
? ?

```

### 输出

```
1 

```

## 样例 #5

### 输入

```
6
0 3
0 3
0 3
0 3
0 3
0 3

```

### 输出

```
2 3 1 5 6 4 

```

## 样例 #6

### 输入

```
2
1 1
1 1

```

### 输出

```
-1

```

