---
title: "APS2 - Amazing Prime Sequence (hard)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: SP19975
tag: []
---

# APS2 - Amazing Prime Sequence (hard)

## 题目描述

This problem is a harder version of [APS](../APS).

Let $ f(n) $ be the smallest prime factor of $ n $ . For example, $ f(2) = 2,\ f(4) = 2 $ and $ f(35) = 5 $ .

The sequence $ S(n) $ is defined for all positive integers as follows:

\- $ S(1) = 0 $

\- $ S(n) = S(n-1) + f(n) $ (if $ n \ge 2 $ )

Given $ N $ , find $ S(N) $ **modulo** $ 2^{64} $ .

## 输入格式

First line contains $ T $ ( $ 1 \le T \le 10000 $ ), the number of test cases.

Each of the next $ T $ lines contains a single integer $ N $ . ( $ 1 \le N \le 1234567891011 $ )

## 输出格式

For each integer $ N $ , output a single line containing $ S(N) $ **modulo** $ 2^{64} $ .

## 样例 #1

### 输入

```
5
1
4
100
1000000
1000000000000
```

### 输出

```
0
7
1257
37568404989
7294954823202325427
```

