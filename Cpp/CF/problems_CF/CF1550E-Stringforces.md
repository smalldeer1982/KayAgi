---
title: "Stringforces"
layout: "post"
diff: 提高+/省选-
pid: CF1550E
tag: []
---

# Stringforces

## 题目描述

You are given a string $ s $ of length $ n $ . Each character is either one of the first $ k $ lowercase Latin letters or a question mark.

You are asked to replace every question mark with one of the first $ k $ lowercase Latin letters in such a way that the following value is maximized.

Let $ f_i $ be the maximum length substring of string $ s $ , which consists entirely of the $ i $ -th Latin letter. A substring of a string is a contiguous subsequence of that string. If the $ i $ -th letter doesn't appear in a string, then $ f_i $ is equal to $ 0 $ .

The value of a string $ s $ is the minimum value among $ f_i $ for all $ i $ from $ 1 $ to $ k $ .

What is the maximum value the string can have?

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ ; $ 1 \le k \le 17 $ ) — the length of the string and the number of first Latin letters used.

The second line contains a string $ s $ , consisting of $ n $ characters. Each character is either one of the first $ k $ lowercase Latin letters or a question mark.

## 输出格式

Print a single integer — the maximum value of the string after every question mark is replaced with one of the first $ k $ lowercase Latin letters.

## 说明/提示

In the first example the question marks can be replaced in the following way: "aaaababbbb". $ f_1 = 4 $ , $ f_2 = 4 $ , thus the answer is $ 4 $ . Replacing it like this is also possible: "aaaabbbbbb". That way $ f_1 = 4 $ , $ f_2 = 6 $ , however, the minimum of them is still $ 4 $ .

In the second example one of the possible strings is "aabbccdda".

In the third example at least one letter won't appear in the string, thus, the minimum of values $ f_i $ is always $ 0 $ .

## 样例 #1

### 输入

```
10 2
a??ab????b
```

### 输出

```
4
```

## 样例 #2

### 输入

```
9 4
?????????
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2 3
??
```

### 输出

```
0
```

## 样例 #4

### 输入

```
15 3
??b?babbc??b?aa
```

### 输出

```
3
```

## 样例 #5

### 输入

```
4 4
cabd
```

### 输出

```
1
```

