---
title: "Malek Dance Club"
layout: "post"
diff: 普及/提高-
pid: CF319A
tag: []
---

# Malek Dance Club

## 题目描述

As a tradition, every year before IOI all the members of Natalia Fan Club are invited to Malek Dance Club to have a fun night together. Malek Dance Club has $ 2^{n} $ members and coincidentally Natalia Fan Club also has $ 2^{n} $ members. Each member of MDC is assigned a unique id $ i $ from $ 0 $ to $ 2^{n}-1 $ . The same holds for each member of NFC.

One of the parts of this tradition is one by one dance, where each member of MDC dances with a member of NFC. A dance pair is a pair of numbers $ (a,b) $ such that member $ a $ from MDC dances with member $ b $ from NFC.

The complexity of a pairs' assignment is the number of pairs of dancing pairs $ (a,b) $ and $ (c,d) $ such that $ a&lt;c $ and $ b&gt;d $ .

You are given a binary number of length $ n $ named $ x $ . We know that member $ i $ from MDC dances with member ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF319A/99db469180d6ab11deff381b4df066112345cbb1.png) from NFC. Your task is to calculate the complexity of this assignment modulo $ 1000000007 $ $ (10^{9}+7) $ .

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF319A/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) denotes applying «XOR» to numbers $ x $ and $ y $ . This operation exists in all modern programming languages, for example, in C++ and Java it denotes as «^», in Pascal — «xor».

## 输入格式

The first line of input contains a binary number $ x $ of lenght $ n $ , $ (1<=n<=100) $ .

This number may contain leading zeros.

## 输出格式

Print the complexity of the given dance assignent modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
11

```

### 输出

```
6

```

## 样例 #2

### 输入

```
01

```

### 输出

```
2

```

## 样例 #3

### 输入

```
1

```

### 输出

```
1

```

