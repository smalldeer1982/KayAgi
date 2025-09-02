---
title: "Working out"
layout: "post"
diff: 普及+/提高
pid: CF429B
tag: []
---

# Working out

## 题目描述

夏天要到了，$\texttt{dxbt}$ 和 $\texttt{songke}$ 决定去健身。它们要去的健身房可以被看做一个 $n$ 行 $m$ 列的矩阵。定义 $a_{i,j}$ 为在健身房第 $i$ 行第 $j$ 列运动后消耗的卡路里。

$\texttt{dxbt}$ 从 $\left(1,1\right)$ 出发，要去 $\left(n,m\right)$。并且，他只能从 $\left(i,j\right)$ 走到 $\left(i+1,j\right)$ 或 $\left(i,j+1\right)$；$\texttt{songke}$ 从 $\left(n,1\right)$ 出发，要去 $\left(1,m\right)$。并且，他只能从 $\left(i,j\right)$ 走到 $\left(i-1,j\right)$ 或 $\left(i,j+1\right)$。

由于 $\texttt{dxbt}$ 和 $\texttt{songke}$ 要聚在一起发张自拍，他们必须在健身房的某行某列相遇。由于他们没有好好健身，所以在自拍地点的卡路里消耗不计入总卡路里消耗值。

如果 $\texttt{dxbt}$ 和 $\texttt{songke}$ 中任何一个人完成了健身，则健身结束。你的任务是求出 $\texttt{dxbt}$ 和 $\texttt{songke}$ 可以消耗的最大总卡路里值。

另外，由于他们的健身速度不一定相同，所以可以走过的路线长度也不一定相同。

## 输入格式

第一行包含两个整数 $n,m(3\le n,m\le1000)$，代表健身房的行数、列数。

接下来 $n$ 行每行 $m$ 个整数，表示 $a_{i,j}$。

## 输出格式

一行一个整数，表示他们可能消耗的总卡路里的最大值。

## 说明/提示

对于样例 $1$，$\texttt{dxbt}$ 可以选择：

$$
\left(1,1\right)\rightarrow\left(1,2\right)\rightarrow\left(2,2\right)\rightarrow\left(3,2\right)\rightarrow\left(3,3\right)
$$

$\texttt{songke}$ 可以选择：

$$
\left(3,1\right)\rightarrow\left(2,1\right)\rightarrow\left(2,2\right)\rightarrow\left(2,3\right)\rightarrow\left(1,3\right)
$$

## 样例 #1

### 输入

```
3 3
100 100 100
100 1 100
100 100 100

```

### 输出

```
800
```

