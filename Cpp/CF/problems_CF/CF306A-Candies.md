---
title: "Candies"
layout: "post"
diff: 入门
pid: CF306A
tag: []
---

# Candies

## 题目描述

Polycarpus has got $ n $ candies and $ m $ friends ( $ n>=m $ ). He wants to make a New Year present with candies to each friend. Polycarpus is planning to present all candies and he wants to do this in the fairest (that is, most equal) manner. He wants to choose such $ a_{i} $ , where $ a_{i} $ is the number of candies in the $ i $ -th friend's present, that the maximum $ a_{i} $ differs from the least $ a_{i} $ as little as possible.

For example, if $ n $ is divisible by $ m $ , then he is going to present the same number of candies to all his friends, that is, the maximum $ a_{i} $ won't differ from the minimum one.

## 输入格式

The single line of the input contains a pair of space-separated positive integers $ n $ , $ m $ ( $ 1<=n,m<=100;n>=m $ ) — the number of candies and the number of Polycarpus's friends.

## 输出格式

Print the required sequence $ a_{1},a_{2},...,a_{m} $ , where $ a_{i} $ is the number of candies in the $ i $ -th friend's present. All numbers $ a_{i} $ must be positive integers, total up to $ n $ , the maximum one should differ from the minimum one by the smallest possible value.

## 说明/提示

Print $ a_{i} $ in any order, separate the numbers by spaces.

## 样例 #1

### 输入

```
12 3

```

### 输出

```
4 4 4 
```

## 样例 #2

### 输入

```
15 4

```

### 输出

```
3 4 4 4 
```

## 样例 #3

### 输入

```
18 7

```

### 输出

```
2 2 2 3 3 3 3 
```

