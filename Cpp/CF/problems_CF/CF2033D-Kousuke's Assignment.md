---
title: "Kousuke's Assignment"
layout: "post"
diff: 普及/提高-
pid: CF2033D
tag: ['动态规划 DP', '前缀和']
---

# Kousuke's Assignment

## 题目描述

After a trip with Sakurako, Kousuke was very scared because he forgot about his programming assignment. In this assignment, the teacher gave him an array $ a $ of $ n $ integers and asked him to calculate the number of non-overlapping segments of the array $ a $ , such that each segment is considered beautiful.

A segment $ [l,r] $ is considered beautiful if $ a_l + a_{l+1} + \dots + a_{r-1} + a_r=0 $ .

For a fixed array $ a $ , your task is to compute the maximum number of non-overlapping beautiful segments.

## 输入格式

The first line of input contains the number $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Each test case consists of $ 2 $ lines.

- The first line contains one integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the array.
- The second line contains $ n $ integers $ a_i $ ( $ -10^5 \le a_i \le 10^5 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 3\cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the maximum number of non-overlapping beautiful segments.

## 样例 #1

### 输入

```
3
5
2 1 -3 2 1
7
12 -4 4 43 -3 -5 8
6
0 -4 0 3 0 1
```

### 输出

```
1
2
3
```

