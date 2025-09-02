---
title: "AFS3 - Amazing Factor Sequence (hard)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: SP33039
tag: ['Stern-Brocot 树']
---

# AFS3 - Amazing Factor Sequence (hard)

## 题目描述

话说在 AFS2 中，NaCly_Fish 好不容易解决了这个问题：  

给定 $n$，求：  
$$ \sum\limits_{i=1}^n(\sigma(i)-i)$$  
其中 $\sigma(n)$ 表示 $n$ 的所有因数之和。  

$\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 过来一看，说：“这题的数据范围太水了，我来把它加强一下。”  

于是她顺手把数据加到了 $10^5$ 组，$n$ 也加到了 $2^{63}$。

然而 NaCly_Fish 根本不会加强版的做法，请你帮帮她吧。

## 输入格式

第一行一个正整数 $T$，表示数据组数。  
接下来 $T$ 行，每行一个正整数 $n$。

## 输出格式

输出 $T$ 行，每行一个整数，表示一组数据的答案。

## 说明/提示

对于 $100\%$ 的数据：  
$1\le T \le 10^5$  
$1\le n \le 2^{63}-1$  

更详细的信息：  
本题有 $6$ 个测试点。  
1、$1\le n \le 10^5$  
2、$1\le T \le 60,1\le n \le10^{15}$  
3、$1\le T \le 25,1\le n \le10^{16}$  
4、$1\le T \le 10,1\le n \le10^{17}$  
5、$1\le T \le 5,1\le n \le 10^{18}$  
6、$1\le T \le 2,1\le n \le 2^{63}-1$

## 样例 #1

### 输入

```
6
1
2
3
10
100
1000000000000000000
```

### 输出

```
0
1
2
32
3249
322467033424113218863487627735401433
```

