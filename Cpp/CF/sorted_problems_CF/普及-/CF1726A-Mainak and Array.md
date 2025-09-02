---
title: "Mainak and Array"
layout: "post"
diff: 普及-
pid: CF1726A
tag: []
---

# Mainak and Array

## 题目描述

### 题目大意

给定一个长度为 $n$ 的数组 $a$，可以选定**一个**区间 $[l, \; r]$ 进行**恰好一次**操作，求操作后最大的 $a_n - a_1$。

操作方法：选定区间 $[l, \; r]$ 和旋转次数 $k$, 每次旋转为 $a_l = a_{l + 1}, \; a_{l + 1} = a_{l + 2}, \; \dots, \; a_{r - 1} = a_r, \; a_r = a_l$

## 输入格式

第一行一个整数 $T \; (1 \leqslant T \leqslant 50)$，表示测试样例组数。

对于每组测试样例，第一行为一个整数 $n \; (1 \leqslant n \leqslant 2000)$ 表示数组长度。

接下来的一行含有 $n$ 个整数 $a_i \; (1 \leqslant a_i \leqslant 999)$，表示该数组。

数据保证 $\sum n \leqslant 2000$。

## 输出格式

对于每组测试样例包含一行一个整数，表示最大的 $a_n - a_1$。

$Translated \; by \; Zigh$

## 样例 #1

### 输入

```
5
6
1 3 9 11 5 7
1
20
3
9 99 999
4
2 1 8 1
3
2 1 5
```

### 输出

```
10
0
990
7
4
```

