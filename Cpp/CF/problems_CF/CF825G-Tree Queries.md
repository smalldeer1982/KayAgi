---
title: "Tree Queries"
layout: "post"
diff: 省选/NOI-
pid: CF825G
tag: []
---

# Tree Queries

## 题目描述

You are given a tree consisting of $ n $ vertices (numbered from $ 1 $ to $ n $ ). Initially all vertices are white. You have to process $ q $ queries of two different types:

1. $ 1 $ $ x $ — change the color of vertex $ x $ to black. It is guaranteed that the first query will be of this type.
2. $ 2 $ $ x $ — for the vertex $ x $ , find the minimum index $ y $ such that the vertex with index $ y $ belongs to the simple path from $ x $ to some black vertex (a simple path never visits any vertex more than once).

For each query of type $ 2 $ print the answer to it.

Note that the queries are given in modified way.

## 输入格式

The first line contains two numbers $ n $ and $ q $ ( $ 3<=n,q<=10^{6} $ ).

Then $ n-1 $ lines follow, each line containing two numbers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i}&lt;y_{i}<=n $ ) and representing the edge between vertices $ x_{i} $ and $ y_{i} $ .

It is guaranteed that these edges form a tree.

Then $ q $ lines follow. Each line contains two integers $ t_{i} $ and $ z_{i} $ , where $ t_{i} $ is the type of $ i $ th query, and $ z_{i} $ can be used to restore $ x_{i} $ for this query in this way: you have to keep track of the answer to the last query of type $ 2 $ (let's call this answer $ last $ , and initially $ last=0 $ ); then $ x_{i}=(z_{i}+last)modn+1 $ .

It is guaranteed that the first query is of type $ 1 $ , and there is at least one query of type $ 2 $ .

## 输出格式

For each query of type $ 2 $ output the answer to it.

## 样例 #1

### 输入

```
4 6
1 2
2 3
3 4
1 2
1 2
2 2
1 3
2 2
2 2

```

### 输出

```
3
2
1

```

