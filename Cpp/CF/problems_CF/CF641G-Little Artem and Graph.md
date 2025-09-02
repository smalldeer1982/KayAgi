---
title: "Little Artem and Graph"
layout: "post"
diff: 提高+/省选-
pid: CF641G
tag: []
---

# Little Artem and Graph

## 题目描述

Little Artem is given a graph, constructed as follows: start with some $ k $ -clique, then add new vertices one by one, connecting them to $ k $ already existing vertices that form a $ k $ -clique.

Artem wants to count the number of spanning trees in this graph modulo $ 10^{9}+7 $ .

## 输入格式

First line of the input contains two integers $ n $ and $ k $ ( $ 1<=n<=10000 $ , $ 1<=k<=min(n,5) $ ) — the total size of the graph and the size of the initial clique, respectively.

Next $ n-k $ lines describe $ k+1 $ -th, $ k+2 $ -th, ..., $ i $ -th, ..., $ n $ -th vertices by listing $ k $ distinct vertex indices $ 1<=a_{ij}&lt;i $ it is connected to. It is guaranteed that those vertices form a k-clique.

## 输出格式

Output a single integer — the number of spanning trees in the given graph modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
3 2
1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 3
1 2 3

```

### 输出

```
16

```

