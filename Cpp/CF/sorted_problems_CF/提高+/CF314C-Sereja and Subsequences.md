---
title: "Sereja and Subsequences"
layout: "post"
diff: 提高+/省选-
pid: CF314C
tag: []
---

# Sereja and Subsequences

## 题目描述

Sereja has a sequence that consists of $ n $ positive integers, $ a_{1},a_{2},...,a_{n} $ .

First Sereja took a piece of squared paper and wrote all distinct non-empty non-decreasing subsequences of sequence $ a $ . Then for each sequence written on the squared paper, Sereja wrote on a piece of lines paper all sequences that do not exceed it.

A sequence of positive integers $ x=x_{1},x_{2},...,x_{r} $ doesn't exceed a sequence of positive integers $ y=y_{1},y_{2},...,y_{r} $ , if the following inequation holds: $ x_{1}<=y_{1},x_{2}<=y_{2},...,x_{r}<=y_{r} $ .

Now Sereja wonders, how many sequences are written on the lines piece of paper. Help Sereja, find the required quantity modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{5}) $ . The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{6}) $ .

## 输出格式

In the single line print the answer to the problem modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
1
42

```

### 输出

```
42

```

## 样例 #2

### 输入

```
3
1 2 2

```

### 输出

```
13

```

## 样例 #3

### 输入

```
5
1 2 3 4 5

```

### 输出

```
719

```

