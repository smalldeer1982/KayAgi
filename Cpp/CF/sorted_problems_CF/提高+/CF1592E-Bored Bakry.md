---
title: "Bored Bakry"
layout: "post"
diff: 提高+/省选-
pid: CF1592E
tag: []
---

# Bored Bakry

## 题目描述

Bakry got bored of solving problems related to xor, so he asked you to solve this problem for him.

You are given an array $ a $ of $ n $ integers $ [a_1, a_2, \ldots, a_n] $ .

Let's call a subarray $ a_{l}, a_{l+1}, a_{l+2}, \ldots, a_r $ good if $ a_l \, \& \, a_{l+1} \, \& \, a_{l+2} \, \ldots \, \& \, a_r > a_l \oplus a_{l+1} \oplus a_{l+2} \ldots \oplus a_r $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) and $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

Find the length of the longest good subarray of $ a $ , or determine that no such subarray exists.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the length of the array.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^6 $ ) — elements of the array.

## 输出格式

Print a single integer — the length of the longest good subarray. If there are no good subarrays, print $ 0 $ .

## 说明/提示

In the first case, the answer is $ 2 $ , as the whole array is good: $ 5 \& 6 = 4 > 5 \oplus 6 = 3 $ .

In the third case, the answer is $ 4 $ , and one of the longest good subarrays is $ [a_2, a_3, a_4, a_5] $ : $ 1\& 3 \& 3 \&1 = 1 > 1\oplus 3 \oplus 3\oplus 1 = 0 $ .

## 样例 #1

### 输入

```
2
5 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
2 4 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6
8 1 3 3 1 2
```

### 输出

```
4
```

