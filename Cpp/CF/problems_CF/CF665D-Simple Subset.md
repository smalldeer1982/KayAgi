---
title: "Simple Subset"
layout: "post"
diff: 普及+/提高
pid: CF665D
tag: []
---

# Simple Subset

## 题目描述

A tuple of positive integers $ {x_{1},x_{2},...,x_{k}} $ is called simple if for all pairs of positive integers $ (i,j) $ ( $ 1<=i&lt;j<=k $ ), $ x_{i}+x_{j} $ is a prime.

You are given an array $ a $ with $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ (not necessary distinct). You want to find a simple subset of the array $ a $ with the maximum size.

A prime number (or a prime) is a natural number greater than $ 1 $ that has no positive divisors other than $ 1 $ and itself.

Let's define a subset of the array $ a $ as a tuple that can be obtained from $ a $ by removing some (possibly all) elements of it.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=1000 $ ) — the number of integers in the array $ a $ .

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=10^{6} $ ) — the elements of the array $ a $ .

## 输出格式

On the first line print integer $ m $ — the maximum possible size of simple subset of $ a $ .

On the second line print $ m $ integers $ b_{l} $ — the elements of the simple subset of the array $ a $ with the maximum size.

If there is more than one solution you can print any of them. You can print the elements of the subset in any order.

## 样例 #1

### 输入

```
2
2 3

```

### 输出

```
2
3 2

```

## 样例 #2

### 输入

```
2
2 2

```

### 输出

```
1
2

```

## 样例 #3

### 输入

```
3
2 1 1

```

### 输出

```
3
1 1 2

```

## 样例 #4

### 输入

```
2
83 14

```

### 输出

```
2
14 83

```

