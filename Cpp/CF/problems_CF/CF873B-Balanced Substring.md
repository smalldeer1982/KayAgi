---
title: "Balanced Substring"
layout: "post"
diff: 普及+/提高
pid: CF873B
tag: ['字符串', '前缀和']
---

# Balanced Substring

## 题目描述

You are given a string $ s $ consisting only of characters 0 and 1. A substring $ [l,r] $ of $ s $ is a string $ s_{l}s_{l+1}s_{l+2}...\ s_{r} $ , and its length equals to $ r-l+1 $ . A substring is called balanced if the number of zeroes (0) equals to the number of ones in this substring.

You have to determine the length of the longest balanced substring of $ s $ .

## 输入格式

The first line contains $ n $ ( $ 1<=n<=100000 $ ) — the number of characters in $ s $ .

The second line contains a string $ s $ consisting of exactly $ n $ characters. Only characters 0 and 1 can appear in $ s $ .

## 输出格式

If there is no non-empty balanced substring in $ s $ , print 0. Otherwise, print the length of the longest balanced substring.

## 说明/提示

In the first example you can choose the substring $ [3,6] $ . It is balanced, and its length is $ 4 $ . Choosing the substring $ [2,5] $ is also possible.

In the second example it's impossible to find a non-empty balanced substring.

## 样例 #1

### 输入

```
8
11010111

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3
111

```

### 输出

```
0

```

