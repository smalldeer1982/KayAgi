---
title: "Divisor Tree"
layout: "post"
diff: 提高+/省选-
pid: CF337E
tag: []
---

# Divisor Tree

## 题目描述

A divisor tree is a rooted tree that meets the following conditions:

- Each vertex of the tree contains a positive integer number.
- The numbers written in the leaves of the tree are prime numbers.
- For any inner vertex, the number within it is equal to the product of the numbers written in its children.

Manao has $ n $ distinct integers $ a_{1},a_{2},...,a_{n} $ . He tries to build a divisor tree which contains each of these numbers. That is, for each $ a_{i} $ , there should be at least one vertex in the tree which contains $ a_{i} $ . Manao loves compact style, but his trees are too large. Help Manao determine the minimum possible number of vertices in the divisor tree sought.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=8 $ ). The second line contains $ n $ distinct space-separated integers $ a_{i} $ ( $ 2<=a_{i}<=10^{12} $ ).

## 输出格式

Print a single integer — the minimum number of vertices in the divisor tree that contains each of the numbers $ a_{i} $ .

## 说明/提示

Sample 1. The smallest divisor tree looks this way: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337E/71b2187cbd06bdd466a640fb3fba452ed4239e72.png)

Sample 2. In this case you can build the following divisor tree: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337E/983e0e8e1e41f9fa18f4f08eec9d634ad5efd21c.png)

Sample 3. Note that the tree can consist of a single vertex.

## 样例 #1

### 输入

```
2
6 10

```

### 输出

```
7

```

## 样例 #2

### 输入

```
4
6 72 8 4

```

### 输出

```
12

```

## 样例 #3

### 输入

```
1
7

```

### 输出

```
1

```

