---
title: "Paths"
layout: "post"
diff: 省选/NOI-
pid: CF870F
tag: []
---

# Paths

## 题目描述

You are given a positive integer $ n $ . Let's build a graph on vertices $ 1,2,...,n $ in such a way that there is an edge between vertices $ u $ and $ v $ if and only if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870F/c23ed97fe13a97ab9d4221da3ee57148bf19e74e.png). Let $ d(u,v) $ be the shortest distance between $ u $ and $ v $ , or $ 0 $ if there is no path between them. Compute the sum of values $ d(u,v) $ over all $ 1<=u<v<=n $ .

The $ gcd $ (greatest common divisor) of two positive integers is the maximum positive integer that divides both of the integers.

## 输入格式

Single integer $ n $ ( $ 1<=n<=10^{7} $ ).

## 输出格式

Print the sum of $ d(u,v) $ over all $ 1<=u<v<=n $ .

## 说明/提示

All shortest paths in the first example:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870F/3e40931641babdd9752cd39292d234015759308e.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870F/6041d67223ddc985153dc52c9e7a7e1d48075179.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870F/3e29ecae5595c93d38537b4ca1a7d7fc6ca1fa60.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870F/c648e4ad2596633a70de4e6c388b5f81739e78ae.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870F/d7426e9934723e8754848fe5e8743b6ef00be8ab.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870F/f09a0e8516170bfe135732c6c4dc8bd6c28ccd78.png)

There are no paths between other pairs of vertices.

The total distance is $ 2+1+1+2+1+1=8 $ .

## 样例 #1

### 输入

```
6

```

### 输出

```
8

```

## 样例 #2

### 输入

```
10

```

### 输出

```
44

```

