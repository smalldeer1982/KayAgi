---
title: "No to Palindromes!"
layout: "post"
diff: 普及+/提高
pid: CF464A
tag: []
---

# No to Palindromes!

## 题目描述

Paul hates palindromes. He assumes that string $ s $ is tolerable if each its character is one of the first $ p $ letters of the English alphabet and $ s $ doesn't contain any palindrome contiguous substring of length 2 or more.

Paul has found a tolerable string $ s $ of length $ n $ . Help him find the lexicographically next tolerable string of the same length or else state that such string does not exist.

## 输入格式

The first line contains two space-separated integers: $ n $ and $ p $ ( $ 1<=n<=1000 $ ; $ 1<=p<=26 $ ). The second line contains string $ s $ , consisting of $ n $ small English letters. It is guaranteed that the string is tolerable (according to the above definition).

## 输出格式

If the lexicographically next tolerable string of the same length exists, print it. Otherwise, print "NO" (without the quotes).

## 说明/提示

String $ s $ is lexicographically larger (or simply larger) than string $ t $ with the same length, if there is number $ i $ , such that $ s_{1}=t_{1} $ , ..., $ s_{i}=t_{i} $ , $ s_{i+1}&gt;t_{i+1} $ .

The lexicographically next tolerable string is the lexicographically minimum tolerable string which is larger than the given one.

A palindrome is a string that reads the same forward or reversed.

## 样例 #1

### 输入

```
3 3
cba

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
3 4
cba

```

### 输出

```
cbd

```

## 样例 #3

### 输入

```
4 4
abcd

```

### 输出

```
abda

```

