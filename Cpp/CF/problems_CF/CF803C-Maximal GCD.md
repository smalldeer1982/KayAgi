---
title: "Maximal GCD"
layout: "post"
diff: 普及+/提高
pid: CF803C
tag: []
---

# Maximal GCD

## 题目描述

You are given positive integer number $ n $ . You should create such strictly increasing sequence of $ k $ positive numbers $ a_{1},a_{2},...,a_{k} $ , that their sum is equal to $ n $ and greatest common divisor is maximal.

Greatest common divisor of sequence is maximum of such numbers that every element of sequence is divisible by them.

If there is no possible sequence then output -1.

## 输入格式

The first line consists of two numbers $ n $ and $ k $ ( $ 1<=n,k<=10^{10} $ ).

## 输出格式

If the answer exists then output $ k $ numbers — resulting sequence. Otherwise output -1. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
6 3

```

### 输出

```
1 2 3

```

## 样例 #2

### 输入

```
8 2

```

### 输出

```
2 6

```

## 样例 #3

### 输入

```
5 3

```

### 输出

```
-1

```

