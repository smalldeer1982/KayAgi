---
title: "LPERMUT - Longest Permutation"
layout: "post"
diff: 省选/NOI-
pid: SP744
tag: ['莫队', '枚举', '可持久化线段树']
---

# LPERMUT - Longest Permutation

## 题目描述

You are given a sequence A of n integer numbers (1<=A $ _{i} $ <=n). A subsequence of A has the form A $ _{u} $ , A $ _{u+1} $ ... , A $ _{v} $ (1<=u<=v<=n). We are interested in subsequences that are permutations of 1, 2, .., k (k is the length of the subsequence).

 Your task is to find the longest subsequence of this type.

## 输入格式

- Line 1: n (1<=n<=100000)
- Line 2: n numbers A $ _{1} $ , A $ _{2} $ , ... ,A $ _{n} $ (1<=A $ _{i} $ <=n)

## 输出格式

A single integer that is the length of the longest permutation

## 样例 #1

### 输入

```
5
4 1 3 1 2
```

### 输出

```
3
```

