---
title: "Accumulation of Dominoes"
layout: "post"
diff: 入门
pid: CF1725A
tag: ['数学']
---

# Accumulation of Dominoes

## 题目描述

给定一个 $N$ 行 $M$ 列的矩阵，数字从 $1$ 开始，从左到右，从上到下依次在矩阵内排列。

定义 domino 为矩阵内相邻的两个差为 $1$ 的数，求一共有多少个不同的 domino。

两个 domino 不同当且仅当第一个 domino 其中的至少一个数在第二个 domino 没有出现。

## 输入格式

一行两个整数 $N$ 和 $M$ ( $ 1 \leq N, M \leq 10^9 $ ) ，表示矩阵共有 $N$ 行 $M$ 列。

## 输出格式

一个整数，表示一共有多少个不同的 domino。

## 样例 #1

### 输入

```
3 4
```

### 输出

```
9
```

## 样例 #2

### 输入

```
2 1
```

### 输出

```
1
```

