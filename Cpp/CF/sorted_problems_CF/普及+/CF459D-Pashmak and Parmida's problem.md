---
title: "Pashmak and Parmida's problem"
layout: "post"
diff: 普及+/提高
pid: CF459D
tag: []
---

# Pashmak and Parmida's problem

## 题目描述

Parmida is a clever girl and she wants to participate in Olympiads this year. Of course she wants her partner to be clever too (although he's not)! Parmida has prepared the following test problem for Pashmak.

There is a sequence $ a $ that consists of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Let's denote $ f(l,r,x) $ the number of indices $ k $ such that: $ l<=k<=r $ and $ a_{k}=x $ . His task is to calculate the number of pairs of indicies $ i,j $ $ (1<=i&lt;j<=n) $ such that $ f(1,i,a_{i})&gt;f(j,n,a_{j}) $ .

Help Pashmak with the test.

## 输入格式

The first line of the input contains an integer $ n $ $ (1<=n<=10^{6}) $ . The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ .

## 输出格式

Print a single integer — the answer to the problem.

## 样例 #1

### 输入

```
7
1 2 1 1 2 2 1

```

### 输出

```
8

```

## 样例 #2

### 输入

```
3
1 1 1

```

### 输出

```
1

```

## 样例 #3

### 输入

```
5
1 2 3 4 5

```

### 输出

```
0

```

