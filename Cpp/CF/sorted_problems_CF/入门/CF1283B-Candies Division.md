---
title: "Candies Division"
layout: "post"
diff: 入门
pid: CF1283B
tag: []
---

# Candies Division

## 题目描述

求最大的$ans$，使得$ans\le n$且$ans\equiv r(mod\ k),r\le\lfloor\dfrac{k}{2}\rfloor$。

## 输入格式

第1行输入1个整数$t(1\le t\le 5·10^4)$，为测试数据组数。

接下来$t$行，每行输入2个整数$n$和$k(1\le n,k\le 10^9)$。

## 输出格式

$t$行，第$i$行输出第$i$个测试数据的$ans$。

## 样例 #1

### 输入

```
5
5 2
19 4
12 7
6 2
100000 50010

```

### 输出

```
5
18
10
6
75015

```

