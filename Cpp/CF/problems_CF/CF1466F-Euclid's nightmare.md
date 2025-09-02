---
title: "Euclid's nightmare"
layout: "post"
diff: 普及+/提高
pid: CF1466F
tag: []
---

# Euclid's nightmare

## 题目描述

给定包含 $n$ 个 $m$ 维向量的向量集 $S$，每个向量 $\overrightarrow{a}$ 满足 $a_i\in \{0,1\}$ 且 $\sum\limits_{i=1}^ma_i\in\{1,2\}$。定义向量加法 $\overrightarrow{c}=\overrightarrow{a}+\overrightarrow{b}$ 为 $\forall i\in \Z\cap[1,m], c_i=a_i\oplus b_i$，其中 $\oplus$ 表示异或运算。

求极大线性空间 $T$ 使得 $T$ 的一组基 $A$ 均为 $S$ 中元素。输出 $|T|,|A|$ 以及 $A$。

要求在 $|A|$ 最小前提下 $A$ 关于向量编号字典序最小。

## 输入格式

第一行 $n,m$

以下 $n$ 行，每行先输入 $\sum\limits_{i=1}^ma_i$，接下来输入 $\sum\limits_{i=1}^ma_i$ 个数字 $k$ 表示 $a_k=1$。

## 输出格式

第一行输出 $|T|$ 和 $|A|$

第二行输出 $A$ 的每个向量，按编号排序并只需输出编号。

## 样例 #1

### 输入

```
3 2
1 1
1 2
2 2 1
```

### 输出

```
4 2
1 2
```

## 样例 #2

### 输入

```
2 3
2 1 3
2 1 2
```

### 输出

```
4 2
1 2
```

## 样例 #3

### 输入

```
3 5
2 1 2
1 3
1 4
```

### 输出

```
8 3
1 2 3
```

