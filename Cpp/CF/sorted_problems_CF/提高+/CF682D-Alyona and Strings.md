---
title: "Alyona and Strings"
layout: "post"
diff: 提高+/省选-
pid: CF682D
tag: []
---

# Alyona and Strings

## 题目描述

After returned from forest, Alyona started reading a book. She noticed strings $ s $ and $ t $ , lengths of which are $ n $ and $ m $ respectively. As usual, reading bored Alyona and she decided to pay her attention to strings $ s $ and $ t $ , which she considered very similar.

Alyona has her favourite positive integer $ k $ and because she is too small, $ k $ does not exceed $ 10 $ . The girl wants now to choose $ k $ disjoint non-empty substrings of string $ s $ such that these strings appear as disjoint substrings of string $ t $ and in the same order as they do in string $ s $ . She is also interested in that their length is maximum possible among all variants.

Formally, Alyona wants to find a sequence of $ k $ non-empty strings $ p_{1},p_{2},p_{3},...,p_{k} $ satisfying following conditions:

- $ s $ can be represented as concatenation $ a_{1}p_{1}a_{2}p_{2}...\ a_{k}p_{k}a_{k+1} $ , where $ a_{1},a_{2},...,a_{k+1} $ is a sequence of arbitrary strings (some of them may be possibly empty);
- $ t $ can be represented as concatenation $ b_{1}p_{1}b_{2}p_{2}...\ b_{k}p_{k}b_{k+1} $ , where $ b_{1},b_{2},...,b_{k+1} $ is a sequence of arbitrary strings (some of them may be possibly empty);
- sum of the lengths of strings in sequence is maximum possible.

Please help Alyona solve this complicated problem and find at least the sum of the lengths of the strings in a desired sequence.

A substring of a string is a subsequence of consecutive characters of the string.

## 输入格式

In the first line of the input three integers $ n $ , $ m $ , $ k $ ( $ 1<=n,m<=1000 $ , $ 1<=k<=10 $ ) are given — the length of the string $ s $ , the length of the string $ t $ and Alyona's favourite number respectively.

The second line of the input contains string $ s $ , consisting of lowercase English letters.

The third line of the input contains string $ t $ , consisting of lowercase English letters.

## 输出格式

In the only line print the only non-negative integer — the sum of the lengths of the strings in a desired sequence.

It is guaranteed, that at least one desired sequence exists.

## 说明/提示

The following image describes the answer for the second sample case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF682D/2e74041884d67a1d079badb418366bd0a678e7b0.png)

## 样例 #1

### 输入

```
3 2 2
abc
ab

```

### 输出

```
2

```

## 样例 #2

### 输入

```
9 12 4
bbaaababb
abbbabbaaaba

```

### 输出

```
7

```

