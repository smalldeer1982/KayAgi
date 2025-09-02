---
title: "Goods transportation"
layout: "post"
diff: 省选/NOI-
pid: CF724E
tag: []
---

# Goods transportation

## 题目描述

There are $ n $ cities located along the one-way road. Cities are numbered from $ 1 $ to $ n $ in the direction of the road.

The $ i $ -th city had produced $ p_{i} $ units of goods. No more than $ s_{i} $ units of goods can be sold in the $ i $ -th city.

For each pair of cities $ i $ and $ j $ such that  $ 1<=i&lt;j<=n $  you can no more than once transport no more than $ c $ units of goods from the city $ i $ to the city $ j $ . Note that goods can only be transported from a city with a lesser index to the city with a larger index. You can transport goods between cities in any order.

Determine the maximum number of produced goods that can be sold in total in all the cities after a sequence of transportations.

## 输入格式

The first line of the input contains two integers $ n $ and $ c $ ( $ 1<=n<=10000 $ , $ 0<=c<=10^{9} $ ) — the number of cities and the maximum amount of goods for a single transportation.

The second line contains $ n $ integers $ p_{i} $ ( $ 0<=p_{i}<=10^{9} $ ) — the number of units of goods that were produced in each city.

The third line of input contains $ n $ integers $ s_{i} $ ( $ 0<=s_{i}<=10^{9} $ ) — the number of units of goods that can be sold in each city.

## 输出格式

Print the maximum total number of produced goods that can be sold in all cities after a sequence of transportations.

## 样例 #1

### 输入

```
3 0
1 2 3
3 2 1

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 1
7 4 2 1 0
1 2 3 4 5

```

### 输出

```
12

```

## 样例 #3

### 输入

```
4 3
13 10 7 4
4 7 10 13

```

### 输出

```
34

```

