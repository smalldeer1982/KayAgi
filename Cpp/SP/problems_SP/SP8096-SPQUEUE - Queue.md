---
title: "SPQUEUE - Queue"
layout: "post"
diff: 难度0
pid: SP8096
tag: []
---

# SPQUEUE - Queue

## 题目描述

在一些特别的场合，Nadia 的公司会为所有员工提供特殊的午餐。食品供应开始之前，所有员工都需要在餐台前排成一列。公司制定了一条排队规则：如果 Abul 是 Babul 的主管，并且 Abul 站在队列的第 $k$ 个位置，那么 Babul 不能站在第 $1$ 到第 $k-1$ 个位置。公司共有 $N$ 名员工，每个人都有一位主管，只有一个例外，没有主管。

你的任务是计算可以有多少种不同的方式来安排这个队列。请放心，至少存在一种排队方式符合要求。

## 输入格式

第一行是测试用例的数量。

对于每个测试用例：

- 第一行包含两个整数 $M$ 和 $N$，其中 $M$ 用于取模运算。
- 接下来的 $N-1$ 行，每行包含一个整数，表示第 $i$ 个员工的主管。

## 输出格式

对于每个测试用例，输出这个问题的排队方式总数对 $M$ 取模后的结果。

## 说明/提示

- $1 \leq N \leq 10^5$
- $1 \leq M \leq 10^9$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n1\n2 2\n1\n
```

### 输出

```
\n\n1\n\nConstraints:\n- Number of test cases &lt;= 10 for small data, N &lt;= 100000\n- Number of test cases = 1 for large data, N &lt;= 500000\n- 1 &lt;= M &lt;= 1000000000\n- Time Limit for all tests: 2s
```

