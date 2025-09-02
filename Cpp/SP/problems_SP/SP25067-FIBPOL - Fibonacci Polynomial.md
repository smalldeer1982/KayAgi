---
title: "FIBPOL - Fibonacci Polynomial"
layout: "post"
diff: NOI/NOI+/CTSC
pid: SP25067
tag: []
---

# FIBPOL - Fibonacci Polynomial

## 题目描述

话说上次 NaCly_Fish 好不容易解决了 $\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 给她的 [这个问题](https://www.luogu.org/problem/SP31428)。  

就在这时 $\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 又来找她，说：“之前那个题确实太水了，我加强了一下，你来看看。”  

定义函数： 
$$ A(x)=\sum\limits_{i=1}^\infty F_ix^i$$  
其中 $f$ 为 $\texttt{fibonacci}$ 数列，即：  
$$ F_0=0,F_1=1$$  
$$ F_n=F_{n-1}+F_{n-2}\space(n\ge2)$$  
现在给定一个自然数 $n$，问是否存在**有理数** $x$，使得 $A(x)=n$。  

如果存在，则输出 $1$，否则输出 $0$。

这下 NaCly_Fish 完全懵掉了，请你帮帮她吧。

## 输入格式

第一行一个正整数 $T$，表示数据组数。

## 输出格式

输出 $T$ 行，每行一个数 $0$ 或 $1$。

## 说明/提示

【样例解释】  
以下为函数值表：  
| $x$ | $A(x)$ |
| :----------- | :----------- |
|$0$ | $0$ |
|$\sqrt2-1$  | $1$ |
|$1/2$  |$2$  |
| $(\sqrt{13}-2)/3$ |$3$  |
| $(\sqrt{89}-5)/8$ | $4$ |  
显然对应输出 $1,0,1,0,0$。  

$1\le T \le 10^5$  
$0\le n \le 10^{17}$

## 样例 #1

### 输入

```
5
0
1
2
3
4
```

### 输出

```
1
0
1
0
0
```

