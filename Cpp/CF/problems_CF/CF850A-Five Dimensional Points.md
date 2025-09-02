---
title: "Five Dimensional Points"
layout: "post"
diff: 普及+/提高
pid: CF850A
tag: ['枚举', '向量']
---

# Five Dimensional Points

## 题目描述

You are given set of $ n $ points in 5-dimensional space. The points are labeled from $ 1 $ to $ n $ . No two points coincide.

We will call point $ a $ bad if there are different points $ b $ and $ c $ , not equal to $ a $ , from the given set such that angle between vectors ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/0653dbc57091409c95cbdb75a14170af617d0442.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/bde2e95036e34134c1ea6bd6b9709d7dd49d1b09.png) is acute (i.e. strictly less than ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/fe3c8011bb9ee15abb5ac0ee9f2f980eef59656c.png)). Otherwise, the point is called good.

The angle between vectors ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/5a3a683029365387cf086e592ebfccb0e126e88a.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/2c10c8fe0b4dfc279c1514830bc9fce0b1aa6b49.png) in 5-dimensional space is defined as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/d27dbfc0849680d0f326c5cde0af47140b2f6df3.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/0fea22328d6b3b4c1d11529ba4c9764cafce84d3.png) is the scalar product and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/f06b81b731bd497af38154f7447638a84ce787f2.png) is length of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/5a3a683029365387cf086e592ebfccb0e126e88a.png).

Given the list of points, print the indices of the good points in ascending order.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1<=n<=10^{3} $ ) — the number of points.

The next $ n $ lines of input contain five integers $ a_{i},b_{i},c_{i},d_{i},e_{i} $ ( $ |a_{i}|,|b_{i}|,|c_{i}|,|d_{i}|,|e_{i}|<=10^{3} $ ) — the coordinates of the i-th point. All points are distinct.

## 输出格式

First, print a single integer $ k $ — the number of good points.

Then, print $ k $ integers, each on their own line — the indices of the good points in ascending order.

## 说明/提示

In the first sample, the first point forms exactly a ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/fe3c8011bb9ee15abb5ac0ee9f2f980eef59656c.png) angle with all other pairs of points, so it is good.

In the second sample, along the cd plane, we can see the points look as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/dc25f4e169ea69409034b12812dd7f4f82002152.png)

We can see that all angles here are acute, so no points are good.

## 样例 #1

### 输入

```
6
0 0 0 0 0
1 0 0 0 0
0 1 0 0 0
0 0 1 0 0
0 0 0 1 0
0 0 0 0 1

```

### 输出

```
1
1

```

## 样例 #2

### 输入

```
3
0 0 1 2 0
0 0 9 2 0
0 0 5 9 0

```

### 输出

```
0

```

