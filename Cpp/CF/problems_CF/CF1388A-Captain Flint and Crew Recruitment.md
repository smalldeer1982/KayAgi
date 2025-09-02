---
title: "Captain Flint and Crew Recruitment"
layout: "post"
diff: 普及-
pid: CF1388A
tag: []
---

# Captain Flint and Crew Recruitment

## 题目描述

如果一个正整数能写成两个不同质数的积，那么我们称它为类质数。

给定一个自然数 $n$，请问是否能将 $n$ 写成四个**互不相同**的正整数的和，并满足这四个正整数中**至少**有三个是类质数。如果能，请给出一种方案。

## 输入格式

**本题包含多组测试数据。**

第一行包含一个整数 $T$ $(1 \le T \le 1000)$，表示数据组数。

接下来 $T$ 行每行一个整数 $n(1 \le n \le 2\times10^5)$。

## 输出格式

对于每组数据，若不能被分解成满足要求的四个正整数，单独输出一行 `NO`。

否则第一行输出 `YES`，第二行输出以单个空格分隔的四个正整数，表示一种可行方案。

Translated by [cmll02](https://www.luogu.com.cn/user/171487)

## 样例 #1

### 输入

```
7
7
23
31
36
44
100
258
```

### 输出

```
NO
NO
YES
14 10 6 1
YES
5 6 10 15
YES
6 7 10 21
YES
2 10 33 55
YES
10 21 221 6
```

