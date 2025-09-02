---
title: "INS17M - Fibonacci and Easy GCD"
layout: "post"
diff: 省选/NOI-
pid: SP31893
tag: ['数论', '莫比乌斯反演', '斐波那契数列']
---

# INS17M - Fibonacci and Easy GCD

## 题目描述

## 计算：
$$S=\sum\limits_{1\le i<j\le n}\gcd(Fib(A_i^k),Fib(A_j^k)) $$  
对1000000007取模的结果   
其中$\gcd$为最大公约数，$Fib$为斐波那契数列，递推式为：
$$Fib(i)=\begin{cases}0&i=0\\1&i=1\\Fib(i-1)+Fib(i-2)&i>1\end{cases}$$

## 输入格式

第一行两个整数，$n$和$k$  
第二行$n$个整数，表示$A_i$

## 输出格式

一行一个整数，结果$S$

## 样例 #1

### 输入

```
5 1
2 4 2 1 4
```

### 输出

```
12
```

