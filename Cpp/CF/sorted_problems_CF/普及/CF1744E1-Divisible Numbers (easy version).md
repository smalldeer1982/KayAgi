---
title: "Divisible Numbers (easy version)"
layout: "post"
diff: 普及/提高-
pid: CF1744E1
tag: []
---

# Divisible Numbers (easy version)

## 题目描述

This is an easy version of the problem. The only difference between an easy and a hard version is the constraints on $ a $ , $ b $ , $ c $ and $ d $ .

You are given $ 4 $ positive integers $ a $ , $ b $ , $ c $ , $ d $ with $ a < c $ and $ b < d $ . Find any pair of numbers $ x $ and $ y $ that satisfies the following conditions:

- $ a < x \leq c $ , $ b < y \leq d $ ,
- $ x \cdot y $ is divisible by $ a \cdot b $ .

Note that required $ x $ and $ y $ may not exist.

## 输入格式

The first line of the input contains a single integer $ t $ $ (1 \leq t \leq 10 $ ), the number of test cases.

The descriptions of the test cases follow.

The only line of each test case contains four integers $ a $ , $ b $ , $ c $ and $ d $ ( $ 1 \leq a < c \leq 10^5 $ , $ 1 \leq b < d \leq 10^5 $ ).

## 输出格式

For each test case print a pair of numbers $ a < x \leq c $ and $ b < y \leq d $ such that $ x \cdot y $ is divisible by $ a \cdot b $ . If there are multiple answers, print any of them. If there is no such pair of numbers, then print -1 -1.

## 样例 #1

### 输入

```
5
1 1 2 2
3 4 5 7
8 9 15 18
12 21 14 24
36 60 48 66
```

### 输出

```
2 2
4 6
12 12
-1 -1
-1 -1
```

