---
title: "k-LCM (hard version)"
layout: "post"
diff: 普及/提高-
pid: CF1497C2
tag: []
---

# k-LCM (hard version)

## 题目描述

It is the hard version of the problem. The only difference is that in this version $ 3 \le k \le n $ .

You are given a positive integer $ n $ . Find $ k $ positive integers $ a_1, a_2, \ldots, a_k $ , such that:

- $ a_1 + a_2 + \ldots + a_k = n $
- $ LCM(a_1, a_2, \ldots, a_k) \le \frac{n}{2} $

Here $ LCM $ is the [least common multiple](https://en.wikipedia.org/wiki/Least_common_multiple) of numbers $ a_1, a_2, \ldots, a_k $ .

We can show that for given constraints the answer always exists.

## 输入格式

The first line contains a single integer $ t $ $ (1 \le t \le 10^4) $ — the number of test cases.

The only line of each test case contains two integers $ n $ , $ k $ ( $ 3 \le n \le 10^9 $ , $ 3 \le k \le n $ ).

It is guaranteed that the sum of $ k $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case print $ k $ positive integers $ a_1, a_2, \ldots, a_k $ , for which all conditions are satisfied.

## 样例 #1

### 输入

```
2
6 4
9 5
```

### 输出

```
1 2 2 1 
1 3 3 1 1
```

