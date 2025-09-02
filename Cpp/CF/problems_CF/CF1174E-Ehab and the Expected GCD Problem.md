---
title: "Ehab and the Expected GCD Problem"
layout: "post"
diff: 省选/NOI-
pid: CF1174E
tag: []
---

# Ehab and the Expected GCD Problem

## 题目描述

Let's define a function $ f(p) $ on a permutation $ p $ as follows. Let $ g_i $ be the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of elements $ p_1 $ , $ p_2 $ , ..., $ p_i $ (in other words, it is the GCD of the prefix of length $ i $ ). Then $ f(p) $ is the number of distinct elements among $ g_1 $ , $ g_2 $ , ..., $ g_n $ .

Let $ f_{max}(n) $ be the maximum value of $ f(p) $ among all permutations $ p $ of integers $ 1 $ , $ 2 $ , ..., $ n $ .

Given an integers $ n $ , count the number of permutations $ p $ of integers $ 1 $ , $ 2 $ , ..., $ n $ , such that $ f(p) $ is equal to $ f_{max}(n) $ . Since the answer may be large, print the remainder of its division by $ 1000\,000\,007 = 10^9 + 7 $ .

## 输入格式

The only line contains the integer $ n $ ( $ 2 \le n \le 10^6 $ ) — the length of the permutations.

## 输出格式

The only line should contain your answer modulo $ 10^9+7 $ .

## 说明/提示

Consider the second example: these are the permutations of length $ 3 $ :

- $ [1,2,3] $ , $ f(p)=1 $ .
- $ [1,3,2] $ , $ f(p)=1 $ .
- $ [2,1,3] $ , $ f(p)=2 $ .
- $ [2,3,1] $ , $ f(p)=2 $ .
- $ [3,1,2] $ , $ f(p)=2 $ .
- $ [3,2,1] $ , $ f(p)=2 $ .

The maximum value $ f_{max}(3) = 2 $ , and there are $ 4 $ permutations $ p $ such that $ f(p)=2 $ .

## 样例 #1

### 输入

```
2

```

### 输出

```
1
```

## 样例 #2

### 输入

```
3

```

### 输出

```
4
```

## 样例 #3

### 输入

```
6

```

### 输出

```
120
```

