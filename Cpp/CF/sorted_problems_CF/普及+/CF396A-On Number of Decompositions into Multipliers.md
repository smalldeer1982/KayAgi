---
title: "On Number of Decompositions into Multipliers"
layout: "post"
diff: 普及+/提高
pid: CF396A
tag: []
---

# On Number of Decompositions into Multipliers

## 题目描述

You are given an integer $ m $ as a product of integers $ a_{1},a_{2},...\ a_{n} $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF396A/511aaee908ff3da31c1047aebc73037f3c2d6e3f.png). Your task is to find the number of distinct decompositions of number $ m $ into the product of $ n $ ordered positive integers.

Decomposition into $ n $ products, given in the input, must also be considered in the answer. As the answer can be very large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains positive integer $ n $ ( $ 1<=n<=500 $ ). The second line contains space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

In a single line print a single number $ k $ — the number of distinct decompositions of number $ m $ into $ n $ ordered multipliers modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the second sample, the get a decomposition of number 2, you need any one number out of three to equal 2, and the rest to equal 1.

In the third sample, the possible ways of decomposing into ordered multipliers are \[7,5\], \[5,7\], \[1,35\], \[35,1\].

A decomposition of positive integer $ m $ into $ n $ ordered multipliers is a cortege of positive integers $ b={b_{1},b_{2},...\ b_{n}} $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF396A/b461305f46e6043012038c3479cb445ca537b144.png). Two decompositions $ b $ and $ c $ are considered different, if there exists index $ i $ such that $ b_{i}≠c_{i} $ .

## 样例 #1

### 输入

```
1
15

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
1 1 2

```

### 输出

```
3

```

## 样例 #3

### 输入

```
2
5 7

```

### 输出

```
4

```

