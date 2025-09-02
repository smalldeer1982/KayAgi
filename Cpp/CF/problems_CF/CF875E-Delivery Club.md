---
title: "Delivery Club"
layout: "post"
diff: 省选/NOI-
pid: CF875E
tag: []
---

# Delivery Club

## 题目描述

Petya and Vasya got employed as couriers. During the working day they are to deliver packages to $ n $ different points on the line. According to the company's internal rules, the delivery of packages must be carried out strictly in a certain order. Initially, Petya is at the point with the coordinate $ s_{1} $ , Vasya is at the point with the coordinate $ s_{2} $ , and the clients are at the points $ x_{1},x_{2},...,x_{n} $ in the order of the required visit.

The guys agree in advance who of them will deliver the package to which of the customers, and then they act as follows. When the package for the $ i $ -th client is delivered, the one who delivers the package to the $ (i+1) $ -st client is sent to the path (it can be the same person who went to the point $ x_{i} $ , or the other). The friend who is not busy in delivering the current package, is standing still.

To communicate with each other, the guys have got walkie-talkies. The walkie-talkies work rather poorly at great distances, so Petya and Vasya want to distribute the orders so that the maximum distance between them during the day is as low as possible. Help Petya and Vasya to minimize the maximum distance between them, observing all delivery rules.

## 输入格式

The first line contains three integers $ n $ , $ s_{1} $ , $ s_{2} $ ( $ 1<=n<=100000 $ , $ 0<=s_{1},s_{2}<=10^{9} $ ) — number of points of delivery and starting positions of Petya and Vasya.

The second line contains $ n $ integers $ x_{1},x_{2},...,x_{n} $ — customers coordinates ( $ 0<=x_{i}<=10^{9} $ ), in the order to make a delivery.

It is guaranteed, that among the numbers $ s_{1},s_{2},x_{1},...,x_{n} $ there are no two equal.

## 输出格式

Output the only integer, minimum possible maximal distance between couriers during delivery.

## 说明/提示

In the first test case the initial distance between the couriers is $ 10 $ . This value will be the answer, for example, Petya can perform both deliveries, and Vasya will remain at the starting point.

In the second test case you can optimally act, for example, like this: Vasya delivers the package to the first customer, Petya to the second and, finally, Vasya delivers the package to the third client. With this order of delivery, the distance between the couriers will never exceed $ 1 $ .

In the third test case only two variants are possible: if the delivery of a single package is carried out by Petya, the maximum distance between them will be $ 5-2=3 $ . If Vasya will deliver the package, the maximum distance is $ 4-2=2 $ . The latter method is optimal.

## 样例 #1

### 输入

```
2 0 10
5 6

```

### 输出

```
10

```

## 样例 #2

### 输入

```
3 2 1
3 4 5

```

### 输出

```
1

```

## 样例 #3

### 输入

```
1 4 5
2

```

### 输出

```
2

```

