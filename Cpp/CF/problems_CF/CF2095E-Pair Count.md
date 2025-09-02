---
title: "Pair Count"
layout: "post"
diff: 难度0
pid: CF2095E
tag: []
---

# Pair Count

## 题目描述

You are given a prime number $ p $ , $ n $ integers $ a_1, a_2, \ldots, a_n $ , and an integer $ k $ .

Find the number of pairs of indexes $ (i, j) $ ( $ 1 \le i < j \le n $ ) for which $ (a_i \oplus a_j)(a_i^2 \oplus a_j^2) \equiv k \bmod p $ .

Here $ \oplus $ denotes the [bitwise XOR operation](https://word.rodeo/?utm_source=share#cvMcraT7fZ6Yj3T3fwWbp8jppto8Pan9HXzC5fWYjPCCvqUMqseEkRFkzttufIM=).

## 输入格式

The first line contains integers $ n, p, k $ ( $ 2 \le n \le 3 \cdot 10^5 $ , $ 2 \le p \le 10^9 $ , $ 0 \le k \le p-1 $ ). $ p $ is guaranteed to be prime.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le p-1 $ ). It is guaranteed that all elements are different.

## 输出格式

Output a single integer — answer to the problem.

## 说明/提示

In the first example:

 $ (0\oplus1)(0^2 \oplus 1^2) = 1 \equiv 1 \bmod 3 $ .

 $ (0\oplus2)(0^2 \oplus 2^2) = 8 \equiv 2 \bmod 3 $ .

 $ (1\oplus2)(1^2 \oplus 2^2) = 15 \equiv 0 \bmod 3 $ .

So only $ 1 $ pair satisfies the condition.

In the second example, there are $ 3 $ such pairs: $ (1, 5) $ , $ (1, 6) $ , $ (3, 6) $ .

## 样例 #1

### 输入

```
3 3 2
0 1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6 11 2
1 3 5 6 7 8
```

### 输出

```
3
```

