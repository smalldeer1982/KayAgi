---
title: "AFSK - Power Factor Sum Sum (hard)"
layout: "post"
diff: 难度0
pid: SP14175
tag: []
---

# AFSK - Power Factor Sum Sum (hard)

## 题目描述

给定 $n,k$，求：  
$$\large \sum\limits_{i=1}^n\sum\limits_{j|i}j^k$$
由于答案可能很大，所以要对 $m$ 取模。

## 输入格式

第一行一个正整数 $T$，表示数据组数。

## 输出格式

输出 $T$ 行，对于每组数据，输出一行一个整数表示结果。

## 说明/提示

$1\le T \le 100$  
$1\le n < 10^9$  
$1\le k \le 10$  
$2\le m < 10^{17}$

## 样例 #1

### 输入

```
3
3 1 10
4 2 55
5 3 97
```

### 输出

```
8
37
43
```

