---
title: "Remove Bridges"
layout: "post"
diff: 省选/NOI-
pid: CF1976F
tag: ['贪心']
---

# Remove Bridges

## 题目描述

You are given a rooted tree, consisting of $ n $ vertices, numbered from $ 1 $ to $ n $ . Vertex $ 1 $ is the root. Additionally, the root only has one child.

You are asked to add exactly $ k $ edges to the tree (possibly, multiple edges and/or edges already existing in the tree).

Recall that a bridge is such an edge that, after you remove it, the number of connected components in the graph increases. So, initially, all edges of the tree are bridges.

After $ k $ edges are added, some original edges of the tree are still bridges and some are not anymore. You want to satisfy two conditions:

- for every bridge, all tree edges in the subtree of the lower vertex of that bridge should also be bridges;
- the number of bridges is as small as possible.

Solve the task for all values of $ k $ from $ 1 $ to $ n - 1 $ and output the smallest number of bridges.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains a single integer $ n $ ( $ 2 \le n \le 3 \cdot 10^5 $ ) — the number of vertices of the tree.

Each of the next $ n - 1 $ lines contain two integers $ v $ and $ u $ ( $ 1 \le v, u \le n $ ) — the description of the edges of the tree. It's guaranteed that the given edges form a valid tree.

Additional constraint on the input: the root (vertex $ 1 $ ) has exactly one child.

The sum of $ n $ over all testcases doesn't exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each testcase, print $ n - 1 $ integers. For each $ k $ from $ 1 $ to $ n - 1 $ print the smallest number of bridges that can be left after you add $ k $ edges to the tree.

## 样例 #1

### 输入

```
4
2
1 2
12
4 10
5 12
12 11
3 6
9 6
1 6
12 7
11 6
2 11
10 9
10 8
8
1 2
2 3
2 4
3 5
3 6
4 7
4 8
5
1 2
2 3
3 4
4 5
```

### 输出

```
0 
7 3 1 0 0 0 0 0 0 0 0 
4 1 0 0 0 0 0 
0 0 0 0
```

