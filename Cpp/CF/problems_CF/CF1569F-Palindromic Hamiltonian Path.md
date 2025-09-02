---
title: "Palindromic Hamiltonian Path"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1569F
tag: []
---

# Palindromic Hamiltonian Path

## 题目描述

You are given a simple undirected graph with $ n $ vertices, $ n $ is even. You are going to write a letter on each vertex. Each letter should be one of the first $ k $ letters of the Latin alphabet.

A path in the graph is called Hamiltonian if it visits each vertex exactly once. A string is called palindromic if it reads the same from left to right and from right to left. A path in the graph is called palindromic if the letters on the vertices in it spell a palindromic string without changing the order.

A string of length $ n $ is good if:

- each letter is one of the first $ k $ lowercase Latin letters;
- if you write the $ i $ -th letter of the string on the $ i $ -th vertex of the graph, there will exist a palindromic Hamiltonian path in the graph.

Note that the path doesn't necesserily go through the vertices in order $ 1, 2, \dots, n $ .

Count the number of good strings.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ k $ ( $ 2 \le n \le 12 $ ; $ n $ is even; $ 0 \le m \le \frac{n \cdot (n-1)}{2} $ ; $ 1 \le k \le 12 $ ) — the number of vertices in the graph, the number of edges in the graph and the number of first letters of the Latin alphabet that can be used.

Each of the next $ m $ lines contains two integers $ v $ and $ u $ ( $ 1 \le v, u \le n $ ; $ v \neq u $ ) — the edges of the graph. The graph doesn't contain multiple edges and self-loops.

## 输出格式

Print a single integer — number of good strings.

## 样例 #1

### 输入

```
4 3 3
1 2
2 3
3 4
```

### 输出

```
9
```

## 样例 #2

### 输入

```
4 6 3
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
21
```

## 样例 #3

### 输入

```
12 19 12
1 3
2 6
3 6
3 7
4 8
8 5
8 7
9 4
5 9
10 1
10 4
10 6
9 10
11 1
5 11
7 11
12 2
12 5
12 11
```

### 输出

```
456165084
```

