---
title: "JUSTAPAL - Just a Palindrome"
layout: "post"
diff: 难度0
pid: SP34117
tag: []
---

# JUSTAPAL - Just a Palindrome

## 题目描述

A palindrome is a symmetrical string, that is, a string read identically from left to right as well as from right to left.

Chiaki has a string $ s $ and she can perform the following operation at most once:

- choose two integer $ i $ and $ j $ ( $ 1 \le i, j \le |s| $ ).
- swap $ s_i $ and $ s_j $ .

Chiaki would like to know the longest palindromic substring of string after the operation.

## 输入格式

There are multiple test cases. The first line of input contains an integer $ T $ , indicating the number of test cases. For each test case:

The first line contains a non-empty string $ s $ ( $ 1 \le |s| \le 10^6 $ ) consisting of lowercase and uppercase letters.

It is guaranteed that the sum of all $ |s| $ does not exceed $ 10^6 $ .

## 输出格式

For each test case, output an integer denoting the answer.

## 样例 #1

### 输入

```
10
a
xxxx
ssfs
aaabbacaa
missimxx
ababababgg
dfsfsdgdg
asdsasdswe
chiaki
teretwer
```

### 输出

```
1
4
3
8
6
9
6
9
3
6
```

