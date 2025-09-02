---
title: "Nearest Fraction"
layout: "post"
diff: 普及+/提高
pid: CF281B
tag: []
---

# Nearest Fraction

## 题目描述

You are given three positive integers $ x,y,n $ . Your task is to find the nearest fraction to fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF281B/4ac5ad94fb5392cd96ac09e5b84eb06e8c8a0edb.png) whose denominator is no more than $ n $ .

Formally, you should find such pair of integers $ a,b $ $ (1<=b<=n; 0<=a) $ that the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF281B/c829c21e70460346cb0c98e0e40815418eed87ca.png) is as minimal as possible.

If there are multiple "nearest" fractions, choose the one with the minimum denominator. If there are multiple "nearest" fractions with the minimum denominator, choose the one with the minimum numerator.

## 输入格式

A single line contains three integers $ x,y,n $ $ (1<=x,y,n<=10^{5}) $ .

## 输出格式

Print the required fraction in the format " $ a $ / $ b $ " (without quotes).

## 样例 #1

### 输入

```
3 7 6

```

### 输出

```
2/5

```

## 样例 #2

### 输入

```
7 2 4

```

### 输出

```
7/2

```

