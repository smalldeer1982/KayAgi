---
title: "SSeeeeiinngg DDoouubbllee"
layout: "post"
diff: 入门
pid: CF1758A
tag: []
---

# SSeeeeiinngg DDoouubbllee

## 题目描述

A palindrome is a string that reads the same backward as forward. For example, the strings $ \texttt{z} $ , $ \texttt{aaa} $ , $ \texttt{aba} $ , and $ \texttt{abccba} $ are palindromes, but $ \texttt{codeforces} $ and $ \texttt{ab} $ are not.

The double of a string $ s $ is obtained by writing each character twice. For example, the double of $ \texttt{seeing} $ is $ \texttt{sseeeeiinngg} $ .

Given a string $ s $ , rearrange its double to form a palindrome. Output the rearranged string. It can be proven that such a rearrangement always exists.

## 输入格式

The first line of input contains $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The only line of each test case contains a single string $ s $ ( $ 1 \leq |s| \leq 100 $ ) consisting only of lowercase English letters.

Note that the sum of $ |s| $ over all test cases is not bounded.

## 输出格式

For each test case, output a palindromic string of length $ 2 \cdot |s| $ that is a rearrangement of the double of $ s $ .

## 说明/提示

In the first test case, the double of $ \texttt{a} $ is $ \texttt{aa} $ , which is already a palindrome.

In the second test case, the double of $ \texttt{sururu} $ is $ \texttt{ssuurruurruu} $ . If we move the first $ \texttt{s} $ to the end, we get $ \texttt{suurruurruus} $ , which is a palindrome.

In the third test case, the double of $ \texttt{errorgorn} $ is $ \texttt{eerrrroorrggoorrnn} $ . We can rearrange the characters to form $ \texttt{rgnororerrerorongr} $ , which is a palindrome.

## 样例 #1

### 输入

```
4
a
sururu
errorgorn
anutforajaroftuna
```

### 输出

```
aa
suurruurruus
rgnororerrerorongr
aannuuttffoorraajjaarrooffttuunnaa
```

