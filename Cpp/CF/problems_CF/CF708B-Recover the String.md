---
title: "Recover the String"
layout: "post"
diff: 普及+/提高
pid: CF708B
tag: []
---

# Recover the String

## 题目描述

For each string $ s $ consisting of characters '0' and '1' one can define four integers $ a_{00} $ , $ a_{01} $ , $ a_{10} $ and $ a_{11} $ , where $ a_{xy} $ is the number of subsequences of length $ 2 $ of the string $ s $ equal to the sequence $ {x,y} $ .

In these problem you are given four integers $ a_{00} $ , $ a_{01} $ , $ a_{10} $ , $ a_{11} $ and have to find any non-empty string $ s $ that matches them, or determine that there is no such string. One can prove that if at least one answer exists, there exists an answer of length no more than $ 1000000 $ .

## 输入格式

The only line of the input contains four non-negative integers $ a_{00} $ , $ a_{01} $ , $ a_{10} $ and $ a_{11} $ . Each of them doesn't exceed $ 10^{9} $ .

## 输出格式

If there exists a non-empty string that matches four integers from the input, print it in the only line of the output. Otherwise, print "Impossible". The length of your answer must not exceed $ 1000000 $ .

## 样例 #1

### 输入

```
1 2 3 4

```

### 输出

```
Impossible

```

## 样例 #2

### 输入

```
1 2 2 1

```

### 输出

```
0110

```

