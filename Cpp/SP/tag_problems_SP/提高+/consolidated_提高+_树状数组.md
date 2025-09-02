---
title: "USUBQSUB - Update Sub-Matrix & Query Sub-Matrix"
layout: "post"
diff: 提高+/省选-
pid: SP15914
tag: ['树状数组']
---

# USUBQSUB - Update Sub-Matrix & Query Sub-Matrix

## 题目描述

Updating and querying 1 dimensional arrays is a popular question. How about updating and quering sub-matrices of a matrix?

A sub-matrix will be depicted as (a, b), (c, d). This implies that it will include all the cells (x, y) such that a<=x<=c and b<=y<=d.

The matrix is indexed from \[1..N\]\[1..N\], where N is the size.

You are given a matrix of size NxN, with each element initially set to 0. There are M queries and each query can be of one of the two types:

1 x1 y1 x2 y2: This query asks you to return the sum of all the elements in the sub-matrix (x1, y1), (x2, y2).

2 x1 y1 x2 y2 K: This query asks you to add K to each element in the sub-matrix (x1, y1), (x2, y2).

## 输入格式

The first line of input contains N, M.

The next M lines contain queries in the same forms as stated above.

You may assume that x1<=x2 and y1<=y2 for all queries.

Also N<=1000 and M<=10 $ ^{5} $ . K<=10 $ ^{9} $

## 输出格式

The answer to all the queries wherein you need to return the sum of elements in the sub-matrix, i.e., all the queries of type 1.



---

---
title: "DQUERY - D-query"
layout: "post"
diff: 提高+/省选-
pid: SP3267
tag: ['莫队', '线段树', '树状数组', '可持久化线段树']
---

# DQUERY - D-query

## 题目描述

[English](/problems/DQUERY/en/) [Vietnamese](/problems/DQUERY/vn/)Given a sequence of n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ and a number of d-queries. A d-query is a pair (i, j) (1 ≤ i ≤ j ≤ n). For each d-query (i, j), you have to return the number of distinct elements in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ .

## 输入格式

- Line 1: n (1 ≤ n ≤ 30000).
- Line 2: n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ (1 ≤ a $ _{i} $ ≤ 10 $ ^{6} $ ).
- Line 3: q (1 ≤ q ≤ 200000), the number of d-queries.
- In the next q lines, each line contains 2 numbers i, j representing a d-query (1 ≤ i ≤ j ≤ n).

## 输出格式

- For each d-query (i, j), print the number of distinct elements in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ in a single line.

## 样例 #1

### 输入

```
5
1 1 2 1 3
3
1 5
2 4
3 5
```

### 输出

```
3
2
3
```



---

