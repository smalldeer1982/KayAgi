---
title: "On Sum of Number of Inversions in Permutations"
layout: "post"
diff: 省选/NOI-
pid: CF396D
tag: []
---

# On Sum of Number of Inversions in Permutations

## 题目描述

You are given a permutation $ p $ . Calculate the total number of inversions in all permutations that lexicographically do not exceed the given one.

As this number can be very large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=10^{6} $ ) — the length of the permutation. The second line contains $ n $ distinct integers $ p_{1},p_{2},...,p_{n} $ ( $ 1<=p_{i}<=n $ ).

## 输出格式

Print a single number — the answer to the problem modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

Permutation $ p $ of length $ n $ is the sequence that consists of $ n $ distinct integers, each of them is from $ 1 $ to $ n $ .

An inversion of permutation $ p_{1},p_{2},...,p_{n} $ is a pair of indexes $ (i,j) $ , such that $ i&lt;j $ and $ p_{i}&gt;p_{j} $ .

Permutation $ a $ do not exceed permutation $ b $ lexicographically, if either $ a=b $ or there exists such number $ i $ , for which the following logical condition fulfills: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF396D/c9f676c4e9d24faf34cdefe9d1d94cdf3a30d1e0.png) AND $ (a_{i}&lt;b_{i}) $ .

## 样例 #1

### 输入

```
2
2 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
2 1 3

```

### 输出

```
2

```

