---
title: "Four Divisors"
layout: "post"
diff: 省选/NOI-
pid: CF665F
tag: []
---

# Four Divisors

## 题目描述

If an integer $ a $ is divisible by another integer $ b $ , then $ b $ is called the divisor of $ a $ .

For example: $ 12 $ has positive $ 6 $ divisors. They are $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 6 $ and $ 12 $ .

Let’s define a function $ D(n) $ — number of integers between $ 1 $ and $ n $ (inclusive) which has exactly four positive divisors.

Between $ 1 $ and $ 10 $ only the integers $ 6 $ , $ 8 $ and $ 10 $ has exactly four positive divisors. So, $ D(10)=3 $ .

You are given an integer $ n $ . You have to calculate $ D(n) $ .

## 输入格式

The only line contains integer $ n $ ( $ 1<=n<=10^{11} $ ) — the parameter from the problem statement.

## 输出格式

Print the only integer $ c $ — the number of integers between $ 1 $ and $ n $ with exactly four divisors.

## 样例 #1

### 输入

```
10

```

### 输出

```
3

```

## 样例 #2

### 输入

```
20

```

### 输出

```
5

```

