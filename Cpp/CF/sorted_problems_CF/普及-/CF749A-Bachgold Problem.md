---
title: "Bachgold Problem"
layout: "post"
diff: 普及-
pid: CF749A
tag: []
---

# Bachgold Problem

## 题目描述

Bachgold problem is very easy to formulate. Given a positive integer $ n $ represent it as a sum of maximum possible number of prime numbers. One can prove that such representation exists for any integer greater than $ 1 $ .

Recall that integer $ k $ is called prime if it is greater than $ 1 $ and has exactly two positive integer divisors — $ 1 $ and $ k $ .

## 输入格式

The only line of the input contains a single integer $ n $ ( $ 2<=n<=100000 $ ).

## 输出格式

The first line of the output contains a single integer $ k $ — maximum possible number of primes in representation.

The second line should contain $ k $ primes with their sum equal to $ n $ . You can print them in any order. If there are several optimal solution, print any of them.

## 样例 #1

### 输入

```
5

```

### 输出

```
2
2 3

```

## 样例 #2

### 输入

```
6

```

### 输出

```
3
2 2 2

```

