---
title: "Different Subsets For All Tuples"
layout: "post"
diff: 省选/NOI-
pid: CF660E
tag: ['组合数学']
---

# Different Subsets For All Tuples

## 题目描述

For a sequence $ a $ of $ n $ integers between $ 1 $ and $ m $ , inclusive, denote $ f(a) $ as the number of distinct subsequences of $ a $ (including the empty subsequence).

You are given two positive integers $ n $ and $ m $ . Let $ S $ be the set of all sequences of length $ n $ consisting of numbers from $ 1 $ to $ m $ . Compute the sum $ f(a) $ over all $ a $ in $ S $ modulo $ 10^{9}+7 $ .

## 输入格式

The only line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=10^{6} $ ) — the number of elements in arrays and the upper bound for elements.

## 输出格式

Print the only integer $ c $ — the desired sum modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
1 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
2 2

```

### 输出

```
14

```

## 样例 #3

### 输入

```
3 3

```

### 输出

```
174

```

