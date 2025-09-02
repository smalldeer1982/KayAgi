---
title: "Klee's SUPER DUPER LARGE Array!!!"
layout: "post"
diff: 普及/提高-
pid: CF2009E
tag: ['数学', '二分', '三分']
---

# Klee's SUPER DUPER LARGE Array!!!

## 题目描述

### 题目大意

你将得到一个长度为 $n$ 的序列 $a=[k,k+1,k+2,\dots, k+n-1]$，请求出 $S$ 的值，其中

$$S=\min\limits_{1\le x\le n}|(\sum\limits_{i=1}^x a_i)-(\sum\limits_{i=x+1}^n a_i)|$$

## 输入格式

**本题存在多组测试数据**。第一行为一个正整数 $T$（$1\le T\le 10^4$），表示数据组数。对于每组数据分别给出用空格隔开的两个整数 $n$ 与 $k$（$2\le n,k\le 10^9$）。

## 输出格式

对于每组数据，输出一行一个整数 $S$。

## 样例 #1

### 输入

```
4
2 2
7 2
5 3
1000000000 1000000000
```

### 输出

```
1
5
1
347369930
```

