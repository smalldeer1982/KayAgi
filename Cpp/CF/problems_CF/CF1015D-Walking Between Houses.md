---
title: "Walking Between Houses"
layout: "post"
diff: 普及/提高-
pid: CF1015D
tag: []
---

# Walking Between Houses

## 题目描述

在一条路上，$n$ 个房子被排成一排，从从左到右编号为 $1\sim n$。一开始，你站在 $1$ 号房子前。

你需要移动到其他的房子 $k$ 次。每一次移动，你不能原地不动（即移动后与移动前，你必须在不同的房子前面）。如果你从 $x$ 房子移动到 $y$ 房子，那么你走过的距离就是 $\left\vert x-y \right\vert$，这里 $\left\vert a \right\vert$ 表示 $a$ 的绝对值。当然，你可以访问同一个房子多次。（只要不连续就行了）

你的目标是一共走 $s$ 个单位长度。

如果是不可能的，输出 $\texttt{NO}$，否则输出 $\texttt{YES}$，并输出任意一种移动方案，记住你只能走恰好 $k$ 次。

## 输入格式

第一行包括三个整数 $n,k,s$，分别表示房子的数目、你要移动的次数和你一共要走的距离。

保证 $2\leqslant n\leqslant 10^9,1\leqslant k\leqslant 2\times 10^5,1\leqslant s\leqslant 10^{18}$。

## 输出格式

如果不能用恰好 $k$ 次移动走过 $s$ 的距离，输出 $\texttt{NO}$。

否则在第一行输出 $\texttt{YES}$，然后在第二行输出恰好 $k$ 个整数 $h_i\left( 1\leqslant h_i\leqslant n \right) $，$h_i$ 就是你第 $i$ 次移动到的房子。

对于每个 $h_j\left( 1\leqslant j\leqslant k-1 \right) $ 应该满足 $h_j\ne h_{j+1}$，当然如果 $h_1=1$，你就寄了。

## 样例 #1

### 输入

```
10 2 15

```

### 输出

```
YES
10 4 

```

## 样例 #2

### 输入

```
10 9 45

```

### 输出

```
YES
10 1 10 1 2 1 2 1 6 

```

## 样例 #3

### 输入

```
10 9 81

```

### 输出

```
YES
10 1 10 1 10 1 10 1 10 

```

## 样例 #4

### 输入

```
10 9 82

```

### 输出

```
NO

```

