---
title: "[ABC355D] Intersecting Intervals"
layout: "post"
diff: 普及/提高-
pid: AT_abc355_d
tag: ['二分']
---

# [ABC355D] Intersecting Intervals

## 题目描述

### 问题陈述

给你 $N(2 \leq N \leq 5 \times 10^5)$ 个实数区间。第 $i$ $(1 \leq i \leq N)$ 个区间是 $[l _ i, r _ i](0 \leq l_i < r_i \leq 10^9)$ 。求有多少对 $(i, j),(1 \leq i < j \leq N)$ 中，$i$ 和 $j$ 两个区间相交。

## 输入格式

第一行，一个整数 $N$。

第二到 $N+1$ 行，两个整数 $l_i$ $r_i$。

## 输出格式

一个整数，表示你的答案。

## 样例 #1

### 输入

```
3
1 5
7 8
3 7
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
3 4
2 5
1 6
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2
1 2
3 4
```

### 输出

```
0
```

