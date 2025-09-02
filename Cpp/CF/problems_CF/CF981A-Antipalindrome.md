---
title: "Antipalindrome"
layout: "post"
diff: 入门
pid: CF981A
tag: ['字符串', '枚举']
---

# Antipalindrome

## 题目描述

A string is a palindrome if it reads the same from the left to the right and from the right to the left. For example, the strings "kek", "abacaba", "r" and "papicipap" are palindromes, while the strings "abb" and "iq" are not.

A substring $ s[l \ldots r] $ ( $ 1 \leq l \leq r \leq |s| $ ) of a string $ s = s_{1}s_{2} \ldots s_{|s|} $ is the string $ s_{l}s_{l + 1} \ldots s_{r} $ .

Anna does not like palindromes, so she makes her friends call her Ann. She also changes all the words she reads in a similar way. Namely, each word $ s $ is changed into its longest substring that is not a palindrome. If all the substrings of $ s $ are palindromes, she skips the word at all.

Some time ago Ann read the word $ s $ . What is the word she changed it into?

## 输入格式

The first line contains a non-empty string $ s $ with length at most $ 50 $ characters, containing lowercase English letters only.

## 输出格式

If there is such a substring in $ s $ that is not a palindrome, print the maximum length of such a substring. Otherwise print $ 0 $ .

Note that there can be multiple longest substrings that are not palindromes, but their length is unique.

## 说明/提示

"mew" is not a palindrome, so the longest substring of it that is not a palindrome, is the string "mew" itself. Thus, the answer for the first example is $ 3 $ .

The string "uffuw" is one of the longest non-palindrome substrings (of length $ 5 $ ) of the string "wuffuw", so the answer for the second example is $ 5 $ .

All substrings of the string "qqqqqqqq" consist of equal characters so they are palindromes. This way, there are no non-palindrome substrings. Thus, the answer for the third example is $ 0 $ .

## 样例 #1

### 输入

```
mew

```

### 输出

```
3

```

## 样例 #2

### 输入

```
wuffuw

```

### 输出

```
5

```

## 样例 #3

### 输入

```
qqqqqqqq

```

### 输出

```
0

```

