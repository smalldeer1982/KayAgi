---
title: "FIBONOMIAL - Fibonacci Polynomial"
layout: "post"
diff: 省选/NOI-
pid: SP31428
tag: []
---

# FIBONOMIAL - Fibonacci Polynomial

## 题目描述

$\mathsf E\color{red}\mathsf{ntropyIncreaser}$ 喜欢数学，所以她的数学也非常好。  

有一天，她想到了这样一个问题：  

定义函数   
$$\large D(n,x)=\sum\limits_{i=1}^nf_ix^i$$  
其中 $f_i$ 为 $\texttt{fibonacci}$ 数列，即：  
$$\large f_1=f_2=1$$  
$$\large f_n=f_{n-1}+f_{n-2}\space (n\ge3)$$  
给定 $n,x$ ，求出 $D(n,x)$ 的值。  
由于答案会非常大，所以要对 $10^9+7$ 取模。  

然而 $\mathsf E\color{red}\mathsf{ntropyIncreaser}$ 觉得这个问题实在太sb了，随手造了几组数据就丢到了OJ上。  

你能求出答案吗？

## 输入格式

第一行一个正整数 $T$，表示数据组数。

## 输出格式

输出 $T$ 行，每行一个整数，表示 $D(n,x) \text{ mod }10^9+7$ 的值。

## 说明/提示

$1\le T \le 1000$  
$0\le n,x \le 10^{15}$

## 样例 #1

### 输入

```
1 
7 11
```

### 输出

```
268357683
```

