---
title: "Natasha, Sasha and the Prefix Sums"
layout: "post"
diff: 省选/NOI-
pid: CF1204E
tag: []
---

# Natasha, Sasha and the Prefix Sums

## 题目描述

NaCly_Fish 最喜欢的数字是 $n$ 和 $1$；$\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 最喜欢 $m$ 和 $-1$。

有一天，她们在一起写出了一个长度为 $n+m$，有 $n$ 个 $1$ 和 $m$ 个 $-1$ 的序列 $a$，定义其最大前缀和为： 
$$\large \max\{ 0,\max\limits_{1\le i\le n+m}\sum\limits_{j=1}^ia_j \}$$
换句话说，就是对于 $a$ 的前缀和的所有项和 $0$ 取 $\max$ 的值。

NaCly_Fish 想知道，对于全部可能的序列，它们的 最大前缀和 之和是多少。  
为了防止答案过大，要对 ${998244\textcolor{red}853}$ (是个质数) 取模。

$\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 只用 1s 就想到了做法，但是 NaCly_Fish 还不会，你能帮帮她吗？

## 输入格式

一行两个非负整数 $n,m$

## 输出格式

一行一个整数表示答案。

## 说明/提示

【样例 $3$ 解释】  
可能的序列有 $6$ 种：  
$1,1,-1,-1$  
$1,-1,1,-1$  
$1,-1,-1,1$  
$-1,1,1,-1$  
$-1,1,-1,1$  
$-1,-1,1,1$  
它们的最大前缀和分别为 $2,1,1,1,0,0$，加起来答案为 $5$。

$0\le n,m \le 2000$

## 样例 #1

### 输入

```
0 2

```

### 输出

```
0

```

## 样例 #2

### 输入

```
2 0

```

### 输出

```
2

```

## 样例 #3

### 输入

```
2 2

```

### 输出

```
5

```

## 样例 #4

### 输入

```
2000 2000

```

### 输出

```
674532367

```

