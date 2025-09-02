---
title: "Wrap Around"
layout: "post"
diff: 省选/NOI-
pid: CF1038F
tag: []
---

# Wrap Around

## 题目描述

You are given a binary string $ s $ .

Find the number of distinct cyclical binary strings of length $ n $ which contain $ s $ as a substring.

The cyclical string $ t $ contains $ s $ as a substring if there is some cyclical shift of string $ t $ , such that $ s $ is a substring of this cyclical shift of $ t $ .

For example, the cyclical string "000111" contains substrings "001", "01110" and "10", but doesn't contain "0110" and "10110".

Two cyclical strings are called different if they differ from each other as strings. For example, two different strings, which differ from each other by a cyclical shift, are still considered different cyclical strings.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 40 $ ) — the length of the target string $ t $ .

The next line contains the string $ s $ ( $ 1 \le |s| \le n $ ) — the string which must be a substring of cyclical string $ t $ . String $ s $ contains only characters '0' and '1'.

## 输出格式

Print the only integer — the number of distinct cyclical binary strings $ t $ , which contain $ s $ as a substring.

## 说明/提示

In the first example, there are three cyclical strings, which contain "0" — "00", "01" and "10".

In the second example, there are only two such strings — "1010", "0101".

## 样例 #1

### 输入

```
2
0

```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1010

```

### 输出

```
2
```

## 样例 #3

### 输入

```
20
10101010101010

```

### 输出

```
962
```

