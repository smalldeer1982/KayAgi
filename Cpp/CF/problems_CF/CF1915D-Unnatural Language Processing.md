---
title: "Unnatural Language Processing"
layout: "post"
diff: 入门
pid: CF1915D
tag: ['模拟']
---

# Unnatural Language Processing

## 题目描述

Lura was bored and decided to make a simple language using the five letters $ \texttt{a} $ , $ \texttt{b} $ , $ \texttt{c} $ , $ \texttt{d} $ , $ \texttt{e} $ . There are two types of letters:

- vowels — the letters $ \texttt{a} $ and $ \texttt{e} $ . They are represented by $ \textsf{V} $ .
- consonants — the letters $ \texttt{b} $ , $ \texttt{c} $ , and $ \texttt{d} $ . They are represented by $ \textsf{C} $ .

 There are two types of syllables in the language: $ \textsf{CV} $ (consonant followed by vowel) or $ \textsf{CVC} $ (vowel with consonant before and after). For example, $ \texttt{ba} $ , $ \texttt{ced} $ , $ \texttt{bab} $ are syllables, but $ \texttt{aa} $ , $ \texttt{eda} $ , $ \texttt{baba} $ are not.A word in the language is a sequence of syllables. Lura has written a word in the language, but she doesn't know how to split it into syllables. Help her break the word into syllables.

For example, given the word $ \texttt{bacedbab} $ , it would be split into syllables as $ \texttt{ba.ced.bab} $ (the dot $ \texttt{.} $ represents a syllable boundary).

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the word.

The second line of each test case contains a string consisting of $ n $ lowercase Latin characters — the word.

All words given are valid words in the language; that is, they only use the letters $ \texttt{a} $ , $ \texttt{b} $ , $ \texttt{c} $ , $ \texttt{d} $ , $ \texttt{e} $ , and each word is made up of several syllables.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For test case, output a string denoting the word split into syllables by inserting a dot $ \texttt{.} $ between every pair of adjacent syllables.

If there are multiple possible splittings, output any of them. The input is given in such a way that at least one possible splitting exists.

## 样例 #1

### 输入

```
6
8
bacedbab
4
baba
13
daddecabeddad
3
dac
6
dacdac
22
dababbabababbabbababba
```

### 输出

```
ba.ced.bab
ba.ba
dad.de.ca.bed.dad
dac
dac.dac
da.bab.ba.ba.bab.bab.ba.bab.ba
```

