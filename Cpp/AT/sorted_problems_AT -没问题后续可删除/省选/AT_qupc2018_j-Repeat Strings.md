---
title: "Repeat Strings"
layout: "post"
diff: 省选/NOI-
pid: AT_qupc2018_j
tag: ['差分', '根号分治']
---

# Repeat Strings

## 题目描述

给定一个由字符 `a` 和 `b` 组成的字符串 $S$，你可以依次进行若干次以下操作：

- 从字符串 $S$ 中选择一个连续的区间 $[l, r]$。对于该区间内满足 $l \leq k \leq r$ 的每个位置 $k$，如果 $S_k$ 是 `a`，就将其变为 `b`；如果 $S_k$ 是 `b`，就将其变为 `a`。

接下来，有 $Q$ 个字符串 $T_i$，每个也是由 `a` 和 `b` 构成。将每个 $T_i$ 重复 $10^{100}$ 次，截取长度为 $|S| + 1$ 的前缀，得到一个新的字符串 $T'_i$。

你的任务是，对于每一个字符串 $T'_i$，计算将字符串 $S$ 变为 $T'_i$ 最少需要多少次操作。

## 输入格式

输入以如下格式给出：

> $ S $ $ Q $ $ T_1 $ $ T_2 $ ... $ T_Q $

## 输出格式

输出 $Q$ 行。每行包含一个整数，表示将 $S$ 变为 $T'_i$ 所需的最小操作次数。

## 数据范围

- $1 \leq |S| \leq 2 \times 10^5$
- $1 \leq Q \leq 2 \times 10^5$
- $1 \leq |T_i| \leq 2 \times 10^5$
- 所有 $T_i$ 的长度总和不超过 $2 \times 10^5$
- $S$ 和 $T_i$ 仅包含字符 `a` 和 `b` 

### 示例解释

对于每个 $T'_i$ 的具体表现如下：
- $T'_1 = $ `abababababa`
- $T'_2 = $ `bbbbbbbbbbb`
- $T'_3 = $ `babaabbabab`
- $T'_4 = $ `aaaaaaaaaaa`

例如，将字符串 $S$ 变为 $T'_1$ 需要最少 $2$ 次操作。可以按以下步骤实现：`babaabbabab` → `ababbaababa` → `abababababa`。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
babaabbabab
4
abab
b
babaabba
aaaaaaaaaaab
```

### 输出

```
2
4
0
5
```

