---
title: "Recursive Queries"
layout: "post"
diff: 普及/提高-
pid: CF932B
tag: []
---

# Recursive Queries

## 题目描述

Let us define two functions $ f $ and $ g $ on positive integer numbers.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF932B/5ea922a7608f7b43dbb7e14356bf3e8277d2c765.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF932B/c3f9cee55fe0b74363392f2f9845da5254de38c3.png)

You need to process $ Q $ queries. In each query, you will be given three integers $ l $ , $ r $ and $ k $ . You need to print the number of integers $ x $ between $ l $ and $ r $ inclusive, such that $ g(x)=k $ .

## 输入格式

The first line of the input contains an integer $ Q $ ( $ 1<=Q<=2×10^{5} $ ) representing the number of queries.

 $ Q $ lines follow, each of which contains 3 integers $ l $ , $ r $ and $ k $ $ (1<=l<=r<=10^{6},1<=k<=9) $ .

## 输出格式

For each query, print a single line containing the answer for that query.

## 说明/提示

In the first example:

- $ g(33)=9 $ as $ g(33)=g(3×3)=g(9)=9 $
- $ g(47)=g(48)=g(60)=g(61)=6 $
- There are no such integers between $ 47 $ and $ 55 $ .
- $ g(4)=g(14)=g(22)=g(27)=g(39)=g(40)=g(41)=g(58)=4 $

## 样例 #1

### 输入

```
4
22 73 9
45 64 6
47 55 7
2 62 4

```

### 输出

```
1
4
0
8

```

## 样例 #2

### 输入

```
4
82 94 6
56 67 4
28 59 9
39 74 4

```

### 输出

```
3
1
1
5

```

