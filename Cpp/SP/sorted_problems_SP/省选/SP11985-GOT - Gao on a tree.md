---
title: "GOT - Gao on a tree"
layout: "post"
diff: 省选/NOI-
pid: SP11985
tag: ['线段树', '树链剖分']
---

# GOT - Gao on a tree

## 题目描述

 There's a tree, with each vertex assigned a number. For each query (a, b, c), you are asked whether there is a vertex on the path from a to b, which is assigned number c?

## 输入格式

There are multiple cases, end by EOF.

For each case, the first line contains n (n <= 100000) and m (m <= 200000), representing the number of vertexes (numbered from 1 to n) and the number of queries.

Then n integers follows, representing the number assigned to the i-th vertex.

Then n-1 lines, each of which contains a edge of the tree.

Then m lines, each of which contains three integers a, b and c (0 <= c <= n), representing a query.

## 输出格式

You should output "`Find`" or "`NotFind`" for every query on one line.

Output a blank line AFTER every case.

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
1 2
1 3
3 4
3 5
2 3 4
2 4 3
2 4 5
4 5 1
4 5 3
```

### 输出

```
NotFind
Find
NotFind
NotFind
Find
```

