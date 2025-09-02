---
title: "YUMMY - Yummy Triangular Pizza"
layout: "post"
diff: 难度0
pid: SP9686
tag: []
---

# YUMMY - Yummy Triangular Pizza

## 题目背景

译自 [SPOJ.com -  Problem YUMMY](https://www.spoj.com/problems/YUMMY/)。

## 题目描述

Pizzahat 发布了一种新型披萨，其切片呈等边三角形形状。这个披萨由若干个大小相同的等边三角形拼接而成。此外，所有的三角形都是连通的，并且如果两个三角形直接相连，它们必须共享一条公共边。

给定 $N$ 个三角形，这种披萨可以有多少种不同的形状？**如果两个形状通过旋转和平移（注意，不包括翻转）后可以完全重合，则认为它们是相同的。**

## 输入格式

输入包含多组测试数据。

第一行包含一个整数，表示测试数据的组数。

每组测试数据仅一行，包含一个整数 $N$，表示可以使用的三角形数量（$1 \leq N \leq 16$）。

## 输出格式

对于每个测试用例，输出一个整数，表示披萨可能的不同形状的数量。

## 说明/提示

![](https://www.spoj.com/content/john_jones:yummy.jpg)

*本题由* **Cabbage** *队（中南大学）在现场赛开始后第 225 分钟首次（也是唯一一次）AC。（在 AC 之前，他们有过 1 次错误提交。）*

## 样例 #1

### 输入

```
3
2
4
10
```

### 输出

```
Case #1: 1
Case #2: 4
Case #3: 866
```

