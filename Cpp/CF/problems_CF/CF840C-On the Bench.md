---
title: "On the Bench"
layout: "post"
diff: 省选/NOI-
pid: CF840C
tag: ['动态规划 DP', '枚举']
---

# On the Bench

## 题目描述

A year ago on the bench in public park Leha found an array of $ n $ numbers. Leha believes that permutation $ p $ is right if for all $ 1<=i&lt;n $ condition, that $ a_{pi}·a_{pi+1} $ is not perfect square, holds. Leha wants to find number of right permutations modulo $ 10^{9}+7 $ .

## 输入格式

First line of input data contains single integer $ n $ ( $ 1<=n<=300 $ ) — length of the array.

Next line contains $ n $ integers $ a_{1},a_{2},...\ ,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — found array.

## 输出格式

Output single integer — number of right permutations modulo $ 10^{9}+7 $ .

## 说明/提示

For first example:

 $ [1,2,4] $ — right permutation, because $ 2 $ and $ 8 $ are not perfect squares.

 $ [1,4,2] $ — wrong permutation, because $ 4 $ is square of $ 2 $ .

 $ [2,1,4] $ — wrong permutation, because $ 4 $ is square of $ 2 $ .

 $ [2,4,1] $ — wrong permutation, because $ 4 $ is square of $ 2 $ .

 $ [4,1,2] $ — wrong permutation, because $ 4 $ is square of $ 2 $ .

 $ [4,2,1] $ — right permutation, because $ 8 $ and $ 2 $ are not perfect squares.

## 样例 #1

### 输入

```
3
1 2 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7
5 2 4 2 4 1 1

```

### 输出

```
144

```

