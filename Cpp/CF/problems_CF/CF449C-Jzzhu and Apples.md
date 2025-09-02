---
title: "Jzzhu and Apples"
layout: "post"
diff: 省选/NOI-
pid: CF449C
tag: ['枚举', '素数判断,质数,筛法', '栈']
---

# Jzzhu and Apples

## 题目描述

Jzzhu has picked $ n $ apples from his big apple tree. All the apples are numbered from $ 1 $ to $ n $ . Now he wants to sell them to an apple store.

Jzzhu will pack his apples into groups and then sell them. Each group must contain two apples, and the greatest common divisor of numbers of the apples in each group must be greater than 1. Of course, each apple can be part of at most one group.

Jzzhu wonders how to get the maximum possible number of groups. Can you help him?

## 输入格式

A single integer $ n $ $ (1<=n<=10^{5}) $ , the number of the apples.

## 输出格式

The first line must contain a single integer $ m $ , representing the maximum number of groups he can get. Each of the next $ m $ lines must contain two integers — the numbers of apples in the current group.

If there are several optimal answers you can print any of them.

## 样例 #1

### 输入

```
6

```

### 输出

```
2
6 3
2 4

```

## 样例 #2

### 输入

```
9

```

### 输出

```
3
9 3
2 4
6 8

```

## 样例 #3

### 输入

```
2

```

### 输出

```
0

```

