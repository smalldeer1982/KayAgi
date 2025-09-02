---
title: "Flights for Regular Customers"
layout: "post"
diff: 省选/NOI-
pid: CF576D
tag: []
---

# Flights for Regular Customers

## 题目描述

In the country there are exactly $ n $ cities numbered with positive integers from $ 1 $ to $ n $ . In each city there is an airport is located.

Also, there is the only one airline, which makes $ m $ flights. Unfortunately, to use them, you need to be a regular customer of this company, namely, you have the opportunity to enjoy flight $ i $ from city $ a_{i} $ to city $ b_{i} $ only if you have already made at least $ d_{i} $ flights before that.

Please note that flight $ i $ flies exactly from city $ a_{i} $ to city $ b_{i} $ . It can not be used to fly from city $ b_{i} $ to city $ a_{i} $ . An interesting fact is that there may possibly be recreational flights with a beautiful view of the sky, which begin and end in the same city.

You need to get from city $ 1 $ to city $ n $ . Unfortunately, you've never traveled by plane before. What minimum number of flights you have to perform in order to get to city $ n $ ?

Note that the same flight can be used multiple times.

## 输入格式

The first line contains two integers, $ n $ and $ m $ ( $ 2<=n<=150 $ , $ 1<=m<=150 $ ) — the number of cities in the country and the number of flights the company provides.

Next $ m $ lines contain numbers $ a_{i} $ , $ b_{i} $ , $ d_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ 0<=d_{i}<=10^{9} $ ), representing flight number $ i $ from city $ a_{i} $ to city $ b_{i} $ , accessible to only the clients who have made at least $ d_{i} $ flights.

## 输出格式

Print "Impossible" (without the quotes), if it is impossible to get from city $ 1 $ to city $ n $ using the airways.

But if there is at least one way, print a single integer — the minimum number of flights you need to make to get to the destination point.

## 样例 #1

### 输入

```
3 2
1 2 0
2 3 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 1
1 2 100500

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
3 3
2 1 0
2 3 6
1 2 0

```

### 输出

```
8

```

