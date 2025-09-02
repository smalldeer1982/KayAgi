---
title: "Candy Bags"
layout: "post"
diff: 普及-
pid: CF334A
tag: []
---

# Candy Bags

## 题目描述

Gerald has $ n $ younger brothers and their number happens to be even. One day he bought $ n^{2} $ candy bags. One bag has one candy, one bag has two candies, one bag has three candies and so on. In fact, for each integer $ k $ from $ 1 $ to $ n^{2} $ he has exactly one bag with $ k $ candies.

Help him give $ n $ bags of candies to each brother so that all brothers got the same number of candies.

## 输入格式

The single line contains a single integer $ n $ ( $ n $ is even, $ 2<=n<=100 $ ) — the number of Gerald's brothers.

## 输出格式

Let's assume that Gerald indexes his brothers with numbers from $ 1 $ to $ n $ . You need to print $ n $ lines, on the $ i $ -th line print $ n $ integers — the numbers of candies in the bags for the $ i $ -th brother. Naturally, all these numbers should be distinct and be within limits from $ 1 $ to $ n^{2} $ . You can print the numbers in the lines in any order.

It is guaranteed that the solution exists at the given limits.

## 说明/提示

The sample shows Gerald's actions if he has two brothers. In this case, his bags contain 1, 2, 3 and 4 candies. He can give the bags with 1 and 4 candies to one brother and the bags with 2 and 3 to the other brother.

## 样例 #1

### 输入

```
2

```

### 输出

```
1 4
2 3

```

