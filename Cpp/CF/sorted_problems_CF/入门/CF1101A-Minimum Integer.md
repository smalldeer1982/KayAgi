---
title: "Minimum Integer"
layout: "post"
diff: 入门
pid: CF1101A
tag: []
---

# Minimum Integer

## 题目描述

题意简述

给出$q$组询问，每组询问给出$l,r,d$，求一个最小的正整数$x$满足$d | x\ $且$ x \not\in [l,r]$

## 输入格式

第一行一个正整数$q(1 \leq q \leq 500)$

接下来$q$行每行三个正整数$l,r,d(1 \leq l \leq r \leq 10^9 , 1 \leq d \leq 10^9)$表示一组询问

## 输出格式

对于每一组询问输出一行表示答案

## 样例 #1

### 输入

```
5
2 4 2
5 10 4
3 10 1
1 2 3
4 6 5

```

### 输出

```
6
4
1
3
10

```

