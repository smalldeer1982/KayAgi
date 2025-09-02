---
title: "PIB - Pibonacci"
layout: "post"
diff: 难度0
pid: SP2138
tag: []
---

# PIB - Pibonacci

## 题目描述

EntropyIncreaser 和 $\pi$bonacci 数列  


NaCly_Fish 的数学很烂，经常问 $\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 一些很水的题。 

定义数列 $F$：  
$$\large F_n= \left\{\begin{aligned} 1\space (n\in[0,4)) \\ F_{n-1}+F_{n-\pi}\space(n\in[4,+\infty))\end{aligned}\right.$$  

$\pi$ 就是我们熟知的圆周率。  

现在给定非负整数 $n$，求 $F_n$ 的值。

$\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 一眼就秒了这个问题，但是菜菜的 NaCly_Fish 还不会，请你帮帮她吧。

## 输入格式

本题有多组数据，以 $-1$ 结尾。  
除最后一行外，每行都有一个整数 $n$，表示要求的项。

## 输出格式

对于每个 $n$，输出一个正整数 $x$ 表示答案。  
需要注意的是，$x$ 应分成 $\lceil (\lfloor \lg x\rfloor+1) /50\rceil$ 行输出。  

除每组数据的最后一行外，每一行都输出 $50$ 位。  
最后一行输出剩下的位数即可。  

简单地说，就是每逢 $50$ 位或结尾就输出一行。

## 说明/提示

$0\le n \le 30000$  
数据组数并未给出，但题目声称数据量“很小”。

## 样例 #1

### 输入

```
file:

0
4
11
-1


 
```

### 输出

```
file:

1
2
20
```

