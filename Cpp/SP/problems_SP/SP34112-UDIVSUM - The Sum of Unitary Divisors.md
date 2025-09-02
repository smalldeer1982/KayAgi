---
title: "UDIVSUM - The Sum of Unitary Divisors"
layout: "post"
diff: NOI/NOI+/CTSC
pid: SP34112
tag: ['数学', '素数判断,质数,筛法']
---

# UDIVSUM - The Sum of Unitary Divisors

## 题目描述

对于一个自然数 $n$，如果 $d\mid n$，且 $\gcd \left(d,\dfrac{n}{d}\right)=1$，则称 $d$ 为 $n$ 的“元因子”。

我们定义函数 $\sigma^*(n)$ 表示 $n$ 的元因子之和。例如 $\sigma^*(1)=1$，$\sigma^*(2)=3$，$\sigma^*(6)=12$。

定义：

$$S(n)=\sum^n_{i=1}\sigma^*(i)$$

现给定 $n$，求 $S(n) \bmod 2^{64}$。

## 输入格式

输入包含多组数据。

输入的第一行包含一个整数 $T$，表示数据的组数。

接下来 $T$ 行，每行包含一个整数 $n$，表示一组询问。

## 输出格式

输出 $T$ 行，每行表示一组询问的解。

## 说明/提示

Input 1：$1\le n$，$T\le 5\times10^4$；

Input 2：$1\le T\le 10^3$，$1\le n \le 5\times10^7$；

Input 3：$1\le T\le 300$，$1\le n \le 5\times10^8$；

Input 4：$1\le T\le 80$，$1\le n \le 5\times10^9$；

Input 5：$1\le T\le 30$，$1\le n \le 5\times10^{10}$；

Input 6：$1\le T\le 10$，$1\le n \le 5\times10^{11}$；

Input 7：$1\le T\le 3$，$1\le n \le 5\times10^{12}$；

Input 8：$1\le T\le 1$，$1\le n \le 5\times10^{13}$。

## 样例 #1

### 输入

```
7
1
2
3
4
5
100
100000
```

### 输出

```
1
4
8
13
19
6889
6842185909
```

