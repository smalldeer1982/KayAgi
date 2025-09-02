---
title: "[ABC245D] Polynomial division"
layout: "post"
diff: 普及/提高-
pid: AT_abc245_d
tag: []
---

# [ABC245D] Polynomial division

## 题目描述

现在有 $N$ 次多项式 $A（x）=A_Nx^N+A_{N-1}x^{N-1}+\cdots\ +A_1x+A_0$ 和 $M$ 次多项式 $B(x)=B_Mx^M+B_{M-1}x^{M-1}+\cdots\ +B_1x+B_0$。

其中，$A(x)、B(x)$ 中的每个系数都是绝对值小于等于 $100$ 的整数，并且最高的下一个系数不是 $0$。

定义它们的积为 $C(x)=A(x)B(x)=C_{N+M}x^{N+M}+C_{N+M-1}x^{N+M-1}+\cdots\ +C_1x+C_0$。

已知 $A_0,A_1,\ldots,\ A_N$ 和 $C_0,C_1,\ldots,\ C_{N+M}$，请求出 $B_0,B_1,\ldots,\ B_M$。

输入保证只有一种 $B_0,B_1,\ldots,\ B_M$。

## 输入格式

第一行输入 $N,M$；

第二行输入 $A_0,A_1,\ldots,A_{N-1}$；

第三行输入 $C_0,C_1,\ldots,C_{N+M}$。

## 输出格式

输出 $M+1$ 个整数 $B_0,B_1,\ldots,\ B_M$。

## 说明/提示

- $ 1\leq N<100 $

- $ 1\leq M<100 $

- $ |A_i|\leq100 $

- $ |C_i|\leq10^6 $

- $ A_N\neq0 $

- $ C_{N+M}\neq0 $

- 满足条件的 $B_0,B_1,\ldots,\ B_M$ 只有一个

## 样例 #1

### 输入

```
1 2
2 1
12 14 8 2
```

### 输出

```
6 4 2
```

## 样例 #2

### 输入

```
1 1
100 1
10000 0 -1
```

### 输出

```
100 -1
```

