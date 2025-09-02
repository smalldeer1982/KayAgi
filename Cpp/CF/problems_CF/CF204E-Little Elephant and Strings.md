---
title: "Little Elephant and Strings"
layout: "post"
diff: 省选/NOI-
pid: CF204E
tag: []
---

# Little Elephant and Strings

## 题目描述

The Little Elephant loves strings very much.

He has an array $ a $ from $ n $ strings, consisting of lowercase English letters. Let's number the elements of the array from 1 to $ n $ , then let's denote the element number $ i $ as $ a_{i} $ . For each string $ a_{i} $ $ (1<=i<=n) $ the Little Elephant wants to find the number of pairs of integers $ l $ and $ r $ $ (1<=l<=r<=|a_{i}|) $ such that substring $ a_{i}[l...\ r] $ is a substring to at least $ k $ strings from array $ a $ (including the $ i $ -th string).

Help the Little Elephant solve this problem.

If you are not familiar with the basic notation in string problems, you can find the corresponding definitions in the notes.

## 输入格式

The first line contains two space-separated integers — $ n $ and $ k $ $ (1<=n,k<=10^{5}) $ . Next $ n $ lines contain array $ a $ . The $ i $ -th line contains a non-empty string $ a_{i} $ , consisting of lowercase English letter. The total length of all strings $ a_{i} $ does not exceed $ 10^{5} $ .

## 输出格式

On a single line print $ n $ space-separated integers — the $ i $ -th number is the answer for string $ a_{i} $ .

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

Let's assume that you are given string $ a=a_{1}a_{2}...\ a_{|a|} $ , then let's denote the string's length as $ |a| $ and the string's $ i $ -th character as $ a_{i} $ .

A substring $ a[l...\ r] $ $ (1<=l<=r<=|a|) $ of string $ a $ is string $ a_{l}a_{l+1}...\ a_{r} $ .

String $ a $ is a substring of string $ b $ , if there exists such pair of integers $ l $ and $ r $ $ (1<=l<=r<=|b|) $ , that $ b[l...\ r]=a $ .

## 样例 #1

### 输入

```
3 1
abc
a
ab

```

### 输出

```
6 1 3 

```

## 样例 #2

### 输入

```
7 4
rubik
furik
abab
baba
aaabbbababa
abababababa
zero

```

### 输出

```
1 0 9 9 21 30 0 

```

