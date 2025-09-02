---
title: "IAPCR2F - Summer Trip"
layout: "post"
diff: 难度0
pid: SP27194
tag: []
---

# IAPCR2F - Summer Trip

## 题目描述

在这个炎热的夏天，AIUB 的学生决定去 Cox’s Bazaar 海滩旅行。每个学生在这次旅行中都带了一些钱准备用。学生们被分为了几个小组，如果学生 A 认识学生 B，B 认识 C，那么 A，B 和 C 属于同一组。

为了合理利用预算，学生们聘请了一家旅行社来获得最佳的旅行计划。学生们给了旅行社所有学生的钱和他们之间的关系的一份资料。现在该旅行社想计算出小组的数量和每个小组的总预算。一个小组的总预算是该小组所有学生的所准备的钱数之和。

## 输入格式

第一行包含一个整数 $T(1\leqslant T\leqslant 50)$，表示数据组数。

每组数据的第一行包含两个整数 $N,M$。   
$N(1\leqslant N\leqslant 1000)$，表示学生人数；       
$M(0\leqslant M\leqslant \dfrac{N\cdot(N-1)}{2})$，表示关系总数。

下一行给出 $N$ 个整数。第 $i$ 个 $(1\leqslant i\leqslant N)$  整数 $A_{i}(1\leqslant A_{i}\leqslant 100)$ 表示学生有多少钱。

接下来的 $M$ 行每行包含两个整数 $u,v$，$(1 \leqslant u，v\leqslant N，u \neq v)$ 表示编号为 $u$ 的学生认识编号为 $v$ 的学生，反之亦然。

## 输出格式

对于每组数据输出`case X:K`，其中 $X$ 表示当前是第 $X$ 组数据（从1开始），$K$ 是当前这组数据中，小组的数量。
在下一行输出 $K$ 个整数，所有组的总预算按预算的**升序**排列。

> Translate By shao_qian

## 样例 #1

### 输入

```
1
5 3
5 7 4 6 8
1 2
1 3
4 5
```

### 输出

```
Case 1: 2
14 16
```

