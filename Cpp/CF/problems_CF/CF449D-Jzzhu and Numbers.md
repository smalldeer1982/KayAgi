---
title: "Jzzhu and Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF449D
tag: ['枚举', '状态合并', '容斥原理']
---

# Jzzhu and Numbers

## 题目描述

Jzzhu have $ n $ non-negative integers $ a_{1},a_{2},...,a_{n} $ . We will call a sequence of indexes $ i_{1},i_{2},...,i_{k} $ $ (1<=i_{1}<i_{2}<...<i_{k}<=n) $ a group of size $ k $ .

Jzzhu wonders, how many groups exists such that $ a_{i1} $ & $ a_{i2} $ & ... & $ a_{ik}=0 $ $ (1<=k<=n) $ ? Help him and print this number modulo $ 1000000007 $ $ (10^{9}+7) $ . Operation $ x $ & $ y $ denotes bitwise AND operation of two numbers.

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=10^{6}) $ . The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (0<=a_{i}<=10^{6}) $ .

## 输出格式

Output a single integer representing the number of required groups modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
3
2 3 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
4
0 1 2 3

```

### 输出

```
10

```

## 样例 #3

### 输入

```
6
5 2 0 5 2 1

```

### 输出

```
53

```

