---
title: "OTOY1 - One Theorem, One Year"
layout: "post"
diff: 难度0
pid: SP10465
tag: []
---

# OTOY1 - One Theorem, One Year

## 题目描述

一个数如果在质因数分解中正好有 $K$ 个质数（这些质数可以重复），我们称这个数为 **Almost-K-Prime**。例如，$12 = 2 \times 2 \times 3$ 是一个 Almost-3-Prime，而 $32 = 2 \times 2 \times 2 \times 2 \times 2$ 是一个 Almost-5-Prime。如果一个数 $X$ 满足以下条件，我们称其为 **Almost-K-First-P-Prime**：

1. $X$ 是一个 Almost-K-Prime
2. $X$ 的所有质因数都是从第一个质数开始的前 $P$ 个质数。

举个例子，当 $K=3$ 且 $P=2$ 时，$18 = 2 \times 3 \times 3$ 和 $12 = 2 \times 2 \times 3$ 满足条件。而 $630 = 2 \times 3 \times 3 \times 5 \times 7$ 则是 Almost-5-First-4-Prime 的一个例子。

给定 $K$ 和 $P$，你需要计算满足条件的所有 $X$ 的 $\Phi(X)$ 之和，其中 $X$ 是 Almost-K-First-P-Prime。

数学中，$\Phi(X)$ 表示小于 $X$ 且与 $X$ 互质的数的数量。两个数互质是指它们的最大公约数（GCD）为 1。例如，$\Phi(12) = 4$，因为 1, 5, 7 和 11 都与 12 互质。

## 输入格式

输入的第一行为整数 $T$，表示测试用例的数量。

每个测试用例包含一行，由两个整数 $K (1 \le K \le 100)$ 和 $P (1 \le P \le 100)$ 组成。

## 输出格式

对于每个测试用例，输出结果时要包括测试用例的编号，并给出结果对 $1000000007$ 取模的值。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3 2
5 4
99 45
```

### 输出

```
Case 1: 10
Case 2: 816
Case 3: 49939643
```

