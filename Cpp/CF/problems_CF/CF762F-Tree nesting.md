---
title: "Tree nesting"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF762F
tag: []
---

# Tree nesting

## 题目描述

You are given two trees (connected undirected acyclic graphs) $ S $ and $ T $ .

Count the number of subtrees (connected subgraphs) of $ S $ that are isomorphic to tree $ T $ . Since this number can get quite large, output it modulo $ 10^{9}+7 $ .

Two subtrees of tree $ S $ are considered different, if there exists a vertex in $ S $ that belongs to exactly one of them.

Tree $ G $ is called isomorphic to tree $ H $ if there exists a bijection $ f $ from the set of vertices of $ G $ to the set of vertices of $ H $ that has the following property: if there is an edge between vertices $ A $ and $ B $ in tree $ G $ , then there must be an edge between vertices $ f(A) $ and $ f(B) $ in tree $ H $ . And vice versa — if there is an edge between vertices $ A $ and $ B $ in tree $ H $ , there must be an edge between $ f^{-1}(A) $ and $ f^{-1}(B) $ in tree $ G $ .

## 输入格式

The first line contains a single integer $ |S| $ ( $ 1<=|S|<=1000 $ ) — the number of vertices of tree $ S $ .

Next $ |S|-1 $ lines contain two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=|S| $ ) and describe edges of tree $ S $ .

The next line contains a single integer $ |T| $ ( $ 1<=|T|<=12 $ ) — the number of vertices of tree $ T $ .

Next $ |T|-1 $ lines contain two integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i},y_{i}<=|T| $ ) and describe edges of tree $ T $ .

## 输出格式

On the first line output a single integer — the answer to the given task modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
5
1 2
2 3
3 4
4 5
3
1 2
2 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
2 3
3 1
3
1 2
1 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
7
1 2
1 3
1 4
1 5
1 6
1 7
4
4 1
4 2
4 3

```

### 输出

```
20

```

## 样例 #4

### 输入

```
5
1 2
2 3
3 4
4 5
4
4 1
4 2
4 3

```

### 输出

```
0

```

