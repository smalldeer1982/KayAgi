---
title: "Diverse Garland"
layout: "post"
diff: 普及/提高-
pid: CF1108D
tag: []
---

# Diverse Garland

## 题目描述

给一串字符，只有`R`和`G`和`B`。问如果要让相邻$2$个字符都不同，最少要改几个?

## 输入格式

第一行：字符串的长度$n$。$(1\leq n\leq2*10^5)$

第二行：$n$个字符，是给的字符串。

## 输出格式

第一行：最少要改动几个字符。

第二行：改后的字符串。（注：有$spj$）

## 样例 #1

### 输入

```
9
RBGRRBRGG

```

### 输出

```
2
RBGRGBRGR

```

## 样例 #2

### 输入

```
8
BBBGBRRR

```

### 输出

```
2
BRBGBRGR

```

## 样例 #3

### 输入

```
13
BBRRRRGGGGGRR

```

### 输出

```
6
BGRBRBGBGBGRG

```

