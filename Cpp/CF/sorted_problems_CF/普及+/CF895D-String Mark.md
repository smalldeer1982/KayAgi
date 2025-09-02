---
title: "String Mark"
layout: "post"
diff: 普及+/提高
pid: CF895D
tag: []
---

# String Mark

## 题目描述

At the Byteland State University marks are strings of the same length. Mark $ x $ is considered better than $ y $ if string $ y $ is lexicographically smaller than $ x $ .

Recently at the BSU was an important test work on which Vasya recived the mark $ a $ . It is very hard for the teacher to remember the exact mark of every student, but he knows the mark $ b $ , such that every student recieved mark strictly smaller than $ b $ .

Vasya isn't satisfied with his mark so he decided to improve it. He can swap characters in the string corresponding to his mark as many times as he like. Now he want to know only the number of different ways to improve his mark so that his teacher didn't notice something suspicious.

More formally: you are given two strings $ a $ , $ b $ of the same length and you need to figure out the number of different strings $ c $ such that:

1\) $ c $ can be obtained from $ a $ by swapping some characters, in other words $ c $ is a permutation of $ a $ .

2\) String $ a $ is lexicographically smaller than $ c $ .

3\) String $ c $ is lexicographically smaller than $ b $ .

For two strings $ x $ and $ y $ of the same length it is true that $ x $ is lexicographically smaller than $ y $ if there exists such $ i $ , that $ x_{1}=y_{1},x_{2}=y_{2},...,x_{i-1}=y_{i-1},x_{i}<y_{i} $ .

Since the answer can be very large, you need to find answer modulo $ 10^{9}+7 $ .

## 输入格式

First line contains string $ a $ , second line contains string $ b $ . Strings $ a,b $ consist of lowercase English letters. Their lengths are equal and don't exceed $ 10^{6} $ .

It is guaranteed that $ a $ is lexicographically smaller than $ b $ .

## 输出格式

Print one integer — the number of different strings satisfying the condition of the problem modulo $ 10^{9}+7 $ .

## 说明/提示

In first sample from string $ abc $ can be obtained strings $ acb,bac,bca,cab,cba $ , all of them are larger than $ abc $ , but smaller than $ ddd $ . So the answer is $ 5 $ .

In second sample any string obtained from $ abcdef $ is larger than $ abcdeg $ . So the answer is $ 0 $ .

## 样例 #1

### 输入

```
abc
ddd

```

### 输出

```
5

```

## 样例 #2

### 输入

```
abcdef
abcdeg

```

### 输出

```
0

```

## 样例 #3

### 输入

```
abacaba
ubuduba

```

### 输出

```
64

```

