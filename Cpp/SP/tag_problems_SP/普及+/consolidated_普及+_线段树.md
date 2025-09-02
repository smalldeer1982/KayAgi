---
title: "PRMQUER - Prime queries"
layout: "post"
diff: 普及+/提高
pid: SP19568
tag: ['线段树']
---

# PRMQUER - Prime queries

## 题目描述

&#8195;这是一个简单的题目

&#8195;给定 $N$ 个数，你需要对它们依次进行 $Q$ 次操作。每次操作的格式如下。

 1. 三个整数 $A$ $V$ $l$ 表示给第 $l$ 个数加上 $V$ 。
 
 2. 四个整数 $R$ $a$ $l$ $r$ 表示把区间 $[l,r]$ 的数都变为 $a$ 。
 
 3. 三个整数 $Q$ $l$ $r$ 表示询问区间 $[l,r]$ 里，小于等于 $10^7$ 的素数有多少个。
 
 &#8195;数据保证任何时刻这 $N$ 个数都不会有一个数大于 $10^9$ 。

## 输出格式

&#8195;对于每个操作 $3$ 输出一行整数表示这个操作的答案。

## 说明/提示

- $1\leq N\leq10^5$

- $1\leq Q\leq10^5$
 
- $V\leq10^3$

- $A[i] \leq10^8$

- $a \leq10^7$

- $1\leq l\leq r \leq N$

## 样例 #1

### 输入

```
5 10

1 2 3 4 5

A 3 1

Q 1 3

R 5 2 4

A 1 1

Q 1 1

Q 1 2

Q 1 4

A 3 5

Q 5 5

Q 1 5
```

### 输出

```
2

1

2

4

0

4
```



---

---
title: "ADARAIN - Ada and Rain"
layout: "post"
diff: 普及+/提高
pid: SP28265
tag: ['线段树', '树状数组']
---

# ADARAIN - Ada and Rain

## 题目描述

瓢虫 Ada 正在种植植物。她有一条非常长的种植沟，这条沟长到雨水通常只能落在它的一部分区域。为了不让植物枯萎，Ada 详细记录了每场雨的降水区域，以了解每颗植物得到了多少雨水。然而，雨下得太多，她一个人忙不过来！

起初，你会得到 $N$ 个查询，每个查询是一个区间 $[L,R]$。第 $i$ 个区间表示第 $i$ 场雨覆盖的范围。随后有 $M$ 个查询，每个查询要求知道在第 $i$ 株植物上落了多少场雨。

## 输入格式

第一行包含三个整数 $N,M,W$，分别表示降雨次数、查询次数和种植沟的总长度；

接下来的 $N$ 行，每行包含两个整数 $L,R$，表示第 $i$ 场雨落在区间 $[L,R]$ 上；

接下来的 $M$ 行，每行包含一个整数 $a$，表示查询第 $a$ 株植物上落了多少场雨。

## 输出格式

输出 $M$ 行，每行一个整数，表示对应查询的植物接收到的降雨次数。

## 说明/提示

对于 $100\%$ 的数据，保证：

* $0 < N,M \le 10^5$

* $0 \le W \le 10^6$

* $0 \le L \le R < W$

* $0 \le a < W$

请注意序列起始位置。



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

