---
title: "Number Transformation II"
layout: "post"
diff: 提高+/省选-
pid: CF346C
tag: []
---

# Number Transformation II

## 题目描述

给定 $n$ 个正整数 $x_i$ 和两个非负整数 $a$ 、 $b$ ，（ $b\leq a$ ），你每次可以进行以下两操作中任一个：
1. $a=a-1$
2. $a=a-a\ mod\ x_i(1\leq i\leq n)$   

问要使 $a$ 变成 $b$ 至少需要多少次操作

## 输入格式

第一行一个整数 $n$ 。   
第二行 $n$ 个整数 $x_i$ 。   
第三行两个整数 $a$ 、 $b$ 。

## 输出格式

一个整数，表示将 $a$ 变成 $b$ 的最少操作数。

#### 数据范围   
$1\leq n\leq 10^5,2\leq x_i\leq 10^9$   
$0\leq b\leq a\leq 10^9,a-b\leq 10^6$

## 样例 #1

### 输入

```
3
3 4 5
30 17

```

### 输出

```
6

```

## 样例 #2

### 输入

```
3
5 6 7
1000 200

```

### 输出

```
206

```

