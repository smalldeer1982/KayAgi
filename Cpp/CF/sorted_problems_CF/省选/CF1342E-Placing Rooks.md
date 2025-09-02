---
title: "Placing Rooks"
layout: "post"
diff: 省选/NOI-
pid: CF1342E
tag: []
---

# Placing Rooks

## 题目描述

$\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 是国际象棋大师。

有这样一个问题：

在 $n \times n$ 的国际象棋棋盘上放 $n$ 个车，要求满足两个条件：

- 所有的空格子都能被至少一个车攻击到。
- **恰好**有 $k$ 对车可以互相攻击到。

答案对 $998244353$ 取模。

$\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 一眼就会了；但 NaCly\_Fish 太菜，并不会做，请你帮帮她吧。

## 输入格式

输入一行两个整数 $n,k$。

## 输出格式

输出一行一个整数，表示答案。

## 说明/提示

$1\le n \le 2\times 10^5$，$0 \le k \le  \frac{n(n-1)}{2}$。

## 样例 #1

### 输入

```
3 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 0
```

### 输出

```
24
```

## 样例 #4

### 输入

```
1337 42
```

### 输出

```
807905441
```

