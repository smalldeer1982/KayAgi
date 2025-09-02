---
title: "Divisibility Problem"
layout: "post"
diff: 入门
pid: CF1328A
tag: []
---

# Divisibility Problem

## 题目描述

You are given two positive integers $ a $ and $ b $ . In one move you can increase $ a $ by $ 1 $ (replace $ a $ with $ a+1 $ ). Your task is to find the minimum number of moves you need to do in order to make $ a $ divisible by $ b $ . It is possible, that you have to make $ 0 $ moves, as $ a $ is already divisible by $ b $ . You have to answer $ t $ independent test cases.

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then $ t $ test cases follow.

The only line of the test case contains two integers $ a $ and $ b $ ( $ 1 \le a, b \le 10^9 $ ).

## 输出格式

For each test case print the answer — the minimum number of moves you need to do in order to make $ a $ divisible by $ b $ .

## 样例 #1

### 输入

```
5
10 4
13 9
100 13
123 456
92 46
```

### 输出

```
2
5
4
333
0
```

