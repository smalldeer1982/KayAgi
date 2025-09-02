---
title: "Powerful array"
layout: "post"
diff: 提高+/省选-
pid: CF86D
tag: ['莫队', '枚举']
---

# Powerful array

## 题目描述

An array of positive integers $ a_{1},a_{2},...,a_{n} $ is given. Let us consider its arbitrary subarray $ a_{l},a_{l+1}...,a_{r} $ , where $ 1<=l<=r<=n $ . For every positive integer $ s $ denote by $ K_{s} $ the number of occurrences of $ s $ into the subarray. We call the power of the subarray the sum of products $ K_{s}·K_{s}·s $ for every positive integer $ s $ . The sum contains only finite number of nonzero summands as the number of different values in the array is indeed finite.

You should calculate the power of $ t $ given subarrays.

## 输入格式

First line contains two integers $ n $ and $ t $ ( $ 1<=n,t<=200000 $ ) — the array length and the number of queries correspondingly.

Second line contains $ n $ positive integers $ a_{i} $ ( $ 1<=a_{i}<=10^{6} $ ) — the elements of the array.

Next $ t $ lines contain two positive integers $ l $ , $ r $ ( $ 1<=l<=r<=n $ ) each — the indices of the left and the right ends of the corresponding subarray.

## 输出格式

Output $ t $ lines, the $ i $ -th line of the output should contain single positive integer — the power of the $ i $ -th query subarray.

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preferred to use cout stream (also you may use %I64d).

## 说明/提示

Consider the following array (see the second sample) and its \[2, 7\] subarray (elements of the subarray are colored):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF86D/5e3c36b108711f9f95c3c3519472e9f583328f8b.png) Then $ K_{1}=3 $ , $ K_{2}=2 $ , $ K_{3}=1 $ , so the power is equal to $ 3^{2}·1+2^{2}·2+1^{2}·3=20 $ .

## 样例 #1

### 输入

```
3 2
1 2 1
1 2
1 3

```

### 输出

```
3
6

```

## 样例 #2

### 输入

```
8 3
1 1 2 2 1 3 1 1
2 7
1 6
2 7

```

### 输出

```
20
20
20

```

