---
title: "[ABC397E] Path Decomposition of a Tree"
layout: "post"
diff: 普及+/提高
pid: AT_abc397_e
tag: ['树形 DP']
---

# [ABC397E] Path Decomposition of a Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc397/tasks/abc397_e

给定一棵包含 $NK$ 个顶点的树。顶点编号为 $1,2,\dots,NK$，其中第 $i$ 条边（$i=1,2,\dots,NK-1$）双向连接顶点 $u_i$ 和 $v_i$。

请判断是否可以将这棵树分解为 $N$ 条长度为 $K$ 的路径。更具体地说，判断是否存在满足以下条件的 $N \times K$ 矩阵 $P$：

- $P_{1,1}, \dots, P_{1,K}, P_{2,1}, \dots, P_{N,K}$ 是 $1,2,\dots,NK$ 的一个排列。
- 对于每个 $i=1,2,\dots,N$ 和 $j=1,2,\dots,K-1$，顶点 $P_{i,j}$ 和顶点 $P_{i,j+1}$ 之间存在一条边。


## 输入格式

输入通过标准输入给出，格式如下：

> $N$ $K$   
> $u_1$ $v_1$    
> $u_2$ $v_2$    
> $\vdots$   
> $u_{NK-1}$ $v_{NK-1}$   

## 输出格式

若可以分解为 $N$ 条长度为 $K$ 的路径，则输出 `Yes`，否则输出 `No`。

## 说明/提示

### 约束条件

- $1 \leq N$
- $1 \leq K$
- $NK \leq 2 \times 10^5$
- $1 \leq u_i < v_i \leq NK$
- 输入的图是一棵树
- 输入均为整数

### 样例解释 1

可以将树分解为由顶点 1,2 组成的路径、由顶点 3,4 组成的路径和由顶点 5,6 组成的路径。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 2
1 2
2 3
3 4
2 5
5 6
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3 2
1 2
2 3
3 4
2 5
3 6
```

### 输出

```
No
```

