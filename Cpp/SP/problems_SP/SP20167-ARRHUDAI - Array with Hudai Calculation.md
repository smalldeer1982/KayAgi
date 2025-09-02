---
title: "ARRHUDAI - Array with Hudai Calculation"
layout: "post"
diff: 难度0
pid: SP20167
tag: []
---

# ARRHUDAI - Array with Hudai Calculation

## 题目描述

数组的胡代计算

给定一个包含 $N$ 个整数的数组 $A[1…N]$，以及两个整数 $P$ 和 $K$。你的任务是找到一个值 $X$（$X$ 必须是数组 $A$ 中的某个值），使得以下表达式的值达到最大：

$$
\text{ABS} \left( \sum_{i=1}^{N} A[i] \times (P \bmod A[i]) - K \right)
$$

在这里，$\text{ABS}$ 表示绝对值操作。例如：$\text{ABS}(-1)$ 的结果是 $1$，$\text{ABS}(1)$ 的结果也是 $1$。

$\text{MOD}$ 指取模运算。即，$W \bmod Y$ 表示 $W$ 除以 $Y$ 后的余数。虽然我们不执着于选择哪个具体的 $X$，但我们想要的是能让这个表达式最大化的那个结果。聪明的你能帮我们找到这个最大值吗？

## 输入格式

第一行为一个整数 $T$，表示测试用例的数量。

对于每个测试用例：
- 第一行包含三个整数：$N$、$P$ 和 $K$。
- 第二行有 $N$ 个整数，分别是 $A[1], A[2], \ldots, A[N]$。

## 输出格式

对于每个测试用例，输出表达式的最大值。

## 说明/提示

- $1 \leq T \leq 10$
- $1 \leq N \leq 10^5$
- $1 \leq P, K \leq 10^9$
- $1 \leq A[i] \leq 10^9$

通过对这些条件的理解，你需要设计一个高效的算法来解决这个问题。

 **本翻译由 AI 自动生成**

