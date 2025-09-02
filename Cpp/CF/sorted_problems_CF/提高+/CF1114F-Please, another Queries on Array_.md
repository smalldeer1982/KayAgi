---
title: "Please, another Queries on Array?"
layout: "post"
diff: 提高+/省选-
pid: CF1114F
tag: ['线段树', '数论']
---

# Please, another Queries on Array?

## 题目描述

你有一个数组 $a_1,a_2,\cdots,a_n$。

现在你需要完成 $q$ 次操作，有以下两种操作形式：

1. `MULTIPLY l r x`，对于所有 $i(l\le i\le r)$，将 $a_i$ 乘上 $x$。

2. `TOTIENT l r`，求出 $\varphi(\prod_{i=l}^ra_i)$，对 $10^9+7$ 取模后的结果。其中 $\varphi$ 表示欧拉函数，$\varphi(n)$ 的定义为 $1\cdots n$ 中与 $n$ 互质的数的个数。


保证数据中至少有一次操作 $2$。

## 输入格式

输入的第一行有两个数 $n,q$，保证 $1\le n\le 4\times10^5,1\le q\le 2\times 10^5$，表示序列的长度以及询问的个数。

第二行是 $n$ 个数 $a_i$ 表示序列，满足 $1\le a_i\le 300$。

## 输出格式

对于每一个操作 $2$ 输出一行，表示答案。

## 说明/提示

在样例中：  
对于第 $1$ 个询问 $\varphi(1)=1$；  
对于第 $2$ 个询问 $\varphi(2)=1$；  
对于第 $3$ 个询问 $\varphi(6)=2$。

## 样例 #1

### 输入

```
4 4
5 9 1 2
TOTIENT 3 3
TOTIENT 3 4
MULTIPLY 4 4 3
TOTIENT 4 4

```

### 输出

```
1
1
2

```

