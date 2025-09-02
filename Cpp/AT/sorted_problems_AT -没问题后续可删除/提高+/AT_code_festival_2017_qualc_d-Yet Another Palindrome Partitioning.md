---
title: "Yet Another Palindrome Partitioning"
layout: "post"
diff: 提高+/省选-
pid: AT_code_festival_2017_qualc_d
tag: []
---

# Yet Another Palindrome Partitioning

## 题目描述

给定一个字符串$\texttt{s}$，把$\texttt{s}$分成$N$个子串，要求每个子串中的字母经过一定的移动，会变成一个回文串（如`aab`经过一定的移动，变成了`aba`，`aba`是一个回文串），**且$N$最少**。

## 输入格式

一个字符串$\texttt{s}$（$1 \le \texttt{|s|} \le 2 \times 10^5$）

## 输出格式

一个正整数$N$，表示最少的子串个数。

## 样例 #1

### 输入

```
aabxyyzz
```

### 输出

```
2
```

## 样例 #2

### 输入

```
byebye
```

### 输出

```
1
```

## 样例 #3

### 输入

```
abcdefghijklmnopqrstuvwxyz
```

### 输出

```
26
```

## 样例 #4

### 输入

```
abcabcxabcx
```

### 输出

```
3
```

