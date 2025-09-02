---
title: "Palindrome Everywhere"
layout: "post"
diff: 省选/NOI-
pid: CF2029F
tag: ['构造']
---

# Palindrome Everywhere

## 题目描述

给定一个 $n$ 个点的环，编号为 $0$ 到 $n-1$，第 $i(0 \leq i \leq n-1)$ 个点向第 $((i+1) \bmod n)$ 个点连一条颜色为 $c_i$（$c_i$ 为 `R` 或 `B`）的无向边。问任意两点是否都满足它们之间有一条“回文路径”。

两点 $(i,j)$ 间的回文路径定义：（假设该回文路径包含的点集为 $p=[p_0,p_1,\dots,p_m]$）

- 回文路径必须是两点之间的一条路径，但 **可以不是简单路径**。

- 对于满足 $x+y=m-1$ 且 $0 \leq x \leq y \leq m-1$ 的两点 $p_x,p_y$，若连接 $p_x,p_x+1$ 的边的颜色和连接 $p_y,p_y+1$ 的边的颜色相同。

## 输入格式

多测，第一行输入数据组数 $t(1 \leq t \leq 10^5)$。

对于每组数据，第一行一个整数 $n(3 \le n \le 10^6,\sum n \le 10^6)$，表示环长。

第二行有一个长度为 $n$ 的字符串 $c$，表示环上边的颜色。

## 输出格式

对于每组测试数据，如果满足任意两个节点都有回文路径，输出 `YES`，否则输出 `NO`。

输出大小写不敏感，即输出 `yEs`，`yes`，`Yes` 或 `YES` 都表示 `YES`。

## 样例 #1

### 输入

```
7
5
RRRRR
5
RRRRB
5
RBBRB
6
RBRBRB
6
RRBBRB
5
RBRBR
12
RRBRRBRRBRRB
```

### 输出

```
YES
YES
YES
NO
NO
YES
NO
```

