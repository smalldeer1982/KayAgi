---
title: "Counting Is Fun (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1943D1
tag: []
---

# Counting Is Fun (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ n $ . You can make hacks only if both versions of the problem are solved.

An array $ b $ of $ m $ non-negative integers is said to be good if all the elements of $ b $ can be made equal to $ 0 $ using the following operation some (possibly, zero) times:

- Select two distinct indices $ l $ and $ r $ ( $ 1 \leq l \color{red}{<} r \leq m $ ) and subtract $ 1 $ from all $ b_i $ such that $ l \leq i \leq r $ .

You are given two positive integers $ n $ , $ k $ and a prime number $ p $ .

Over all $ (k+1)^n $ arrays of length $ n $ such that $ 0 \leq a_i \leq k $ for all $ 1 \leq i \leq n $ , count the number of good arrays.

Since the number might be too large, you are only required to find it modulo $ p $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains three positive integers $ n $ , $ k $ and $ p $ ( $ 3 \leq n \leq 400 $ , $ 1 \leq k \leq n $ , $ 10^8 < p < 10^9 $ ) — the length of the array $ a $ , the upper bound on the elements of $ a $ and modulus $ p $ .

It is guaranteed that the sum of $ n^2 $ over all test cases does not exceed $ 2 \cdot 10^5 $ , and $ p $ is prime.

## 输出格式

For each test case, on a new line, output the number of good arrays modulo $ p $ .

## 说明/提示

In the first test case, the $ 4 $ good arrays $ a $ are:

- $ [0,0,0] $ ;
- $ [0,1,1] $ ;
- $ [1,1,0] $ ;
- $ [1,1,1] $ .

## 样例 #1

### 输入

```
4
3 1 998244853
4 1 998244353
3 2 998244353
343 343 998244353
```

### 输出

```
4
7
10
456615865
```

