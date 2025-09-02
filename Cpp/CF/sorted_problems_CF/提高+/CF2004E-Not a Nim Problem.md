---
title: "Not a Nim Problem"
layout: "post"
diff: 提高+/省选-
pid: CF2004E
tag: ['博弈论']
---

# Not a Nim Problem

## 题目描述

有 $n$ 堆石子，每堆有 $a_i$ 个。

Alice 和 Bob 轮流取石子。Alice 先手。每个人在当前回合下可以随意选择一堆石子取任意数量个，要求：

- 设选择的这堆石子有 $x$，取走 $y$ 个，则必须使 $x$ 与 $y$ 互质。

第一个不能操作的人输掉这场游戏。在两人都使用最优策略的前提下，求获胜者。

## 输入格式

第一行一个正整数 $t(1 \leq t \leq 10^4)$ 表示测试数据组数。

每一组测试数据中： 

- 第一行输入一个正整数 $n(1 \leq n \leq 3 \times 10^5)$。
- 第二行输入 $n$ 个正整数 $a_i(1 \leq a_i \leq 10^7)$。

保证单测试点内所有测试数据下 $n$ 的总和不超过 $3 \times 10^5$。

## 输出格式

对于每一组测试数据，输出一行一个字符串 $\texttt{Alice}$ 或 $\texttt{Bob}$ 表示获胜者。

$\scriptsize \text{Written by McIron233.}$

## 样例 #1

### 输入

```
3
3
3 2 9
4
3 3 6 1
5
1 2 3 4 5
```

### 输出

```
Bob
Alice
Bob
```

