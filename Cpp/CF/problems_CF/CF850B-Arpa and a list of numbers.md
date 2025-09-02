---
title: "Arpa and a list of numbers"
layout: "post"
diff: 提高+/省选-
pid: CF850B
tag: []
---

# Arpa and a list of numbers

## 题目描述

Arpa has found a list containing $ n $ numbers. He calls a list bad if and only if it is not empty and gcd (see notes section for more information) of numbers in the list is $ 1 $ .

Arpa can perform two types of operations:

- Choose a number and delete it with cost $ x $ .
- Choose a number and increase it by $ 1 $ with cost $ y $ .

Arpa can apply these operations to as many numbers as he wishes, and he is allowed to apply the second operation arbitrarily many times on the same number.

Help Arpa to find the minimum possible cost to make the list good.

## 输入格式

First line contains three integers $ n $ , $ x $ and $ y $ ( $ 1<=n<=5·10^{5} $ , $ 1<=x,y<=10^{9} $ ) — the number of elements in the list and the integers $ x $ and $ y $ .

Second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{6} $ ) — the elements of the list.

## 输出格式

Print a single integer: the minimum possible cost to make the list good.

## 说明/提示

In example, number $ 1 $ must be deleted (with cost $ 23 $ ) and number $ 16 $ must increased by $ 1 $ (with cost $ 17 $ ).

A gcd (greatest common divisor) of a set of numbers is the maximum integer that divides all integers in the set. Read more about gcd [here](https://en.wikipedia.org/wiki/Greatest_common_divisor).

## 样例 #1

### 输入

```
4 23 17
1 17 17 16

```

### 输出

```
40

```

## 样例 #2

### 输入

```
10 6 2
100 49 71 73 66 96 8 60 41 63

```

### 输出

```
10

```

