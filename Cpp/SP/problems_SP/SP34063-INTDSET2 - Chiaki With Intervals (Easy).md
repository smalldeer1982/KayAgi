---
title: "INTDSET2 - Chiaki With Intervals (Easy)"
layout: "post"
diff: 难度0
pid: SP34063
tag: []
---

# INTDSET2 - Chiaki With Intervals (Easy)

## 题目描述

给你一个有 $n$ 个区间的集合 $A$，求有多少个子集 $S$ 满足条件：任意区间 $a \in A$ 且 $a \notin S$ 均与 $S$ 的至少一个子集有交集。

答案对 $10^9+7$ 取模。

注意 $A$ 本身是一个合法的答案。

## 输入格式

第一行输入整数 $T$ ，代表数据组数。

对于每组数据，先输入整数 $n$，代表区间的个数，接下来是 $n$ 行，每行两个整数 $l_i,r_i$，代表一个区间。**与 Hard Version 不同，在本题中每组测试数据最多有 $\color{Red}15$ 个不同的 $r_i$**。

## 输出格式

对于每组数据，输出一个整数。

## 样例 #1

### 输入

```
2
3
1 2
3 4
5 6
3
1 4
2 4
3 4
```

### 输出

```
1
7
```

