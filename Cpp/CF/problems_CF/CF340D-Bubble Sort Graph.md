---
title: "Bubble Sort Graph"
layout: "post"
diff: 提高+/省选-
pid: CF340D
tag: []
---

# Bubble Sort Graph

## 题目描述

Iahub recently has learned Bubble Sort, an algorithm that is used to sort a permutation with $ n $ elements $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ in ascending order. He is bored of this so simple algorithm, so he invents his own graph. The graph (let's call it $ G $ ) initially has $ n $ vertices and 0 edges. During Bubble Sort execution, edges appear as described in the following algorithm (pseudocode).

`<br></br>procedure bubbleSortGraph()<br></br>    build a graph G with n vertices and 0 edges<br></br>    repeat<br></br>        swapped = false<br></br>        for i = 1 to n - 1 inclusive do:<br></br>            if a[i] > a[i + 1] then<br></br>                add an undirected edge in G between a[i] and a[i + 1]<br></br>                swap( a[i], a[i + 1] )<br></br>                swapped = true<br></br>            end if<br></br>        end for<br></br>    until not swapped <br></br>    /* repeat the algorithm as long as swapped value is true. */ <br></br>end procedure<br></br>`For a graph, an independent set is a set of vertices in a graph, no two of which are adjacent (so there are no edges between vertices of an independent set). A maximum independent set is an independent set which has maximum cardinality. Given the permutation, find the size of the maximum independent set of graph $ G $ , if we use such permutation as the premutation $ a $ in procedure bubbleSortGraph.

## 输入格式

The first line of the input contains an integer $ n $ ( $ 2<=n<=10^{5} $ ). The next line contains $ n $ distinct integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ $ (1<=a_{i}<=n) $ .

## 输出格式

Output a single integer — the answer to the problem.

## 说明/提示

Consider the first example. Bubble sort swaps elements 3 and 1. We add edge (1, 3). Permutation is now \[1, 3, 2\]. Then bubble sort swaps elements 3 and 2. We add edge (2, 3). Permutation is now sorted. We have a graph with 3 vertices and 2 edges (1, 3) and (2, 3). Its maximal independent set is \[1, 2\].

## 样例 #1

### 输入

```
3
3 1 2

```

### 输出

```
2

```

