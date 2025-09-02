---
title: "LANDFILL - Landfill"
layout: "post"
diff: 普及+/提高
pid: SP9378
tag: []
---

# LANDFILL - Landfill

## 题目描述

给定一个长度为 $n$ 的序列 $h$，你可以花费 $c_i$ 的钱使得 $h_i,h_{i+1},...,h_{\min(i+k-1,n)}$ 都乘上 $e_i$，但这个操作对于每一个 $i$ 至多执行一次。

你现在手上有 $b$ 的预算，请问在成本不超过预算的情况下 $h$ 的最小值最大是多少？

## 输入格式

第一行三个数 $n,b,k$。

接下来 $n$ 行，每行三个数 $h_i,e_i,c_i$。

## 输出格式

输出 $h$ 的最小值的最大值。

## 说明/提示

$1\le k\le 11,1\le n\le 100,1\le h_i,e_i,c_i\le10^6$。

Translated by \_Ponder_

## 样例 #1

### 输入

```
4 20 1
1 3 5
1 7 3
4 6 9
3 5 13
```

### 输出

```
3
```

