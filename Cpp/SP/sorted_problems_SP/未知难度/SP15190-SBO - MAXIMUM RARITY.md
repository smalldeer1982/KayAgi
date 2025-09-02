---
title: "SBO - MAXIMUM RARITY"
layout: "post"
diff: 难度0
pid: SP15190
tag: []
---

# SBO - MAXIMUM RARITY

## 题目描述

给定一个数列，其中每个数的取值范围在 1 到 100000 之间。你的任务是找到一段连续子序列，使其稀有度达到最大值。

我们将稀有度定义为一个序列中仅出现一次的数的数量。例如，考虑以下数列：

`1 1 2 5 1 16 5`

在这个数列中，子序列 `1 1 2 5` 的稀有度为 2，因为只有数字 2 和 5 各出现了一次，而数字 1 出现了两次，所以不算在内。子序列 `1 16 5` 的稀有度则为 3，因为其中的每个数字都只出现了一次。对于完整的数列 `1 1 2 5 1 16 5`，我们可以找到稀有度最大的连续子序列 `2 5 1 16`，其稀有度为 4。

你需要做的是输出这个最大稀有度的数值，而不是子序列本身。

## 输入格式

第一行是一个整数 $N$，表示数列中数字的数量。

$1 \le N \le 500000$。

第二行给出这个数列，其中每个数字都是 1 到 100000 之间的整数。

## 输出格式

输出具有最大稀有度的任意连续子序列的稀有度值。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1:
7\n1 1 2 5 1 16 5\n
```

### 输出

```
1:
4\n\nInput 2:\n3\n1 2 3\nOutput 2:\n3\n\nInput 3:\n10\n2 1 4 1 5 6 7 1 8 2\nOutput 3:\n6\n\nInput 4:\n20\n3 4 14 14 9 7 11 7 15 13 9 9 14 9 13 10 13 9 5 4\nOutput 4:\n7\n\nExplanation:\nInput 2: The maximum rarity is achieved by the sequence itself.\nInput 3: The maximum rarity is achieved by the subsequences 1 4 1 5 6 7 1 8 2, 4 1 5 6 7 1 8 2 and 5 6 7 1 8 2.\n            All the three contiguous subsequences have rarity 6.\nInput 4: The maximum rarity is achieved by the subsequence 11 7 15 13 9 9 14 9 13 10 13 9 5 4.\n            This sequence has 7 numbers which appear only once in it, i.e., 11, 7, 15, 14, 10, 5, 4.
```

