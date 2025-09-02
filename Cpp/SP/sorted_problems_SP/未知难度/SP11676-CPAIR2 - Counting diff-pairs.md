---
title: "CPAIR2 - Counting diff-pairs"
layout: "post"
diff: 难度0
pid: SP11676
tag: []
---

# CPAIR2 - Counting diff-pairs

## 题目描述

You are given sequence A of N integers. You are also given integer K and M queries. Each query consists of two integers l, r. For each query output number of pairs i, j such that l <= i < j <= r and abs(A\[i\] - A\[j\]) >= K.

Indexing starts with 1.

N <= 50000

M <= 50000

1 <= A\[i\] <= 100000

NOTE: All tests are randomly generated.

## 输入格式

First line of input contains integers N, M, K in this order.

Second line contains N integers representing array A.

Next M lines describe queries.

## 输出格式

Output answer for each query.

## 样例 #1

### 输入

```
3 1 2\n1 2 3\n1 3\n
```

### 输出

```
1
```

