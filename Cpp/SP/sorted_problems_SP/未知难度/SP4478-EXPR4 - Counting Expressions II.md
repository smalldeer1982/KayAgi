---
title: "EXPR4 - Counting Expressions II"
layout: "post"
diff: 难度0
pid: SP4478
tag: []
---

# EXPR4 - Counting Expressions II

## 题目描述

Count the number of distinct expressions involving _n_ different operands **a**, **b**, **c**, etc. Only operators +, -, \*, / and parentheses are permitted. Single minus operator (for ex. -a\*b) is not allowed.

Two expression are distinct if for some valid input values (i.e. You won't divide some number by zero) **a**, **b**, **c**, ... , the two expressions leads to different results. For example, a/b/c and a/(b\*c) are the same expressions, but a/b+c and a/(b+c) are not.

## 输入格式

Multiply test cases. For each test case:

A single line - _n_.(1<= _n_ <=2000).

Input terminates by a single zero.

## 输出格式

For each test case:

The number of different expressions, modulo 1000000007.

## 样例 #1

### 输入

```
3
0
```

### 输出

```
68
```

