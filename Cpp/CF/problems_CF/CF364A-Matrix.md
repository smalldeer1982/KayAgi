---
title: "Matrix"
layout: "post"
diff: 普及/提高-
pid: CF364A
tag: []
---

# Matrix

## 题目描述

You have a string of decimal digits $ s $ . Let's define $ b_{ij}=s_{i}·s_{j} $ . Find in matrix $ b $ the number of such rectangles that the sum $ b_{ij} $ for all cells $ (i,j) $ that are the elements of the rectangle equals $ a $ in each rectangle.

A rectangle in a matrix is a group of four integers $ (x,y,z,t) $  $ (x<=y,z<=t) $ . The elements of the rectangle are all cells $ (i,j) $ such that $ x<=i<=y,z<=j<=t $ .

## 输入格式

The first line contains integer $ a $ ( $ 0<=a<=10^{9} $ ), the second line contains a string of decimal integers $ s $ ( $ 1<=|s|<=4000 $ ).

## 输出格式

Print a single integer — the answer to a problem.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
10
12345

```

### 输出

```
6

```

## 样例 #2

### 输入

```
16
439873893693495623498263984765

```

### 输出

```
40

```

