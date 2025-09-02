---
title: "SOLDIER - Help the soldier"
layout: "post"
diff: 难度0
pid: SP3033
tag: []
---

# SOLDIER - Help the soldier

## 题目描述

Igor 要买 6 件物品，用数字 1 到 6 表示。这 6 种物品共有 $N (7 \le N \le 100)$ 个物品。每件物品的特点是其价格 $p_i$ 和质量 $q_i$ 。Igor 有 $T (1 \le T \le 1000)$ 元钱，他想最大化他购买的物品中的最小重量。

## 输入格式

第 1 行有两个整数 $N$ 和 $T$。

第 $2$ 至 $N+1$ 行，每行有3个整数，输入 $type_i$ (从1到6，表示物品类型)，$p_i$ 和 $q_i$ 。$(1 \le p_i,q_i \le T-1)$

## 输出格式

一行一个整数，表示最大总质量。

## 说明/提示

如果没有答案，输出 `0` 。

可以有少于 6 种类型的输入。

## 样例 #1

### 输入

```
7 53
5 8 2
2 4 8
6 8 13
1 13 12
4 5 1
3 2 7
3 13 5
```

### 输出

```
1

Note:
If there is no answer, output 0.
There can be less than 6 types of items.
```

