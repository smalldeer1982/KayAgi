---
title: "Uniformly Branched Trees"
layout: "post"
diff: 省选/NOI-
pid: CF724F
tag: []
---

# Uniformly Branched Trees

## 题目描述

A tree is a connected graph without cycles.

Two trees, consisting of $ n $ vertices each, are called isomorphic if there exists a permutation $ p:{1,...,n}→{1,...,n} $ such that the edge $ (u,v) $ is present in the first tree if and only if the edge $ (p_{u},p_{v}) $ is present in the second tree.

Vertex of the tree is called internal if its degree is greater than or equal to two.

Count the number of different non-isomorphic trees, consisting of $ n $ vertices, such that the degree of each internal vertex is exactly $ d $ . Print the answer over the given prime modulo $ mod $ .

## 输入格式

The single line of the input contains three integers $ n $ , $ d $ and $ mod $ ( $ 1<=n<=1000 $ , $ 2<=d<=10 $ , $ 10^{8}<=mod<=10^{9} $ ) — the number of vertices in the tree, the degree of internal vertices and the prime modulo.

## 输出格式

Print the number of trees over the modulo $ mod $ .

## 样例 #1

### 输入

```
5 2 433416647

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10 3 409693891

```

### 输出

```
2

```

## 样例 #3

### 输入

```
65 4 177545087

```

### 输出

```
910726

```

