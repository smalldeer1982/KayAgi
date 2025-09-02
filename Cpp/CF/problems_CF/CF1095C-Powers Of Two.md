---
title: "Powers Of Two"
layout: "post"
diff: 普及/提高-
pid: CF1095C
tag: []
---

# Powers Of Two

## 题目描述

A positive integer $ x $ is called a power of two if it can be represented as $ x = 2^y $ , where $ y $ is a non-negative integer. So, the powers of two are $ 1, 2, 4, 8, 16, \dots $ .

You are given two positive integers $ n $ and $ k $ . Your task is to represent $ n $ as the sum of exactly $ k $ powers of two.

## 输入格式

The only line of the input contains two integers $ n $ and $ k $ ( $ 1 \le n \le 10^9 $ , $ 1 \le k \le 2 \cdot 10^5 $ ).

## 输出格式

If it is impossible to represent $ n $ as the sum of $ k $ powers of two, print NO.

Otherwise, print YES, and then print $ k $ positive integers $ b_1, b_2, \dots, b_k $ such that each of $ b_i $ is a power of two, and $ \sum \limits_{i = 1}^{k} b_i = n $ . If there are multiple answers, you may print any of them.

## 样例 #1

### 输入

```
9 4

```

### 输出

```
YES
1 2 2 4 

```

## 样例 #2

### 输入

```
8 1

```

### 输出

```
YES
8 

```

## 样例 #3

### 输入

```
5 1

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
3 7

```

### 输出

```
NO

```

