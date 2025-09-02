---
title: "Varying Kibibits"
layout: "post"
diff: 省选/NOI-
pid: CF772D
tag: []
---

# Varying Kibibits

## 题目描述

You are given $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Denote this list of integers as $ T $ .

Let $ f(L) $ be a function that takes in a non-empty list of integers $ L $ .

The function will output another integer as follows:

- First, all integers in $ L $ are padded with leading zeros so they are all the same length as the maximum length number in $ L $ .
- We will construct a string where the $ i $ -th character is the minimum of the $ i $ -th character in padded input numbers.
- The output is the number representing the string interpreted in base 10.

For example $ f(10,9)=0 $ , $ f(123,321)=121 $ , $ f(530,932,81)=30 $ .

Define the function

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/d730bfc2d6a92400175f0319f4f66324ea578631.png) Here, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/cbe1963e07d9486bdfb07e1dbd14017f5caa5e0f.png) denotes a subsequence.In other words, $ G(x) $ is the sum of squares of sum of elements of nonempty subsequences of $ T $ that evaluate to $ x $ when plugged into $ f $ modulo $ 1000000007 $ , then multiplied by $ x $ . The last multiplication is not modded.

You would like to compute $ G(0),G(1),...,G(999999) $ . To reduce the output size, print the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/8f5e81fbdf6da04693b872f68826db1077fb8afc.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/4298d47c0191af3c0a3103f431751061bc7e2362.png) denotes the bitwise XOR operator.

## 输入格式

The first line contains the integer $ n $ ( $ 1<=n<=1000000 $ ) — the size of list $ T $ .

The next line contains $ n $ space-separated integers, $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=999999 $ ) — the elements of the list.

## 输出格式

Output a single integer, the answer to the problem.

## 说明/提示

For the first sample, the nonzero values of $ G $ are $ G(121)=144611577 $ , $ G(123)=58401999 $ , $ G(321)=279403857 $ , $ G(555)=170953875 $ . The bitwise XOR of these numbers is equal to $ 292711924 $ .

For example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/80f1729ba4a2b96fab1f9859f95517b43796aaad.png), since the subsequences $ [123] $ and $ [123,555] $ evaluate to $ 123 $ when plugged into $ f $ .

For the second sample, we have ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/9bd3e43505031904f9ba81eca399add9357f139b.png)

For the last sample, we have ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/7321daac88d9c4bf2177a9da2946fe31cfad61d4.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/19620adc13a0563d84e1e536cfd1730ef5b2a55f.png) is the binomial coefficient.

## 样例 #1

### 输入

```
3
123 321 555

```

### 输出

```
292711924

```

## 样例 #2

### 输入

```
1
999999

```

### 输出

```
997992010006992

```

## 样例 #3

### 输入

```
10
1 1 1 1 1 1 1 1 1 1

```

### 输出

```
28160

```

