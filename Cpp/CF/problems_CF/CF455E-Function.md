---
title: "Function"
layout: "post"
diff: 省选/NOI-
pid: CF455E
tag: []
---

# Function

## 题目描述

Serega and Fedor play with functions. One day they came across a very interesting function. It looks like that:

- $ f(1,j)=a[j] $ , $ 1<=j<=n $ .
- $ f(i,j)=min(f(i-1,j),f(i-1,j-1))+a[j] $ , $ 2<=i<=n $ ,  $ i<=j<=n $ .

Here $ a $ is an integer array of length $ n $ .

Serega and Fedya want to know what values this function takes at some points. But they don't want to calculate the values manually. So they ask you to help them.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the length of array $ a $ . The next line contains $ n $ integers: $ a[1],a[2],...,a[n] $ ( $ 0<=a[i]<=10^{4} $ ).

The next line contains integer $ m $ $ (1<=m<=10^{5}) $ — the number of queries. Each of the next $ m $ lines contains two integers: $ x_{i} $ , $ y_{i} $ ( $ 1<=x_{i}<=y_{i}<=n $ ). Each line means that Fedor and Serega want to know the value of $ f(x_{i},y_{i}) $ .

## 输出格式

Print $ m $ lines — the answers to the guys' queries.

## 样例 #1

### 输入

```
6
2 2 3 4 3 4
4
4 5
3 4
3 4
2 3

```

### 输出

```
12
9
9
5

```

## 样例 #2

### 输入

```
7
1 3 2 3 4 0 2
4
4 5
2 3
1 4
4 6

```

### 输出

```
11
4
3
0

```

