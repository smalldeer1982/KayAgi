---
title: "LEXBRAC - Bracket Sequence"
layout: "post"
diff: 难度0
pid: SP2317
tag: []
---

# LEXBRAC - Bracket Sequence

## 题目描述

## 题目背景

正确括号序列 (CBS) 是可以通过以下规则获得的序列：

1. 空字符串是 CBS。
2. 如果 $A$ 是 CBS，那么 $B = (A)$ 也是 CBS。
3. 如果 $A$ 是 CBS，那么 $B = [A]$ 也是 CBS。
4. 如果 $A$ 和 $B$ 都是 CBS，那么 $C = AB$ 也是 CBS。

CBS 的长度是指其中括号的数量，这个数量总是偶数。

假设 `(` < `)` < `[` < `]`。

CBS $a_1 a_2 \cdots a_n$ 在字典序上小于 CBS $b_1 b_2 \cdots b_n$ 当且仅当存在一个整数 $i, i \le n$，使得对于每个 $j, 1 \le j < i$ 有 $a_j = b_j$ 且 $a_i < b_i$。

## 输入格式

输入包含两个整数 $n$（$2 \le n \le 250$）和 $k$（$1 \le k \le 10^{120}$）。

## 输出格式

输出长度为 $n$ 的第 $k$ 个按字典序排列的 CBS。

## 说明/提示

- $2 \le n \le 250$
- $1 \le k \le 10^{120}$

## 样例 #1

### 输入

```
4
3
```

### 输出

```
()[]
```

