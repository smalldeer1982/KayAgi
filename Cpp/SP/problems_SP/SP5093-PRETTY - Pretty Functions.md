---
title: "PRETTY - Pretty Functions"
layout: "post"
diff: 难度0
pid: SP5093
tag: []
---

# PRETTY - Pretty Functions

## 题目描述

Let S = {1, 2, 3, ..., N}.  
For a given positive integer K, the function f : S --> S is called "pretty" if, for every X in S, it holds that  
f ( f ( f ( ... f ( X ) ... ) ) ) = X, where f is repeated exactly K times.  
  
How many pretty functions are there, modulo M?

## 输入格式

Three natural numbers N, K and M. It holds that 1 <= K <= N <= 30 000 and M <= 10^9.

## 输出格式

Number of pretty functions modulo M.

## 样例 #1

### 输入

```
\n2 1\n1000\n\n
```

### 输出

```
\n1
```

