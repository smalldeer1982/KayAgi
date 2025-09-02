---
title: "TREEISO - Tree Isomorphism"
layout: "post"
diff: 省选/NOI-
pid: SP7826
tag: []
---

# TREEISO - Tree Isomorphism

## 题目描述

Given two undirected trees T1 and T2 with equal number of vertices N (1   
Two trees T1 and T2 are isomorphic if there is a bijection f between the vertex sets of T1 and T2 such that any two vertices u and v of T1 are adjacent in T1 if and only if f(u) and f(v) are adjacent in T2.

## 输入格式

The first line of input contains the number of test cases nTest (1<= nTest <= 400). Each test case contains:

- The first line contains the number of nodes N.
- Each of next N-1 lines contain two integers A, B, denoting that there is an edge in T1 between nodes A and B (1
- Each of next N-1 lines contain two integers A, B, denoting that there is an edge in T2 between nodes A and B (1

The sum of N over all test cases will not exceed 100,000.

## 输出格式

For each test case print YES if T1 and T2 are isomorphic and NO otherwise.

## 样例 #1

### 输入

```
2
4
4 2
4 1
2 3
4 2
2 3
4 1
5
3 4
3 2
3 5
3 1
3 4
4 2
2 5
2 1
```

### 输出

```
YES
NO
```

