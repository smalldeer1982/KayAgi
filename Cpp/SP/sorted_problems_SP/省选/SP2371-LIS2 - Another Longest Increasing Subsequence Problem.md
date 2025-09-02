---
title: "LIS2 - Another Longest Increasing Subsequence Problem"
layout: "post"
diff: 省选/NOI-
pid: SP2371
tag: []
---

# LIS2 - Another Longest Increasing Subsequence Problem

## 题目描述

Given a sequence of **N** pairs of integers, find the length of the **longest increasing subsequence** of it.

An **increasing sequence** _A $ _{1} $ ..A $ _{n} $_  is a sequence such that for every  _i < j_, _A $ _{i} $ < A $ _{j} $_ .

A **subsequence** of a sequence is a sequence that appears in the same relative order, but not necessarily contiguous.

A pair of integers  _(x $ _{1} $ , y $ _{1} $ )_ is less than  _(x $ _{2} $ , y $ _{2} $ )_ **iff** _x $ _{1} $ < x $ _{2} $_  and  _y $ _{1} $ < y $ _{2} $_ .

## 输入格式

The first line of input contains an integer  **N** (2 ≤  **N** ≤ 100000).

The following  **N** lines consist of  **N** pairs of integers _(x $ _{i} $ , y $ _{i} $ )_ (-10 $ ^{9} $ ≤ _x $ _{i} $ , y $ _{i} $_  ≤ 10 $ ^{9} $ ).

## 输出格式

The output contains an integer: the length of the longest increasing subsequence of the given sequence.

## 样例 #1

### 输入

```
8
1 3
3 2
1 1
4 5
6 3
9 9
8 7
7 6
```

### 输出

```
3
```

