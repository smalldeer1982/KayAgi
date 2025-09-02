---
title: "MEX Queries"
layout: "post"
diff: 提高+/省选-
pid: CF817F
tag: ['线段树', '离散化']
---

# MEX Queries

## 题目描述

You are given a set of integer numbers, initially it is empty. You should perform $ n $ queries.

There are three different types of queries:

- 1 $ l $ $ r $ — Add all missing numbers from the interval $ [l,r] $
- 2 $ l $ $ r $ — Remove all present numbers from the interval $ [l,r] $
- 3 $ l $ $ r $ — Invert the interval $ [l,r] $ — add all missing and remove all present numbers from the interval $ [l,r] $

After each query you should output MEX of the set — the smallest positive (MEX $ >=1 $ ) integer number which is not presented in the set.

## 输入格式

The first line contains one integer number $ n $ ( $ 1<=n<=10^{5} $ ).

Next $ n $ lines contain three integer numbers $ t,l,r $ ( $ 1<=t<=3,1<=l<=r<=10^{18} $ ) — type of the query, left and right bounds.

## 输出格式

Print MEX of the set after each query.

## 说明/提示

Here are contents of the set after each query in the first example:

1. $ {3,4} $ — the interval $ [3,4] $ is added
2. $ {1,2,5,6} $ — numbers $ {3,4} $ from the interval $ [1,6] $ got deleted and all the others are added
3. $ {5,6} $ — numbers $ {1,2} $ got deleted

## 样例 #1

### 输入

```
3
1 3 4
3 1 6
2 1 3

```

### 输出

```
1
3
1

```

## 样例 #2

### 输入

```
4
1 1 3
3 5 6
2 4 4
3 1 6

```

### 输出

```
4
4
4
1

```

