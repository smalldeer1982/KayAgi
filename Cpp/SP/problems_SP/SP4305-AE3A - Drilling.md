---
title: "AE3A - Drilling"
layout: "post"
diff: 省选/NOI-
pid: SP4305
tag: []
---

# AE3A - Drilling

## 题目描述

Byteman has asked you for help. He has divided the segment connecting points A and B into n+1 segments of equal length. If we assume that point A has coordinate 0, and point B coordinate n + 1, then there are n points with coordinates 1, 2, . . . , n between them. It is enough to find the farthest from A of these points in which some crude oil occurs. Byteman has informed you about the amounts of time necessary for making boreholes in these points — they are equal to t $ _{1} $ , t $ _{2} $ , . . . , t $ _{n} $ respectively. You should create such a plan of drilling, that the time necessary to identify the oil reservoir’s boundary is shortest possible, assuming the worst-case scenario.

## 输入格式

The first line of the standard input contains a single positive integer n (1 ≤ n ≤ 2000). The second line contains n positive integers t1, t2, . . . , tn separated by single spaces (1 ≤ t $ _{i} $ ≤ 10 $ ^{6} $ ).

## 输出格式

Your program should write a single integer to the standard output—the smallest amount of time that Byteman has to spend (assuming the worst-case scenario) drilling in search of oil, to be sure that he will identify the reservoir’s boundary.

## 样例 #1

### 输入

```
4
8 24 12 6

```

### 输出

```
42

```

