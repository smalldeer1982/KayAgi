---
title: "Reading Books (hard version)"
layout: "post"
diff: 省选/NOI-
pid: CF1374E2
tag: []
---

# Reading Books (hard version)

## 题目描述

做此题前，建议先做 [CF1374E1 Reading Books (easy version)](https://www.luogu.com.cn/problem/CF1374E1) 。

Alice 和 Bob 一共有 $n$ 本书要读。第 $i$ 本书有三个属性：阅读时间 $t_i$ ， $a_i$（为 $1$ 表示 Alice 喜欢这本书，为 $0$ 表示 Alice 不喜欢）， $b_i$ （为 $1$ 表示 Bob 喜欢这本书，为 $0$ 表示 Bob 不喜欢）。

他们需要从这些书中选择 $m$ 本，满足
- 这些书中至少有 $k$ 本是 Alice 喜欢的，至少有 $k$ 本是 Bob 喜欢的。
- 阅读的总时间最小（总时间为选中的书的 $t_i$ 的总和）

## 输入格式

第一行三个整数 $n,m$ 和 $k$ $(1 \leq k \leq n \leq 2 \times 10^5)$ 。

之后的 $n$ 行，每行三个整数 $t_i,a_i,b_i$ $(1 \leq t_i \leq 10^4,0 \leq a_i,b_i \leq 1)$ 。

## 输出格式

如果无解，输出 ```-1```。

如果有解，第一行输出 $T$ ——最少的阅读时间，第二行输出 $m$ 个不同的数——阅读的书的编号。

e.g. 由于 SPJ ，可以输出任意一种编号的组合，任意一种顺序。

## 样例 #1

### 输入

```
6 3 1
6 0 0
11 1 0
9 0 1
21 1 1
10 1 0
8 0 1
```

### 输出

```
24
6 5 1
```

## 样例 #2

### 输入

```
6 3 2
6 0 0
11 1 0
9 0 1
21 1 1
10 1 0
8 0 1
```

### 输出

```
39
4 6 5
```

