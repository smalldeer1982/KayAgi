---
title: "Coins"
layout: "post"
diff: 普及-
pid: CF58B
tag: ['素数判断,质数,筛法']
---

# Coins

## 题目描述

In Berland a money reform is being prepared. New coins are being introduced. After long economic calculations was decided that the most expensive coin should possess the denomination of exactly $ n $ Berland dollars. Also the following restriction has been introduced for comfort: the denomination of each coin should be divisible by the denomination of any cheaper coin. It is known that among all the possible variants the variant with the largest number of new coins will be chosen. Find this variant. Print in the order of decreasing of the coins' denominations.

## 输入格式

The first and only line contains an integer $ n $ ( $ 1<=n<=10^{6} $ ) which represents the denomination of the most expensive coin.

## 输出格式

Print the denominations of all the coins in the order of decreasing. The number of coins must be the largest possible (with the given denomination $ n $ of the most expensive coin). Also, the denomination of every coin must be divisible by the denomination of any cheaper coin. Naturally, the denominations of all the coins should be different. If there are several solutins to that problem, print any of them.

## 样例 #1

### 输入

```
10

```

### 输出

```
10 5 1

```

## 样例 #2

### 输入

```
4

```

### 输出

```
4 2 1

```

## 样例 #3

### 输入

```
3

```

### 输出

```
3 1

```

