---
title: "SNGPG - Prime Generator The Easiest Question Ever"
layout: "post"
diff: 普及/提高-
pid: SP15891
tag: ['数论', '素数判断,质数,筛法']
---

# SNGPG - Prime Generator The Easiest Question Ever

## 题目描述

给定区间 $[a, b]$，求该区间中满足 $p^2 + 1$ 或 $p^2 + 2$ 为质数的质数 $p$ 的数量。特别地，我们认为 $0$ 和 $1$ 也为质数。

## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

一行，两个整数 $a, b$。

## 输出格式

对于每组数据，输出一行，一个整数，表示所求的值。
### 输入输出样例
#### 输入 #1
```
2
0 1
4 5
```
#### 输出 #1
```
2
0
```

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T < 100$，$0 \leq a \leq 5 \times 10^4$，$1 \leq b \leq 10^5$，$a < b$。

## 样例 #1

### 输入

```
2\n0 1\n4 5
```

### 输出

```
2\n0\n\n[Consider 0 and 1 as prime numbers for this question]
```

