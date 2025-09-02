---
title: "String Journey"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1063F
tag: []
---

# String Journey

## 题目描述

对于一个字符串数组 $t_1, \ldots, t_k$，若对于每一个 $t_i$ 都是 $t_{i-1}$ 的真子串的话，即 $t_i$ 是 $t_{i - 1}$ 的子串且 $t_i \ne t_{i-1}$，则称为有序串组，列如 $\{\mathtt{ab}, \mathtt{b}\}$ 是，$\{\mathtt{ab}, \mathtt{c}\}$ 和 $\{ \mathtt{a}, \mathtt{a}\}$ 不是。

给定字符串 $s$，构造有序串组 $t_1,\ldots,t_k$ 和任意字符串数组 $u_1,\ldots,u_{k+1}$，使 $s=u_1+t_1+u_2+t_2 + \cdots +t_k+u_{k+1}$，其中 $+$ 为字符串的拼接

现在给定一个字符串，求满足条件的最大 $k$。

## 输入格式

一个字符串 $s$

## 输出格式

一个整数 $k$

## 样例 #1

### 输入

```
7
abcdbcc

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
bbcb

```

### 输出

```
2

```

