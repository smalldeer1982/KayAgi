---
title: "Quadratic Set"
layout: "post"
diff: 省选/NOI-
pid: CF1622F
tag: ['图论', '哈希 hashing']
---

# Quadratic Set

## 题目描述

Let's call a set of positive integers $ a_1, a_2, \dots, a_k $ quadratic if the product of the factorials of its elements is a square of an integer, i. e. $ \prod\limits_{i=1}^{k} a_i! = m^2 $ , for some integer $ m $ .

You are given a positive integer $ n $ .

Your task is to find a quadratic subset of a set $ 1, 2, \dots, n $ of maximum size. If there are multiple answers, print any of them.

## 输入格式

A single line contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ).

## 输出格式

In the first line, print a single integer — the size of the maximum subset. In the second line, print the subset itself in an arbitrary order.

## 样例 #1

### 输入

```
1
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
4
```

### 输出

```
3
1 3 4
```

## 样例 #3

### 输入

```
7
```

### 输出

```
4
1 4 5 6
```

## 样例 #4

### 输入

```
9
```

### 输出

```
7
1 2 4 5 6 7 9
```

