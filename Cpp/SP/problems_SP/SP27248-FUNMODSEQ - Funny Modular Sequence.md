---
title: "FUNMODSEQ - Funny Modular Sequence"
layout: "post"
diff: 难度0
pid: SP27248
tag: []
---

# FUNMODSEQ - Funny Modular Sequence

## 题目描述

我们定义一个有趣的模序列，满足以下条件：$a_1 \times a_2 \equiv 1 \pmod{p}$，$a_2 \times a_3 \equiv 1 \pmod{p}$，依此类推，直到 $a_{n-1} \times a_n \equiv 1 \pmod{p}$。同时，序列中的每个元素 $a_1, a_2, a_3, \ldots, a_n$ 都必须小于 $p$ 且不小于 0。给定第一个元素 $a_1$，求这个长度为 $n$ 的有趣模序列的所有元素之和。如果在任意位置 $a_i$（其中 $i \geq 1$）找不到 $a_{i+1}$ 使得 $a_i \times a_{i+1} \equiv 1 \pmod{p}$，则输出 -1。

**注意**：这里的 $p$ 不一定是质数。

## 输入格式

- 第一行是整数 $T$，表示测试用例的数量。
- 接下来的 $T$ 行中，每行包含三个整数 $a_1, p, n$。

## 输出格式

- 对于每个测试用例，输出结果，即所求和。

## 说明/提示

- $1 \leq T \leq 10^5$
- $1 \leq a_1 \leq 10^5$
- $1 \leq n \leq 10^9$
- $a_1 < p \leq 10^9$

**样例输入**：
```
2
2 3 2
3 7 2
```

**样例输出**：
```
4
8
```

**解释**：

在第一个测试用例中，有趣的模序列为 2, 2，所以它们的和为 4。

第二个测试用例中，序列为 3, 5，所以它们的和为 8。

 **本翻译由 AI 自动生成**

