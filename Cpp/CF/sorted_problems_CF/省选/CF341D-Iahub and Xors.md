---
title: "Iahub and Xors"
layout: "post"
diff: 省选/NOI-
pid: CF341D
tag: ['线段树', '树状数组', '树套树']
---

# Iahub and Xors

## 题目描述

Iahub does not like background stories, so he'll tell you exactly what this problem asks you for.

You are given a matrix $ a $ with $ n $ rows and $ n $ columns. Initially, all values of the matrix are zeros. Both rows and columns are 1-based, that is rows are numbered 1, 2, ..., $ n $ and columns are numbered 1, 2, ..., $ n $ . Let's denote an element on the $ i $ -th row and $ j $ -th column as $ a_{i,j} $ .

We will call a submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ such elements $ a_{i,j} $ for which two inequalities hold: $ x_{0}<=i<=x_{1} $ , $ y_{0}<=j<=y_{1} $ .

Write a program to perform two following operations:

1. Query( $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ ): print the xor sum of the elements of the submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ .
2. Update( $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ , $ v $ ): each element from submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ gets xor-ed by value $ v $ .

## 输入格式

The first line contains two integers: $ n $ ( $ 1<=n<=1000 $ ) and $ m $ ( $ 1<=m<=10^{5} $ ). The number $ m $ represents the number of operations you need to perform. Each of the next $ m $ lines contains five or six integers, depending on operation type.

If the $ i $ -th operation from the input is a query, the first number from $ i $ -th line will be 1. It will be followed by four integers $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ . If the $ i $ -th operation is an update, the first number from the $ i $ -th line will be 2. It will be followed by five integers $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ , $ v $ .

It is guaranteed that for each update operation, the following inequality holds: $ 0<=v<2^{62} $ . It is guaranteed that for each operation, the following inequalities hold: $ 1<=x_{0}<=x_{1}<=n $ , $ 1<=y_{0}<=y_{1}<=n $ .

## 输出格式

For each query operation, output on a new line the result.

## 说明/提示

After the first $ 3 $ operations, the matrix will look like this:

```
1 1 2
1 1 2
3 3 3
```
The fourth operation asks us to compute 1 xor 2 xor 3 xor 3 = 3.

The fifth operation asks us to compute 1 xor 3 = 2.

## 样例 #1

### 输入

```
3 5
2 1 1 2 2 1
2 1 3 2 3 2
2 3 1 3 3 3
1 2 2 3 3
1 2 2 3 2

```

### 输出

```
3
2

```

