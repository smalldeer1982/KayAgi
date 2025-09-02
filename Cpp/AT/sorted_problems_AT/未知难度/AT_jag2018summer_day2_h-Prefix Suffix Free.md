---
title: "Prefix Suffix Free"
layout: "post"
diff: 难度0
pid: AT_jag2018summer_day2_h
tag: []
---

# Prefix Suffix Free

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jag2018summer-day2/tasks/jag2018summer_day2_h

You are given a string $ S $ consisting of lowercase English letters. Count the number of strings $ T $ that satisfies all of the following conditions:

- $ T $ is a string of the same length as $ S $, consisting of lowercase English letters.
- For all $ K $ ( $ 1\ \leq\ K\ \leq\ |S| $ ), the string formed by the first $ K $ letters of $ S $ does not coincide with the string formed by the last $ K $ letters of $ T $.

Since the answer can be very large, find the number modulo $ 10^9+7 $.

## 输入格式

Input is given from Standard Input in the following format:

> $ S $

## 输出格式

Print the number of strings that satisfy the condition, modulo $ 10^9+7 $.

## 说明/提示

### Constraints

- $ 1\ \leq\ |S|\ \leq\ 10^6 $
- $ S $ consists of lowercase English letters.

### Sample Explanation 1

For example, $ T= $ `zz` and `ab` satisfy the condition, but `ba` or `aa` does not.

## 样例 #1

### 输入

```
aa
```

### 输出

```
650
```

## 样例 #2

### 输入

```
abc
```

### 输出

```
16873
```

## 样例 #3

### 输入

```
xrxbaxrxikxrxgvcpuwx
```

### 输出

```
352084595
```

