---
title: "Text Volume"
layout: "post"
diff: 入门
pid: CF837A
tag: ['字符串', '概率论']
---

# Text Volume

## 题目描述

You are given a text of single-space separated words, consisting of small and capital Latin letters.

Volume of the word is number of capital letters in the word. Volume of the text is maximum volume of all words in the text.

Calculate the volume of the given text.

## 输入格式

The first line contains one integer number $ n $ ( $ 1<=n<=200 $ ) — length of the text.

The second line contains text of single-space separated words $ s_{1},s_{2},...,s_{i} $ , consisting only of small and capital Latin letters.

## 输出格式

Print one integer number — volume of text.

## 说明/提示

In the first example there is only one word, there are 5 capital letters in it.

In the second example all of the words contain 0 capital letters.

## 样例 #1

### 输入

```
7
NonZERO

```

### 输出

```
5

```

## 样例 #2

### 输入

```
24
this is zero answer text

```

### 输出

```
0

```

## 样例 #3

### 输入

```
24
Harbour Space University

```

### 输出

```
1

```

