---
title: "Good Sequences"
layout: "post"
diff: 普及+/提高
pid: CF264B
tag: ['动态规划 DP', '枚举', '最大公约数 gcd']
---

# Good Sequences

## 题目描述

Squirrel Liss is interested in sequences. She also has preferences of integers. She thinks $ n $ integers $ a_{1},a_{2},...,a_{n} $ are good.

Now she is interested in good sequences. A sequence $ x_{1},x_{2},...,x_{k} $ is called good if it satisfies the following three conditions:

- The sequence is strictly increasing, i.e. $ x_{i}&lt;x_{i+1} $ for each $ i $ $ (1<=i<=k-1) $ .
- No two adjacent elements are coprime, i.e. $ gcd(x_{i},x_{i+1})&gt;1 $ for each $ i $ $ (1<=i<=k-1) $ (where $ gcd(p,q) $ denotes the greatest common divisor of the integers $ p $ and $ q $ ).
- All elements of the sequence are good integers.

Find the length of the longest good sequence.

## 输入格式

The input consists of two lines. The first line contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of good integers. The second line contains a single-space separated list of good integers $ a_{1},a_{2},...,a_{n} $ in strictly increasing order ( $ 1<=a_{i}<=10^{5}; a_{i}&lt;a_{i+1} $ ).

## 输出格式

Print a single integer — the length of the longest good sequence.

## 说明/提示

In the first example, the following sequences are examples of good sequences: \[2; 4; 6; 9\], \[2; 4; 6\], \[3; 9\], \[6\]. The length of the longest good sequence is 4.

## 样例 #1

### 输入

```
5
2 3 4 6 9

```

### 输出

```
4

```

## 样例 #2

### 输入

```
9
1 2 3 5 6 7 8 9 10

```

### 输出

```
4

```

