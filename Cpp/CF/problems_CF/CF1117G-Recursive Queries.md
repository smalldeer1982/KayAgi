---
title: "Recursive Queries"
layout: "post"
diff: 省选/NOI-
pid: CF1117G
tag: []
---

# Recursive Queries

## 题目描述

有一个长度为$n$的排列$p_1,p_2,\dots,p_n$，还有$q$次询问，每次询问一段区间$[l_i, r_i]$，你需要计算出$f(l_i, r_i)$。

定义$m_{l, r}$表示$p_l, p_{l+1}, \dots, p_r$这一段数列的最大值的出现位置，则

$$f(l, r) =\begin{cases}(r-l+1)+f(l,m_{l,r}-1)+f(m_{l,r}+1,r)&\text{if $l<=r$}\\0&\text{else}\end{cases}$$

## 输入格式

第一行两个整数$n$和$q$，表示排列的长度和询问的个数。$(1\le n\le 10^6,1\le q\le 10^6)$

第二行$n$个整数，表示排列$p$。

第三行$q$个整数，依次表示每一次询问的左端点。

第四行$q$个整数，依次表示每一次询问的右端点。

数据保证$1\le l_i\le r_i\le n$

## 输出格式

输出一行$q$个整数，表示每一次询问的答案。

## 样例 #1

### 输入

```
4 5
3 1 4 2
2 1 1 2 1
2 3 4 4 1

```

### 输出

```
1 6 8 5 1 

```

