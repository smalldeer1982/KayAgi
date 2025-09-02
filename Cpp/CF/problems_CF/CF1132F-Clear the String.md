---
title: "Clear the String"
layout: "post"
diff: 提高+/省选-
pid: CF1132F
tag: ['动态规划 DP', '区间 DP']
---

# Clear the String

## 题目描述

You are given a string $ s $ of length $ n $ consisting of lowercase Latin letters. You may apply some operations to this string: in one operation you can delete some contiguous substring of this string, if all letters in the substring you delete are equal. For example, after deleting substring bbbb from string abbbbaccdd we get the string aaccdd.

Calculate the minimum number of operations to delete the whole string $ s $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 500 $ ) — the length of string $ s $ .

The second line contains the string $ s $ ( $ |s| = n $ ) consisting of lowercase Latin letters.

## 输出格式

Output a single integer — the minimal number of operation to delete string $ s $ .

## 样例 #1

### 输入

```
5
abaca

```

### 输出

```
3

```

## 样例 #2

### 输入

```
8
abcddcba

```

### 输出

```
4

```

