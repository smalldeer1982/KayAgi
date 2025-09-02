---
title: "AquaMoon and Potatoes"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1545F
tag: []
---

# AquaMoon and Potatoes

## 题目描述

给你三个长度为 $n$ 的数组 $a,b,c$。

有 $m$ 次操作，每次操作为下面两种之一：

+ `1 k x`：将 $a_k$ 修改为 $x$。
+ `2 r`：求出有多少个三元组 $(i,j,k)$，满足 $1\leq i<j<k\le r$ 且 $b_{a_i}=a_j=c_{a_k}$。

## 输入格式

第一行两个整数 $n,m$。

接下来一行 $n$ 个数，第 $i$ 个数表示 $a_i$。

接下来一行 $n$ 个数，第 $i$ 个数表示 $b_i$。

接下来一行 $n$ 个数，第 $i$ 个数表示 $c_i$。

接下来 $m$ 行，为 $m$ 次操作。

## 输出格式

对于每个询问操作，输出一行一个整数，表示满足条件的三元组个数。

## 说明/提示

对于所有数据，$1\leq n\leq2\times 10^5,1\leq m\leq 5\times 10^4,1\leq a_i,b_i,c_i,k,x,r\leq n$。

## 样例 #1

### 输入

```
5 4
1 2 3 4 5
2 3 4 5 1
5 1 2 3 4
2 5
1 2 3
2 4
2 5
```

### 输出

```
3
0
2
```

