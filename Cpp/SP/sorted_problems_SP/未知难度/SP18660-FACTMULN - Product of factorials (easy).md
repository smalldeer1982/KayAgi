---
title: "FACTMULN - Product of factorials (easy)"
layout: "post"
diff: 难度0
pid: SP18660
tag: []
---

# FACTMULN - Product of factorials (easy)

## 题目描述

给定一个正整数 $n$，我们定义 $F(n) = 1! \times 2! \times 3! \times \ldots \times n!$，这表示从 1 到 $n$ 所有整数阶乘的乘积。集合 $G(n)$ 包含所有满足 $n$ 可以整除 $F(i)$ 的整数 $i$，其中 $i$ 的范围是从 1 到 $n$。显而易见，$n$ 自己一定在 $G(n)$ 中，因此 $G(n)$ 不是空集。

## 输入格式

第一行为一个整数 $T$，表示测试用例的数量。接下来的 $T$ 行中，每行包含一个整数 $n$。

## 输出格式

对于每个测试用例，输出集合 $G(n)$ 中的最小值。

## 说明/提示

- $1 \leq T \leq 10^5$
- $1 \leq n \leq 10^5$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
4
5
6
```

### 输出

```
3
5
3
```

