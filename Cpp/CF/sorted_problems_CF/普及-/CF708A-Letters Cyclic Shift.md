---
title: "Letters Cyclic Shift"
layout: "post"
diff: 普及-
pid: CF708A
tag: ['字符串']
---

# Letters Cyclic Shift

## 题目描述

You are given a non-empty string $ s $ consisting of lowercase English letters. You have to pick exactly one non-empty substring of $ s $ and shift all its letters 'z' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'y' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'x' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/23d27bb9cf2cd76a0555d2babeb08bc9315530bc.png) 'b' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'a' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'z'. In other words, each character is replaced with the previous character of English alphabet and 'a' is replaced with 'z'.

What is the lexicographically minimum string that can be obtained from $ s $ by performing this shift exactly once?

## 输入格式

The only line of the input contains the string $ s $ ( $ 1<=|s|<=100000 $ ) consisting of lowercase English letters.

## 输出格式

Print the lexicographically minimum string that can be obtained from $ s $ by shifting letters of exactly one non-empty substring.

## 说明/提示

String $ s $ is lexicographically smaller than some other string $ t $ of the same length if there exists some $ 1<=i<=|s| $ , such that $ s_{1}=t_{1},s_{2}=t_{2},...,s_{i-1}=t_{i-1} $ , and $ s_{i}&lt;t_{i} $ .

## 样例 #1

### 输入

```
codeforces

```

### 输出

```
bncdenqbdr

```

## 样例 #2

### 输入

```
abacaba

```

### 输出

```
aaacaba

```

