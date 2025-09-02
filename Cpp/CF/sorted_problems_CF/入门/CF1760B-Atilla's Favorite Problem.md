---
title: "Atilla's Favorite Problem"
layout: "post"
diff: 入门
pid: CF1760B
tag: []
---

# Atilla's Favorite Problem

## 题目描述

In order to write a string, Atilla needs to first learn all letters that are contained in the string.

Atilla needs to write a message which can be represented as a string $ s $ . He asks you what is the minimum alphabet size required so that one can write this message.

The alphabet of size $ x $ ( $ 1 \leq x \leq 26 $ ) contains only the first $ x $ Latin letters. For example an alphabet of size $ 4 $ contains only the characters $ \texttt{a} $ , $ \texttt{b} $ , $ \texttt{c} $ and $ \texttt{d} $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 100 $ ) — the length of the string.

The second line of each test case contains a string $ s $ of length $ n $ , consisting of lowercase Latin letters.

## 输出格式

For each test case, output a single integer — the minimum alphabet size required to so that Atilla can write his message $ s $ .

## 说明/提示

For the first test case, Atilla needs to know only the character $ \texttt{a} $ , so the alphabet of size $ 1 $ which only contains $ \texttt{a} $ is enough.

For the second test case, Atilla needs to know the characters $ \texttt{d} $ , $ \texttt{o} $ , $ \texttt{w} $ , $ \texttt{n} $ . The smallest alphabet size that contains all of them is $ 23 $ (such alphabet can be represented as the string $ \texttt{abcdefghijklmnopqrstuvw} $ ).

## 样例 #1

### 输入

```
5
1
a
4
down
10
codeforces
3
bcf
5
zzzzz
```

### 输出

```
1
23
19
6
26
```

