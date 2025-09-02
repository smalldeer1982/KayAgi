---
title: "Mars"
layout: "post"
diff: 省选/NOI-
pid: CF1599F
tag: []
---

# Mars

## 题目描述

In the year 2420 humans have finally built a colony on Mars thanks to the work of Elon Tusk. There are $ 10^9+7 $ cities arranged in a circle in this colony and none of them are connected yet. Elon Tusk wants to connect some of those cities using only roads of the same size in order to lower the production cost of those roads. Because of that he gave a list on N cites where some cites can appear more than once and Q queries that you need to answer. For the query you need to determine if it is possible to connect all the cities from $ L_{i} $ to $ R_{i} $ on that list using only roads of length $ D_{i} $ .

## 输入格式

The first line contains two integers $ N $ and $ Q $ ( $ 1 \leq N, Q \leq 2\cdot10^5 $ ) — the length of the array of cities and the number of queries you need to answer.

The second lines contains $ N $ integers representing the array of cites. Next Q lines contain three integers $ L, R $ and $ D $ ( $ 1 \leq L_{i}, R_{i} \leq N $ , $ 0 \leq D_{i} \leq 10^9+6 $ ) — the range of cities that needs to be connected and the length of the road that you can use.

## 输出格式

The output contains Q lines. If it is possible to connect all the cities from the i-th query can be connected with roads of length $ D_{i} $ the i-th line should contain the word "Yes", otherwise it should contain the word "No".

## 说明/提示

In the $ 5^{th} $ query of the first test case we can connect cities in this order 0-2-4-6-8-10-12 this way distance between any two connected cities is 2. In the second test case we can connect cities in this order 21-14-7-0 this way distance between any two connected cities is $ 10^9 $ module $ 10^9+7 $ .

## 样例 #1

### 输入

```
9 8
17 0 12 6 10 8 2 4 5
2 3 12
2 3 6
2 4 6
4 6 2
2 8 2
1 2 17
1 8 2
9 9 14
```

### 输出

```
Yes
No
Yes
Yes
Yes
Yes
No
Yes
```

## 样例 #2

### 输入

```
4 1
7 21 14 0
1 4 1000000000
```

### 输出

```
Yes
```

