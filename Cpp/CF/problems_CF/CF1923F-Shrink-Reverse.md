---
title: "Shrink-Reverse"
layout: "post"
diff: 省选/NOI-
pid: CF1923F
tag: ['后缀自动机 SAM', '后缀数组 SA']
---

# Shrink-Reverse

## 题目描述

You are given a binary string $ s $ of length $ n $ (a string consisting of $ n $ characters, and each character is either 0 or 1).

Let's look at $ s $ as at a binary representation of some integer, and name that integer as the value of string $ s $ . For example, the value of 000 is $ 0 $ , the value of 01101 is $ 13 $ , "100000" is $ 32 $ and so on.

You can perform at most $ k $ operations on $ s $ . Each operation should have one of the two following types:

- SWAP: choose two indices $ i < j $ in $ s $ and swap $ s_i $ with $ s_j $ ;
- SHRINK-REVERSE: delete all leading zeroes from $ s $ and reverse $ s $ .

 For example, after you perform SHRINK-REVERSE on 000101100, you'll get 001101.What is the minimum value of $ s $ you can achieve by performing at most $ k $ operations on $ s $ ?

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2 \le n \le 5 \cdot 10^5 $ ; $ 1 \le k \le n $ ) — the length of the string $ s $ and the maximum number of operations.

The second line contains the string $ s $ of length $ n $ consisting of characters 0 and/or 1.

Additional constraint on the input: $ s $ contains at least one 1.

## 输出格式

Print a single integer — the minimum value of $ s $ you can achieve using no more than $ k $ operations. Since the answer may be too large, print it modulo $ 10^{9} + 7 $ .

Note that you need to minimize the original value, not the remainder.

## 说明/提示

In the first example, one of the optimal strategies is the following:

1. 10010010 $ \xrightarrow{\texttt{SWAP}} $ 00010110;
2. 00010110 $ \xrightarrow{\texttt{SWAP}} $ 00000111.

 The value of 00000111 is $ 7 $ .In the second example, one of the optimal strategies is the following:

1. 01101000 $ \xrightarrow{\texttt{SHRINK}} $ 1101000 $ \xrightarrow{\texttt{REVERSE}} $ 0001011;
2. 0001011 $ \xrightarrow{\texttt{SWAP}} $ 0000111.

 The value of 0000111 is $ 7 $ .

## 样例 #1

### 输入

```
8 2
10010010
```

### 输出

```
7
```

## 样例 #2

### 输入

```
8 2
01101000
```

### 输出

```
7
```

## 样例 #3

### 输入

```
30 30
111111111111111111111111111111
```

### 输出

```
73741816
```

## 样例 #4

### 输入

```
14 1
10110001111100
```

### 输出

```
3197
```

