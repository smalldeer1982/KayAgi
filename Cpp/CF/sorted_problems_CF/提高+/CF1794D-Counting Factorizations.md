---
title: "Counting Factorizations"
layout: "post"
diff: 提高+/省选-
pid: CF1794D
tag: []
---

# Counting Factorizations

## 题目描述

The prime factorization of a positive integer $ m $ is the unique way to write it as $ \displaystyle m=p_1^{e_1}\cdot p_2^{e_2}\cdot \ldots \cdot p_k^{e_k} $ , where $ p_1, p_2, \ldots, p_k $ are prime numbers, $ p_1 < p_2 < \ldots < p_k $ and $ e_1, e_2, \ldots, e_k $ are positive integers.

For each positive integer $ m $ , $ f(m) $ is defined as the multiset of all numbers in its prime factorization, that is $ f(m)=\{p_1,e_1,p_2,e_2,\ldots,p_k,e_k\} $ .

For example, $ f(24)=\{2,3,3,1\} $ , $ f(5)=\{1,5\} $ and $ f(1)=\{\} $ .

You are given a list consisting of $ 2n $ integers $ a_1, a_2, \ldots, a_{2n} $ . Count how many positive integers $ m $ satisfy that $ f(m)=\{a_1, a_2, \ldots, a_{2n}\} $ . Since this value may be large, print it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1\le n \le 2022 $ ).

The second line contains $ 2n $ integers $ a_1, a_2, \ldots, a_{2n} $ ( $ 1\le a_i\le 10^6 $ ) — the given list.

## 输出格式

Print one integer, the number of positive integers $ m $ satisfying $ f(m)=\{a_1, a_2, \ldots, a_{2n}\} $ modulo $ 998\,244\,353 $ .

## 说明/提示

In the first sample, the two values of $ m $ such that $ f(m)=\{1,2,3,3\} $ are $ m=24 $ and $ m=54 $ . Their prime factorizations are $ 24=2^3\cdot 3^1 $ and $ 54=2^1\cdot 3^3 $ .

In the second sample, the five values of $ m $ such that $ f(m)=\{2,2,3,5\} $ are $ 200, 225, 288, 500 $ and $ 972 $ .

In the third sample, there is no value of $ m $ such that $ f(m)=\{1,4\} $ . Neither $ 1^4 $ nor $ 4^1 $ are prime factorizations because $ 1 $ and $ 4 $ are not primes.

## 样例 #1

### 输入

```
2
1 3 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
2 2 3 5
```

### 输出

```
5
```

## 样例 #3

### 输入

```
1
1 4
```

### 输出

```
0
```

