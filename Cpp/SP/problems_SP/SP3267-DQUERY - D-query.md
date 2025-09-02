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

