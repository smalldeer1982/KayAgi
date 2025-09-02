---
title: "Newspaper Headline"
layout: "post"
diff: 普及/提高-
pid: CF91A
tag: []
---

# Newspaper Headline

## 题目描述

A newspaper is published in Walrusland. Its heading is $ s_{1} $ , it consists of lowercase Latin letters. Fangy the little walrus wants to buy several such newspapers, cut out their headings, glue them one to another in order to get one big string. After that walrus erase several letters from this string in order to get a new word $ s_{2} $ . It is considered that when Fangy erases some letter, there's no whitespace formed instead of the letter. That is, the string remains unbroken and it still only consists of lowercase Latin letters.

For example, the heading is "abc". If we take two such headings and glue them one to the other one, we get "abcabc". If we erase the letters on positions $ 1 $ and $ 5 $ , we get a word "bcac".

Which least number of newspaper headings $ s_{1} $ will Fangy need to glue them, erase several letters and get word $ s_{2} $ ?

## 输入格式

The input data contain two lines. The first line contain the heading $ s_{1} $ , the second line contains the word $ s_{2} $ . The lines only consist of lowercase Latin letters ( $ 1<=|s_{1}|<=10^{4},1<=|s_{2}|<=10^{6} $ ).

## 输出格式

If it is impossible to get the word $ s_{2} $ in the above-described manner, print "-1" (without the quotes). Otherwise, print the least number of newspaper headings $ s_{1} $ , which Fangy will need to receive the word $ s_{2} $ .

## 样例 #1

### 输入

```
abc
xyz

```

### 输出

```
-1

```

## 样例 #2

### 输入

```
abcd
dabc

```

### 输出

```
2

```

