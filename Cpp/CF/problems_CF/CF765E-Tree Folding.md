---
title: "Tree Folding"
layout: "post"
diff: 提高+/省选-
pid: CF765E
tag: []
---

# Tree Folding

## 题目描述

Vanya wants to minimize a tree. He can perform the following operation multiple times: choose a vertex $ v $ , and two disjoint (except for $ v $ ) paths of equal length $ a_{0}=v $ , $ a_{1} $ , ..., $ a_{k} $ , and $ b_{0}=v $ , $ b_{1} $ , ..., $ b_{k} $ . Additionally, vertices $ a_{1} $ , ..., $ a_{k} $ , $ b_{1} $ , ..., $ b_{k} $ must not have any neighbours in the tree other than adjacent vertices of corresponding paths. After that, one of the paths may be merged into the other, that is, the vertices $ b_{1} $ , ..., $ b_{k} $ can be effectively erased:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF765E/8a327dc5b22e7a12ad1fd6e8837e08cb4a661c45.png)Help Vanya determine if it possible to make the tree into a path via a sequence of described operations, and if the answer is positive, also determine the shortest length of such path.

## 输入格式

The first line of input contains the number of vertices $ n $ ( $ 2<=n<=2·10^{5} $ ).

Next $ n-1 $ lines describe edges of the tree. Each of these lines contains two space-separated integers $ u $ and $ v $ ( $ 1<=u,v<=n $ , $ u≠v $ ) — indices of endpoints of the corresponding edge. It is guaranteed that the given graph is a tree.

## 输出格式

If it is impossible to obtain a path, print -1. Otherwise, print the minimum number of edges in a possible path.

## 说明/提示

In the first sample case, a path of three edges is obtained after merging paths $ 2-1-6 $ and $ 2-4-5 $ .

It is impossible to perform any operation in the second sample case. For example, it is impossible to merge paths $ 1-3-4 $ and $ 1-5-6 $ , since vertex 6 additionally has a neighbour 7 that is not present in the corresponding path.

## 样例 #1

### 输入

```
6
1 2
2 3
2 4
4 5
1 6

```

### 输出

```
3

```

## 样例 #2

### 输入

```
7
1 2
1 3
3 4
1 5
5 6
6 7

```

### 输出

```
-1

```

