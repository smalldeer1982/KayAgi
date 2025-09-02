---
title: "Two Substrings"
layout: "post"
diff: 普及/提高-
pid: CF550A
tag: []
---

# Two Substrings

## 题目描述

You are given string $ s $ . Your task is to determine if the given string $ s $ contains two non-overlapping substrings "AB" and "BA" (the substrings can go in any order).

## 输入格式

The only line of input contains a string $ s $ of length between $ 1 $ and $ 10^{5} $ consisting of uppercase Latin letters.

## 输出格式

Print "YES" (without the quotes), if string $ s $ contains two non-overlapping substrings "AB" and "BA", and "NO" otherwise.

## 说明/提示

In the first sample test, despite the fact that there are substrings "AB" and "BA", their occurrences overlap, so the answer is "NO".

In the second sample test there are the following occurrences of the substrings: BACFAB.

In the third sample test there is no substring "AB" nor substring "BA".

## 样例 #1

### 输入

```
ABA

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
BACFAB

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
AXBYBXA

```

### 输出

```
NO

```

