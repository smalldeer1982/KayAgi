---
title: "Thief in a Shop"
layout: "post"
diff: 省选/NOI-
pid: CF632E
tag: ['枚举', '排序', '背包 DP']
---

# Thief in a Shop

## 题目描述

A thief made his way to a shop.

As usual he has his lucky knapsack with him. The knapsack can contain $ k $ objects. There are $ n $ kinds of products in the shop and an infinite number of products of each kind. The cost of one product of kind $ i $ is $ a_{i} $ .

The thief is greedy, so he will take exactly $ k $ products (it's possible for some kinds to take several products of that kind).

Find all the possible total costs of products the thief can nick into his knapsack.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n,k<=1000 $ ) — the number of kinds of products and the number of products the thief will take.

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=1000 $ ) — the costs of products for kinds from $ 1 $ to $ n $ .

## 输出格式

Print the only line with all the possible total costs of stolen products, separated by a space. The numbers should be printed in the ascending order.

## 样例 #1

### 输入

```
3 2
1 2 3

```

### 输出

```
2 3 4 5 6

```

## 样例 #2

### 输入

```
5 5
1 1 1 1 1

```

### 输出

```
5

```

## 样例 #3

### 输入

```
3 3
3 5 11

```

### 输出

```
9 11 13 15 17 19 21 25 27 33

```

