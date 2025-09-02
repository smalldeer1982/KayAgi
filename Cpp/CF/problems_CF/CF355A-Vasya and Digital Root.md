---
title: "Vasya and Digital Root"
layout: "post"
diff: 普及-
pid: CF355A
tag: []
---

# Vasya and Digital Root

## 题目描述

Vasya has recently found out what a digital root of a number is and he decided to share his knowledge with you.

Let's assume that $ S(n) $ is the sum of digits of number $ n $ , for example, $ S(4098)=4+0+9+8=21 $ . Then the digital root of number $ n $ equals to:

1. $ dr(n)=S(n) $ , if $ S(n)&lt;10 $ ;
2. $ dr(n)=dr(S(n)) $ , if $ S(n)>=10 $ .

For example, $ dr(4098)=dr(21)=3 $ .

Vasya is afraid of large numbers, so the numbers he works with are at most $ 10^{1000} $ . For all such numbers, he has proved that $ dr(n)=S(S(S(S(n)))) $ $ (n<=10^{1000}) $ .

Now Vasya wants to quickly find numbers with the given digital root. The problem is, he hasn't learned how to do that and he asked you to help him. You task is, given numbers $ k $ and $ d $ , find the number consisting of exactly $ k $ digits (the leading zeroes are not allowed), with digital root equal to $ d $ , or else state that such number does not exist.

## 输入格式

The first line contains two integers $ k $ and $ d $ $ (1<=k<=1000; 0<=d<=9) $ .

## 输出格式

In a single line print either any number that meets the requirements (without the leading zeroes) or "No solution" (without the quotes), if the corresponding number does not exist.

The chosen number must consist of exactly $ k $ digits. We assume that number 0 doesn't contain any leading zeroes.

## 说明/提示

For the first test sample $ dr(5881)=dr(22)=4 $ .

For the second test sample $ dr(36172)=dr(19)=dr(10)=1 $ .

## 样例 #1

### 输入

```
4 4

```

### 输出

```
5881

```

## 样例 #2

### 输入

```
5 1

```

### 输出

```
36172

```

## 样例 #3

### 输入

```
1 0

```

### 输出

```
0

```

