---
title: "QTREE7 - Query on a tree VII"
layout: "post"
diff: 省选/NOI-
pid: SP16580
tag: ['平衡树', '连通块', '动态树 LCT']
---

# QTREE7 - Query on a tree VII

## 题目描述

You are given a tree (an acyclic undirected connected graph) with $n$ nodes. The tree nodes are numbered from $1$ to $n$. Each node has a color, white or black, and a weight. We will ask you to perfrom some instructions of the following form:

- `0 u`: ask for the maximum weight among the nodes which are connected to $u$, two nodes are connected if all the node on the path from $u$ to $v$ (inclusive $u$ and $v$) have a same color.
- `1 u`: toggle the color of $u$(that is, from black to white, or from white to black).
- `2 u w`: change the weight of $u$ to $w$.

## 输入格式

The first line contains a number $n$ denoted how many nodes in the tree($n-1$ lines), each line has two numbers $(u, v)$ describe a edge of the tree(1 u, **v** n number, the first line is the initial color of each node(0 or 1), and the second line is the initial weight, let's say Wi, of each node(|**Wi**| m denoted how many operations we are going to process(1 m m lines, each line describe a operation (**t**, **u**) as we mentioned above(0 t u n, |**w**|

## 输出格式

For each query operation, output the corresponding result.

## 样例 #1

### 输入

```
5
1 2
1 3
1 4
1 5
0 1 1 1 1
1 2 3 4 5
3
0 1
1 1
0 1
```

### 输出

```
1
5
```

## 样例 #2

### 输入

```
7
1 2
1 3
2 4
2 5
3 6
3 7
0 0 0 0 0 0 0
1 2 3 4 5 6 7
4
0 1
1 1
0 2
0 3
```

### 输出

```
7
5
7
```

