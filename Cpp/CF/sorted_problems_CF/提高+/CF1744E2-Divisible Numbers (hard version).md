---
title: "Divisible Numbers (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF1744E2
tag: []
---

# Divisible Numbers (hard version)

## 题目描述

This is an hard version of the problem. The only difference between an easy and a hard version is the constraints on $ a $ , $ b $ , $ c $ and $ d $ .

You are given $ 4 $ positive integers $ a $ , $ b $ , $ c $ , $ d $ with $ a < c $ and $ b < d $ . Find any pair of numbers $ x $ and $ y $ that satisfies the following conditions:

- $ a < x \leq c $ , $ b < y \leq d $ ,
- $ x \cdot y $ is divisible by $ a \cdot b $ .

Note that required $ x $ and $ y $ may not exist.

## 输入格式

The first line of the input contains a single integer $ t $ $ (1 \leq t \leq 10 $ ), the number of test cases.

The descriptions of the test cases follow.

The only line of each test case contains four integers $ a $ , $ b $ , $ c $ and $ d $ ( $ 1 \leq a < c \leq 10^9 $ , $ 1 \leq b < d \leq 10^9 $ ).

## 输出格式

For each test case print a pair of numbers $ a < x \leq c $ and $ b < y \leq d $ such that $ x \cdot y $ is divisible by $ a \cdot b $ . If there are multiple answers, print any of them. If there is no such pair of numbers, then print -1 -1.

## 样例 #1

### 输入

```
10
1 1 2 2
3 4 5 7
8 9 15 18
12 21 14 24
36 60 48 66
1024 729 373248 730
1024 729 373247 730
5040 40320 40319 1000000000
999999999 999999999 1000000000 1000000000
268435456 268435456 1000000000 1000000000
```

### 输出

```
2 2
4 6
12 12
-1 -1
-1 -1
373248 730
-1 -1
15120 53760
-1 -1
536870912 536870912
```

