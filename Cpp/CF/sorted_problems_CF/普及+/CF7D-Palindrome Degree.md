---
title: "Palindrome Degree"
layout: "post"
diff: 普及+/提高
pid: CF7D
tag: ['字符串', '哈希 hashing', '构造']
---

# Palindrome Degree

## 题目描述

String $ s $ of length $ n $ is called $ k $ -palindrome, if it is a palindrome itself, and its prefix and suffix of length ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF7D/f337f976991ac53405b164907ebe1f51ebb0830e.png) are $ (k-1) $ -palindromes. By definition, any string (even empty) is 0-palindrome.

Let's call the palindrome degree of string $ s $ such a maximum number $ k $ , for which $ s $ is $ k $ -palindrome. For example, "abaaba" has degree equals to $ 3 $ .

You are given a string. Your task is to find the sum of the palindrome degrees of all its prefixes.

## 输入格式

The first line of the input data contains a non-empty string, consisting of Latin letters and digits. The length of the string does not exceed $ 5·10^{6} $ . The string is case-sensitive.

## 输出格式

Output the only number — the sum of the polindrome degrees of all the string's prefixes.

## 样例 #1

### 输入

```
a2A

```

### 输出

```
1
```

## 样例 #2

### 输入

```
abacaba

```

### 输出

```
6
```

