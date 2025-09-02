---
title: "Most socially-distanced subsequence"
layout: "post"
diff: 普及/提高-
pid: CF1364B
tag: []
---

# Most socially-distanced subsequence

## 题目描述

给出一个长度为 $n$ 的排列 $P$，你需要找到它的一个子序列 $P_{s_1},P_{s_2},\dots,P_{s_k}$ 满足：
- $|P_{s_1}-P_{s_2}|+|P_{s_2}-P_{s_3}|+\dots+|P_{s_{k-1}}-P_{s_k}|$ 最大。
- 在上式最大的前提下 $k$ 最小。

求这个子序列的最长长度。

## 输入格式

**本题有多组数据**

第一行一个整数 $T$，表示数据组数。

每组数据第一行一个整数 $n$。

之后一行 $n$ 个整数，表示给出的排列 $P$。

保证 $1\le T\le2\times10^4$，$2\le n\le10^5$，$1\le P_i\le n$，$\sum n\le10^5$。

## 输出格式

每组数据第一行输出你选择的 $k$，之后一行输出 $k$ 个整数，表示你选择的子序列。

## 样例 #1

### 输入

```
2
3
3 2 1
4
1 3 4 2
```

### 输出

```
2
3 1 
3
1 4 2
```

