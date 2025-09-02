---
title: "[ABC262Ex] Max Limited Sequence"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_abc262_h
tag: ['动态规划 DP', '容斥原理']
---

# [ABC262Ex] Max Limited Sequence

## 题目描述

### 题目大意
求满足以下条件的长度为 $N$ 的序列 $A=(A_1,A_2,\cdots A_N)$ 有多少种：
+ $\forall i \in[1,N],0\leq A_i\leq M$
+ $\forall i \in[1,Q],\max \limits_{L_i\leq j\leq R_i}A_j=X_i$

## 输入格式

第一行输入 $3$ 个正整数 $N,M,Q$ 

后面 $Q$ 行每行 $3$ 个正整数表示 $L_i,R_i,X_i$

$1\leq N\leq 2\times 10^5$

$1\leq M<998244353$

$1\leq Q\leq 2\times 10^5$

$\forall i \in [1,Q],1\leq L_i\leq R_i\leq N,1\leq X_i\leq M$

## 输出格式

输出满足条件的序列数，对 $998244353$ 取模。

## 样例 #1

### 输入

```
3 3 2
1 2 2
2 3 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
1 1 1
1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6 40000000 3
1 4 30000000
2 6 20000000
3 5 10000000
```

### 输出

```
135282163
```

