---
title: "Ghd"
layout: "post"
diff: 省选/NOI-
pid: CF364D
tag: []
---

# Ghd

## 题目描述

John Doe offered his sister Jane Doe find the gcd of some set of numbers $ a $ .

Gcd is a positive integer $ g $ , such that all number from the set are evenly divisible by $ g $ and there isn't such $ g' $ $ (g'>g) $ , that all numbers of the set are evenly divisible by $ g' $ .

Unfortunately Jane couldn't cope with the task and John offered her to find the ghd of the same subset of numbers.

Ghd is a positive integer $ g $ , such that at least half of numbers from the set are evenly divisible by $ g $ and there isn't such $ g' $ $ (g'>g) $ that at least half of the numbers from the set are evenly divisible by $ g' $ .

Jane coped with the task for two hours. Please try it, too.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=10^{6} $ ) showing how many numbers are in set $ a $ . The second line contains space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{12}) $ . Please note, that given set can contain equal numbers.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the %I64d specifier.

## 输出格式

Print a single integer $ g $ — the Ghd of set $ a $ .

## 样例 #1

### 输入

```
6
6 2 3 4 5 6

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5
5 5 6 10 15

```

### 输出

```
5

```

