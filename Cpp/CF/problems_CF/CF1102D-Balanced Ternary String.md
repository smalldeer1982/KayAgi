---
title: "Balanced Ternary String"
layout: "post"
diff: 普及/提高-
pid: CF1102D
tag: []
---

# Balanced Ternary String

## 题目描述

You are given a string $ s $ consisting of exactly $ n $ characters, and each character is either '0', '1' or '2'. Such strings are called ternary strings.

Your task is to replace minimum number of characters in this string with other characters to obtain a balanced ternary string (balanced ternary string is a ternary string such that the number of characters '0' in this string is equal to the number of characters '1', and the number of characters '1' (and '0' obviously) is equal to the number of characters '2').

Among all possible balanced ternary strings you have to obtain the lexicographically (alphabetically) smallest.

Note that you can neither remove characters from the string nor add characters to the string. Also note that you can replace the given characters only with characters '0', '1' and '2'.

It is guaranteed that the answer exists.

## 输入格式

The first line of the input contains one integer $ n $ ( $ 3 \le n \le 3 \cdot 10^5 $ , $ n $ is divisible by $ 3 $ ) — the number of characters in $ s $ .

The second line contains the string $ s $ consisting of exactly $ n $ characters '0', '1' and '2'.

## 输出格式

Print one string — the lexicographically (alphabetically) smallest balanced ternary string which can be obtained from the given one with minimum number of replacements.

Because $ n $ is divisible by $ 3 $  it is obvious that the answer exists. And it is obvious that there is only one possible answer.

## 样例 #1

### 输入

```
3
121

```

### 输出

```
021

```

## 样例 #2

### 输入

```
6
000000

```

### 输出

```
001122

```

## 样例 #3

### 输入

```
6
211200

```

### 输出

```
211200

```

## 样例 #4

### 输入

```
6
120110

```

### 输出

```
120120

```

