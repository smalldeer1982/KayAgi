---
title: "Restaurant"
layout: "post"
diff: 普及-
pid: CF597B
tag: []
---

# Restaurant

## 题目描述

A restaurant received $ n $ orders for the rental. Each rental order reserve the restaurant for a continuous period of time, the $ i $ -th order is characterized by two time values — the start time $ l_{i} $ and the finish time $ r_{i} $ ( $ l_{i}<=r_{i} $ ).

Restaurant management can accept and reject orders. What is the maximal number of orders the restaurant can accept?

No two accepted orders can intersect, i.e. they can't share even a moment of time. If one order ends in the moment other starts, they can't be accepted both.

## 输入格式

The first line contains integer number $ n $ ( $ 1<=n<=5·10^{5} $ ) — number of orders. The following $ n $ lines contain integer values $ l_{i} $ and $ r_{i} $ each ( $ 1<=l_{i}<=r_{i}<=10^{9} $ ).

## 输出格式

Print the maximal number of orders that can be accepted.

## 样例 #1

### 输入

```
2
7 11
4 7

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
4 5
5 6

```

### 输出

```
3

```

## 样例 #3

### 输入

```
6
4 8
1 5
4 7
2 5
1 3
6 8

```

### 输出

```
2

```

