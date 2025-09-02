---
title: "Keep XOR Low"
layout: "post"
diff: 省选/NOI-
pid: CF1616H
tag: ['动态规划 DP', '字典树 Trie']
---

# Keep XOR Low

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ and an integer $ x $ .

Find the number of non-empty subsets of indices of this array $ 1 \leq b_1 < b_2 < \ldots < b_k \leq n $ , such that for all pairs $ (i, j) $ where $ 1 \leq i < j \leq k $ , the inequality $ a_{b_i} \oplus a_{b_j} \leq x $ is held. Here, $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). As the answer may be very large, output it modulo $ 998\,244\,353 $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ x $ ( $ 1 \leq n \leq 150\,000 $ , $ 0 \leq x < 2^{30} $ ). Here, $ n $ is the size of the array.

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < 2^{30} $ ): the array itself.

## 输出格式

Print one integer: the number of non-empty subsets such that the bitwise XOR of every pair of elements is at most $ x $ , modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
4 2
0 1 2 3
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3 6
4 2 2
```

### 输出

```
7
```

## 样例 #3

### 输入

```
4 0
1 1 2 2
```

### 输出

```
6
```

