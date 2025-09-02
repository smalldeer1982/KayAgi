---
title: "Three strings"
layout: "post"
diff: 省选/NOI-
pid: CF452E
tag: []
---

# Three strings

## 题目描述

You are given three strings $ (s_{1},s_{2},s_{3}) $ . For each integer $ l $ $ (1<=l<=min(|s_{1}|,|s_{2}|,|s_{3}|) $ you need to find how many triples ( $ i_{1},i_{2},i_{3} $ ) exist such that three strings $ s_{k}[i_{k}...\ i_{k}+l-1] $ $ (k=1,2,3) $ are pairwise equal. Print all found numbers modulo $ 1000000007 (10^{9}+7) $ .

See notes if you are not sure about some of the denotions used in the statement.

## 输入格式

First three lines contain three non-empty input strings. The sum of lengths of all strings is no more than $ 3·10^{5} $ . All strings consist only of lowercase English letters.

## 输出格式

You need to output $ min(|s_{1}|,|s_{2}|,|s_{3}|) $ numbers separated by spaces — answers for the problem modulo $ 1000000007 (10^{9}+7) $ .

## 说明/提示

Consider a string $ t=t_{1}t_{2}...\ t_{|t|} $ , where $ t_{i} $ denotes the $ i $ -th character of the string, and $ |t| $ denotes the length of the string.

Then $ t[i...\ j] $ $ (1<=i<=j<=|t|) $ represents the string $ t_{i}t_{i+1}...\ t_{j} $ (substring of $ t $ from position $ i $ to position $ j $ inclusive).

## 样例 #1

### 输入

```
abc
bc
cbc

```

### 输出

```
3 1 

```

## 样例 #2

### 输入

```
abacaba
abac
abcd

```

### 输出

```
11 2 0 0 

```

