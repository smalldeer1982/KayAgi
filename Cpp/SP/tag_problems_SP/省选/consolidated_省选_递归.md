---
title: "QTREE4 - Query on a tree IV"
layout: "post"
diff: 省选/NOI-
pid: SP2666
tag: ['递归', '分治', '动态树 LCT', '概率论']
---

# QTREE4 - Query on a tree IV

## 题目描述

You are given a tree (an acyclic undirected connected graph) with $N$ nodes, and nodes numbered $1,2,3\ldots,N$. Each edge has an integer value assigned to it (note that the value can be negative). Each node has a color, white or black. We define $dist(a, b)$ as the sum of the value of the edges on the path from node $a$ to node $b$.

All the nodes are white initially.

We will ask you to perfrom some instructions of the following form:

- `C a` : change the color of node $a$.(from black to white or from white to black)
- `A` : ask for the maximum $dist(a, b)$, both of node a and node $b$ must be white ($a$ can be equal to $b$). Obviously, as long as there is a white node, the result will alway be non negative.

## 输入格式

- In the first line there is an integer $N$. ($N \leq 100000$)
- In the next $N-1$ lines, the $i$-th line describes the $i$-th edge: a line with three integers $a,b,c$ denotes an edge between $a, b$ of value $c$. ($-10^3 \leq c \leq 10^3$)
- In the next line, there is an integer $Q$ denotes the number of instructions. ($Q \leq 100000$)
- In the next $Q$ lines, each line contains an instruction `C a` or `A`.

## 输出格式

For each `A` operation, write one integer representing its result. If there is no white node in the tree, you should write `They have disappeared.`.

## 样例 #1

### 输入

```
3
1 2 1
1 3 1
7
A
C 1
A
C 2
A
C 3
A
```

### 输出

```
2
2
0
They have disappeared.
```



---

