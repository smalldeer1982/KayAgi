---
title: "GCDEX2 - GCD Extreme (hard)"
layout: "post"
diff: 省选/NOI-
pid: SP19985
tag: ['标签461']
---

# GCDEX2 - GCD Extreme (hard)

## 题目描述

This problem is a harder version of [GCDEX](../GCDEX).

Let

 $$ G(n) = \sum _{i=1}^{n} \sum _{j=i+1}^{n} \gcd(i, j). $$

For example, $ G(1) = 0 $ , $ G(2) = \gcd(1, 2) = 1 $ , $ G(3) = \gcd(1, 2) + \gcd(1, 3) + \gcd(2, 3) = 3 $ .

Given $ N $ , find $ G(N) $ **modulo** $ 2^{64} $ .

## 输入格式

First line of contains $ T $ ( $ 1 \le T \le 10000 $ ), the number of test cases.

Each of the next $ T $ lines contains a single integer $ N $ . ( $ 1 \le N \le 235711131719 $ )

## 输出格式

For each number $ N $ , output a single line containing $ G(N) $ **modulo** $ 2^{64} $ .

## 样例 #1

### 输入

```
5
1
4
100
1000000
100000000000

```

### 输出

```
0
7
13015
4071628673912
5482289417216306300

```

