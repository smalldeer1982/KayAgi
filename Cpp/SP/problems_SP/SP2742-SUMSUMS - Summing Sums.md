---
title: "SUMSUMS - Summing Sums"
layout: "post"
diff: 省选/NOI-
pid: SP2742
tag: []
---

# SUMSUMS - Summing Sums

## 题目描述

EntropyIncreaser 与 $T$ 次求和  
****   

$\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 在BJOI2018上，秒切了一道链上二次求和，并吊打标算，觉得这是一道大水题。  

然而 NaCly_Fish 表示很不服，她找了一道自己好久都没想出来的“ $T$次求和 ”给 $\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 看。  

给定一个长度为  $n$ 的序列 $a$，定义一次操作为： 将序列中的每个数变成除它外所有数的和。  

求进行 $T$ 次操作之后的序列，答案对 $98765431$ 取模。

$\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 瞟了一眼，说：“这题不是更水嘛。” 于是只用了 $\text{1ms}$ 写出AC代码，便大步走开。  

机房里只剩下一脸懵逼的 NaCly_Fish，还不知道这题是怎么做的。

## 输入格式

第一行两个正整数 $n,T$  
接下来 $n$ 行，每行一个整数 $a_i$，表示序列 $a$ 中的第 $i$ 个数。

## 输出格式

输出 $n$ 行，每行一个整数，表示经过 $T$ 次操作后的序列，要对 $98765431$ 取模。

## 说明/提示

【样例解释】  

$1$ ~ $4$ 次操作后的序列分别是：  
$$4,5,1$$  
$$6,5,9$$  
$$14,15,11$$  
$$26,25,29$$  

$1\le n \le 50000$  
$0\le a_i \le9\times10^8$  
$1\le T\le 1414213562$

## 样例 #1

### 输入

```
3 4
1
0
4
```

### 输出

```
26
25
29
```

