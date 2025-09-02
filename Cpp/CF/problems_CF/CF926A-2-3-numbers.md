---
title: "2-3-numbers"
layout: "post"
diff: 普及/提高-
pid: CF926A
tag: []
---

# 2-3-numbers

## 题目描述

A positive integer is called a 2-3-integer, if it is equal to $ 2^{x}·3^{y} $ for some non-negative integers $ x $ and $ y $ . In other words, these integers are such integers that only have $ 2 $ and $ 3 $ among their prime divisors. For example, integers $ 1 $ , $ 6 $ , $ 9 $ , $ 16 $ and $ 108 $ — are 2-3 integers, while $ 5 $ , $ 10 $ , $ 21 $ and $ 120 $ are not.

Print the number of 2-3-integers on the given segment $ [l,r] $ , i. e. the number of sich 2-3-integers $ t $ that $ l<=t<=r $ .

## 输入格式

The only line contains two integers $ l $ and $ r $ ( $ 1<=l<=r<=2·10^{9} $ ).

## 输出格式

Print a single integer the number of 2-3-integers on the segment $ [l,r] $ .

## 说明/提示

In the first example the 2-3-integers are $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 6 $ , $ 8 $ and $ 9 $ .

In the second example the 2-3-integers are $ 108 $ , $ 128 $ , $ 144 $ , $ 162 $ and $ 192 $ .

## 样例 #1

### 输入

```
1 10

```

### 输出

```
7

```

## 样例 #2

### 输入

```
100 200

```

### 输出

```
5

```

## 样例 #3

### 输入

```
1 2000000000

```

### 输出

```
326

```

