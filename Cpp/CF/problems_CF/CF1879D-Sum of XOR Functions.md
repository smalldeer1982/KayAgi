---
title: "Sum of XOR Functions"
layout: "post"
diff: 普及+/提高
pid: CF1879D
tag: []
---

# Sum of XOR Functions

## 题目描述

You are given an array $ a $ of length $ n $ consisting of non-negative integers.

You have to calculate the value of $ \sum_{l=1}^{n} \sum_{r=l}^{n} f(l, r) \cdot (r - l + 1) $ , where $ f(l, r) $ is $ a_l \oplus a_{l+1} \oplus \dots \oplus a_{r-1} \oplus a_r $ (the character $ \oplus $ denotes bitwise XOR).

Since the answer can be very large, print it modulo $ 998244353 $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^9) $ .

## 输出格式

Print the one integer — the value of $ \sum_{l=1}^{n} \sum_{r=l}^{n} f(l, r) \cdot (r - l + 1) $ , taken modulo $ 998244353 $ .

## 说明/提示

In the first example, the answer is equal to $ f(1, 1) + 2 \cdot f(1, 2) + 3 \cdot f(1, 3) + f(2, 2) + 2 \cdot f(2, 3) + f(3, 3) =  $ $ = 1 + 2 \cdot 2 + 3 \cdot 0 + 3 + 2 \cdot 1 + 2 = 12 $ .

## 样例 #1

### 输入

```
3
1 3 2
```

### 输出

```
12
```

## 样例 #2

### 输入

```
4
39 68 31 80
```

### 输出

```
1337
```

## 样例 #3

### 输入

```
7
313539461 779847196 221612534 488613315 633203958 394620685 761188160
```

### 输出

```
257421502
```

