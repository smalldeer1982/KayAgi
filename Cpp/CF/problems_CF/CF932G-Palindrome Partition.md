---
title: "Palindrome Partition"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF932G
tag: []
---

# Palindrome Partition

## 题目描述

Given a string $ s $ , find the number of ways to split $ s $ to substrings such that if there are $ k $ substrings $ (p_{1},p_{2},p_{3},...,p_{k}) $ in partition, then $ p_{i}=p_{k-i+1} $ for all $ i $ $ (1<=i<=k) $ and $ k $ is even.

Since the number of ways can be large, print it modulo $ 10^{9}+7 $ .

## 输入格式

The only line of input contains a string $ s $ $ (2<=|s|<=10^{6}) $ of even length consisting of lowercase Latin letters.

## 输出格式

Print one integer, the number of ways of partitioning the string modulo $ 10^{9}+7 $ .

## 说明/提示

In the first case, the only way to partition the string is $ ab|cd|cd|ab $ .

In the second case, the string can be partitioned as $ ab|b|ab|ab|ab|ab|b|ab $ or $ ab|b|abab|abab|b|ab $ or $ abbab|ab|ab|abbab $ .

## 样例 #1

### 输入

```
abcdcdab

```

### 输出

```
1
```

## 样例 #2

### 输入

```
abbababababbab

```

### 输出

```
3
```

