---
title: "Travelling Salesman Problem"
layout: "post"
diff: 提高+/省选-
pid: CF1503C
tag: []
---

# Travelling Salesman Problem

## 题目描述

There are $ n $ cities numbered from $ 1 $ to $ n $ , and city $ i $ has beauty $ a_i $ .

A salesman wants to start at city $ 1 $ , visit every city exactly once, and return to city $ 1 $ .

For all $ i\ne j $ , a flight from city $ i $ to city $ j $ costs $ \max(c_i,a_j-a_i) $ dollars, where $ c_i $ is the price floor enforced by city $ i $ . Note that there is no absolute value. Find the minimum total cost for the salesman to complete his trip.

## 输入格式

The first line contains a single integer $ n $ ( $ 2\le n\le 10^5 $ ) — the number of cities.

The $ i $ -th of the next $ n $ lines contains two integers $ a_i $ , $ c_i $ ( $ 0\le a_i,c_i\le 10^9 $ ) — the beauty and price floor of the $ i $ -th city.

## 输出格式

Output a single integer — the minimum total cost.

## 说明/提示

In the first test case, we can travel in order $ 1\to 3\to 2\to 1 $ .

- The flight $ 1\to 3 $ costs $ \max(c_1,a_3-a_1)=\max(9,4-1)=9 $ .
- The flight $ 3\to 2 $ costs $ \max(c_3, a_2-a_3)=\max(1,2-4)=1 $ .
- The flight $ 2\to 1 $ costs $ \max(c_2,a_1-a_2)=\max(1,1-2)=1 $ .

The total cost is $ 11 $ , and we cannot do better.

## 样例 #1

### 输入

```
3
1 9
2 1
4 1
```

### 输出

```
11
```

## 样例 #2

### 输入

```
6
4 2
8 4
3 0
2 3
7 1
0 1
```

### 输出

```
13
```

