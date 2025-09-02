---
title: "FIBOSUM2 - Fibonacci extraction Sum"
layout: "post"
diff: 提高+/省选-
pid: SP19406
tag: []
---

# FIBOSUM2 - Fibonacci extraction Sum

## 题目描述

设 $fib[i]$ 为斐波那契数列第 $i$ 项。

给定三个整数 $c,k,n$，求

$$\sum ^{n} _ {i=1}{fib[k\times i+c]}$$

对 $10 ^ 9 + 7$ 取模的值。

## 输入格式

第一行一个非负整数 $T$，表示测试数据组数。

之后每行三个整数 $c,k,n$。

## 输出格式

输出 $T$ 行，每行一个非负整数表示这组数据的答案。

## 说明/提示

- $ 0 < T \le 60606 $
- $ 0 \le c < k \le 2^{15} $
- $ 0 < N \le 10^{18} $

## 样例 #1

### 输入

```
1
3 5 2
```

### 输出

```
254
```

