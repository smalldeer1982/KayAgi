---
title: "Trivial Conjecture"
layout: "post"
diff: 难度0
pid: CF1812D
tag: []
---

# Trivial Conjecture

## 题目描述

$ $$$f(n) = \left\{ \begin{array}{ll} \frac{n}{2} & n \equiv 0 \pmod{2}\\ 3n+1 & n \equiv 1 \pmod{2}\\ \end{array} \right. $ $ </p><p>Find an integer  $ n $  so that none of the first  $ k $  terms of the sequence  $ n, f(n), f(f(n)), f(f(f(n))), \\dots $  are equal to  $ 1$$$.

## 输入格式

The only line contains an integer $ k $ ( $ 1 \leq k \leq \min(\textbf{[REDACTED]}, 10^{18}) $ ).

## 输出格式

Output a single integer $ n $ such that none of the first $ k $ terms of the sequence $ n, f(n), f(f(n)), f(f(f(n))), \dots $ are equal to $ 1 $ .

Integer $ n $ should have at most $ 10^3 $ digits.

## 说明/提示

In the first test, the sequence created with $ n = 5 $ looks like $ 5, 16, 8, 4, 2, 1, 4, \dots $ , and none of the first $ k=1 $ terms are equal to $ 1 $ .

In the second test, the sequence created with $ n = 6 $ looks like $ 6, 3, 10, 5, 16, 8, 4, \dots $ , and none of the first $ k=5 $ terms are equal to $ 1 $ .

## 样例 #1

### 输入

```
1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
```

### 输出

```
6
```

