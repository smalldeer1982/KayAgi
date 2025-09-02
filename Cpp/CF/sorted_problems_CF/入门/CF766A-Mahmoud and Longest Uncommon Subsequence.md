---
title: "Mahmoud and Longest Uncommon Subsequence"
layout: "post"
diff: 入门
pid: CF766A
tag: ['字符串']
---

# Mahmoud and Longest Uncommon Subsequence

## 题目描述

While Mahmoud and Ehab were practicing for IOI, they found a problem which name was Longest common subsequence. They solved it, and then Ehab challenged Mahmoud with another problem.

Given two strings $ a $ and $ b $ , find the length of their longest uncommon subsequence, which is the longest string that is a subsequence of one of them and not a subsequence of the other.

A subsequence of some string is a sequence of characters that appears in the same order in the string, The appearances don't have to be consecutive, for example, strings "ac", "bc", "abc" and "a" are subsequences of string "abc" while strings "abbc" and "acb" are not. The empty string is a subsequence of any string. Any string is a subsequence of itself.

## 输入格式

The first line contains string $ a $ , and the second line — string $ b $ . Both of these strings are non-empty and consist of lowercase letters of English alphabet. The length of each string is not bigger than $ 10^{5} $ characters.

## 输出格式

If there's no uncommon subsequence, print "-1". Otherwise print the length of the longest uncommon subsequence of $ a $ and $ b $ .

## 说明/提示

In the first example: you can choose "defgh" from string $ b $ as it is the longest subsequence of string $ b $ that doesn't appear as a subsequence of string $ a $ .

## 样例 #1

### 输入

```
abcd
defgh

```

### 输出

```
5

```

## 样例 #2

### 输入

```
a
a

```

### 输出

```
-1

```

