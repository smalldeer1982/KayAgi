---
title: "Quasi-palindrome"
layout: "post"
diff: 入门
pid: CF863A
tag: ['模拟', '字符串', '概率论']
---

# Quasi-palindrome

## 题目描述

Let quasi-palindromic number be such number that adding some leading zeros (possible none) to it produces a palindromic string.

String $ t $ is called a palindrome, if it reads the same from left to right and from right to left.

For example, numbers $ 131 $ and $ 2010200 $ are quasi-palindromic, they can be transformed to strings " $ 131 $ " and " $ 002010200 $ ", respectively, which are palindromes.

You are given some integer number $ x $ . Check if it's a quasi-palindromic number.

## 输入格式

The first line contains one integer number $ x $ ( $ 1<=x<=10^{9} $ ). This number is given without any leading zeroes.

## 输出格式

Print "YES" if number $ x $ is quasi-palindromic. Otherwise, print "NO" (without quotes).

## 样例 #1

### 输入

```
131

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
320

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
2010200

```

### 输出

```
YES

```

