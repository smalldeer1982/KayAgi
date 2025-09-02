---
title: "Lengthening Sticks"
layout: "post"
diff: 提高+/省选-
pid: CF571A
tag: ['枚举', '容斥原理']
---

# Lengthening Sticks

## 题目描述

You are given three sticks with positive integer lengths of $ a,b $ , and $ c $ centimeters. You can increase length of some of them by some positive integer number of centimeters (different sticks can be increased by a different length), but in total by at most $ l $ centimeters. In particular, it is allowed not to increase the length of any stick.

Determine the number of ways to increase the lengths of some sticks so that you can form from them a non-degenerate (that is, having a positive area) triangle. Two ways are considered different, if the length of some stick is increased by different number of centimeters in them.

## 输入格式

The single line contains $ 4 $ integers $ a,b,c,l $ ( $ 1<=a,b,c<=3·10^{5} $ , $ 0<=l<=3·10^{5} $ ).

## 输出格式

Print a single integer — the number of ways to increase the sizes of the sticks by the total of at most $ l $ centimeters, so that you can make a non-degenerate triangle from it.

## 说明/提示

In the first sample test you can either not increase any stick or increase any two sticks by $ 1 $ centimeter.

In the second sample test you can increase either the first or the second stick by one centimeter. Note that the triangle made from the initial sticks is degenerate and thus, doesn't meet the conditions.

## 样例 #1

### 输入

```
1 1 1 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
1 2 3 1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
10 2 1 7

```

### 输出

```
0

```

