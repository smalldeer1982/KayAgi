---
title: "Maxim and Matrix"
layout: "post"
diff: 普及+/提高
pid: CF261C
tag: []
---

# Maxim and Matrix

## 题目描述

Maxim loves to fill in a matrix in a special manner. Here is a pseudocode of filling in a matrix of size $ (m+1)×(m+1) $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF261C/2ee53d83c775f11a8b5c62a496d38d42095666d0.png)

Maxim asks you to count, how many numbers $ m $ $ (1<=m<=n) $ are there, such that the sum of values in the cells in the row number $ m+1 $ of the resulting matrix equals $ t $ .

Expression ( $ x $ $ xor $ $ y $ ) means applying the operation of bitwise excluding "OR" to numbers $ x $ and $ y $ . The given operation exists in all modern programming languages. For example, in languages C++ and Java it is represented by character "^", in Pascal — by "xor".

## 输入格式

A single line contains two integers $ n $ and $ t $ $ (1<=n,t<=10^{12},t<=n+1) $ .

Please, do not use the %lld specifier to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 输出格式

In a single line print a single integer — the answer to the problem.

## 样例 #1

### 输入

```
1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 2

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 3

```

### 输出

```
0

```

## 样例 #4

### 输入

```
1000000000000 1048576

```

### 输出

```
118606527258

```

