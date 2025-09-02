---
title: "Vanya and Field"
layout: "post"
diff: 提高+/省选-
pid: CF492E
tag: []
---

# Vanya and Field

## 题目描述

> 滑稽树上滑稽果
>
> 滑稽树下你和我

> 滑稽树前做游戏
>
> 滑稽多又多

一天，Vanya 来到了一片滑稽树林中，准备采摘滑稽果。滑稽树林可看作一个 $n \times n$ 的正方形，其中 $m$ 个点上有滑稽果，某些点没有。（注意一个点上可能有多个滑稽果）

Vanya 会沿向量 $(\mathit{dx},\mathit{dy})$ 方向移动。也就是说，如果 Vanya 在 $(x,y)$ 处，她将移动到 $((x + \mathit{dx})\bmod n,(y + \mathit{dy})\bmod n)$ 处。每到一个点，她会拿走该点所有滑稽果。（$\mathit{dx},\mathit{dy}$ 为定值（输入中给出），且 $\gcd(n,\mathit{dx})=\gcd(n,\mathit{dy})=1$）

由于滑稽树林太巨了，当 Vanya 走到一个她走到过的点时，她就会停止走动。

现在 Vanya 想知道她怎么走才能拿到最多的滑稽果。

## 输入格式

第一行四个数：$n,m,dx,dy$。

接下来 $m$ 行，每行两个数 $x,y$ 表示在 $(x,y)$ 处有一个滑稽果。

## 输出格式

两个数 $x,y$，表示 Vanya 从 $(x,y)$ 处出发可拿到最多滑稽果。

如果有多个答案，输出任意一个。

## 说明/提示

对于所有测试数据，$1 \le n \le 10^6$，$1 \le m \le 10^5$，$1 \le dx,dy \le n$，$0 \le x_i,y_i \le n-1$。

Translated By InterestingLSY.

## 样例 #1

### 输入

```
5 5 2 3
0 0
1 2
1 3
2 4
3 1

```

### 输出

```
1 3

```

## 样例 #2

### 输入

```
2 3 1 1
0 0
0 1
1 1

```

### 输出

```
0 0

```

