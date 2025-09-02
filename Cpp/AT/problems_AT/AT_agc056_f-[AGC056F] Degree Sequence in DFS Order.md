---
title: "[AGC056F] Degree Sequence in DFS Order"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_agc056_f
tag: ['贪心', '组合数学']
---

# [AGC056F] Degree Sequence in DFS Order

## 题目描述

已知整数 $N,M$， 求有多少个整数序列 $a=(a_1,a_2,\cdots,a_N)$ 可以由以下方式生成，答案对 $998244353$ 取模。

- 选择一个 $N$ 个点，$M$ 条边的无向连通图 $G$，要求无自环，但可以有重边。
- 进行 DFS，令 $a_i$ 表示遍历到的第 $i$ 个点的度数，具体的，执行以下代码：

```
a = empty array

dfs(v):
    visited[v]=True
    a.append(degree[v])
    for u in g[v]:
        if not visited[u]:
            dfs(u)

dfs(arbitrary root)
```

这里，$g$ 是图 $G$ 的邻接表，$g[v]$ 是任意顺序的与 $v$ 相连的顶点列表。

举个例子，对于 $N=4,M=5$，一个可能的 $a=(2,4,1,3)$，图 $G$ 如下图所示：

![G](https://img.atcoder.jp/agc056/3bfec17f881ae4cd27eccae94ebeae10.png)

顶点上的数字表示访问他们的顺序，橙色箭头表示遍历时经过的边。

## 输入格式

一行两个数 $N,M$。

## 输出格式

一行一个数，表示答案。

### 样例解释 $\textbf 1$

只有 $a=(2,2)$ 合法。


**Translated by @nr0728.**

## 说明/提示

- $2\le N\le M\le 10^6$。

## 样例 #1

### 输入

```
2 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 4
```

### 输出

```
9
```

## 样例 #3

### 输入

```
10 20
```

### 输出

```
186225754
```

## 样例 #4

### 输入

```
100000 1000000
```

### 输出

```
191021899
```

