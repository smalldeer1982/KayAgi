---
title: "Close Vertices"
layout: "post"
diff: 省选/NOI-
pid: CF293E
tag: ['点分治', '树状数组', '概率论']
---

# Close Vertices

## 题目描述

You've got a weighted tree, consisting of $ n $ vertices. Each edge has a non-negative weight. The length of the path between any two vertices of the tree is the number of edges in the path. The weight of the path is the total weight of all edges it contains.

Two vertices are close if there exists a path of length at most $ l $ between them and a path of weight at most $ w $ between them. Count the number of pairs of vertices $ v,u $ $ (v&lt;u) $ , such that vertices $ v $ and $ u $ are close.

## 输入格式

The first line contains three integers $ n $ , $ l $ and $ w $ $ (1<=n<=10^{5},1<=l<=n,0<=w<=10^{9}) $ . The next $ n-1 $ lines contain the descriptions of the tree edges. The $ i $ -th line contains two integers $ p_{i},w_{i} $ $ (1<=p_{i}&lt;(i+1),0<=w_{i}<=10^{4}) $ , that mean that the $ i $ -th edge connects vertex $ (i+1) $ and $ p_{i} $ and has weight $ w_{i} $ .

Consider the tree vertices indexed from 1 to $ n $ in some way.

## 输出格式

Print a single integer — the number of close pairs.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
4 4 6
1 3
1 4
1 3

```

### 输出

```
4

```

## 样例 #2

### 输入

```
6 2 17
1 3
2 5
2 13
1 6
5 9

```

### 输出

```
9

```

