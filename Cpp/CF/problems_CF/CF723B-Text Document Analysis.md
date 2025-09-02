---
title: "Text Document Analysis"
layout: "post"
diff: 普及-
pid: CF723B
tag: []
---

# Text Document Analysis

## 题目描述

Modern text editors usually show some information regarding the document being edited. For example, the number of words, the number of pages, or the number of characters.

In this problem you should implement the similar functionality.

You are given a string which only consists of:

- uppercase and lowercase English letters,
- underscore symbols (they are used as separators),
- parentheses (both opening and closing).

It is guaranteed that each opening parenthesis has a succeeding closing parenthesis. Similarly, each closing parentheses has a preceding opening parentheses matching it. For each pair of matching parentheses there are no other parenthesis between them. In other words, each parenthesis in the string belongs to a matching "opening-closing" pair, and such pairs can't be nested.

For example, the following string is valid: "\_Hello\_Vasya(and\_Petya)\_\_bye\_(and\_OK)".

Word is a maximal sequence of consecutive letters, i.e. such sequence that the first character to the left and the first character to the right of it is an underscore, a parenthesis, or it just does not exist. For example, the string above consists of seven words: "Hello", "Vasya", "and", "Petya", "bye", "and" and "OK". Write a program that finds:

- the length of the longest word outside the parentheses (print 0, if there is no word outside the parentheses),
- the number of words inside the parentheses (print 0, if there is no word inside the parentheses).

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=255 $ ) — the length of the given string. The second line contains the string consisting of only lowercase and uppercase English letters, parentheses and underscore symbols.

## 输出格式

Print two space-separated integers:

- the length of the longest word outside the parentheses (print 0, if there is no word outside the parentheses),
- the number of words inside the parentheses (print 0, if there is no word inside the parentheses).

## 说明/提示

In the first sample, the words "Hello", "Vasya" and "bye" are outside any of the parentheses, and the words "and", "Petya", "and" and "OK" are inside. Note, that the word "and" is given twice and you should count it twice in the answer.

## 样例 #1

### 输入

```
37
_Hello_Vasya(and_Petya)__bye_(and_OK)

```

### 输出

```
5 4
```

## 样例 #2

### 输入

```
37
_a_(_b___c)__de_f(g_)__h__i(j_k_l)m__

```

### 输出

```
2 6
```

## 样例 #3

### 输入

```
27
(LoooonG)__shOrt__(LoooonG)

```

### 输出

```
5 2
```

## 样例 #4

### 输入

```
5
(___)

```

### 输出

```
0 0

```

