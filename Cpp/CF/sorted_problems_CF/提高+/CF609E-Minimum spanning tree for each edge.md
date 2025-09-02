---
title: "Minimum spanning tree for each edge"
layout: "post"
diff: 提高+/省选-
pid: CF609E
tag: ['生成树', '树链剖分']
---

# Minimum spanning tree for each edge

## 题目描述

# Minimum spanning tree for each edge

## 题面翻译


给你 $n$ 个点，$m$ 条边，如果对于一个最小生成树中要求必须包括第 $i(1 \le i \le m)$ 条边，那么最小生成树的权值总和最小是多少。


Connected undirected weighted graph without self-loops and multiple edges is given. Graph contains $ n $ vertices and $ m $ edges.

For each edge $ (u,v) $ find the minimal possible weight of the spanning tree that contains the edge $ (u,v) $ .

The weight of the spanning tree is the sum of weights of all edges included in spanning tree.

## 输入格式

第一行有两个整数 $n$ 和 $m$。

接下来 $m$ 行，每行有三个整数 $u$，$v$ 和 $w$ 表示一条权值为 $w$ 的边连接 $u$ 和 $v$。


First line contains two integers $ n $ and $ m $ ( $ 1<=n<=2·10^{5},n-1<=m<=2·10^{5} $ ) — the number of vertices and edges in graph.

Each of the next $ m $ lines contains three integers $ u_{i},v_{i},w_{i} $ ( $ 1<=u_{i},v_{i}<=n,u_{i}≠v_{i},1<=w_{i}<=10^{9} $ ) — the endpoints of the $ i $ -th edge and its weight.

## 输出格式

总共 $m$ 行，第 $i$ 行一个整数代表包括第 $i$ 条边时的最小权值和。


Print $ m $ lines. $ i $ -th line should contain the minimal possible weight of the spanning tree that contains $ i $ -th edge.

The edges are numbered from $ 1 $ to $ m $ in order of their appearing in input.

## 说明/提示

$1 \le n \le 2 \times 10^5,n-1 \le m\le 2 \times 10^5$

$1 \le u_i,v_i \le n,u_i \neq v_i,1 \le w_i \le 10^9$

## 样例 #1

### 输入

```
5 7
1 2 3
1 3 1
1 4 5
2 3 2
2 5 3
3 4 2
4 5 4

```

### 输出

```
9
8
11
8
8
8
9

```

