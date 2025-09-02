---
title: "Duff and Weight Lifting"
layout: "post"
diff: 普及/提高-
pid: CF587A
tag: []
---

# Duff and Weight Lifting

## 题目描述

Recently, Duff has been practicing weight lifting. As a hard practice, Malek gave her a task. He gave her a sequence of weights. Weight of $ i $ -th of them is $ 2^{w_{i}} $ pounds. In each step, Duff can lift some of the remaining weights and throw them away. She does this until there's no more weight left. Malek asked her to minimize the number of steps.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF587A/ae0bf97f46f744ec67cd3653eed80d2fdb7f3472.png)Duff is a competitive programming fan. That's why in each step, she can only lift and throw away a sequence of weights $ 2^{a_{1}},...,2^{a_{k}} $ if and only if there exists a non-negative integer $ x $ such that $ 2^{a_{1}}+2^{a_{2}}+...+2^{a_{k}}=2^{x} $ , i. e. the sum of those numbers is a power of two.

Duff is a competitive programming fan, but not a programmer. That's why she asked for your help. Help her minimize the number of steps.

## 输入格式

The first line of input contains integer $ n $ ( $ 1<=n<=10^{6} $ ), the number of weights.

The second line contains $ n $ integers $ w_{1},...,w_{n} $ separated by spaces ( $ 0<=w_{i}<=10^{6} $ for each $ 1<=i<=n $ ), the powers of two forming the weights values.

## 输出格式

Print the minimum number of steps in a single line.

## 说明/提示

In the first sample case: One optimal way would be to throw away the first three in the first step and the rest in the second step. Also, it's not possible to do it in one step because their sum is not a power of two.

In the second sample case: The only optimal way is to throw away one weight in each step. It's not possible to do it in less than 4 steps because there's no subset of weights with more than one weight and sum equal to a power of two.

## 样例 #1

### 输入

```
5
1 1 2 3 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4
0 1 2 3

```

### 输出

```
4

```

