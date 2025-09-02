---
title: "Numbers"
layout: "post"
diff: 普及+/提高
pid: CF213B
tag: ['动态规划 DP', '枚举', '组合数学']
---

# Numbers

## 题目描述

Furik loves writing all sorts of problems, especially such that he can't solve himself. You've got one of his problems, the one Furik gave to Rubik. And Rubik asks you to solve it.

There is integer $ n $ and array $ a $ , consisting of ten integers, indexed by numbers from 0 to 9. Your task is to count the number of positive integers with the following properties:

- the number's length does not exceed $ n $ ;
- the number doesn't have leading zeroes;
- digit $ i $ $ (0<=i<=9) $ occurs in the number at least $ a[i] $ times.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=100) $ . The next line contains 10 integers $ a[0] $ , $ a[1] $ , $ ... $ , $ a[9] $ $ (0<=a[i]<=100) $ — elements of array $ a $ . The numbers are separated by spaces.

## 输出格式

On a single line print the remainder of dividing the answer to the problem by $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample number 9 meets the requirements.

In the second sample number 10 meets the requirements.

In the third sample numbers 10, 110, 210, 120, 103 meet the requirements. There are other suitable numbers, 36 in total.

## 样例 #1

### 输入

```
1
0 0 0 0 0 0 0 0 0 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
1 1 0 0 0 0 0 0 0 0

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3
1 1 0 0 0 0 0 0 0 0

```

### 输出

```
36

```

