---
title: "Mahmoud and Ehab and yet another xor task"
layout: "post"
diff: 提高+/省选-
pid: CF959F
tag: ['排序', '线性基']
---

# Mahmoud and Ehab and yet another xor task

## 题目描述

Ehab has an array $ a $ of $ n $ integers. He likes the [bitwise-xor operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) and he likes to bother Mahmoud so he came up with a problem. He gave Mahmoud $ q $ queries. In each of them, he gave Mahmoud 2 integers $ l $ and $ x $ , and asked him to find the number of subsequences of the first $ l $ elements of the array such that their bitwise-xor sum is $ x $ . Can you help Mahmoud answer the queries?

A subsequence can contain elements that are not neighboring.

## 输入格式

The first line contains integers $ n $ and $ q $ $ (1<=n,q<=10^{5}) $ , the number of elements in the array and the number of queries.

The next line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ $ (0<=a_{i}<2^{20}) $ , the elements of the array.

The next $ q $ lines, each contains integers $ l $ and $ x $ $ (1<=l<=n $ , $ 0<=x<2^{20}) $ , representing the queries.

## 输出格式

For each query, output its answer modulo $ 10^{9}+7 $ in a newline.

## 说明/提示

The bitwise-xor sum of the empty set is 0 and the bitwise-xor sum of a set containing one element is that element itself.

## 样例 #1

### 输入

```
5 5
0 1 2 3 4
4 3
2 0
3 7
5 7
5 8

```

### 输出

```
4
2
0
4
0

```

## 样例 #2

### 输入

```
3 2
1 1 1
3 1
2 0

```

### 输出

```
4
2

```

