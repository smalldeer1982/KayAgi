---
title: "SEQ - Recursive Sequence"
layout: "post"
diff: 难度0
pid: SP339
tag: []
---

# SEQ - Recursive Sequence

## 题目描述

Sequence _(a $ _{i} $ )_ of natural numbers is defined as follows:  
  
 _a $ _{i} $ = b $ _{i} $_  (for _i <= k_)  
 _a $ _{i} $ = c $ _{1} $ a $ _{i-1} $ + c $ _{2} $ a $ _{i-2} $ + ... + c $ _{k} $ a $ _{i-k} $_  (for _i > k_)  
  
 where _b $ _{j} $_  and _c $ _{j} $_  are given natural numbers for _1<=j<=k_. Your task is to compute _a $ _{n} $_  for given _n_ and output it modulo _10 $ ^{9} $_ .

## 输入格式

On the first row there is the number _C_ of test cases (equal to about 1000).  
 Each test contains four lines:

_k_ - number of elements of _(c)_ and _(b)_ (_1 <= k <= 10_)  
_b $ _{1} $ ,...,b $ _{k} $_  - _k_ natural numbers where _0 <= b $ _{j} $ <= 10 $ ^{9} $_  separated by spaces  
_c $ _{1} $ ,...,c $ _{k} $_  - _k_ natural numbers where _0 <= c $ _{j} $ <= 10 $ ^{9} $_  separated by spaces  
_n_ - natural number (_1 <= n <= 10 $ ^{9} $_ )

## 输出格式

Exactly _C_ lines, one for each test case: _a $ _{n} $_  modulo _10 $ ^{9} $_

## 样例 #1

### 输入

```
3 
3 
5 8 2 
32 54 6 
2 
3 
1 2 3 
4 5 6 
6 
3 
24 354 6 
56 57 465 
98765432
```

### 输出

```
8 
714 
257599514
```

