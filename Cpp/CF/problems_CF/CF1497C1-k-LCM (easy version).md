---
title: "k-LCM (easy version)"
layout: "post"
diff: 普及-
pid: CF1497C1
tag: []
---

# k-LCM (easy version)

## 题目描述

It is the easy version of the problem. The only difference is that in this version $ k = 3 $ .

You are given a positive integer $ n $ . Find $ k $ positive integers $ a_1, a_2, \ldots, a_k $ , such that:

- $ a_1 + a_2 + \ldots + a_k = n $
- $ LCM(a_1, a_2, \ldots, a_k) \le \frac{n}{2} $

Here $ LCM $ is the [least common multiple](https://en.wikipedia.org/wiki/Least_common_multiple) of numbers $ a_1, a_2, \ldots, a_k $ .

We can show that for given constraints the answer always exists.

## 输入格式

The first line contains a single integer $ t $ $ (1 \le t \le 10^4) $ — the number of test cases.

The only line of each test case contains two integers $ n $ , $ k $ ( $ 3 \le n \le 10^9 $ , $ k = 3 $ ).

## 输出格式

For each test case print $ k $ positive integers $ a_1, a_2, \ldots, a_k $ , for which all conditions are satisfied.

## 样例 #1

### 输入

```
3
3 3
8 3
14 3
```

### 输出

```
1 1 1
4 2 2
2 6 6
```

