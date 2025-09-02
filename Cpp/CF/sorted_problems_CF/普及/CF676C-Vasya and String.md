---
title: "Vasya and String"
layout: "post"
diff: 普及/提高-
pid: CF676C
tag: []
---

# Vasya and String

## 题目描述

High school student Vasya got a string of length $ n $ as a birthday present. This string consists of letters 'a' and 'b' only. Vasya denotes beauty of the string as the maximum length of a substring (consecutive subsequence) consisting of equal letters.

Vasya can change no more than $ k $ characters of the original string. What is the maximum beauty of the string he can achieve?

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1<=n<=100000,0<=k<=n $ ) — the length of the string and the maximum number of characters to change.

The second line contains the string, consisting of letters 'a' and 'b' only.

## 输出格式

Print the only integer — the maximum beauty of the string Vasya can achieve by changing no more than $ k $ characters.

## 说明/提示

In the first sample, Vasya can obtain both strings "aaaa" and "bbbb".

In the second sample, the optimal answer is obtained with the string "aaaaabaa" or with the string "aabaaaaa".

## 样例 #1

### 输入

```
4 2
abba

```

### 输出

```
4

```

## 样例 #2

### 输入

```
8 1
aabaabaa

```

### 输出

```
5

```

