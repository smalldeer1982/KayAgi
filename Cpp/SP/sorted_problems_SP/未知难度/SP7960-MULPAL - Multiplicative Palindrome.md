---
title: "MULPAL - Multiplicative Palindrome"
layout: "post"
diff: 难度0
pid: SP7960
tag: []
---

# MULPAL - Multiplicative Palindrome

## 题目描述

给定一个由 $N$ 个整数构成的序列。请找到两个不相重叠的回文子串，分别记为 $X$ 和 $Y$。你的任务是挑选出这两个子串，使得它们长度的乘积达到最大。

## 输入格式

第一行输入一个整数 $N$（$1 < N \leq 10^5$），表示整数序列的长度。第二行包含 $N$ 个整数，为该序列的具体元素。

## 输出格式

输出一行，包含一个整数，表示所求的最大乘积。

## 说明/提示

$$1 < N \leq 10^5$$

在寻找 $X$ 和 $Y$ 的过程中，仔细考虑如何保证它们不相重叠是关键。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n2\n1 1\n\n
```

### 输出

```
\n1\n\n\n\nInput:\n4\n1 1 2 2\n\nOutput:\n4\n\n\n\nInput:\n6\n10 11 12 12 11 10\n\nOutput:\n4\n\n\n\nInput:\n6\n0 1 0 1 0 1\n\nOutput:\n9\n\n&nbsp;
```

