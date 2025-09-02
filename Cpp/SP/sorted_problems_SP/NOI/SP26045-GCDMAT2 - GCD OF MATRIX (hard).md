---
title: "GCDMAT2 - GCD OF MATRIX (hard)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: SP26045
tag: []
---

# GCDMAT2 - GCD OF MATRIX (hard)

## 题目描述

You have given a matrix of size nxm. Every cell of matrix denote gcd of respective indices. For ex-

A 3x2 matrix have entries

 gcd(1,1)   gcd(1,2) gcd(2,1)  gcd(2,2) gcd(3,1)  gcd(3,2)You have given queries i1 j1 i2 j2.

You have to find the sum of matrix formed by upper left corner (i1,j1) and lower right corner (i2,j2).

## 输入格式

First line indicates number of testcases. (T<=50000)

Next line have space separated two integer n and m. (1<=n,m<=1000000).

Next T lines contains queries i1 j1 i2 j2.

where i1<=i2 j1<=j2.

## 输出格式

Print ans modulo M for each query in newline. (M=10^9+7)

## 样例 #1

### 输入

```
2
3 2
1 1 2 2
2 1 3 2
```

### 输出

```
5
5
```

