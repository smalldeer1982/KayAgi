---
title: "Exponential Equation"
layout: "post"
diff: 入门
pid: CF1787A
tag: []
---

# Exponential Equation

## 题目描述

You are given an integer $ n $ .

Find any pair of integers $ (x,y) $ ( $ 1\leq x,y\leq n $ ) such that $ x^y\cdot y+y^x\cdot x = n $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1\leq t\leq 10^4 $ ) — the number of test cases.

Each test case contains one line with a single integer $ n $ ( $ 1\leq n\leq 10^9 $ ).

## 输出格式

For each test case, if possible, print two integers $ x $ and $ y $ ( $ 1\leq x,y\leq n $ ). If there are multiple answers, print any.

Otherwise, print $ -1 $ .

## 说明/提示

In the third test case, $ 2^3 \cdot 3+3^2 \cdot 2 = 42 $ , so $ (2,3),(3,2) $ will be considered as legal solutions.

In the fourth test case, $ 5^5 \cdot 5+5^5 \cdot 5 = 31250 $ , so $ (5,5) $ is a legal solution.

## 样例 #1

### 输入

```
5
3
7
42
31250
20732790
```

### 输出

```
-1
-1
2 3
5 5
3 13
```

