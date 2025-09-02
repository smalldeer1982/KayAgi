---
title: "[ABC405C] Sum of Product"
layout: "post"
diff: 普及-
pid: AT_abc405_c
tag: ['数学', '前缀和']
---

# [ABC405C] Sum of Product

## 题目描述

给你一个数列 $A=(A_1,A_2,\cdots,A_N)$。

求 $\sum\limits_{1\le i<j\le N} A_iA_j$ 的值。

## 输入格式

第一行一个整数 $N(2\le N\le 3\times 10^5)$。\
第二行 $N$ 个整数 $A_1,A_2,\cdots,A_N(1\le A_i\le 10^4)$。

## 输出格式

一行一个整数表示答案。

## 说明/提示

**样例 1 解释**

答案为 $\sum\limits_{1\le i<j\le N} A_iA_j=A_1A_2+A_1A_3+A_2A_3=4\times 2+4\times 3+2\times 3=26$。

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
3
4 2 3
```

### 输出

```
26
```

## 样例 #2

### 输入

```
2
9 45
```

### 输出

```
405
```

## 样例 #3

### 输入

```
10
7781 8803 8630 9065 8831 9182 8593 7660 7548 8617
```

### 输出

```
3227530139
```

