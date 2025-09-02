---
title: "Joty and Chocolate"
layout: "post"
diff: 普及/提高-
pid: CF678C
tag: []
---

# Joty and Chocolate

## 题目描述

Little Joty has got a task to do. She has a line of $ n $ tiles indexed from $ 1 $ to $ n $ . She has to paint them in a strange pattern.

An unpainted tile should be painted Red if it's index is divisible by $ a $ and an unpainted tile should be painted Blue if it's index is divisible by $ b $ . So the tile with the number divisible by $ a $ and $ b $ can be either painted Red or Blue.

After her painting is done, she will get $ p $ chocolates for each tile that is painted Red and $ q $ chocolates for each tile that is painted Blue.

Note that she can paint tiles in any order she wants.

Given the required information, find the maximum number of chocolates Joty can get.

## 输入格式

The only line contains five integers $ n $ , $ a $ , $ b $ , $ p $ and $ q $ ( $ 1<=n,a,b,p,q<=10^{9} $ ).

## 输出格式

Print the only integer $ s $ — the maximum number of chocolates Joty can get.

Note that the answer can be too large, so you should use $ 64 $ -bit integer type to store it. In C++ you can use the long long integer type and in Java you can use long integer type.

## 样例 #1

### 输入

```
5 2 3 12 15

```

### 输出

```
39

```

## 样例 #2

### 输入

```
20 2 3 3 5

```

### 输出

```
51

```

