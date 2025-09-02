---
title: "[ABC409C] Equilateral Triangle"
layout: "post"
diff: 难度0
pid: AT_abc409_c
tag: []
---

# [ABC409C] Equilateral Triangle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc409/tasks/abc409_c

有一个周长为 $L$ 的圆，圆周上分布着 $N$ 个点，编号为 $1,2,\ldots,N$。对于每个 $i=1,2,\ldots,N-1$，点 $i+1$ 位于从点 $i$ 出发沿顺时针方向移动 $d_i$ 距离的位置。

请统计满足以下两个条件的整数三元组 $(a,b,c)$（$1 \leq a < b < c \leq N$）的个数：

1. 三个点 $a,b,c$ 的位置互不相同；
2. 以 $a,b,c$ 为顶点的三角形是正三角形。

## 输入格式

输入通过标准输入给出，格式如下：

> $N$ $L$    
> $d_1$ $d_2$ $\ldots$ $d_{N-1}$

## 输出格式

输出答案。


## 说明/提示

### 约束条件

- $3 \leq L, N \leq 3 \times 10^5$
- $0 \leq d_i < L$
- 输入均为整数

### 样例解释 1

5 个点的分布如下图所示。满足条件的三元组有 $(a,b,c)=(1,2,4)$ 和 $(1,4,5)$ 共 2 个。  
![](https://img.atcoder.jp/abc409/58e1047b72e249e1390cc813d4e78a2f.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5 6
4 3 1 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 4
1 1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
10 12
4 4 5 7 1 7 0 8 5
```

### 输出

```
13
```

