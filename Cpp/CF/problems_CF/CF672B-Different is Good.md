---
title: "Different is Good"
layout: "post"
diff: 普及-
pid: CF672B
tag: []
---

# Different is Good

## 题目描述

A wise man told Kerem "Different is good" once, so Kerem wants all things in his life to be different.

Kerem recently got a string $ s $ consisting of lowercase English letters. Since Kerem likes it when things are different, he wants all substrings of his string $ s $ to be distinct. Substring is a string formed by some number of consecutive characters of the string. For example, string "aba" has substrings "" (empty substring), "a", "b", "a", "ab", "ba", "aba".

If string $ s $ has at least two equal substrings then Kerem will change characters at some positions to some other lowercase English letters. Changing characters is a very tiring job, so Kerem want to perform as few changes as possible.

Your task is to find the minimum number of changes needed to make all the substrings of the given string distinct, or determine that it is impossible.

## 输入格式

The first line of the input contains an integer $ n $ ( $ 1<=n<=100000 $ ) — the length of the string $ s $ .

The second line contains the string $ s $ of length $ n $ consisting of only lowercase English letters.

## 输出格式

If it's impossible to change the string $ s $ such that all its substring are distinct print -1. Otherwise print the minimum required number of changes.

## 说明/提示

In the first sample one of the possible solutions is to change the first character to 'b'.

In the second sample, one may change the first character to 'a' and second character to 'b', so the string becomes "abko".

## 样例 #1

### 输入

```
2
aa

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4
koko

```

### 输出

```
2

```

## 样例 #3

### 输入

```
5
murat

```

### 输出

```
0

```

