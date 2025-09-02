---
title: "Random Forest Rank"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1067E
tag: []
---

# Random Forest Rank

## 题目描述

Let's define rank of undirected graph as rank of its adjacency matrix in $ \mathbb{R}^{n \times n} $ .

Given a tree. Each edge of this tree will be deleted with probability $ 1/2 $ , all these deletions are independent. Let $ E $ be the expected rank of resulting forest. Find $ E \cdot 2^{n-1} $ modulo $ 998244353 $ (it is easy to show that $ E \cdot 2^{n-1} $ is an integer).

## 输入格式

First line of input contains $ n $ ( $ 1 \le n \le 5 \cdot 10^{5} $ ) — number of vertices.

Next $ n-1 $ lines contains two integers $ u $ $ v $ ( $ 1 \le u, \,\, v \le n; \,\, u \ne v $ ) — indices of vertices connected by edge.

It is guaranteed that given graph is a tree.

## 输出格式

Print one integer — answer to the problem.

## 样例 #1

### 输入

```
3
1 2
2 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4
1 2
1 3
1 4

```

### 输出

```
14

```

## 样例 #3

### 输入

```
4
1 2
2 3
3 4

```

### 输出

```
18

```

