---
title: "Palindrome pairs"
layout: "post"
diff: 普及+/提高
pid: CF159D
tag: []
---

# Palindrome pairs

## 题目描述

You are given a non-empty string $ s $ consisting of lowercase letters. Find the number of pairs of non-overlapping palindromic substrings of this string.

In a more formal way, you have to find the quantity of tuples $ (a,b,x,y) $ such that $ 1<=a<=b&lt;x<=y<=|s| $ and substrings $ s[a...\ b] $ , $ s[x...\ y] $ are palindromes.

A palindrome is a string that can be read the same way from left to right and from right to left. For example, "abacaba", "z", "abba" are palindromes.

A substring $ s[i...\ j] $ ( $ 1<=i<=j<=|s| $ ) of string $ s $ = $ s_{1}s_{2}...\ s_{|s|} $ is a string $ s_{i}s_{i+1}...\ s_{j} $ . For example, substring $ s[2...4] $ of string $ s $ = "abacaba" equals "bac".

## 输入格式

The first line of input contains a non-empty string $ s $ which consists of lowercase letters ('a'...'z'), $ s $ contains at most $ 2000 $ characters.

## 输出格式

Output a single number — the quantity of pairs of non-overlapping palindromic substrings of $ s $ .

Please do not use the %lld format specifier to read or write 64-bit integers in С++. It is preferred to use cin, cout streams or the %I64d format specifier.

## 样例 #1

### 输入

```
aa

```

### 输出

```
1

```

## 样例 #2

### 输入

```
aaa

```

### 输出

```
5

```

## 样例 #3

### 输入

```
abacaba

```

### 输出

```
36

```

