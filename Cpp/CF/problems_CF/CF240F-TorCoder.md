---
title: "TorCoder"
layout: "post"
diff: 提高+/省选-
pid: CF240F
tag: []
---

# TorCoder

## 题目描述

A boy named Leo doesn't miss a single TorCoder contest round. On the last TorCoder round number 100666 Leo stumbled over the following problem. He was given a string $ s $ , consisting of $ n $ lowercase English letters, and $ m $ queries. Each query is characterised by a pair of integers $ l_{i},r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ .

We'll consider the letters in the string numbered from 1 to $ n $ from left to right, that is, $ s=s_{1}s_{2}...\ s_{n} $ .

After each query he must swap letters with indexes from $ l_{i} $ to $ r_{i} $ inclusive in string $ s $ so as to make substring $ (l_{i},r_{i}) $ a palindrome. If there are multiple such letter permutations, you should choose the one where string $ (l_{i},r_{i}) $ will be lexicographically minimum. If no such permutation exists, you should ignore the query (that is, not change string $ s $ ).

Everybody knows that on TorCoder rounds input line and array size limits never exceed $ 60 $ , so Leo solved this problem easily. Your task is to solve the problem on a little bit larger limits. Given string $ s $ and $ m $ queries, print the string that results after applying all $ m $ queries to string $ s $ .

## 输入格式

**从文件 `input.txt` 中读入数据。**

The first input line contains two integers $ n $ and $ m $ $ (1<=n,m<=10^{5}) $ — the string length and the number of the queries.

The second line contains string $ s $ , consisting of $ n $ lowercase Latin letters.

Each of the next $ m $ lines contains a pair of integers $ l_{i},r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) — a query to apply to the string.

## 输出格式

**输出到文件 `output.txt` 中。**

In a single line print the result of applying $ m $ queries to string $ s $ . Print the queries in the order in which they are given in the input.

## 说明/提示

A substring $ (l_{i},r_{i}) $ $ 1<=l_{i}<=r_{i}<=n) $ of string $ s=s_{1}s_{2}...\ s_{n} $ of length $ n $ is a sequence of characters $ s_{li}s_{li+1}...s_{ri} $ .

A string is a palindrome, if it reads the same from left to right and from right to left.

String $ x_{1}x_{2}...\ x_{p} $ is lexicographically smaller than string $ y_{1}y_{2}...\ y_{q} $ , if either $ p&lt;q $ and $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{p}=y_{p} $ , or exists such number $ r $ $ (r&lt;p,r&lt;q) $ , that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}&lt;y_{r+1} $ .

## 样例 #1

### 输入

```
7 2
aabcbaa
1 3
5 7

```

### 输出

```
abacaba

```

## 样例 #2

### 输入

```
3 2
abc
1 2
2 3

```

### 输出

```
abc

```

