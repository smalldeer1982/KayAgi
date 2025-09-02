---
title: "Count Pairs"
layout: "post"
diff: 提高+/省选-
pid: CF1188B
tag: []
---

# Count Pairs

## 题目描述

You are given a prime number $ p $ , $ n $ integers $ a_1, a_2, \ldots, a_n $ , and an integer $ k $ .

Find the number of pairs of indexes $ (i, j) $ ( $ 1 \le i < j \le n $ ) for which $ (a_i + a_j)(a_i^2 + a_j^2) \equiv k \bmod p $ .

## 输入格式

The first line contains integers $ n, p, k $ ( $ 2 \le n \le 3 \cdot 10^5 $ , $ 2 \le p \le 10^9 $ , $ 0 \le k \le p-1 $ ). $ p $ is guaranteed to be prime.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le p-1 $ ). It is guaranteed that all elements are different.

## 输出格式

Output a single integer — answer to the problem.

## 说明/提示

In the first example:

 $ (0+1)(0^2 + 1^2) = 1 \equiv 1 \bmod 3 $ .

 $ (0+2)(0^2 + 2^2) = 8 \equiv 2 \bmod 3 $ .

 $ (1+2)(1^2 + 2^2) = 15 \equiv 0 \bmod 3 $ .

So only $ 1 $ pair satisfies the condition.

In the second example, there are $ 3 $ such pairs: $ (1, 5) $ , $ (2, 3) $ , $ (4, 6) $ .

## 样例 #1

### 输入

```
3 3 0
0 1 2

```

### 输出

```
1
```

## 样例 #2

### 输入

```
6 7 2
1 2 3 4 5 6

```

### 输出

```
3
```

