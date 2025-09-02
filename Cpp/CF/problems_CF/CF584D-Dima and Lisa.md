---
title: "Dima and Lisa"
layout: "post"
diff: 普及+/提高
pid: CF584D
tag: []
---

# Dima and Lisa

## 题目描述

Dima loves representing an odd number as the sum of multiple primes, and Lisa loves it when there are at most three primes. Help them to represent the given number as the sum of at most than three primes.

More formally, you are given an odd numer $ n $ . Find a set of numbers $ p_{i} $ ( $ 1<=i<=k $ ), such that

1. $ 1<=k<=3 $
2. $ p_{i} $ is a prime
3. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF584D/e7615e00ba022b6aedbad362df530b3fd81c2681.png)

The numbers $ p_{i} $ do not necessarily have to be distinct. It is guaranteed that at least one possible solution exists.

## 输入格式

The single line contains an odd number $ n $ ( $ 3<=n<10^{9} $ ).

## 输出格式

In the first line print $ k $ $ (1<=k<=3) $ , showing how many numbers are in the representation you found.

In the second line print numbers $ p_{i} $ in any order. If there are multiple possible solutions, you can print any of them.

## 说明/提示

A prime is an integer strictly larger than one that is divisible only by one and by itself.

## 样例 #1

### 输入

```
27

```

### 输出

```
3
5 11 11

```

