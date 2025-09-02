---
title: "MOD - Power Modulo Inverted"
layout: "post"
diff: 省选/NOI-
pid: SP3105
tag: ['枚举', '分块']
---

# MOD - Power Modulo Inverted

## 题目描述

Given 3 positive integers _x_, _y_ and _z_, you can find _k = x $ ^{y} $ %z_ easily, by fast power-modulo algorithm. Now your task is the inverse of this algorithm. Given 3 positive integers _x_, _z_ and _k_, find the smallest non-negative integer _y_, such that _k%z = x $ ^{y} $ %z_.

## 输入格式

About 600 test cases.

Each test case contains one line with 3 integers _x_, _z_ and _k_.(1<= _x_, _z_, _k_ <=10 $ ^{9} $ )

Input terminates by three zeroes.

## 输出格式

For each test case, output one line with the answer, or "No Solution"(without quotes) if such an integer doesn't exist.

## 样例 #1

### 输入

```
5 58 33
2 4 3
0 0 0
```

### 输出

```
9
No Solution
```

