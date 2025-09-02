---
title: "DIVCNTK - Counting Divisors (general)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: SP34096
tag: []
---

# DIVCNTK - Counting Divisors (general)

## 题目描述

Let $\sigma_0(n)$ be the number of positive divisors of $n$.

For example, $\sigma_0(1) = 1$ , $\sigma_0(2) = 2$ and $\sigma_0(6) = 4$.

Let $S_k(n) = \sum _{i=1}^n \sigma_0(i^k)$.

Given $n$ and $k$ , find $S_k(n) \bmod 2^{64}$.

## 输入格式

There are multiple test cases. The first line of input contains an integer $ T $ ( $ 1 \le T \le 10000 $ ), indicating the number of test cases. For each test case:

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 10^{10} $ ).

## 输出格式

For each test case, output a single line containing $ S_k(n) \bmod 2^{64} $ .

## 说明/提示

+ Input #1: $1\leq n\leq 10000,TL=1s$
+ Input #2: $1\leq T\leq 300,1\leq n\leq 10^{7},TL=5s$
+ Input #3: $1\leq T\leq 75,1\leq n\leq 10^{8},TL=5s$
+ Input #4: $1\leq T\leq 15,1\leq n\leq 10^{9},TL=5s$
+ Input #5: $1\leq T\leq 5,1\leq n\leq 10^{10},TL=5s$

## 样例 #1

### 输入

```
5
1 3
2 3
3 3
10 3
100 3
```

### 输出

```
1
5
9
73
2302
```

