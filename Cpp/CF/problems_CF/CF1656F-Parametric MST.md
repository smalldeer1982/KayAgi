---
title: "Parametric MST"
layout: "post"
diff: 省选/NOI-
pid: CF1656F
tag: []
---

# Parametric MST

## 题目描述

You are given $ n $ integers $ a_1, a_2, \ldots, a_n $ . For any real number $ t $ , consider the complete weighted graph on $ n $ vertices $ K_n(t) $ with weight of the edge between vertices $ i $ and $ j $ equal to $ w_{ij}(t) = a_i \cdot a_j + t \cdot (a_i + a_j) $ .

Let $ f(t) $ be the cost of the [minimum spanning tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree) of $ K_n(t) $ . Determine whether $ f(t) $ is bounded above and, if so, output the maximum value it attains.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ T $ ( $ 1 \leq T \leq 10^4 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the number of vertices of the graph.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^6 \leq a_i \leq 10^6 $ ).

The sum of $ n $ for all test cases is at most $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single line with the maximum value of $ f(t) $ (it can be shown that it is an integer), or INF if $ f(t) $ is not bounded above.

## 样例 #1

### 输入

```
5
2
1 0
2
-1 1
3
1 -1 -2
3
3 -1 -2
4
1 2 3 -4
```

### 输出

```
INF
-1
INF
-6
-18
```

