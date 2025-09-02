---
title: "KQUERY - K-query"
layout: "post"
diff: 提高+/省选-
pid: SP3266
tag: []
---

# KQUERY - K-query

## 题目描述

[English](/problems/KQUERY/en/) [Vietnamese](/problems/KQUERY/vn/)Given a sequence of n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ and a number of k- queries. A k-query is a triple (i, j, k) (1 ≤ i ≤ j ≤ n). For each k-query (i, j, k), you have to return the number of elements greater than k in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ .

## 输入格式

- Line 1: n (1 ≤ n ≤ 30000).
- Line 2: n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ (1 ≤ a $ _{i} $ ≤ 10 $ ^{9} $ ).
- Line 3: q (1 ≤ q ≤ 200000), the number of k- queries.
- In the next q lines, each line contains 3 numbers i, j, k representing a k-query (1 ≤ i ≤ j ≤ n, 1 ≤ k ≤ 10 $ ^{9} $ ).

## 输出格式

- For each k-query (i, j, k), print the number of elements greater than k in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ in a single line.

## 样例 #1

### 输入

```
5
5 1 2 3 4
3
2 4 1
4 4 4
1 5 2
```

### 输出

```
2
0
3
```

