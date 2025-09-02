---
title: "Cashback"
layout: "post"
diff: 提高+/省选-
pid: CF940E
tag: ['动态规划 DP', '单调队列', '队列']
---

# Cashback

## 题目描述

Since you are the best Wraith King, Nizhniy Magazin «Mir» at the centre of Vinnytsia is offering you a discount.

You are given an array $ a $ of length $ n $ and an integer $ c $ .

The value of some array $ b $ of length $ k $ is the sum of its elements except for the ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF940E/7767e68a87566f0732f029bd691b100b0a741ae2.png) smallest. For example, the value of the array $ [3,1,6,5,2] $ with $ c=2 $ is $ 3+6+5=14 $ .

Among all possible partitions of $ a $ into contiguous subarrays output the smallest possible sum of the values of these subarrays.

## 输入格式

The first line contains integers $ n $ and $ c $ ( $ 1<=n,c<=100000 $ ).

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ) — elements of $ a $ .

## 输出格式

Output a single integer — the smallest possible sum of values of these subarrays of some partition of $ a $ .

## 说明/提示

In the first example any partition yields 6 as the sum.

In the second example one of the optimal partitions is $ [1,1],[10,10,10,10,10,10,9,10,10,10] $ with the values 2 and 90 respectively.

In the third example one of the optimal partitions is $ [2,3],[6,4,5,7],[1] $ with the values 3, 13 and 1 respectively.

In the fourth example one of the optimal partitions is $ [1],[3,4,5,5,3,4],[1] $ with the values 1, 21 and 1 respectively.

## 样例 #1

### 输入

```
3 5
1 2 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
12 10
1 1 10 10 10 10 10 10 9 10 10 10

```

### 输出

```
92

```

## 样例 #3

### 输入

```
7 2
2 3 6 4 5 7 1

```

### 输出

```
17

```

## 样例 #4

### 输入

```
8 4
1 3 4 5 5 3 4 1

```

### 输出

```
23

```

