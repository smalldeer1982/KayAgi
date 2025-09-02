---
title: "Pangram"
layout: "post"
diff: 入门
pid: CF520A
tag: ['模拟', '字符串', '二分', '枚举']
---

# Pangram

## 题目描述

A word or a sentence in some language is called a pangram if all the characters of the alphabet of this language appear in it at least once. Pangrams are often used to demonstrate fonts in printing or test the output devices.

You are given a string consisting of lowercase and uppercase Latin letters. Check whether this string is a pangram. We say that the string contains a letter of the Latin alphabet if this letter occurs in the string in uppercase or lowercase.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=100 $ ) — the number of characters in the string.

The second line contains the string. The string consists only of uppercase and lowercase Latin letters.

## 输出格式

Output "YES", if the string is a pangram and "NO" otherwise.

## 样例 #1

### 输入

```
12
toosmallword

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
35
TheQuickBrownFoxJumpsOverTheLazyDog

```

### 输出

```
YES

```

