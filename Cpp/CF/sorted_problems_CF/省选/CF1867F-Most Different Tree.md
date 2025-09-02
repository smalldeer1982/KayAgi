---
title: "Most Different Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1867F
tag: []
---

# Most Different Tree

## 题目描述

Given a tree with $ n $ vertices rooted at vertex $ 1 $ , denote it as $ G $ . Also denote $ P(G) $ as the multiset of subtrees of all vertices in tree $ G $ . You need to find a tree $ G' $ of size $ n $ rooted at vertex $ 1 $ such that the number of subtrees in $ P(G') $ that are isomorphic to any subtree in $ P(G) $ is minimized.

A subtree of vertex $ v $ is a graph that contains all vertices for which vertex $ v $ lies on the path from the root of the tree to itself, as well as all edges between these vertices.

Two rooted trees are considered isomorphic if it is possible to relabel the vertices of one of them so that it becomes equal to the other, with the root of the first tree receiving the number of the root of the second tree.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 10^6 $ ) - the number of vertices in tree $ G $ . Each of the next $ n-1 $ lines contains two integers $ a $ and $ b $ $ (1 \leq a,b \leq n) $ , indicating that there is an edge between vertices $ a $ and $ b $ in the tree.

## 输出格式

Output $ n-1 $ lines, each line containing two numbers $ a $ , $ b $ $ (1 \leq a,b \leq n) $ - the edges of tree $ G' $ . If there are multiple optimal answers, output any.

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
3
1 2
1 3
```

### 输出

```
1 2
2 3
```

## 样例 #3

### 输入

```
4
1 2
1 3
3 4
```

### 输出

```
1 2
2 3
3 4
```

