---
title: "Levko and Strings"
layout: "post"
diff: 省选/NOI-
pid: CF360C
tag: []
---

# Levko and Strings

## 题目描述

Levko loves strings of length $ n $ , consisting of lowercase English letters, very much. He has one such string $ s $ . For each string $ t $ of length $ n $ , Levko defines its beauty relative to $ s $ as the number of pairs of indexes $ i $ , $ j $ $ (1<=i<=j<=n) $ , such that substring  $ t[i..j] $ is lexicographically larger than substring $ s[i..j] $ .

The boy wondered how many strings $ t $ are there, such that their beauty relative to $ s $ equals exactly $ k $ . Help him, find the remainder after division this number by $ 1000000007 $ $ (10^{9}+7) $ .

A substring $ s[i..j] $ of string $ s=s_{1}s_{2}...\ s_{n} $ is string $ s_{i}s_{i+1}...\ s_{j} $ .

String $ x=x_{1}x_{2}...\ x_{p} $ is lexicographically larger than string $ y=y_{1}y_{2}...\ y_{p} $ , if there is such number $ r $ ( $ r&lt;p $ ), that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}&gt;y_{r+1} $ . The string characters are compared by their ASCII codes.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=2000 $ , $ 0<=k<=2000 $ ).

The second line contains a non-empty string $ s $ of length $ n $ . String $ s $ consists only of lowercase English letters.

## 输出格式

Print a single number — the answer to the problem modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
2 2
yz

```

### 输出

```
26

```

## 样例 #2

### 输入

```
2 3
yx

```

### 输出

```
2

```

## 样例 #3

### 输入

```
4 7
abcd

```

### 输出

```
21962

```

