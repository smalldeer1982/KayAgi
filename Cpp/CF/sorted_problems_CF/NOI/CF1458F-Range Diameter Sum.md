---
title: "Range Diameter Sum"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1458F
tag: []
---

# Range Diameter Sum

## 题目描述

You are given a tree with $ n $ vertices numbered $ 1, \ldots, n $ . A tree is a connected simple graph without cycles.

Let $ \mathrm{dist}(u, v) $ be the number of edges in the unique simple path connecting vertices $ u $ and $ v $ .

Let $ \mathrm{diam}(l, r) = \max \mathrm{dist}(u, v) $ over all pairs $ u, v $ such that $ l \leq u, v \leq r $ .

Compute $ \sum_{1 \leq l \leq r \leq n} \mathrm{diam}(l, r) $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the number of vertices in the tree.

The next $ n - 1 $ lines describe the tree edges. Each of these lines contains two integers $ u, v $ ( $ 1 \leq u, v \leq n $ ) — endpoint indices of the respective tree edge. It is guaranteed that the edge list indeed describes a tree.

## 输出格式

Print a single integer — $ \sum_{1 \leq l \leq r \leq n} \mathrm{diam}(l, r) $ .

## 样例 #1

### 输入

```
4
1 2
2 4
3 2
```

### 输出

```
10
```

## 样例 #2

### 输入

```
10
1 8
2 9
5 6
4 8
4 2
7 9
3 6
10 4
3 9
```

### 输出

```
224
```

