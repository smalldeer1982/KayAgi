---
title: "Maximum Substring"
layout: "post"
diff: 入门
pid: CF1750B
tag: ['枚举']
---

# Maximum Substring

## 题目描述

A binary string is a string consisting only of the characters 0 and 1. You are given a binary string $ s $ .

For some non-empty substring $ ^\dagger $ $ t $ of string $ s $ containing $ x $ characters 0 and $ y $ characters 1, define its cost as:

- $ x \cdot y $ , if $ x > 0 $ and $ y > 0 $ ;
- $ x^2 $ , if $ x > 0 $ and $ y = 0 $ ;
- $ y^2 $ , if $ x = 0 $ and $ y > 0 $ .

Given a binary string $ s $ of length $ n $ , find the maximum cost across all its non-empty substrings.

 $ ^\dagger $ A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the string $ s $ .

The second line of each test case contains a binary string $ s $ of length $ n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the maximum cost across all substrings.

## 说明/提示

In the first test case, we can take a substring $ 111 $ . It contains $ 3 $ characters 1 and $ 0 $ characters 0. So $ a = 3 $ , $ b = 0 $ and its cost is $ 3^2 = 9 $ .

In the second test case, we can take the whole string. It contains $ 4 $ characters 1 and $ 3 $ characters 0. So $ a = 4 $ , $ b = 3 $ and its cost is $ 4 \cdot 3 = 12 $ .

In the third test case, we can can take a substring $ 1111 $ and its cost is $ 4^2 = 16 $ .

In the fourth test case, we can take the whole string and cost is $ 4 \cdot 3 = 12 $ .

In the fifth test case, we can take a substring $ 000 $ and its cost is $ 3 \cdot 3 = 9 $ .

In the sixth test case, we can only take the substring $ 0 $ and its cost is $ 1 \cdot 1 = 1 $ .

## 样例 #1

### 输入

```
6
5
11100
7
1100110
6
011110
7
1001010
4
1000
1
0
```

### 输出

```
9
12
16
12
9
1
```

