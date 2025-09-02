---
title: "Tenzing and Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1842F
tag: []
---

# Tenzing and Tree

## 题目描述

Tenzing has an undirected tree of $ n $ vertices.

Define the value of a tree with black and white vertices in the following way. The value of an edge is the absolute difference between the number of black nodes in the two components of the tree after deleting the edge. The value of the tree is the sum of values over all edges.

For all $ k $ such that $ 0 \leq k \leq n $ , Tenzing wants to know the maximum value of the tree when $ k $ vertices are painted black and $ n-k $ vertices are painted white.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1\leq n\leq 5000 $ ) — the number of vertices.

The following $ n-1 $ lines of the input contains $ 2 $ integers $ u_i $ and $ v_i $ ( $ 1 \leq u_i, v_i \leq n, u_i \neq v_i $ ) — indicating an edge between vertices $ u_i $ and $ v_i $ . It is guaranteed that the given edges form a tree.

## 输出格式

Output $ n+1 $ numbers. The $ i $ -th number is the answer of $ k=i-1 $ .

## 说明/提示

Consider the first example. When $ k=2 $ , Tenzing can paint vertices $ 1 $ and $ 2 $ black then the value of edge $ (1,2) $ is 0, and the values of other edges are all equal to $ 2 $ . So the value of that tree is $ 4 $ .

## 样例 #1

### 输入

```
4
1 2
3 2
2 4
```

### 输出

```
0 3 4 5 6
```

## 样例 #2

### 输入

```
1
```

### 输出

```
0 0
```

