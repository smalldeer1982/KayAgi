---
title: "Divide OR Conquer"
layout: "post"
diff: 省选/NOI-
pid: CF2038D
tag: ['动态规划 DP', '树状数组', '动态规划优化']
---

# Divide OR Conquer

## 题目描述

You are given an array $ [a_1, a_2, \ldots a_n] $ consisting of integers between $ 0 $ and $ 10^9 $ . You have to split this array into several segments (possibly one) in such a way that each element belongs to exactly one segment.

Let the first segment be the array $ [a_{l_1}, a_{l_1 + 1}, \ldots, a_{r_1}] $ , the second segment be $ [a_{l_2}, a_{l_2+ 1}, \ldots, a_{r_2}] $ , ..., the last segment be $ [a_{l_k}, a_{l_k+ 1}, \ldots, a_{r_k}] $ . Since every element should belong to exactly one array, $ l_1 = 1 $ , $ r_k = n $ , and $ r_i + 1 = l_{i+1} $ for each $ i $ from $ 1 $ to $ k-1 $ . The split should meet the following condition: $ f([a_{l_1}, a_{l_1 + 1}, \ldots, a_{r_1}]) \le f([a_{l_2}, a_{l_2+ 1}, \ldots, a_{r_2}]) \le \dots \le f([a_{l_k}, a_{l_k+1}, \ldots, a_{r_k}]) $ , where $ f(a) $ is the bitwise OR of all elements of the array $ a $ .

Calculate the number of ways to split the array, and print it modulo $ 998\,244\,353 $ . Two ways are considered different if the sequences $ [l_1, r_1, l_2, r_2, \ldots, l_k, r_k] $ denoting the splits are different.

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10 ^9 $ ) — the elements of the given array.

## 输出格式

Print one integer — the number of ways to split the array, taken modulo $ 998\,244\,353 $ .

## 说明/提示

In the first two examples, every way to split the array is valid.

In the third example, there are three valid ways to split the array:

- $ k = 3 $ ; $ l_1 = 1, r_1 = 1, l_2 = 2, r_2 = 2, l_3 = 3, r_3 = 3 $ ; the resulting arrays are $ [3] $ , $ [4] $ , $ [6] $ , and $ 3 \le 4 \le 6 $ ;
- $ k = 2 $ ; $ l_1 = 1, r_1 = 1, l_2 = 2, r_2 = 3 $ ; the resulting arrays are $ [3] $ and $ [4, 6] $ , and $ 3 \le 6 $ ;
- $ k = 1 $ ; $ l_1 = 1, r_1 = 3 $ ; there will be only one array: $ [3, 4, 6] $ .

If you split the array into two arrays $ [3, 4] $ and $ [6] $ , the bitwise OR of the first array is $ 7 $ , and the bitwise OR of the second array is $ 6 $ ; $ 7 > 6 $ , so this way to split the array is invalid.

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1000 1000 1000 1000 1000
```

### 输出

```
16
```

## 样例 #3

### 输入

```
3
3 4 6
```

### 输出

```
3
```

