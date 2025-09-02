---
title: "FACTMULP - Product of factorials (hard)"
layout: "post"
diff: 难度0
pid: SP18667
tag: []
---

# FACTMULP - Product of factorials (hard)

## 题目描述

对于正整数 $n$，定义函数 $F(n)$ 为 $1!\times 2!\times \cdots \times n!$，即所有不大于 $n$ 的正整数阶乘的积。

给你一个质数 $p$，和一个正整数 $e$，你需要求出最大的整数 $k$，使得 $p^k$ 能整除 $F(p^e)$。

由于答案可能很大，需要对 $10^9+7$ 取模后输出。

## 输入格式

第一行一个正整数 $T$，表示数据组数。

## 输出格式

输出 $T$ 行，对应每组数据的答案。

## 说明/提示

对于 $100\%$ 的数据，$1\le T \le 10^5$，$1\le p,e \le 10^{18}$，保证 $p$ 为质数。

## 样例 #1

### 输入

```
1
2 2
```

### 输出

```
5
```

