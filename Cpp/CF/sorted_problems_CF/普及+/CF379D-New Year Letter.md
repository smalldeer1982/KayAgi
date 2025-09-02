---
title: "New Year Letter"
layout: "post"
diff: 普及+/提高
pid: CF379D
tag: []
---

# New Year Letter

## 题目描述

Many countries have such a New Year or Christmas tradition as writing a letter to Santa including a wish list for presents. Vasya is an ordinary programmer boy. Like all ordinary boys, he is going to write the letter to Santa on the New Year Eve (we Russians actually expect Santa for the New Year, not for Christmas).

Vasya has come up with an algorithm he will follow while writing a letter. First he chooses two strings, $ s_{1} $ anf $ s_{2} $ , consisting of uppercase English letters. Then the boy makes string $ s_{k} $ , using a recurrent equation $ s_{n}=s_{n-2}+s_{n-1} $ , operation '+' means a concatenation (that is, the sequential record) of strings in the given order. Then Vasya writes down string $ s_{k} $ on a piece of paper, puts it in the envelope and sends in to Santa.

Vasya is absolutely sure that Santa will bring him the best present if the resulting string $ s_{k} $ has exactly $ x $ occurrences of substring AC (the short-cut reminds him оf accepted problems). Besides, Vasya decided that string $ s_{1} $ should have length $ n $ , and string $ s_{2} $ should have length $ m $ . Vasya hasn't decided anything else.

At the moment Vasya's got urgent New Year business, so he asks you to choose two strings for him, $ s_{1} $ and $ s_{2} $ in the required manner. Help Vasya.

## 输入格式

The first line contains four integers $ k,x,n,m $ $ (3<=k<=50; 0<=x<=10^{9}; 1<=n,m<=100) $ .

## 输出格式

In the first line print string $ s_{1} $ , consisting of $ n $ uppercase English letters. In the second line print string $ s_{2} $ , consisting of $ m $ uppercase English letters. If there are multiple valid strings, print any of them.

If the required pair of strings doesn't exist, print "Happy new year!" without the quotes.

## 样例 #1

### 输入

```
3 2 2 2

```

### 输出

```
AC
AC

```

## 样例 #2

### 输入

```
3 3 2 2

```

### 输出

```
Happy new year!

```

## 样例 #3

### 输入

```
3 0 2 2

```

### 输出

```
AA
AA

```

## 样例 #4

### 输入

```
4 3 2 1

```

### 输出

```
Happy new year!

```

## 样例 #5

### 输入

```
4 2 2 1

```

### 输出

```
Happy new year!

```

