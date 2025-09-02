---
title: "Permutation Graph"
layout: "post"
diff: 提高+/省选-
pid: CF1696D
tag: ['贪心', '线段树', '分治']
---

# Permutation Graph

## 题目描述

给出一个 $1$ 到 $n$ 的排列 $ [a_1,a_2,\dots,a_n] $ 。对于 $1\le i < j\le n$ ，记 $ \operatorname{mn}(i,j) $ 为 $\min\limits_{k=i}^j a_k$ ，记  $ \operatorname{mx}(i,j) $ 为 $ \max\limits_{k=i}^j a_k $ 。

有一张 $n$ 个点的无向图，点的编号为 $1$ 到 $n$ 。对于每一对整数 $ 1\le i<j\le n $ ，如果同时满足 $ \operatorname{mn}(i,j)=a_i $ 且 $ \operatorname{mx}(i,j)=a_j $ ，或同时满足 $ \operatorname{mn}(i,j)=a_j $ 和 $ \operatorname{mx}(i,j)=a_i $ ，那么就在 $i$ 和 $j$ 之间连一条长度为 $1$ 的边。

询问这张图中从 $1$ 到 $n$ 的最短路的长度。可以证明 $1$ 和 $n$ 总是连通，所以最短路总是存在。

## 输入格式

每个数据点包含多组数据。第一行一个整数 $t$ ( $ 1 \le t \le 5\cdot 10^4 $ ) 表示测试组数

对于每组数据，第一行一个整数 $n$ ( $ 1\le n\le 2.5\cdot 10^5 $ ) 。

第二行包含 $n$ 个整数 $ a_1 $ , $ a_2 $ , $ \ldots $ , $ a_n $ ( $ 1\le a_i\le n $ ) 。保证 $a$ 是 $ 1 $ , $ 2 $ , $ \dots $ , $ n $ 的一个排列。

保证所有数据的 $n$ 之和不超过 $ 5\cdot 10^5 $

## 输出格式

对于每组数据，输出一个整数表示从 $1$ 到 $n$ 的最短路长度

## 样例 #1

### 输入

```
5
1
1
2
1 2
5
1 4 2 3 5
5
2 1 5 3 4
10
7 4 8 1 6 10 3 5 2 9
```

### 输出

```
0
1
1
4
6
```

