---
title: "AB-string"
layout: "post"
diff: 提高+/省选-
pid: CF1238D
tag: []
---

# AB-string

## 题目描述

The string $ t_1t_2 \dots t_k $ is good if each letter of this string belongs to at least one palindrome of length greater than 1.

A palindrome is a string that reads the same backward as forward. For example, the strings A, BAB, ABBA, BAABBBAAB are palindromes, but the strings AB, ABBBAA, BBBA are not.

Here are some examples of good strings:

- $ t $ = AABBB (letters $ t_1 $ , $ t_2 $ belong to palindrome $ t_1 \dots t_2 $ and letters $ t_3 $ , $ t_4 $ , $ t_5 $ belong to palindrome $ t_3 \dots t_5 $ );
- $ t $ = ABAA (letters $ t_1 $ , $ t_2 $ , $ t_3 $ belong to palindrome $ t_1 \dots t_3 $ and letter $ t_4 $ belongs to palindrome $ t_3 \dots t_4 $ );
- $ t $ = AAAAA (all letters belong to palindrome $ t_1 \dots t_5 $ );

You are given a string $ s $ of length $ n $ , consisting of only letters A and B.

You have to calculate the number of good substrings of string $ s $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — the length of the string $ s $ .

The second line contains the string $ s $ , consisting of letters A and B.

## 输出格式

Print one integer — the number of good substrings of string $ s $ .

## 说明/提示

In the first test case there are six good substrings: $ s_1 \dots s_2 $ , $ s_1 \dots s_4 $ , $ s_1 \dots s_5 $ , $ s_3 \dots s_4 $ , $ s_3 \dots s_5 $ and $ s_4 \dots s_5 $ .

In the second test case there are three good substrings: $ s_1 \dots s_2 $ , $ s_1 \dots s_3 $ and $ s_2 \dots s_3 $ .

## 样例 #1

### 输入

```
5
AABBB

```

### 输出

```
6

```

## 样例 #2

### 输入

```
3
AAA

```

### 输出

```
3

```

## 样例 #3

### 输入

```
7
AAABABB

```

### 输出

```
15

```

