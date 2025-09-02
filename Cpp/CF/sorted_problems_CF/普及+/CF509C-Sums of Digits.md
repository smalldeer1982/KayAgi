---
title: "Sums of Digits"
layout: "post"
diff: 普及+/提高
pid: CF509C
tag: ['构造']
---

# Sums of Digits

## 题目描述

Vasya had a strictly increasing sequence of positive integers $ a_{1} $ , ..., $ a_{n} $ . Vasya used it to build a new sequence $ b_{1} $ , ..., $ b_{n} $ , where $ b_{i} $ is the sum of digits of $ a_{i} $ 's decimal representation. Then sequence $ a_{i} $ got lost and all that remained is sequence $ b_{i} $ .

Vasya wonders what the numbers $ a_{i} $ could be like. Of all the possible options he likes the one sequence with the minimum possible last number $ a_{n} $ . Help Vasya restore the initial sequence.

It is guaranteed that such a sequence always exists.

## 输入格式

The first line contains a single integer number $ n $ ( $ 1<=n<=300 $ ).

Next $ n $ lines contain integer numbers $ b_{1} $ , ..., $ b_{n} $ — the required sums of digits. All $ b_{i} $ belong to the range $ 1<=b_{i}<=300 $ .

## 输出格式

Print $ n $ integer numbers, one per line — the correct option for numbers $ a_{i} $ , in order of following in sequence. The sequence should be strictly increasing. The sum of digits of the $ i $ -th number should be equal to $ b_{i} $ .

If there are multiple sequences with least possible number $ a_{n} $ , print any of them. Print the numbers without leading zeroes.

## 样例 #1

### 输入

```
3
1
2
3

```

### 输出

```
1
2
3

```

## 样例 #2

### 输入

```
3
3
2
1

```

### 输出

```
3
11
100

```

