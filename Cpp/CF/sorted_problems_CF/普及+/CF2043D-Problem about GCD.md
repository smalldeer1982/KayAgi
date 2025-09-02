---
title: "Problem about GCD"
layout: "post"
diff: 普及+/提高
pid: CF2043D
tag: ['数论']
---

# Problem about GCD

## 题目描述

给出三个整数 $l,r,G$，要求找到一个数对 $A,B$ 满足 $l\le A\le B\le r$ 且 $\gcd (A,B) = G$，并且满足 $\left\vert A-B \right\vert$ 最大。

如果有多组解，选择 $A$ 的值最小的一个。

## 输入格式

第一行一个整数 $T$，表示测试点数量。

## 输出格式

$T$ 行，每行两个数 $A,B$ 表示该测试点的答案。

## 说明/提示

$1\le t\le 10^3$

$1\le l\le r\le 10^{18}$

$1\le G\le 10^{18}$

## 样例 #1

### 输入

```
4
4 8 2
4 8 3
4 8 4
5 7 6
```

### 输出

```
4 6
-1 -1
4 8
6 6
```

