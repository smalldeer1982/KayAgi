---
title: "Oolimry and Suffix Array"
layout: "post"
diff: 提高+/省选-
pid: CF1526E
tag: []
---

# Oolimry and Suffix Array

## 题目描述

Once upon a time, Oolimry saw a suffix array. He wondered how many strings can produce this suffix array.

More formally, given a suffix array of length $ n $ and having an alphabet size $ k $ , count the number of strings that produce such a suffix array.

Let $ s $ be a string of length $ n $ . Then the $ i $ -th suffix of $ s $ is the substring $ s[i \ldots n-1] $ . A suffix array is the array of integers that represent the starting indexes of all the suffixes of a given string, after the suffixes are sorted in the lexicographic order. For example, the suffix array of oolimry is $ [3,2,4,1,0,5,6] $ as the array of sorted suffixes is $ [\texttt{imry},\texttt{limry},\texttt{mry},\texttt{olimry},\texttt{oolimry},\texttt{ry},\texttt{y}] $ .

A string $ x $ is lexicographically smaller than string $ y $ , if either $ x $ is a prefix of $ y $ (and $ x\neq y $ ), or there exists such $ i $ that $ x_i < y_i $ , and for any $ 1\leq j < i $ , $ x_j = y_j $ .

## 输入格式

The first line contain 2 integers $ n $ and $ k $ ( $ 1 \leq n \leq 200000,1 \leq k \leq 200000 $ ) — the length of the suffix array and the alphabet size respectively.

The second line contains $ n $ integers $ s_0, s_1, s_2, \ldots, s_{n-1} $ ( $ 0 \leq s_i \leq n-1 $ ) where $ s_i $ is the $ i $ -th element of the suffix array i.e. the starting position of the $ i $ -th lexicographically smallest suffix. It is guaranteed that for all $ 0 \leq i< j \leq n-1 $ , $ s_i \neq s_j $ .

## 输出格式

Print how many strings produce such a suffix array. Since the number can be very large, print the answer modulo $ 998244353 $ .

## 说明/提示

In the first test case, "abb" is the only possible solution.

In the second test case, it can be easily shown no possible strings exist as all the letters have to be equal.

In the fourth test case, one possible string is "ddbacef".

Please remember to print your answers modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3 2
0 2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 1
0 1 2 3 4
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6 200000
0 1 2 3 4 5
```

### 输出

```
822243495
```

## 样例 #4

### 输入

```
7 6
3 2 4 1 0 5 6
```

### 输出

```
36
```

