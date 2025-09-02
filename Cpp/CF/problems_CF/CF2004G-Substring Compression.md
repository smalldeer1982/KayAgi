---
title: "Substring Compression"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2004G
tag: ['动态规划 DP', '矩阵乘法', '双指针 two-pointer']
---

# Substring Compression

## 题目描述

Let's define the operation of compressing a string $ t $ , consisting of at least $ 2 $ digits from $ 1 $ to $ 9 $ , as follows:

- split it into an even number of non-empty substrings — let these substrings be $ t_1, t_2, \dots, t_m $ (so, $ t = t_1 + t_2 + \dots + t_m $ , where $ + $ is the concatenation operation);
- write the string $ t_2 $ $ t_1 $ times, then the string $ t_4 $ $ t_3 $ times, and so on.

For example, for a string "12345", one could do the following: split it into ("1", "23", "4", "5"), and write "235555".

Let the function $ f(t) $ for a string $ t $ return the minimum length of the string that can be obtained as a result of that process.

You are given a string $ s $ , consisting of $ n $ digits from $ 1 $ to $ 9 $ , and an integer $ k $ . Calculate the value of the function $ f $ for all contiguous substrings of $ s $ of length exactly $ k $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2 \le k \le n \le 2 \cdot 10^5 $ ).

The second line contains the string $ s $ ( $ |s| = n $ ), consisting only of digits from $ 1 $ to $ 9 $ .

## 输出格式

Output $ n - k + 1 $ integers — $ f(s_{1,k}), f(s_{2,k+1}), \dots, f(s_{n - k + 1, n}) $ .

## 样例 #1

### 输入

```
4 4
5999
```

### 输出

```
14
```

## 样例 #2

### 输入

```
10 3
1111111111
```

### 输出

```
2 2 2 2 2 2 2 2
```

## 样例 #3

### 输入

```
11 4
49998641312
```

### 输出

```
12 18 17 15 12 7 7 2
```

