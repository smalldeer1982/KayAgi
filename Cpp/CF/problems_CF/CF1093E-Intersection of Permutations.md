---
title: "Intersection of Permutations"
layout: "post"
diff: 省选/NOI-
pid: CF1093E
tag: []
---

# Intersection of Permutations

## 题目描述

给定整数 $n$ 和两个 $1,\dots,n$ 的排列 $a,b$。

$m$ 个操作，操作有两种：
  - $1\ l_a\ r_a\ l_b\ r_b$，设 $a$ 的 $[l_a;r_a]$ 区间内的元素集合为 $S_a$，设 $b$ 的 $[l_b;r_b]$ 区间内的元素集合为 $S_b$，求 $\lvert S_a \bigcap S_b \rvert$。
  - $2\ x\ y$，交换 $b$ 的第 $x$ 位与第 $y$ 位。

$1 \le n,m \le 2 \cdot 10^5$

## 输入格式

第一行，两个整数 $n,m$。  
以下两行，每行 $n$ 个整数，分别表示 $a,b$。  
以下 $m$ 行，每行一个操作。

## 输出格式

对于每个 $1$ 操作，输出答案。

## 样例 #1

### 输入

```
6 7
5 1 4 2 3 6
2 5 3 1 4 6
1 1 2 4 5
2 2 4
1 1 2 4 5
1 2 3 3 5
1 1 6 1 2
2 4 1
1 4 4 1 3

```

### 输出

```
1
1
1
2
0

```

