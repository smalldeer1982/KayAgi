---
title: "The Time"
layout: "post"
diff: 普及-
pid: CF622B
tag: []
---

# The Time

## 题目描述

You are given the current time in $ 24 $ -hour format hh:mm. Find and print the time after $ a $ minutes.

Note that you should find only the time after $ a $ minutes, see the examples to clarify the problem statement.

You can read more about $ 24 $ -hour format here [https://en.wikipedia.org/wiki/24-hour\_clock](https://en.wikipedia.org/wiki/24-hour_clock).

## 输入格式

The first line contains the current time in the format hh:mm ( $ 0<=hh&lt;24,0<=mm&lt;60 $ ). The hours and the minutes are given with two digits (the hours or the minutes less than $ 10 $ are given with the leading zeroes).

The second line contains integer $ a $ ( $ 0<=a<=10^{4} $ ) — the number of the minutes passed.

## 输出格式

The only line should contain the time after $ a $ minutes in the format described in the input. Note that you should print exactly two digits for the hours and the minutes (add leading zeroes to the numbers if needed).

See the examples to check the input/output format.

## 样例 #1

### 输入

```
23:59
10

```

### 输出

```
00:09

```

## 样例 #2

### 输入

```
20:20
121

```

### 输出

```
22:21

```

## 样例 #3

### 输入

```
10:10
0

```

### 输出

```
10:10

```

