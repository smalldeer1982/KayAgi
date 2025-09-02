---
title: "Hongcow Learns the Cyclic Shift"
layout: "post"
diff: 普及-
pid: CF745A
tag: []
---

# Hongcow Learns the Cyclic Shift

## 题目描述

Hongcow正在学习拼写单词！这天，他（他？）的老师给了他一个需要拼写的单词。作为一个好学生，他很快就学会了如何拼写。  
Hongcow决定搞个大新闻。他从刚学会拼写的单词开始，每次把最后一个字符移到单词开头。他称此为一次变换。他可以进行多次变换，例如：单词"abracadabra"可以变成"aabracadabr"、"raabracadab"等等  
现在，他想知道通过变换能变成几个不同的单词，包括初始单词

## 输入格式

一行一个字符串$s(1\leq|s|\leq 50)$，表示初始单词，只由$a-z$组成

## 输出格式

一行表示不同单词个数
感谢 @Fheiwn  提供的翻译。

## 样例 #1

### 输入

```
abcd

```

### 输出

```
4

```

## 样例 #2

### 输入

```
bbb

```

### 输出

```
1

```

## 样例 #3

### 输入

```
yzyz

```

### 输出

```
2

```

