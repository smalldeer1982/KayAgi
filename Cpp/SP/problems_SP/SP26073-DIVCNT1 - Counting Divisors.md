---
title: "DIVCNT1 - Counting Divisors"
layout: "post"
diff: NOI/NOI+/CTSC
pid: SP26073
tag: ['Stern-Brocot 树']
---

# DIVCNT1 - Counting Divisors

## 题目描述

Let $ \sigma_0(n) $ be the number of positive divisors of $ n $ .

For example, $ \sigma_0(1) = 1 $ , $ \sigma_0(2) = 2 $ and $ \sigma_0(6) = 4 $ .

Let 

$$ S_1(n) = \sum _{i=1}^n \sigma_0(i). $$

Given $ N $ , find $ S_1(N) $ .

## 输入格式

First line contains $ T $ ( $ 1 \le T \le 100000 $ ), the number of test cases.

Each of the next $ T $ lines contains a single integer $ N $ . ( $ 1 \le N < 2^{63} $ )

## 输出格式

For each number $ N $ , output a single line containing $ S_1(N) $ .

## 样例 #1

### 输入

```
5
1
2
3
10
100
```

### 输出

```
1
3
5
27
482
```

