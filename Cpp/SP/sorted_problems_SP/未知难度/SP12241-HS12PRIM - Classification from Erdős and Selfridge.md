---
title: "HS12PRIM - Classification from Erdős and Selfridge"
layout: "post"
diff: 难度0
pid: SP12241
tag: []
---

# HS12PRIM - Classification from Erdős and Selfridge

## 题目描述

Erdős Pál 和 John Selfridge 提出了一种对素数的分类方法：对任意素数 $p$，如果 $p-1$ 的最大素因子是 $2$ 或 $3$，那么 $p$ 归为第一类。否则，$p$ 的类别为 $c+1$，其中 $c$ 是 $p-1$ 的所有素因子中最大的一类。特别地，我们将 $p=2$ 定义为第一类。

举个例子，素数 $p=89$ 属于第三类，因为 $p-1=2^3 \cdot 11$，其中 $2$ 属于第一类，而 $11$ 属于第二类（因为 $11-1=2 \cdot 5$，且 $2$ 和 $5$ 都在第一类）。你的任务是计算给定闭区间内各类素数（最多到第十三类）的数量。

## 输入格式

第一行包含整数 $T$，代表测试用例的数量，满足 $T \leq 4$。接下来的 $T$ 行中，每行含有两个整数 $a$ 和 $b$，表示感兴趣的闭区间的起始和终止位置，且满足 $0 < a \leq b \leq 10^6$。

## 输出格式

对于每个测试用例，按照编号输出，并以正确的格式显示该区间内每一类（最多到第十三类）的素数分布。具体格式可参考样例输入和输出。

## 说明/提示

- $T \leq 4$
- $0 < a \leq b \leq 10^6$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
2 100
23 23
0 50000000
```

### 输出

```
Case 1:
There are 10 primes in class 1.
There are 9 primes in class 2.
There are 5 primes in class 3.
There are 1 primes in class 4.
There are 0 primes in class 5.
There are 0 primes in class 6.
There are 0 primes in class 7.
There are 0 primes in class 8.
There are 0 primes in class 9.
There are 0 primes in class 10.
There are 0 primes in class 11.
There are 0 primes in class 12.
There are 0 primes in class 13.

Case 2:
There are 0 primes in class 1.
There are 0 primes in class 2.
There are 1 primes in class 3.
There are 0 primes in class 4.
There are 0 primes in class 5.
There are 0 primes in class 6.
There are 0 primes in class 7.
There are 0 primes in class 8.
There are 0 primes in class 9.
There are 0 primes in class 10.
There are 0 primes in class 11.
There are 0 primes in class 12.
There are 0 primes in class 13.

Case 3:
There are 54 primes in class 1.
There are 14196 primes in class 2.
There are 364182 primes in class 3.
There are 1029984 primes in class 4.
There are 939493 primes in class 5.
There are 458831 primes in class 6.
There are 150902 primes in class 7.
There are 34878 primes in class 8.
There are 7085 primes in class 9.
There are 1310 primes in class 10.
There are 203 primes in class 11.
There are 15 primes in class 12.
There are 1 primes in class 13.
```

