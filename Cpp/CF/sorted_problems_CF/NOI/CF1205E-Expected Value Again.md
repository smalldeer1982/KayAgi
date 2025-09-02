---
title: "Expected Value Again"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1205E
tag: []
---

# Expected Value Again

## 题目描述

You are given integers $ n $ , $ k $ . Let's consider the alphabet consisting of $ k $ different elements.

Let beauty $ f(s) $ of the string $ s $ be the number of indexes $ i $ , $ 1\le i<|s| $ , for which prefix of $ s $ of length $ i $ equals to suffix of $ s $ of length $ i $ . For example, beauty of the string $ abacaba $ equals $ 2 $ , as for $ i = 1, 3 $ prefix and suffix of length $ i $ are equal.

Consider all words of length $ n $ in the given alphabet. Find the expected value of $ f(s)^2 $ of a uniformly chosen at random word. We can show that it can be expressed as $ \frac{P}{Q} $ , where $ P $ and $ Q $ are coprime and $ Q $ isn't divided by $ 10^9 + 7 $ . Output $ P\cdot Q^{-1} \bmod 10^9 + 7 $ .

## 输入格式

The first and the only line contains two integers $ n $ , $ k $ ( $ 1\le n \le 10^5 $ , $ 1\le k\le 10^9 $ ) — the length of a string and the size of alphabet respectively.

## 输出格式

Output a single integer — $ P\times Q^{-1} \bmod 10^9 + 7 $ .

## 说明/提示

In the first example, there are $ 9 $ words of length $ 2 $ in alphabet of size $ 3 $ — $ aa $ , $ ab $ , $ ac $ , $ ba $ , $ bb $ , $ bc $ , $ ca $ , $ cb $ , $ cc $ . $ 3 $ of them have beauty $ 1 $ and $ 6 $ of them have beauty $ 0 $ , so the average value is $ \frac{1}{3} $ .

In the third example, there is only one such word, and it has beauty $ 99 $ , so the average value is $ 99^2 $ .

## 样例 #1

### 输入

```
2 3

```

### 输出

```
333333336

```

## 样例 #2

### 输入

```
1 5

```

### 输出

```
0

```

## 样例 #3

### 输入

```
100 1

```

### 输出

```
9801

```

## 样例 #4

### 输入

```
10 10

```

### 输出

```
412377396

```

