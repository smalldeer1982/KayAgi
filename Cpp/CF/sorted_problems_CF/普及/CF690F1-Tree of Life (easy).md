---
title: "Tree of Life (easy)"
layout: "post"
diff: 普及/提高-
pid: CF690F1
tag: []
---

# Tree of Life (easy)

## 题目描述

Heidi has finally found the mythical Tree of Life – a legendary combinatorial structure which is said to contain a prophecy crucially needed to defeat the undead armies.

On the surface, the Tree of Life is just a regular undirected tree well-known from computer science. This means that it is a collection of $ n $ points (called vertices), some of which are connected using $ n-1 $ line segments (edges) so that each pair of vertices is connected by a path (a sequence of one or more edges).

To decipher the prophecy, Heidi needs to perform a number of steps. The first is counting the number of lifelines in the tree – these are paths of length $ 2 $ , i.e., consisting of two edges. Help her!

## 输入格式

The first line of the input contains a single integer $ n $ – the number of vertices in the tree ( $ 1<=n<=10000 $ ). The vertices are labeled with the numbers from 1 to $ n $ . Then $ n-1 $ lines follow, each describing one edge using two space-separated numbers $ a b $ – the labels of the vertices connected by the edge ( $ 1<=a<b<=n $ ). It is guaranteed that the input represents a tree.

## 输出格式

Print one integer – the number of lifelines in the tree.

## 说明/提示

In the second sample, there are four lifelines: paths between vertices $ 1 $ and $ 3 $ , $ 2 $ and $ 4 $ , $ 2 $ and $ 5 $ , and $ 4 $ and $ 5 $ .

## 样例 #1

### 输入

```
4
1 2
1 3
1 4

```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
3 5

```

### 输出

```
4
```

