---
title: "Ehab and Path-etic MEXs"
layout: "post"
diff: 普及/提高-
pid: CF1325C
tag: []
---

# Ehab and Path-etic MEXs

## 题目描述

You are given a tree consisting of $ n $ nodes. You want to write some labels on the tree's edges such that the following conditions hold:

- Every label is an integer between $ 0 $ and $ n-2 $ inclusive.
- All the written labels are distinct.
- The largest value among $ MEX(u,v) $ over all pairs of nodes $ (u,v) $ is as small as possible.

Here, $ MEX(u,v) $ denotes the smallest non-negative integer that isn't written on any edge on the unique simple path from node $ u $ to node $ v $ .

## 输入格式

The first line contains the integer $ n $ ( $ 2 \le n \le 10^5 $ ) — the number of nodes in the tree.

Each of the next $ n-1 $ lines contains two space-separated integers $ u $ and $ v $ ( $ 1 \le u,v \le n $ ) that mean there's an edge between nodes $ u $ and $ v $ . It's guaranteed that the given graph is a tree.

## 输出格式

Output $ n-1 $ integers. The $ i^{th} $ of them will be the number written on the $ i^{th} $ edge (in the input order).

## 说明/提示

The tree from the second sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1325C/3987a692dde98854639547ed68f742fb6eeb5979.png)

## 样例 #1

### 输入

```
3
1 2
1 3
```

### 输出

```
0
1
```

## 样例 #2

### 输入

```
6
1 2
1 3
2 4
2 5
5 6
```

### 输出

```
0
3
2
4
1
```

