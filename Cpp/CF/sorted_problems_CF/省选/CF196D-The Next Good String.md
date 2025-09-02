---
title: "The Next Good String"
layout: "post"
diff: 省选/NOI-
pid: CF196D
tag: ['字符串', '枚举', '哈希 hashing']
---

# The Next Good String

## 题目描述

In problems on strings one often has to find a string with some particular properties. The problem authors were reluctant to waste time on thinking of a name for some string so they called it good. A string is good if it doesn't have palindrome substrings longer than or equal to $ d $ .

You are given string $ s $ , consisting only of lowercase English letters. Find a good string $ t $ with length $ |s| $ , consisting of lowercase English letters, which is lexicographically larger than $ s $ . Of all such strings string $ t $ must be lexicographically minimum.

We will call a non-empty string $ s[a ... b]=s_{a}s_{a+1}...\ s_{b} $ $ (1<=a<=b<=|s|) $ a substring of string $ s=s_{1}s_{2}...\ s_{|s|} $ .

A non-empty string $ s=s_{1}s_{2}...\ s_{n} $ is called a palindrome if for all $ i $ from $ 1 $ to $ n $ the following fulfills: $ s_{i}=s_{n-i+1} $ . In other words, palindrome read the same in both directions.

String $ x=x_{1}x_{2}...\ x_{|x|} $ is lexicographically larger than string $ y=y_{1}y_{2}...\ y_{|y|} $ , if either $ |x|&gt;|y| $ and $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{|y|}=y_{|y|} $ , or there exists such number $ r $ $ (r&lt;|x|,r&lt;|y|) $ , that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}&gt;y_{r+1} $ . Characters in such strings are compared like their ASCII codes.

## 输入格式

The first line contains integer $ d $ ( $ 1<=d<=|s| $ ).

The second line contains a non-empty string $ s $ , its length is no more than $ 4·10^{5} $ characters. The string consists of lowercase English letters.

## 输出格式

Print the good string that lexicographically follows $ s $ , has the same length and consists of only lowercase English letters. If such string does not exist, print "Impossible" (without the quotes).

## 样例 #1

### 输入

```
3
aaaaaaa

```

### 输出

```
aabbcaa

```

## 样例 #2

### 输入

```
3
zzyzzzz

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
4
abbabbbabbb

```

### 输出

```
abbbcaaabab

```

