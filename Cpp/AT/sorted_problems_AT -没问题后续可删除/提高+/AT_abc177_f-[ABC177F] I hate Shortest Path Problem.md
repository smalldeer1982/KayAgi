---
title: "[ABC177F] I hate Shortest Path Problem"
layout: "post"
diff: 提高+/省选-
pid: AT_abc177_f
tag: []
---

# [ABC177F] I hate Shortest Path Problem

## 题目描述

### 题目大意

有一个 $(H+1)$ 行 $W$ 列的矩阵，你每步可以在矩阵中向右或向下移动一个格子。其中，在第 $i\,(1 \le i \le H)$ 行中，你无法从左至右第 $A_i$ 至 $B_i$ 个格子向下走。对于每一个 $k\,(1 \le k \le H)$，求出你从第 $1$ 行的任意一个格子出发移动到第 $(k+1)$ 行的最少步数，若无法移动到则输出 `-1`。

数据范围：$1 \le H,W \le 2\times 10^5$，$1 \le A_i \le B_i \le W$。

## 输入格式

第一行两个整数 $H,W$，接下来 $H$ 行每行两个整数 $A_i,B_i$。

## 输出格式

共 $H$ 行，每行一个整数，第 $i$ 行的数字表示从第 $1$ 行移动到第 $(i+1)$ 行需要的最少步数，若无法移动到则为 `-1`。

### 样例解释

$k=1$ 时，其中一种答案最小的移动顺序为 $(1,1)\rightarrow (2,1)$；

$k=2$ 时，一种移动顺序为 $(1,1)\rightarrow (2,1)\rightarrow (2,2)\rightarrow (3,2)$；

$k=3$ 时，一种移动顺序为 $(1,1)\rightarrow (2,1)\rightarrow (2,2)\rightarrow (3,2)\rightarrow (3,3)\rightarrow (3,4)\rightarrow (4,4)$；

$k=4$ 时，无法从第 $1$ 行移动到第 $5$ 行。

（翻译 by @CarroT1212）

## 样例 #1

### 输入

```
4 4
2 4
1 1
2 3
2 4
```

### 输出

```
1
3
6
-1
```

