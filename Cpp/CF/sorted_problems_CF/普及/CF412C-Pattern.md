---
title: "Pattern"
layout: "post"
diff: 普及/提高-
pid: CF412C
tag: []
---

# Pattern

## 题目描述

Developers often face with regular expression patterns. A pattern is usually defined as a string consisting of characters and metacharacters that sets the rules for your search. These patterns are most often used to check whether a particular string meets the certain rules.

In this task, a pattern will be a string consisting of small English letters and question marks ('?'). The question mark in the pattern is a metacharacter that denotes an arbitrary small letter of the English alphabet. We will assume that a string matches the pattern if we can transform the string into the pattern by replacing the question marks by the appropriate characters. For example, string aba matches patterns: ???, ??a, a?a, aba.

Programmers that work for the R1 company love puzzling each other (and themselves) with riddles. One of them is as follows: you are given $ n $ patterns of the same length, you need to find a pattern that contains as few question marks as possible, and intersects with each of the given patterns. Two patterns intersect if there is a string that matches both the first and the second pattern. Can you solve this riddle?

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=10^{5}) $ — the number of patterns. Next $ n $ lines contain the patterns.

It is guaranteed that the patterns can only consist of small English letters and symbols '?'. All patterns are non-empty and have the same length. The total length of all the patterns does not exceed $ 10^{5} $ characters.

## 输出格式

In a single line print the answer to the problem — the pattern with the minimal number of signs '?', which intersects with each of the given ones. If there are several answers, print any of them.

## 说明/提示

Consider the first example. Pattern xab intersects with each of the given patterns. Pattern ??? also intersects with each of the given patterns, but it contains more question signs, hence it is not an optimal answer. Clearly, xab is the optimal answer, because it doesn't contain any question sign. There are a lot of other optimal answers, for example: aab, bab, cab, dab and so on.

## 样例 #1

### 输入

```
2
?ab
??b

```

### 输出

```
xab

```

## 样例 #2

### 输入

```
2
a
b

```

### 输出

```
?

```

## 样例 #3

### 输入

```
1
?a?b

```

### 输出

```
cacb

```

