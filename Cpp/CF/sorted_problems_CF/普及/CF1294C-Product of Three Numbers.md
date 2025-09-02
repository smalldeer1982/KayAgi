---
title: "Product of Three Numbers"
layout: "post"
diff: 普及/提高-
pid: CF1294C
tag: []
---

# Product of Three Numbers

## 题目描述

给定一个数 $n$ ，请求出三个不相同的整数 $a,b,c$ 且 $2 \leq a,b,c$ ，使得 $a \cdot b \cdot c =n$。

如果有多个答案，输出任一合法解。

本题有多组数据。

## 输入格式

第一行有一个数 $t$ $(1\leq t \leq 100)$ ，代表数据组数。

接下来 $t$ 行，每行一个数 $n$ $(2 \leq n \leq 10^9)$ ，为题中所给的 $n$ 。

## 输出格式

如果不存在合法的 $a,b,c$ ，输出 `NO` 。

否则，输出 `YES` 。

## 样例 #1

### 输入

```
5
64
32
97
2
12345
```

### 输出

```
YES
2 4 8 
NO
NO
NO
YES
3 5 823
```

