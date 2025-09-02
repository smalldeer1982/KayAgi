---
title: "k-Tree"
layout: "post"
diff: 普及+/提高
pid: CF431C
tag: ['动态规划 DP']
---

# k-Tree

## 题目描述

Quite recently a creative student Lesha had a lecture on trees. After the lecture Lesha was inspired and came up with the tree of his own which he called a $ k $ -tree.

A $ k $ -tree is an infinite rooted tree where:

- each vertex has exactly $ k $ children;
- each edge has some weight;
- if we look at the edges that goes from some vertex to its children (exactly $ k $ edges), then their weights will equal $ 1,2,3,...,k $ .

The picture below shows a part of a 3-tree.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF431C/83eea7df0a509cbc1e6d27ff0b5f74fa2e2e451c.png)

 As soon as Dima, a good friend of Lesha, found out about the tree, he immediately wondered: "How many paths of total weight $ n $ (the sum of all weights of the edges in the path) are there, starting from the root of a $ k $ -tree and also containing at least one edge of weight at least $ d $ ?".Help Dima find an answer to his question. As the number of ways can be rather large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

A single line contains three space-separated integers: $ n $ , $ k $ and $ d $ ( $ 1<=n,k<=100; $ $ 1<=d<=k $ ).

## 输出格式

Print a single integer — the answer to the problem modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
3 3 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 3 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
4 3 2

```

### 输出

```
6

```

## 样例 #4

### 输入

```
4 5 2

```

### 输出

```
7

```

