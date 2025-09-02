---
title: "Optimal Array Multiplication Sequence"
layout: "post"
diff: 提高+/省选-
pid: UVA348
tag: ['搜索', '记忆化搜索']
---

# Optimal Array Multiplication Sequence

## 题目描述

对于三个矩阵$A,B,C$，若$C=AB$，则C的计算方式为$C_{i,j}=\sum_k A_{i,k} \times B_{k,j}$。

可见若要计算两个大小分别为$a \times b$和$b \times c$的矩阵的乘积，需要$a \times b \times c$次计算；
对于两个矩阵$A,B$，不满足$A \times B = B \times A$；对于三个矩阵$A,B,C$，满足$(A \times B) \times C = A \times (B \times C)$。

给定$n$个矩阵$A1,A2, \dots ,An$的行列数，现在要算出这些矩阵的积，问如何安排运算顺序可使运算次数最少。

本题包含多组数据。

## 输入格式

对于每组数据，首先输入一个正整数$n(0 \le n \le 10)$，然后每行输入两个正整数，表示每个矩阵的行数和列数。

## 输出格式

首先输出“$Case\ k:\ $”，其中$k$为当前数据的组别编号。然后输出最优计算顺序，其中乘号用“x”代表，且前后都要输出一个空格。每一次乘法的外面都要套一对小括号。

例如第一组数据的最优解为先计算$A2 \times A3$，再计算$A1 \times (A2 \times A3)$，则要输出“(A1 x (A2 x A3))”。

## 样例 #1

### 输入

```
3
1 5
5 20
20 1
3
5 10
10 20
20 35
6
30 35
35 15
15 5
5 10
10 20
20 25
0
```

### 输出

```
Case 1: (A1 x (A2 x A3))
Case 2: ((A1 x A2) x A3)
Case 3: ((A1 x (A2 x A3)) x ((A4 x A5) x A6))
```

