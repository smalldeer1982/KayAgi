---
title: "The Text Splitting"
layout: "post"
diff: 普及-
pid: CF612A
tag: []
---

# The Text Splitting

## 题目描述

You are given the string $ s $ of length $ n $ and the numbers $ p,q $ . Split the string $ s $ to pieces of length $ p $ and $ q $ .

For example, the string "Hello" for $ p=2 $ , $ q=3 $ can be split to the two strings "Hel" and "lo" or to the two strings "He" and "llo".

Note it is allowed to split the string $ s $ to the strings only of length $ p $ or to the strings only of length $ q $ (see the second sample test).

## 输入格式

The first line contains three positive integers $ n,p,q $ ( $ 1<=p,q<=n<=100 $ ).

The second line contains the string $ s $ consists of lowercase and uppercase latin letters and digits.

## 输出格式

If it's impossible to split the string $ s $ to the strings of length $ p $ and $ q $ print the only number "-1".

Otherwise in the first line print integer $ k $ — the number of strings in partition of $ s $ .

Each of the next $ k $ lines should contain the strings in partition. Each string should be of the length $ p $ or $ q $ . The string should be in order of their appearing in string $ s $ — from left to right.

If there are several solutions print any of them.

## 样例 #1

### 输入

```
5 2 3
Hello

```

### 输出

```
2
He
llo

```

## 样例 #2

### 输入

```
10 9 5
Codeforces

```

### 输出

```
2
Codef
orces

```

## 样例 #3

### 输入

```
6 4 5
Privet

```

### 输出

```
-1

```

## 样例 #4

### 输入

```
8 1 1
abacabac

```

### 输出

```
8
a
b
a
c
a
b
a
c

```

