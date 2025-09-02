---
title: "Set of Strings"
layout: "post"
diff: 入门
pid: CF544A
tag: []
---

# Set of Strings

## 题目描述

You are given a string $ q $ . A sequence of $ k $ strings $ s_{1},s_{2},...,s_{k} $ is called beautiful, if the concatenation of these strings is string $ q $ (formally, $ s_{1}+s_{2}+...+s_{k}=q $ ) and the first characters of these strings are distinct.

Find any beautiful sequence of strings or determine that the beautiful sequence doesn't exist.

## 输入格式

The first line contains a positive integer $ k $ ( $ 1<=k<=26 $ ) — the number of strings that should be in a beautiful sequence.

The second line contains string $ q $ , consisting of lowercase Latin letters. The length of the string is within range from $ 1 $ to $ 100 $ , inclusive.

## 输出格式

If such sequence doesn't exist, then print in a single line "NO" (without the quotes). Otherwise, print in the first line "YES" (without the quotes) and in the next $ k $ lines print the beautiful sequence of strings $ s_{1},s_{2},...,s_{k} $ .

If there are multiple possible answers, print any of them.

## 说明/提示

In the second sample there are two possible answers: $ {&quot;aaaca&quot;,&quot;s&quot;} $ and $ {&quot;aaa&quot;,&quot;cas&quot;} $ .

## 样例 #1

### 输入

```
1
abca

```

### 输出

```
YES
abca

```

## 样例 #2

### 输入

```
2
aaacas

```

### 输出

```
YES
aaa
cas

```

## 样例 #3

### 输入

```
4
abc

```

### 输出

```
NO

```

