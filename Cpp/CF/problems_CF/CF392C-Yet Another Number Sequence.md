---
title: "Yet Another Number Sequence"
layout: "post"
diff: 省选/NOI-
pid: CF392C
tag: []
---

# Yet Another Number Sequence

## 题目描述

Everyone knows what the Fibonacci sequence is. This sequence can be defined by the recurrence relation:

 $ F_{1}=1,F_{2}=2,F_{i}=F_{i-1}+F_{i-2} (i&gt;2). $ We'll define a new number sequence $ A_{i}(k) $ by the formula:

 $ A_{i}(k)=F_{i}×i^{k} (i>=1). $ In this problem, your task is to calculate the following sum: $ A_{1}(k)+A_{2}(k)+...+A_{n}(k) $ . The answer can be very large, so print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains two space-separated integers $ n $ , $ k $ $ (1<=n<=10^{17}; 1<=k<=40) $ .

## 输出格式

Print a single integer — the sum of the first $ n $ elements of the sequence $ A_{i}(k) $ modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4 1

```

### 输出

```
34

```

## 样例 #3

### 输入

```
5 2

```

### 输出

```
316

```

## 样例 #4

### 输入

```
7 4

```

### 输出

```
73825

```

