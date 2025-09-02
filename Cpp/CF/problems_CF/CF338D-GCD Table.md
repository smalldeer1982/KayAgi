---
title: "GCD Table"
layout: "post"
diff: 省选/NOI-
pid: CF338D
tag: []
---

# GCD Table

## 题目描述

Consider a table $ G $ of size $ n×m $ such that $ G(i,j)=GCD(i,j) $ for all $ 1<=i<=n,1<=j<=m $ . $ GCD(a,b) $ is the greatest common divisor of numbers $ a $ and $ b $ .

You have a sequence of positive integer numbers $ a_{1},a_{2},...,a_{k} $ . We say that this sequence occurs in table $ G $ if it coincides with consecutive elements in some row, starting from some position. More formally, such numbers $ 1<=i<=n $ and $ 1<=j<=m-k+1 $ should exist that $ G(i,j+l-1)=a_{l} $ for all $ 1<=l<=k $ .

Determine if the sequence $ a $ occurs in table $ G $ .

## 输入格式

The first line contains three space-separated integers $ n $ , $ m $ and $ k $ ( $ 1<=n,m<=10^{12} $ ; $ 1<=k<=10000 $ ). The second line contains $ k $ space-separated integers $ a_{1},a_{2},...,a_{k} $ ( $ 1<=a_{i}<=10^{12} $ ).

## 输出格式

Print a single word "YES", if the given sequence occurs in table $ G $ , otherwise print "NO".

## 说明/提示

Sample 1. The tenth row of table $ G $ starts from sequence {1, 2, 1, 2, 5, 2, 1, 2, 1, 10}. As you can see, elements from fifth to ninth coincide with sequence $ a $ .

Sample 2. This time the width of table $ G $ equals 8. Sequence $ a $ doesn't occur there.

## 样例 #1

### 输入

```
100 100 5
5 2 1 2 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
100 8 5
5 2 1 2 1

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
100 100 7
1 2 3 4 5 6 7

```

### 输出

```
NO

```

