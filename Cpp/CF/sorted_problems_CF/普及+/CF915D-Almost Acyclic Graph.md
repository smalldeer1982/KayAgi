---
title: "Almost Acyclic Graph"
layout: "post"
diff: 普及+/提高
pid: CF915D
tag: ['枚举', '排序', '拓扑排序']
---

# Almost Acyclic Graph

## 题目描述

You are given a [directed graph](https://en.wikipedia.org/wiki/Directed_graph) consisting of $ n $ vertices and $ m $ edges (each edge is directed, so it can be traversed in only one direction). You are allowed to remove at most one edge from it.

Can you make this graph [acyclic](https://en.wikipedia.org/wiki/Directed_acyclic_graph) by removing at most one edge from it? A directed graph is called acyclic iff it doesn't contain any cycle (a non-empty path that starts and ends in the same vertex).

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=500 $ , $ 1<=m<=min(n(n-1),100000) $ ) — the number of vertices and the number of edges, respectively.

Then $ m $ lines follow. Each line contains two integers $ u $ and $ v $ denoting a directed edge going from vertex $ u $ to vertex $ v $ ( $ 1<=u,v<=n $ , $ u≠v $ ). Each ordered pair $ (u,v) $ is listed at most once (there is at most one directed edge from $ u $ to $ v $ ).

## 输出格式

If it is possible to make this graph acyclic by removing at most one edge, print YES. Otherwise, print NO.

## 说明/提示

In the first example you can remove edge ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png), and the graph becomes acyclic.

In the second example you have to remove at least two edges (for example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/7480c546ca7ee72615c3ded7d769355b1c864f93.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png)) in order to make the graph acyclic.

## 样例 #1

### 输入

```
3 4
1 2
2 3
3 2
3 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
5 6
1 2
2 3
3 2
3 1
2 1
4 5

```

### 输出

```
NO

```

