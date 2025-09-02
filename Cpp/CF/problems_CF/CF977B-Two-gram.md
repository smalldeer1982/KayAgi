---
title: "Two-gram"
layout: "post"
diff: 普及-
pid: CF977B
tag: ['字符串', '枚举']
---

# Two-gram

## 题目描述

Two-gram is an ordered pair (i.e. string of length two) of capital Latin letters. For example, "AZ", "AA", "ZA" — three distinct two-grams.

You are given a string $ s $ consisting of $ n $ capital Latin letters. Your task is to find any two-gram contained in the given string as a substring (i.e. two consecutive characters of the string) maximal number of times. For example, for string $ s $ = "BBAABBBA" the answer is two-gram "BB", which contained in $ s $ three times. In other words, find any most frequent two-gram.

Note that occurrences of the two-gram can overlap with each other.

## 输入格式

The first line of the input contains integer number $ n $ ( $ 2 \le n \le 100 $ ) — the length of string $ s $ . The second line of the input contains the string $ s $ consisting of $ n $ capital Latin letters.

## 输出格式

Print the only line containing exactly two capital Latin letters — any two-gram contained in the given string $ s $ as a substring (i.e. two consecutive characters of the string) maximal number of times.

## 说明/提示

In the first example "BA" is also valid answer.

In the second example the only two-gram "ZZ" can be printed because it contained in the string "ZZZAA" two times.

## 样例 #1

### 输入

```
7
ABACABA

```

### 输出

```
AB

```

## 样例 #2

### 输入

```
5
ZZZAA

```

### 输出

```
ZZ

```

