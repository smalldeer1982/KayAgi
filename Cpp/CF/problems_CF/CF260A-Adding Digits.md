---
title: "Adding Digits"
layout: "post"
diff: 普及/提高-
pid: CF260A
tag: []
---

# Adding Digits

## 题目描述

Vasya has got two number: $ a $ and $ b $ . However, Vasya finds number $ a $ too short. So he decided to repeat the operation of lengthening number $ a $ $ n $ times.

One operation of lengthening a number means adding exactly one digit to the number (in the decimal notation) to the right provided that the resulting number is divisible by Vasya's number $ b $ . If it is impossible to obtain the number which is divisible by $ b $ , then the lengthening operation cannot be performed.

Your task is to help Vasya and print the number he can get after applying the lengthening operation to number $ a\ n $ times.

## 输入格式

The first line contains three integers: $ a,b,n\ (1<=a,b,n<=10^{5}) $ .

## 输出格式

In a single line print the integer without leading zeros, which Vasya can get when he applies the lengthening operations to number $ a\ n $ times. If no such number exists, then print number -1. If there are multiple possible answers, print any of them.

## 样例 #1

### 输入

```
5 4 5

```

### 输出

```
524848

```

## 样例 #2

### 输入

```
12 11 1

```

### 输出

```
121

```

## 样例 #3

### 输入

```
260 150 10

```

### 输出

```
-1

```

