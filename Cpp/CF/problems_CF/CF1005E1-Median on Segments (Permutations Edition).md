---
title: "Median on Segments (Permutations Edition)"
layout: "post"
diff: 普及+/提高
pid: CF1005E1
tag: []
---

# Median on Segments (Permutations Edition)

## 题目描述

#### 题目翻译

给定 $1\sim n$ 的排列 $(1\leq n\leq 2\times 10^5)$，求中位数为 $m$ 的子段个数（子段长度为偶数时，取其第 $\frac k 2$ 项，$k$ 为子段长度）

## 输入格式

第一行两个整数 $n, m$。

第二行长度为 $n$ 的排列。

## 输出格式

输出满足要求的方案数。

## 样例 #1

### 输入

```
5 4
2 4 5 3 1

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 5
1 2 3 4 5

```

### 输出

```
1

```

## 样例 #3

### 输入

```
15 8
1 15 2 14 3 13 4 8 12 5 11 6 10 7 9

```

### 输出

```
48

```

