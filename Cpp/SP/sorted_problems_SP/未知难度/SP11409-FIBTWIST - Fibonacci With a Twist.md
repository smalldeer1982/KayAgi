---
title: "FIBTWIST - Fibonacci With a Twist"
layout: "post"
diff: 难度0
pid: SP11409
tag: []
---

# FIBTWIST - Fibonacci With a Twist

## 题目描述

Fibonacci numbers are given by

- f(n) = f(n-1) + f(n-2)

with f(0) = 0 & f(1) = 1.

first number of series ------ 0 1 1 2 3 5 8 13

Now let's have a new series called "Fibonacci Twist" which is given by

- ft(n) = ft(n-1) + ft(n-2) + (n-1)

with ft(0) = 0 & ft(1) = 1.

with first few number in the series ----- 0 1 2 5 10 19 34 59

Now your task is to find ft(n).

Since the number can be Big you have to find the result mod M.

## 输入格式

first line having single number 't' -- number of test cases.

next t lines have 2 number each 'n' and 'M'

## 输出格式

Single number given the n-th term mod M

## 样例 #1

### 输入

```
3
5 20
10 77
15 111
```

### 输出

```
19
45
69
```

