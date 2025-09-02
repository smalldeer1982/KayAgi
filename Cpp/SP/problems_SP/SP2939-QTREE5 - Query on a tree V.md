---
title: "QTREE5 - Query on a tree V"
layout: "post"
diff: 省选/NOI-
pid: SP2939
tag: ['动态树 LCT']
---

# QTREE5 - Query on a tree V

## 题目描述

You are given a tree (an acyclic undirected connected graph) with N nodes. The tree nodes are numbered from 1 to N. We define dist(a, b) as the number of edges on the path from node a to node b.

Each node has a color, white or black. All the nodes are black initially.

We will ask you to perfrom some instructions of the following form:

- 0 i : change the color of i-th node(from black to white, or from white to black).
- 1 **v** : ask for the minimum dist(u, **v**), node u must be white(u can be equal to **v**). Obviously, as long as node **v** is white, the result will always be 0.

## 输入格式

- In the first line there is an integer N (N <= 100000)
- In the next N-1 lines, the i-th line describes the i-th edge: a line with two integers a b denotes an edge between a and b.
- In the next line, there is an integer Q denotes the number of instructions (Q <= 100000)
- In the next Q lines, each line contains an instruction "0 i" or "1 **v**"

## 输出格式

For each "1 **v**" operation, print one integer representing its result. If there is no white node in the tree, you should write "**-1**".

## 样例 #1

### 输入

```
10
1 2
1 3
2 4
1 5
1 6
4 7
7 8
5 9
1 10
10
0 6
0 6
0 6
1 3
0 1
0 1
1 3
1 10
1 4
1 6
```

### 输出

```
2
2
2
3
0
```

