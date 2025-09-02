---
title: "IITD4 - Divisor Summation Powered"
layout: "post"
diff: 普及/提高-
pid: SP7567
tag: []
---

# IITD4 - Divisor Summation Powered

## 题目描述

EntropyIncreaser 与 因子 $k$ 次方和

****  
$\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 钦定了一个函数：  
$$\large F(n,k)=\sum\limits_{i|n}i^k$$  
她现在给你 $a,b,k$，你需要求出：  
$$\large \sum\limits_{i=a}^bF(i,k)$$  

答案要对 $10^9+7$ 取模。

## 输入格式

第一行一个正整数 $T$，表示数据组数。  
接下来 $T$ 行，每行三个正整数 $a,b,k$，表示一组数据。

## 输出格式

输出 $T$ 行，每行一个整数，表示答案。

## 说明/提示

$\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 想到了这题 $a,b,k\le10^{19260817}$ 的做法。  
但是她非常良心，所以这题的实际数据范围很小：  

$1\le a \le b \le 10^5$  
$1\le k \le 10^5$  
$1\le T \le 20$

