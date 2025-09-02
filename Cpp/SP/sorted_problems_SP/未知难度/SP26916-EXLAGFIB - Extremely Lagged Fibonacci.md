---
title: "EXLAGFIB - Extremely Lagged Fibonacci"
layout: "post"
diff: 难度0
pid: SP26916
tag: []
---

# EXLAGFIB - Extremely Lagged Fibonacci

## 题目描述

很久很久以前，有一个二阶递推数列，但是因为延迟太大（？）这个数列变成了

$$a_n = \begin{cases} 0 & (0 \le n < k - 1) \\ 1 & (n = k - 1)\\ b \times a_{n-j} + c \times a_{n-k} & (n \ge k) \end{cases}$$
出于某些原因，你想算出这个数列的第 $n$ 项对 $1000000037$（不是质数）取模的值。

## 输入格式

第一行一个正整数 $T$，表示数据组数。  
接下来 $T$ 行，每行五个正整数 $n,j,k,b,c$ 表示一组数据。

## 输出格式

输出 $T$ 行，每行一个整数对应一组数据的答案。

## 说明/提示

对于 $100\%$ 的数据：  
- $1\le T \le 100$
- $0\le n \le 10^9$
- $\color{red} 10^5 \le k \le 10^8$，$1\le j < k$  
- $1\le b,c \le 10^9$

## 样例 #1

### 输入

```
2
1000000 1 100000 1 1
1000000000 1 100000000 1 1
```

### 输出

```
372786243
994974348
```

