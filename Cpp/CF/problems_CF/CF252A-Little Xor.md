---
title: "Little Xor"
layout: "post"
diff: 普及-
pid: CF252A
tag: ['博弈论', '枚举', '前缀和']
---

# Little Xor

## 题目描述

Little Petya likes arrays that consist of non-negative integers a lot. Recently his mom has presented him one such array consisting of $ n $ elements. Petya immediately decided to find there a segment of consecutive elements, such that the $ xor $ of all numbers from this segment was maximal possible. Help him with that.

The $ xor $ operation is the bitwise exclusive "OR", that is denoted as "xor" in Pascal and "^" in C/C++/Java.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=100 $ ) — the number of elements in the array. The second line contains the space-separated integers from the array. All numbers are non-negative integers strictly less than $ 2^{30} $ .

## 输出格式

Print a single integer — the required maximal $ xor $ of a segment of consecutive elements.

## 说明/提示

In the first sample one of the optimal segments is the segment that consists of the first and the second array elements, if we consider the array elements indexed starting from one.

The second sample contains only one optimal segment, which contains exactly one array element (element with index three).

## 样例 #1

### 输入

```
5
1 2 1 1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
1 2 7

```

### 输出

```
7

```

## 样例 #3

### 输入

```
4
4 2 4 8

```

### 输出

```
14

```

