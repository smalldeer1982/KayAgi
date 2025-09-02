---
title: "Delicious Dessert"
layout: "post"
diff: 省选/NOI-
pid: CF1780G
tag: ['后缀自动机 SAM']
---

# Delicious Dessert

## 题目描述

Today is an important day for chef Tonio — an auditor has arrived in his hometown of Morioh. He has also arrived at Tonio's restaurant and ordered dessert. Tonio has not been prepared for this turn of events.

As you know, dessert is a string of lowercase English letters. Tonio remembered the rule of desserts — a string $ s $ of length $ n $ . Any dessert $ t $ is delicious if the number of occurrences of $ t $ in $ s $ as a substring is divisible by the length of $ t $ .

Now Tonio wants to know the number of delicious substrings of $ s $ . If the substring occurs several times in the string $ s $ , then all occurrences must be taken into account.

## 输入格式

The first line contains an integer $ n $ ( $ 1 \leq n \leq 10^6 $ ) — the length of the rule $ s $ .

The second line contains the string $ s $ of length $ n $ — the rule. The rule consists only of lowercase English letters.

## 输出格式

In a single line print the number of delicious substrings of $ s $ .

## 说明/提示

In the first sample, there are many delicious substrings. $ 7 $ of them are substrings of length $ 1 $ (because any number is divisible by $ 1 $ ). Consider other delicious substrings:

- "ab" occurs in $ s $ $ 2 $ times, which is divisible by the length of the substring.
- "ba" also occurs $ 2 $ times.

Therefore, the answer is $ 7 + 2 + 2 = 11 $ .

Note that the answer includes both occurrences of "ab" and "ba".

## 样例 #1

### 输入

```
7
abacaba
```

### 输出

```
11
```

## 样例 #2

### 输入

```
8
abaababa
```

### 输出

```
11
```

## 样例 #3

### 输入

```
10
deadinside
```

### 输出

```
12
```

## 样例 #4

### 输入

```
5
aaaaa
```

### 输出

```
12
```

