---
title: "Distinct Split"
layout: "post"
diff: 普及-
pid: CF1791D
tag: []
---

# Distinct Split

## 题目描述

Let's denote the $ f(x) $ function for a string $ x $ as the number of distinct characters that the string contains. For example $ f(\texttt{abc}) = 3 $ , $ f(\texttt{bbbbb}) = 1 $ , and $ f(\texttt{babacaba}) = 3 $ .

Given a string $ s $ , split it into two non-empty strings $ a $ and $ b $ such that $ f(a) + f(b) $ is the maximum possible. In other words, find the maximum possible value of $ f(a) + f(b) $ such that $ a + b = s $ (the concatenation of string $ a $ and string $ b $ is equal to string $ s $ ).

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 2 \leq n \leq 2\cdot10^5 $ ) — the length of the string $ s $ .

The second line contains the string $ s $ , consisting of lowercase English letters.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum possible value of $ f(a) + f(b) $ such that $ a + b = s $ .

## 说明/提示

For the first test case, there is only one valid way to split $ \texttt{aa} $ into two non-empty strings $ \texttt{a} $ and $ \texttt{a} $ , and $ f(\texttt{a}) + f(\texttt{a}) = 1 + 1 = 2 $ .

For the second test case, by splitting $ \texttt{abcabcd} $ into $ \texttt{abc} $ and $ \texttt{abcd} $ we can get the answer of $ f(\texttt{abc}) + f(\texttt{abcd}) = 3 + 4 = 7 $ which is maximum possible.

For the third test case, it doesn't matter how we split the string, the answer will always be $ 2 $ .

## 样例 #1

### 输入

```
5
2
aa
7
abcabcd
5
aaaaa
10
paiumoment
4
aazz
```

### 输出

```
2
7
2
10
3
```

