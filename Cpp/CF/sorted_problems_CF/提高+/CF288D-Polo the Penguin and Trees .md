---
title: "Polo the Penguin and Trees "
layout: "post"
diff: 提高+/省选-
pid: CF288D
tag: []
---

# Polo the Penguin and Trees 

## 题目描述

Little penguin Polo has got a tree — a non-directed connected acyclic graph, containing $ n $ nodes and $ n-1 $ edges. We will consider the tree nodes numbered by integers from 1 to $ n $ .

Today Polo wonders, how to find the number of pairs of paths that don't have common nodes. More formally, he should find the number of groups of four integers $ a,b,c $ and $ d $ such that:

- $ 1<=a&lt;b<=n $ ;
- $ 1<=c&lt;d<=n $ ;
- there's no such node that lies on both the shortest path from node $ a $ to node $ b $ and from node $ c $ to node $ d $ .

The shortest path betweem two nodes is the path that is shortest in the number of edges.

Help Polo solve this problem.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=80000) $ — the number of tree nodes. Each of the following $ n-1 $ lines contains a pair of integers $ u_{i} $ and $ v_{i} $ $ (1<=u_{i},v_{i}<=n; u_{i}≠v_{i}) $ — the $ i $ -th edge of the tree.

It is guaranteed that the given graph is a tree.

## 输出格式

In a single line print a single integer — the answer to the problem.

Please do not use the %lld specificator to read or write 64-bit numbers in С++. It is recommended to use the cin, cout streams or the %I64d specificator.

## 样例 #1

### 输入

```
4
1 2
2 3
3 4

```

### 输出

```
2

```

