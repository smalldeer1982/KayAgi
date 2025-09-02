---
title: "Tetrahedron"
layout: "post"
diff: 普及+/提高
pid: CF166E
tag: ['递推', '线性递推', '逆元']
---

# Tetrahedron

## 题目描述

You are given a tetrahedron. Let's mark its vertices with letters $ A $ , $ B $ , $ C $ and $ D $ correspondingly.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166E/40dcfda00eddce9e7e8701e13b2759e732ca40f3.png)An ant is standing in the vertex $ D $ of the tetrahedron. The ant is quite active and he wouldn't stay idle. At each moment of time he makes a step from one vertex to another one along some edge of the tetrahedron. The ant just can't stand on one place.

You do not have to do much to solve the problem: your task is to count the number of ways in which the ant can go from the initial vertex $ D $ to itself in exactly $ n $ steps. In other words, you are asked to find out the number of different cyclic paths with the length of $ n $ from vertex $ D $ to itself. As the number can be quite large, you should print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line contains the only integer $ n $ ( $ 1<=n<=10^{7} $ ) — the required length of the cyclic path.

## 输出格式

Print the only integer — the required number of ways modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

The required paths in the first sample are:

- $ D-A-D $
- $ D-B-D $
- $ D-C-D $

## 样例 #1

### 输入

```
2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4

```

### 输出

```
21

```



---

