---
title: "Lucky Common Subsequence"
layout: "post"
diff: 提高+/省选-
pid: CF346B
tag: ['字符串', '动态规划 DP', '枚举', 'KMP 算法']
---

# Lucky Common Subsequence

## 题目描述

In mathematics, a subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements. For example, the sequence BDF is a subsequence of ABCDEF. A substring of a string is a continuous subsequence of the string. For example, BCD is a substring of ABCDEF.

You are given two strings $ s_{1} $ , $ s_{2} $ and another string called $ virus $ . Your task is to find the longest common subsequence of $ s_{1} $ and $ s_{2} $ , such that it doesn't contain $ virus $ as a substring.

## 输入格式

The input contains three strings in three separate lines: $ s_{1} $ , $ s_{2} $ and $ virus $ ( $ 1<=|s_{1}|,|s_{2}|,|virus|<=100 $ ). Each string consists only of uppercase English letters.

## 输出格式

Output the longest common subsequence of $ s_{1} $ and $ s_{2} $ without $ virus $ as a substring. If there are multiple answers, any of them will be accepted.

If there is no valid common subsequence, output 0.

## 样例 #1

### 输入

```
AJKEQSLOBSROFGZ
OVGURWZLWVLUXTH
OZ

```

### 输出

```
ORZ

```

## 样例 #2

### 输入

```
AA
A
A

```

### 输出

```
0

```

