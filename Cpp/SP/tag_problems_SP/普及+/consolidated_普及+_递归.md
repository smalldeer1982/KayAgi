---
title: "CORNET - Corporative Network"
layout: "post"
diff: 普及+/提高
pid: SP264
tag: ['并查集', '递归']
---

# CORNET - Corporative Network

## 题目描述

原本有 $n$ 个节点，最初每个节点的父亲都是自己。

现在给你若干操作，共分为两种，操作格式如下：

1. `I x y`（大写字母`I`）

将 $x$ 的父亲变为 $y$，而且令 $x$ 与 $y$ 之间的距离为 $\lvert x-y \rvert \bmod 1000$。

2. `E x` 询问x点到其根节点的距离

数据保证对于所有的 $1$ 操作合法，即保证之前 $y$ 不是 $x$ 的父亲、

## 输入格式

第一行输入一个整数 $T$，表示每个数据点的数据组数。


第一行包含一个正整数 $n$，表示原有的节点个数


`I x y` 或`E x` 分别代表以上的两种操作

对于这些操作，以输入一个`O`（大写字母`O`）为终止。

## 输出格式

一共若干行，表示对于每一组测试数据中的 `E` 操作输出答案。

## 样例 #1

### 输入

```
1
4
E 3
I 3 1
E 3
I 1 2
E 3
I 2 4
E 3
O
```

### 输出

```
0
2
3
5
```



---

---
title: "LITE - Light Switching"
layout: "post"
diff: 普及+/提高
pid: SP7259
tag: ['线段树', '递归', '分块']
---

# LITE - Light Switching

## 题目描述

  
Farmer John tries to keep the cows sharp by letting them play with intellectual toys. One of the larger toys is the lights in the barn. Each of the N (2 <= N <= 100,000) cow stalls conveniently numbered 1..N has a colorful light above it.  
  
At the beginning of the evening, all the lights are off. The cows control the lights with a set of N pushbutton switches that toggle the lights; pushing switch i changes the state of light i from off to on or from on to off.  
  
The cows read and execute a list of M (1 <= M <= 100,000) operations expressed as one of two integers (0 <= operation <= 1).  
  
The first kind of operation (denoted by a 0 command) includes two subsequent integers S\_i and E\_i (1 <= S\_i <= E\_i <= N) that indicate a starting switch and ending switch. They execute the operation by pushing each pushbutton from S\_i through E\_i inclusive exactly once.  
  
The second kind of operation (denoted by a 1 command) asks the cows to count how many lights are on in the range given by two integers S\_i and E\_i (1 <= S\_i <= E\_i <= N) which specify the inclusive range in which the cows should count the number of lights that are on.  
  
Help FJ ensure the cows are getting the correct answer by processing the list and producing the proper counts.

## 输入格式

  
Line 1: Two space-separated integers: N and M  
Lines 2..M+1: Each line represents an operation with three space-separated integers: operation, S\_i, and E\_i

## 输出格式

Lines 1..number of queries: For each output query, print the count as an integer by itself on a single line.

## 样例 #1

### 输入

```
4 5
0 1 2
0 2 4
1 2 3
0 2 4
1 1 4

```

### 输出

```
1
2
```



---

