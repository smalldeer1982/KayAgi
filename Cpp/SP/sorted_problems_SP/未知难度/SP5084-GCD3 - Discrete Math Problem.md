---
title: "GCD3 - Discrete Math Problem"
layout: "post"
diff: 难度0
pid: SP5084
tag: []
---

# GCD3 - Discrete Math Problem

## 题目描述

Given N, M and K (1 <= N, M <= 100^200 and 1 <= K <= 16) which  
  
N = a + b  
M = a^2 + b^2 - (2^K - 2)  \* a \* b  
  
with a > 0, b > 0 and gcd(a, b) = 1.  
  
Your task is to find gcd(N, M).

## 输入格式

The input file consists of several data sets. The first line contains  
the number of data sets T (1 <= T <= 10000). The fallowing T lines  
describe the data sets, one triple (N, M, K) for each.

## 输出格式

For each data test in the input write the gcd(N, M).

## 样例 #1

### 输入

```
\n\n2\n648570884104668119354133 420644191708310845403065233058235585438328857465 5\n8017723549 59173349743176010825 9\n
```

### 输出

```
\n\n1\n1\n\nNote: For the first trio a = 648570884104668119354126 and b = 7.\nFor the second a = 8016478423 and b = 1245126.\n
```

