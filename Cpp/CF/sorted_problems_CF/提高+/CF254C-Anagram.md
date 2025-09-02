---
title: "Anagram"
layout: "post"
diff: 提高+/省选-
pid: CF254C
tag: ['字符串', '动态规划 DP']
---

# Anagram

## 题目描述

String $ x $ is an anagram of string $ y $ , if we can rearrange the letters in string $ x $ and get exact string $ y $ . For example, strings "DOG" and "GOD" are anagrams, so are strings "BABA" and "AABB", but strings "ABBAC" and "CAABA" are not.

You are given two strings $ s $ and $ t $ of the same length, consisting of uppercase English letters. You need to get the anagram of string $ t $ from string $ s $ . You are permitted to perform the replacing operation: every operation is replacing some character from the string $ s $ by any other character. Get the anagram of string $ t $ in the least number of replacing operations. If you can get multiple anagrams of string $ t $ in the least number of operations, get the lexicographically minimal one.

The lexicographic order of strings is the familiar to us "dictionary" order. Formally, the string $ p $ of length $ n $ is lexicographically smaller than string $ q $ of the same length, if $ p_{1}=q_{1} $ , $ p_{2}=q_{2} $ , ..., $ p_{k-1}=q_{k-1} $ , $ p_{k}&lt;q_{k} $ for some $ k $ ( $ 1<=k<=n $ ). Here characters in the strings are numbered from 1. The characters of the strings are compared in the alphabetic order.

## 输入格式

The input consists of two lines. The first line contains string $ s $ , the second line contains string $ t $ . The strings have the same length (from $ 1 $ to $ 10^{5} $ characters) and consist of uppercase English letters.

## 输出格式

In the first line print $ z $ — the minimum number of replacement operations, needed to get an anagram of string $ t $ from string $ s $ . In the second line print the lexicographically minimum anagram that could be obtained in $ z $ operations.

## 说明/提示

The second sample has eight anagrams of string $ t $ , that can be obtained from string $ s $ by replacing exactly two letters: "ADBADC", "ADDABC", "CDAABD", "CDBAAD", "CDBADA", "CDDABA", "DDAABC", "DDBAAC". These anagrams are listed in the lexicographical order. The lexicographically minimum anagram is "ADBADC".

## 样例 #1

### 输入

```
ABA
CBA

```

### 输出

```
1
ABC

```

## 样例 #2

### 输入

```
CDBABC
ADCABD

```

### 输出

```
2
ADBADC

```

