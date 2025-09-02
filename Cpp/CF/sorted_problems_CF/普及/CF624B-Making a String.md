---
title: "Making a String"
layout: "post"
diff: 普及/提高-
pid: CF624B
tag: []
---

# Making a String

## 题目描述

You are given an alphabet consisting of $ n $ letters, your task is to make a string of the maximum possible length so that the following conditions are satisfied:

- the $ i $ -th letter occurs in the string no more than $ a_{i} $ times;
- the number of occurrences of each letter in the string must be distinct for all the letters that occurred in the string at least once.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=26 $ ) — the number of letters in the alphabet.

The next line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ) — $ i $ -th of these integers gives the limitation on the number of occurrences of the $ i $ -th character in the string.

## 输出格式

Print a single integer — the maximum length of the string that meets all the requirements.

## 说明/提示

For convenience let's consider an alphabet consisting of three letters: "a", "b", "c". In the first sample, some of the optimal strings are: "cccaabbccbb", "aabcbcbcbcb". In the second sample some of the optimal strings are: "acc", "cbc".

## 样例 #1

### 输入

```
3
2 5 5

```

### 输出

```
11

```

## 样例 #2

### 输入

```
3
1 1 2

```

### 输出

```
3

```

