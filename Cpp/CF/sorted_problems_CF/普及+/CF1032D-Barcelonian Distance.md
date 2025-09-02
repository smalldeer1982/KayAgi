---
title: "Barcelonian Distance"
layout: "post"
diff: 普及+/提高
pid: CF1032D
tag: []
---

# Barcelonian Distance

## 题目描述

In this problem we consider a very simplified model of Barcelona city.

Barcelona can be represented as a plane with streets of kind $ x = c $ and $ y = c $ for every integer $ c $ (that is, the rectangular grid). However, there is a detail which makes Barcelona different from Manhattan. There is an avenue called Avinguda Diagonal which can be represented as a the set of points $ (x, y) $ for which $ ax + by + c = 0 $ .

One can walk along streets, including the avenue. You are given two integer points $ A $ and $ B $ somewhere in Barcelona. Find the minimal possible distance one needs to travel to get to $ B $ from $ A $ .

## 输入格式

The first line contains three integers $ a $ , $ b $ and $ c $ ( $ -10^9\leq a, b, c\leq 10^9 $ , at least one of $ a $ and $ b $ is not zero) representing the Diagonal Avenue.

The next line contains four integers $ x_1 $ , $ y_1 $ , $ x_2 $ and $ y_2 $ ( $ -10^9\leq x_1, y_1, x_2, y_2\leq 10^9 $ ) denoting the points $ A = (x_1, y_1) $ and $ B = (x_2, y_2) $ .

## 输出格式

Find the minimum possible travel distance between $ A $ and $ B $ . Your answer is considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer is accepted if and only if $ \frac{|a - b|}{\max{(1, |b|)}} \le 10^{-6} $ .

## 说明/提示

The first example is shown on the left picture while the second example us shown on the right picture below. The avenue is shown with blue, the origin is shown with the black dot.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1032D/d9be16980f00189d5199b81c1601b819612b0d94.png)

## 样例 #1

### 输入

```
1 1 -3
0 3 3 0

```

### 输出

```
4.2426406871

```

## 样例 #2

### 输入

```
3 1 -9
0 3 3 -1

```

### 输出

```
6.1622776602

```

