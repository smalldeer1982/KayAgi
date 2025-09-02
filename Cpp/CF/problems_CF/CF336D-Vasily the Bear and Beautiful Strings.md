---
title: "Vasily the Bear and Beautiful Strings"
layout: "post"
diff: 提高+/省选-
pid: CF336D
tag: []
---

# Vasily the Bear and Beautiful Strings

## 题目描述

Vasily the Bear loves beautiful strings. String $ s $ is beautiful if it meets the following criteria:

1. String $ s $ only consists of characters $ 0 $ and $ 1 $ , at that character $ 0 $ must occur in string $ s $ exactly $ n $ times, and character $ 1 $ must occur exactly $ m $ times.
2. We can obtain character $ g $ from string $ s $ with some (possibly, zero) number of modifications. The character $ g $ equals either zero or one.

A modification of string with length at least two is the following operation: we replace two last characters from the string by exactly one other character. This character equals one if it replaces two zeros, otherwise it equals zero. For example, one modification transforms string "01010" into string "0100", two modifications transform it to "011". It is forbidden to modify a string with length less than two.

Help the Bear, count the number of beautiful strings. As the number of beautiful strings can be rather large, print the remainder after dividing the number by $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line of the input contains three space-separated integers $ n,m,g $ $ (0<=n,m<=10^{5},n+m>=1,0<=g<=1) $ .

## 输出格式

Print a single integer — the answer to the problem modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample the beautiful strings are: "01", "10".

In the second sample the beautiful strings are: "0011", "1001", "1010", "1100".

In the third sample there are no beautiful strings.

## 样例 #1

### 输入

```
1 1 0

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 2 0

```

### 输出

```
4

```

## 样例 #3

### 输入

```
1 1 1

```

### 输出

```
0

```

