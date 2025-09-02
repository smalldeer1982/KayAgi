---
title: "Even Substrings"
layout: "post"
diff: 普及-
pid: CF1139A
tag: []
---

# Even Substrings

## 题目描述

You are given a string $ s=s_1s_2\dots s_n $ of length $ n $ , which only contains digits $ 1 $ , $ 2 $ , ..., $ 9 $ .

A substring $ s[l \dots r] $ of $ s $ is a string $ s_l s_{l + 1} s_{l + 2} \ldots s_r $ . A substring $ s[l \dots r] $ of $ s $ is called even if the number represented by it is even.

Find the number of even substrings of $ s $ . Note, that even if some substrings are equal as strings, but have different $ l $ and $ r $ , they are counted as different substrings.

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 65000 $ ) — the length of the string $ s $ .

The second line contains a string $ s $ of length $ n $ . The string $ s $ consists only of digits $ 1 $ , $ 2 $ , ..., $ 9 $ .

## 输出格式

Print the number of even substrings of $ s $ .

## 说明/提示

In the first example, the $ [l, r] $ pairs corresponding to even substrings are:

- $ s[1 \dots 2] $
- $ s[2 \dots 2] $
- $ s[1 \dots 4] $
- $ s[2 \dots 4] $
- $ s[3 \dots 4] $
- $ s[4 \dots 4] $

In the second example, all $ 10 $ substrings of $ s $ are even substrings. Note, that while substrings $ s[1 \dots 1] $ and $ s[2 \dots 2] $ both define the substring "2", they are still counted as different substrings.

## 样例 #1

### 输入

```
4
1234

```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
2244

```

### 输出

```
10
```

