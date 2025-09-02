---
title: "Maximum Sum on Even Positions"
layout: "post"
diff: 普及/提高-
pid: CF1373D
tag: []
---

# Maximum Sum on Even Positions

## 题目描述

给定一个包含 $n$ 个元素的序列（下标从 $0$ 到 $n-1$），你可以选择一个连续区间进行翻转，使得翻转过后的序列偶数项的总和（即 $a_0,a_2,\ldots,a_{2k}$ 的和，其中 $k=\lfloor \dfrac{n-1}{2} \rfloor$）最大。

## 输入格式

**本题有多组数据**

第一行一个整数 $t$ $(1 \leq t \leq 2 \times 10^4)$，表示数据的组数。

每组数据包含两行，第一行一个整数 $n$ $(1 \leq n \leq 2 \times 10^5)$，表示序列的长度。下一行 $n$ 个整数，表示序列 $a_i$。

保证 $\sum n \leq 2 \times 10^5$。

## 输出格式

共 $t$ 行，每行一个数，表示该组数据的答案。

## 样例 #1

### 输入

```
4
8
1 7 3 4 7 6 2 9
5
1 2 1 2 1
10
7 8 4 5 7 6 8 9 7 3
4
3 1 2 1
```

### 输出

```
26
5
37
5
```

