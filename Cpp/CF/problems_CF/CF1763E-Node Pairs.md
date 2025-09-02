---
title: "Node Pairs"
layout: "post"
diff: 普及+/提高
pid: CF1763E
tag: []
---

# Node Pairs

## 题目描述

Let's call an ordered pair of nodes $ (u, v) $ in a directed graph unidirectional if $ u \neq v $ , there exists a path from $ u $ to $ v $ , and there are no paths from $ v $ to $ u $ .

A directed graph is called  $ p $ -reachable if it contains exactly $ p $ ordered pairs of nodes $ (u, v) $ such that $ u < v $ and $ u $ and $ v $ are reachable from each other. Find the minimum number of nodes required to create a $ p $ -reachable directed graph.

Also, among all such $ p $ -reachable directed graphs with the minimum number of nodes, let $ G $ denote a graph which maximizes the number of unidirectional pairs of nodes. Find this number.

## 输入格式

The first and only line contains a single integer $ p $ ( $ 0 \le p \le 2 \cdot 10^5 $ ) — the number of ordered pairs of nodes.

## 输出格式

Print a single line containing two integers — the minimum number of nodes required to create a $ p $ -reachable directed graph, and the maximum number of unidirectional pairs of nodes among all such $ p $ -reachable directed graphs with the minimum number of nodes.

## 说明/提示

In the first test case, the minimum number of nodes required to create a $ 3 $ -reachable directed graph is $ 3 $ . Among all $ 3 $ -reachable directed graphs with $ 3 $ nodes, the following graph $ G $ is one of the graphs with the maximum number of unidirectional pairs of nodes, which is $ 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1763E/056ef4fb4b6b27a5f901099fab6d214793a2d54c.png)

## 样例 #1

### 输入

```
3
```

### 输出

```
3 0
```

## 样例 #2

### 输入

```
4
```

### 输出

```
5 6
```

## 样例 #3

### 输入

```
0
```

### 输出

```
0 0
```

