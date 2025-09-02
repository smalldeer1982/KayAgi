---
title: "SORTBIT - Sorted bit squence"
layout: "post"
diff: 普及+/提高
pid: SP1182
tag: []
---

# SORTBIT - Sorted bit squence

## 题目描述

Let's consider the 32 bit representation of all integers i from m up to n inclusive (m ≤ i ≤ n; m × n ≥ 0, -2^31 ≤ m ≤ n ≤ 2^31-1). Note that a negative number is represented in 32 bit Additional Code. That is the 32 bit sequence, the binary sum of which and the 32 bit representation of the corresponding positive number is 2^32 (1 0000 0000 0000 0000 0000 0000 0000 0000 in binary).

For example, the 32 bit representation of 6 is  0000 0000 0000 0000 0000 0000 0000 0110

 and the 32 bit representation of -6 is 1111 1111 1111 1111 1111 1111 1111 1010

 because

  0000 0000 0000 0000 0000 0000 0000 0110 (6)   
\+   
 1111 1111 1111 1111 1111 1111 1111 1010 (-6)   
\-------------------------------------------------  
= 1 0000 0000 0000 0000 0000 0000 0000 0000 (2^32)

Let's sort the 32 bit representations of these numbers in increasing order of the number of bit 1. If two 32 bit representations that have the same number of bit 1, they are sorted in lexicographical order.

For example, with m = 0 and n = 5, the result of the sorting will be

  No.

  Decimal number

  Binary 32 bit representation

  1

  0

  0000 0000 0000 0000 0000 0000 0000 0000

  2

  1

  0000 0000 0000 0000 0000 0000 0000 0001

  3

  2

  0000 0000 0000 0000 0000 0000 0000 0010

  4

  4

  0000 0000 0000 0000 0000 0000 0000 0100

  5

  3

  0000 0000 0000 0000 0000 0000 0000 0011

  6

  5

  0000 0000 0000 0000 0000 0000 0000 0101

 with m = -5 and n = -2, the result of the sorting will be

  No.

  Decimal number

  Binary 32 bit representation

  1

  -4

  1111 1111 1111 1111 1111 1111 1111 1100

  2

  -5

  1111 1111 1111 1111 1111 1111 1111 1011

  3

  -3

  1111 1111 1111 1111 1111 1111 1111 1101

  4

  -2

  1111 1111 1111 1111 1111 1111 1111 1110

 Given m, n and k (1 ≤ k ≤ min{n − m + 1, 2 147 473 547}), your task is to write a program to find a number corresponding to k-th representation in the sorted sequence.

## 输入格式

 The input consists of several data sets. The first line of the input file contains the number of data sets which is a positive integer and is not bigger than 1000. The following lines describe the data sets.

 For each data set, the only line contains 3 integers m, n and k separated by space.

## 输出格式

 For each data set, write in one line the k-th number of the sorted numbers.

## 样例 #1

### 输入

```
2
0 5 3
-5 -2 2
```

### 输出

```
2
-5
```

