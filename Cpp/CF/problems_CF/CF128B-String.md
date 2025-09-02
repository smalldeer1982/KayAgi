---
title: "String"
layout: "post"
diff: 省选/NOI-
pid: CF128B
tag: []
---

# String

## 题目描述

One day in the IT lesson Anna and Maria learned about the lexicographic order.

String $ x $ is lexicographically less than string $ y $ , if either $ x $ is a prefix of $ y $ (and $ x≠y $ ), or there exists such $ i $ ( $ 1<=i<=min(|x|,|y|) $ ), that $ x_{i}&lt;y_{i} $ , and for any $ j $ ( $ 1<=j&lt;i $ ) $ x_{j}=y_{j} $ . Here $ |a| $ denotes the length of the string $ a $ . The lexicographic comparison of strings is implemented by operator < in modern programming languages​​.

The teacher gave Anna and Maria homework. She gave them a string of length $ n $ . They should write out all substrings of the given string, including the whole initial string, and the equal substrings (for example, one should write out the following substrings from the string "aab": "a", "a", "aa", "ab", "aab", "b"). The resulting strings should be sorted in the lexicographical order. The cunning teacher doesn't want to check all these strings. That's why she said to find only the $ k $ -th string from the list. Help Anna and Maria do the homework.

## 输入格式

The first line contains a non-empty string that only consists of small Latin letters ("a"-"z"), whose length does not exceed $ 10^{5} $ . The second line contains the only integer $ k $ ( $ 1<=k<=10^{5} $ ).

## 输出格式

Print the string Anna and Maria need — the $ k $ -th (in the lexicographical order) substring of the given string. If the total number of substrings is less than $ k $ , print a string saying "No such line." (without the quotes).

## 说明/提示

In the second sample before string "bc" follow strings "a", "ab", "abc", "b".

## 样例 #1

### 输入

```
aa
2

```

### 输出

```
a

```

## 样例 #2

### 输入

```
abc
5

```

### 输出

```
bc

```

## 样例 #3

### 输入

```
abab
7

```

### 输出

```
b

```

