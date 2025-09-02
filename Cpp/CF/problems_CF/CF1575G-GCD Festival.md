---
title: "GCD Festival"
layout: "post"
diff: 省选/NOI-
pid: CF1575G
tag: []
---

# GCD Festival

## 题目描述

Mr. Chanek has an array $ a $ of $ n $ integers. The prettiness value of $ a $ is denoted as:

 $ $$$\sum_{i=1}^{n} {\sum_{j=1}^{n} {\gcd(a_i, a_j) \cdot \gcd(i, j)}} $ $ </p><p>where  $ \\gcd(x, y) $  denotes the greatest common divisor (GCD) of integers  $ x $  and  $ y $ .</p><p>In other words, the prettiness value of an array  $ a $  is the total sum of  $ \\gcd(a\_i, a\_j) \\cdot \\gcd(i, j) $  for all pairs  $ (i, j) $ .</p><p>Help Mr. Chanek find the prettiness value of  $ a $ , and output the result modulo  $ 10^9 + 7$$$!

## 输入格式

The first line contains an integer $ n $ ( $ 2 \leq n \leq 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^5 $ ).

## 输出格式

Output an integer denoting the prettiness value of $ a $ modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
5
3 6 2 1 4
```

### 输出

```
77
```

