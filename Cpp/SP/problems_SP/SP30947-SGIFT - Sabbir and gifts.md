---
title: "SGIFT - Sabbir and gifts"
layout: "post"
diff: 难度0
pid: SP30947
tag: []
---

# SGIFT - Sabbir and gifts

## 题目描述

Sabbir 是个小男孩，他和母亲一起去了一家礼品店。店里有 $n$ 种不同的礼品，每一种礼品都对 Sabbir 很有吸引力。他想要购买所有价格在区间 $[a, b]$ 内的礼品。现在你需要帮助 Sabbir 的妈妈计算出这个价格区间内所有礼品的总价格。

## 输入格式

第一行输入一个整数 $n$，表示礼品的种类数量。  
第二行输入 $n$ 个整数 $p_1, p_2, p_3, \ldots, p_n$，分别表示每种礼品的价格。  
第三行输入一个整数 $Q$，表示要处理的查询次数。  
接下来的 $Q$ 行，每行包含两个整数 $a$ 和 $b$，表示需要查询的价格区间。

## 输出格式

对于每个查询，输出一行，表示该查询的价格区间内所有礼品的总和。

## 数据范围

- $1 \leq n \leq 10^5$
- $1 \leq p_i \leq 10^9$
- $1 \leq Q \leq 10^5$
- $1 \leq a, b \leq 10^9$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
7\n1 3 2 1 5 2 2\n4\n1 2\n1 5\n3 5\n4 5
```

### 输出

```
8\n16\n8\n5\n\nNOTE: for first query sabbir will buy all the gifts of prices 1 , 2 , 1 , 2, 2 . so, sum is 8\nfor second query sabbir will buy all the gifts . so the sum is 16\n&nbsp;
```

