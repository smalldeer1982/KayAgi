---
title: "Yet Another Substring Reverse"
layout: "post"
diff: 提高+/省选-
pid: CF1234F
tag: ['动态规划 DP', '状态合并']
---

# Yet Another Substring Reverse

## 题目描述

You are given a string $ s $ consisting only of first $ 20 $ lowercase Latin letters ('a', 'b', ..., 't').

Recall that the substring $ s[l; r] $ of the string $ s $ is the string $ s_l s_{l + 1} \dots s_r $ . For example, the substrings of "codeforces" are "code", "force", "f", "for", but not "coder" and "top".

You can perform the following operation no more than once: choose some substring $ s[l; r] $ and reverse it (i.e. the string $ s_l s_{l + 1} \dots s_r $ becomes $ s_r s_{r - 1} \dots s_l $ ).

Your goal is to maximize the length of the maximum substring of $ s $ consisting of distinct (i.e. unique) characters.

The string consists of distinct characters if no character in this string appears more than once. For example, strings "abcde", "arctg" and "minecraft" consist of distinct characters but strings "codeforces", "abacaba" do not consist of distinct characters.

## 输入格式

The only line of the input contains one string $ s $ consisting of no more than $ 10^6 $ characters 'a', 'b', ..., 't' (first $ 20 $ lowercase Latin letters).

## 输出格式

Print one integer — the maximum possible length of the maximum substring of $ s $ consisting of distinct characters after reversing no more than one its substring.

## 样例 #1

### 输入

```
abacaba

```

### 输出

```
3

```

## 样例 #2

### 输入

```
abcdecdf

```

### 输出

```
6

```

## 样例 #3

### 输入

```
aabbcc

```

### 输出

```
3

```

## 样例 #4

### 输入

```
abcdeefc

```

### 输出

```
6

```

