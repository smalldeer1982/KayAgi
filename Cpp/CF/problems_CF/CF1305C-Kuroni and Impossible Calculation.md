---
title: "Kuroni and Impossible Calculation"
layout: "post"
diff: 普及+/提高
pid: CF1305C
tag: []
---

# Kuroni and Impossible Calculation

## 题目描述

To become the king of Codeforces, Kuroni has to solve the following problem.

He is given $ n $ numbers $ a_1, a_2, \dots, a_n $ . Help Kuroni to calculate $ \prod_{1\le i<j\le n} |a_i - a_j| $ . As result can be very big, output it modulo $ m $ .

If you are not familiar with short notation, $ \prod_{1\le i<j\le n} |a_i - a_j| $ is equal to $ |a_1 - a_2|\cdot|a_1 - a_3|\cdot $ $ \dots $ $ \cdot|a_1 - a_n|\cdot|a_2 - a_3|\cdot|a_2 - a_4|\cdot $ $ \dots $ $ \cdot|a_2 - a_n| \cdot $ $ \dots $ $ \cdot |a_{n-1} - a_n| $ . In other words, this is the product of $ |a_i - a_j| $ for all $ 1\le i < j \le n $ .

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 2\le n \le 2\cdot 10^5 $ , $ 1\le m \le 1000 $ ) — number of numbers and modulo.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^9 $ ).

## 输出格式

Output the single number — $ \prod_{1\le i<j\le n} |a_i - a_j| \bmod m $ .

## 说明/提示

In the first sample, $ |8 - 5| = 3 \equiv 3 \bmod 10 $ .

In the second sample, $ |1 - 4|\cdot|1 - 5|\cdot|4 - 5| = 3\cdot 4 \cdot 1 = 12 \equiv 0 \bmod 12 $ .

In the third sample, $ |1 - 4|\cdot|1 - 9|\cdot|4 - 9| = 3 \cdot 8 \cdot 5 = 120 \equiv 1 \bmod 7 $ .

## 样例 #1

### 输入

```
2 10
8 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 12
1 4 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3 7
1 4 9
```

### 输出

```
1
```

