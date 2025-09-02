---
title: "Alex and Julian"
layout: "post"
diff: 提高+/省选-
pid: CF1220D
tag: []
---

# Alex and Julian

## 题目描述

Boy Dima gave Julian a birthday present - set $ B $ consisting of positive integers. However, he didn't know, that Julian hates sets, but enjoys bipartite graphs more than anything else!

Julian was almost upset, but her friend Alex said, that he can build an undirected graph using this set in such way: let all integer numbers be vertices, then connect any two $ i $ and $ j $ with an edge if $ |i - j| $ belongs to $ B $ .

Unfortunately, Julian doesn't like the graph, that was built using $ B $ . Alex decided to rectify the situation, so he wants to erase some numbers form $ B $ , so that graph built using the new set is bipartite. The difficulty of this task is that the graph, Alex has to work with, has an infinite number of vertices and edges! It is impossible to solve this task alone, so Alex asks you for help. Write a program that erases a subset of minimum size from $ B $ so that graph constructed on the new set is bipartite.

Recall, that graph is bipartite if all its vertices can be divided into two disjoint sets such that every edge connects a vertex from different sets.

## 输入格式

First line contains an integer $ n ~ (1 \leqslant n \leqslant 200\,000) $ — size of $ B $

Second line contains $ n $ integers $ b_1, b_2, \ldots, b_n ~ (1 \leqslant b_i \leqslant 10^{18}) $ — numbers of $ B $ , all $ b_i $ are unique

## 输出格式

In first line print single integer $ k $ – number of erased elements. In second line print $ k $ integers – values of erased elements.

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3
1 2 3

```

### 输出

```
1
2 
```

## 样例 #2

### 输入

```
2
2 6

```

### 输出

```
0

```

