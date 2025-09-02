---
title: "Orray"
layout: "post"
diff: 普及+/提高
pid: CF1742G
tag: []
---

# Orray

## 题目描述

You are given an array $ a $ consisting of $ n $ nonnegative integers.

Let's define the prefix OR array $ b $ as the array $ b_i = a_1~\mathsf{OR}~a_2~\mathsf{OR}~\dots~\mathsf{OR}~a_i $ , where $ \mathsf{OR} $ represents the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR). In other words, the array $ b $ is formed by computing the $ \mathsf{OR} $ of every prefix of $ a $ .

You are asked to rearrange the elements of the array $ a $ in such a way that its prefix OR array is lexicographically maximum.

An array $ x $ is lexicographically greater than an array $ y $ if in the first position where $ x $ and $ y $ differ, $ x_i > y_i $ .

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ nonnegative integers $ a_1, \ldots, a_n $ ( $ 0 \leq a_i \leq 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case print $ n $ integers — any rearrangement of the array $ a $ that obtains the lexicographically maximum prefix OR array.

## 样例 #1

### 输入

```
5
4
1 2 4 8
7
5 1 2 3 4 5 5
2
1 101
6
2 3 4 2 3 4
8
1 4 2 3 4 5 7 1
```

### 输出

```
8 4 2 1 
5 2 1 3 4 5 5 
101 1 
4 3 2 2 3 4 
7 1 4 2 3 4 5 1
```

