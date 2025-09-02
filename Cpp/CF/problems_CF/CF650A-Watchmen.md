---
title: "Watchmen"
layout: "post"
diff: 普及+/提高
pid: CF650A
tag: []
---

# Watchmen

## 题目描述

Watchmen are in a danger and Doctor Manhattan together with his friend Daniel Dreiberg should warn them as soon as possible. There are $ n $ watchmen on a plane, the $ i $ -th watchman is located at point $ (x_{i},y_{i}) $ .

They need to arrange a plan, but there are some difficulties on their way. As you know, Doctor Manhattan considers the distance between watchmen $ i $ and $ j $ to be $ |x_{i}-x_{j}|+|y_{i}-y_{j}| $ . Daniel, as an ordinary person, calculates the distance using the formula ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF650A/fcefde1ea60e1105aa698e148af7dc900a7454c9.png).

The success of the operation relies on the number of pairs $ (i,j) $ ( $ 1<=i&lt;j<=n $ ), such that the distance between watchman $ i $ and watchmen $ j $ calculated by Doctor Manhattan is equal to the distance between them calculated by Daniel. You were asked to compute the number of such pairs.

## 输入格式

The first line of the input contains the single integer $ n $ ( $ 1<=n<=200000 $ ) — the number of watchmen.

Each of the following $ n $ lines contains two integers $ x_{i} $ and $ y_{i} $ ( $ |x_{i}|,|y_{i}|<=10^{9} $ ).

Some positions may coincide.

## 输出格式

Print the number of pairs of watchmen such that the distance between them calculated by Doctor Manhattan is equal to the distance calculated by Daniel.

## 说明/提示

In the first sample, the distance between watchman $ 1 $ and watchman $ 2 $ is equal to $ |1-7|+|1-5|=10 $ for Doctor Manhattan and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF650A/91477f866a0e0d69e03fe1418359568f2f96b567.png) for Daniel. For pairs $ (1,1) $ , $ (1,5) $ and $ (7,5) $ , $ (1,5) $ Doctor Manhattan and Daniel will calculate the same distances.

## 样例 #1

### 输入

```
3
1 1
7 5
1 5

```

### 输出

```
2

```

## 样例 #2

### 输入

```
6
0 0
0 1
0 2
-1 1
0 1
1 1

```

### 输出

```
11

```

